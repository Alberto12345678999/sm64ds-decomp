#ifndef DASETSE_C_H
#define DASETSE_C_H

#include "dActor_c.h"

/* daSetSE_c_Spawn allocates 0xd8 bytes and constructs only the
 * dActor_c base. Behavior stores the active long-sound handle in the sole
 * derived word at 0xd4; the effect selector is inherited param1 at 0x08.
 */
struct daSetSE_c : dActor_c {
    u8  pad_0d0[0x4];
    u32 mSoundHandle;       /* 0x0d4 */

    virtual ~daSetSE_c();

    virtual s32 InitResources();
    virtual s32 CleanupResources();
    virtual s32 Behavior();
    virtual s32 Render();
    virtual void OnPendingDestroy();
};

typedef char daSetSE_c_size_must_be_0xd8[
    sizeof(daSetSE_c) == 0xd8 ? 1 : -1];

#endif /* DASETSE_C_H */
