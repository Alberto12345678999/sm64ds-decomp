# Minigame readability passes: handoff (2026-10-15)

Branch `mg/readability-passes`, based on origin/main `bbdf1582a3`.

Goal (the user's): three passes over the minigame classes for human-readable code
that still byte-matches. Rename with confidence; otherwise record the guess and a
plan to confirm it by playing under melonDS and the GDB stub.

## Status

| Pass | Scope | State |
|---|---|---|
| 1 Names | every unnamed function, virtual, base field and global in ov004/ov005/ov006 | **done** |
| 2 Shape | structural rewrites, each proven by object compare | **done** except the SharedState enum (needs pass 3) |
| 3 Review and runtime | top-to-bottom read; runtime confirmation of the medium/low names | **plan written, not run** |

**Pass 1, as committed:**
- **Scene virtuals.** `dScMgBase_c` slots 18-35 carried `dActor_c` names copied by slot index (`OnAimedAtWithEgg` and the rest). All 18 are renamed from their bodies on the base and every override in the 33-class family. The investigation into where those names came from is recorded in names.md.
- **Unnamed helpers.** Of the 758 in the three overlays (174 ov004 + 17 ov005 + 567 ov006), 753 are named. Five stay unnamed for lack of evidence: ov004 `func_ov004_020b67e4` (empty), ov006 `func_ov006_020ca840`, `dScMgBomroom_c::func_ov006_020d8c88`, `func_ov006_020fea70` and `dScMgTeresa_c::func_ov006_0211cc90`.
- **Base fields.** Eighteen `dScMgBase_c` fields are renamed. The compiler located every use, so same-named fields of other structs were left alone.
- **Globals.** The minigame globals are renamed: `gMgScene`, `gMgMenuRow`, `gMgSaveDirty`, the banner, coin and fx pools.
- **Member-pointer records.** The 630 `{fn, adj}` records are now `pmf_<target>`.

**Pass 2 so far** (details and measured negatives in themes.md, themes 1, 7 and 16):
- **`gMgScene`.** It is declared `dScMgBase_c *`, its casts are dropped, and its `char *` aliases and local externs are retired where the code stays identical.
- **Base fields.** Raw base-field reads through `this` aliases and the scene pointer became members. `+0x4650` is named `mTopRecord`.
- **`dMgPsOpt_c`.** `Open`/`Close`/`Update`/`Draw`/`IsIdle` are real members.
- **Teresa.** `SmallBoo mBoos[16]` is typed at 0x4660 and 13 Boo handlers read it by field. Pachinko's mFx/mFlyer/mTarget/mBg are typed (0x5958..0x5c10), with four readers converted. Teresa's mExclaims/mFoundMarks/mRisingIcons (0x48a0..0x4ba0) and the round counters at 0x4c21..0x4c26 are typed too. Teresa 0x4ba0..0x4be8 is now mReveal[1] + mMarker + the big Boo; the supposed overlap was a view starting 0xc bytes into the reveal record. Pachinko 0x5418..0x5958 is never accessed by any reconstructed function, so it stays padding with a note.
- **Not done.** The 13 capped score bumps stay spelled out, because a header inline renumbers the pinned labels.
- **Compare.** The object compare must match the compiler-local `@N`/`$N` names exactly. The manifests pin them.

**Evidence:**
- [notes/minigames/names.md](../../minigames/names.md): every renamed name with its evidence and confidence.
- [notes/minigames/runtime-checks.md](../../minigames/runtime-checks.md): the breakpoint plan.

## Proof (every commit)

**Per commit:**
- All 45 minigame TUs (`config/tu_manifest.d/ov004/`, `config/tu_manifest.d/ov005/` and `config/tu_manifest.d/ov006/` with `src/minigames/` sources) were compiled with `tools/tubuild.py compile`.
- Each object was compared to the pre-pass baseline, either byte for byte or by a semantic ELF compare: every section's bytes, every relocation's offset/type/target and the symbol table, with the recorded rename map applied. Every commit came out identical.

**Gates:** `tools/port_refcheck.py`, `tools/check_decl_agreement.py --changed origin/main`
and `tools/check_rename_ledger.py` pass at HEAD. Lineage rows for the renamed mangled
members are appended to `symbols/actor_renames.tsv`.

**Pending at handoff:** `tools/rombuild.py -j16 --no-rom` (started at handoff) and
`tools/prepush_linkcheck.py --range origin/main..HEAD`. The link check was started
early on and had verified about 2,260 functions across 219 header consumers with no
failure; its WARN lines are pre-existing BLIND sinit/dtor notes outside the
minigames. The `validate` CI on the PR is the authority.

## How the renames were made (to continue the work)

The helper scripts are not in the PR (tooling goes in its own PR). A local copy, with
the baseline objects, is in `build/mgnames-tools/` (gitignored):
- `mgsnap.py snap|cmp <dir> [filter]`: compile the minigame TUs and compare them to a baseline. `objsem.py` is the semantic compare, applying `renames.json` and `methods.json`.
- `mgrename.py symbols <map>`: in-place symbol renames across symbols.txt, the manifests, attribution, function-authors, baselines and `src/` + `include/`. Retired `src/.../func_x.c` paths keep their old spelling.
- `mgrename.py methods <map>` does the same for method names scoped to `dScM*` classes.
- `memren.py`: turns a `{func_addr: Name}` map into member-aware mangled renames.
- `fieldren.py`: the compile-guided member rename.
- `ledger_fix.py`: appends lineage rows for whatever `check_rename_ledger` reports.
- `pmfmap.py` / `gameprep.py` / `fsum.py` / `peek.py`: resolve state tables through relocs and summarize helpers.
- `trykeep.py <rules> <files>`: the Pass 2 harness. It applies a rewrite, compiles, and keeps the rewrite only if the object is identical.

## Next steps

1. **Pass 2 (shape), suggested order.** Each step is measured with `trykeep.py`, and anything that changes bytes goes into themes.md as a measured negative.
   - A `SharedState` enum for `Mg_SetSharedState` arguments, once runtime-checks.md has named the states.
   - The handlers left on offsets (Teresa StepBoo, CountRubbedTiles, Boo_State7, Reveal_State1/4, ResetRound; Pachinko Fx_Spawn, Bg_State0/1/3, Bg_Start, Flyer_State0/2/3/4) measured different typed; retry only with a new spelling idea, one function at a time with `tryrepl.py`.
2. **Pass 3.** Run runtime-checks.md in melonDS and fold the answers into names.md as renames. Then do the read-through for comment drift.

There is also one unrelated defect, found while investigating the transplanted
names: ov064 `symbols.txt:111-112` files two `daObjFl_Puzzle_c` vtable slots (32 and
34) under `daWater_Hakidasi_c`.
