//cpp
#include "ActorBase.h"
/* ActorBase::AfterBehavior(u32 vfSuccess) at 0x02043af8 -- vtable slot 8.
 * Post-behavior hook; vfSuccess is the VirtualFuncSuccess code from Behavior().
 * Base ActorBase does nothing; leaf classes override.
 */

void ActorBase::AfterBehavior(u32 vfSuccess)
{
}
