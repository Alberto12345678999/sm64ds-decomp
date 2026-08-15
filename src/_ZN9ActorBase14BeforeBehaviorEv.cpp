//cpp
#include "ActorBase.h"
/* ActorBase::BeforeBehavior() at 0x02043afc -- vtable slot 7, behavior guard.
 * Blocks the per-frame update once the actor is already marked for
 * destruction, or if mSpawnFlags bit 1 is clear.
 */
int ActorBase::BeforeBehavior()
{
  if(shouldBeKilled!=0) goto ret0;
  if((mSpawnFlags&2)==0) goto ret1;
ret0:
  return 0;
ret1:
  return 1;
}
