//cpp
#include "ActorBase.h"
/* ActorBase::BeforeInitResources() at 0x02043c78 -- vtable slot 1, init guard.
 * Base returns the VirtualFuncSuccess code VS_FAIL (1); leaf classes override.
 */

bool ActorBase::BeforeInitResources()
{
    return 1; /* VS_FAIL */
}
