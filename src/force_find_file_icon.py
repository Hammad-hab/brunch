import os
import asyncio
from concurrent.futures import ThreadPoolExecutor

executor = ThreadPoolExecutor()

EXCLUDED_DIRS = {'/proc', '/dev', '/sys', '/run', '/var/lib', '/snap', '/bin', '/usr/bin', '/usr/local/bin'}

def should_skip(path):
    return any(path.startswith(exclude) for exclude in EXCLUDED_DIRS)

async def list_dirs_pngs(path, icon_name):
    def _listdir_sync():
        if should_skip(path):
            return [], []

        pngs = []
        subdirs = []

        try:
            with os.scandir(path) as entries:
                for entry in entries:
                    if entry.is_dir(follow_symlinks=False):
                        subdirs.append(entry.path)
                    elif entry.is_file() and icon_name in entry.name.lower():
                        pngs.append(entry.path)
        except Exception:
            return [], []

        return pngs, subdirs

    # Run the blocking scandir logic in a thread
    pngs, subdirs = await asyncio.get_event_loop().run_in_executor(executor, _listdir_sync)

    # Recurse into subdirectories
    tasks = [list_dirs_pngs(subdir, icon_name) for subdir in subdirs]
    results = await asyncio.gather(*tasks)

    # Flatten results
    for result in results:
        pngs.extend(result)

    return pngs

async def scan_all(root, icon_name):
    pngs = await list_dirs_pngs(root, icon_name)
    print(f"\nFound {len(pngs)} matching files:")
    for path in pngs:
        print(path)
    return pngs

# 🚀 Entry point
if __name__ == "__main__":
    import sys
    icon_name = sys.argv[1] if len(sys.argv) > 1 else "icon"  # default search
    asyncio.run(scan_all("/", icon_name))
