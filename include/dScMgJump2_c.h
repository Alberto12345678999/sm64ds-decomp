/* class dScMgJump2_c, real ROM name confirmed by tools/rtti_extract.py:
 * dScMgJump2_c : dScMgD3DBase_c, single edge, offset 0 (build/rtti.json).
 * Its own vtable is ov006:0x0213ccfc.
 *
 * SIZE 0x5a78. The factory is `MgBounceAndTrounce_Spawn` (ov006:0x020efaf0,
 * still `complete`/byte-matched -- this was a rename, not a rematch): its
 * body is `operator new(0x5a78)`, dScMgBase_c's constructor,
 * dScMgD3DBase_c's vtable, mSysTracker, then THIS class's vtable and every
 * member below. It had been carrying a wrong name, `_ZN8PathLift17BaseInit
 * ResourcesEv` -- neither a PathLift method nor a BaseInitResources; the
 * real `PathLift` class lives in ov002 (`_ZN8PathLiftD1Ev` and friends at
 * 0x020ef320..0x020eff18), and this was a name matched across an OVERLAY
 * BOUNDARY at a near-identical address. The identification comes from this
 * class's own MgBounceAndTrounce_SpawnInfo entry (ov006:0x0213cc7c): its
 * first field is a raw function pointer, and it points at exactly this
 * address -- same layout as MgBounceAndPounce_SpawnInfo pointing at
 * dScMgJump_c's already-named MgBounceAndPounce_Spawn, its sibling class
 * under the same base. "Bounce and Trounce" is the multiplayer half of
 * "Bounce and Pounce," per the mariowiki minigame list.
 *
 * mModel IS DELIBERATELY RAW BYTES, and this is the interesting contrast
 * with dScMgJump_c. The ROM's destructor here destroys the Model FIRST,
 * before all three arrays. A typed member is always destroyed AFTER the
 * user-written body, so a typed `Model mModel` could only ever produce
 * arrays-then-Model -- the opposite order. Left as raw bytes with an
 * explicit `_ZN5ModelD1Ev` call in the measured position instead, the same
 * reasoning include/dScMgRoulette_c.h records for its own two models. The
 * factory's `_ZN5ModelC1Ev(p + 0x5a14)` and sizeof(Model) == 0x50 still fix
 * the offset and the extent.
 *
 * THE DESTRUCTOR IS NOT DEFINED INLINE -- a leaf. No separate operator
 * delete is needed: dScMgD3DBase_c, the immediate base, provides one. */
#ifndef DSCMGJUMP2_C_H
#define DSCMGJUMP2_C_H
#include "dScMgD3DBase_c.h"

extern "C" void __destroy_arr(void *base, int count, int stride, void *dtor);
extern "C" void _ZN5ModelD1Ev(void *p);
extern "C" void func_ov006_020c6f3c(void);
extern "C" void func_ov006_020c893c(void);
extern "C" void func_ov006_020eed64(void);

struct dScMgJump2_c : dScMgD3DBase_c {
    virtual ~dScMgJump2_c();

    u8  pad_5004[0x8];    /* 0x5004 -- no matched access in this class's methods */
    u8  mArray1[0x228];   /* 0x500c -- 3 * 0xb8,  elem dtor func_ov006_020c893c */
    u8  mArray2[0x5a0];   /* 0x5234 -- 6 * 0xf0,  elem dtor func_ov006_020c6f3c */
    u8  mArray3[0x240];   /* 0x57d4 -- 0x10 * 0x24, elem dtor func_ov006_020eed64 */
    u8  mModel[0x50];     /* 0x5a14 -- a real Model, raw bytes; see banner */
    s32 unk_5a64;         /* 0x5a64 */
    u8  pad_5a68[0x4];    /* 0x5a68 */
    u32 unk_5a6c;         /* 0x5a6c */
    u8  pad_5a70[0x8];    /* 0x5a70 -- no matched access */
};

typedef char dScMgJump2_c_size_must_be_0x5a78[sizeof(dScMgJump2_c) == 0x5a78 ? 1 : -1];

#endif
