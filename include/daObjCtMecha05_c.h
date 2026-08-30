#ifndef DAOBJCTMECHA05_C_H
#define DAOBJCTMECHA05_C_H

#include "types.h"

/* The ROM's RTTI identifies this as daObjCtMecha05_c derived directly from
 * dBgActor_c. Its own storage begins at 0x320; positions, angles, horizontal
 * speed, model, and collision members before that point are inherited.
 *
 * The factory's 0x394 allocation fixes the complete size. The shadow helper
 * identifies the final 0x30 bytes as one Matrix4x3: it builds a rotation,
 * writes the translation, and passes the same object to DropShadowScaleXYZ.
 */

#ifdef __cplusplus

#include "dBgActor_c.h"
#include "ShadowModel.h"

struct daObjCtMecha05_c : dBgActor_c {
    s32 mHomePosX;                     /* 0x320 -- snapshot of mPosX at InitResources */
    s32 mHomePosY;                     /* 0x324 -- snapshot of mPosY at InitResources */
    s32 mHomePosZ;                     /* 0x328 -- snapshot of mPosZ at InitResources */
    s32 mTravel;                       /* 0x32c -- path distance */
    s32 mPrevTravel;                   /* 0x330 -- prior path distance */
    s16 mStateTimer;                   /* 0x334 -- state countdown */
    u8  mState;                        /* 0x336 -- Behavior state, 0..3 */
    u8  pad_337[0x1];
    s32 mGroundY;                      /* 0x338 */
    ShadowModel mShadowModel;          /* 0x33c */
    Matrix4x3 mShadowMatrix;           /* 0x364 */

    /* --- vtable --- */
    /* Inline on purpose: when this class's vtable is instantiated, mwccarm
       emits the cartridge's D1 then D0 order without a homeless D2. */
    virtual ~daObjCtMecha05_c() {}

    int CleanupResources();
    int InitResources();
    int Behavior();
    int Render();

};

typedef char daObjCtMecha05_c_size_must_be_0x394[sizeof(daObjCtMecha05_c) == 0x394 ? 1 : -1];

#endif /* __cplusplus */

#endif /* DAOBJCTMECHA05_C_H */
