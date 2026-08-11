#!/usr/bin/env python3
"""Question-oriented runtime probe for readable-C++ reconstruction.

The matching/decompiler workflow answers *what instructions exist*.  This tool
uses a running melonDS/DeSmuME GDB stub to answer the complementary runtime
questions that come up while turning those instructions into honest C++:

* Is r0 really a ``this`` pointer, and which concrete objects/vtables arrive?
* Which named header fields change across the call?
* What values/ranges do candidate fields take in real gameplay?
* Which callers and virtual slots are actually observed?

It resolves both near-miss records and already-matched config symbols, discovers
the class and named fields from ``include/<Class>.h``, captures ``this`` before
and after the call, then prints and saves a compact evidence report.  Runtime
evidence constrains a type/layout hypothesis; it does not replace byte matching
or prove byte-unobservable properties such as signedness at an inert access.

Examples (melonDS running with its ARM9 GDB stub on port 3333):

  python tools/trace/cpp_probe.py _ZN5Fader13AdvanceInterpEv --hits 8 \
      --ask "which Fader fields change while the fade advances?"

  python tools/trace/cpp_probe.py _ZN5Actor8BehaviorEv --class-name Actor \
      --field 0x5c:Vector3:position --vtable-slots 18

  python tools/trace/cpp_probe.py _ZN5Fader13AdvanceInterpEv --resolve-only
  python tools/trace/cpp_probe.py --input traces/questions/Fader_AdvanceInterp.json
"""
import argparse
from collections import Counter
import datetime as dt
import json
import pathlib
import re
import sys
import time

TRACE_DIR = pathlib.Path(__file__).resolve().parent
TOOLS_DIR = TRACE_DIR.parent
REPO = TOOLS_DIR.parent
sys.path.insert(0, str(TRACE_DIR))
sys.path.insert(0, str(TOOLS_DIR))

import bplist  # noqa: E402
import demangle  # noqa: E402
import fieldmap  # noqa: E402
from rsp import RspClient, RspError  # noqa: E402
import static_symbols  # noqa: E402
import symindex  # noqa: E402


ITCM_LO = 0x01FF8000
RAM_LO, RAM_HI = 0x02000000, 0x02400000
SCHEMA = "sm64ds-cpp-runtime-question-v1"

# Runtime decoders, not ABI assertions.  Unknown field types stay out of the
# automatic report until the contributor supplies --field with an explicit
# decoder; silently assuming a width would defeat this tool's purpose.
_SCALARS = {
    "u8": (1, False), "unsigned char": (1, False),
    "s8": (1, True), "signed char": (1, True), "char": (1, True),
    "bool": (1, False),
    "u16": (2, False), "unsigned short": (2, False),
    "s16": (2, True), "short": (2, True), "Angle": (2, True),
    "u32": (4, False), "unsigned": (4, False), "unsigned int": (4, False),
    "s32": (4, True), "int": (4, True), "long": (4, True),
}
_FIX12 = {"Fix12i", "Fix12<int>", "Fix12<s32>"}
_VECTORS = {"Vector3": (12, "vec3_fix12"), "Vector3_16": (6, "vec3_s16")}


def parse_int(text):
    return int(str(text), 0)


def _norm_type(typ):
    typ = re.sub(r"\b(const|volatile|struct|class)\b", "", typ)
    return re.sub(r"\s+", " ", typ).strip()


def decoder_for(typ):
    """Return ``(kind, size)`` for a field type, or ``None`` if unknown."""
    typ = _norm_type(typ)
    if typ in _FIX12:
        return "fix12", 4
    if typ in _VECTORS:
        size, kind = _VECTORS[typ]
        return kind, size
    if typ.endswith("*"):
        return "pointer", 4
    if typ in _SCALARS:
        size, signed = _SCALARS[typ]
        return ("signed" if signed else "unsigned"), size
    return None


def parse_field_spec(text):
    """Parse ``OFFSET:TYPE[:NAME]`` (commas are accepted too)."""
    sep = "," if "," in text else ":"
    parts = [p.strip() for p in text.split(sep, 2)]
    if len(parts) < 2:
        raise argparse.ArgumentTypeError("field must be OFFSET:TYPE[:NAME]")
    try:
        offset = parse_int(parts[0])
    except ValueError as exc:
        raise argparse.ArgumentTypeError(f"invalid field offset: {parts[0]}") from exc
    if offset < 0:
        raise argparse.ArgumentTypeError("field offset must be non-negative")
    typ = parts[1]
    decoder = decoder_for(typ)
    if decoder is None:
        known = "u8/s8/u16/s16/u32/s32/Fix12i/Vector3/Vector3_16/pointer"
        raise argparse.ArgumentTypeError(f"no decoder for {typ!r}; use one of {known}")
    kind, size = decoder
    return {
        "offset": offset,
        "type": typ,
        "name": parts[2] if len(parts) == 3 and parts[2] else f"field_{offset:03x}",
        "kind": kind,
        "size": size,
        "source": "cli",
    }


def _header_class(symbol, class_name, repo=REPO):
    if class_name:
        return class_name
    info = demangle.demangle(symbol)
    if not info or not info.get("class"):
        return None
    cls = info["class"]
    if (pathlib.Path(repo) / "include" / f"{cls}.h").is_file():
        return cls
    flattened = cls.replace("::", "__")
    if (pathlib.Path(repo) / "include" / f"{flattened}.h").is_file():
        return flattened
    return cls


def _receiver_classification(symbol, repo=REPO):
    """Classify r0 from the source; mangling alone cannot identify statics."""
    if demangle.demangle(symbol) is None:
        return "not-applicable", "symbol is not a C++ mangled name"
    src = pathlib.Path(repo) / "src"
    direct = [src / f"{symbol}.c", src / f"{symbol}.cpp"]
    path = next((p for p in direct if p.is_file()), None)
    if path is None and src.is_dir():
        path = next((p for p in src.rglob(f"{symbol}.*")
                     if p.suffix in (".c", ".cpp") and p.stem == symbol), None)
    if path is None:
        return "undecided", "source definition not found"
    try:
        kind, detail = static_symbols.classify(
            symbol, path.read_text(encoding="utf-8", errors="replace"))
    except (AttributeError, TypeError, ValueError) as exc:
        return "undecided", f"receiver classifier failed: {exc}"
    if kind.startswith("undecided"):
        return "undecided", kind
    return kind, detail


def discover_layout(symbol, class_name=None, extra_fields=None, repo=REPO,
                    object_size=None, max_auto_bytes=0x400, this_reg="auto"):
    """Build the capture layout from the mangled class and reconstructed header."""
    repo = pathlib.Path(repo)
    cls = _header_class(symbol, class_name, repo)
    header = repo / "include" / f"{cls}.h" if cls else None
    header_exists = bool(header and header.is_file())
    fields, chain = fieldmap.fields_for(cls, repo=repo) if header_exists else ({}, [])

    by_offset = {}
    skipped = []
    for offset, (name, typ) in sorted(fields.items()):
        decoder = decoder_for(typ)
        if decoder is None:
            skipped.append({"offset": offset, "name": name, "type": typ})
            continue
        kind, size = decoder
        by_offset[offset] = {
            "offset": offset, "name": name, "type": typ,
            "kind": kind, "size": size, "source": "header",
        }
    for spec in extra_fields or []:
        by_offset[spec["offset"]] = dict(spec)

    header_text = (header.read_text(encoding="utf-8", errors="replace")
                   if header_exists else "")
    header_code = re.sub(r"/\*.*?\*/|//[^\n]*", "", header_text, flags=re.S)
    zero = by_offset.get(0, {})
    has_vtable = (bool(re.search(r"\bvirtual\b", header_code)) or
                  zero.get("name", "").lower() in ("vtable", "vptr"))

    receiver_kind, receiver_detail = _receiver_classification(symbol, repo)
    resolved_this = this_reg
    if this_reg == "auto":
        # Itanium mangling does not distinguish instance from static/namespace
        # functions.  Only source arity/method form establishes the implicit
        # object.  UNDECIDED IS NOT INSTANCE; require --this-reg in that case.
        resolved_this = "r0" if receiver_kind == "instance" else None
    elif this_reg == "none":
        resolved_this = None

    required = max((f["offset"] + f["size"] for f in by_offset.values()), default=0)
    if object_size is None:
        auto_size = max(0x10, (required + 3) & ~3)
        capture_size = min(auto_size, max_auto_bytes)
    else:
        capture_size = object_size
    omitted = [f for f in by_offset.values()
               if f["offset"] + f["size"] > capture_size]
    visible = [f for f in by_offset.values()
               if f["offset"] + f["size"] <= capture_size]

    return {
        "class": cls,
        "header": str(header.relative_to(repo)) if header_exists else None,
        "header_chain": chain,
        "receiver_classification": receiver_kind,
        "receiver_evidence": receiver_detail,
        "has_vtable": has_vtable,
        "this_reg": resolved_this,
        "object_size": capture_size if resolved_this else 0,
        "fields": sorted(visible, key=lambda f: f["offset"]),
        "unknown_type_fields": skipped,
        "omitted_fields": omitted,
    }


def _signed(raw, bits):
    top = 1 << (bits - 1)
    return raw - (1 << bits) if raw & top else raw


def decode_value(blob_hex, field):
    """Decode one field from an object hex dump into JSON-friendly evidence."""
    if not blob_hex:
        return None
    blob = bytes.fromhex(blob_hex)
    off, size = field["offset"], field["size"]
    if off < 0 or off + size > len(blob):
        return None
    raw = blob[off:off + size]
    kind = field["kind"]
    if kind in ("signed", "unsigned", "fix12", "pointer"):
        value = int.from_bytes(raw, "little")
        if kind in ("signed", "fix12"):
            value = _signed(value, size * 8)
        if kind == "fix12":
            display = f"{value / 4096:g} (raw {value:#x})"
        elif kind == "pointer":
            display = f"0x{value:08x}"
        elif kind == "unsigned":
            display = f"{value} ({value:#x})"
        else:
            display = f"{value}"
        return {"value": value, "display": display, "hex": raw.hex()}
    if kind == "vec3_fix12":
        vals = [_signed(int.from_bytes(raw[i:i + 4], "little"), 32)
                for i in (0, 4, 8)]
        return {"value": vals,
                "display": "(" + ", ".join(f"{v / 4096:g}" for v in vals) + ")",
                "hex": raw.hex()}
    if kind == "vec3_s16":
        vals = [_signed(int.from_bytes(raw[i:i + 2], "little"), 16)
                for i in (0, 2, 4)]
        return {"value": vals, "display": str(tuple(vals)), "hex": raw.hex()}
    return {"value": raw.hex(), "display": raw.hex(), "hex": raw.hex()}


def _in_ram(value):
    return RAM_LO <= value < RAM_HI


def _in_code(value):
    return ITCM_LO <= value < RAM_HI


def _read(cli, addr, size):
    try:
        return cli.read_mem(addr, size)
    except (RspError, OSError, ValueError):
        return None


def _resolve_at(syms, addr):
    """Resolve an actual code pointer, without treating it as a return PC."""
    pc = addr & ~1
    return sorted({name for lo, hi, name in syms.ranges if lo <= pc < hi})


def _resolve_caller(syms, lr):
    """Resolve the call instruction immediately before an ARM/Thumb LR."""
    return_addr = lr & ~1
    callsite = return_addr - (2 if lr & 1 else 4)
    return _resolve_at(syms, callsite)


def _resolve_exact(syms, addr):
    resolver = getattr(syms, "resolve_exact", None)
    return resolver(addr) if resolver else []


def _vtable_label(vtable):
    addr = vtable.get("addr")
    address = f"0x{addr:08x}" if addr is not None else "unknown"
    names = " | ".join(vtable.get("symbols") or [])
    return f"{names} @ {address}" if names else address


def _snapshot_object(cli, regs, layout, syms, vtable_slots):
    reg = layout.get("this_reg")
    if not reg:
        return {"addr": None, "hex": None, "vtable": None}
    addr = regs[reg]
    if not _in_ram(addr):
        return {"addr": addr, "hex": None, "vtable": None,
                "error": f"{reg} is not a main-RAM pointer"}
    raw = _read(cli, addr, layout["object_size"])
    out = {"addr": addr, "hex": raw.hex() if raw else None, "vtable": None}
    if not raw or len(raw) < 4 or vtable_slots <= 0 or not layout.get("has_vtable"):
        return out
    vt = int.from_bytes(raw[:4], "little")
    vt_symbols = _resolve_exact(syms, vt)
    if not _in_ram(vt):
        out["vtable"] = {"addr": vt, "symbols": vt_symbols,
                         "slots": [], "plausible": False}
        return out
    table = _read(cli, vt, vtable_slots * 4)
    slots = []
    if table:
        for i in range(0, len(table) - 3, 4):
            target = int.from_bytes(table[i:i + 4], "little")
            slots.append({
                "slot": i // 4,
                "addr": target,
                "symbols": _resolve_at(syms, target) if _in_code(target) else [],
            })
    out["vtable"] = {"addr": vt, "symbols": vt_symbols,
                     "slots": slots, "plausible": True}
    return out


def capture_case(cli, target, regs, layout, syms, vtable_slots=12,
                 capture_return=True):
    """Capture one entry and, when requested, its return via the LR breakpoint.

    Returns ``(case, running)``.  ``running`` tells the outer loop whether this
    function timed out after continuing, so it must not send a duplicate ``c``.
    """
    case = {
        "entry": {
            "regs": {k: regs[k] for k in ("r0", "r1", "r2", "r3", "sp", "lr", "pc")},
            "caller_addr": regs["lr"],
            "caller_symbols": _resolve_caller(syms, regs["lr"]),
            "object": _snapshot_object(cli, regs, layout, syms, vtable_slots),
        },
        "status": "entry-only" if not capture_return else "waiting-return",
    }
    observations = []
    for spec in layout.get("memory_reads", []):
        raw = _read(cli, spec["addr"], spec.get("size", 8))
        seen = raw.hex().lower() if raw is not None else None
        matches = [
            candidate["qualified_name"]
            for candidate in spec.get("candidates", [])
            if seen is not None and seen.startswith(candidate["canary"].lower())
        ]
        observations.append({
            "name": spec["name"],
            "addr": spec["addr"],
            "bytes": seen,
            "matches": matches,
        })
    if observations:
        case["observations"] = observations
    if not capture_return:
        return case, False

    lr = regs["lr"]
    return_addr = lr & ~1
    return_kind = 2 if lr & 1 else 4
    if not _in_code(return_addr) or not cli.set_breakpoint(return_addr, return_kind):
        case["status"] = "return-breakpoint-failed"
        return case, False

    running = False
    try:
        cli.cont()
        running = True
        try:
            cli.wait_for_stop()
        except (RspError, OSError, TimeoutError):
            case["status"] = "return-timeout"
            return case, True
        running = False
        out_regs = cli.read_registers()
        if out_regs["pc"] in (lr, return_addr):
            case["exit"] = {
                "regs": {k: out_regs[k] for k in ("r0", "r1", "sp", "lr", "pc")},
                "object": _snapshot_object(cli, regs, layout, syms, 0),
            }
            case["status"] = "returned"
        elif out_regs["pc"] == target["addr"]:
            case["status"] = "recursive-entry"
        else:
            case["status"] = f"unexpected-stop-{out_regs['pc']:#x}"
        return case, False
    finally:
        try:
            cli.clear_breakpoint(return_addr, return_kind)
        except (RspError, OSError):
            pass


def collect(target, layout, host="127.0.0.1", port=3333, hits=5,
            duration=90.0, idle=20.0, poll_timeout=2.0, vtable_slots=12,
            capture_return=True, client_factory=RspClient, on_ready=None,
            should_abort=None):
    syms = symindex.get()
    cli = client_factory(host, port, timeout=poll_timeout)
    cases = []
    alias_rejects = 0
    started = time.time()
    last_hit = started
    try:
        cli.connect()
        bp_kind = target.get("breakpoint_kind", 4)
        if not cli.set_breakpoint(target["addr"], bp_kind):
            raise RspError(f"stub refused breakpoint at {target['addr']:#x}")
        cli.cont()
        if on_ready is not None:
            on_ready(cli)
        while len(cases) < hits and time.time() - started < duration:
            if should_abort is not None and should_abort():
                raise RuntimeError("runtime probe aborted by scenario input failure")
            if time.time() - last_hit >= idle:
                break
            try:
                cli.wait_for_stop()
            except (RspError, OSError, TimeoutError):
                if should_abort is not None and should_abort():
                    raise RuntimeError("runtime probe aborted by scenario input failure")
                continue
            regs = cli.read_registers()
            if regs["pc"] != target["addr"]:
                cli.cont()
                continue
            expected = target["canary"]
            seen = _read(cli, target["addr"], len(expected) // 2)
            if seen is None or seen.hex().lower() != expected.lower():
                alias_rejects += 1
                cli.cont()
                continue
            case, running = capture_case(
                cli, target, regs, layout, syms, vtable_slots, capture_return)
            cases.append(case)
            last_hit = time.time()
            if not running:
                cli.cont()
    finally:
        try:
            cli.clear_breakpoint(target["addr"], target.get("breakpoint_kind", 4))
        except (RspError, OSError):
            pass
        try:
            cli.detach()
        finally:
            cli.close()
    return cases, alias_rejects, time.time() - started


def _unique_displays(values):
    out = []
    seen = set()
    for value in values:
        if value is None:
            continue
        display = value["display"]
        if display not in seen:
            seen.add(display)
            out.append(display)
    return out


def _changed_ranges(cases, object_size):
    counts = Counter()
    comparable = 0
    for case in cases:
        before = case.get("entry", {}).get("object", {}).get("hex")
        after = case.get("exit", {}).get("object", {}).get("hex")
        if not before or not after:
            continue
        a, b = bytes.fromhex(before), bytes.fromhex(after)
        comparable += 1
        for i, (x, y) in enumerate(zip(a[:object_size], b[:object_size])):
            if x != y:
                counts[i] += 1
    ranges = []
    offsets = sorted(counts)
    i = 0
    while i < len(offsets):
        start = end = offsets[i]
        count = counts[start]
        i += 1
        while i < len(offsets) and offsets[i] == end + 1 and counts[offsets[i]] == count:
            end = offsets[i]
            i += 1
        ranges.append({"start": start, "end": end, "cases": count})
    return ranges, comparable


def summarize(evidence):
    cases = evidence.get("cases", [])
    layout = evidence["layout"]
    summary = {
        "entry_hits": len(cases),
        "completed_returns": sum(c.get("status") == "returned" for c in cases),
        "statuses": dict(Counter(c.get("status", "unknown") for c in cases)),
    }

    callers = Counter()
    objects = Counter()
    vtables = Counter()
    for case in cases:
        entry = case.get("entry", {})
        names = entry.get("caller_symbols") or [f"0x{entry.get('caller_addr', 0):08x}"]
        callers[" | ".join(names)] += 1
        obj = entry.get("object", {})
        if obj.get("addr") is not None:
            objects[f"0x{obj['addr']:08x}"] += 1
        vt = obj.get("vtable") or {}
        if vt.get("addr") is not None:
            vtables[_vtable_label(vt)] += 1
    summary["callers"] = dict(callers)
    summary["objects"] = dict(objects)
    summary["vtables"] = dict(vtables)

    entry_registers = Counter()
    for case in cases:
        regs = case.get("entry", {}).get("regs")
        if regs:
            entry_registers[" ".join(
                f"{reg}=0x{regs[reg]:08x}" for reg in ("r0", "r1", "r2", "r3"))] += 1
    summary["entry_registers"] = dict(entry_registers)

    observations = {}
    for case in cases:
        for item in case.get("observations", []):
            label = " | ".join(item.get("matches", []))
            if not label:
                label = item.get("bytes") or "unread"
            observations.setdefault(item["name"], Counter())[label] += 1
    summary["observations"] = {
        name: dict(counts) for name, counts in observations.items()
    }

    field_rows = []
    covered = set()
    for field in layout.get("fields", []):
        entry_values, exit_values = [], []
        changed = comparable = 0
        for case in cases:
            before = decode_value(case.get("entry", {}).get("object", {}).get("hex"), field)
            after = decode_value(case.get("exit", {}).get("object", {}).get("hex"), field)
            entry_values.append(before)
            exit_values.append(after)
            if before is not None and after is not None:
                comparable += 1
                if before["hex"] != after["hex"]:
                    changed += 1
        covered.update(range(field["offset"], field["offset"] + field["size"]))
        field_rows.append({
            **field,
            "entry_values": _unique_displays(entry_values),
            "exit_values": _unique_displays(exit_values),
            "changed_cases": changed,
            "comparable_cases": comparable,
        })
    summary["fields"] = field_rows

    ranges, comparable = _changed_ranges(cases, layout.get("object_size", 0))
    for row in ranges:
        row["named"] = all(off in covered for off in range(row["start"], row["end"] + 1))
    summary["write_ranges"] = ranges
    summary["write_comparable_cases"] = comparable

    returns = Counter()
    for case in cases:
        regs = case.get("exit", {}).get("regs")
        if regs:
            returns[f"r0=0x{regs['r0']:08x} r1=0x{regs['r1']:08x}"] += 1
    summary["returns"] = dict(returns)

    # Preserve the first observed table per concrete vptr; every later hit with
    # that vptr should be identical, and retaining all copies bloats the report.
    tables = {}
    for case in cases:
        vt = case.get("entry", {}).get("object", {}).get("vtable") or {}
        if vt.get("plausible") and vt.get("addr") is not None:
            tables.setdefault(_vtable_label(vt), vt.get("slots", []))
    summary["vtable_slots"] = tables
    return summary


def _format_counts(counts):
    return ", ".join(f"{name} ({count})" for name, count in counts.items()) or "none"


def _slot_class_counts(slots):
    """Method-owner hints from resolved slots; not concrete-vtable claims."""
    counts = Counter()
    for slot in slots:
        for symbol in slot.get("symbols", []):
            info = demangle.demangle(symbol)
            if info and info.get("class"):
                counts[info["class"]] += 1
    return dict(counts)


def render_report(evidence):
    target = evidence["target"]
    layout = evidence["layout"]
    summary = evidence.get("summary") or summarize(evidence)
    info = demangle.demangle(target["name"])
    qualified = info.get("qualified") if info else target["name"]
    lines = []
    if evidence.get("question"):
        lines.append(f"Question: {evidence['question']}")
    lines.append(f"Target: {qualified}  [{target['name']}]")
    lines.append(f"Runtime: {target['module']} {target['addr']:#010x} "
                 f"({target.get('instruction_set', 'arm')}), "
                 f"canary={target['canary']} ({target.get('canary_source', 'unknown')})")
    if layout.get("class"):
        source = layout.get("header") or "no reconstructed header"
        lines.append(f"C++ view: class {layout['class']}, {source}, this={layout.get('this_reg') or 'disabled'}, "
                     f"capture={layout.get('object_size', 0):#x} bytes")
        lines.append(f"Receiver evidence: {layout.get('receiver_classification', 'undecided')}"
                     + (f" ({layout['receiver_evidence']})" if layout.get("receiver_evidence") else ""))
    lines.append(f"Evidence: {summary['entry_hits']} entry hit(s), "
                 f"{summary['completed_returns']} completed return(s), "
                 f"{evidence.get('alias_rejects', 0)} overlay-alias reject(s)")
    if summary.get("statuses"):
        lines.append("Statuses: " + _format_counts(summary["statuses"]))
    lines.append("Callers: " + _format_counts(summary.get("callers", {})))
    if summary.get("entry_registers"):
        lines.append("Entry registers: " + _format_counts(summary["entry_registers"]))
    for name, counts in summary.get("observations", {}).items():
        lines.append(f"Observed {name}: " + _format_counts(counts))
    if layout.get("this_reg"):
        lines.append("Objects: " + _format_counts(summary.get("objects", {})))
        lines.append("Vtables: " + _format_counts(summary.get("vtables", {})))

    if summary.get("fields"):
        lines.append("Named field observations:")
        for field in summary["fields"]:
            entry = "; ".join(field["entry_values"]) or "unread"
            exit_values = "; ".join(field["exit_values"])
            change = (f", changed {field['changed_cases']}/{field['comparable_cases']} return(s)"
                      if field["comparable_cases"] else "")
            suffix = f" -> {exit_values}" if exit_values else ""
            lines.append(f"  +0x{field['offset']:03x} {field['name']} ({field['type']}): "
                         f"{entry}{suffix}{change}")
    elif layout.get("this_reg"):
        lines.append("Named field observations: none decodable; add --field OFFSET:TYPE:NAME")

    if summary.get("write_ranges"):
        lines.append("Writes through this (byte ranges):")
        for row in summary["write_ranges"]:
            end = f"..+0x{row['end']:03x}" if row["end"] != row["start"] else ""
            label = "named" if row.get("named") else "UNNAMED"
            lines.append(f"  +0x{row['start']:03x}{end}: {row['cases']}/"
                         f"{summary['write_comparable_cases']} return(s), {label}")
    elif summary.get("write_comparable_cases"):
        lines.append("Writes through this: none observed in the captured window")

    for vt, slots in summary.get("vtable_slots", {}).items():
        lines.append(f"Vtable {vt}:")
        slot_classes = _slot_class_counts(slots)
        if slot_classes:
            lines.append("  method-owner hints (not concrete type proof): "
                         + _format_counts(slot_classes))
        for slot in slots:
            names = " | ".join(slot["symbols"]) or "unresolved"
            lines.append(f"  [{slot['slot']:02d}] 0x{slot['addr']:08x} {names}")
    if summary.get("returns"):
        lines.append("Return registers: " + _format_counts(summary["returns"]))

    if layout.get("unknown_type_fields"):
        items = ", ".join(f"+0x{f['offset']:x} {f['name']}:{f['type']}"
                          for f in layout["unknown_type_fields"][:8])
        lines.append(f"Header fields not auto-decoded: {items}")
    if layout.get("omitted_fields"):
        lines.append(f"{len(layout['omitted_fields'])} known field(s) fell outside the capture; "
                     "raise --object-size to include them")
    lines.append("Interpretation limit: observed values/calls/writes constrain the C++ hypothesis; "
                 "they do not prove unobserved paths, field signedness, or byte identity.")
    return "\n".join(lines)


def resolution_report(target, layout):
    size = target.get("size")
    size_text = f"{size:#x}" if isinstance(size, int) else str(size or "unknown")
    lines = [
        f"resolved {target['name']} -> {target['module']} {target['addr']:#010x} "
        f"size={size_text} {target.get('instruction_set', 'arm')} "
        f"canary={target['canary']} "
        f"({target.get('canary_source', 'unknown')})",
        f"class={layout.get('class') or '-'} header={layout.get('header') or '-'} "
        f"this={layout.get('this_reg') or '-'} object_size={layout.get('object_size', 0):#x} "
        f"vtable={'yes' if layout.get('has_vtable') else 'no'}",
        f"receiver={layout.get('receiver_classification', 'undecided')} "
        f"({layout.get('receiver_evidence') or 'no evidence'})",
    ]
    for field in layout.get("fields", []):
        lines.append(f"  +0x{field['offset']:03x} {field['name']}: {field['type']} "
                     f"[{field['kind']}, {field['size']} byte(s)]")
    if layout.get("unknown_type_fields"):
        lines.append(f"  ({len(layout['unknown_type_fields'])} header field(s) need an explicit decoder)")
    return "\n".join(lines)


def _default_output(symbol):
    info = demangle.demangle(symbol)
    label = info.get("qualified") if info else symbol
    safe = re.sub(r"[^A-Za-z0-9_.-]+", "_", label).strip("_") or "probe"
    return REPO / "traces" / "questions" / f"{safe}.json"


def main(argv=None):
    ap = argparse.ArgumentParser(
        description="answer readable-C++ questions with runtime emulator evidence")
    ap.add_argument("symbol", nargs="?", help="configured function symbol (module:name if ambiguous)")
    ap.add_argument("--input", help="render a previously saved evidence JSON instead of capturing")
    ap.add_argument("--ask", help="human question stored with the evidence")
    ap.add_argument("--class-name", help="header class override (normally inferred from mangling)")
    ap.add_argument("--this-reg", choices=("auto", "none", "r0", "r1", "r2", "r3"),
                    default="auto", help="object pointer register (auto: r0 only when source proves an instance method)")
    ap.add_argument("--field", action="append", type=parse_field_spec, default=[],
                    help="extra/override field OFFSET:TYPE[:NAME] (repeatable)")
    ap.add_argument("--object-size", type=parse_int,
                    help="bytes to capture at this (default: fit known fields, capped at 0x400)")
    ap.add_argument("--max-auto-bytes", type=parse_int, default=0x400)
    ap.add_argument("--vtable-slots", type=int, default=12)
    ap.add_argument("--hits", type=int, default=5)
    ap.add_argument("--duration", type=float, default=90.0)
    ap.add_argument("--idle", type=float, default=20.0)
    ap.add_argument("--poll-timeout", type=float, default=2.0)
    ap.add_argument("--no-return", action="store_true",
                    help="entry-only capture for recursive/non-returning/hot functions")
    ap.add_argument("--host", default="127.0.0.1")
    ap.add_argument("--port", type=int, default=3333)
    ap.add_argument("--extracted", help="ROM extract directory (else auto-find/SM64DS_EXTRACTED)")
    ap.add_argument("--out", help="evidence JSON path (default traces/questions/<method>.json)")
    ap.add_argument("--resolve-only", action="store_true",
                    help="show target/header/field resolution without connecting")
    args = ap.parse_args(argv)

    if args.input:
        evidence = json.loads(pathlib.Path(args.input).read_text(encoding="utf-8"))
        print(render_report(evidence))
        return 0
    if not args.symbol:
        ap.error("symbol is required unless --input is used")
    if args.hits < 1:
        ap.error("--hits must be at least 1")
    if args.duration <= 0 or args.idle <= 0 or args.poll_timeout <= 0:
        ap.error("--duration, --idle, and --poll-timeout must be positive")
    if args.vtable_slots < 0:
        ap.error("--vtable-slots cannot be negative")
    if args.object_size is not None and args.object_size < 1:
        ap.error("--object-size must be positive")
    if args.max_auto_bytes < 0x10:
        ap.error("--max-auto-bytes must be at least 0x10")

    targets, missing = bplist.from_names(
        [args.symbol], repo=REPO, extracted=args.extracted)
    if missing or not targets:
        print(f"[!] could not resolve {args.symbol!r} with an 8-byte ROM canary.\n"
              "    If this is a linked worktree, set SM64DS_EXTRACTED to the primary\n"
              "    checkout's extracted directory. Use module:name for duplicate symbols.",
              file=sys.stderr)
        return 2
    target = targets[0]
    layout = discover_layout(
        target["name"], args.class_name, args.field, REPO,
        args.object_size, args.max_auto_bytes, args.this_reg)
    print(resolution_report(target, layout))
    if args.resolve_only:
        return 0

    print(f"[*] connecting to {args.host}:{args.port}; play/load the scene that calls the target ...")
    try:
        cases, alias_rejects, elapsed = collect(
            target, layout, args.host, args.port, args.hits, args.duration,
            args.idle, args.poll_timeout, args.vtable_slots, not args.no_return)
    except (OSError, RspError, TimeoutError) as exc:
        print(f"[!] emulator probe failed: {exc}\n"
              "    Start melonDS with [Gdb.ARM9] enabled, JIT off, and restart it if a\n"
              "    previous client used the stub's single session.", file=sys.stderr)
        return 3

    evidence = {
        "schema": SCHEMA,
        "created_at": dt.datetime.now(dt.timezone.utc).isoformat(),
        "question": args.ask,
        "target": target,
        "layout": layout,
        "capture": {
            "host": args.host, "port": args.port, "requested_hits": args.hits,
            "elapsed_seconds": elapsed, "capture_return": not args.no_return,
            "vtable_slots": args.vtable_slots,
        },
        "alias_rejects": alias_rejects,
        "cases": cases,
    }
    evidence["summary"] = summarize(evidence)
    out = pathlib.Path(args.out) if args.out else _default_output(target["name"])
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(evidence, indent=2) + "\n", encoding="utf-8")
    print()
    print(render_report(evidence))
    print(f"\n[=] evidence saved to {out}")
    return 0 if cases else 4


if __name__ == "__main__":
    sys.exit(main())
