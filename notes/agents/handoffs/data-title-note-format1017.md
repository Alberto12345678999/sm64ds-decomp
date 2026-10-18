# Title historical conflict-note formatting

The manifest-conflicts check on PR #4060 rejected two historical resolved-conflict
notes because their added history qualifier preceded the checker's exact prefix.
This follow-up moves that same qualifier to the end of each note. It preserves
all historical content, resolutions and other manifest values; source, headers,
symbol bindings, delinks ranges and compiler inputs are unchanged.

Task `data-title-note-format1017` continues `data-title-native1017` on issue #4052.
The repair base is `72eb388e1f72cbb1b456c6ec3cd67de0227faaee`; the original native
data candidate was tested on `1b98141e598440a0432317b58678f3c5c088d558`.
The producer reproduced the two errors, then ran
`python tools/check_tubuild_conflicts.py --list` successfully after the repair.
Finding `title-note-format-ci-001` is fixed. This checker was missing from the
initial local validation and is now explicitly part of this handoff.

All six deferred source findings and the fixed startup-provenance finding are
carried forward verbatim in the experiment. The separate optional raw-data
diagnostic continuation `title-raw-local-resolution-001` also remains open;
the two note changes neither suppress nor change that measurement.

The predecessor's exact 59-provider, 106-module and full-ROM proof remains
attributed to its immutable SHA. This follow-up proves functional input identity;
the independent verifier refreshes final production binding before publication.
The repair appends to PR #4060 after review. No merge.
