# Historical integration measurements (reference only)

Use [the current integrator role](../roles/integrator.md). Ledger and compiler
measurements below are historical evidence; they do not override the current
protocol, exact-head checks, or repository validation requirements.

This role exists because of a hard resource limit, not a quality one. The
validator is **one box, one job, ~20-33 minutes**, and every merge to `main`
invalidates the pinned base of every other open PR. So five separately-proven
class PRs do not cost five validator runs — they cost five runs plus four
rebases plus the conflict cascade the rebases cause. Composed into one branch
they cost **one run**.

You do not re-derive anything. Every class you compose has already been proven
by a builder. Your job is to move proven commits onto a fresh base without
losing or inventing anything, and to prove *that*.

## When to compose

- Two or more class PRs are open, each already green from its builder.
- They touch the same ledger files (they always do), so they will conflict with
  each other in sequence no matter what order they land in.
- Nobody has started rebasing them by hand yet. If someone has, read their
  branch first — hand-resolved ledger files are the one thing you cannot trust.

Do **not** compose a class whose builder has not finished. An unproven class in
the batch makes the whole batch unmergeable, and the validator will not tell you
which one.

## The shape

Work in a fresh short-path wired worktree created with the `decomp-worktree`
skill. Do not compose in the primary checkout or reuse either writer's build
directory; the compiler, ROM inputs and per-branch build state must be isolated.

Cut from `origin/main` at a named SHA — write the SHA in the PR body, it is the
only record of what you rebased onto:

    git fetch origin main
    git log -1 --format=%H origin/main          # record this
    git checkout -b integrate/<ovNN>-promotions-<MMDD> origin/main

Then cherry-pick each class's **content** commits, in class order, class by
class. Recompose generated and shared bookkeeping once:

- **Regenerate the TU state note once.** Who matched each function is already
  in `function-authors.json`, keyed by address. Do not copy credit onto the
  new file, and do not run a credit script.
- **Reconcile anything touching the two ratchet files once.** Take `origin/main`'s copies and
  reconcile once at the end (below). Cherry-picking them class by class is how
  double-banked rows get created.

Everything else — the TU `.cpp`, the deleted shards, `delinks.txt`,
`symbols.txt`, the manifest — is content and comes across intact.

## Ledger reconciliation, once, at the end

This is the step that goes wrong, and the failure is silent in both directions.
Reconcile the shared ledgers (`attribution.json`, manifest entries) once at the
end, non-destructively, and read the diff — do not just look at the exit code.

## Prove the composition, not the classes

The builders proved the classes. You prove that composing them changed nothing:

Immediately before the proof block, fetch and merge the newest `origin/main`.
If that changes the tree, repeat the one-time ledger/state reconciliation above;
an earlier green head is not evidence for the new merge commit.

    python tools/tubuild.py verify <ov>/<Class>        # once per class
    python tools/rombuild.py -j 16                     # 106/106 exact + retail NDS
    python tools/romdata_check.py --files src/game/<dir>/<file>.cpp   # per class
    python tools/cpp_tu_state.py --check-note
    python tools/source_coverage.py --check --base origin/main

Run `git status` after **every** `verify` — it writes to the manifest when it
fails, and a dirty tree after a green-looking run means it did not pass.

Two things to re-confirm per class rather than trust the builder's PR body,
because both are cheap and both have been wrong before:

- the delink **row count** against the formula, and
- that `externalized_output` is empty (a non-empty block means the class took
  the text-verified-only route and cannot be promoted at all).
- that you did not add or change a row in `function-authors.json` for a move.
  Who matched each function is already there, keyed by address.

Also re-verify every canonical address against the **owning module's**
`symbols.txt` — not the class's own overlay. Cross-module homes are normal and
are what make the promotion legal.

## The PR

Title: `Integrate <n> <ovNN> TU promotions (<Class>, <Class>)`.

Body must carry, because none of it is recoverable from the diff:

- the base SHA you cut from,
- the list of source PRs being superseded, by number,
- which commits you dropped and why,
- the ledger verdict from step 4 above, with the identical-record count,
- the source-coverage verdict (`0 B handed back to the cartridge`). A credit
  note in the validation report does not fail the merge,
- one gate block per class, plus the single `rombuild` line
  that covers the whole batch.

When it merges, **close the source PRs as superseded** with a comment naming the
integration PR. They will not close themselves, and a stale open PR whose work
already landed is what makes the next agent rebase something twice.

## What not to do

- Do not "fix" a partial promotion you are composing. A builder that shipped
  22-of-61 measured a real refusal; raising the count in an integration branch
  means you re-derived something without the evidence.
- Do not compose across overlays without a reason. Same-overlay batches share
  the ledger rows that were going to conflict anyway; cross-overlay batches just
  make the blast radius bigger for the same one validator slot.
- Do not use `git merge-tree` to predict whether this will merge. The exceptions
  file is declared `merge=union`, GitHub ignores the driver, and `merge-tree`
  honours it — so it reports clean where GitHub reports CONFLICTING. Use
  `gh pr view <n> --json mergeable`.
