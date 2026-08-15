#ifndef SHUTTERBOB_H
#define SHUTTERBOB_H

#include "types.h"
#include "daObjSwdoor_c.h"

/* class ShutterBob -- Bob-omb Battlefield's switch shutter (ov014).
 *
 * Base is daObjSwdoor_c, NOT Platform. Its destructor stores three vtables in
 * chain order and its factory allocates 804 = 0x324, storing _ZTV13daObjSwdoor_c
 * before its own vtable -- the chain confirmed from both sides.
 *
 * Was a flat AUTO-GENERATED struct whose `Model mModel` at 0xd4 and
 * `u8 mMovingMeshCollider` marker at 0x124 are Platform's own members; both now
 * come from the base, where the collider is the real MovingMeshCollider and is
 * spelled mMeshCollider.
 *
 * No member of its own is declared: the destructor destroys Platform's Model and
 * MovingMeshCollider and nothing else, and the 4 bytes above 0x320 belong to
 * daObjSwdoor_c on that class's own TU evidence.
 */

struct ShutterBob : daObjSwdoor_c {
    virtual ~ShutterBob();

    int Behavior();
    int CleanupResources();
    int InitResources();
};

typedef char ShutterBob_size_must_be_0x324[sizeof(ShutterBob) == 0x324 ? 1 : -1];

#endif
