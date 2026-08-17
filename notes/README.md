# notes/

Working documentation for the decomp. Everything here is hand-written prose;
generated artifacts live in `docs/` (the published site), `config/` (dsd data),
and `symbols/` (derived naming tables).

Start with [CONTRIBUTING.md](../CONTRIBUTING.md) for the workflow. This index
covers the notes themselves.

- [Start here](#start-here)
- [Codegen doctrine](#codegen-doctrine)
- [Runbooks](#runbooks)
- [Reference: naming and RTTI](#reference-naming-and-rtti)
- [Reference: ROM geography](#reference-rom-geography)
- [Reference: C++ and translation units](#reference-c-and-translation-units)
- [Plans](#plans)
- [Handoffs](#handoffs)
- [Research](#research)
- [Archive](#archive)

## Start here

| Note | What it gets you |
|---|---|
| [setup-mwccarm.md](setup-mwccarm.md) | The pinned mwccarm `2004/b56` and the NITRO-SDK. Section 1 is scripted. |
| [rom-build.md](rom-build.md) | Building a bootable hybrid `.nds` from our C plus the delinked gap objects. |
| [pr-validation.md](pr-validation.md) | What the merge gate asks, metric by metric. Read before your first PR. |
| [link-verification.md](link-verification.md) | `linkcheck.py`, which closes the reloc-destination blind spot a byte match leaves open. |
| [match-logging-console.md](match-logging-console.md) | The three tools tangOS Console needs present to work. |
| [m2c-setup.md](m2c-setup.md) | Wiring m2c as a free semantic-draft tier for large functions. |
| [assets.md](assets.md) | Extracting and editing NitroFS assets, and carrying them back into a build. |

## Codegen doctrine

The core of the project: how to write C that mwccarm turns into the ROM's bytes.

| Note | What it gets you |
|---|---|
| [mwccarm-codegen.md](mwccarm-codegen.md) | **The master catalogue**, from 4,400+ matched pairs. Cited by ~160 files *by section number* — see the warning below. |
| [matching-style.md](matching-style.md) | Source rules for steering codegen *shape* once the logic is already right. Includes the pret-decomp survey and which of their levers do **not** transfer to our pin. |
| [asm-policy.md](asm-policy.md) | When an `asm {}` block may still count as decompiled. |

> [!WARNING]
> `mwccarm-codegen.md` is referenced by section number from outside this repo
> (`tangos.json`, `tools/chaosviewer.config.json`, the refine/sched runners).
> Renumbering or reordering its sections breaks those silently — nothing in CI
> checks them. Append new sections; do not renumber old ones.

## Runbooks

| Note | What it gets you |
|---|---|
| [runbook-type-reconstruction.md](runbook-type-reconstruction.md) | Offsets → typed members → a function rewritten as real C++. |
| [runbook-reference-repair.md](runbook-reference-repair.md) | Making a reference point at the symbol the ROM actually uses. |
| [match-provenance.md](match-provenance.md) | Stamping *how* a function was matched, after it matches. |
| [match-attempts.md](match-attempts.md) | Which of the three jsonl attempt stores holds what. |

## Reference: naming and RTTI

The ROM names 429 classes. These notes are how we read them, and how far the
evidence actually goes.

| Note | What it gets you |
|---|---|
| [rtti-reconciliation.md](rtti-reconciliation.md) | The full 429-class graph and where this tree's headers disagree with it. |
| [cpp-naming-guide.md](cpp-naming-guide.md) | Itanium mangling rules for writing symbols the ROM agrees with. |
| [symbol-name-provenance.md](symbol-name-provenance.md) | Which *parts* of a mangled name are evidence and which are assertion. |
| [actor-vtables.md](actor-vtables.md) | All four Actor-hierarchy vtables, every slot resolved. |
| [actor-naming.md](actor-naming.md) | How 2,241 symbols got names out of the spawn table. |
| [model-rtti-names.md](model-rtti-names.md) | Model/animation class names read from RTTI records. |
| [dscene-c-siblings-census.md](dscene-c-siblings-census.md) | Vtable maps for `dScene_c`'s eight unnamed children. |

Rendered views of the same data are published from `docs/`: the
[class reference](https://tangosdev.github.io/sm64ds-decomp/class-reference.html)
and [the fBase tree](https://tangosdev.github.io/sm64ds-decomp/class-hierarchy.html).

## Reference: ROM geography

| Note | What it gets you |
|---|---|
| [itcm.md](itcm.md) | What the 41 ITCM functions are, and why they were invisible for so long. |
| [overlay-residency.md](overlay-residency.md) | Which overlays can be co-resident, and the evidence behind the tool. |
| [collision-query-classes.md](collision-query-classes.md) | RaycastLine / RaycastGround / SphereClsn share a base — proven from destructors. |
| [arm9-msl-walls.md](arm9-msl-walls.md) | Two MSL functions that stay asm **by design**. Closed, not a gap. |

## Reference: C++ and translation units

| Note | What it gets you |
|---|---|
| [dtor-variant-audit.md](dtor-variant-audit.md) | Which destructor variant a symbol actually is. 41% were mislabelled. |
| [dtor-migration.md](dtor-migration.md) | The four things blocking a D1 file from becoming a real `~Class()`. |
| [tu-boundaries.md](tu-boundaries.md) | What `tu_map.py` knows about TU boundaries, and where it stops. |
| [objisolate.md](objisolate.md) | Why 81 C++ destructor files would not link, and the four bugs behind it. |
| [port-selftest-bmp-gate.md](port-selftest-bmp-gate.md) | The comparison rule for the port's only CI rendering gate. |

## Plans

Forward-looking intent. Some describe work that has since landed — check the
status line at the top of each before trusting it.

[roadmap.md](roadmap.md) (MATCH → LIFT → PORT → POLISH) ·
[plan-cpp-language-mode.md](plan-cpp-language-mode.md) ·
[plan-base-headers.md](plan-base-headers.md) ·
[translation-unit-reconstruction-plan.md](translation-unit-reconstruction-plan.md) ·
[arm9-endgame.md](arm9-endgame.md) ·
[declaration-centralization.md](declaration-centralization.md) ·
[global-data-migration.md](global-data-migration.md) ·
[llm-assisted-global-data-migration.md](llm-assisted-global-data-migration.md) ·
[emu-trace-plan.md](emu-trace-plan.md) ·
[emu-trace-build.md](emu-trace-build.md)

## Handoffs

Working state for in-flight tasks. These go stale by design — they are a
snapshot of one session, not a maintained document.

[handoff-sphereclsn-detectclsn.md](handoff-sphereclsn-detectclsn.md) (live) ·
[handoff-class-skeleton.md](handoff-class-skeleton.md) ·
[handoff-marker-typing.md](handoff-marker-typing.md) ·
[handoff-validator-and-tests.md](handoff-validator-and-tests.md) ·
[tu-reconstruction-pilot-report.md](tu-reconstruction-pilot-report.md) ·
[tu-reconstruction-pilot-2-report.md](tu-reconstruction-pilot-2-report.md)

## Research

One-off investigations. Kept for the evidence, not as instructions.

[ghidra-dsd-landscape.md](ghidra-dsd-landscape.md) ·
[converted-tier.md](converted-tier.md) ·
[tu-naming-and-swallowers.md](tu-naming-and-swallowers.md) ·
[mwccarm-version-archive-search.md](mwccarm-version-archive-search.md) ·
[research-matching-levers.md](research-matching-levers.md) ·
[overlay-ambiguous-references.md](overlay-ambiguous-references.md) (superseded by `overlay-residency.md`)

## Archive

[archive/](archive/) holds superseded notes, with [archive/ARCHIVE_LOG.md](archive/ARCHIVE_LOG.md)
recording what moved and why.

> [!IMPORTANT]
> Archiving is a rename, and a rename breaks every inbound link. Before moving
> a note, grep its basename across the whole repo — including `tools/*.py`
> docstrings, `src/` comments, `tangos.json`, and `tools/chaosviewer.config.json`
> — and fix the referrers in the same commit. Nothing in CI checks this, and the
> last two archive passes left 17 dangling paths behind.
