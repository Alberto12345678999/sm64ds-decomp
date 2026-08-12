# tools/trace — emu-trace pipeline

Runtime-trace tooling for the emulator-assisted matching/labeling plan.
Strategy: `notes/emu-trace-plan.md`. Build spec: `notes/emu-trace-build.md`.

Status: **Phase 0 spike** (attach + breakpoint + canary + register/mem dump).

## Files
- `rsp.py` — minimal GDB Remote Serial Protocol client over a TCP socket (no
  gdb dependency). Set/clear breakpoints, read registers/memory, continue.
- `symindex.py` — addr→symbol index from `config/**/symbols.txt` + `nearmiss/db.jsonl`,
  used to resolve a captured `lr` to a caller name.
- `gdb_harness.py` — the Phase-0 spike runner. Breaks at always-resident arm9
  functions and validates the pipeline against ground truth.
- `cpp_probe.py` — question-oriented readable-C++ probe. Resolves a matched or
  unmatched symbol, discovers its class/header fields, captures `this` before
  and after calls, and reports named field changes, values, callers, returns,
  and vtable slots.
- `scenario.py` + `input_win.py` — one-session automation layer. Arms a probe,
  drives configured melonDS controls from a small JSON scenario, and records
  the exact input recipe with the runtime evidence.

## Prerequisites: melonDS GDB stub

1. Install melonDS (Qt frontend — the GDB stub lives there).
2. Emu settings → enable the GDB stub. In `melonDS.ini` the keys are roughly:
   ```
   GdbEnabled=1
   GdbPortARM9=3333
   GdbPortARM7=3334
   JIT_Enable=0          ; REQUIRED — the stub needs the interpreter core
   ```
   (Exact key names vary by melonDS version — confirm in the UI. The two that
   matter: stub ON, JIT OFF.)
3. Load `sm64.nds` and **load a savestate / let the game run past boot** so the
   CPU is actually executing game code (otherwise the arm9 targets never fire).
   melonDS suspends the CPU while a GDB client is attached, then resumes on
   `continue` — that's expected.

DeSmuME fallback: launch with `--arm9gdb=3333`; everything below is identical.

## Run the spike

```
# default: 6 small always-resident arm9 funcs, 20s window
python tools/trace/gdb_harness.py --duration 20

# pick your own targets (must exist in nearmiss/db.jsonl)
python tools/trace/gdb_harness.py --names func_02043288,DMASyncFillTransfer

# write every hit record to JSONL for inspection
python tools/trace/gdb_harness.py --duration 30 --out traces/spike.jsonl

# canary-rejection test: bp an address whose overlay is swapped out (or any
# address you expect NOT to hold the named func) and confirm canary_ok=false
python tools/trace/gdb_harness.py --negative 0x0211640c
```

## What to look for (Phase-0 acceptance gates)

The run prints a summary. Report these back:

1. **Register layout** — the startup line `register packet: N words; pc=... cpsr=...`.
   - `pc` on a breakpoint hit MUST equal the target function's address.
   - Confirm `cpsr` has a sane mode (low byte one of 10/11/12/13/1f) and note
     `cpsr_src` (`word16` = core layout, `last` = legacy-FPA layout). **Write the
     confirmed layout here** once known — it's the classic stub gotcha.
2. **Canary** — `canary clean` count > 0 on resident targets; the `--negative`
   test should log a rejected/unexpected hit (canary_ok=false). Both directions
   must work.
3. **Throughput** — `total hits (X/s)`. **Gate: ≥ 5 hits/s.** Below that after
   capping derefs, the pivot (per the build plan) is a small melonDS fork with
   an in-process addr-set logger instead of stop-the-world breakpoints.

## Confirmed facts (Phase 0 spike, 2026-07-14, melonDS 1.1 windows-x86_64)

**Register packet layout** (from `src/debug/GdbArch.h`, validated live): 39 words.
Indices 0–12 = r0–r12, 13 = sp, 14 = lr, 15 = pc, 16 = cpsr, then banked/spsr
regs. `rsp.py` reads word13/14/15/16 — correct. cpsr src = `word16`.

**Throughput: ~1,500 breakpoint hits/sec** with 206 breakpoints armed on the
title/intro scene (14,998 hits in 10s, all canary-clean). The <5/s kill
criterion is not remotely a concern — stop-the-world breakpoints are plenty fast.

**melonDS 1.1 GDB-stub quirks (these shaped rsp.py — do not regress them):**
1. **Config is per-instance.** Enabling `[Gdb] Enabled=true` alone does NOTHING;
   you must set `[Instance0.Gdb] Enabled=true`. JIT is `[JIT] Enable=false`.
   Config lives in `melonDS.toml` next to the exe.
2. **Mandatory handshake:** on accept the stub blocks in `WaitAckBlocking`
   expecting the CLIENT to send a `+` byte first, then it replies `+`. Without
   that leading `+` it closes the connection on the first packet. `rsp.py`
   `connect()` sends it.
3. **Single session.** The stub services ONE client. You MUST send `D` (detach)
   before disconnecting, or it keeps holding the dead ConnFd and the next
   connection's packets go unanswered (times out). It rebuilds its listen
   socket on each disconnect, so a fresh `connect()` can be briefly refused —
   `rsp.py` retries.
4. **Never send a `0x03` break.** Halting a running target (or breaking while
   stopped) resets/wedges the Windows stub. Not needed anyway: set breakpoints
   while the target runs, and each bp HIT stops it on its own. Teardown = `D`.
5. **A SIGKILL'd client wedges the stub** (dead ConnFd, single session). If runs
   start timing out, restart melonDS. Restarting between trace sessions is
   expected anyway (to cycle savestates).

**Working model (what the collector should do):** launch melonDS with ROM +
savestate → open ONE persistent RSP connection → set all breakpoints while
running → continue → loop {wait_for_stop → read regs/mem → continue} → `D` +
close → kill melonDS. One connection per trace session, detach cleanly.

Launch recipe used:
`Start-Process melonDS.exe -ArgumentList '<rom>'` with the pre-written
`melonDS.toml`; stub binds ~6–8s after boot.

## cpp-probe: answer readable-C++ questions (`cpp_probe.py`)

The raw collector is designed for batches and emits register/memory records.
`cpp_probe.py` is the single-method, human-facing layer for questions that arise
during the C-to-real-C++ conversion:

- Does the proposed method actually receive an object in `r0`?
- Which concrete object/vtable implementations reach it?
- Which reconstructed fields change across the call?
- What values and ranges does a proposed `Fix12i`, timer, flag, or pointer take
  during real gameplay?
- Which callers and vtable slot targets are observed?

For a ready-to-copy contributor or agent assignment that requires a runtime
answer and a verified deliverable, use [`CPP_PROBE_JOB.md`](CPP_PROBE_JOB.md).

First check resolution without occupying melonDS's one GDB session:

```
python tools/trace/cpp_probe.py _ZN5Fader13AdvanceInterpEv --resolve-only
```

This resolves the config symbol to an address plus an eight-byte ROM canary,
demangles `Fader`, reads `include/Fader.h`, and lists every field it can decode.
Unlike the older breakpoint-list path, it works for already-matched functions,
not only records still present in `nearmiss/db.jsonl`. In a linked worktree it
automatically borrows the primary checkout's gitignored `extracted/`; set
`SM64DS_EXTRACTED` (or pass `--extracted`) for a different layout.

Then start melonDS, load a scene/savestate that reaches the method, and ask the
runtime question:

```
python tools/trace/cpp_probe.py _ZN5Fader13AdvanceInterpEv \
  --hits 8 \
  --ask "which Fader fields change while the fade advances?"
```

The default is `--this-reg auto`: the tool checks the source definition's arity
or real method form and enables `this=r0` only when that evidence says this is an
instance method. Mangling alone cannot distinguish a static member from an
instance method; an undecided result leaves object capture disabled until you
explicitly pass `--this-reg r0`. The tool sets the entry breakpoint,
canary-gates every hit against overlay aliasing, snapshots the object, catches
the return at `lr`, re-reads the same object, prints the answer, and saves the
full evidence to `traces/questions/` (gitignored). Re-render an evidence file
without reconnecting:

```
python tools/trace/cpp_probe.py --input traces/questions/Fader_AdvanceInterp.json
```

Useful overrides:

```
# Add a field the header has not named yet, or override its interpretation.
python tools/trace/cpp_probe.py <symbol> --field 0x5c:Vector3:position

# A static/namespace function has no implicit object.
python tools/trace/cpp_probe.py <symbol> --this-reg none

# Large classes are auto-capped at 0x400 bytes; opt in to a wider object window.
python tools/trace/cpp_probe.py <symbol> --object-size 0x900

# Entry-only capture avoids the lr-return pairing on recursion/non-returning code.
python tools/trace/cpp_probe.py <symbol> --no-return
```

Automatic decoders are deliberately narrow: integer widths/signs, pointers,
`Fix12i`, `Vector3`, and `Vector3_16`. Unknown header types are listed instead
of assigned a guessed width; add an explicit `--field` decoder when the width is
known.

### What the answer proves

The saved report is runtime evidence: an observed caller, value, vtable, or
write is real for the captured path. Absence is not proof—the gameplay path may
not have exercised it. Runtime values also cannot prove byte-unobservable C++
properties such as signedness when no executed operation distinguishes it. Keep
the normal gates: header-wide affected-source checks, byte matching, strict
relocations, and the full ROM build. For retail-vs-recompiled behavioral
equivalence on identical inputs, continue to use `behavior.py` plus
`behavior_diff.py`; `cpp_probe.py` answers the interpretation question for one
runtime.

### Confirmed live probe (2026-08-10, melonDS 1.1)

`Fader::AdvanceInterp` was captured for 900 entry/return pairs with a ROM-clean
canary and no overlay rejects. The idle title-screen object at `0x02189b68`
used vtable `data_0208ea6c`, arrived from `func_02018efc`, held
`currInterp=0`, `speed=-1.0`, and returned true without writing the object.
That proves the observed endpoint path, not that active fades never write it.

The session also confirmed two reporting rules. A vtable entry is an exact code
pointer and must not be resolved like a link-register return address; doing so
falsely added the preceding function at adjacent boundaries. Also, class names
seen on virtual methods are reported only as **method-owner hints**. They do not
rename a generic `data_*` vtable or prove the object's concrete class.

## scenario runner: drive a reproducible question (`scenario.py`)

`scenario.py` is the first automation layer above `cpp_probe.py`.  A scenario
combines one target/question with a short sequence of configured DS controls.
The runner arms the target breakpoint first, then drives the instrumented
melonDS localhost control API and finally saves the normal question evidence
plus the exact input recipe. Input and capture stay in one process because the
GDB stub still exposes only one usable debugger client session. The control API
is a separate socket, so it can supply deterministic input and frame stepping
without competing for that session or requiring window focus.

Input failures abort the capture on its next short debugger poll instead of
leaving a broken scenario waiting for the full capture duration.

Optional `setup_steps` run before the trigger steps.  After setup (normally a
savestate load), the runner reads the target's live canary through the same GDB
session and records whether the requested overlay is actually resident.  This
makes a no-hit result distinguishable from a wrong-overlay setup.

Optional `setup_memory` entries make small, explicit 1/2/4-byte RAM changes
after the savestate load.  Each entry supports `value`, `set_bits`, or
`clear_bits`; the runner records the before/after bytes and reads the value back
before continuing.  Use this for a known cutscene or event gate, not to invent
the behavior being tested.

For ambiguous overlay calls, `target` may instead be an exact always-resident
ARM9 address object.  An `observe` list resolves candidate symbols that share an
address and reads that address on every callsite hit, reporting which candidate
canary was live.  This avoids depending on a breakpoint inside an overlay that
is not resident during scenario setup.

`observe_args` reads a typed value at `register + offset` on each hit, while
`observe_registers` records a register value directly.  `capture.unique_by`
can retain only a bounded number of cases per observation value, which makes a
dispatcher or actor-spawn inventory useful without storing every repeated
frame.  An `expect` list turns observation counts into saved, machine-checkable
PASS/FAIL assertions; an unmet assertion exits with status 6.

The included pilot answers the camera-spline ambiguity from the proven quick
slot state `sm64.ml5` at Bob-omb Battlefield's `TOUCH ME` screen. Build and
start the control fork first (the server remains localhost-only):

```powershell
$env:MELONDS_CONTROL_TOKEN = 'sm64-research'
C:\tmp\melonds-ai-controller\tools\start_control.ps1 `
  -Rom C:\Users\andre\source\tangosdev\sm64ds-decomp\sm64.nds
```

Then make the scenario runner the first GDB client and provide the directory
containing the relative savestate path:

```powershell
python tools/trace/scenario.py `
  tools/trace/scenarios/bobomb_camera_spline.json `
  --dry-run

python tools/trace/scenario.py `
  tools/trace/scenarios/bobomb_camera_spline.json `
  --state-root C:\Users\andre\source\tangosdev\sm64ds-decomp
```

The manifest loads the state directly, clears the exact saved-game bit that
suppresses the first-level intro, touches Yoshi, and captures one canary-clean
hit at the original ARM9 callsite. Scenario steps support `load_state`,
`focus` (a socket ping under this backend), `wait`, `tap`, `hold`, and `touch`.
`wait`/`tap`/`hold` may specify exact `frames`; touch coordinates are normalized
to the 256x192 DS touch screen and are independent of window layout. Use
`--input-backend win32` only as a compatibility fallback for an unmodified
melonDS build. `--input-only` tests controls without occupying the GDB stub.
Scenario evidence is written under `traces/scenarios/` (gitignored).

Confirmed live on 2026-08-11: `bobomb_intro_camera_commands.json` observed
`ProcessKuppaScript` dispatch message `0x020890fb` as opcode 4, camera command
6.  The command-6 PMF is `func_020082a0`; it reached callsite `0x02008c18` from
`func_02009414`, where the shared `0x020effb8` bytes matched
`ov002:func_ov002_020effb8`.  The direct evidence file was
`traces/scenarios/bobomb-camera-spline_20260811_204245.json`.

The control-backend replay was independently verified the same day with direct
`sm64.ml5` loading and exact frame steps; its passing evidence is
`traces/scenarios/bobomb-camera-spline_20260811_222253.json`. It required no
foreground window, Win32 key event, or manual intervention.

`bobomb_actor_spawn_inventory.json` is the coverage companion.  The same
automated course entry retained 33 distinct actor IDs, and every spawn observed
ov002 in the shared overlay slot.  It is a useful first check that a scenario
really crossed into level loading before debugging a darker target.

This is intentionally a deterministic scenario runner, not yet a general game
solver.  The next layer should reuse `actors.py`'s player/world-position reads
for waypoint steering and stuck detection, then choose scenarios/savestates
from the overlay-residency backlog.

## actorcam: live actor-list heartbeat (`actors.py`)

Human-friendly runtime naming tool: while YOU play in melonDS, it walks the
game's global Actor list every snapshot and prints what is alive - actor ID
joined to the community `ActorList.h` name, vtable, uniqueID, param, world
position - and diffs snapshots so "what spawned/despawned when X happened" is
one keypress. Snapshots append to `traces/actors/session_*.jsonl` with your
event labels for later vtable->name joining.

Setup (once): `melonDS.toml` needs `[Gdb] Enabled=true`, `[Gdb.ARM9]
Port=3333 BreakOnStartup=true`, `[JIT] Enable=false`; clone
`reference/DynamicAllocationDecomp` for actor-ID names.

Use:
```
1. start melonDS with sm64.nds        (game waits, halted, for the client)
2. python tools/trace/actors.py       (attaches, releases the boot, prompts)
3. play; press Enter to snapshot, or type "star exploded" + Enter to tag one
```

melonDS 1.1 stub facts this tool obeys (learned the hard way):
- one client per emulator launch; if attach probes time out -> restart melonDS
- do **not** use `Test-NetConnection`, telnet, or a raw socket as a port check;
  that consumes the one session without sending RSP detach and wedges the stub
- memory reads work fine while the game RUNS; `?` only answers when halted
- with BreakOnStartup the game powers on halted; the tool auto-continues
- every reply must be ACKed - only talk to the stub through `rsp.py`

Addresses are EU (this repo's ROM): actor list head `0x0209b468` (node
embedded at actor+0x50), `LOADED_LEVEL_OVL_ID 0x02092130`; layouts credited to
SplattyDS/DynamicAllocationDecomp (see CREDITS.md), vtable slot semantics
validated in `tools/actor_names.py`.
