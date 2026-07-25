//cpp
// NONMATCHING: WRONG-DEST relocation, not a byte-reproducing match.
// The instruction bytes match, but the tail-call at +0x8 relocates to _ZN14BlendModelAnimD1Ev (0x02016690)
// while the ROM branches to _ZN14BlendModelAnimD0Ev (0x02016644). A deleting-destructor thunk that jumps
// to the complete destructor would destroy the object and never free it, so this is a real
// defect, not a naming nit - the match gate misses it because it wildcards relocated words.
//
// The thunk is COMPILER-GENERATED from the class shape below, so no symbol rename fixes it:
// mwccarm emits a D1-targeting D0 thunk for this shape. Tried a bare out-of-line definition,
// an explicit delete site to force the deleting variant, and a class-level operator delete -
// all three still relocate to D1. The tell is that _ZThn80_N14BlendModelAnimD1Ev
// is byte-identical source and VERIFIES, i.e. this shape only ever yields the D1 thunk.
// Recovering the real class layout (base order / vtable shape) is the open work.
struct Base1 { int pad[19]; virtual ~Base1(); virtual void f1(); };
struct Base2 { int b; virtual ~Base2(); virtual void g1(); };
struct BlendModelAnim : Base1, Base2 { virtual ~BlendModelAnim(); };
BlendModelAnim::~BlendModelAnim() {}
