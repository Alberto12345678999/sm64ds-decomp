# daMky_c finishing checkpoint

WIP continuation of issue2410 and merged PR3882; this checkpoint does not complete the issue or accept production integration.

Base: df618e80271212106c9f1e225756f691abaa498b. Task issue2410-finish1015, producer codex-mky-finish-producer1015. Source is in the wired worktree C:/tmp/sm64ds-mky2410-finish1015, branch cpp/mky2410-finish1015. Independent Astra scouts have made no production edits.

Completed source changes in this checkpoint:

- Native dBgCh_Lin local constructed after the reset-timer early return; ordinary method calls and destructor now reproduce the retail lifetime.
- Native shared flat Matrix4x3 assignment and a typed mCapMtx field, replacing a private matrix view and raw scalar array. The repository's incompatible common.h/math/Matrix.h type definitions remain a shared-source defect; this checkpoint explicitly does not solve it.
- dActor_c::mCarryMatrix recovered at0xc8 in the existing alignment gap, without changing field count or class size. Monkey cap/player access uses this pointer.
- Cage-push accumulator named mCagePushProgress from observed increments; no unit is asserted and unobserved padding stays padding.

Evidence (ignored local build artifacts): native-checkpoint-verify.log reports46/46 MATCH, clean exact compiler-only policy, clean isolation, clean relocation destinations, correct order. actor-header-equivalence.json reports306/306 other production source raw ELF objects identical; the remaining consumer is the intentionally changed Monkey TU. This is not a fresh full-ROM or private CI pass.

Remaining: seven shared scalar API migrations, meaningful helper names, genuine owned globals/initializer/profiles and nontext production enrollment, canonical matrix type review, full-ROM and module-aware consumer checks, independent exact-commit source/byte review and terminal private validation. Conditional scalar maps are experiments, not production acceptance. Metadata tool reports4 VERIFIED/5 PARTIAL; complete vtable slots and NUL-terminated strings are measured separately, with alignment tails identified rather than hidden.

Shared API/rename work is pending explicit recovery of four bookkeeping reservations whose stopped owners confirmed missing receipts. Review-only plan: build/queue-resource-recovery-plan.json. No foreign resources or queue ownership have been changed. Preserve all old checkpoints and evidence. Do not start2412 or close2410 at this checkpoint.


## Verified continuation and remaining dependency (2026-10-15)

Merged refreshed remote main e209dacfaaa95cb5490637ff053d62182689bebe normally into this branch; the accepted input remains an ancestor. That base refresh changed contributions.json only. Native UpdateAngle and cstd::fdiv calls now replace their two hand-mangled imports. Pinned19.1.7 formatting preserves token streams and the COMPLETE raw Monkey ELF object; no codegen identity mask was used.

Fresh full-ROM check:106/106 modules exact,11334/11334 functions reproduced,332/332 source-owned data claims reproduced,0 mismatches, intact-TU gates pass and no new symbol errors. The declaration ratchet reports no new disagreements/local copies; the changed-line style check has0 findings/0 deferrals. Only the owned manifest verification metadata was refreshed through a scratch manifest. Full hashes and report scope are in notes/experiments/mky-finish1015.json. This is local byte proof, not private CI or final Source acceptance.

The old native line/matrix failures are now disproved by this source. The seven scalar interface probes also succeed with genuine native callee bodies, so the old Fix12 wall must not be carried as compiler impossibility. Their canonical migration is still unapplied. Independent Astra Source review rejected four provisional Monkey-specific file-handle lifecycle aliases; a real shared8-byte model and seven native lifecycle bodies now match conditionally, including the full1196-byte initializer. Shared layout migration reaches264 sources, including391 duplicate-storage wrappers in199 source files. Active actor owners retain their leases; no foreign paths were edited.

Native global candidate,58 owned objects and163 nontext relocations are preserved in build/completion-scout/preview and interface-finish/native-handles. They are experiments, not accepted production. The shared handle/lifecycle migration must precede native global production enrollment. The separate tooling task issue2410-terminal-bss-tool1015 preserves four linker-owned BSS alignment bytes using independently configured actual object size, without padding objects; its own producer/verifier stages and PR are separate.

Keep2410 OPEN and do not start2412. Next action after the explicit reservation recovery decision: coordinate actual shared API/type migrations with current actors' owners, preserve existing accepted outputs and debt, compose and revalidate the completed source. User authorization for the four-file administrative recovery remains pending. Recovery review artifact: build/queue-resource-recovery-plan.json. No Source-stage completion has been published for this WIP task.

Exact full-ROM source checkpoint was a24cdcbf48348bd1ce9bca8f8ffea4a9ef1d462f. The later formatting is covered by token equality and complete raw Monkey object equality; subsequent manifest changes refresh verification metadata only. The experiment record keeps that bridge explicit instead of representing a fresh full-ROM execution on every documentation/formatting commit.
