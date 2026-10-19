# Raw data measurements and compiler-local names

Task: `tools-raw-data-locals1017`. Base:
`1b98141e598440a0432317b58678f3c5c088d558`. This is a tooling continuation of
`title-raw-local-resolution-001` on issue #4052, separate from Title source PR
#4060. It changes neither source enrollment nor linker inputs.

The raw scanner previously resolved compiler-generated `@NNN` names through a
global registry before applying the producing TU's licensed names. At Title head
`11f6228ca9e30c7ae88825672d4938ff867ba51c`, 46 table pointers consequently resolved
to unrelated globals and eight remained blind. Its private CI failed the data
ratchet even though all 11 affected functions and all 106 modules passed.

`check_object` now selects the rename policy by the exact source path, validates
it through the shared production admission rule, checks the function population,
and renames an in-memory copy using the existing ELF rewrite. Mapped targets use
their manifest module's registry entry. Missing canonical homes and unmapped
local symbols remain unresolved. The original compiler output is not modified.
Ambiguous or rejected policies produce an explicit diagnostic and retain the
original measurements, so rejection cannot erase an existing differing body.

The actual Title object SHA-256 is
`d445fde9a3d061c24f09a248bdc28e8105d7567175acfee32e5554265df6d1a3`.
Old and new scanners use the same immutable Title configuration and ROM inputs.
The table changes from 400 compared bytes, 184 differing bytes and eight blind
words to all 432 bytes VERIFIED with zero blind words. The other ten emitted
records are identical. This diagnoses and repairs the scanner; it is not new
source-byte or provider acceptance.

Thirteen new synthetic ELF tests cover local literals, cross-overlay name collisions,
source-path isolation, missing homes, rejected mappings, missing definitions,
ambiguous policies, separator normalization and unlicensed local references.
All 34 scanner tests, 27 owned-function rename tests and 39 rombuild tests pass.
The five legacy relocation-rename tests retain one baseline failure: an old test
expects longer names to be refused, while the existing ELF rewrite supports them.
The untouched control exhibits the identical failure; it is not repaired here.

The first full-build probe correctly exposed an incomplete local-symbol policy: two
existing 60-byte state tables lost coverage because their named strings were owned
but not renamed. That probe is retained as rejected evidence. The corrected policy
requires a unique owned row whose module address and size agree with the native
local definition. Fresh PathLift and PowerUpItem objects now preserve every prior
measurement, including both complete tables; negative size/address/duplicate-row
tests retain unresolved references.

Final normal production passes all 106 modules, 11,334 functions, 338 data claims
and 245 BSS claims, with the full retail ROM SHA-256
d1506e90efae5e2d2cf119926a4ac2a291bd5ca78349d09d5024e1a918c478e8.
The complete scanner summary, including every verified and differing identity,
is identical to the clean exact-base control: 974 verified, 1,559 partial, one
differing and 15 unnamed symbols, 49,088 verified bytes. All 5,297 object records
contain zero rename-refusal diagnostics. The fresh baseline retains nine symbol
errors and the candidate adds none. Independent review and CI remain separate.
The pre-existing unrelated `dCcAcPos_c` raw-data diagnostic is not waived or fixed.
Direct calls to `verify_data_symbol` without a source context retain their existing
behavior; source-aware callers should use `check_object`. This change does not
claim recovery of original data names or complete historical TU boundaries.
