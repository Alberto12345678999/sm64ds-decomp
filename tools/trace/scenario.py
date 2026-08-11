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
import datetime as dt
import json
import pathlib
import sys
import threading

TRACE_DIR = pathlib.Path(__file__).resolve().parent
TOOLS_DIR = TRACE_DIR.parent
REPO = TOOLS_DIR.parent
sys.path.insert(0, str(TRACE_DIR))
sys.path.insert(0, str(TOOLS_DIR))

import bplist  # noqa: E402
import cpp_probe  # noqa: E402
from input_win import Win32MelonInput, load_bindings, run_steps  # noqa: E402
from rsp import RspError  # noqa: E402


SCHEMA = "sm64ds-emulator-scenario-v1"


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
    return target, layout


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
        bindings = load_bindings(args.melon_config)
    except (OSError, RuntimeError, ValueError, json.JSONDecodeError) as exc:
        print(f"[!] scenario setup failed: {exc}", file=sys.stderr)
        return 2

    if args.dry_run:
        _print_dry_run(data, target, layout, bindings)
        return 0

    try:
        driver = Win32MelonInput(
            bindings=bindings, title_contains=args.window_title)
    except (OSError, RuntimeError, ValueError) as exc:
        print(f"[!] input setup failed: {exc}", file=sys.stderr)
        return 2

    if args.input_only:
        try:
            run_steps(driver, data.get("setup_steps", []) + data["steps"])
        except (OSError, RuntimeError, ValueError) as exc:
            print(f"[!] input script failed: {exc}", file=sys.stderr)
            return 3
        return 0

    capture = data.get("capture", {})
    setup_events = []
    residency = {}
    script = InputThread(driver, data["steps"])

    def prepare_and_start(cli):
        def announce(message):
            setup_events.append(message)
            print(message)

        run_steps(driver, data.get("setup_steps", []), announce=announce)
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
        script.start()
    print(cpp_probe.resolution_report(target, layout))
    print(f"[*] question: {data.get('question') or '-'}")
    print("[*] connecting; scripted input starts after the target breakpoint is armed")
    try:
        cases, alias_rejects, elapsed = cpp_probe.collect(
            target, layout, args.host, args.port,
            hits=capture.get("hits", 5),
            duration=capture.get("duration", 120.0),
            idle=capture.get("idle", capture.get("duration", 120.0)),
            poll_timeout=capture.get("poll_timeout", 2.0),
            vtable_slots=capture.get("vtable_slots", 12),
            capture_return=capture.get("capture_return", True),
            on_ready=prepare_and_start,
            should_abort=lambda: script.error is not None)
    except (OSError, RspError, RuntimeError, TimeoutError, ValueError) as exc:
        print(f"[!] emulator scenario failed: {exc}\n"
              "    Restart melonDS and make this runner its first GDB client.",
              file=sys.stderr)
        return 3
    finally:
        script.stop()

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
            "start_state": data.get("start_state"),
            "setup_steps": data.get("setup_steps", []),
            "setup_events": setup_events,
            "pretrigger_target": residency,
            "steps": data["steps"],
            "events": script.events,
            "input_error": repr(script.error) if script.error else None,
        },
        "alias_rejects": alias_rejects,
        "cases": cases,
    }
    evidence["summary"] = cpp_probe.summarize(evidence)
    out = pathlib.Path(args.out) if args.out else _default_output(data["name"])
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(evidence, indent=2) + "\n", encoding="utf-8")
    print()
    print(cpp_probe.render_report(evidence))
    print(f"\n[=] scenario evidence saved to {out}")
    if script.error:
        print(f"[!] input script error: {script.error}", file=sys.stderr)
        return 5
    return 0 if cases else 4


if __name__ == "__main__":
    sys.exit(main())
