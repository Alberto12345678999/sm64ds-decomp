//cpp
// @symbol _ZN12FallBlockBfsD0Ev
/* recovered: real C++ deleting destructor -- the compiler emits the whole body
 *
 * THREE vtable stores and three destructor calls, every one a consequence of
 * `struct FallBlockBfs : daObjFallBlock_c : Platform`: its own vptr, then daObjFallBlock_c's and then
 * Platform's -- both inlined, because both of those destructors are defined in
 * their class bodies -- then Platform's Model and MovingMeshCollider, then Actor.
 * D0 is vtable slot 17: it then returns the object to the actor heap through
 * Actor's inline operator delete, which is why no heap is named here.
 *
 * This file used to spell the middle store with the generic dBgActor_c vtable
 * placeholder -- a name that exists in no symbols.txt and stands for four
 * different addresses. The file therefore never linked. Deriving for real retires it by construction.
 */
#include "FallBlockBfs.h"

FallBlockBfs::~FallBlockBfs()
{
}
