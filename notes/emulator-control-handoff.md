# Emulator control for decomp research

## What this is

We have an instrumented melonDS fork that exposes an opt-in JSON control API on
`127.0.0.1`. A research script can now load a savestate, hold semantic DS
buttons, touch exact DS-screen coordinates, advance an exact number of frames,
and read or write ARM9 memory without focusing the emulator window or sending
Windows key events.

The decomp repo's scenario runner uses that same control API for melonDS's
in-process ARM9 breakpoints. It can arm a ROM-backed breakpoint, execute a
repeatable gameplay trigger, capture registers/objects/live overlay bytes, and
turn the result into a saved PASS/FAIL assertion without the GDB stub's
single-session timeout failure.

This does **not** replace matching or relocation verification. It supplies
runtime evidence when static reading leaves questions such as:

- which overlay owns a shared runtime address in this scene;
- which caller reaches an unnamed function;
- which actor/class is passed as `this`;
- which command, variant, resource, or state value is live at a call;
- what spawned or changed after a reproducible game event.

## Current implementation

On the current workstation:

| Part | Location | Branch / commit |
|---|---|---|
| Instrumented melonDS 1.1 fork | `C:\tmp\melonds-ai-controller` | `ai/control-api` |
| Decomp scenario tooling | `C:\tmp\sm64ds-emulator-cpp-query` | `tools/emulator-cpp-query` |
| Research backlog | `notes/emulator-research-queue.md` | five concrete questions |
| Scenario manifests | `tools/trace/scenarios/` | reusable JSON jobs |
| Runtime evidence | `traces/scenarios/` | local and gitignored |

These commits are currently local. Someone working on another machine needs the
fork/branches copied or published before the paths below will exist.

## Start it

The fork is built with melonDS's documented MSYS2 UCRT64 toolchain. Its local
build is `C:\tmp\melonds-ai-controller\build\ai-ucrt64\melonDS.exe`.

Keep JIT disabled; managed ARM9 breakpoints run in the interpreter. The normal
workflow does not require the GDB stub to be enabled.

Start the controller-enabled emulator:

```powershell
$env:MELONDS_CONTROL_TOKEN = 'sm64-research'

C:\tmp\melonds-ai-controller\tools\start_control.ps1 `
  -Rom C:\Users\andre\source\tangosdev\sm64ds-decomp\sm64.nds
```

Check the API before doing research:

```powershell
python C:\tmp\melonds-ai-controller\tools\control_client.py `
  --token sm64-research status
```

The default control port is `45987`. The server is disabled unless
`--control-port` is supplied and binds only to localhost. Legacy emulators can
still use `--breakpoint-backend gdb --port 3333` explicitly.

## Run the proven example

With the controller-enabled emulator running, run:

```powershell
cd C:\tmp\sm64ds-emulator-cpp-query
$env:MELONDS_CONTROL_TOKEN = 'sm64-research'

python tools\trace\scenario.py `
  tools\trace\scenarios\bobomb_camera_spline.json `
  --state-root C:\Users\andre\source\tangosdev\sm64ds-decomp
```

The scenario directly loads `sm64.ml5`, advances setup frames, verifies three
RAM setup writes, arms callsite `0x02008c18`, touches Yoshi, and advances the
intro. The confirmed result is:

```text
caller: func_02009414
shared address 0x020effb8: ov002:func_ov002_020effb8
assertion: PASS (1 observed hit, 0 overlay rejects)
```

The passing evidence from development is
`traces/scenarios/bobomb-camera-spline_20260811_222253.json`.

## Turn another question into a job

1. Pick one item from `notes/emulator-research-queue.md` and coordinate so two
   people do not collect the same evidence.
2. State one narrow question and what observation would answer it.
3. Find or create a savestate immediately before the trigger.
4. Add a JSON manifest under `tools/trace/scenarios/` with a ROM-backed target,
   setup steps, exact frame input, observations, and at least one `expect`.
5. Run `scenario.py --dry-run`, then restart melonDS and run the live scenario.
6. Keep the evidence path, observed callers/registers/canaries, and assertion
   result with the research note. A clean negative result is useful when its
   scene and trigger coverage are explicit.
7. Use the result to guide names, ownership, call-graph reading, or C++
   hypotheses. Do not treat runtime behavior alone as a byte match and do not
   put an unverified implementation in `src/`.

A minimal input portion looks like:

```json
{
  "setup_steps": [
    {"action": "load_state", "path": "before_trigger.mln"},
    {"action": "wait", "frames": 60}
  ],
  "steps": [
    {"action": "hold", "keys": ["dpad_up", "button_a"], "frames": 1},
    {"action": "wait", "frames": 300}
  ],
  "expect": [
    {"observation": "resident overlay", "value": "ovNNN:symbol", "min_count": 1}
  ]
}
```

Supported control primitives include `load_state`, `wait`, `tap`, `hold`, and
`touch`. Wait/tap/hold can use exact `frames`; touch coordinates are normalized
to the DS touch screen. Scenarios can additionally use `setup_memory`,
`observe`, `observe_args`, `observe_registers`, and bounded `unique_by`
captures. See `tools/trace/README.md` and the existing manifests for the full
schema.

## Copy-paste assignment

```text
Use notes/emulator-control-handoff.md and notes/emulator-research-queue.md.
Work on the tools/emulator-cpp-query branch; do not add speculative files to
src/. Pick one unclaimed runtime question from the queue and turn it into a
reproducible tools/trace/scenarios JSON job. Use the controller-enabled melonDS
fork for direct savestate loading, exact-frame DS input, and ARM9 memory access;
use its protocol-2 managed breakpoints for register capture. Include a
ROM-backed canary, an explicit expect assertion, tests for any harness change,
and report the exact command plus saved evidence path. A covered negative
result is valid; an unexplained timeout is not.
```

## Near-term direction

The current API is a deterministic robot body, not yet a general game-playing
agent. The next useful layer is a savestate catalog plus actor/player position,
collision-aware waypoint steering, stuck detection, and `run_until` conditions.
Those additions should remain reusable primitives; the research scenario should
still state the question, trigger, coverage, and success condition explicitly.
