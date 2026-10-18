# KuriKing native metadata

Task `data-kuriking-metadata1018`, issue #4091, continues the global-data inventory
with two native actor profiles and compiler-owned class metadata. This is partial
TU reconstruction. The historical queue base/input is
`39e31d5aaea817b56e971f9fe389d0e3d98113ea`; initialized-boundary tooling is a
separate dependency, with independent tool and source acceptance required.

## Source and types

The existing `SpawnInfo<daKuriKing_c>` definition describes a 28-byte registry
entry: typed allocating factory, two u16 behavior/render priorities, u32 actor
flags, and four Q12 range values. The shared header records the framework readers
that establish these fields. It is included without copying or changing its
declaration. Both factories already exist as native C++ and need no casts.

`g_profile_KURIKING` at 0x02122e78 uses factory 0x02122838, priorities 198/22,
flags 0x34800000, and ranges 0, 0x100000, 0x3000000, 0x3000000.
`g_profile_KURIKING_VANISH` at 0x02122e94 uses factory 0x02122764, priorities
199/23, flags 0x24800002, and the same ranges. These established registry names
and consumer-derived field names are reconstructed identifiers, not a claim to
recover the original source spelling.

The compiler's own `_ZTI12daKuriKing_c` (12 bytes at 0x02122e30),
`_ZTS12daKuriKing_c` (15 bytes at 0x02122e3c), and `_ZTV12daKuriKing_c`
(132 bytes of storage at 0x02122eb0, with its 124-byte public address point at
0x02122eb8) become actual source providers. The existing native class and header
are preserved. Inherited metadata retains its canonical owner. Exactly two raw
definitions are new: the profiles. The three native metadata objects were
already emitted but previously discarded in favor of ROM providers.

## Complete ranges and linker boundaries

The new ranges are `.data.kuriMeta0` [0x02122e30,0x02122e4c) and
`.data.kuriMeta1` [0x02122e78,0x02122f34). Five objects contain 215 emitted bytes;
the complete ranges occupy 216 linked bytes. The first range contains 27 native
bytes and one explicitly licensed zero byte from terminal ALIGN(4). No source
padding array, widened string, or enlarged compiler symbol supplies that byte.
The name's config row explicitly states `byte[15]`.

The existing numeric identity `data_ov074_02122eb0` is a zero-size GLOBAL/NOTYPE
LCF symbol naming the full vtable's storage prefix. It is not a second eight-byte
compiler object. The ARM9 reference at 0x02090964 retains its overlay alternatives
71 and 74; OV071's same-address `g_profile_CASKET` is unchanged. The prefix is
proved as part of the complete 132-byte native vtable, separately from the
124-byte public provider request. The old DSD eight-byte OBJECT representation
and new zero-size LCF identity differ deliberately in symbol metadata.

The six existing claims remain: text [0x0211f000,0x0212290c), rodata
[0x0212292c,0x02122978), init [0x02122978,0x02122d70), ctor
[0x02122d70,0x02122d74), data [0x02122d84,0x02122e24), and BSS
[0x02122fe0,0x021231a0). The historical manifest note incorrectly called
0x02122e24 the RTTI start; the actual RTTI starts at 0x02122e30, after the
12-byte bone-index array. That earlier note is retained as history, not evidence.

## Evidence and limits

The producer compares every one of 122 prior raw definitions, 59 functions and
590 relocations with the base object. All remain unchanged; only the two
profiles are added. The raw candidate SHA256 is
`8b9b97f15add13f77a816c06fcffecc1f2536177d7e035f7711138d00c10d009`.
The base raw SHA256 is
`a68822ecef67faae0cee377e5eeb521abb44aceb9264ebd22e578d69bac70837`.

The strict focused checker reports 53 VERIFIED results and three known blind
results: each 212-byte factory has BLIND-1 and the 1016-byte initializer has
BLIND-31. These are not 56 strict passes. Complete normal-provider, linked-map
and retail-byte checks must cover both factories and the initializer, including
all 78 initializer relocations, its four-byte ctor entry, and the full vtable.
The eight-range scratch check covers 153 nontext relocations. Nine baseline
symbol diagnostics remain, with zero new errors; this is not a clean symbol
check. The declaration ratchet has 212 historical scoped disagreements and no
new disagreement or duplicated header declaration.

Failed experiments remain recorded privately: exact-emission admission rejected
27 bytes against the 28-byte section; splitting a one-byte ROM gap introduced
linker alignment and shifted subsequent data; an unsized final name row cannot
license terminal fill. None is a valid control or a passing source result.

## Remaining inventory

Four ranges remain actual DSD gap providers, not implicit source ownership:

| Range | Bytes | Evidence and next work |
| --- | ---: | --- |
| 0x0212290c..0x0212292c | 32 | Shared declaration ownership needs reconciliation. |
| 0x02122e24..0x02122e30 | 12 | Three int bone indices (1, 8, 10), copied for foot collision cylinders; researched but excluded. |
| 0x02122e4c..0x02122e78 | 44 | Float constants and a BTA pointer list; shared declarations remain under another live owner. |
| 0x02122f34..0x02122fe0 | 172 | Animation records with interior aliases used by SetAnim; complete type and ownership proof still needed. |

Existing free helpers, raw matrix/field accesses, state PMF stand-in and scalar
ABI bridges remain reconstruction debt. The existing BSS state table's trailing
24-byte alignment representation is unchanged, not newly justified here. PR
#3937 has a same-file proposal; integration must reconcile it explicitly. This
slice does not complete the entire TU or remove every ROM-supplied data byte.

## Producer result

The principal commands are:

```text
python tools/tubuild.py linkcheck --baseline --module ov074 -j16
python tools/tubuild.py linkcheck ov074/daKuriKing_c -j16
python tools/rombuild.py -j16 --data-provenance-requests build/requests.json --report-json build/kuri-production.json --data-json build/kuri-romdata.json
python tools/prepush_linkcheck.py --range 09da716a1d67ad6b93b40c046fa83f9fa135be5e..HEAD --json build/kuri-strict.json
python tools/check_decl_agreement.py --changed 09da716a1d67ad6b93b40c046fa83f9fa135be5e
python tools/source_coverage.py --check --base 09da716a1d67ad6b93b40c046fa83f9fa135be5e
python tools/port_refcheck.py
```

Private verification scripts preserve the object comparison and independently
check actual normal providers, complete linked payloads and all input hashes.

The separate tooling candidate is `09da716a1d67ad6b93b40c046fa83f9fa135be5e`. Its runtime files are identical
to the measured a3f24866 runtime; its additional commit contains documentation only.
The final-config no-source control, scratch and normal build each reproduce all
106 modules and full ROM SHA256
`d1506e90efae5e2d2cf119926a4ac2a291bd5ca78349d09d5024e1a918c478e8`.
The normal build proves all 56 requested providers and all 7,173 bound inputs
were rehashed. Full vtable, initializer, ctor, factories and all four actual DSD
gaps were checked separately. Source coverage increases by 216 linked bytes
with zero bytes returned to ROM. Style, declaration ratchet, port references,
rename ledger, TU conflicts and dead-reference checks pass their scoped gates.
The optional raw data diagnostic retains the pre-existing dCcAcPos vtable
difference; it is not a claim that every emitted object in the repository matches.

Independent tool/source review and committed-input verification remain required
before publication. The experiment record retains 58 findings, including
all 41 inherited source findings and relevant tool findings.

## Independent-review correction

The first source candidate `2ff356d05bae99687bda235ee2a6ee22a5361867`
was returned for two provenance corrections. DSD supports local symbols; the
initializer and ctor binding rewrites preserve this manifest's existing GLOBAL
identities, rather than work around an inability to express local symbols. Both
original explanations remain in the experiment history. The unchanged rewrite
rules still preserve the exact native initializer and ctor destinations.

The old standalone snapshot also called itself current while describing six
sections and discarded own metadata. It is now explicitly historical in its
entirety. The fresh eight-range linkcheck remains the active admission record;
normal actual-provider proof is separate. These edits change no source bytes,
configured ranges, compiler policy or linkcheck admission. Both findings remain
in the review history, and the descendant receives fresh committed-input proof.
