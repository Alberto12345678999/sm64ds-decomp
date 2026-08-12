"""Focused tests for the question-oriented emulator C++ probe."""
import json
import pathlib
import struct
import sys

TOOLS = pathlib.Path(__file__).resolve().parent
TRACE = TOOLS / "trace"
sys.path.insert(0, str(TRACE))
sys.path.insert(0, str(TOOLS))

import bplist  # noqa: E402
import cpp_probe as CP  # noqa: E402
import symindex  # noqa: E402


def _object(vtable=0x02018000, curr=0x400, speed=-0x80):
    return struct.pack("<IiiI", vtable, curr, speed, 0)


def test_find_extracted_prefers_explicit_environment_override(tmp_path, monkeypatch):
    local = tmp_path / "repo" / "extracted"
    override = tmp_path / "override"
    local.mkdir(parents=True)
    override.mkdir()
    (local / "arm9_dec.bin").write_bytes(b"local")
    (override / "arm9_dec.bin").write_bytes(b"override")
    monkeypatch.setenv("SM64DS_EXTRACTED", str(override))

    assert bplist.find_extracted(tmp_path / "repo") == override


def test_symbol_index_resolves_exact_vtable_aliases(tmp_path):
    cfg = tmp_path / "config" / "arm9"
    cfg.mkdir(parents=True)
    (cfg / "symbols.txt").write_text(
        "_ZTV5Thing kind:data(any) addr:0x02018000\n"
        "ThingVtableAlias kind:data(any) addr:0x02018000\n",
        encoding="utf-8")

    index = symindex.SymIndex(tmp_path)

    assert index.resolve_exact(0x02018000) == [
        "arm9:ThingVtableAlias", "arm9:_ZTV5Thing"]


def test_configured_matched_symbol_gets_rom_canary(tmp_path):
    cfg = tmp_path / "config" / "arm9"
    cfg.mkdir(parents=True)
    (cfg / "symbols.txt").write_text(
        "_ZN5Thing4TickEv kind:function(arm,size=0xc) addr:0x02004004\n"
        "Div kind:function(thumb,size=0x4) addr:0x02004008\n",
        encoding="utf-8")
    (tmp_path / "nearmiss").mkdir()
    (tmp_path / "nearmiss" / "db.jsonl").write_text("", encoding="utf-8")
    extracted = tmp_path / "rom-assets"
    extracted.mkdir()
    blob = bytes.fromhex("00010203 aabbccdd 11223344 55667788")
    (extracted / "arm9_dec.bin").write_bytes(blob)

    targets, missing = bplist.from_names(
        ["_ZN5Thing4TickEv"], repo=tmp_path, extracted=extracted)

    assert missing == []
    assert targets == [{
        "name": "_ZN5Thing4TickEv",
        "addr": 0x02004004,
        "module": "arm9",
        "size": 0xC,
        "canary": "aabbccdd11223344",
        "canary_source": "rom",
        "instruction_set": "arm",
        "breakpoint_kind": 4,
    }]

    thumb, missing = bplist.from_names(["Div"], repo=tmp_path, extracted=extracted)
    assert missing == []
    assert thumb[0]["instruction_set"] == "thumb"
    assert thumb[0]["breakpoint_kind"] == 2


def test_overlay_canary_uses_data_symbol_before_first_function(tmp_path):
    cfg = tmp_path / "config" / "arm9"
    overlay_cfg = cfg / "overlays" / "ov001"
    overlay_cfg.mkdir(parents=True)
    (cfg / "symbols.txt").write_text("", encoding="utf-8")
    (overlay_cfg / "symbols.txt").write_text(
        "data_02110000 kind:data(any) addr:0x02110000\n"
        "_ZN5Thing4TickEv kind:function(arm,size=0xc) addr:0x02110004\n",
        encoding="utf-8")
    (tmp_path / "nearmiss").mkdir()
    (tmp_path / "nearmiss" / "db.jsonl").write_text("", encoding="utf-8")
    overlays = tmp_path / "extracted" / "overlays"
    overlays.mkdir(parents=True)
    (tmp_path / "extracted" / "arm9_dec.bin").write_bytes(b"")
    (overlays / "overlay_0001.bin").write_bytes(
        bytes.fromhex("deadbeef aabbccdd 11223344 55667788"))

    targets, missing = bplist.from_names(
        ["_ZN5Thing4TickEv"], repo=tmp_path, extracted=tmp_path / "extracted")

    assert missing == []
    assert targets[0]["module"] == "ov001"
    assert targets[0]["addr"] == 0x02110004
    assert targets[0]["canary"] == "aabbccdd11223344"


def test_nearmiss_target_still_resolves_without_local_rom_extracts(tmp_path):
    (tmp_path / "nearmiss").mkdir()
    row = {"name": "func_02005000", "addr": "0x02005000", "module": "arm9",
           "size": 0x10, "target_hex": "1122334455667788" + "00" * 8}
    (tmp_path / "nearmiss" / "db.jsonl").write_text(
        json.dumps(row) + "\n", encoding="utf-8")

    targets, missing = bplist.from_names([row["name"]], repo=tmp_path)

    assert missing == []
    assert targets[0]["canary"] == "1122334455667788"
    assert targets[0]["canary_source"] == "nearmiss"


def test_layout_is_inferred_from_class_header_and_cli_can_override(tmp_path):
    inc = tmp_path / "include"
    inc.mkdir()
    (inc / "Thing.h").write_text("""\
struct Thing {
    void* vtable;       /* 0x000 */
    Fix12i amount;      /* 0x004 */
    s16 state;          /* 0x008 */
};
""", encoding="utf-8")
    src = tmp_path / "src"
    src.mkdir()
    (src / "_ZN5Thing4TickEv.cpp").write_text(
        "void Thing::Tick() {}\n", encoding="utf-8")
    override = CP.parse_field_spec("0x8:u16:stateBits")

    layout = CP.discover_layout(
        "_ZN5Thing4TickEv", extra_fields=[override], repo=tmp_path)

    assert layout["class"] == "Thing"
    assert layout["receiver_classification"] == "instance"
    assert layout["this_reg"] == "r0"
    assert layout["has_vtable"]
    assert layout["object_size"] == 0x10
    by_off = {f["offset"]: f for f in layout["fields"]}
    assert by_off[4]["kind"] == "fix12"
    assert by_off[8]["name"] == "stateBits"
    assert by_off[8]["kind"] == "unsigned"


def test_auto_receiver_does_not_turn_static_or_undecided_into_this(tmp_path):
    inc = tmp_path / "include"
    inc.mkdir()
    (inc / "Thing.h").write_text("""\
struct Thing { s32 value; /* 0x000 */ };
""", encoding="utf-8")
    src = tmp_path / "src"
    src.mkdir()
    # The mangling carries one int arg and the hand-spelled C definition also
    # carries one: r0 is argument 1, not an implicit object.
    symbol = "_ZN5Thing4PickEi"
    (src / f"{symbol}.c").write_text(
        f"int {symbol}(int value) {{ return value; }}\n", encoding="utf-8")

    layout = CP.discover_layout(symbol, repo=tmp_path)

    assert layout["receiver_classification"] == "static"
    assert layout["this_reg"] is None
    assert not layout["has_vtable"]
    assert CP.discover_layout(symbol, repo=tmp_path, this_reg="r0")["this_reg"] == "r0"


def test_plain_c_symbol_has_no_implicit_receiver(tmp_path):
    layout = CP.discover_layout("Div", repo=tmp_path)

    assert layout["receiver_classification"] == "not-applicable"
    assert layout["this_reg"] is None


def test_runtime_value_decoders_keep_fixed_point_and_signedness_visible():
    blob = _object().hex()
    fix = {"offset": 4, "size": 4, "kind": "fix12"}
    signed = {"offset": 8, "size": 4, "kind": "signed"}

    assert CP.decode_value(blob, fix)["display"] == "0.25 (raw 0x400)"
    assert CP.decode_value(blob, signed)["value"] == -0x80


class _Syms:
    ranges = [(0x02012000, 0x02012100, "Caller"),
              (0x02013000, 0x02013100, "VirtualMethod")]

    @staticmethod
    def resolve_exact(addr):
        return ["arm9:_ZTV5Thing"] if addr == 0x02018000 else []


def test_code_pointers_resolve_exactly_but_lr_resolves_the_callsite():
    class Adjacent:
        ranges = [(0x02010000, 0x02010004, "Previous"),
                  (0x02010004, 0x02010100, "Current")]

    assert CP._resolve_at(Adjacent(), 0x02010004) == ["Current"]
    assert CP._resolve_caller(Adjacent(), 0x02010008) == ["Current"]
    assert CP._resolve_caller(Adjacent(), 0x02010007) == ["Current"]


class _FakeClient:
    def __init__(self):
        self.after = False
        self.cleared = []

    def read_mem(self, addr, size):
        if addr == 0x02020000:
            data = _object(curr=0x800 if self.after else 0x400)
            return data[:size]
        if addr == 0x02018000:
            table = struct.pack("<III", 0x02013000, 0, 0x02013004)
            return table[:size]
        raise AssertionError(f"unexpected read {addr:#x}, {size}")

    def set_breakpoint(self, addr, kind=4):
        assert addr == 0x02012004
        assert kind == 4
        return True

    def clear_breakpoint(self, addr, kind=4):
        assert kind == 4
        self.cleared.append(addr)
        return True

    def cont(self):
        self.after = True

    def wait_for_stop(self):
        return "S05"

    def read_registers(self):
        return {"r0": 7, "r1": 9, "r2": 0, "r3": 0,
                "sp": 0x023FF000, "lr": 0x02012004, "pc": 0x02012004}


def test_capture_pairs_entry_and_return_and_rereads_same_object():
    cli = _FakeClient()
    target = {"addr": 0x02011000}
    regs = {"r0": 0x02020000, "r1": 0, "r2": 0, "r3": 0,
            "sp": 0x023FF000, "lr": 0x02012004, "pc": 0x02011000}
    layout = {"this_reg": "r0", "object_size": 0x10, "has_vtable": True}

    case, running = CP.capture_case(
        cli, target, regs, layout, _Syms(), vtable_slots=3, capture_return=True)

    assert not running
    assert case["status"] == "returned"
    assert case["entry"]["caller_symbols"] == ["Caller"]
    assert case["entry"]["object"]["vtable"]["symbols"] == ["arm9:_ZTV5Thing"]
    assert case["entry"]["object"]["vtable"]["slots"][0]["symbols"] == ["VirtualMethod"]
    assert case["entry"]["object"]["hex"] != case["exit"]["object"]["hex"]
    assert cli.cleared == [0x02012004]


def test_capture_joins_receiver_to_protocol_actor_snapshot():
    class ActorClient:
        def read_mem(self, addr, size):
            assert addr == 0x02020000
            return bytes(size)

        def research_snapshot(self):
            return {
                "profile": "ASMP",
                "level_overlay": 2,
                "actors": [{
                    "address": "0x02020000", "id": 74, "name": "Goomba",
                    "kind": "enemy", "class": "Goomba",
                    "vtable": "0x020f1234", "behavior": "0x020e4d24",
                    "behavior_name": "Goomba::Behavior()",
                    "position": {"x": 1.0, "y": 2.0, "z": 3.0},
                }],
            }

    regs = {"r0": 0x02020000, "r1": 0, "r2": 0, "r3": 0,
            "sp": 0x023FF000, "lr": 0x02012004, "pc": 0x02011000}
    layout = {"this_reg": "r0", "object_size": 0x10, "has_vtable": False}

    case, running = CP.capture_case(
        ActorClient(), {"addr": 0x02011000}, regs, layout, _Syms(),
        capture_return=False)

    assert not running
    assert case["entry"]["actor"]["class"] == "Goomba"
    assert case["entry"]["actor"]["level_overlay"] == 2
    assert case["entry"]["actor"]["position"]["z"] == 3.0
    assert case["entry"]["actor"]["configured_vtable_symbols"] == []
    assert case["entry"]["actor"]["configured_behavior_symbols"] == []


def test_summary_and_report_call_out_named_write():
    before = _object(curr=0x400).hex()
    after = _object(curr=0x800).hex()
    evidence = {
        "question": "does AdvanceInterp change currInterp?",
        "target": {"name": "_ZN5Fader13AdvanceInterpEv", "module": "arm9",
                   "addr": 0x020175E8, "canary": "00" * 8,
                   "canary_source": "rom"},
        "layout": {
            "class": "Fader", "header": "include/Fader.h", "header_chain": ["Fader"],
            "this_reg": "r0", "object_size": 0x10,
            "unknown_type_fields": [], "omitted_fields": [],
            "fields": [{"offset": 4, "size": 4, "kind": "fix12",
                        "name": "currInterp", "type": "Fix12i", "source": "header"}],
        },
        "alias_rejects": 0,
        "cases": [{
            "status": "returned",
            "entry": {"caller_addr": 0x02012004, "caller_symbols": ["Caller"],
                      "regs": {"r0": 0x02020000, "r1": 0x1e, "r2": 0, "r3": 0},
                      "actor": {"address": 0x02020000, "id": 74,
                                "name": "Goomba", "class": "Goomba",
                                "configured_vtable_symbols": ["ov084:_ZTV6Goomba"],
                                "configured_behavior_symbols": [
                                    "ov084:_ZN6Goomba8BehaviorEv"]},
                      "object": {"addr": 0x02020000, "hex": before,
                                 "vtable": {"addr": 0x02018000, "plausible": True,
                                            "symbols": ["arm9:_ZTV5Thing"],
                                            "slots": [{
                                                "slot": 5,
                                                "addr": 0x02013000,
                                                "symbols": ["_ZN15FaderBrightness7IsAtEndEv"],
                                            }]}}},
            "exit": {"regs": {"r0": 0, "r1": 0},
                     "object": {"addr": 0x02020000, "hex": after, "vtable": None}},
        }],
    }

    evidence["summary"] = CP.summarize(evidence)
    report = CP.render_report(evidence)

    assert evidence["summary"]["fields"][0]["changed_cases"] == 1
    assert any(r["start"] <= 5 <= r["end"] and r["named"]
               for r in evidence["summary"]["write_ranges"])
    assert "currInterp" in report
    assert "r1=0x0000001e" in report
    assert "arm9:_ZTV5Thing @ 0x02018000" in report
    assert "method-owner hints (not concrete type proof): FaderBrightness (1)" in report
    assert "Live actor receivers (catalog labels): Goomba @ 0x02020000 (1)" in report
    assert "config-vtable=ov084:_ZTV6Goomba" in report
    assert "config-behavior=ov084:_ZN6Goomba8BehaviorEv" in report
    assert "changed 1/1" in report
    assert "does AdvanceInterp change currInterp?" in report
