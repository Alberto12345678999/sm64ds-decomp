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
