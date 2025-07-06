"""
    This file searches the operating system for executables
"""
import os
import sys
import subprocess

os.environ['DISPLAY'] = ':0'

def format_path(path: str):
    splits = path.split(' ')
    if len(splits) <= 1:
        return path # no need to format this, it has no spaces
    
    splits = [split.strip() + '\ ' for split in splits]
    splits[-1] = splits[-1].replace('\ ', '').strip()
    return r''.join(splits)

dsv = ''

if not os.path.isdir('/tmp/.xlunch'):
    os.mkdir('/tmp/.xlunch')
    
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
        os.system(f'sips -s format png {icon} --out /tmp/.xlunch/{name}.png')
        dsv += f'{name};/tmp/.xlunch/{name}.png;open /Applications/{format_path(app)}\n'

        MODE = '+x'

        if os.path.isfile('/tmp/.xlunch/entries.dsv'):
            MODE = 'w'

        with open('/tmp/.xlunch/entries.dsv', MODE) as f:
            print('USING MODE', MODE)
            f.write(dsv)
        os.system('xquartz')
        os.system('./xlunch --input /tmp/.xlunch/entries.dsv')