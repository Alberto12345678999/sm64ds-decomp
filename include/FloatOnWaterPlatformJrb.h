#ifndef FLOAT_ON_WATER_PLATFORM_JRB_H
#define FLOAT_ON_WATER_PLATFORM_JRB_H

#include "types.h"
#include "daObjFloatBoard_c.h"

/* class FloatOnWaterPlatformJrb -- Jolly Roger Bay's floating platform (ov016).
 *
 * Base is daObjFloatBoard_c, NOT Platform. Its destructor at 0x02112ef4 stores three
 * vtables in chain order -- its own, then daObjFloatBoard_c's, then _ZTV8Platform -- and
 * only a two-deep chain above it produces three stores. Its factory allocates
 * 840 = 0x348 and stores _ZTV17daObjFloatBoard_c before its own vtable,
 * confirming the same chain from the constructor side.
 *
 * No member of its own is declared: the destructor destroys Platform's Model at
 * 0xd4 and MovingMeshCollider at 0x124 and nothing else.
 */

struct FloatOnWaterPlatformJrb : daObjFloatBoard_c {
    virtual ~FloatOnWaterPlatformJrb();
};

typedef char FloatOnWaterPlatformJrb_size_must_be_0x348[sizeof(FloatOnWaterPlatformJrb) == 0x348 ? 1 : -1];

#endif
