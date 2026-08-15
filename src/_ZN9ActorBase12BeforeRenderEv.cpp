//cpp
#include "ActorBase.h"
/* ActorBase::BeforeRender() at 0x02043ac8 -- vtable slot 10, render guard.
 * Blocks rendering once the actor is already marked for destruction, or if
 * mSpawnFlags bit 3 is clear.
 */
int ActorBase::BeforeRender()
{
  if(shouldBeKilled!=0) goto ret0;
  if((mSpawnFlags&8)==0) goto ret1;
ret0:
  return 0;
ret1:
  return 1;
}
