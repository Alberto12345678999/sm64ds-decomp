#ifndef DAOBJBK_ROTEBAR_C_H
#define DAOBJBK_ROTEBAR_C_H

#include "types.h"
#include "dBgActor_c.h"

extern "C" void *_ZN7fBase_cnwEj(unsigned size);

/**
 * Whomp's Fortress rotating bar (profile BK_ROTEBAR). Factory
 * allocates 0x324 = sizeof(dBgActor_c) plus mPauseTimer / mTurnSound.
 * Pauses 0x3c frames, then steps yaw by 0x100 until
 * (mPrevAngleY & 0x7fff) == 0 -- a half turn -- and pauses again.
 *
 * `daObjBk_Rotebar_c` is the RTTI name. Direct base is dBgActor_c.
 */
struct daObjBk_Rotebar_c : dBgActor_c {
    s8  mPauseTimer;   /* 0x31e -- 0x3c; DecIfAbove0_Byte gates the turn */
    s32 mTurnSound;    /* 0x320 -- recycled Sound::PlayLong handle */

    /* Inline empty dtor: mwccarm emits D1 then D0, no D2.
     * Both bodies are short because the chain is short: this class's vptr
     * store, then dBgActor_c's -- inlined, its destructor is defined in its
     * class body -- then dBgActor_c's Model and dBgW_KcMbg, then dActor_c. This
     * class adds no member with a destructor of its own. D0's trailing
     * deallocation is the inherited inline operator delete, which is why
     * nothing in the source names a heap.*/
    // @symbol _ZN17daObjBk_Rotebar_cD1Ev
    // @symbol _ZN17daObjBk_Rotebar_cD0Ev
    virtual ~daObjBk_Rotebar_c() {}

    s32 InitResources();      /* slot  0 */
    s32 Behavior();           /* slot  6 */
    s32 Render();             /* slot  9 */
    s32 CleanupResources();   /* slot  3 */

    /* size_t == unsigned long here; unsigned int is illegal. */
    static void *operator new(size_t size) {
        return _ZN7fBase_cnwEj((unsigned)size);
    }
};

#ifndef SM64DS_PLATFORM_PC
/* ROM layout under mwccarm; host ABI divergence is tracked separately. */
typedef char daObjBk_Rotebar_c_size_must_be_0x324[
    sizeof(daObjBk_Rotebar_c) == 0x324 ? 1 : -1];
#endif

#endif /* DAOBJBK_ROTEBAR_C_H */
