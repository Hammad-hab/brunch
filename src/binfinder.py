"""
    This file searches the operating system for executables
"""
import os
import sys
import glob
import configparser

os.environ['DISPLAY'] = ':0'

if not os.path.isfile('./xlunch'):
    print('Make file not found, building app...')
    os.system("make") # build the package

def find_linux_icon_file(icon_name):
    # Try hicolor theme sizes
    for size in ['16x16', '32x32', '48x48', '64x64', '128x128', '256x256']:
        path = f'/usr/share/icons/hicolor/{size}/apps/{icon_name}.png'
        if os.path.isfile(path):
            return path
        path = f'/usr/share/icons/hicolor/{size}/apps/{icon_name}.svg'
        if os.path.isfile(path):
            return path

    # Try pixmaps
    for ext in ['png', 'svg', 'xpm']:
        path = f'/usr/share/pixmaps/{icon_name}.{ext}'
        if os.path.isfile(path):
            return path

    # Try generic catch-all glob
    matches = glob.glob(f'/usr/share/icons/**/{icon_name}.*', recursive=True)
    if matches:
        return matches[0]

    return ''

def generate_dsv():
    dsv = ''
    if sys.platform == 'darwin':
        apps = os.listdir('/Applications')
        for app in apps:
            if app.startswith('.'): # file not meant to be seen
                continue
            path = f'/Applications/{app}/Contents/Resources'
            name = app.replace('.app', '')
            if not os.path.isdir(path): continue
            reasources = (os.listdir(path))
            reasources = [reasource for reasource in reasources if '.icns' in reasource]
            icon = f'/Applications/{app}/Contents/Resources/{reasources[0]}' 
            os.system(f'sips -s format png "{icon}" --out /tmp/.xlunch/{name.replace(" ", "_")}.png')
            dsv += f'{name};/tmp/.xlunch/{name.replace(" ", "_")}.png;open /Applications/{app}\n'

    elif sys.platform == 'linux':
        dir_path = '/usr/share/applications'
        apps = os.listdir(dir_path)

        for app in apps:
            if app.endswith('.desktop'):
                full_path = os.path.join(dir_path, app)

                p = configparser.ConfigParser(interpolation=None)
                p.optionxform = str  # preserve case
                p.read(full_path)

                if 'Desktop Entry' not in p:
                    continue

                entry = p['Desktop Entry']
                name = entry.get('Name')
                exec_cmd = entry.get('Exec')
                icon = entry.get('Icon')

                if not name or not exec_cmd:
                    continue

                # Try to resolve icon file
                icon_path = ''
    
                if icon:
                    if os.path.isabs(icon) and os.path.isfile(icon):
                        icon_path = icon
                    else:
                        icon_path = find_linux_icon_file(icon)

                if not icon_path:
                    icon_path = ''  # fallback empty icon

                # Add to DSV
                dsv += f'{name};{icon_path};{exec_cmd}\n'
    return dsv

if not os.path.isdir('/tmp/.xlunch'):
    os.mkdir('/tmp/.xlunch')

if not os.path.isfile('/tmp/.xlunch/entries.dsv'):
    dsv = generate_dsv()
    # Write the DSV file
    MODE = '+x'
    if os.path.isfile('/tmp/.xlunch/entries.dsv'):
        MODE = 'w'

    with open('/tmp/.xlunch/entries.dsv', MODE) as f:
        print('USING MODE', MODE)
        f.write(dsv)

os.system('./xlunch --input /tmp/.xlunch/entries.dsv')