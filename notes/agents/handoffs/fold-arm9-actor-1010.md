# fold/arm9-actor-1010 -- arm9/Actor promotion (dActor_c)

## Target

`arm9/Actor` -- the `dActor_c` translation unit, `0x0200f658..0x02011654`,
97 functions. A link-verified staged source already sat at
`src_tu/actors/Actor.cpp` (the pilot TU from
`notes/tu-reconstruction-pilot-report.md`); this run promoted it to
`src/actors/dActor_c.cpp` and absorbed the 97 legacy per-symbol shards.

Engine target -- allowed under the current sweep (Player remains
excluded). Nothing else claims it: no live worktree, branch, or open PR.

## What landed

- `src/actors/dActor_c.cpp`: the staged TU promoted in place, deslopped
  per current conventions -- `dActor_c::Spawn(...)` call sites now use the
  static member spelling instead of a local `extern "C"` alias; the three
  `dBgCh_LinPad`/`RaycastGroundPod` POD dodge declarations carry
  `local extern:` reasons; `// @symbol <mangled>` markers on all 97
  definitions so the converted ratchet scores members, not the whole file.
- Readability ports recovered from the retired shards (they were built
  from a newer snapshot than the staged file): `BumpedUnderneathByPlayer`
  uses `Player` members, `HorzAngleToCPlayer`/`HorzAngleToFPlayer` use
  named position fields, and `DetectRaycastClsn` takes the real
  `dBgCh_Lin` member form (ctor/dtor are out-of-line, so the member
  spelling emits identical calls) -- all re-verified byte-exact.
- Config: `config/arm9/delinks.txt` consolidated the 97 shard blocks into
  the TU span; `config/tu_manifest.d/arm9/Actor.json` records the promoted
  source, the `_ZN7Vector3D1Ev` `deadstrip-duplicate` policy
  (canonical home arm9:0x020072c0), and the verify results;
  `attribution.json` gained 97 `path#symbol` overrides (tangosdev,
  matching shard credit); `port/slice_gate9.txt` and three live comments
  (`include/daHanachan_c.h`, `src/_ZN13daObjSwdoor_cD1Ev.cpp`,
  `src/game/actors/d_a_sound_obj.cpp`, `src/game/actors/daObjPushblock_c.cpp`)
  repointed from retired shard paths to the promoted file.
- `config/converted-baseline.json`: 56 banked member identities migrated
  to `src/actors/dActor_c.cpp#symbol` keys; five members moved to
  `converted-backslide-exceptions.jsonl` with reasons (see below).
- `config/decl-agreement-baseline.json`: 102 rows banked -- every
  declaration another file (or this file's own reconciled externs) makes
  that disagrees with the moved definitions, e.g. `decl_Actor.h`'s stub
  `int` prototypes for `LandingDust`/`FarthestPlayer`/`FindEgg`, sibling
  callers' loose `Spawn` spellings, and the local `func_02037dc4`
  `Vector3 * (SurfaceInfo *)` decl vs its stub definition.

## Deliberate exceptions (backslide rows)

- `_ZN8dActor_cD0Ev`/`D1Ev`/`D2Ev` keep `extern "C"` bodies:
  `~dActor_c` is declared first in the header so it is the key function;
  a real method definition would emit `_ZTV8dActor_c` locally and collide
  with the copy the module's gap object supplies from ROM.
- `_ZN8Vector3sD1Ev` spells its mangled symbol directly: the shard's
  `Vector3s_ForceDestructor` scaffold emits 0x50 of unlicensed `.text`
  inside the licensed span under a merged TU.
- `_ZN8dActor_c22UpdatePosWithOnlySpeedEP5dCc_c` keeps `unk_0a4`/`unk_0ac`:
  `notes/actor-core-provenance.md` records those fields as deliberately
  unnamed -- existence proved, meaning not.

## Verification

- `tools/tubuild.py verify arm9/Actor`: 97/97 MATCH, objisolate clean,
  reloc-destinations clean, emission order ROM-ascending,
  `_ZN7Vector3D1Ev` deadstrips exactly.
- `check_decl_agreement --changed origin/main`: no new disagreements.
- `tiers_ratchet --check`: PASS (baseline 3103, current 3467;
  +364 gained, not banked).
- `check_src_tu_compiles`: 347/347.
- `queue_audit --check-promoted`, `port_refcheck`,
  `check_dead_references`, attribution check: clean.
- `dsd check symbols` reports the same nine pre-existing ARM9/ITCM errors
  as the baseline control (overlay_100/102, data_020ad524/60, ITCM
  0x01ff98f4..0x01ff9e2c); nothing new.

## Known environmental note

This machine's `extracted/` inputs produce whole-ROM sha256 `ddab9300...`
while the admitted intact proofs record `d1506e90...`. The main checkout's
baseline produces the same `ddab9300` with the identical
`moduleSetSha256` (`f9852ffaf80ef196...`) and `romInputsSha256`
(`2d36439e...`) -- so the difference is outside compared module bytes and
predates this change. `rombuild`'s strict intact-TU control needs either
the admitted sha or a same-worker `build/sm64ds.nds` oracle; CI has both.
