#ifndef FALL_BLOCK_BFS_H
#define FALL_BLOCK_BFS_H

#include "types.h"
#include "daObjFallBlock_c.h"

/* class FallBlockBfs -- Bob-omb Battlefield's falling/rolling platform (ov045).
 *
 * Base is daObjFallBlock_c, NOT Platform. Its destructor stores three vtables in chain
 * order and its factory allocates 844 = 0x34c, storing _ZTV16daObjFallBlock_c before
 * its own vtable.
 *
 * No member of its own is declared: the destructor destroys Platform's Model at
 * 0xd4 and MovingMeshCollider at 0x124 and nothing else.
 */

struct FallBlockBfs : daObjFallBlock_c {
    virtual ~FallBlockBfs();
};

typedef char FallBlockBfs_size_must_be_0x34c[sizeof(FallBlockBfs) == 0x34c ? 1 : -1];

#endif
