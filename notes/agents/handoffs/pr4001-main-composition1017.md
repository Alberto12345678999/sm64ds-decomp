# PR 4001: current-main composition handoff

This document describes this commit. The queue records its immutable output SHA.

- Task: `pr4001-main-composition1017`; composer: `codex-stacked-composer1017` (Codex `/root/review_stacked`).
- Issue: https://github.com/tangosdev/sm64ds-decomp/issues/3839
- Accepted candidate: `8ed73181c71e2eb81f8962ecbc238502890ee7f2`; preceding independent review: `enemy-surface-currenta6de-composition1016`.
- Composition base and workflow: `0301d63f80c3d7ddb3358b277cc592c19af6dff7`; clean merge checkpoint: `a21a51a4526619b5ceb6d3912ac51bac7aba526a`.
- Active independent source-review policy remains `18af52b49b9fb5663d417bdfa86109b7b157aaa3`.

The merge preserves both the accepted candidate and pinned main as ancestors. Git merged them without conflicts. The complete `src/runtime/actor/d_enemy_base.cpp` blob is identical to the accepted candidate. The only change made by this composer beyond the mechanical merge is this handoff report. Existing source, header, manifest, symbol, attribution and historical report contents were not edited. The original source reservation remains with its existing owner; this task reserves only this report.

The source scope and reconstruction limits remain those recorded in `notes/experiments/enemy-surface-results1016.json` and the preceding independently published review. This composition does not complete the class or adopt overlapping PR #4008. Previously recorded deferred reconstruction findings and measured compiler barriers remain outstanding; no identifier provenance or object ownership claim is added.

The pinned compiler canary passed `(True, '2004/b56')` in this dedicated wired worktree. Full-ROM and scoped checks are running at this report checkpoint. Their completed results belong to the separately published producer and independent-review evidence, pinned to this commit and the base above:

- `python tools/rombuild.py -j16 --no-rom`: `build/composition-rombuild.log`.
- `python tools/prepush_linkcheck.py --range 0301d63f80c3d7ddb3358b277cc592c19af6dff7..HEAD --json build/composition-prepush.json`: `build/composition-prepush.log`.
- `python tools/check_decl_agreement.py --changed 0301d63f80c3d7ddb3358b277cc592c19af6dff7`: `build/composition-decl.log`.
- Complete emitted-object, initializer, data and relocation proof: independent reviewer, pending at this checkpoint.

Historical stock-control symbol diagnostics and data advisories remain qualified in their evidence; no blanket clean data result is asserted. No paths were renamed and no shared header changed in the PR delta. Fresh independent composition acceptance and private validation are pending. Root controls source-branch publication and merging after those gates; this producer has not pushed the PR branch.
