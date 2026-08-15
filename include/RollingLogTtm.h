#ifndef ROLLING_LOG_TTM_H
#define ROLLING_LOG_TTM_H

#include "types.h"
#include "daObjMaruta_c.h"

/* class RollingLogTtm -- Tall, Tall Mountain's falling/rolling platform (ov030).
 *
 * Base is daObjMaruta_c, NOT Platform. Its destructor stores three vtables in chain
 * order and its factory allocates 836 = 0x344, storing _ZTV13daObjMaruta_c before
 * its own vtable.
 *
 * No member of its own is declared: the destructor destroys Platform's Model at
 * 0xd4 and MovingMeshCollider at 0x124 and nothing else.
 */

struct RollingLogTtm : daObjMaruta_c {
    virtual ~RollingLogTtm();
};

typedef char RollingLogTtm_size_must_be_0x344[sizeof(RollingLogTtm) == 0x344 ? 1 : -1];

#endif
