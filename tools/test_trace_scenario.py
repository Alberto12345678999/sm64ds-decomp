import json
import pathlib
import sys

import pytest

TRACE = pathlib.Path(__file__).parent / "trace"
sys.path.insert(0, str(TRACE))

import input_win  # noqa: E402
import melon_control  # noqa: E402
import scenario  # noqa: E402
import cpp_probe  # noqa: E402
import rsp  # noqa: E402


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

    def step_frames(self, frames):
        self.events.append(("step_frames", frames))

    def load_state(self, path):
        self.events.append(("load_state", path))


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


def test_input_steps_support_deterministic_frames_and_direct_savestate_load():
    driver = FakeDriver()
    input_win.run_steps(driver, [
        {"action": "load_state", "path": "painting.mln"},
        {"action": "wait", "frames": 75},
        {"action": "hold", "keys": ["dpad_up", "button_a"], "frames": 1},
    ], announce=lambda _: None)

    assert driver.events == [
        ("load_state", "painting.mln"),
        ("step_frames", 60), ("step_frames", 15),
        ("down", "dpad_up"), ("down", "button_a"),
        ("step_frames", 1),
        ("up", "button_a"), ("up", "dpad_up"),
        ("release_all",),
    ]


def test_control_driver_maps_buttons_touch_and_frame_chunks(tmp_path):
    class FakeControl:
        def __init__(self):
            self.requests = []

        def request(self, command, **parameters):
            self.requests.append((command, parameters))
            return {"ok": True}

    driver = melon_control.ControlMelonInput.__new__(
        melon_control.ControlMelonInput)
    driver.client = FakeControl()
    driver.state_root = tmp_path
    driver.fps = 60.0
    driver.held = set()
    driver._fractional_frames = 0.0

    driver.key_down("dpad_up")
    driver.key_down("button_a")
    driver.touch(0.5, 0.25, seconds=0.1)
    driver.step_frames(601)
    driver.release_all()
    driver.resume()
    driver.close()

    assert driver.client.requests == [
        ("set_input", {"buttons": ["Up"]}),
        ("set_input", {"buttons": ["A", "Up"]}),
        ("set_input", {
            "buttons": ["A", "Up"], "touch": {"x": 128, "y": 48}}),
        ("step", {"frames": 6}),
        ("set_input", {"buttons": ["A", "Up"]}),
        ("step", {"frames": 600}),
        ("step", {"frames": 1}),
        ("release_input", {}),
        ("resume", {}),
        ("clear_input_override", {}),
    ]


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


def test_collect_runs_pre_arm_hook_before_breakpoint_and_continue():
    events = []

    class FakeClient:
        def connect(self):
            events.append("connect")
            return self

        def set_breakpoint(self, addr, kind):
            events.append("arm")
            return True

        def clear_breakpoint(self, addr, kind):
            events.append("clear")
            return True

        def cont(self):
            events.append("continue")

        def detach(self):
            events.append("detach")

        def close(self):
            events.append("close")

    cpp_probe.collect(
        {"addr": 0x02008C18, "breakpoint_kind": 4},
        {"memory_reads": []}, hits=0,
        client_factory=lambda *args, **kwargs: FakeClient(),
        on_pre_arm=lambda _cli: events.append("pre-arm"),
        on_ready=lambda _cli: events.append("ready"))

    assert events == [
        "connect", "pre-arm", "arm", "continue", "ready",
        "clear", "detach", "close",
    ]


def test_capture_case_reads_register_relative_values():
    class FakeClient:
        def read_mem(self, addr, size):
            assert (addr, size) == (0x02010006, 1)
            return b"\x0c"

    class FakeSymbols:
        ranges = []

    regs = {
        "r0": 1, "r1": 0x02010000, "r2": 3, "r3": 4,
        "sp": 0x02020000, "lr": 0x02009000, "pc": 0x02008550,
    }
    layout = {
        "this_reg": None, "object_size": 0, "fields": [],
        "memory_reads": [],
        "register_reads": [{
            "name": "camera command", "register": "r1",
            "offset": 6, "size": 1, "type": "u8",
        }],
    }

    case, running = cpp_probe.capture_case(
        FakeClient(), {"addr": 0x02008550}, regs, layout,
        FakeSymbols(), capture_return=False)

    assert running is False
    assert case["observations"] == [{
        "name": "camera command", "register": "r1", "offset": 6,
        "addr": 0x02010006, "bytes": "0c", "value": 12,
        "display": "12",
    }]
    evidence = {"layout": layout, "cases": [case]}
    assert cpp_probe.summarize(evidence)["observations"] == {
        "camera command": {"12": 1}}


def test_setup_memory_clear_bits_is_verified_and_audited():
    class FakeClient:
        def __init__(self):
            self.value = b"\xd5"

        def read_mem(self, addr, size):
            assert (addr, size) == (0x0209CAA2, 1)
            return self.value

        def write_mem(self, addr, data):
            assert addr == 0x0209CAA2
            self.value = data
            return True

    events = scenario.apply_memory_setup(FakeClient(), [{
        "name": "rearm intro", "address": "0x0209caa2",
        "size": 1, "clear_bits": "0x80",
    }])

    assert events == [{
        "name": "rearm intro", "address": 0x0209CAA2, "size": 1,
        "before": "d5", "after": "55",
    }]


def test_unique_observation_filter_keeps_bounded_examples_per_value():
    accept, counts = scenario.unique_observation_filter(
        "camera command", max_per_value=1)
    case6 = {"observations": [{"name": "camera command", "value": 6}]}
    case12 = {"observations": [{"name": "camera command", "value": 12}]}

    assert accept(case6) is True
    assert accept(case6) is False
    assert accept(case12) is True
    assert counts == {"6": 1, "12": 1}


def test_rsp_write_mem_uses_binary_hex_packet():
    client = rsp.RspClient()
    sent = []
    client.send_packet = lambda payload: sent.append(payload) or "OK"

    assert client.write_mem(0x0209CAA2, b"\x55") is True
    assert sent == ["M209caa2,1:55"]


def test_capture_case_records_direct_register_value():
    class FakeClient:
        pass

    class FakeSymbols:
        ranges = []

    regs = {
        "r0": 0x14F, "r1": 2, "r2": 3, "r3": 4,
        "sp": 0x02020000, "lr": 0x02009000, "pc": 0x02013EE8,
    }
    layout = {
        "this_reg": None, "object_size": 0, "fields": [],
        "memory_reads": [], "register_reads": [],
        "register_values": [{
            "name": "actor id", "register": "r0", "display": "hex",
        }],
    }

    case, running = cpp_probe.capture_case(
        FakeClient(), {"addr": 0x02013EE8}, regs, layout,
        FakeSymbols(), capture_return=False)

    assert running is False
    assert case["observations"] == [{
        "name": "actor id", "register": "r0", "value": 0x14F,
        "display": "0x0000014f",
    }]


def test_scenario_expectations_are_machine_checkable():
    summary = {"observations": {
        "callee overlay": {"ov002:func_ov002_020effb8": 1},
        "camera command": {"6": 1},
    }}
    results = scenario.evaluate_expectations([
        {
            "observation": "callee overlay",
            "value": "ov002:func_ov002_020effb8",
        },
        {"observation": "camera command", "value": 12},
    ], summary)

    assert results[0]["passed"] is True
    assert results[1]["passed"] is False
    assert results[1]["actual_count"] == 0
