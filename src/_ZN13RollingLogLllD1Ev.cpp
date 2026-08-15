//cpp
// @symbol _ZN13RollingLogLllD1Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * THREE vtable stores and three destructor calls, every one a consequence of
 * `struct RollingLogLll : daObjMaruta_c : Platform`: its own vptr, then daObjMaruta_c's and then
 * Platform's -- both inlined, because both of those destructors are defined in
 * their class bodies -- then Platform's Model and MovingMeshCollider, then Actor.
 *
 * This file used to spell the middle store with the generic dBgActor_c vtable
 * placeholder -- a name that exists in no symbols.txt and stands for four
 * different addresses. The file therefore never linked. Deriving for real retires it by construction.
 */
#include "RollingLogLll.h"

RollingLogLll::~RollingLogLll()
{
}
