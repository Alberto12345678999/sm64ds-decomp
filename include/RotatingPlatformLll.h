#ifndef ROTATING_PLATFORM_LLL_H
#define ROTATING_PLATFORM_LLL_H

#include "types.h"
#include "daObjKaitendai_c.h"

/* class RotatingPlatformLll -- Lethal Lava Land's rotating platform (ov022).
 *
 * Base is daObjKaitendai_c, NOT Platform. Its destructor at 0x021115a8 stores
 * three vtables in chain order -- _ZTV19RotatingPlatformLll, then ov002:0x021091d4
 * (daObjKaitendai_c's), then _ZTV8Platform -- and only a two-deep chain above
 * it produces three stores.
 *
 * No data member is declared: the destructor destroys Platform's own Model at
 * 0xd4 and MovingMeshCollider at 0x124 and nothing else, so nothing in the
 * matched corpus places a field of this class's own. Absent evidence, not an
 * assertion of emptiness.
 */

struct RotatingPlatformLll : daObjKaitendai_c {
    virtual ~RotatingPlatformLll();
};

/* sizeof is 0x320: the class adds no data member, and its own factory allocates the
 * literal 800 = 0x320, same as Platform's, and stores _ZTV16daObjKaitendai_c
 * before its own vtable -- the intermediate confirmed from the ctor side too. */
typedef char RotatingPlatformLll_size_must_be_0x320[sizeof(RotatingPlatformLll) == 0x320 ? 1 : -1];

#endif
