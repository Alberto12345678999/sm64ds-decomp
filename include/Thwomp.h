#ifndef THWOMP_H
#define THWOMP_H

#include "types.h"
#include "daDsnBase_c.h"

/* class Thwomp -- the ROM's RTTI calls it daDsn_c (ov091:0x0213512c), and its
 * vtable is the one the tree already spells _ZTV6Thwomp at 0x02135174.
 *
 * Base is daDsnBase_c, NOT Platform. Its destructor stores three vtables in
 * chain order -- _ZTV6Thwomp, then _ZTV11daDsnBase_c, then _ZTV8Platform -- and
 * Thwomp_Spawn allocates 932 = 0x3a4 and stores _ZTV11daDsnBase_c before its own.
 * The chain is confirmed from both sides. Its sibling under that base is daDkk_c,
 * which the tree spawns through Grindel_Spawn.
 *
 * Was a flat AUTO-GENERATED struct that claimed six members it does not own:
 *   mModel 0x0d4, mMovingMeshCollider 0x124  -- Platform's, and the collider is
 *                                               really a MovingMeshCollider,
 *                                               spelled mMeshCollider there
 *   mFileTable 0x320, mTextureSequence 0x324,
 *   mShadowModel 0x338                       -- daDsnBase_c's; that class's own
 *                                               destructor destroys exactly those
 *                                               two subobjects and nothing else
 *   unk_32c                                  -- not a member at all: it is
 *                                               mTextureSequence.currFrame, the
 *                                               Animation frame counter at +0x8
 *                                               of the subobject at 0x324, which
 *                                               Behavior reuses as a countdown.
 *
 * What is left below is what this class actually adds, all of it above
 * daDsnBase_c's 0x360 end.
 */

struct Thwomp : daDsnBase_c {
    u8  pad_360[0x38];
    s32 mState;              /* 0x398 */
    u8  pad_39c[0x2];
    u8  unk_39e;             /* 0x39e */
    /* The two bytes after 0x39f hold a u16 that Behavior and InitResources both
       reach as (this + 0x300) + 0xa0 rather than as a member. */
    u8  pad_39f[0x3];
    u8  mTriggered;          /* 0x3a2 */

    virtual ~Thwomp();

    int Behavior();
    int CleanupResources();
    int InitResources();
    int Render();
};

/* sizeof is 0x3a4: mTriggered ends at 0x3a3 and rounds up to the class's
 * 4-byte alignment, which is exactly the literal Thwomp_Spawn allocates. */
typedef char Thwomp_size_must_be_0x3a4[sizeof(Thwomp) == 0x3a4 ? 1 : -1];

#endif
