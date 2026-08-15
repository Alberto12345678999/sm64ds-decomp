//cpp
// @symbol _ZN6ThwompD0Ev
/* recovered: real C++ deleting destructor -- the compiler emits the whole body
 *
 * THREE vtable stores and four destructor calls, every one a consequence of
 * `struct Thwomp : daDsnBase_c : Platform`: its own vptr, then daDsnBase_c's and
 * then Platform's -- both inlined, because both of those destructors are defined
 * in their class bodies -- with daDsnBase_c's ShadowModel and TextureSequence
 * between the second and third store, and Platform's Model and MovingMeshCollider
 * after it, then Actor.
 * D0 is vtable slot 17: it then returns the object to the actor heap through
 * Actor's inline operator delete, which is why no heap is named here even though
 * the hand-written C file this replaces spelled out Memory::Deallocate.
 */
#include "Thwomp.h"

Thwomp::~Thwomp()
{
}
