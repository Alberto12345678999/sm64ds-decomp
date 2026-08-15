//cpp
// @symbol _ZN18TiltingPlatformBfsD0Ev
/* recovered: real C++ deleting destructor -- the compiler emits the whole body
 *
 * THREE vtable stores and three destructor calls, every one a consequence of
 * `struct TiltingPlatformBfs : daObjGuragura_c : Platform`: its own vptr, then
 * daObjGuragura_c's and then Platform's -- both inlined, because both of those
 * destructors are defined in their class bodies -- then Platform's Model and
 * MovingMeshCollider, then Actor.
 * D0 is vtable slot 17: it then returns the object to the actor heap through
 * Actor's inline operator delete, which is why no heap is named here.
 *
 * The middle store used to be an unnamed data_ placeholder, which is why this
 * class read as a direct Platform child.
 */
#include "TiltingPlatformBfs.h"

TiltingPlatformBfs::~TiltingPlatformBfs()
{
}
