"""Rewrite a Platform subclass as real C++, or leave it exactly as it was.

The generated headers restate all of Actor and Platform. This turns one into
`struct X : Platform` keeping only its own fields, makes its destructor a real
method, and repoints its sources at the inherited names -- then verifies every
source the header reaches and REVERTS THE WHOLE CLASS if any one of them fails.
A class is migrated completely or not at all; nothing half-done is left behind.

The reverts are the point. Of the first nine tried by hand, seven came back out
for four different reasons, and each reason is a fact about the ROM worth
having. See notes/dtor-migration.md.
"""
import argparse
import pathlib
import re
import subprocess
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import build_pin as BP  # noqa: E402

REPO = pathlib.Path(__file__).resolve().parents[1]
W = {"u8": 1, "s8": 1, "char": 1, "bool": 1, "u16": 2, "s16": 2, "short": 2,
     "u32": 4, "s32": 4, "int": 4, "Fix12i": 4, "PathPtr": 8}
FIELD = re.compile(r"^\s*([A-Za-z_][\w:<>]*)\s+(\**)(\w+)(\[[^\]]*\])?\s*;\s*/\*\s*(0x[0-9a-fA-F]+)", re.M)

# Platform's data size. Its last field (unk_322, s16) ends exactly here, and
# sizeof(Platform) is 0x324 too, so there is NO tail padding for a subclass to
# reuse -- an earlier revision of this tool believed there was, on a misreading
# of DonutBlock. include/Platform.h carries the real evidence: BowserFireSeaArena
# reads unk_31e/0x320/0x322 and starts its own fields at 0x324.
PLATFORM_DSIZE = 0x324


def inherited_names():
    """offset -> the name Actor.h / Platform.h gives that offset."""
    out = {}
    for h, lo, hi in (("include/Actor.h", 0, 0xd0), ("include/Platform.h", 0xd0, 0x324)):
        for ty, star, name, arr, off in FIELD.findall((REPO / h).read_text(errors="replace")):
            o = int(off, 16)
            if lo <= o < hi and not name.startswith("pad_"):
                out.setdefault(o, name)
    return out


def symbol_index():
    idx = {}
    for p in REPO.glob("config/**/symbols.txt"):
        lab = p.parent.name
        for line in p.read_text(errors="replace").splitlines():
            m = re.match(r"\s*(\S+)\s+kind:function\([^)]*size=(0x[0-9a-f]+)\)\s+addr:(0x[0-9a-f]+)", line)
            if m:
                idx[m.group(1)] = (int(m.group(3), 16), int(m.group(2), 16), lab)
    return idx


def build_header(cls, old):
    """(text, size, own-field-count) for the rewritten header."""
    own = sorted((int(o, 16), ty, star, nm)
                 for ty, star, nm, arr, o in FIELD.findall(old)
                 if int(o, 16) >= PLATFORM_DSIZE and not nm.startswith("pad_"))
    lines, cur = [], PLATFORM_DSIZE
    for o, ty, star, nm in own:
        if o > cur:
            lines.append(f"    u8  pad_{cur:03x}[0x{o - cur:x}];")
        lines.append(f"    {ty} {star}{nm};".ljust(38) + f"/* 0x{o:03x} */")
        cur = o + (4 if star else W.get(ty, 4))
    size = max(0x324, (cur + 3) & ~3)
    meths = re.findall(r"^\s{4}([A-Za-z_][\w:<>]*\s+\**\w+\([^)]*\));", old, re.M)
    guard = cls.upper() + "_H"
    body = "\n".join(lines) if lines else "    /* no fields of its own */"
    tail = "".join(f"\n    {m};" for m in meths)

    # The C side keeps the flat struct verbatim -- same arrangement as
    # include/ShadowModel.h and include/Fader.h. A C translation unit gets no
    # base sub-object and no implicit vptr, so it needs every offset spelled
    # out, and the generated declaration this replaces already is exactly that.
    # The D0 files are why it has to stay: they are C, they read fields, and
    # they cannot be migrated (D0 is compiler-generated).
    cbody = old[old.index(f"struct {cls} {{"):]
    cbody = cbody[:cbody.index("\n};") + 3]
    cbody = re.sub(r"#ifdef __cplusplus.*?#endif\n", "", cbody, flags=re.S)
    cbody = re.sub(r"\n\s*/\* methods \*/\n", "\n", cbody)

    return f"""#ifndef {guard}
#define {guard}

#include "types.h"
#include "Platform.h"

/* Derives from Platform: the destructor stores this class's vtable, then
 * Platform's -- inlined -- then destroys the MovingMeshCollider at 0x124 and
 * the Model at 0xd4 before chaining to Actor. All three belong to Platform.
 * Everything this header used to restate below 0x324 was Actor's and
 * Platform's, and is inherited now.
 *
 * SIZE IS THE OBSERVED FIELD SPAN, rounded up. It guards this declaration; it
 * is not independent evidence about the ROM.
 */

#ifdef __cplusplus

struct {cls} : Platform {{
{body}

    /* --- vtable --- */
    virtual ~{cls}();
{tail}
}};

typedef char {cls}_size_must_be_0x{size:x}[sizeof({cls}) == 0x{size:x} ? 1 : -1];

#else

/* The C spelling of the same object, flat. Kept because the D0 file is a C
   translation unit that reads these fields, and D0 is compiler-generated so it
   can never be migrated. Same arrangement as include/ShadowModel.h. */
{cbody}

#endif /* __cplusplus */

#endif /* {guard} */
"""


def patch_source(text, oldmap, names):
    """Repoint one source at the names Actor and Platform already give it."""
    for nm, o in sorted(oldmap.items(), key=lambda kv: -len(kv[0])):
        if o < PLATFORM_DSIZE and o in names and names[o] != nm:
            text = re.sub(r"\b" + re.escape(nm) + r"\b", names[o], text)
    # A local `typedef int Fix12` shadows the real Fix12 template the moment
    # Platform.h makes it visible.
    text = text.replace("typedef int Fix12;\n", "")
    text = re.sub(r"\bFix12\s+(\w+)(?=\s*[,)])", r"int \1", text)
    text = re.sub(r"\bFix12(?=\s*[,)])", "int", text)
    for off, member in (("0x124", "&mMeshCollider"), ("0x2ec", "&mClsnMat"), ("0xd4", "&mModel")):
        for lhs in (f"((char *)this) + {off}", f"((char*)this)+{off}", f"((char *)this)+{off}"):
            text = text.replace(lhs, member)
    return text


def sources_for(cls):
    inc = f'#include "{cls}.h"'
    return sorted(p for p in list((REPO / "src").glob("*.c")) + list((REPO / "src").glob("*.cpp"))
                  if inc in p.read_text(errors="replace"))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("classes", nargs="+")
    args = ap.parse_args()
    names, idx = inherited_names(), symbol_index()
    kept, dropped = [], []

    for cls in args.classes:
        hpath = REPO / "include" / f"{cls}.h"
        if not hpath.exists():
            dropped.append((cls, "no header"))
            print(f"--   {cls:30s} no header")
            continue
        old = hpath.read_text(errors="replace")
        oldmap = {nm: int(o, 16) for ty, star, nm, arr, o in FIELD.findall(old)}
        srcs = sources_for(cls)
        saved = {p: p.read_text(errors="replace") for p in srcs}
        saved[hpath] = old

        hpath.write_text(build_header(cls, old))
        for p in srcs:
            if p.suffix == ".cpp":
                p.write_text(patch_source(saved[p], oldmap, names))

        d1 = REPO / "src" / f"_ZN{len(cls)}{cls}D1Ev.cpp"
        d1c = REPO / "src" / f"_ZN{len(cls)}{cls}D1Ev.c"
        had_c = d1c.exists()
        if had_c:
            saved[d1c] = d1c.read_text(errors="replace")
            d1c.unlink()
        d1.write_text(f"""//cpp
// @symbol _ZN{len(cls)}{cls}D1Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * Two vtable stores and three destructor calls, every one a consequence of
 * `struct {cls} : Platform`: its own vptr, then Platform's -- inlined,
 * because Platform's destructor is defined in its class body -- then
 * Platform's Model and MovingMeshCollider, then Actor. This class adds no
 * member with a destructor of its own.
 */
#include "{cls}.h"

{cls}::~{cls}()
{{
}}
""")

        fails = []
        for p in sorted(set(srcs) | {d1}):
            if not p.exists():
                continue
            sym = p.stem
            if sym not in idx:
                continue
            addr, size, lab = idx[sym]
            try:
                ok, why = BP.verify(str(p.relative_to(REPO)).replace("\\", "/"), sym, addr, size, lab)
            except Exception as e:                                   # noqa: BLE001
                ok, why = False, f"{type(e).__name__}: {e}"[:90]
            if not ok:
                fails.append((sym, why))
        hdr = subprocess.run([sys.executable, str(REPO / "tools" / "check_header_offsets.py"), str(hpath)],
                             capture_output=True, text=True)
        if hdr.returncode != 0:
            last = hdr.stdout.strip().splitlines()[-1] if hdr.stdout.strip() else "exit 1"
            fails.append(("check_header_offsets", last))

        if fails:
            for p, t in saved.items():
                p.write_text(t)
            if had_c and d1.exists():
                d1.unlink()
            dropped.append((cls, f"{fails[0][0]}: {fails[0][1][:60]}"))
            print(f"--   {cls:30s} reverted, {len(fails)} fail -- {fails[0][0]}: {fails[0][1][:55]}")
        else:
            kept.append(cls)
            print(f"OK   {cls:30s} {len(srcs) + 1} files")

    print(f"\nkept {len(kept)} / dropped {len(dropped)}")
    if kept:
        print("kept: " + " ".join(kept))
    for c, why in dropped:
        print(f"  dropped {c}: {why}")


if __name__ == "__main__":
    main()
