//cpp
#include "ActorBase.h"
/* ActorBase::OnHeapCreated() at 0x02043494 -- vtable slot 15.
 * Hook fired after the actor's dedicated heap is set up.
 * Base returns the VirtualFuncSuccess code VS_FAIL (1); leaf classes override.
 */

bool ActorBase::OnHeapCreated()
{
    return 1; /* VS_FAIL */
}
