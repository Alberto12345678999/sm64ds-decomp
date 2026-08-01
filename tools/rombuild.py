"""Build a playable .nds from source.

Runs the whole ds-decomp link pipeline: every `src/` file enrolled in a
`config/**/delinks.txt` file entry is compiled with mwccarm and linked by mwldarm
into the module it belongs to; every address range NOT enrolled is supplied by a
delinked gap object carrying the original ROM bytes. The result is packaged back
into a bootable ROM.

    dsd delink   -> build/delinks/*.o      (gap objects, ROM bytes)
    mwccarm      -> build/src/*.o          (our C, one function per file)
    dsd lcf      -> build/arm9.lcf + build/objects.txt
    mwldarm      -> build/final_link.o     + build/build/*.bin per region
    dsd rom config / rom build             -> build/sm64ds.nds
    dsd check modules                      -> byte-diff every module vs the ROM

A module is "green" when its linked bytes equal the retail module, so a green build
with N functions enrolled is proof those N functions' source is the real thing.

Usage:
    python tools/rombuild.py                 # full build + verify
    python tools/rombuild.py --no-rom        # link and verify, skip .nds packaging
    python tools/rombuild.py --no-check      # skip the module byte-diff
    python tools/rombuild.py -j 16           # parallel compiles

See notes/rom-build.md for the milestones and the enrollment rules.
"""
import argparse
import concurrent.futures
import os
import pathlib
import shutil
import subprocess
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
DSD = REPO / "tools" / "bin" / "dsd.exe"
MW = REPO / "tools" / "mwccarm"
LICENSE = MW / "license.dat"
INCLUDE = REPO / "include"
CONFIG = REPO / "config" / "arm9" / "config.yaml"
BUILD = REPO / "build"

# The pinned toolchain, same as tools/match.py: what verified the bytes must build them.
VERSION = "1.2/sp2p3"
CFLAGS = ("-O4,p -enum int -lang c99 -char signed -interworking "
          "-proc arm946e -gccext,on -msgstyle gcc")
LDFLAGS = ("-proc arm946e -nostdlib -interworking -m Entry "
           "-map closure,unused -msgstyle gcc -nodead")


def launcher():
    """Wine prefix on the Linux build box; empty on native Windows (see match.py)."""
    return os.environ.get("MWCCARM_LAUNCHER", "").split()


def run(cmd, what, quiet_patterns=()):
    r = subprocess.run(cmd, capture_output=True, text=True,
                       env=dict(os.environ, LM_LICENSE_FILE=str(LICENSE)), cwd=REPO)
    out = "\n".join(l for l in (r.stdout + r.stderr).splitlines()
                    if not any(p in l for p in quiet_patterns))
    if r.returncode != 0:
        print(f"!! {what} failed (exit {r.returncode})")
        print(out[:4000])
        sys.exit(1)
    return out


def enrolled():
    """Every `src/` file carved out by a `complete` file entry in a delinks.txt.

    A file entry is an unindented path ending in ':'; the indented lines that follow
    hold `complete` and its section ranges. Without `complete`, dsd supplies the range
    from ROM bytes instead, so the file is configured but not yet source-built.
    """
    files, path, saw_complete = [], None, False
    for delinks in sorted((REPO / "config").rglob("delinks.txt")):
        for line in delinks.read_text(encoding="utf-8").splitlines():
            if not line.strip():
                continue
            if not line[0].isspace():
                if path and saw_complete:
                    files.append(path)
                path = line.strip().rstrip(":") if line.rstrip().endswith(":") else None
                saw_complete = False
            elif line.strip() == "complete":
                saw_complete = True
        if path and saw_complete:
            files.append(path)
        path, saw_complete = None, False
    return sorted(set(files))


def compile_one(rel):
    """Compile one enrolled source file to the object path dsd's objects.txt names."""
    src = REPO / rel
    obj = BUILD / pathlib.Path(rel).with_suffix(".o")
    obj.parent.mkdir(parents=True, exist_ok=True)
    flags = CFLAGS
    # A leading //cpp marker means C++, matched to how match.py/fdiff compile it.
    try:
        if src.read_text(encoding="utf-8").startswith("//cpp"):
            flags = flags.replace("-lang c99", "-lang c++")
    except OSError:
        pass
    cmd = [*launcher(), str(MW / VERSION / "mwccarm.exe"), *flags.split(),
           "-i", str(INCLUDE), "-c", str(src), "-o", str(obj)]
    r = subprocess.run(cmd, capture_output=True, text=True,
                       env=dict(os.environ, LM_LICENSE_FILE=str(LICENSE)), cwd=REPO)
    if r.returncode != 0 or not obj.is_file():
        detail = "\n".join(s for s in (r.stdout.strip(), r.stderr.strip()) if s)
        return rel, detail[:400]
    return rel, None


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("-j", "--jobs", type=int, default=os.cpu_count() or 8)
    ap.add_argument("--rom-out", default=str(BUILD / "sm64ds.nds"))
    ap.add_argument("--no-rom", action="store_true", help="stop after linking")
    ap.add_argument("--no-check", action="store_true", help="skip dsd check modules")
    ap.add_argument("--arm7-bios", help="passed to dsd rom build if your dump needs it")
    args = ap.parse_args()

    for tool in (DSD, MW / VERSION / "mwccarm.exe", MW / VERSION / "mwldarm.exe"):
        if not tool.is_file():
            sys.exit(f"missing {tool} - see notes/setup-mwccarm.md")
    if not (REPO / "extracted" / "dsd" / "config.yaml").is_file():
        sys.exit("no extracted ROM - run tools/unpack.py on your own dump first")

    # Gap objects first: delinks.txt drives which ranges dsd carves out for us.
    print("[1/6] dsd delink")
    run([str(DSD), "delink", "-c", str(CONFIG)], "dsd delink",
        quiet_patterns=("No module for relocation",))

    print("[2/6] dsd lcf")
    run([str(DSD), "lcf", "-c", str(CONFIG)], "dsd lcf")

    srcs = enrolled()
    print(f"[3/6] mwccarm: {len(srcs)} enrolled source file(s), -j{args.jobs}")
    failures = []
    if srcs:
        with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as ex:
            for rel, err in ex.map(compile_one, srcs):
                if err:
                    failures.append((rel, err))
    if failures:
        print(f"!! {len(failures)} file(s) failed to compile:")
        for rel, err in failures[:10]:
            print(f"   {rel}: {err.splitlines()[0] if err else ''}")
        sys.exit(1)

    print("[4/6] mwldarm")
    run([*launcher(), str(MW / VERSION / "mwldarm.exe"), *LDFLAGS.split(),
         f"@{BUILD / 'objects.txt'}", str(BUILD / "arm9.lcf"),
         "-o", str(BUILD / "final_link.o")], "mwldarm")

    if args.no_rom:
        print("[5/6] skipped (--no-rom)")
    else:
        print("[5/6] dsd rom config + rom build")
        run([str(DSD), "rom", "config", "--elf", str(BUILD / "final_link.o"),
             "--config", str(CONFIG)], "dsd rom config")
        cmd = [str(DSD), "rom", "build", "--config", str(BUILD / "build" / "rom_config.yaml"),
               "--rom", args.rom_out]
        if args.arm7_bios:
            cmd += ["--arm7-bios", args.arm7_bios]
        run(cmd, "dsd rom build", quiet_patterns=("Compressing arm9 overlay",))
        print(f"      -> {args.rom_out}")

    if args.no_check:
        print("[6/6] skipped (--no-check)")
        return
    print("[6/6] dsd check modules")
    out = run([str(DSD), "check", "modules", "-c", str(CONFIG), "--fail"],
              "dsd check modules", quiet_patterns=(": OK",))
    if out.strip():
        print(out)
    print(f"\nAll modules match the ROM. {len(srcs)} function(s) built from src/.")


if __name__ == "__main__":
    main()
