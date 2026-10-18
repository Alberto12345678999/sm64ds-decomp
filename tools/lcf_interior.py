"""Define, at link time, ROM functions that live inside another source's body.

A hand-asm source can cover several ROM functions in one asm block.
`src/unnamed/arm9/01ff/func_01ff97d8.c` is the ITCM soft-float routine at
0x01ff97d8..0x01ffa344: symbols.txt splits it into five functions (97d8, 98f4,
99a4, 9d40 `_deq`, 9e2c), but branches cross every boundary into interior
labels, so it is one asm block. mwccarm cannot export a second name from an asm
block (no `entry`, `.global` or `sym+off`), so that object defines only
`func_01ff97d8`.

A delinked caller never notices: dsd leaves a `module:none` call as raw bytes
and imports nothing. A compiled caller does. `bl func_01ff99a4` carries a
relocation against that name, and the link aborts `Undefined`, because the
range is source-built and no gap object defines the rows inside it any more.

`patch` closes that gap with absolute definitions: for every function row
of a fixed-address module (arm9, itcm, dtcm) that lies strictly inside a
`complete` delinks range, that some object handed to the link imports and that
none defines, it adds `name = 0x<addr>;` to the linker command file. Those
modules never move, so the address in symbols.txt is the address the linked
code is at. Overlay code entry points are left alone.

BSS interior labels, including overlay labels, retain configured identities even
without live imports when one actual source provider proves the complete NOBITS
object. The older imported-label path remains available. The LCF
defines the canonical label inside its enclosing output module. This preserves aliases
without adding storage, changing object bytes, or assuming an overlay base.

Initialized-data labels at an object's start or inside it are retained even without
live imports, because dsd validates configured identities. Each alias needs one actual PROGBITS OBJECT
definition from its complete source provider, a unique configured module home,
and a matching .data/.rodata range covering the entire emitted object.

It also adds the NitroSDK linker constants in LINKER_CONSTANTS. The SDK's own
LCF template assigns them and its OS init code takes their *address* as the
value (`(s32)SDK_IRQ_STACKSIZE`); dsd's generated command file does not, so a
compiled reader (func_02058308, func_02058df4) links `Undefined`.
"""
import pathlib
import re
import struct


def initialized_interior_rows(config_root, objects_txt, definitions):
    """Initialized-object aliases, including another name at the object's start."""
    return _source_storage_interior_rows(config_root, objects_txt, definitions)


def source_bss_interior_rows(config_root, objects_txt, definitions):
    return _source_storage_interior_rows(config_root, objects_txt, definitions, bss=True)


def _source_storage_interior_rows(config_root, objects_txt, definitions, bss=False):
    """Configured labels inside complete, actual source-defined storage objects.

    Unlike an unresolved import, an unreferenced configured interior label still
    needs an ELF identity for symbol validation. Only matching OBJECT storage
    in the same section, module and source provider can justify that identity.
    This adds no storage and does not infer an object's extent from the next label.
    """
    import io
    from elftools.elf.elffile import ELFFile

    root = pathlib.Path(config_root)
    sections = (".bss",) if bss else (".data", ".rodata")
    storage_type = "SHT_NOBITS" if bss else "SHT_PROGBITS"
    homes, claims = {}, []
    symbol_row = re.compile(r"^(\S+)\s+kind:(\S+)\s+addr:0x([0-9a-fA-F]+)")
    section_row = re.compile(
        r"^\s+(" + "|".join(re.escape(s) for s in sections) +
        r")\s+start:0x([0-9a-fA-F]+)\s+end:0x([0-9a-fA-F]+)")
    for symbols in sorted(root.rglob("symbols.txt")):
        module = symbols.parent.relative_to(root).as_posix()
        for line in symbols.read_text(encoding="utf-8").splitlines():
            match = symbol_row.match(line)
            if match:
                name, kind, address = match.groups()
                size = re.search(r"\bsize=(0x[0-9a-fA-F]+|[0-9]+)", kind)
                valid_kind = (re.fullmatch(r"bss(?:\(size=(?:0x[0-9a-fA-F]+|[0-9]+)\))?", kind)
                              is not None) if bss else kind.startswith("data(")
                homes.setdefault(name, []).append((
                    module, int(address, 16), valid_kind,
                    int(size[1], 0) if size else (None if bss else 0)))
        delinks = symbols.with_name("delinks.txt")
        if not delinks.is_file():
            continue
        source, complete, ranges = None, False, []

        def flush():
            if source and source.startswith("src/") and complete:
                claims.extend((module, source, *row) for row in ranges)

        for line in delinks.read_text(encoding="utf-8").splitlines():
            if line and not line[0].isspace() and line.rstrip().endswith(":"):
                flush()
                source, complete, ranges = line.strip()[:-1], False, []
            elif line.strip() == "complete":
                complete = True
            else:
                match = section_row.match(line)
                if match:
                    ranges.append((match[1], int(match[2], 16), int(match[3], 16)))
        flush()

    objects, definition_counts = {}, {}
    for line in pathlib.Path(objects_txt).read_text(encoding="utf-8").splitlines():
        path = pathlib.Path(line.strip().strip('"'))
        if not line.strip():
            continue
        raw = path.read_bytes()
        if raw[:4] != b"\x7fELF":
            continue
        elf = ELFFile(io.BytesIO(raw))
        if (elf.elfclass != 32 or not elf.little_endian
                or elf["e_type"] != "ET_REL" or elf["e_machine"] != "EM_ARM"):
            continue
        tables = [section for section in elf.iter_sections()
                  if section["sh_type"] == "SHT_SYMTAB"]
        for symbol in (symbol for table in tables for symbol in table.iter_symbols()):
            index = symbol["st_shndx"]
            if (symbol.name and index != "SHN_UNDEF"
                    and symbol["st_info"]["bind"] != "STB_LOCAL"):
                definition_counts[symbol.name] = definition_counts.get(symbol.name, 0) + 1
            if (not symbol.name or not isinstance(index, int) or index <= 0
                    or index >= elf.num_sections()
                    or symbol["st_info"]["bind"] == "STB_LOCAL"
                    or symbol["st_info"]["type"] != "STT_OBJECT"):
                continue
            section = elf.get_section(index)
            size, value = symbol["st_size"], symbol["st_value"]
            if (section["sh_type"] != storage_type
                    or section.name not in sections
                    or not size or value + size > section["sh_size"]):
                continue
            objects.setdefault(symbol.name, []).append((path, section.name, size))

    owners = []
    for name, rows in objects.items():
        locations = homes.get(name, [])
        if (name not in definitions or len(rows) != 1 or len(locations) != 1
                or definition_counts.get(name) != 1):
            continue
        path, section, size = rows[0]
        module, address, is_data, declared_size = locations[0]
        if not is_data or (((bss and declared_size is not None) or declared_size)
                           and declared_size != size):
            continue
        matching = [(source, start, end) for mod, source, sec, start, end in claims
                    if mod == module and sec == section
                    and start <= address and address + size <= end
                    and path.resolve().as_posix().endswith("/" + str(
                        pathlib.PurePosixPath(source).with_suffix(".o")))]
        if len(matching) == 1:
            owners.append((name, module, address, size))
    out = []
    for name, locations in sorted(homes.items()):
        if name in definitions or len(locations) != 1:
            continue
        module, address, is_data, declared_size = locations[0]
        if not is_data:
            continue
        enclosing = [(owner, base) for owner, mod, base, size in owners
                     if mod == module and base <= address < base + size
                     and (not bss or base < address)
                     and address + (declared_size or 0) <= base + size]
        if len(enclosing) == 1:
            owner, base = enclosing[0]
            out.append((name, address, owner, address - base, module))
    return out

FIXED = ("arm9", "itcm", "dtcm")

# Value = what the ROM's literal pools hold where these are read: 0 at
# 0x02058458/0x02058e8c (no override, so the default system stack) and 0x600
# at 0x0205846c/0x02058e90.
LINKER_CONSTANTS = {
    "SDK_SYS_STACKSIZE": 0x0,
    "SDK_IRQ_STACKSIZE": 0x600,
}

_ROW = re.compile(
    r"^(\S+)\s+kind:(?:function|label)\([^)]*\).*?addr:0x([0-9a-fA-F]+)")
_TEXT = re.compile(r"^\s+\.text\s+start:0x([0-9a-fA-F]+)\s+end:0x([0-9a-fA-F]+)")


def _module_dir(config_root, module):
    return config_root if module == "arm9" else config_root / module


def _complete_ranges(delinks_path, pattern):
    """Ranges selected from complete source entries, excluding module headers."""
    out, body, complete = [], [], False

    def flush():
        if complete:
            for ln in body:
                m = pattern.match(ln)
                if m:
                    out.append((int(m.group(1), 16), int(m.group(2), 16)))

    for ln in delinks_path.read_text(errors="ignore").splitlines():
        if ln and not ln[0].isspace() and ln.rstrip().endswith(":"):
            flush()
            body, complete = [], False
        elif ln.strip() == "complete":
            complete = True
        else:
            body.append(ln)
    flush()
    return out


def complete_text_ranges(delinks_path):
    """[(start, end)] of the .text section of every `complete` source entry."""
    return _complete_ranges(delinks_path, _TEXT)


def _elf_bss_definitions(data):
    """Global object extents in NOBITS sections; values stay section-relative."""
    if data[:6] != b"\x7fELF\x01\x01":
        return {}
    shoff, = struct.unpack_from("<I", data, 0x20)
    shentsize, shnum = struct.unpack_from("<HH", data, 0x2e)
    secs = [struct.unpack_from("<IIIIIIIIII", data, shoff + i * shentsize)
            for i in range(shnum)]
    out = {}
    for sec in secs:
        if sec[1] != 2:
            continue
        strings = secs[sec[6]]
        for off in range(sec[4], sec[4] + sec[5], 16):
            name, value, size, info, _other, shndx = struct.unpack_from(
                "<IIIBBH", data, off)
            if not name or not (info >> 4) or (info & 15) != 1 \
                    or not 0 < shndx < len(secs) or secs[shndx][1] != 8 \
                    or not size or value + size > secs[shndx][5]:
                continue
            start = strings[4] + name
            symbol = data[start:data.index(b"\0", start)].decode("latin-1")
            out.setdefault(symbol, []).append(size)
    return out


def bss_interior_rows(config_root, definitions, imported, bss_definitions):
    """Missing, uniquely homed labels inside actual source-defined BSS objects.

    Return (label, address, enclosing symbol, offset, module). The extent check
    ties each label to real source storage before an LCF definition is allowed.
    Both names must have exactly one configured home in the same module, the
    enclosing symbol must have one NOBITS definition, and its entire extent must
    lie in a complete BSS range. Ambiguity leaves the ordinary link checks red.
    """
    root = pathlib.Path(config_root)
    pattern = re.compile(r"^\s+\.bss\s+start:0x([0-9a-fA-F]+)\s+end:0x([0-9a-fA-F]+)")
    row_pattern = re.compile(r"^(\S+)\s+kind:bss\s+addr:0x([0-9a-fA-F]+)(?:\s|$)")
    homes, ranges = {}, {}
    for syms in sorted(root.rglob("symbols.txt")):
        dl = syms.with_name("delinks.txt")
        module = syms.parent.relative_to(root).as_posix()
        ranges[module] = _complete_ranges(dl, pattern) if dl.is_file() else []
        for line in syms.read_text(errors="ignore").splitlines():
            # Count every kind's home: a same-named function/data in another
            # overlay is just as ambiguous as a second BSS row.
            match = re.match(r"^(\S+)\s+kind:.*?addr:0x([0-9a-fA-F]+)", line)
            if match:
                bss = row_pattern.match(line) is not None
                homes.setdefault(match[1], []).append((module, int(match[2], 16), bss))
    owners = []
    for name, sizes in bss_definitions.items():
        locations = homes.get(name, [])
        if name not in definitions or len(sizes) != 1 or len(locations) != 1:
            continue
        module, address, is_bss = locations[0]
        if is_bss and any(lo <= address and address + sizes[0] <= hi
                          for lo, hi in ranges[module]):
            owners.append((name, module, address, sizes[0]))
    out = []
    for name in sorted(imported - definitions):
        locations = homes.get(name, [])
        if len(locations) != 1:
            continue
        module, address, is_bss = locations[0]
        if not is_bss:
            continue
        enclosing = [(owner, base) for owner, mod, base, size in owners
                     if mod == module and base < address < base + size]
        if len(enclosing) == 1:
            owner, base = enclosing[0]
            out.append((name, address, owner, address - base, module))
    return out


def interior_rows(config_root):
    """[(name, addr)] for function and label rows strictly inside a complete range.

    Zero-size rows count: `_deq` is a size-0 alias row at 0x01ff9d40, the same
    address as func_01ff9d40, and a compiled caller of a `double ==` imports it
    by that name (func_0206f46c, func_020708b4). Skipping it left those links
    `Undefined : "_deq"`. Label rows count too: a secondary entry point inside
    a hand-asm function (_ZN3IRQ11SetIRQStateEb, 0x10 into func_0206da18) is a
    label, not a function, but callers import it by name all the same. A row at
    a range's own start is still skipped (strict `<`): that address is the
    source's own symbol, defined by its object."""
    config_root = pathlib.Path(config_root)
    rows = []
    for module in FIXED:
        d = _module_dir(config_root, module)
        syms, dl = d / "symbols.txt", d / "delinks.txt"
        if not (syms.is_file() and dl.is_file()):
            continue
        ranges = complete_text_ranges(dl)
        for ln in syms.read_text(errors="ignore").splitlines():
            m = _ROW.match(ln)
            if not m:
                continue
            addr = int(m.group(2), 16)
            if any(lo < addr < hi for lo, hi in ranges):
                rows.append((m.group(1), addr))
    return rows


def _link_inventory(objects_txt):
    """(defined, imported, BSS extents): the non-local names the link's objects define, and the
    names they reference undefined."""
    defined, imported, bss = set(), set(), {}
    for line in pathlib.Path(objects_txt).read_text(errors="ignore").splitlines():
        path = line.strip().strip('"')
        if not path:
            continue
        try:
            data = pathlib.Path(path).read_bytes()
        except OSError:
            continue
        d, i = _elf_names(data)
        defined |= d
        imported |= i
        for name, sizes in _elf_bss_definitions(data).items():
            bss.setdefault(name, []).extend(sizes)
    return defined, imported, bss


def link_names(objects_txt):
    """(defined, imported) non-local symbols from the actual link inputs."""
    defined, imported, _bss = _link_inventory(objects_txt)
    return defined, imported


def _elf_names(data):
    """(defined, imported) names of one ELF object. Any binding but STB_LOCAL is a
    definition: mwcc marks vague-linkage ("multidef") definitions STB_LOPROC."""
    if data[:4] != b"\x7fELF" or data[4] != 1:
        return set(), set()
    shoff, = struct.unpack_from("<I", data, 0x20)
    shentsize, shnum = struct.unpack_from("<HH", data, 0x2e)
    secs = [struct.unpack_from("<IIIIIIIIII", data, shoff + i * shentsize)
            for i in range(shnum)]
    defined, imported = set(), set()
    for sec in secs:
        if sec[1] != 2:                     # SHT_SYMTAB
            continue
        strtab = secs[sec[6]]
        for off in range(sec[4], sec[4] + sec[5], 16):
            name, _value, _size, info, _other, shndx = struct.unpack_from(
                "<IIIBBH", data, off)
            if not name or (info >> 4) == 0:              # unnamed, or local
                continue
            start = strtab[4] + name
            sym = data[start:data.index(b"\0", start)].decode("latin-1")
            (imported if shndx == 0 else defined).add(sym)
    return defined, imported


def patch(lcf_path, objects_txt, config_root):
    """Add the missing interior definitions and linker constants to `lcf_path`;
    return [(name, addr)].

    Code labels require an import. Source-proven storage interior labels also
    preserve configured identities checked by dsd, even without an import."""
    defined, imported, bss = _link_inventory(objects_txt)
    aliases = bss_interior_rows(config_root, defined, imported, bss)
    aliases += initialized_interior_rows(config_root, objects_txt, defined)
    aliases += source_bss_interior_rows(config_root, objects_txt, defined)
    aliases = sorted(set(aliases))
    rows = interior_rows(config_root) + list(LINKER_CONSTANTS.items())
    missing = sorted({(n, a) for n, a in rows
                      if n in imported and n not in defined}, key=lambda r: r[1])
    if not missing and not aliases:
        return []
    lcf_path = pathlib.Path(lcf_path)
    text = lcf_path.read_bytes().decode("latin-1")    # keep CRLF visible
    nl = "\r\n" if "\r\n" in text else "\n"
    if missing:
        anchor = "SECTIONS {"
        at = text.index(anchor) + len(anchor)
        block = "".join(f"{nl}    {n} = 0x{a:08x};" for n, a in missing)
        text = text[:at] + block + text[at:]
    for name, address, _owner, _offset, module in aliases:
        section = pathlib.PurePosixPath(module).name if module != "." else "arm9"
        pattern = re.compile(r"^([ \t]*\." + re.escape(section) +
                             r"[ \t]*:[ \t]*\{)", re.MULTILINE)
        matches = list(pattern.finditer(text))
        if len(matches) != 1:
            raise ValueError(f"storage alias {name} requires exactly one .{section} "
                             "output section")
        at = matches[0].end()
        # mwldarm evaluates `object + offset` here before relocating the
        # object and would retain only the offset. A canonical value INSIDE
        # the output module preserves both the address and ELF section identity.
        text = text[:at] + f"{nl}        {name} = 0x{address:08x};" + text[at:]
        missing.append((name, address))
    lcf_path.write_bytes(text.encode("latin-1"))
    return sorted(missing, key=lambda row: row[1])
