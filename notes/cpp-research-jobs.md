# Resumable readable-C++ research jobs

`tools/cpp_job.py` turns one configured function into a local research folder
that an AI agent or human can work without placing an unverified draft in
`src/`. It joins the three evidence sources that were previously separate:

1. static ROM/config evidence: exact module, address, size, bytes, hash,
   canary, relocations, and symbolic assembly;
2. existing decomp work: the current source, reconstructed class/header fields,
   prior attempt/provenance rows, and the best banked near-miss; and
3. optional emulator evidence: saved `cpp_probe.py` or `scenario.py` JSON,
   including callers, live receiver identities, values, and writes.

The generated folders live under `progress/cpp-jobs/`, which is gitignored.
They may contain ROM-derived bytes and memory captures: keep them local and do
not publish or commit them.

## Create a job

```powershell
python tools\cpp_job.py create _ZN5Fader13AdvanceInterpEv `
  --runtime-evidence traces\questions\Fader_AdvanceInterp_live.json
```

Use `module:symbol` when a configured name exists in multiple modules. The
default folder is `progress/cpp-jobs/<module>/<symbol>/`. `create` can be run
again to refresh ROM/config/source context. It preserves `candidate.cpp`, saved
runtime evidence, and a still-current verification result. Pass
`--reset-candidate` only when intentionally discarding the job's working copy.

Each job contains:

| File | Purpose |
|---|---|
| `TASK.md` | Vendor-neutral assignment and proof boundary for an agent/human. |
| `job.json` | Machine-readable target, source, class, evidence, and latest verdict. |
| `candidate.cpp` | The only file to edit during reconstruction. |
| `target.bin` | Exact local ROM bytes for the configured function. |
| `target.s` | Relocation-aware symbolic ARM scaffold. |
| `semantic_draft.c` | Optional m2c comprehension draft; never a match claim. |
| `source_snapshot.*` | Current canonical implementation, when one exists. |
| `relocations.json` | Every configured relocation inside the target. |
| `prior_work.json` | Matching attempts, provenance, and near-miss rows. |
| `runtime/*.json` | Copied emulator evidence supplied on creation. |
| `verification.json` | Latest canonical compile and linked-byte verdict. |

`target.s` is generated even when the optional `vendor/m2c` checkout is not
installed. In that case the manifest records why `semantic_draft.c` is absent
instead of silently omitting the stage.

When the current source is C, `create` seeds `candidate.cpp` with `//cpp`, gives
the target definition C linkage, and wraps configured ROM callee declarations
with `extern "C"`. This is a mechanically verifiable migration baseline, not a
claim that the body or names are already ideal C++. The agent can then improve
types, methods, and names while the verifier guards code generation and
relocation identity.

## Work and verify

Give the job folder—or simply its `TASK.md`—to another agent working in the
same checkout. It should edit `candidate.cpp`, then run:

```powershell
python tools\cpp_job.py verify `
  progress\cpp-jobs\arm9\_ZN5Fader13AdvanceInterpEv
```

The verifier does not trust command exit text from `match.py`. It directly:

1. compiles `candidate.cpp` with canonical `mwccarm 2004/b56` and the repo's
   C++ flags;
2. finds the emitted function and compares every non-relocation word against
   `target.bin`;
3. reconstructs each relocation through `linkcheck`; and
4. sets `promotion_ready: true` only for exactly one emitted symbol with
   `verdict: VERIFIED` and `blind: 0`.

An incorrect candidate exits nonzero and records `NO-BYTE-MATCH`, `WRONG`,
`BLIND-N`, or another explicit non-promotion verdict. If a translation unit
emits multiple byte-and-link-verified functions, the result is
`AMBIGUOUS-VERIFIED-SYMBOL`; rerun with `--candidate-symbol` rather than letting
object symbol order choose.

Read the current state without compiling:

```powershell
python tools\cpp_job.py status `
  progress\cpp-jobs\arm9\_ZN5Fader13AdvanceInterpEv
```

## Promotion boundary

The tool deliberately does not copy anything into `src/`. A job's local
`VERIFIED` result proves the candidate is eligible for deliberate promotion;
it does not claim the target, select a final uncertain name, edit shared
headers, stamp authorship, or create a PR.

Before promotion, follow `AGENTS.md`: claim the target, use `tools/srcpath.py`
for placement, retain attempt history, stamp match provenance, and run any
header/move/port checks that the final diff requires. Tooling/docs changes and
source-match changes remain separate PRs.

## Proven smoke test

The Fader job above was exercised against the current extraction and existing
readable C++ source. Its 40-byte candidate emitted
`_ZN5Fader13AdvanceInterpEv` under `2004/b56`; byte comparison passed, its one
relocation linked to `_Z14ApproachLinearRiii`, and `linkcheck` returned
`VERIFIED` with `blind: 0`. An intentionally wrong 12-byte candidate was then
rejected as `NO-BYTE-MATCH`, after which the valid candidate was reverified.

An overlay/C-migration smoke test used
`ov002:func_ov002_020effb8` plus the passing Bob-omb camera scenario. `create`
converted the existing 784-byte C source into `candidate.cpp`, preserved the
target and both called ROM symbols with C linkage, and `verify` returned a
canonical byte match plus `VERIFIED`, `blind: 0`. This checks overlay binary
selection, runtime-evidence bundling, and the automatic C-to-C++ baseline—not
just an already-C++ arm9 leaf.
