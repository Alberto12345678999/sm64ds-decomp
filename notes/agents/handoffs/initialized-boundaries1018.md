# Initialized linker boundaries

Task `tools-initialized-boundaries1018`, issue #4094, starts from
`39e31d5aaea817b56e971f9fe389d0e3d98113ea`. This tooling change does not enroll
source, change configured ranges, or accept the private KuriKing source fixture.
The KuriKing source producer supplied early tool review findings. A separate
session performs final independent tool verification; KuriKing source will
receive its own independent review after adopting the accepted tool.

The compiler emits the KuriKing RTTI as 12 bytes and its type name as 15 bytes.
The complete logical linker section occupies 28 bytes. The prior exact-extent
check rejected this honest claim because it modeled 27 emitted bytes. A separate
one-byte ROM gap was also incorrect: ALIGNALL(4) aligned that provider before
placing its byte and shifted the following section. A pinned native-linker probe
demonstrates that the generated terminal `. = ALIGN(4);` supplies one zero byte
without changing either compiler object or its symbol sizes. Both failed source
trials remain private evidence; neither is used as a valid baseline.

The optional `terminal_linker_fill` section policy accepts exactly
`{"alignment": 4, "value": 0}`. It licenses one to three zero bytes only when the
source owns the complete logical initialized section. A full configured symbol
and relocation census must show that no symbol occupies the fill and no
relocation occupies or targets it. Retail bytes must be zero. For fill licensing,
an unsized initialized config row is conservatively treated as extending to its
next configured address or logical section end; it is never treated as an
explicit zero-size identity. Thus an unsized final type-name row refuses fill,
while RTTI bounded by the following explicitly sized name remains valid. The
actual generated LCF must select the sole provider between the matching module markers
and end with ALIGN(4). Wildcard, list and unknown selector syntax is refused;
the guard examines the entire LCF for competing selectors. This conservative
policy does not support alternative linker scripts merely because they might
produce equivalent output.

The comparison view includes licensed linker fill, while `emittedBytes` remains
the physical compiler contribution and `linkedBytes` includes the fill. No ELF
payload, section size, alignment or symbol size is extended. Named data-section
routing still performs only its previously accepted routing operation.

The same fixture has a complete 132-byte native vtable at `0x02122eb0` and a
124-byte public address point at `0x02122eb8`. An incoming configured identity
names the storage prefix. Existing initialized-interior handling starts at the
public symbol and therefore cannot expose this prefix. The separate existing
`storage_alias` ELF mechanism can emit an exact eight-byte OBJECT alias, as
confirmed against a successful 200-byte control, but normal automatic admission
still refuses that mechanism because its baseline bootstrap would be circular.
That guard is retained.

The optional `initialized_prefix_aliases` entry contains only `symbol` and
`vtable` names and requires an explicit full-storage vtable row in `data`.
It requests a zero-size LCF identity, not an additional emitted
object. The new proof requires all of the following:

- One actual source provider in the complete linker object population, with a
  fresh successful owned-section proof bound to its bytes, claims and manifest.
- A dedicated initialized vtable section: exactly eight bytes before the public
  symbol, the declared complete storage extent, and no competing substantive
  symbols or configured identities anywhere in that storage.
- The exact zero/addend-zero ABS32 RTTI preamble, no overlapping prefix
  relocations, and a unique same-source RTTI provider whose native binding,
  visibility, claim and computed placement agree with its manifest and config.
- Recomputed prepared-object section placement and unique same-module configured
  public/prefix homes. A manifest address alone is insufficient.

The final identity is GLOBAL/NOTYPE, size zero, in OV074. The successful control's
original configured prefix symbol is GLOBAL/OBJECT, size eight. These metadata
representations are deliberately different. Full 132-byte provider storage and
the eight prefix bytes are proved separately from identity preservation.

Both ordinary scratch and normal builds call the same boundary planner after
object preparation and before linking. Baseline controls pass an empty source
policy population and retain DSD providers. Malformed opt-ins are rejected by
scratch claim parsing and normal intact-object admission. The boundary helper,
existing alias helper and alignment helper are explicit baseline/provenance
inputs. Public tests reside in existing CI-wired test modules; no workflow file
or unrelated source is changed.

Early review reproduced an unsupported `*(.data*)` selector bypass in the first
private checkpoint. The final grammar guard rejects this and section lists,
patterns and wrappers; the rejected checkpoint remains historical evidence.
The second review finding reproduced an unsized final `data(any)` name being
treated as zero storage. An actual compiler-object preparation probe now rejects
that exact mutation and accepts the restored 15-byte name; its earlier acceptance
is retained as rejected evidence.
The full test population and final runtime results are recorded in the adjacent
experiment. Existing predecessor findings remain there with their historical
scope; this tool does not retroactively accept those source fixtures.

Private reproduction material is under
`C:/tmp/sm64ds-initialized-boundaries1018/build` and the separately wired
`C:/tmp/sm64ds-kuri-boundary-fixture1018`. The latter contains four authorized
KuriKing source/config fixture changes, which are excluded from this tool commit.
Its normal provider proof covers the actual default build, while its explicit
final audit checks module bytes, physical/linker extents, the complete vtable and
the zero-size alias in the final ELF. Independent review and source acceptance
remain separate gates. No merge is performed by this work.

Producer validation at runtime checkpoint
`a3f248666800895f5d69099ef9dfaed375d9c7cf` passes 212 focused tests, a fresh
source-independent control, the eight-range scratch link, and the normal build
with 56 actual provider requests. All 106 modules and the complete ROM reproduce
(`d1506e90efae5e2d2cf119926a4ac2a291bd5ca78349d09d5024e1a918c478e8`).
The final module-byte audit proves both new ranges, all 132 vtable bytes and the
single terminal zero; all recorded input hashes were rechecked. Nine pre-existing
strict-symbol diagnostics remain, with zero new errors. The optional raw-data
scanner still reports the existing dCcAcPos vtable identity in two legacy objects;
that diagnostic is not described as an all-data pass. The final tool commit adds
only this handoff and its experiment after the runtime checkpoint; tool blobs are
identical to the measured inputs.
