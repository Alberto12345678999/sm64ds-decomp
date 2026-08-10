//cpp
// @symbol _ZN19FloatingFloorLllBigD1Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * Two vtable stores and three destructor calls, all consequences of
 * `struct FloatingFloorLllBig : Platform`: its own vptr, then Platform's --
 * inlined, because Platform's destructor is defined in its class body -- then
 * Platform's Model and MovingMeshCollider, then Actor.
 */
#include "FloatingFloorLllBig.h"

FloatingFloorLllBig::~FloatingFloorLllBig()
{
}
