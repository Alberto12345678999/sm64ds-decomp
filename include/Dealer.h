#ifndef DEALER_H
#define DEALER_H

#include "types.h"

/* Dealer, Luigi dealing in the card games: the 0x270-byte record
 * Dealer_Construct builds and the Dealer_* helpers in
 * src/minigames/unit020bfec0.cpp animate. The name is coined. Its model is
 * MG/luigi_d.bmd, and the thirteen animation slots resolve
 * (tools/asset_catalog.py) to MG/luigi_d_wait, shuffle_start, shuffle,
 * deal_start, deal, deal_end, deal_end2, deal_wait, throw, win_start, win,
 * win_end and lose.bca. A layout view only: the helpers are free functions
 * over a char* record and read it through their DEALER() cast. */
struct DealerFile {
    s32 handle; /* +0x0 */
    s32 file;   /* +0x4 -- the loaded file, 0 until loaded */
};

enum DealerAnim {
    DEALER_ANIM_WAIT,
    DEALER_ANIM_SHUFFLE_START,
    DEALER_ANIM_SHUFFLE,
    DEALER_ANIM_DEAL_START,
    DEALER_ANIM_DEAL,
    DEALER_ANIM_DEAL_END,
    DEALER_ANIM_DEAL_END2,
    DEALER_ANIM_DEAL_WAIT,
    DEALER_ANIM_THROW,
    DEALER_ANIM_WIN_START,
    DEALER_ANIM_WIN,
    DEALER_ANIM_WIN_END,
    DEALER_ANIM_LOSE,
    DEALER_ANIM_COUNT
};

struct Dealer {
    s32 mState[2]; /* 0x000 -- the current state's member-pointer record */
    Vector3 mPos;  /* 0x008 */
    s16 mRot[3];   /* 0x014 */
    s16 mHand; /* 0x01a -- picks deal_end (0) or deal_end2 (2); 1 makes PlayLose play deal_end first */
    u8 mModel[0x1c];       /* 0x01c -- a BlendModelAnim, running to 0x08c */
    u8 mModelMatrix[0x30]; /* 0x038 -- mModel's Matrix4x3 (Model +0x1c), set by ResetMatrices */
    u8 pad_068[0x4];       /* 0x068 -- the rest of mModel's Model */
    /* mModel's dExtFrameCtrl_c (ModelAnim +0x50), which the state functions
       test with Finished and WillHitFrame. */
    s32 mModelFrame[4]; /* 0x06c */
    s32 mAnim;          /* 0x07c -- the BCA file mModel plays */
    u8 pad_080[0xc];    /* 0x080 */
    u8 mTable[0xc];     /* 0x08c -- a Model, running to 0x0dc */
    /* mTable's material table (Model +0xc, ModelComponents::materials):
       Load clears and sets flags on materials 0, 4 and 5. */
    s32 mTableMaterials;   /* 0x098 */
    u8 pad_09c[0xc];       /* 0x09c */
    u8 mTableMatrix[0x30]; /* 0x0a8 -- mTable's Matrix4x3 (Model +0x1c), set by ResetMatrices */
    u8 pad_0d8[0x4];       /* 0x0d8 -- the rest of mTable */
    u8 mWalker[0xf8];  /* 0x0dc -- a MascotWalker */
    s32 mDealtCount;   /* 0x1d4 -- a short the deal loop bumps once per card, or 0 */
    s16 mShuffleLeft;  /* 0x1d8 -- shuffle repeats left */
    s16 mDealDoneAt;   /* 0x1da -- the repeat that calls OnDealDone */
    s16 mShuffleRound; /* 0x1dc -- 0 for the first hand (four shuffles), then one; cycles 0..5 */
    s16 mDealLeft;     /* 0x1de -- deal repeats left */
    s16 mLampTimer;    /* 0x1e0 */
    s16 mLampPattern;  /* 0x1e2 -- three lamp bits, cycling 1..7 */
    s16 mLightAngle;   /* 0x1e4 -- turns 0x400 a frame */
    s16 mReserved;     /* 0x1e6 -- only Dealer_Construct writes it (to 0) */
    DealerFile mModelFile;                /* 0x1e8 -- luigi_d.bmd */
    DealerFile mTableFile;                /* 0x1f0 */
    DealerFile mAnims[DEALER_ANIM_COUNT]; /* 0x1f8 */
    s32 mModelData;                       /* 0x260 -- the loaded luigi_d.bmd */
    s32 mTableData;                       /* 0x264 */
    s32 mShuffleSoundPlayed;              /* 0x268 -- sound 0x139, once per shuffle */
    s32 mDealSoundPlayed;                 /* 0x26c -- sound 0x13a, once per deal */
};

#ifndef SM64DS_PLATFORM_PC
typedef char DealerFile_size_must_be_0x8[sizeof(DealerFile) == 0x8 ? 1 : -1];
typedef char Dealer_size_must_be_0x270[sizeof(Dealer) == 0x270 ? 1 : -1];
#endif

#endif
