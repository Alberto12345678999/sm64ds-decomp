//cpp
// @symbol _ZN18RickshawPlatformBsD0Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * THREE vtable stores, TWO array teardowns and three destructor calls, every one
 * a consequence of `struct RickshawPlatformBs : daObjDorifu_c : Platform`: its own
 * vptr, then daObjDorifu_c's and then Platform's -- both inlined, because both of
 * those destructors are defined in their class bodies. The two __destroy_arr
 * calls between the second and third store are daObjDorifu_c's mColliders[5] and
 * mModels[5]; the compiler emits them from the array members, in reverse
 * declaration order. Then Platform's own Model and MovingMeshCollider, then
 * Actor.
 * D0 is vtable slot 17: it then returns the object to the actor heap through
 * Actor's inline operator delete.
 */
#include "RickshawPlatformBs.h"

RickshawPlatformBs::~RickshawPlatformBs()
{
}
