#ifndef TILTINGPLATFORMLLL_H
#define TILTINGPLATFORMLLL_H

#include "types.h"
#include "daObjGuragura_c.h"

/* class TiltingPlatformLll -- Lethal Lava Land's tilting platform (ov064).
 *
 * Base is daObjGuragura_c, NOT Platform. Its destructor stores three vtables in
 * chain order and its factory allocates 848 = 0x350, storing _ZTV15daObjGuragura_c
 * before its own vtable.
 *
 * No member of its own is declared: the destructor destroys Platform's Model at
 * 0xd4 and MovingMeshCollider at 0x124 and nothing else.
 * THIS REPLACES A FLAT HEADER THAT CONTRADICTED THE ROM. The generated struct
 * declared `PathPtr mPath` at 0x360 -- past the 0x350 this class's own factory
 * allocates -- and its own comment records where that came from: it was named by
 * `MetalNetLift_Spawn`, a DIFFERENT class's factory. Same misattribution family
 * as RickshawBs_Spawn. Neither of the two files that include this header touches
 * the member, so dropping it costs nothing and removes a claim the ROM refutes.
 */

struct TiltingPlatformLll : daObjGuragura_c {
    virtual ~TiltingPlatformLll();

    int CleanupResources();
    int InitResources();
};

typedef char TiltingPlatformLll_size_must_be_0x350[sizeof(TiltingPlatformLll) == 0x350 ? 1 : -1];

#endif
