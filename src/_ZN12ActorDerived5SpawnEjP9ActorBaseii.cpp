//cpp
#include "ActorDerived.h"
/* ActorDerived::Spawn(u32, ActorBase*, int, int) @ 0x02013ee8 -- tail-call
 * veneer to func_02042ffc (0x02042ffc): `ldr ip, [pc]; bx ip; .word
 * 0x2042ffc`. func_02042ffc's own two parameters are read straight off
 * `this` call's r0/r1 -- actorID and parent -- unmodified by the jump; the
 * trailing (int, int) pair rides through in r2/r3 the same way, which is
 * why the callee only declares two parameters of its own.
 */
extern "C" ActorBase *func_02042ffc(u32 actorID, ActorBase *parent);

ActorBase *ActorDerived::Spawn(u32 actorID, ActorBase *parent, int a, int b)
{
    return func_02042ffc(actorID, parent);
}
