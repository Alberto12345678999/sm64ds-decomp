#ifndef DAOBJDORIFU_C_H
#define DAOBJDORIFU_C_H

#include "types.h"
#include "Platform.h"
#include "Model.h"
#include "MovingMeshCollider.h"

/* daObjDorifu_c -- an intermediate the ROM's RTTI names and the tree did not.
 *
 *     Actor -> Platform -> daObjDorifu_c -> daObjRc_Dorifu_c    (TrickyTriangles_Spawn)
 *                                        -> daObjKm1_Dorifu_c   (StairsBdw_Spawn)
 *                                        -> RickshawPlatformBs  (StairsBs_Spawn,
 *                                                                RTTI daObjKm3_Dorifu_c)
 *
 * type_info 0x02108d70 (ov002), vtable 0x02108d94 (ov002).
 *
 * A PLATFORM THAT MORPHS BETWEEN FIVE SHAPES ON AN EVENT BIT. It carries five
 * Models and five MovingMeshColliders, shows one at a time, and steps the active
 * one up or down when a global event flag flips. Slot 6 of its own vtable runs
 * the state machine and enables exactly the collider whose index matches; slot 9
 * renders exactly mModels[mActiveIndex]. Both live in ov002 with the class.
 *
 * THE TWO ARRAYS ARE MEASURED, NOT INFERRED. All three children construct them
 * identically, between the store of this class's vtable and the store of their
 * own -- so this class's constructor, inlined:
 *
 *     func_020733a8(this + 0x320, 5, 0x50,  Model ctor,              Model dtor)
 *     func_020733a8(this + 0x4b0, 5, 0x1c8, MovingMeshCollider ctor, ...  dtor)
 *
 * and all three destructors tear them down with the matching __destroy_arr pair,
 * in reverse. The counts and strides are literals in the ROM, and 0x50 and 0x1c8
 * are exactly sizeof(Model) and sizeof(MovingMeshCollider). Five models from
 * 0x320 end at 0x4b0, where the colliders start; five colliders end at 0xd98.
 *
 * BEING BETWEEN THE TWO VPTR STORES IS WHAT MAKES THEM THE BASE'S, and that is
 * airtight rather than merely suggestive: C++ sets the vptr to the class under
 * construction on entry to each constructor, so everything between the store of
 * this class's vtable and the store of the child's is, by the language's own
 * rules, this class's constructor body. Three children independently agreeing on
 * the same two calls at the same two offsets then rules out coincidence.
 *
 * THE FOUR CONTROL BYTES ARE THE BASE'S BECAUSE ALL THREE CHILDREN SHARE THE
 * CODE THAT READS THEM. Diffing each child's vtable against this one, all three
 * override only slots 0, 3, 16 and 17 -- so slots 6 and 9 are inherited, and the
 * two functions below are reached through three different derived types.
 * Storage a shared function reads must belong to the common base. ("Read off the
 * class's own TU" would be the weaker form of this, and a downcast defeats it.)
 *
 *     0xdc8  mActiveIndex  0..4 -- indexes both arrays, in slot 6 and slot 9
 *     0xdc9  mStepDelay    reloaded to 2 between steps
 *     0xdca  mState        0 armed, 1 stepping down, 2 held, 3 stepping up
 *     0xdcb  mEventBit     the Event::GetBit id the state machine watches
 *
 * SIZE 0xdcc, on all three children's factory literals, and mEventBit ends
 * exactly there.
 *
 * 0xd98..0xdc8 IS UNOBSERVED, not known to be padding. No matched function in
 * the corpus reaches those 0x30 bytes; they are carried as an explicit gap so
 * the control bytes land where the ROM puts them.
 *
 * DESTRUCTOR IS INLINE, like Platform's above it: no child's destructor contains
 * a `bl` to this one -- each stores this vptr and then runs the two
 * __destroy_arr calls itself. The out-of-line pair at 0x020b4af8 (D1) and
 * 0x020b4a70 (D0) exists because slots 16/17 of the table need an address.
 *
 * BEWARE THE FACTORY NAMES IN THIS FAMILY. src/RickshawPlatformBs_Spawn.c does
 * NOT build RickshawPlatformBs -- it allocates 800 and stores _ZTV13daObjKuruma_c
 * and _ZTV17daObjKm3_Kuruma_c, a different chain entirely. This class's third
 * child is built by StairsBs_Spawn. Pair a class to its factory by vtable
 * address, never by filename.
 */

struct daObjDorifu_c : Platform {
    u8  pad_31e[0x2];                    /* Platform's tail padding, reused */
    Model              mModels[5];       /* 0x320 */
    MovingMeshCollider mColliders[5];    /* 0x4b0 */
    u8  unk_d98[0x30];                   /* 0xd98 -- unobserved, see above */
    u8  mActiveIndex;                    /* 0xdc8 */
    u8  mStepDelay;                      /* 0xdc9 */
    u8  mState;                          /* 0xdca */
    u8  mEventBit;                       /* 0xdcb */

    virtual ~daObjDorifu_c() {}
};

typedef char daObjDorifu_c_size_must_be_0xdcc[sizeof(daObjDorifu_c) == 0xdcc ? 1 : -1];

#endif
