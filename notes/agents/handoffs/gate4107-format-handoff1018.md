# PR #4107 formatting handoff

Original contributor head: `57926327ad3851d118061aaf28a69e3cf7cb6a6d`. Source review anchor: `5b43fb8862985abbe781bf190184b42f750914bf`.
Author handoff: https://github.com/tangosdev/sm64ds-decomp/pull/4107#issuecomment-6251695951. The author confirmed no unpublished work or further edits and released all thirteen legacy claims. Fresh REST and v2 checks were clear before these two separate scoped producer claims.

Task: `gate4107-format-handoff1018`. This descendant preserves the original contributor commits. Only the reviewed whitespace patch and this handoff are added; all source preprocessing tokens are identical to the original head. Shared headers, tooling, configuration and declaration baseline remain untouched.

Fresh proof: 7 complete before/after raw ELF objects are byte-identical under pinned compiler 2004/b56; 7/7 relocated functions verified; source style zero findings and zero deferrals; full changed declaration ratchet has no new disagreements; port references 247/247 resolve. Existing banked declaration diagnostics remain, and are not claimed fixed.

Private artifacts in this wired worktree: `build/format-proof.json`, `build/strict.json`, `build/style.json`, `build/declaration.log`, and `build/producer-findings.json`. Reproduce raw equality with `python build/prove-format.py`. No full ROM rebuild was repeated for whitespace-only changes. The original private pass is historical evidence; the repaired head still requires its own live public/private checks before landing.

Independent source review is pending. This producer report does not grant source acceptance or merge approval.

## Retained source findings

- `gate4107-source-01` (fixed): Vector3 is three Fix12i/s32/signed-int coordinates in C, matching removed local int x/y/z structs. C++ constructors/destructor are guarded by __cplusplus; none of these seven C files gains C++ lifecycle behavior.
  Original bounded source inquiry accepted. Formatting requirement is resolved by token-identical patch and exact complete raw-object proof; original-body correction, if cited, was already applied by the maintainer.
- `gate4107-source-02` (fixed): a730 retains named basePosition/offset/velocity and typed PtclDef/Child/List pointers, every offset, arithmetic expression, callback and linked-list action. Only vector type and compiler annotation change.
  Original bounded source inquiry accepted. Formatting requirement is resolved by token-identical patch and exact complete raw-object proof; original-body correction, if cited, was already applied by the maintainer.
- `gate4107-source-03` (fixed): b460/b81c use identical coordinate math and structs; CrossVec3 keeps the callee-compatible local three-int Vec3_Fix12 twin and pointer casts. NormalizeVec3 and MulVec3Mat3x3 declarations now match definitions. No corresponding include header declaration exists.
  Original bounded source inquiry accepted. Formatting requirement is resolved by token-identical patch and exact complete raw-object proof; original-body correction, if cited, was already applied by the maintainer.
- `gate4107-source-04` (fixed): b460/b81c/bbd8/be40 MulVec3Mat4x3 signatures now use existing common.h Matrix4x3 (12 s32 words); the same existing matrix address is cast, with no matrix storage or indexing change.
  Original bounded source inquiry accepted. Formatting requirement is resolved by token-identical patch and exact complete raw-object proof; original-body correction, if cited, was already applied by the maintainer.
- `gate4107-source-05` (fixed): c304 retains typed Particle and Node pointers, coordinate copies, RNG, lifetime and color logic; only two vector field types change.
  Original bounded source inquiry accepted. Formatting requirement is resolved by token-identical patch and exact complete raw-object proof; original-body correction, if cited, was already applied by the maintainer.
- `gate4107-source-06` (fixed): c584 shared scalar typedefs match the removed ones; named ParticleElement and ParticleSystem pointer views and offset/velocity x/y/z are retained. NormalizeVec3 receives the same addresses through definition-compatible int pointers.
  Original bounded source inquiry accepted. Formatting requirement is resolved by token-identical patch and exact complete raw-object proof; original-body correction, if cited, was already applied by the maintainer.
- `gate4107-source-07` (deferred): Existing local C particle views, opaque callbacks, raw field placeholders, integer-array math interfaces and CrossVec3 twin remain partial reconstruction. This PR does not claim a class/TU promotion or resolve that pre-existing debt.
  Original bounded finding retained verbatim; existing partial reconstruction is outside this formatting-only repair.
- `gate4107-format-identity-001` (fixed): Changed-line formatting failures repaired without changing any preprocessing token or complete compiled object.
  Pinned compiler produced 7 byte-identical before/after raw ELF objects; all functions independently pass fresh strict relocation checks. No header, baseline, config or tool edit.
