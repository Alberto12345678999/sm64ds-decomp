#ifndef FALL_BLOCK_WF_H
#define FALL_BLOCK_WF_H

#include "types.h"
#include "daObjFallBlock_c.h"

/* class FallBlockWf -- Whomp's Fortress's falling/rolling platform (ov015).
 *
 * Base is daObjFallBlock_c, NOT Platform. Its destructor stores three vtables in chain
 * order and its factory allocates 844 = 0x34c, storing _ZTV16daObjFallBlock_c before
 * its own vtable.
 *
 * No member of its own is declared: the destructor destroys Platform's Model at
 * 0xd4 and MovingMeshCollider at 0x124 and nothing else.
 */

struct FallBlockWf : daObjFallBlock_c {
    virtual ~FallBlockWf();
};

typedef char FallBlockWf_size_must_be_0x34c[sizeof(FallBlockWf) == 0x34c ? 1 : -1];

#endif
