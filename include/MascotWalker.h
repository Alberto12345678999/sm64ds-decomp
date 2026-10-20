#ifndef MASCOTWALKER_H
#define MASCOTWALKER_H

#include "types.h"

/* MascotWalker, the small figure that walks the card table's paths in the card
 * games (the dealer embeds one at +0xdc, which fixes the 0xf8 size). The name
 * is coined. A layout view only: the MascotWalker_* helpers in
 * src/minigames/unit020bfec0.cpp are free functions over a char* record and
 * read it through their WALKER() cast. Unnamed regions are touched in one
 * place at most, or sit inside an embedded object. */
struct MascotWalker {
    u8 pad_00[0xc];   /* 0x00 */
    s32 mPauseAnim;   /* 0x0c -- the BCA file Load starts and StartPause restarts */
    u8 pad_10[0x4];   /* 0x10 */
    s32 mWalkAnim;    /* 0x14 -- the BCA file StartNextPath restarts */
    u8 mModel[0x1c];  /* 0x18 -- a BlendModelAnim, running to 0x88 */
    u8 mMatrix[0x30]; /* 0x34 -- mModel's Matrix4x3 (Model +0x1c), set by UpdateMatrix */
    u8 pad_64[0x24];  /* 0x64 -- the rest of mModel */
    /* Built by Construct, InitCylinder'd by Load and InitModel'd on mMatrix by Draw. */
    u8 mShadow[0x28]; /* 0x88 -- a dExtShadowModel_c */
    s32 mPath;        /* 0xb0 -- the path walked: a point count, then the points */
    s32 mState[2];    /* 0xb4 -- the current state's member-pointer record */
    /* Load sets all three to 0x1000 (1.0), beside mPos and the angles; nothing
       in this file reads it back. */
    Vector3 mScale;   /* 0xbc */
    Vector3 mPos;     /* 0xc8 */
    Vector3 mDir;     /* 0xd4 -- unit vector toward the next point */
    s32 mPathPoint;   /* 0xe0 -- the point being walked to */
    s32 mPathIndex;   /* 0xe4 -- which of the four paths, cycling */
    /* Load copies data_020a0edc's x/y/z into 0xe8/0xea/0xec, the same start
       rotation Dealer_Load copies into Dealer::mRot. */
    s16 mAngleX;      /* 0xe8 */
    s16 mAngleY;      /* 0xea -- eased toward mTargetAngle */
    s16 mAngleZ;      /* 0xec */
    s16 mTargetAngle; /* 0xee -- horizontal angle to the next point */
    /* Applied as an X rotation to bone 6 by UpdateMatrix; Update eases it
       toward sMascotWalkerOffset (clamped to +/-0x3000) while mPaused, else to 0. */
    s16 mHeadAngle; /* 0xf0 */
    /* Counted down by StateWalk and StatePause: 0x78 frames of pause from
       StartPause, then 0x258..0x4af frames of walking from StatePause. */
    s16 mStateTimer; /* 0xf2 */
    s32 mPaused;     /* 0xf4 -- set by StartPause, cleared when StatePause resumes the walk */
};

#ifndef SM64DS_PLATFORM_PC
typedef char MascotWalker_size_must_be_0xf8[sizeof(MascotWalker) == 0xf8 ? 1 : -1];
#endif

#endif
