# OV007 portrait stroke table continuation

Issue [#4112](https://github.com/tangosdev/sm64ds-decomp/issues/4112), task `data-ov007-pathsets-native1018`. Tested base `43ad1f4dd7e296a9d783078cc77b637c01d135da`; source branch `data/ov007-pathsets-native1018`. Producer: `codex-ov007-pathsets-native1018`. Predecessor: `ov002-030-language1017`; all four inherited findings and their original text are retained in the experiment.

Five complete native objects supply 120 bytes: `020cdb34..020cdb4c` contains six stroke counts and `020d7e68..020d7ec8` contains four six-pointer tables. All five symbols retain native local linkage. The existing `func_ov007_020bbe60.c` is admitted as an intact compiler object with these two complete data ranges and its existing 312-byte text range. No neighboring source is absorbed, and this is not a historical-TU or class-identity claim.

## Names and formats

Plotting the decoded coordinate pairs produces Mario front/side portraits, Luigi, and three Yoshi variants. The inferred `sPortraitStroke*` names reflect that evidence. The screen role and original identifiers are unknown. The six stroke counts are 30, 34, 36, 20, 32, 32; selector 0..1 and cycle 0..2 establish the six-row index. Per-stroke point counts are 32-bit values; coordinates are bytes in mode 1 and 32-bit values in mode 0. The projector accepts screen X/Y coordinates, negates Y and takes depth separately. Cumulative progress thresholds are 32-bit values; literal timing units are not established.

The outer pointer arrays remain mutable `.data` objects. Const pointees express observed reads, not uniquely recovered historical qualifiers. All 24 nested arrays remain ROM imports. Sharing among the 184 paths means a future continuation must preserve aliases and unique storage rather than emit a copy per drawing.

## Helper contracts and limits

The dispatcher accepts each entire coordinate-pointer table as `const void*`; its two branches interpret that object as the correct byte-pointer or 32-bit-pointer array. Point counts and threshold-pointer arrays have concrete types. Both branches retain their original instructions. The per-path allocator now explicitly returns the pointer its callers consume; the return produces identical output under 2004/b56. The lower allocator's existing integer-address return/declaration mismatch and additional callers are untouched and recorded as debt.

All five original definitions, 812 code bytes and 20 relocations remain identical after the five intentional top-table target renames at the same addresses. The native tables have 120 object bytes and no alignment gaps. Twenty-four new data relocations preserve the exact configured `overlay(7)` destinations. The 24 non-text relocation licenses cover every data pointer; the 8 text relocations are checked through the strict function gate. No relocated word is accepted through masking.

## Validation and handoff

Private proof: `build/native/proof.json`; final provider proof: `build/final-ownership.json`; native requests: `build/requests.json`. Reproduce with `python build/prove-native.py`, final-config `python tools/tubuild.py linkcheck --baseline --module ov007 -j16`, ordinary `python tools/tubuild.py linkcheck ov007/AnimationPathSets -j16`, and `python tools/rombuild.py -j16 --data-provenance-requests build/requests.json --report-json build/production.json` (full ROM enabled). Private scripts are evidence helpers, not tracked build dependencies.

Current strict checks: 5 verified, 0 warnings or blind results; declaration ratchet and style pass; source coverage adds 120 bytes and gives back 0. Current normal-provider result: **PASS**. The known nine baseline strict-symbol diagnostics must remain distinct from zero new diagnostics. Final immutable source acceptance, private validation and publication are separate gates; no merge is authorized.

All 14 findings are retained in `notes/experiments/data-ov007-pathsets-native1018.json`. The inherited stale-document-reference failure is preserved as history; the current gate passes without source-path changes in this task. Remaining portrait identity, timing, constness, nested data, lower allocator and raw-layout/TU questions keep reconstruction partial.
