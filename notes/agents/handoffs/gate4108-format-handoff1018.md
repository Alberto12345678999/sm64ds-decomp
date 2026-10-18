# PR #4108 formatting handoff

Original contributor head: `c9d05a4f57b30a434c25fc10d62d0cfeb6608fb1`. Source review anchor: `5b43fb8862985abbe781bf190184b42f750914bf`.
Author handoff: https://github.com/tangosdev/sm64ds-decomp/pull/4107#issuecomment-6251695951. The author confirmed no unpublished work or further edits and released all thirteen legacy claims. Fresh REST and v2 checks were clear before these two separate scoped producer claims.

Task: `gate4108-format-handoff1018`. This descendant preserves the original contributor commits. Only the reviewed whitespace patch and this handoff are added; all source preprocessing tokens are identical to the original head. Shared headers, tooling, configuration and declaration baseline remain untouched.

Fresh proof: 6 complete before/after raw ELF objects are byte-identical under pinned compiler 2004/b56; 6/6 relocated functions verified; source style zero findings and zero deferrals; full changed declaration ratchet has no new disagreements; port references 247/247 resolve. Existing banked declaration diagnostics remain, and are not claimed fixed.

Private artifacts in this wired worktree: `build/format-proof.json`, `build/strict.json`, `build/style.json`, `build/declaration.log`, and `build/producer-findings.json`. Reproduce raw equality with `python build/prove-format.py`. No full ROM rebuild was repeated for whitespace-only changes. The original private pass is historical evidence; the repaired head still requires its own live public/private checks before landing.

Independent source review is pending. This producer report does not grant source acceptance or merge approval.

## Retained source findings

- `gate4108-source-01` (fixed): Six C initializers use existing shared three-signed-int Vector3 layout; no C++ constructors/destructors are implicitly introduced. Existing explicit destructor registrations remain unchanged.
  Original bounded source inquiry accepted. Formatting requirement is resolved by token-identical patch and exact complete raw-object proof; original-body correction, if cited, was already applied by the maintainer.
- `gate4108-source-02` (fixed): Bodies are identical after V3-to-Vector3 spelling and two OV006 negative-literal cast removals, ignoring whitespace/comments. Every coordinate constant, store order, resource handle and destructor registration target is preserved.
  Original bounded source inquiry accepted. Formatting requirement is resolved by token-identical patch and exact complete raw-object proof; original-body correction, if cited, was already applied by the maintainer.
- `gate4108-source-03` (fixed): OV006 unsigned-coordinate local view becomes signed fixed-point Vector3. Two direct x stores now assign representable negative integers rather than implementation-defined unsigned-to-signed conversions. Ten pre-existing unsigned int pointer slot writes remain unchanged; no named coordinate was replaced by array indexing in this PR.
  Original bounded source inquiry accepted. Formatting requirement is resolved by token-identical patch and exact complete raw-object proof; original-body correction, if cited, was already applied by the maintainer.
- `gate4108-source-04` (fixed): OV021/OV102 volatile Vector3 pointers preserve volatile qualification and x/y/z writes exactly. OV019/OV062/OV078 existing pointer and resource declarations remain intact.
  Original bounded source inquiry accepted. Formatting requirement is resolved by token-identical patch and exact complete raw-object proof; original-body correction, if cited, was already applied by the maintainer.
- `gate4108-source-05` (fixed): Baseline changed exactly five symbols: two OV019 stale rows removed because callers already use Vector3; three V3 rows rekeyed Vector3 with identical scalar-versus-array disagreement populations. No unrelated exemption or new mismatch is banked.
  Original bounded source inquiry accepted. Formatting requirement is resolved by token-identical patch and exact complete raw-object proof; original-body correction, if cited, was already applied by the maintainer.
- `gate4108-source-06` (deferred): sTrmpGoalSlots, OV021 first vector, OV062 first vector retain scalar-versus-array disagreements. Existing handwritten destructor registration and raw initializer views remain partial reconstruction; no promotion or recovered original type extent is claimed.
  Original bounded finding retained verbatim; existing partial reconstruction is outside this formatting-only repair.
- `gate4108-source-07` (fixed): 48 formatting findings in OV021 lines50/53/56 and OV102 lines38/41/44 (six blocks), zero deferrals. Proposed ignored patch touches only those two files and retains every preprocessing token.
  Original bounded source inquiry accepted. Formatting requirement is resolved by token-identical patch and exact complete raw-object proof; original-body correction, if cited, was already applied by the maintainer.
- `gate4108-source-08` (fixed): PR body says current --update writes a shape without top-level known. Exact head tools/check_decl_agreement.py write_baseline explicitly writes both _comment and known, and --update calls that writer. The alleged missing-known behavior is not supported by this head; correct the body or identify a different historical tool/artifact. The small manual baseline diff itself remains narrowly valid; no whole-tree rebaseline is requested.
  Original bounded source inquiry accepted. Formatting requirement is resolved by token-identical patch and exact complete raw-object proof; original-body correction, if cited, was already applied by the maintainer.
- `gate4108-format-identity-001` (fixed): Changed-line formatting failures repaired without changing any preprocessing token or complete compiled object.
  Pinned compiler produced 6 byte-identical before/after raw ELF objects; all functions independently pass fresh strict relocation checks. No header, baseline, config or tool edit.
