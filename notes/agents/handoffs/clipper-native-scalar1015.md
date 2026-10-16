# Native clipper scalar continuation for issue 2410

This checkpoint follows the independently accepted Monkey lifetime/matrix slice (PR #3896, fc20639c19766d05227360ee5617f5246f3887c1), which contains remote main 53dc648eaf7d24847f461a193a3f81203cf4d098. It does not complete Monkey or close issue #2410.

The arm9 0x02015560 wrapper becomes a genuine dClipper::TransformAndClip member with the canonical Fix12i scalar parameter. TransformAndClip and radius are inferred descriptive names: its body transforms the point to view space, then calls the existing sphere/frustum clipping routine. There is no perspective divide. The other legacy Fix12 boundary stays explicit; the common.h/math/Matrix.h representation debt remains.

Native callers include the owning header and use the real dClipper singleton. UnknownVsPlayer's former int[2] output was too small for the three-component result. A real Vector3 output fixes that extent while reproducing the complete TU and initializer. Camera's retained C-linkage handler declares the same singleton type and passes its address; its entire raw ELF is literally unchanged.

The symbol at 0x02015560 keeps its address, size and original authors. Canonical symbol, attribution, verification ledger and TU records follow the compiler-confirmed native mangling. Compiler-local mappings in Monkey and dEntObj are individually enumerated; prior admission reasons and canonical destinations are retained. No blanket local-symbol admission is added.

Prepublication checkpoint: the independent scratch preview strictly verified 196/196 functions (including the dEntObj initializer) in both controls and candidates with zero blind relocations, and compared all seven complete emitted TUs including storage/typed graphs. Camera adds an eighth complete object with literal equality. These preview results are not final production acceptance. Tree remains owned by its existing producer: its API-only source commit must be adopted without the unfinished grouped Actor header dependency. Production full-ROM, declaration agreement across all callers, exact-head independent Source and CI still have to pass before this continuation is ready.

Findings carried forward: all 40 predecessor findings remain recorded in queue history. CLIPPER-RESULT-EXTENT-01 is a fixed correctness finding for the undersized dEntObj result. CLIPPER-SINGLETON-DECL-01 tracks the declaration gate's camera and Tree singleton disagreements; Camera is corrected here, Tree remains pending its owner's contribution at this checkpoint.
