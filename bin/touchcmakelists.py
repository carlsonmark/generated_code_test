#!/usr/bin/python3

import sys
from pathlib import Path


def filesMatch(path1, path2):
    p1 = Path(path1)
    files1 = sorted([f.name.replace('.in','') for f in p1.glob('*.in')])
    p2 = Path(path2)
    files2 = sorted([f.name.replace('.hpp','') for f in p2.glob('*.hpp')])
    matched = files1 == files2
    # Remove any generated files in p2 that are not in p1
    for fn in files1:
        try:
            files2.remove(fn)
        except: pass
    removed = False
    for fn in files2:
        removed = True
        print('Deleting', fn)
        p2.joinpath(Path(fn+'.hpp')).unlink()
        p2.joinpath(Path(fn+'.cpp')).unlink()
    return matched, removed

if __name__ == '__main__':
    match, removed = filesMatch(sys.argv[2], sys.argv[3])
    if not match:
        Path(sys.argv[1]).touch()
        print('!'*79)
        print('! Generated files changed.')
        print('! Please re-build.')
        print('!'*79)
        sys.exit(100)
