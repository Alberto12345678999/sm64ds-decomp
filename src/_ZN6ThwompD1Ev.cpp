//cpp
// @symbol _ZN6ThwompD1Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * THREE vtable stores and four destructor calls, every one a consequence of
 * `struct Thwomp : daDsnBase_c : Platform`: its own vptr, then daDsnBase_c's and
 * then Platform's -- both inlined, because both of those destructors are defined
 * in their class bodies -- with daDsnBase_c's ShadowModel and TextureSequence
 * between the second and third store, and Platform's Model and MovingMeshCollider
 * after it, then Actor.
 *
 * The middle store used to be a hand-written assignment in a C file, which is
 * why this class read as a direct Platform child.
 */
#include "Thwomp.h"

Thwomp::~Thwomp()
{
}
