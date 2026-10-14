## Current-main provenance continuation, 2026-10-14

Producer: `codex-menbo-current-provenance-producer1014`, the same actual agent as
the preceding `codex-menbo-retire-integrator1014` and Yegg producer roles. This
agent is the author of these prose repairs, not the original Menbo reconstruction
and not an independent reviewer of this candidate. Own producer lease:
`7ea79669-5815-4298-b4ad-c2203b447531`. This is a lease identifier, not a model-session UUID.

Claimed write input remains `b047df1001747e57c320295cb5219d67ca300bf1`.
The original accepted Source and manifest were literal at external squash
`4bf6ccdaebe25c3b9a7ed04bd30f753957bf6f3e` (PR #3007). Current main has later
reconstruction; the normal composition `a568bd0b3e702d144bb7f953b6b792973588516a`
retains both that accepted input and current base
`0e2e4c63fa3e0530f542a8028febf5cffacd777e` as ancestors. Its named-blob conflict
resolution preserved every current-main tracked file. The actual provenance
history is eleven later Source/manifest commits plus the original landing;
all full commit IDs are retained in `build/menbo-retire1014/composition.json`.

Independent review of that composition found two current factual errors. This
does not reopen the original accepted Source or assert a runtime mismatch:

- `MENBO-CURRENT-INIT-STATE-02`: both exceptional InitResources branches select
  node `021344f4`, entry `02131db0` / updater `02131c48` (water chase). The
  comment now says water chase. Water rest is the distinct `02134504` node.
- `MENBO-CURRENT-OWNERSHIP-PROSE-02`: the active vtable reason now distinguishes
  external canonical RTTI/vtable metadata from owned initializer, ctor, PMF and
  BSS storage. The old text-only boundary note is explicitly historical.

Only this comment, two manifest prose fields, and this reserved handoff change.
Source executable tokens, headers, symbols, enrollment, ownership addresses,
aliases and all other manifest policy values remain unchanged. The seven prior
fixed dictionaries remain exact; the two current repairs await independent
recheck. The raw independent failure and its older inherited finding epoch are
retained separately, without regressing the canonical accepted fixes.

Tested Source/manifest checkpoint: `4a5edacca22e1cd38f46c375a7a96c8b3253cb2f`.
All five tested tree objects are bound privately; this report-only final commit
must retain them. Actual compiler canary: `VERIFIED 2004/b56`.

- Fresh current control and repaired raw objects are entirely identical:
  `b74698a5a976112942e97773dc9f6828290c9e7f2b77ed7cff35a03b1a3c4f76`.
- Entire ordinary prepared objects are also identical:
  `d0e2b9c43489179b31118e82a40766ad03542100c08c171c1205b4392855b4f4`.
- All 26 unique functions (25 text plus the 448-byte initializer), 6,492 function
  bytes and 235 typed references pass strict comparison with zero differences
  and zero blind relocations. The initializer has 34 proved references.
- Raw: 62 allocated sections / 7,034 bytes / 295 references. Prepared:
  49 sections / 6,724 bytes / 244 references. Existing canonical metadata:
  11 externalized records / 242 bytes / 46 references.
- Retained non-executable storage is PMF data 64 + BSS 164 + ctor 4 = 232 bytes.
  The executable initializer is already among the 26 functions; it is not
  additional non-executable metadata. All section bytes, sizes and references
  pass under the unchanged intact-object policy.
- Official prepush: 26 checked, 25 VERIFIED, one `BLIND-12` initializer warning,
  zero blockers. This warning is retained; the normal-object focused proof
  separately verifies every initializer reference without blindness.
- Scoped declaration ratchet, port references, unique Source stems, rename
  ledger, draft compilation and whitespace checks all exit zero. Declaration
  inventory remains 7,483 banked disagreements, with none newly introduced.
- Fresh stock `rombuild.py -j16 --no-rom` at the repaired checkpoint exits zero
  in 246.734 seconds: 106/106 exact modules, all 11,334 Source-built functions,
  331 source-data and 239 BSS claims. Its nine symbol diagnostics equal the
  same-run scratch baseline, with zero new symbol or storage-alias errors.
  Global data remains 970 verified / 1,519 partial / one differing / 21 unnamed;
  this is not universal data acceptance. Normal ROM packaging was skipped;
  the same-run scratch baseline did build its 16-MiB image.

The class remains partially reconstructed. Raw counter/timer accesses, scalar
Fix12 boundaries, local resource wrappers, numeric/descriptive identifiers and
other inherited interfaces are not newly resolved by a provenance correction.
No new genuine method definition or original identifier recovery is claimed.
The old accepted review and byte controls do not accept this new Source by
themselves. Another actual agent must review the exact repaired head/base.

Canonical seven historical fixed findings (unchanged dictionaries):

```json
[
  {
    "disposition": "fixed",
    "id": "MENBO-RTTI-01",
    "kind": "provenance",
    "location": "src/actors/daMenbo_c.cpp:14",
    "reason": "Independent ROM and relocation reads give first word arm9:0x0209a764, second the name record, third ov002:0x021081c0. Revised wording matches all three.",
    "summary": "Identify the runtime RTTI vtable correctly."
  },
  {
    "disposition": "fixed",
    "id": "MENBO-VTABLE-01",
    "kind": "provenance",
    "location": "src/actors/daMenbo_c.cpp:20; config/tu_manifest.d/ov090/daMenbo_c.json:199",
    "reason": "Independent ROM read finds exactly slots0,3,6,9,12,16,17,18,19,29; both corrected descriptions list ten.",
    "summary": "Count every vtable slot targeting the TU."
  },
  {
    "disposition": "fixed",
    "id": "MENBO-MATRIX-01",
    "kind": "provenance",
    "location": "src/actors/daMenbo_c.cpp:193; src/actors/daMenbo_c.cpp:332",
    "reason": "Read complete src/MulMat4x3Mat4x3.c: its third argument receives the product. Source argument order and types are unchanged; only labels and explanation are repaired.",
    "summary": "Match declaration labels and scratch description to actual matrix helper."
  },
  {
    "disposition": "fixed",
    "id": "MENBO-RAYCAST-01",
    "kind": "provenance",
    "location": "src/actors/daMenbo_c.cpp:1084",
    "reason": "Complete InitResources review confirms only the level/mode branch bypasses DetectClsn; the revised comment now states this distinction.",
    "summary": "Separate the pre-raycast return from the surface-flag return."
  },
  {
    "disposition": "fixed",
    "id": "MENBO-STATE-01",
    "kind": "provenance",
    "location": "src/actors/daMenbo_c.cpp:578; src/actors/daMenbo_c.cpp:850",
    "reason": "Independent sinit and ROM PMF relocation review pairs entry02131608 with updater02131584 and entry02131db0 with updater02131c48. Animation handles match the unchanged calls.",
    "summary": "Use evidenced entry/updater pairings without unsupported state names."
  },
  {
    "disposition": "fixed",
    "id": "MENBO-RTTI-PADDING-01",
    "kind": "provenance",
    "location": "config/tu_manifest.d/ov090/daMenbo_c.json:199",
    "reason": "Fresh twelve-byte ROM name read contains ten encoded-name characters and exactly two trailing zeros total. The final manifest says terminator and padding; handoff preserves the finding as fixed.",
    "summary": "Count the RTTI name terminator and padding accurately."
  },
  {
    "disposition": "fixed",
    "id": "MENBO-CURRENT-BASE-01",
    "kind": "correctness",
    "location": "src/actors/daMenbo_c.cpp:309",
    "reason": "This is a base-validity finding, not a new runtime defect. The candidate contains tested base5e1b as an ancestor and preserves its D0 marker. Fresh independent current-base complete-object/TU/strict/static/full-ROM proof passes; the unchanged converted ratchet now passes at3016 versus baseline2993. Original blocked reason: Pinned main adds // @symbol _ZN9daMenbo_cD0Ev beside the D1 marker. The exact tested candidate lacks it. No defect is asserted in the six repaired provenance descriptions; current-base preservation and proof remain required.",
    "summary": "Preserve the landed D0 marker and validate the current source base."
  }
]
```

New current findings, retained exactly as independently reported before repair:

```json
[
  {
    "id": "MENBO-CURRENT-INIT-STATE-02",
    "kind": "provenance",
    "disposition": "unresolved",
    "location": "src/actors/daMenbo_c.cpp:859",
    "summary": "InitResources comment calls the selected state water rest, while both branches install the water-chase node.",
    "reason": "Both the mode2/course0x12 and surface0x20 branches install data_ov090_021344f4. Sinit and current state map pair this with entry02131db0/update02131c48; the water-rest node is02134504 with entry02131b94/update02131ac4. Runtime code is unchanged; correct only the descriptive text."
  },
  {
    "id": "MENBO-CURRENT-OWNERSHIP-PROSE-02",
    "kind": "provenance",
    "disposition": "unresolved",
    "location": "config/tu_manifest.d/ov090/daMenbo_c.json:1393",
    "summary": "Active externalized-vtable reason says the promotion stays text-only despite current owned initializer, ctor, data and BSS.",
    "reason": "Current intact-object policy retains .init/.ctor/.data/.bss. Vtable metadata remains externally licensed. Qualify the historical text-only boundary note and update the active reason without changing ownership, addresses, sections or any policy."
  }
]
```

Private current evidence: `build/menbo-retire1014/repair/` contains the actual
focused whole-object proof, prose-only input proof, per-gate terminal records
and ROM report. A final five-tree binding records the report commit. No public
push, PR merge or self-acceptance is performed by this producer.

---

The following handoff is the preserved historical record; its old candidate,
base and publication status are not current acceptance claims.

# Menbo provenance corrections after PR #2994

Input: `8f5b7274a11573c4ba50a41b66449da984927665`. PR #2994 was merged externally as `c6c1b71a420a20c27d7f1f845b2619b439157c75` while this repair was being reviewed. This candidate composes main `5e1b476856667904a074d1a8914877170f49cba0`, preserving the explicit D0 source marker landed separately in PR #3003. The earlier review of `cfa2e9ba` against `1e80857f` remains historical; fresh evidence binds this composition and base.

Independent review read all 24 promoted functions, their predecessor bodies, the unchanged class header, relevant callees, relocation rows, enrollment and baseline migrations. It found inaccurate new explanatory text without an introduced runtime regression.

- MENBO-RTTI-01: corrected the RTTI first word to the ABI runtime type-info vtable at arm9 `0x0209a764`; the third word still identifies the enemy base.
- MENBO-RTTI-PADDING-01: corrected the manifest to ten encoded-name characters followed by a terminator and one padding byte, matching the twelve ROM bytes.
- MENBO-VTABLE-01: corrected four in-run slots to ten, with the exact indices in source and manifest.
- MENBO-MATRIX-01: named matrix declaration parameters in the actual input/input/output order and corrected the description of the scratch destination. Types, argument order and executable statements are unchanged.
- MENBO-RAYCAST-01: distinguished the pre-raycast level/mode return from the surface-flag return after collision detection.
- MENBO-STATE-01: replaced unsupported state-entry names with the evidenced updater/animation pairings.

MENBO-CURRENT-BASE-01: preserved the landed D0 marker while composing the current source base. PR #3003 fixes the immediate converted-ratchet failure; the general classifier improvement in PR #3002 is no longer a dependency. No baseline is lowered here. This task corrects provenance; raw-offset accesses, anonymous helpers and mangled ABI bridges remain inherited reconstruction work, not newly solved methods or layouts.

Producer and independent verifier record exact object/link/static and full-ROM evidence in the task. Publication is not merge acceptance, and no main merge is requested by this handoff.
