#ifndef FLOAT_ON_WATER_PLATFORM_WDW_SQUARE_H
#define FLOAT_ON_WATER_PLATFORM_WDW_SQUARE_H

#include "types.h"
#include "daObjFloatBoard_c.h"

/* class FloatOnWaterPlatformWdwSquare -- Wet-Dry World's square floating platform (ov029).
 *
 * Base is daObjFloatBoard_c, NOT Platform. Its destructor at 0x021111a0 stores three
 * vtables in chain order -- its own, then daObjFloatBoard_c's, then _ZTV8Platform -- and
 * only a two-deep chain above it produces three stores. Its factory allocates
 * 840 = 0x348 and stores _ZTV17daObjFloatBoard_c before its own vtable,
 * confirming the same chain from the constructor side.
 *
 * No member of its own is declared: the destructor destroys Platform's Model at
 * 0xd4 and MovingMeshCollider at 0x124 and nothing else.
 */

struct FloatOnWaterPlatformWdwSquare : daObjFloatBoard_c {
    virtual ~FloatOnWaterPlatformWdwSquare();
};

typedef char FloatOnWaterPlatformWdwSquare_size_must_be_0x348[sizeof(FloatOnWaterPlatformWdwSquare) == 0x348 ? 1 : -1];

#endif
