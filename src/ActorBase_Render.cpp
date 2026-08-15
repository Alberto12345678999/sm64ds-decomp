//cpp
#include "ActorBase.h"
/* ActorBase::Render() at 0x02043af0 -- vtable slot 9, per-frame draw.
 * Base ActorBase draws nothing and returns VS_FAIL (1); leaf classes override
 * slot 9 to do the actual rendering.
 */

s32 ActorBase::Render()
{
    return 1; /* VS_FAIL */
}
