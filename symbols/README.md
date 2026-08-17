# symbols/

**Generated output. Do not hand-edit.** Every file here is produced by a script
and consumed by other scripts; edits are lost on the next regeneration.

Not to be confused with `config/**/symbols.txt`, which is dsd's per-module symbol
data and *is* hand-maintained.

| File | Written by | Read by | Format |
|---|---|---|---|
| `actor_renames.tsv` | `tools/actor_names.py` | `tools/cpp_index.py`, `tools/cpp_rename.py` | TSV, 5 columns |
| `overlay_actors.md` | `tools/actor_names.py` | `tools/rtti_reference.py` | Markdown, but **parsed by regex** — the extension is misleading |
| `actor_renames_report.txt` | `tools/actor_names.py` | nothing — human audit trail (`UNRESOLVED` / `NOVTABLE` / `SKIP`) | text |
| `verified.tsv` | `tools/import_symbols.py` | `tools/cpp_rename.py`, `tools/cluster_targets.py` | TSV: `addr`, `name`, `kind` |

> [!CAUTION]
> **Do not re-run `tools/actor_names.py` to "refresh" `actor_renames.tsv`.** It is
> destructive today, and silently so. `propose()` only emits a row for a symbol
> still spelled `func_<addr>` / `data_<addr>`, and all 2,241 of those renames were
> `--apply`'d to `config/**/symbols.txt` long ago — verified: 2241/2241 of those
> addresses now hold real names, zero placeholders remain. A plain re-run therefore
> finds nothing and rewrites the file down to its header row, destroying the
> addr → mangled-name map that `cpp_index.py:86` and `cpp_rename.py:43` read. Both
> are `.is_file()`-guarded, so they degrade to empty with no error and ~2,241 names
> simply vanish from the rename map.
>
> The file is a **historical record of a completed rename pass**, not a cache. Treat
> it as append-only. `tools/import_symbols.py` (which writes `verified.tsv`) has no
> such hazard.

## Two things to know before you touch this directory

**Nothing here is on a gate path.** No byte or CI gate reads these files —
verified against `eligible.py`, `rombuild.py`, `port_refcheck.py`,
`check_references.py`, `prepush_attribution.py`, `langmode_audit.py` and the
report generators. Moving or deleting a file will not turn anything red.

**Which is exactly the hazard.** Every reader is `.is_file()`-guarded and
degrades to empty without an error. Lose `overlay_actors.md` and
`docs/class-reference.html` regenerates with its actor column silently blank
(`load_overlay_levels()`, `tools/rtti_reference.py:218`). Lose `actor_renames.tsv` and ~2,241 mangled
names vanish from the rename map with no diagnostic. If you move anything here,
update the six path constants in `actor_names.py`, `rtti_reference.py`,
`cpp_index.py`, `cpp_rename.py`, `cluster_targets.py`, and `import_symbols.py`
in the same commit.

## Currency

`actor_renames.tsv`, `overlay_actors.md`, and `actor_renames_report.txt` were all
written by one commit (`4172a92ee`, 2026-07-10) and their **data** has never been
regenerated since. `overlay_actors.md` has since gained a provenance header, but its
body is still that 2026-07-10 derivation — if the config addressing has drifted, the
map is as stale as it was before.
`verified.tsv` was last refreshed 2026-08-09 and is described in
[`notes/symbol-name-provenance.md`](../notes/symbol-name-provenance.md) as
"a record, not an assertion — left stale on purpose."
