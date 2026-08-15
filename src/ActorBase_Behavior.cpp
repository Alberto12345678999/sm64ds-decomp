//cpp
#include "ActorBase.h"
/* ActorBase::Behavior() at 0x02043b24 -- vtable slot 6, per-frame update tick.
 * Base ActorBase does nothing and returns VS_FAIL (1); leaf classes override
 * slot 6 to supply their per-frame behavior.
 */

s32 ActorBase::Behavior()
{
    return 1; /* VS_FAIL */
}
