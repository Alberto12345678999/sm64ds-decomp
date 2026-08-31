"""Census a dScMgBase_c vtable slot straight out of the cartridge.

Answers "which classes override slot N, and at what address" WITHOUT trusting
any worklist, any `recovered name:` comment, or any header.  Run it before
applying a slot: the count it prints is the number of override files the apply
step must touch, and a mismatch means an override is about to be silently
skipped -- which is a DIFFERS, not a warning.

Two gotchas it already handles:
  * `_ZTV<class>` in symbols.txt points at SLOT 0, not at the address point.
    There is no 2-word offset-to-top/typeinfo header inside the symbol's range
    (dsd cuts it off), so index == slot with no bias.
  * `dMgJump3DMario_c` and `dMg3DHeyhoObjAdapter_c` are NOT dScMgBase_c
    descendants.  Their tables are a different shape (alternating 0 words) and
    reading index N in them returns garbage that never equals the base's, so
    they look like an override at EVERY slot.  They are excluded by name.

Usage: python slot_census.py 24 25 26        (from the worktree root)
"""
import glob
import os
import re
import sys

import yaml

NOT_DESCENDANTS = {'_ZTV16dMgJump3DMario_c', '_ZTV22dMg3DHeyhoObjAdapter_c'}
BASE_VT = ('ov004', 0x020BC0C0)


def _images():
    cfg = yaml.safe_load(open('extracted/dsd/arm9_overlays/overlays.yaml'))['overlays']
    img = {}
    for o in cfg:
        p = 'extracted/overlays/overlay_%04d.bin' % o['id']
        if os.path.exists(p):
            img['ov%03d' % o['id']] = (o['base_address'], open(p, 'rb').read())
    return img


def _vtables():
    vt = {}
    for sf in glob.glob('config/arm9/overlays/*/symbols.txt'):
        mod = os.path.basename(os.path.dirname(sf))
        for line in open(sf, encoding='utf-8', errors='ignore'):
            m = re.match(r'(_ZTV\S+)\s+kind:data\S*\s+addr:0x([0-9a-fA-F]+)', line)
            if m:
                vt[m.group(1)] = (mod, int(m.group(2), 16))
    return vt


def census(slot, img=None, vt=None):
    img = img or _images()
    vt = vt or _vtables()
    b0, d0 = img[BASE_VT[0]]
    o0 = BASE_VT[1] - b0 + slot * 4
    base = int.from_bytes(d0[o0:o0 + 4], 'little')
    inherit, over = 0, []
    for name, (mod, addr) in sorted(vt.items()):
        if not ('dScMg' in name or 'dMg' in name):
            continue
        if name == '_ZTV11dScMgBase_c' or name in NOT_DESCENDANTS:
            continue
        if name.startswith('_ZTVN') or mod not in img:
            continue
        b, d = img[mod]
        o = addr - b + slot * 4
        w = int.from_bytes(d[o:o + 4], 'little')
        if w == base:
            inherit += 1
        else:
            over.append((name[4:].lstrip('0123456789'), mod, w))
    return base, inherit, over


if __name__ == '__main__':
    img, vt = _images(), _vtables()
    for s in (int(a) for a in sys.argv[1:]):
        base, inherit, over = census(s, img, vt)
        print('slot %-2d  base 0x%08x  tables %d  inherit %d  OVERRIDE %d'
              % (s, base, inherit + len(over), inherit, len(over)))
        for cls, mod, w in over:
            print('    %-24s %s 0x%08x' % (cls, mod, w))
