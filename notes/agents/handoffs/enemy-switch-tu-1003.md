# Handoff: enemy-switch-tu-1003

This document describes this commit. Local-only WIP; bookkeeping is not yet accepted.

## Identity and resumption

- Producer/integration owner: codex-enemy-switch-1003 / codex-tu-reduce-1002.
- Harness: Codex. Branch: tu/enemy-switch-1003.
- Source and workflow input: ef4a02ce0f5d0e0447e992eeb89f706f11a0c7af.
- Independent source reviewer: scene_review; final immutable review pending.
- Worktree: C:/tmp/sm64ds-enemy-switch-tu-1003; private evidence under build/.
- No PR, push, merge, issue message or queue source publication is authorized.

## Production change and evidence

Twelve existing functions at ov002:0x020f15fc..0x020f198c now compile from
src/game/actors/d_a_e_switch.cpp. The twelve per-function files and shadow copy
are retired: eleven fewer src inputs, or thirty-one fewer including the Scene
input commit. The interleaved methods and neighboring actor boundaries support
a combined TU; this is medium-confidence inference, not an original object map.

The cartridge RTTI names daECreate_c (string 0x0210b304, typeinfo 0x0210b2f8)
and daESwitch_c (string 0x0210b314, typeinfo 0x0210b2ec). Both inherit dActor_c.
Their vtable address points are 0x0210b364 and 0x0210b3e8. Historical descriptive
names remain compatibility typedefs; existing imported vtable aliases remain.
Factory/profile identifiers and field names are reconstructed, not recovered.

Both factories now use new, both destructors are inline empty native definitions,
and behavior uses named fields and native Event/model/collider/lifecycle calls.
Header order gives the observed destructor group order. The compiler emits all
twelve functions in ascending ROM order. Twelve exact metadata policies preserve
existing data ownership; no metadata range is newly enrolled.

One documented ABI bridge calls the existing raw-word dCcAc_c::Init definition.
Native Fix12<int> aggregate initialization, explicit .val assignment, and an
inline conversion helper each produced 0xc4 bytes instead of the ROM's 0xac.
Their sources are retained in build/enemy-switch-native-*-failed.cpp. The retained
bridge agrees with the current definition and eliminates raw object offsets.
The spawn call still views the base class's scalar coordinate fields as vectors;
func_ov102_0214ad14 remains unresolved. Reconstruction is therefore partial.

## Verification and limits

- Production rombuild.py -j16: exit 0, 106/106 modules exact, 11255/11255 source
  functions match, 32/32 source-owned data claims, no new dsd symbol errors.
  Final 16777216-byte ROM SHA256:
  d1506e90efae5e2d2cf119926a4ac2a291bd5ca78349d09d5024e1a918c478e8.
  Log: build/enemy-switch-rombuild.log. Stock control still has known symbol
  errors; global advisory metadata contains three unrelated differing records.
- tubuild verify: 12/12 MATCH, isolation and relocation destinations clean,
  complete output accounting and ascending emission order.
- Strict isolated link proof: 12/12 VERIFIED, zero blind/differing words.
- Independent full metadata comparison: 12 records / 376 bytes exact, including
  string tails and both complete vtables with preambles; no blind relocations.
  Executable check and evidence: build/check_enemy_switch.py and enemy-switch-proof.json.
- Port references: 408 resolve. Changed-scope declaration agreement passes with
  no new disagreements. No new Enemy declaration-baseline exception is needed.
- Committed-range relocation, attribution and final independent review pending.
- ES-SR-01: fixed stale paths/class identity in notes/actor-leaf-provenance.md.

## Remaining integration work

The canonical promotion helper's APIs applied the reserved source, manifest and
ov002 delinks changes. Its attribution and CONVERTED outputs were saved only as
unapplied proposals: build/enemy-switch-attribution-proposal.json (12 credits)
and build/enemy-switch-converted-baseline-proposal.json (5 existing identities).
The ten renamed method ledger rows are prepared in
build/enemy-switch-rename-ledger-proposal.tsv. Their original historical names
are preserved in the why column. These three tracked files are reserved by other
tasks; request scoped isolated bookkeeping authorization before applying them.
The actual ledger gate currently fails on those ten unapplied rows; proposal
validation passes. No attribution or converted acceptance is claimed yet.

Scene's separate declaration-baseline migration remains pending user approval.
Do not infer permission for either task from automatic goal continuation.
After approval, apply only reviewed scoped proposals, run the tracked gates,
commit, and obtain independent exact-candidate acceptance. Keep local.
