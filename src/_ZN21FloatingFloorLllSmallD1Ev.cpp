//cpp
// @symbol _ZN21FloatingFloorLllSmallD1Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * THREE vtable stores and three destructor calls, every one a consequence of
 * `struct FloatingFloorLllSmall : daObjUkiyuka_c : Platform`: its own vptr, then
 * daObjUkiyuka_c's and then Platform's -- both inlined, because both of those
 * destructors are defined in their class bodies -- then Platform's Model and
 * MovingMeshCollider, then Actor. The intermediate contributes no destructor
 * call of its own: its four fields are plain scalars.
 */
#include "FloatingFloorLllSmall.h"

FloatingFloorLllSmall::~FloatingFloorLllSmall()
{
}
