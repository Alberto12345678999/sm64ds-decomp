//cpp
#include "ActorBase.h"
/* ActorBase::CleanupResources() at 0x02043bf0 -- vtable slot 3.
 * Release files/heap on death. Base returns VS_FAIL (1); leaf classes override.
 */

s32 ActorBase::CleanupResources()
{
    return 1; /* VS_FAIL */
}
