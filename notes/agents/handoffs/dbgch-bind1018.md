# Handoff: dbgch-bind1018

This document describes this commit. It is a WIP checkpoint, not a buildable
or independently verified integration candidate.

## Identity and scope

- Related collision-interface issue: https://github.com/tangosdev/sm64ds-decomp/issues/3854
- Task/stage: `dbgch-bind1018` / `reconstruct`; producer session
  `codex-dbgch-producer1018`, Codex. Branch: `cpp/dbgch-bind1018`.
- Source base and workflow: `3d76ff61c15e9e00d6d9ea317f4400aa1649764b`.
- Active independent source-review policy:
  `18af52b49b9fb5663d417bdfa86109b7b157aaa3`.
- Requested scope: reconstruct arm9 `0x020353b0..0x020353d4` as
  `dBgCh::SetActor(dActor_c*)`, and name sphere helpers
  `0x02037a6c..0x02037b1c` and `0x02037b1c..0x02037b5c`.

## Evidence and implementation

`SetActor` writes the existing `mOwner` and `mOwnerUniqueID` fields. The actor's
ID is `fBase_c::uniqueID` at offset 4. A null actor writes null and -1;
`func_02035354` compares the saved pointer and ID to exclude self-colliders.
Ground, line, and sphere setup now call the inherited member; the unused
declaration in the registry-query source is removed.

`ResetDisplacement` clears `disp` plus both accumulated push-out extrema.
It is narrower than `func_02037b5c`, which also resets hit flags, records, and
the floor normal. `ExpandPushOutBounds` merges supplied per-axis extrema.
The ITCM KCL scan computes depth-scaled surface normals, retains their extrema,
and passes those to this helper. The moving-collider variants rescale the local
query's extrema before merging them. `func_02037a38` sums min and max into the
displacement consumed by actor movement. These are push-out bounds, not
broad-phase spatial bounds; the caller comments now say so.

All three names are inferred from behavior, not recovered Nintendo identifiers.
The compiler's `mangle.py` output established their linker spellings.
`srcpath.new_path_for` selected the standalone SetActor source. The existing
`dBgCh` manifest owns a different text range; this change does not claim an
original TU boundary or broaden its range. The sphere manifest retains its
existing ranges and updates only the two member names. Layout, lifecycle,
vtable/RTTI, and unrelated ABI bridges are unchanged.

## Current proof and limits

- `linkcheck.py` on each of the three functions, with explicit arm9 address
  and size: all `VERIFIED`, no diffs, `blind: 0`; 276 bytes total. Local reports:
  `build/set-actor-link.json`, `build/reset-displacement-link.json`, and
  `build/expand-bounds-link.json`.
- A separate read-only agent reviewed the source diff and caller semantics;
  no source correction requested. This is not formal exact-commit acceptance.
- `affected_src.py include/dBgCh.h include/dBgCh_SphCrr.h --json` identified
  194 consumers before adding the new member source. Recompute the final closure.
- `port_refcheck.py`: 247 references checked, all resolve.
- `check_decl_agreement.py --changed` against the pinned base: no new local
  redeclarations or declaration disagreements. Existing disagreements remain.
- The whole-tree eligibility baseline was stopped before source edits because
  it recompiles consolidated TUs per function; no completed baseline result is
  claimed. Final production coverage and affected-consumer verification remain
  required.
- Full-ROM build and caller relocation proof have NOT run on this WIP.

## Blocker and exact next action

The live task `issue2410-sound-playsub1015`, owned by
`codex-mky-finish-producer1015`, reserves `config/arm9/symbols.txt`,
`symbols/actor_renames.tsv`, `function-authors.json`, and `attribution.json`.
Its reservation and source work have not been changed. The current task
successfully reserved its nonconflicting source/header/delinks/manifest scope.

The user has been asked for an explicit exception allowing only these three
collision functions' metadata rows in this isolated branch. No answer has yet
been received. The complete unapplied patch is preserved locally at
`build/dbgch-shared-metadata.patch`; `git apply --check` passes. It renames the
three configured symbols, appends three inferred-name lineage rows, updates
three author-record names and two source attribution keys, and preserves every
author. Until applied, symbol configuration still names the old functions, so
this checkpoint must not be offered for integration.

Next owner: this task's producer. After an explicit exception or an authorized
owner handoff, apply the narrow metadata patch, verify its scope, run affected
consumer relocation checks and `rombuild.py -j16 --no-rom`, then static gates.
Update this handoff to reflect actual results, commit the candidate, and publish
its immutable SHA to the queue's independent `verify` stage. The reviewer is
the separate `collision_review` agent, using its own wired worktree. No PR or
merge is claimed. The wider collision classes remain partially reconstructed.
