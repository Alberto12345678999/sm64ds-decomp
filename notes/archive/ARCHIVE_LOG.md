# notes/ archive log

Generated 2026-08-14 by an automated triage pass (4 parallel haiku agents, one
per ~14-file slice of `notes/`, each checking currency, supersession, inbound
references, and whether described work has already landed). Results were
independently verified against `git status` / file content before being
trusted — see the corruption note at the bottom.

Nothing was deleted. Archiving is a plain filesystem move; git still has full
history for every file under its original path.

## Archived (1 of 57 reviewed)

| File | Reason |
|---|---|
| `n64-decomp-cross-reference.md` | Self-marked `Status: investigation notes, incomplete. Parked 2026-08-06 for later revisit.` Not linked from any current handoff/plan doc. |

## Kept (56 of 57)

All other files were judged current/load-bearing: either actively linked from
other notes or `AGENTS.md`/`CONTRIBUTING.md`/`README.md`, describe still-open
work, or are the canonical reference for an idiom/process still in use
(`matching-style.md`, `mwccarm-codegen.md`, `pret-idioms.md`, etc.). No note
was found to state a claim about compiler idioms that is now contradicted
elsewhere — the "idiom notes going stale" concern didn't turn up a concrete
case in this pass, but see the two flagged items below for the closest
candidates.

## Needs a human decision (left in place, not archived)

| File | Why it's borderline |
|---|---|
| `overlay-ambiguous-references.md` | Content opens with "Status: mostly closed... of the 137 references that were really overlay-ambiguous, 10 remain." Mostly-resolved but not fully — could go either way. (Also: this file got mangled by a tool-execution glitch during the automated pass and was restored verbatim from git HEAD — see below.) |
| `plan-scalar-markers.md` | Opens with "Status: done for the 71 mechanical cases. A handful remain for a person -- `gen_header.py --report` is the live count; it was 1 when this was written." One review agent recommended archiving it; I left it for a human call since "1 remains" means it isn't fully closed. |

## Incident: one agent's move command malfunctioned

While archiving `n64-decomp-cross-reference.md`, one agent's shell also
somehow renamed `overlay-ambiguous-references.md` to a garbage filename
(`archive"` + an embedded newline + literal leftover command text) sitting
directly in `notes/`, instead of moving it into `notes/archive/`. Content was
unaffected (verified byte-identical to `git show HEAD:notes/overlay-ambiguous-references.md`
modulo CRLF/LF). I found it via `git status`, confirmed the content, and
renamed it back to `notes/overlay-ambiguous-references.md`. No data was lost,
but it's the reason I independently re-verified every claimed move in this
pass rather than trusting agent self-reports at face value.

## Second pass: #1511 (2026-08-15), and one revert

`bc93fa767` ("cleanup and archive outdated docs", #1511) archived six more files
without amending this log, so the tables above understated the archive by 6 of 7
entries until now:

| File | Status |
|---|---|
| `crack-loop-runbook.md` | archived by #1511 |
| `func_02059d8c-asm-origin.md` | archived by #1511 |
| `func_ov079_02124008-floor.md` | archived by #1511 |
| `plan-gen-header.md` | archived by #1511 |
| `plan-scalar-markers.md` | archived by #1511 — **contradicts** the "Needs a human decision (left in place)" row above; no human decision is recorded |
| `pret-idioms.md` | archived by #1511 — **correctly**, on content; see below |

### `pret-idioms.md`: #1511 was right about the file and wrong about the links

The "Kept" section above names `pret-idioms.md` as a canonical reference, so it
was briefly restored to `notes/` on that basis. That was a process argument, not
a content judgement. On the content it does not survive:

- **Six of its eleven idioms are verbatim duplicates.** `matching-style.md:289`
  ("Reference-decomp ground truth", 2026-06-21) mined the same two repos —
  pret/pokediamond and pret/pokeplatinum — eight days earlier, quoting the same
  in-source comment strings, *and* did the version triage this note never does
  (`matching-style.md:315` names two reference levers as 2.0-series and
  inapplicable to us).
- **Two are contradicted by our own measurements.** Its idiom 5 recommends
  `register`-qualified locals; `mwccarm-codegen.md` records that knob as inert at
  `:24`, `:616`, `:1017`, and `:3036`, and `matching-style.md:348` says decl order
  and `register` have "*zero* effect". Its idiom 6 says keep ternaries as
  ternaries; `matching-style.md:453` says that guidance "**is not universal**" and
  that rewriting one as `if/else` fixed a 20-instruction coloring residual.
- **None of its idioms are unique.** Idiom 11 is ours, not pret's, and already
  lives at `mwccarm-codegen.md` §6bc.
- **It names no compiler build.** pokediamond is 1.2-series and pokeplatinum
  2.0-series; we pin 2004/b56. Every register-allocation idiom is therefore
  unattributed on the one axis our corpus proves is build-sensitive. Its framing
  is pre-b56 throughout ("wall #1 remains largely unsolved"), a wall
  `mwccarm-codegen.md` §6ai reports as fallen once b56 was recovered.

The cost was not passive. Four of its referrers were **agent prompt text** —
`tangos.json`, `tools/chaosviewer.config.json`, `tools/refine_run.js`,
`tools/sched_run.js` — and `tools/sched_run.js:50` handed it to an agent
precisely when stalled, pointing it at the two levers our corpus disproved.

All eight live referrers have been repointed at `mwccarm-codegen.md` or
`matching-style.md`: the four above, plus `AGENTS.md`, `CONTRIBUTING.md`,
`notes/itcm.md`, and `notes/levers.jsonl`. The two already-archived referrers
(`tools/archive/crack_pr104.js`, `archive/crack-loop-runbook.md`) were left alone.

The lesson for future passes: **archiving is a rename, and a rename breaks every
inbound link.** Before moving a note, grep its basename across the repo and fix
the referrers in the same commit. Nothing in CI checks this.
