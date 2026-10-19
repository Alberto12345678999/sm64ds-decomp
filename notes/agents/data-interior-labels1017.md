# Initialized data interior labels

Task tools-data-interiors1017, issue #4023. Base e8dc126bcda1865cce7a4a4cb920fb2095deefb9.
This tooling candidate supports the separate cart source task #4018.

A typed CLPS block emits16 correct bytes under one compiler symbol, while the
configuration also names its entry at offset8. The old linker helper preserved
only code/BSS interior imports; strict symbol validation therefore correctly
reported the missing initialized-data label.

The helper now retains configured interior data identities, including labels with
no live import. It requires one actual non-local initialized OBJECT definition,
one configured module home, matching .data/.rodata section, a complete source
claim covering the entire emitted object, and the actual object's path matching
that source provider. It refuses conflicting declared sizes, duplicate definitions
or homes, wrong providers, uncovered storage, and boundary/outside labels. Object
extent comes from the compiled ELF symbol, never the next configured address.
The alias is scoped inside the owning output module, using the existing linker
mechanism. Source and object storage are unchanged. Final module/ROM/provider
validation remains mandatory; this mechanism does not recover original ownership.

Validation on this candidate:

- python -m pytest -q tools/test_lcf_interior.py tools/test_rombuild.py tools/test_tu_production.py:90 passed.
- The real cart prepared-object inventory selects exactly one additional label:
  data_ov047_02111abc inside gKm3KurumaClps at+8, overlay47.
- A fresh isolated link reuses those immutable prepared objects and the candidate
  helper. All106 executable module binaries are unchanged. The alias has value
  02111abc and the same OV047 ELF section index as its source-defined parent.
  Strict dsd symbol diagnostics return to exactly the nine unchanged baseline
  errors; the cart interior-label error disappears. All object/input hashes are
  rechecked. This is a tool integration probe, not final production cart admission.
- Independent verification of 0e6f7941f1ee1fa7771589d1c6c8c647731e813d passed
  the same 90 tests, 12 additional adverse-input probes, and a fresh cart link.
  The reviewer found only a trailing CR in this handoff, corrected in a
  documentation-only follow-up. PR CI remains pending.

Private reproducible probe:build/probe-cart-link.py; successful receipt:
build/cart-link-probe-v3/proof.json. The earlier v1 probe's assertion expected a
lowercase section name; the linker uses OV047. v2 verified the previous helper;
v3 binds the final helper. No ROM/compiler inputs or private receipts are committed.

Next:publish the tooling PR, then compose the cart source on this dependency
and refresh its control/TU/production proofs.
Do not merge without further authorization.
