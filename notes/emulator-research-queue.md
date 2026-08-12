# Emulator research queue

## Goal

Turn one runtime-observable question into a reproducible scenario with:

1. an exact savestate and trigger recipe;
2. a ROM-backed breakpoint canary;
3. the relevant register, memory, actor, and overlay observations;
4. a machine-checkable expectation; and
5. a saved positive or negative result.

This queue covers the six cases in `notes/overlay-residency.md` that still need
runtime evidence or call-site reading.  The first is now solved; the remaining
five are ordered by expected time to a useful answer.

## Solved baseline: ARM9 camera spline call

Question: does callsite `0x02008c18` use ov002 or ov006 at the shared address
`0x020effb8` during level gameplay?

Result: **ov002, directly observed.**  The reproducible chain was:

```text
intro script 0x020890a0
  record 0x020890fb: opcode 4, camera command 6
  data_02086d98 PMF -> func_020082a0
  func_020082a0 -> func_02009414 -> func_02008b4c
  callsite 0x02008c18 -> live ov002 bytes at 0x020effb8
```

The initial course-entry trigger was correctly negative because slot 5 had the
saved-game intro bit set.  The working scenario clears bit `0x80` from the
32-bit word at `data_0209caa0[2]` (`0x0209caa8`) after loading the savestate.
The runner recorded `88020300 -> 08020300`, then captured:

- caller: `func_02009414`;
- target: exact ARM9 callsite `0x02008c18`;
- accepted hits: 1, overlay rejects: 0;
- candidate: `ov002:func_ov002_020effb8`.

Reproduce after a fresh melonDS launch:

```powershell
python tools/trace/scenario.py `
  tools/trace/scenarios/bobomb_camera_spline.json
```

Local evidence from the confirming run is
`traces/scenarios/bobomb-camera-spline_20260811_204245.json`.

The coverage scenario also captured 33 distinct BOB spawn IDs while ov002 was
resident: Player, Camera, Warp, RotatingUpDownPlatform, SeesawBob, RollingIronBall,
QuestionBlock, ExclamationSwitch, ShutterBob, Goomba, BobOmb, Stump, SignPost,
Cannon, HealingHeart, InvisibleSecret, OneUpMushroom, CannonHatch, both arrow
signs, BrickBlock, Tree, Coin, StarMarker, RedCoin, PowerStar, WaterBomb,
BobOmbBuddy, KingBobOmb, ChainChomp, ChainChompFence, Minimap, and HUD.

## Next five

### 1. CapEnemy cap-file table: ov002 or ov007

- Unknown: shared data `0x020ff028` is named both
  `ov002:data_ov002_020ff028` and `ov007:data_ov007_020ff028`.
- Trigger: a cap-bearing enemy reaching `CapEnemy::AddCap(unsigned int)`.
- Capture: break at `_ZN8CapEnemy6AddCapEj`, record the selector in `r1`, the
  loaded scene/level overlay, and the bytes at `0x020ff028`.
- Savestate: nearest cap enemy, saved before it initializes or receives a cap.
- Done when: at least one canary-clean AddCap call and one resident-module
  classification are asserted.  Repeat in any ov007 scene if the table is used
  there; this may intentionally have two answers.

### 2. Whomp collision callback at `0x02123804`

- Unknown: `func_ov002_020ec670` can call one of four real functions at the
  same address: ov077 (size `0x8`), ov078 (`0x60`), ov079 (`0x288`), or ov080
  (`MontyMoleRockD0Ev`, `0x54`).
- Trigger: collide with actor ID `0xa4` (Whomp) or `0xa5` (Whomp King); the
  source calls the slot only for those two actor IDs.
- Capture: arm the exact callsite after the target level overlay is resident,
  record the collided actor pointer/ID and classify the four canaries.
- Savestate: one immediately before a Whomp collision in each relevant level.
- Done when: every exercised level maps to a module-qualified target.  A
  per-level mapping is an acceptable result; this likely has no single owner.

### 3. CutsceneObject resource at `0x02113c20`

- Unknown: `CutsceneObject::InitResources()` passes the shared level-slot
  address for object variants `0x1a..0x2d`.
- Trigger: actor ID `0x160` (CutsceneObject) with `this+0x8` in that range.
- Capture: break at `_ZN14CutsceneObject13InitResourcesEv`, read `this+0x8`,
  the loaded level-overlay ID, and the first 8 bytes at `0x02113c20`.
- Savestate: a small catalog of levels whose spawn inventory contains actor
  `0x160`; actor-spawn inventory selects these automatically.
- Done when: each observed object variant is paired with the resident level
  module and resource canary.  Keep a variant-to-level table rather than
  forcing one global name.

### 4. BowserShockwaves resources across three Bowser levels

- Unknown: resource pointers at `0x021115e4` and `0x021115f4` narrow by
  residency to ov044, ov046, or ov048.
- Trigger: actor ID `0x119` (BowserShockwaves) initialization.
- Capture: break at `_ZN16BowserShockwaves13InitResourcesEv`, observe both
  addresses plus the loaded level-overlay ID.
- Savestate: one before the shockwave actor spawns in each Bowser fight.
- Done when: three asserted scenario results map both resource addresses for
  all three fights.

### 5. Identify ov089's cinematic actor and `0x02111b68`

- Unknown: `func_ov089_0213162c` writes through the shared level-slot symbol
  `data_02111b68`; ov089 is used by more than one level, so residency alone did
  not settle it.
- First capture: break at the function entry and join `r0` to the live actor
  list to recover actor ID, concrete vtable, position, and level.
- Second capture: observe the bytes at `0x02111b68` on the state-2 transition
  that writes it, plus the loaded level-overlay ID.
- Savestate: chosen after the first actor-identity capture reveals the scene
  and event.
- Done when: the concrete actor/event is named and each observed level maps the
  shared address to a module-qualified symbol.

## Harness work that unlocks the five

1. **Done:** control-backed `setup_steps` now load and settle a savestate before
   the GDB client attaches; RAM setup and residency checks happen after attach,
   and the target breakpoint is armed only before trigger steps.
2. Add fixed-address typed observations (not only candidate-canary groups) for
   the loaded level-overlay ID and shared resource pointers.
3. Build a savestate catalog containing level, star, actor-spawn inventory,
   loaded overlays, and exact trigger position/action.
4. Make actor-ID names available inside worktrees without silently depending
   on an unlinked `reference/DynamicAllocationDecomp` checkout.
5. Keep `expect` assertions in every scenario so batch runs distinguish
   positive proof, clean negative coverage, wrong-overlay setup, and input
   failure without reading console prose.
