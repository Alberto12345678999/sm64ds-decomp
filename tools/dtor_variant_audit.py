#!/usr/bin/env python3
"""Check every destructor-variant symbol against the one thing the ROM decides.

The Itanium ABI gives a polymorphic class up to three destructors:

    D0  deleting     -- in the vtable, and calls operator delete
    D1  complete     -- in the vtable
    D2  base-object  -- NEVER in a vtable; only ever reached by a direct `bl`
                        from a derived class's destructor

That last line is a hard structural fact, not a heuristic, and it is decidable
from `config/**/relocs.txt` alone:

    a `kind:load` reloc pointing at a function == that function's address was
    taken as data == it sits in a table.  For a destructor, the only table it
    can sit in is a vtable.

So:

    a symbol named ...D2Ev that a load-reloc points at   -> cannot be a D2

The inverse direction needs one more condition, and getting it wrong produces a
false positive. "A D1 always sits in a vtable" holds only for a **polymorphic**
class; a class with no virtual functions has a D1 that is simply called, and no
vtable for it to sit in. So:

    a symbol named ...D1Ev that no load-reloc points at
      AND that itself stores a known vtable address       -> cannot be a D1

The second clause is the polymorphism test, and it is read from the ROM rather
than from a name: a destructor of a polymorphic class always writes its class's
vptr, which appears as a load-reloc *from* inside the function *to* a vtable VA
that `build/rtti.json` knows. Without it this tool flagged
`_ZN8Particle10SysTrackerD1Ev` -- a correctly-named D1 of a non-polymorphic class
that writes no vptr at all.

Both directions are reported, because they are each other's control: if the
forward rule were noise, the inverse list would fill up with ordinary
destructors.

For every offender the tool resolves the referencing address back through
`build/rtti.json` to the owning class and slot index, which names what the
symbol should have been.

That rule decides `D2` versus `{D0, D1}` and stops there.  It cannot separate a
D0 from a D1, because both sit in a vtable, so a D0/D1 swap passes it silently.
**Slot position is what separates them**, and it is the same kind of structural
fact rather than a heuristic:

    the ABI emits the destructor pair adjacently, complete first
      -> slot N is the D1 and slot N+1 is the D0, never the reverse

so a vtable holding a `...D0Ev` immediately above a `...D1Ev` has the two names
on the wrong bodies.  A pair is checked once per *body*, not once per table:
a derived class that does not override its destructor inherits the base's two
slots verbatim, so one swap in a base would otherwise be reported once for every
class beneath it.

    python tools/dtor_variant_audit.py            # report
    python tools/dtor_variant_audit.py --json     # machine-readable

Nothing is written.  Renaming is a separate, gated change: a symbol rename is a
`config/**/symbols.txt` edit plus a source rewrite plus a file move, and
`notes/rtti-reconciliation.md` section 9 records a rename of this exact shape
dropping module fidelity 106/106 -> 104/106.
"""

import argparse
import collections
import glob
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
RTTI = os.path.join(ROOT, "build", "rtti.json")

SYM_RE = re.compile(r"(\S+)\s+kind:\w+\([^)]*\)\s+addr:(0x[0-9a-fA-F]+)")
FUNC_RE = re.compile(r"(\S+)\s+kind:function\([^)]*\)\s+addr:(0x[0-9a-fA-F]+)")
RELOC_RE = re.compile(r"from:(0x[0-9a-fA-F]+)\s+kind:(\w+)\s+to:(0x[0-9a-fA-F]+)")

# Hard cap on how far past a vtable's start the reverse lookup will search, for
# the last vtable in a module where no successor bounds it.  Every other vtable
# is bounded by the next vtable start in the same module -- a fixed window
# instead mis-attributes, because vtables are packed tightly: dBgCh's successor
# begins 11 slots later, so a 256-slot window swallowed three sibling tables and
# reported "dBgCh slot 108" for an address that is not in dBgCh's vtable at all.
MAX_VTABLE_BYTES = 0x400


def module_of(path):
    return os.path.basename(os.path.dirname(path))


FUNC_SIZE_RE = re.compile(
    r"(\S+)\s+kind:function\([^,]*,size=(0x[0-9a-fA-F]+)\)\s+addr:(0x[0-9a-fA-F]+)")


def load_functions():
    """module -> {addr: (symbol, size)} for every function symbol."""
    out = {}
    for p in glob.glob(os.path.join(ROOT, "config", "**", "symbols.txt"), recursive=True):
        mod = module_of(p)
        with open(p, encoding="utf-8") as fh:
            for ln in fh:
                s = ln.strip()
                m = FUNC_SIZE_RE.match(s)
                if m:
                    out.setdefault(mod, {})[int(m.group(3), 16)] = (m.group(1),
                                                                    int(m.group(2), 16))
                    continue
                m = FUNC_RE.match(s)
                if m:
                    out.setdefault(mod, {})[int(m.group(2), 16)] = (m.group(1), 0)
    return out


def load_outgoing():
    """module -> sorted [(from_addr, target_addr)] for every kind:load reloc."""
    out = collections.defaultdict(list)
    for p in glob.glob(os.path.join(ROOT, "config", "**", "relocs.txt"), recursive=True):
        mod = module_of(p)
        with open(p, encoding="utf-8") as fh:
            for ln in fh:
                m = RELOC_RE.search(ln)
                if m and m.group(2) == "load":
                    out[mod].append((int(m.group(1), 16), int(m.group(3), 16)))
    for v in out.values():
        v.sort()
    return out


def load_data_refs():
    """module -> {target_addr: [(module, from_addr), ...]} for kind:load relocs."""
    out = collections.defaultdict(lambda: collections.defaultdict(list))
    for p in glob.glob(os.path.join(ROOT, "config", "**", "relocs.txt"), recursive=True):
        mod = module_of(p)
        with open(p, encoding="utf-8") as fh:
            for ln in fh:
                m = RELOC_RE.search(ln)
                if m and m.group(2) == "load":
                    out[mod][int(m.group(3), 16)].append((mod, int(m.group(1), 16)))
    return out


def load_vtables():
    """module -> sorted [(vtable_va, end_va, class)] from the ROM's RTTI records.

    Each vtable is bounded by the *next* vtable start in the same module. That
    bound is what makes the slot attribution trustworthy; see MAX_VTABLE_BYTES.
    """
    if not os.path.exists(RTTI):
        return None
    data = json.loads(open(RTTI, encoding="utf-8").read())
    by_mod = collections.defaultdict(list)
    for rec in data["records"].values():
        if rec.get("vtable"):
            by_mod[rec["vtable_module"]].append((int(rec["vtable"], 16), rec["name"]))
    out = {}
    for mod, entries in by_mod.items():
        entries.sort()
        spans = []
        for i, (va, cls) in enumerate(entries):
            nxt = entries[i + 1][0] if i + 1 < len(entries) else va + MAX_VTABLE_BYTES
            spans.append((va, min(nxt, va + MAX_VTABLE_BYTES), cls))
        out[mod] = spans
    return out


def locate(vtables, mod, addr):
    """Resolve a referencing address to (class, slot) if it lands in a vtable.

    Returns None when the address is inside no known vtable -- reported as such
    rather than guessed, since a wrong class here names the wrong symbol.
    """
    if not vtables:
        return None
    for va, end, cls in vtables.get(mod, ()):
        if va <= addr < end and (addr - va) % 4 == 0:
            return cls, (addr - va) // 4
    return None


def dtor_kind(name):
    """D0/D1/D2 for a destructor-variant symbol, else None."""
    for suffix in ("D0Ev", "D1Ev", "D2Ev"):
        if name.endswith(suffix):
            return suffix[:2]
    return None


def slot_order():
    """Check the vtable destructor pair: D1 at slot N, D0 at slot N+1.

    `audit()` decides D2 versus {D0, D1}. It cannot go further, because both a D0
    and a D1 sit in a vtable and the reloc kind is identical for the two. Slot
    order is the remaining structural signal: the ABI lays the pair down
    adjacently with the complete destructor first, so a table holding D0 above D1
    has the names swapped.

    Read the same way as the rest of this tool -- from the ROM. A `kind:load`
    reloc *from* an address inside a known vtable *to* a function is one slot, and
    `build/rtti.json` bounds the table, so the slot index is exact rather than
    inferred from a name.

    Results are keyed by the pair of *bodies*, not by the table they appear in.
    A derived class that does not override its destructor reuses the base's two
    function addresses in its own slots, so a single swap in a base class would
    otherwise be reported once per descendant -- the shape that makes a two-row
    finding look like a forty-row one.

    Returns None when build/rtti.json is absent; there is no slot index without it.
    """
    funcs = load_functions()
    vtables = load_vtables()
    outgoing = load_outgoing()
    if not vtables:
        return None

    def sym_at(mod, addr):
        """The function symbol at a vtable slot's target, same-module then arm9.

        Not a flat address map: overlays share address ranges, so a global lookup
        would resolve an ov002 slot to whatever overlay happened to be indexed
        last at that VA.
        """
        hit = funcs.get(mod, {}).get(addr)
        if hit is None and mod != "arm9":
            hit = funcs.get("arm9", {}).get(addr)
        return hit[0] if hit else None

    # (module, class) -> {slot: (symbol, kind)}, destructor slots only.
    tables = collections.defaultdict(dict)
    for mod, entries in outgoing.items():
        for frm, tgt in entries:
            loc = locate(vtables, mod, frm)
            if not loc:
                continue
            name = sym_at(mod, tgt)
            if not name:
                continue
            kind = dtor_kind(name)
            # D2s in a vtable are the other rule's finding; including them here
            # would report #1203's category a second time under a new name.
            if kind in ("D0", "D1"):
                tables[(mod, loc[0])][loc[1]] = (name, kind)

    swapped, anomalous, unpaired = {}, {}, {}
    counts = collections.Counter()
    for (mod, cls), slots in sorted(tables.items()):
        paired = set()
        for slot in sorted(slots):
            if slot in paired or slot + 1 not in slots:
                continue
            paired.add(slot)
            paired.add(slot + 1)
            (lo_sym, lo_kind), (hi_sym, hi_kind) = slots[slot], slots[slot + 1]
            key = (lo_sym, hi_sym)
            row = {"low": {"symbol": lo_sym, "kind": lo_kind, "slot": slot},
                   "high": {"symbol": hi_sym, "kind": hi_kind, "slot": slot + 1}}
            if lo_kind == "D1" and hi_kind == "D0":
                counts["pairs_ok"] += 1
                continue
            bucket = swapped if (lo_kind == "D0" and hi_kind == "D1") else anomalous
            bucket.setdefault(key, dict(row, tables=[]))["tables"].append(
                {"module": mod, "class": cls})
        for slot in sorted(slots):
            if slot not in paired:
                sym, kind = slots[slot]
                unpaired.setdefault(sym, {"symbol": sym, "kind": kind, "tables": []})
                unpaired[sym]["tables"].append(
                    {"module": mod, "class": cls, "slot": slot})

    def rows(d):
        return sorted(d.values(), key=lambda r: r.get("symbol") or r["low"]["symbol"])

    return {
        "counts": dict(counts),
        "swapped": rows(swapped),
        "anomalous_pairs": rows(anomalous),
        "unpaired": rows(unpaired),
    }


def audit():
    funcs = load_functions()
    refs = load_data_refs()
    vtables = load_vtables()
    outgoing = load_outgoing()

    # Every vtable VA the ROM knows about, for the polymorphism test.
    vtable_vas = set()
    if vtables:
        for spans in vtables.values():
            for va, _end, _cls in spans:
                vtable_vas.add(va)

    def referenced(mod, addr):
        """Every load-reloc pointing at addr, from any module that can mean it.

        Which modules count depends on where the *target* lives, because overlays
        share address ranges and arm9 does not:

          target in arm9      every module. arm9 is always mapped and no overlay
                              is mapped over it, so an ov002 reloc to an arm9 VA
                              can only mean that arm9 function. Searching just
                              {arm9} here hid `_ZN8CapEnemyD2Ev` -- an arm9 D2
                              sitting in ov002's `dCapEnemy_c` vtable, which is a
                              D2-in-a-vtable that the first sweep never saw.
          target in an overlay  that overlay, plus arm9. A reloc from a *different*
                              overlay to the same VA addresses whatever its own
                              module has there, not this function.
        """
        if mod == "arm9":
            hits = []
            for hmod in refs:
                hits += refs[hmod].get(addr, [])
            return hits
        hits = list(refs.get(mod, {}).get(addr, []))
        hits += refs.get("arm9", {}).get(addr, [])
        return hits

    def writes_vptr(mod, addr, size):
        """Does this function store a known vtable address? -> its class is polymorphic.

        Read from the ROM, not from the symbol's name: a destructor of a
        polymorphic class always writes its class's vptr.
        """
        if not vtable_vas or not size:
            return None  # undecidable; reported as such rather than guessed
        for frm, tgt in outgoing.get(mod, ()):
            if addr <= frm < addr + size and tgt in vtable_vas:
                return True
        return False

    counts = collections.Counter()
    d2_in_vtable, d1_orphaned = [], []

    for mod, table in sorted(funcs.items()):
        for addr, (name, size) in sorted(table.items()):
            if name.endswith("D2Ev"):
                kind = "D2"
            elif name.endswith("D1Ev"):
                kind = "D1"
            elif name.endswith("D0Ev"):
                kind = "D0"
            else:
                continue
            counts[kind] += 1
            hits = referenced(mod, addr)
            if kind == "D2" and hits:
                sites = []
                for hmod, hfrom in hits:
                    loc = locate(vtables, hmod, hfrom)
                    sites.append({
                        "from": "0x%08x" % hfrom,
                        "class": loc[0] if loc else None,
                        "slot": loc[1] if loc else None,
                    })
                d2_in_vtable.append({"module": mod, "addr": "0x%08x" % addr,
                                     "symbol": name, "sites": sites})
            elif kind == "D1" and not hits:
                poly = writes_vptr(mod, addr, size)
                if poly is False:
                    counts["D1_orphan_nonpolymorphic"] += 1
                    continue  # a non-polymorphic class's D1 has no vtable to sit in
                d1_orphaned.append({"module": mod, "addr": "0x%08x" % addr,
                                    "symbol": name, "polymorphic": poly})

    return {
        "counts": dict(counts),
        "d2_in_vtable": d2_in_vtable,
        "d1_not_in_any_vtable": d1_orphaned,
        "rtti_available": vtables is not None,
    }


def discover():
    """Find D2s the tree has never named -- `func_*` symbols that are base-object dtors.

    The audit above can only judge symbols that already claim to be a destructor.
    A genuine D2 sitting under a `func_*` name is invisible to it, and those exist:
    `include/MeshColliderBase.h` names two by hand, and the Fader family holds two
    more. This is the discovery direction.

    A base-object destructor has a signature no other function shares:

      * nothing takes its address -- no `kind:load` reloc points at it
      * it stores a vtable address, so its class is polymorphic
      * every caller reaches it by `bl`

    and the vtable it stores **names the owning class**, because a D2 writes its own
    class's vptr. Where base destructors were inlined into it, more than one vtable
    is written; the one at the lowest address inside the function is its own, and
    the rest belong to ancestors, so they are reported rather than collapsed.

    This proposes; it does not rename. Each candidate still wants its size checked
    against the class's D1 (a D2 and D1 of the same class are usually identical) and
    its callers eyeballed.
    """
    funcs = load_functions()
    refs = load_data_refs()
    vtables = load_vtables()
    outgoing = load_outgoing()
    if not vtables:
        return []

    vt_owner = {}
    for mod, spans in vtables.items():
        for va, _end, cls in spans:
            vt_owner[(mod, va)] = cls

    # Reverse index of call targets, so each candidate can show who reaches it.
    callers = collections.defaultdict(list)
    for p in glob.glob(os.path.join(ROOT, "config", "**", "relocs.txt"), recursive=True):
        mod = module_of(p)
        with open(p, encoding="utf-8") as fh:
            for ln in fh:
                m = RELOC_RE.search(ln)
                if m and m.group(2).startswith("arm_call"):
                    callers[int(m.group(3), 16)].append((mod, int(m.group(1), 16)))

    out = []
    for mod, table in sorted(funcs.items()):
        for addr, (name, size) in sorted(table.items()):
            if not name.startswith("func_") or not size:
                continue
            if refs.get(mod, {}).get(addr) or refs.get("arm9", {}).get(addr):
                continue                       # address taken -> in a table, not a D2
            written = []
            for frm, tgt in outgoing.get(mod, ()):
                if addr <= frm < addr + size:
                    owner = vt_owner.get((mod, tgt)) or vt_owner.get(("arm9", tgt))
                    if owner:
                        written.append((frm, owner))
            if not written:
                continue
            written.sort()
            who = callers.get(addr, [])
            if not who:
                continue                       # never called: not a base-object routine
            names = sorted({funcs.get(m, {}).get(_nearest(funcs.get(m, {}), a), ("?", 0))[0]
                            for m, a in who})

            # A C2 has the SAME signature as a D2 -- never in a vtable, writes a vptr,
            # only ever called directly. Two independent things separate them:
            #
            #   callers     a D2 is called by derived DESTRUCTORS, a C2 by derived
            #               CONSTRUCTORS
            #   write order a destructor writes own vptr then its bases', so its own
            #               class is written FIRST; a constructor builds base-up, so
            #               its own class is written LAST
            #
            # Without this every constructor in the tree came back as a D2 proposal.
            dtor_callers = sum(1 for n in names if n.endswith(("D0Ev", "D1Ev", "D2Ev")))
            ctor_callers = sum(1 for n in names if n.endswith(("C1Ev", "C2Ev", "C3Ev")))
            if ctor_callers > dtor_callers:
                kind, owner = "C2", written[-1][1]
            elif dtor_callers > ctor_callers:
                kind, owner = "D2", written[0][1]
            else:
                kind, owner = "unknown", written[0][1]

            out.append({
                "module": mod, "addr": "0x%08x" % addr, "symbol": name,
                "size": "0x%x" % size, "kind": kind, "owner": owner,
                "rom_chain": [o for _f, o in written],
                "callers": ["%s:0x%08x" % (m, a) for m, a in who],
                "caller_names": names,
            })
    return out


def tree_names():
    """ROM class name -> the tree's name for it, where rtti_reconcile proved one."""
    p = os.path.join(ROOT, "build", "rtti_reconcile.json")
    if not os.path.exists(p):
        return {}
    data = json.loads(open(p, encoding="utf-8").read())
    return {r["rom_name"]: r["tree_name"] for r in data.get("rows", []) if r.get("tree_name")}


def propose(cls, kind, tree):
    """The Itanium symbol for `cls`'s D2/C2, or None when it cannot be spelt safely.

    Only simple (non-nested) names are proposed. A nested class mangles as
    `_ZN...E`-with-components and guessing it wrong writes a symbol that resolves to
    nothing, so those are reported as a class and left for a human.
    """
    name = tree.get(cls) or cls
    if kind not in ("D2", "C2") or "::" in name or not name.isidentifier():
        return None
    return "_ZN%d%s%sEv" % (len(name), name, kind)


def _nearest(table, addr):
    """The start address of the function containing `addr`."""
    best = None
    for a in table:
        if a <= addr and (best is None or a > best):
            best = a
    return best


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--discover", action="store_true",
                    help="propose names for D2s that were never named at all")
    args = ap.parse_args()

    if args.discover:
        cands = discover()
        if args.json:
            print(json.dumps(cands, indent=2))
            return 0
        tree = tree_names()
        by_kind = collections.Counter(c["kind"] for c in cands)
        print("unnamed base-object routine candidates: %d D2, %d C2, %d undecided\n"
              % (by_kind["D2"], by_kind["C2"], by_kind["unknown"]))
        for want in ("D2", "C2", "unknown"):
            rows = [c for c in cands if c["kind"] == want]
            if not rows:
                continue
            print("== %s (%d)" % (want, len(rows)))
            for c in rows:
                sym = propose(c["owner"], c["kind"], tree)
                treename = tree.get(c["owner"])
                print("  %-18s %s  %-6s %s" % (c["symbol"], c["addr"], c["size"], c["module"]))
                print("      class %s%s  ->  %s"
                      % (c["owner"],
                         " (tree: %s)" % treename if treename else "",
                         sym or "no safe spelling -- nested or unnamed in the tree"))
                if len(c["rom_chain"]) > 1:
                    print("      vptr writes in order: %s" % " -> ".join(c["rom_chain"]))
                print("      called by: %s" % ", ".join(c["caller_names"][:5]))
            print()
        print("Proposals, not conclusions. Each still wants its size compared against the")
        print("class's D1/C1 and its callers read. Nothing is renamed by this tool.")
        return 0

    res = audit()
    res["slot_order"] = slot_order()
    if args.json:
        print(json.dumps(res, indent=2))
        return 0

    c = res["counts"]
    print("destructor-variant symbols: D0 %d   D1 %d   D2 %d"
          % (c.get("D0", 0), c.get("D1", 0), c.get("D2", 0)))
    if not res["rtti_available"]:
        print("  (build/rtti.json absent -- run tools/rtti_extract.py --report --check")
        print("   for the owning class and slot of each offender)")
    print()

    bad = res["d2_in_vtable"]
    print("D2 symbols a load-reloc points at -- a D2 is never in a vtable (%d):" % len(bad))
    for r in bad:
        print("  %-30s %s  %s" % (r["symbol"], r["addr"], r["module"]))
        for s in r["sites"]:
            if s["class"] is not None:
                print("      <- %s slot %d" % (s["class"], s["slot"]))
            else:
                print("      <- %s (not inside a known vtable)" % s["from"])
    print()

    orph = res["d1_not_in_any_vtable"]
    print("D1 symbols in no vtable, whose class IS polymorphic -- so not D1s (%d):"
          % len(orph))
    for r in orph:
        note = "" if r.get("polymorphic") else "   (polymorphism undecidable)"
        print("  %-30s %s  %s%s" % (r["symbol"], r["addr"], r["module"], note))
    skipped = res["counts"].get("D1_orphan_nonpolymorphic", 0)
    print("  (%d further D1s sit in no vtable because their class is not polymorphic;"
          % skipped)
    print("   they write no vptr, so they are correctly named and are not listed)")

    print()
    print("These two lists are each other's control. A rule that fired on noise would")
    print("put ordinary destructors in the second list.")

    slots = res["slot_order"]
    print()
    if slots is None:
        print("slot order: not checked (build/rtti.json absent)")
        return 0

    ok = slots["counts"].get("pairs_ok", 0)
    print("D0/D1 slot order -- the ABI lays the pair down D1 first, D0 next (%d pairs ok):"
          % ok)
    for r in slots["swapped"]:
        print("  SWAPPED  %s at slot %d, above %s at slot %d"
              % (r["low"]["symbol"], r["low"]["slot"],
                 r["high"]["symbol"], r["high"]["slot"]))
        print("      in: %s" % ", ".join("%s/%s" % (t["module"], t["class"])
                                         for t in r["tables"][:5]))
    for r in slots["anomalous_pairs"]:
        print("  ODD PAIR %s(%s) then %s(%s) at slots %d,%d"
              % (r["low"]["symbol"], r["low"]["kind"],
                 r["high"]["symbol"], r["high"]["kind"],
                 r["low"]["slot"], r["high"]["slot"]))
        print("      in: %s" % ", ".join("%s/%s" % (t["module"], t["class"])
                                         for t in r["tables"][:5]))
    if not slots["swapped"] and not slots["anomalous_pairs"]:
        print("  none -- every destructor pair in every known vtable is D1 then D0")
    if slots["unpaired"]:
        print("  (%d destructor symbols sit in a vtable slot with no destructor in the"
              % len(slots["unpaired"]))
        print("   adjacent slot; the rule cannot judge those, so they are not a finding)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
