#ifndef TILTINGPLATFORMBFS_H
#define TILTINGPLATFORMBFS_H

#include "types.h"
#include "daObjGuragura_c.h"

/* class TiltingPlatformBfs -- Bob-omb Battlefield's tilting platform (ov045).
 *
 * Base is daObjGuragura_c, NOT Platform. Its destructor stores three vtables in
 * chain order and its factory allocates 848 = 0x350, storing _ZTV15daObjGuragura_c
 * before its own vtable.
 *
 * No member of its own is declared: the destructor destroys Platform's Model at
 * 0xd4 and MovingMeshCollider at 0x124 and nothing else.
 */

struct TiltingPlatformBfs : daObjGuragura_c {
    virtual ~TiltingPlatformBfs();

    int CleanupResources();
    int InitResources();
};

typedef char TiltingPlatformBfs_size_must_be_0x350[sizeof(TiltingPlatformBfs) == 0x350 ? 1 : -1];

#endif
