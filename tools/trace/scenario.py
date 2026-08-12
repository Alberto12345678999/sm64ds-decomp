#!/usr/bin/env python3
"""Run one emulator research question with scripted gameplay input.

The runner intentionally combines breakpoint evidence and input automation in
one process.  melonDS 1.1 exposes only one usable GDB client session, so a
separate actor watcher/probe/controller trio will wedge or race the stub.

A scenario is a small JSON document: one configured function target, capture
limits, and a deterministic sequence of DS controls.  It is not a general game
solver.  Scenarios should begin from a named, reproducible savestate or a very
specific manual setup, then automate only the path needed to answer the runtime
question.
"""
from __future__ import annotations

import argparse
from collections import Counter
import datetime as dt
import json
import os
import pathlib
import sys
import threading
import time

TRACE_DIR = pathlib.Path(__file__).resolve().parent
TOOLS_DIR = TRACE_DIR.parent
REPO = TOOLS_DIR.parent
sys.path.insert(0, str(TRACE_DIR))
sys.path.insert(0, str(TOOLS_DIR))

import bplist  # noqa: E402
import cpp_probe  # noqa: E402
from input_win import Win32MelonInput, load_bindings, run_steps  # noqa: E402
from melon_control import ControlMelonInput  # noqa: E402
from rsp import RspError  # noqa: E402


SCHEMA = "sm64ds-emulator-scenario-v1"
REGISTER_READ_TYPES = {
    "u8": 1, "s8": 1,
    "u16": 2, "s16": 2,
    "u32": 4, "s32": 4,
    "hex": None,
}
READ_REGISTERS = {"r0", "r1", "r2", "r3", "sp", "lr"}


def load_scenario(path):
    path = pathlib.Path(path)
    data = json.loads(path.read_text(encoding="utf-8"))
    if data.get("schema") != SCHEMA:
        raise ValueError(f"{path}: schema must be {SCHEMA!r}")
    if not isinstance(data.get("name"), str) or not data["name"].strip():
        raise ValueError(f"{path}: non-empty name is required")
    target = data.get("target")
    if not ((isinstance(target, str) and target.strip()) or
            (isinstance(target, dict) and target.get("module") and target.get("address"))):
        raise ValueError(
            f"{path}: target must be a module-qualified symbol or address object")
    setup_steps = data.get("setup_steps", [])
    steps = data.get("steps")
    if not isinstance(setup_steps, list):
        raise ValueError(f"{path}: setup_steps must be a list")
    if not isinstance(steps, list) or not steps:
        raise ValueError(f"{path}: at least one input step is required")
    for group_name, group in (("setup step", setup_steps), ("step", steps)):
        for index, step in enumerate(group, 1):
            if not isinstance(step, dict) or not isinstance(step.get("action"), str):
                raise ValueError(f"{path}: {group_name} {index} requires an action")
    for index, spec in enumerate(data.get("observe_args", []), 1):
        if spec.get("register") not in READ_REGISTERS:
            raise ValueError(f"{path}: observe_args {index} has invalid register")
        if spec.get("type", "hex") not in REGISTER_READ_TYPES:
            raise ValueError(f"{path}: observe_args {index} has invalid type")
    for index, spec in enumerate(data.get("observe_registers", []), 1):
        if spec.get("register") not in READ_REGISTERS:
            raise ValueError(f"{path}: observe_registers {index} has invalid register")
    for index, spec in enumerate(data.get("setup_memory", []), 1):
        ops = [name for name in ("value", "set_bits", "clear_bits") if name in spec]
        if "address" not in spec or len(ops) != 1:
            raise ValueError(
                f"{path}: setup_memory {index} needs address and exactly one operation")
    return data


def resolve_scenario(data, extracted=None):
    target_spec = data["target"]
    if isinstance(target_spec, str):
        targets, missing = bplist.from_names(
            [target_spec], repo=REPO, extracted=extracted)
        if missing or len(targets) != 1:
            raise ValueError(
                f"could not resolve {target_spec!r} with an 8-byte ROM canary")
        target = targets[0]
    else:
        address = target_spec["address"]
        address = int(address, 0) if isinstance(address, str) else int(address)
        target = bplist.from_address(
            target_spec["module"], address, name=target_spec.get("name"),
            repo=REPO, extracted=extracted,
            instruction_set=target_spec.get("instruction_set", "arm"),
            size=target_spec.get("size", 4))
        if target is None:
            raise ValueError(
                f"could not resolve {target_spec!r} with an 8-byte ROM canary")
    view = data.get("view", {})
    fields = [cpp_probe.parse_field_spec(item) for item in view.get("fields", [])]
    layout = cpp_probe.discover_layout(
        target["name"], class_name=view.get("class_name"),
        extra_fields=fields, repo=REPO, object_size=view.get("object_size"),
        max_auto_bytes=view.get("max_auto_bytes", 0x400),
        this_reg=view.get("this_reg", "auto"))
    memory_reads = []
    for spec in data.get("observe", []):
        candidates, missing = bplist.from_names(
            spec.get("candidates", []), repo=REPO, extracted=extracted)
        if missing or not candidates:
            raise ValueError(
                f"could not resolve observation candidates: {missing or spec!r}")
        addresses = {candidate["addr"] for candidate in candidates}
        if len(addresses) != 1:
            raise ValueError(f"observation candidates do not share one address: {spec!r}")
        memory_reads.append({
            "name": spec.get("name") or f"memory_{next(iter(addresses)):08x}",
            "addr": next(iter(addresses)),
            "size": spec.get("size", 8),
            "candidates": [
                {
                    "qualified_name": f"{candidate['module']}:{candidate['name']}",
                    "canary": candidate["canary"],
                }
                for candidate in candidates
            ],
        })
    layout["memory_reads"] = memory_reads
    register_reads = []
    for spec in data.get("observe_args", []):
        typ = spec.get("type", "hex")
        size = spec.get("size", REGISTER_READ_TYPES[typ])
        if not isinstance(size, int) or size < 1 or size > 64:
            raise ValueError(f"invalid observe_args size: {spec!r}")
        register_reads.append({
            "name": spec.get("name") or
                    f"{spec['register']}{_as_int(spec.get('offset', 0)):+#x}",
            "register": spec["register"],
            "offset": _as_int(spec.get("offset", 0)),
            "size": size,
            "type": typ,
        })
    layout["register_reads"] = register_reads
    layout["register_values"] = [
        {
            "name": spec.get("name") or spec["register"],
            "register": spec["register"],
            "display": spec.get("display", "hex"),
        }
        for spec in data.get("observe_registers", [])
    ]
    return target, layout


def _as_int(value):
    return int(value, 0) if isinstance(value, str) else int(value)


def apply_memory_setup(cli, specs):
    """Apply small, verified RAM setup operations and return their audit trail."""
    events = []
    for spec in specs:
        address = _as_int(spec["address"])
        size = int(spec.get("size", 1))
        if size not in (1, 2, 4):
            raise ValueError(f"setup_memory size must be 1, 2, or 4: {spec!r}")
        before_raw = cli.read_mem(address, size)
        before = int.from_bytes(before_raw, "little")
        mask = (1 << (size * 8)) - 1
        if "value" in spec:
            after = _as_int(spec["value"])
        elif "set_bits" in spec:
            after = before | _as_int(spec["set_bits"])
        else:
            after = before & ~_as_int(spec["clear_bits"])
        after &= mask
        after_raw = after.to_bytes(size, "little")
        if not cli.write_mem(address, after_raw):
            raise RuntimeError(f"stub refused setup_memory write at {address:#010x}")
        verified = cli.read_mem(address, size)
        if verified != after_raw:
            raise RuntimeError(
                f"setup_memory verification failed at {address:#010x}: "
                f"wrote {after_raw.hex()}, read {verified.hex()}")
        events.append({
            "name": spec.get("name") or f"memory_{address:08x}",
            "address": address,
            "size": size,
            "before": before_raw.hex(),
            "after": verified.hex(),
        })
    return events


def unique_observation_filter(name, max_per_value=1):
    counts = Counter()

    def accept(case):
        item = next((item for item in case.get("observations", [])
                     if item.get("name") == name), None)
        if item is None:
            key = "missing"
        else:
            key = json.dumps(item.get("value", item.get("bytes")), sort_keys=True)
        if counts[key] >= max_per_value:
            return False
        counts[key] += 1
        return True

    return accept, counts


def evaluate_expectations(specs, summary):
    results = []
    observations = summary.get("observations", {})
    for spec in specs:
        name = spec.get("observation")
        value = str(spec.get("value"))
        minimum = int(spec.get("min_count", 1))
        actual = int(observations.get(name, {}).get(value, 0))
        results.append({
            "observation": name,
            "value": value,
            "min_count": minimum,
            "actual_count": actual,
            "passed": actual >= minimum,
        })
    return results


class InputThread:
    def __init__(self, driver, steps):
        self.driver = driver
        self.steps = steps
        self.stop_event = threading.Event()
        self.thread = None
        self.error = None
        self.events = []

    def announce(self, message):
        self.events.append(message)
        print(message)

    def _run(self):
        try:
            run_steps(self.driver, self.steps,
                      sleep=getattr(self.driver, "sleep", time.sleep),
                      should_stop=self.stop_event.is_set,
                      announce=self.announce)
        except BaseException as exc:  # carry thread failures to the main result
            self.error = exc
            self.stop_event.set()

    def start(self):
        if self.thread is not None:
            raise RuntimeError("input script already started")
        self.thread = threading.Thread(
            target=self._run, name="melonDS-scenario-input", daemon=True)
        self.thread.start()

    def stop(self):
        self.stop_event.set()
        if self.thread is not None:
            self.thread.join(timeout=2.0)
        self.driver.release_all()


def _default_output(name):
    safe = "".join(c if c.isalnum() or c in "-_" else "_" for c in name)
    stamp = dt.datetime.now().strftime("%Y%m%d_%H%M%S")
    return REPO / "traces" / "scenarios" / f"{safe}_{stamp}.json"


def _print_dry_run(data, target, layout, bindings):
    print(f"scenario={data['name']}")
    print(cpp_probe.resolution_report(target, layout))
    print(f"question={data.get('question') or '-'}")
    all_steps = data.get("setup_steps", []) + data["steps"]
    print("setup input:")
    for index, step in enumerate(data.get("setup_steps", []), 1):
        print(f"  {index:02d}. {json.dumps(step, sort_keys=True)}")
    print("trigger input:")
    for index, step in enumerate(data["steps"], 1):
        print(f"  {index:02d}. {json.dumps(step, sort_keys=True)}")
    used = sorted({key for step in all_steps
                   for key in ([step.get("key")] if step.get("key") else step.get("keys", []))})
    if used:
        print("bindings=" + ", ".join(
            f"{key}=VK_{bindings[key]:02x}" if key in bindings else f"{key}=UNBOUND"
            for key in used))


def main(argv=None):
    ap = argparse.ArgumentParser(
        description="drive one reproducible melonDS scene and capture runtime evidence")
    ap.add_argument("scenario", help="scenario JSON")
    ap.add_argument("--host", default="127.0.0.1")
    ap.add_argument("--port", type=int, default=3333)
    ap.add_argument("--melon-config", help="melonDS.toml (auto-detected by default)")
    ap.add_argument("--window-title", default="melonDS")
    ap.add_argument("--input-backend", choices=("control", "win32"),
                    default="control",
                    help="input path; control is deterministic and needs the instrumented fork")
    ap.add_argument("--control-port", type=int, default=45987)
    ap.add_argument("--control-token", default=os.getenv("MELONDS_CONTROL_TOKEN"))
    ap.add_argument("--state-root",
                    help="base directory for relative load_state paths")
    ap.add_argument("--extracted", help="ROM extract directory")
    ap.add_argument("--out", help="evidence JSON path")
    ap.add_argument("--dry-run", action="store_true",
                    help="resolve target and validate inputs without connecting")
    ap.add_argument("--input-only", action="store_true",
                    help="run controls without using the GDB stub")
    args = ap.parse_args(argv)

    try:
        data = load_scenario(args.scenario)
        target, layout = resolve_scenario(data, args.extracted)
        bindings = (load_bindings(args.melon_config)
                    if args.input_backend == "win32" else {})
    except (OSError, RuntimeError, ValueError, json.JSONDecodeError) as exc:
        print(f"[!] scenario setup failed: {exc}", file=sys.stderr)
        return 2

    if args.dry_run:
        _print_dry_run(data, target, layout, bindings)
        return 0

    try:
        if args.input_backend == "control":
            driver = ControlMelonInput(
                host=args.host, port=args.control_port,
                token=args.control_token, state_root=args.state_root)
        else:
            driver = Win32MelonInput(
                bindings=bindings, title_contains=args.window_title)
    except (OSError, RuntimeError, ValueError) as exc:
        print(f"[!] input setup failed: {exc}", file=sys.stderr)
        return 2

    if args.input_only:
        try:
            run_steps(driver, data.get("setup_steps", []) + data["steps"],
                      sleep=getattr(driver, "sleep", time.sleep))
        except (OSError, RuntimeError, ValueError) as exc:
            print(f"[!] input script failed: {exc}", file=sys.stderr)
            return 3
        finally:
            if hasattr(driver, "close"):
                driver.close()
        return 0

    capture = data.get("capture", {})
    setup_events = []
    memory_setup_events = []
    residency = {}
    script = InputThread(driver, data["steps"])

    def prepare_setup():
        def announce(message):
            setup_events.append(message)
            print(message)

        run_steps(driver, data.get("setup_steps", []), announce=announce,
                  sleep=getattr(driver, "sleep", time.sleep))
        # Exact control-API stepping returns paused. The GDB listener accepts
        # a socket while paused but the ARM core cannot service its first
        # memory command until emulation is resumed. Setup is complete here;
        # the target-specific trigger has not started yet.
        if hasattr(driver, "resume"):
            driver.resume()

    def prepare_target(cli):
        memory_setup_events.extend(
            apply_memory_setup(cli, data.get("setup_memory", [])))
        for event in memory_setup_events:
            print(f"[*] setup memory: {event['name']} {event['before']} -> "
                  f"{event['after']} at {event['address']:#010x}")
        expected = target["canary"].lower()
        observed = cli.read_mem(target["addr"], len(expected) // 2).hex().lower()
        residency.update({
            "address": target["addr"],
            "expected_canary": expected,
            "observed_canary": observed,
            "matches_target": observed == expected,
        })
        state = "target resident" if observed == expected else "different overlay resident"
        print(f"[*] pre-trigger overlay check: {state} at {target['addr']:#010x} "
              f"(observed {observed})")

    def start_trigger(_cli):
        script.start()
    print(cpp_probe.resolution_report(target, layout))
    print(f"[*] question: {data.get('question') or '-'}")
    print("[*] preparing savestate/input before attaching the GDB client")
    try:
        prepare_setup()
    except (OSError, RuntimeError, ValueError) as exc:
        if hasattr(driver, "close"):
            driver.close()
        print(f"[!] scenario setup input failed: {exc}", file=sys.stderr)
        return 3
    print("[*] connecting; scripted input starts after the target breakpoint is armed")
    accept_case = None
    unique_counts = None
    if capture.get("unique_by"):
        accept_case, unique_counts = unique_observation_filter(
            capture["unique_by"], int(capture.get("max_per_value", 1)))
    try:
        cases, alias_rejects, elapsed = cpp_probe.collect(
            target, layout, args.host, args.port,
            hits=capture.get("hits", 5),
            duration=capture.get("duration", 120.0),
            idle=capture.get("idle", capture.get("duration", 120.0)),
            poll_timeout=capture.get("poll_timeout", 2.0),
            vtable_slots=capture.get("vtable_slots", 12),
            capture_return=capture.get("capture_return", True),
            on_pre_arm=prepare_target,
            on_ready=start_trigger,
            should_abort=lambda: script.error is not None,
            accept_case=accept_case)
    except (OSError, RspError, RuntimeError, TimeoutError, ValueError) as exc:
        print(f"[!] emulator scenario failed: {exc}\n"
              "    Restart melonDS and make this runner its first GDB client.",
              file=sys.stderr)
        return 3
    finally:
        script.stop()
        if hasattr(driver, "close"):
            driver.close()

    evidence = {
        "schema": cpp_probe.SCHEMA,
        "created_at": dt.datetime.now(dt.timezone.utc).isoformat(),
        "question": data.get("question"),
        "target": target,
        "layout": layout,
        "capture": {
            "host": args.host,
            "port": args.port,
            "requested_hits": capture.get("hits", 5),
            "elapsed_seconds": elapsed,
            "capture_return": capture.get("capture_return", True),
            "vtable_slots": capture.get("vtable_slots", 12),
        },
        "automation": {
            "scenario_schema": SCHEMA,
            "scenario_name": data["name"],
            "input_backend": args.input_backend,
            "control_port": (args.control_port
                             if args.input_backend == "control" else None),
            "start_state": data.get("start_state"),
            "setup_steps": data.get("setup_steps", []),
            "setup_events": setup_events,
            "setup_memory": data.get("setup_memory", []),
            "setup_memory_events": memory_setup_events,
            "pretrigger_target": residency,
            "steps": data["steps"],
            "events": script.events,
            "input_error": repr(script.error) if script.error else None,
        },
        "alias_rejects": alias_rejects,
        "unique_observation_counts": dict(unique_counts or {}),
        "cases": cases,
    }
    evidence["summary"] = cpp_probe.summarize(evidence)
    evidence["expectations"] = evaluate_expectations(
        data.get("expect", []), evidence["summary"])
    out = pathlib.Path(args.out) if args.out else _default_output(data["name"])
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(evidence, indent=2) + "\n", encoding="utf-8")
    print()
    print(cpp_probe.render_report(evidence))
    if evidence["expectations"]:
        print("\nScenario assertions:")
        for item in evidence["expectations"]:
            state = "PASS" if item["passed"] else "FAIL"
            print(f"  [{state}] {item['observation']} == {item['value']}: "
                  f"{item['actual_count']} >= {item['min_count']}")
    print(f"\n[=] scenario evidence saved to {out}")
    if script.error:
        print(f"[!] input script error: {script.error}", file=sys.stderr)
        return 5
    if any(not item["passed"] for item in evidence["expectations"]):
        return 6
    return 0 if cases else 4


if __name__ == "__main__":
    sys.exit(main())
