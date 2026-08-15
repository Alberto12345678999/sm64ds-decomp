//cpp
// @symbol _ZN23FloatOnWaterPlatformJrbD1Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * THREE vtable stores and three destructor calls, every one a consequence of
 * `struct FloatOnWaterPlatformJrb : daObjFloatBoard_c : Platform`: its own vptr, then daObjFloatBoard_c's and then
 * Platform's -- both inlined, because both of those destructors are defined in
 * their class bodies -- then Platform's Model and MovingMeshCollider, then Actor.
 *
 * The middle store used to be spelled as an unnamed data_ placeholder, which is
 * why this class read as a direct Platform child.
 */
#include "FloatOnWaterPlatformJrb.h"

FloatOnWaterPlatformJrb::~FloatOnWaterPlatformJrb()
{
}
