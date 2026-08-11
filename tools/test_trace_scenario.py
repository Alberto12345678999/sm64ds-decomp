import json
import pathlib
import sys

import pytest

TRACE = pathlib.Path(__file__).parent / "trace"
sys.path.insert(0, str(TRACE))

import input_win  # noqa: E402
import scenario  # noqa: E402
import cpp_probe  # noqa: E402


class FakeDriver:
    def __init__(self):
        self.events = []

    def focus(self):
        self.events.append(("focus",))

    def key_down(self, key):
        self.events.append(("down", key))

    def key_up(self, key):
        self.events.append(("up", key))

    def release_all(self):
        self.events.append(("release_all",))

    def touch(self, x, y, seconds=0.08):
        self.events.append(("touch", x, y, seconds))


def test_melonds_keyboard_bindings_translate_qt_special_keys(tmp_path):
    config = tmp_path / "melonDS.toml"
    config.write_text(
        "[Instance0.Keyboard]\n"
        "A = 16777236\n"
        "B = 16777237\n"
        "Up = 87\n"
        "Start = 16777220\n", encoding="utf-8")

    bindings = input_win.load_bindings(config)

    assert bindings["button_a"] == 0x27
    assert bindings["button_b"] == 0x28
    assert bindings["dpad_up"] == ord("W")
    assert bindings["start"] == 0x0D
    assert bindings["hotkey_load_slot_1"] == 0x70


def test_input_steps_press_combinations_and_always_release():
    driver = FakeDriver()
    steps = [
        {"action": "focus"},
        {"action": "tap", "key": "button_b", "seconds": 0},
        {"action": "touch", "x": 0.5, "y": 0.9, "seconds": 0},
        {"action": "hold", "keys": ["dpad_up", "button_b"], "seconds": 0},
    ]

    input_win.run_steps(driver, steps, announce=lambda _: None)

    assert driver.events == [
        ("focus",),
        ("down", "button_b"), ("up", "button_b"),
        ("touch", 0.5, 0.9, 0),
        ("down", "dpad_up"), ("down", "button_b"),
        ("up", "button_b"), ("up", "dpad_up"),
        ("release_all",),
    ]


def test_input_steps_release_keys_when_a_later_step_is_invalid():
    driver = FakeDriver()
    with pytest.raises(ValueError, match="unsupported input action"):
        input_win.run_steps(driver, [{"action": "bogus"}], announce=lambda _: None)
    assert driver.events[-1] == ("release_all",)


def test_scenario_manifest_requires_one_target_and_steps(tmp_path):
    path = tmp_path / "scenario.json"
    path.write_text(json.dumps({
        "schema": scenario.SCHEMA,
        "name": "pilot",
        "target": "ov002:func_ov002_020effb8",
        "setup_steps": [{"action": "focus"}],
        "steps": [{"action": "wait", "seconds": 1}],
    }), encoding="utf-8")

    loaded = scenario.load_scenario(path)
    assert loaded["name"] == "pilot"
    assert loaded["setup_steps"] == [{"action": "focus"}]

    loaded.pop("target")
    path.write_text(json.dumps(loaded), encoding="utf-8")
    with pytest.raises(ValueError, match="target"):
        scenario.load_scenario(path)


def test_capture_case_classifies_observed_overlay_candidate():
    class FakeClient:
        def read_mem(self, addr, size):
            assert addr == 0x020EFFB8
            assert size == 8
            return bytes.fromhex("f04f2de91cd04de2")

    class FakeSymbols:
        ranges = []

    regs = {
        "r0": 1, "r1": 2, "r2": 3, "r3": 4,
        "sp": 0x02010000, "lr": 0x02009000, "pc": 0x02008C18,
    }
    layout = {
        "this_reg": None,
        "object_size": 0,
        "fields": [],
        "memory_reads": [{
            "name": "callee overlay",
            "addr": 0x020EFFB8,
            "size": 8,
            "candidates": [{
                "qualified_name": "ov002:func_ov002_020effb8",
                "canary": "f04f2de91cd04de2",
            }, {
                "qualified_name": "ov006:func_ov006_020effb8",
                "canary": "10402de9",
            }],
        }],
    }

    case, running = cpp_probe.capture_case(
        FakeClient(), {"addr": 0x02008C18}, regs, layout,
        FakeSymbols(), capture_return=False)

    assert running is False
    assert case["observations"][0]["matches"] == [
        "ov002:func_ov002_020effb8"]
    evidence = {"layout": layout, "cases": [case]}
    assert cpp_probe.summarize(evidence)["observations"] == {
        "callee overlay": {"ov002:func_ov002_020effb8": 1}}


def test_collect_aborts_immediately_after_input_failure():
    class FakeClient:
        def connect(self):
            return self

        def set_breakpoint(self, addr, kind):
            return True

        def clear_breakpoint(self, addr, kind):
            return True

        def cont(self):
            return None

        def detach(self):
            return None

        def close(self):
            return None

    with pytest.raises(RuntimeError, match="scenario input failure"):
        cpp_probe.collect(
            {"addr": 0x02008C18, "breakpoint_kind": 4},
            {"memory_reads": []},
            client_factory=lambda *args, **kwargs: FakeClient(),
            should_abort=lambda: True)
