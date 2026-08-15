#ifndef RICKSHAW_PLATFORM_BDW_H
#define RICKSHAW_PLATFORM_BDW_H

#include "types.h"
#include "daObjKuruma_c.h"

/* class RickshawPlatformBdw -- Bob-omb Battlefield's rickshaw platform (ov043).
 *
 * Base is daObjKuruma_c, NOT Platform. Its destructor at 0x02111518 stores three
 * vtables in chain order -- its own, then daObjKuruma_c's, then _ZTV8Platform -- and
 * only a two-deep chain above it produces three stores. Its factory allocates
 * 800 = 0x320 and stores _ZTV13daObjKuruma_c before its own vtable,
 * confirming the same chain from the constructor side.
 *
 * No member of its own is declared: the destructor destroys Platform's Model at
 * 0xd4 and MovingMeshCollider at 0x124 and nothing else.
 */

struct RickshawPlatformBdw : daObjKuruma_c {
    virtual ~RickshawPlatformBdw();
};

typedef char RickshawPlatformBdw_size_must_be_0x320[sizeof(RickshawPlatformBdw) == 0x320 ? 1 : -1];

#endif
