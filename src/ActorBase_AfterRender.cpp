//cpp
#include "ActorBase.h"
/* ActorBase::AfterRender(u32 vfSuccess) at 0x02043ac4 -- vtable slot 11.
 * Post-render hook; vfSuccess is the VirtualFuncSuccess code from Render().
 * Base ActorBase does nothing; leaf classes override.
 */

void ActorBase::AfterRender(u32 vfSuccess)
{
}
