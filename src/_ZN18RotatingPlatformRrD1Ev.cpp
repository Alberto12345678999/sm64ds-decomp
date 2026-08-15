//cpp
// @symbol _ZN18RotatingPlatformRrD1Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * THREE vtable stores and three destructor calls, every one a consequence of
 * `struct RotatingPlatformRr : daObjKaitendai_c : Platform`: its own vptr, then
 * daObjKaitendai_c's and then Platform's -- both inlined, because both of those
 * destructors are defined in their class bodies -- then Platform's Model and
 * MovingMeshCollider, then Actor.
 *
 * The middle store used to be spelled `data_ov002_021091d4`, an unnamed
 * placeholder, which is why this class read as a direct Platform child.
 */
#include "RotatingPlatformRr.h"

RotatingPlatformRr::~RotatingPlatformRr()
{
}
