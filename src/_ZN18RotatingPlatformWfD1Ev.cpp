//cpp
// @symbol _ZN18RotatingPlatformWfD1Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * THREE vtable stores and three destructor calls, every one a consequence of
 * `struct RotatingPlatformWf : daObjKaitendai_c : Platform`: its own vptr, then
 * daObjKaitendai_c's and then Platform's -- both inlined, because both of those
 * destructors are defined in their class bodies -- then Platform's Model and
 * MovingMeshCollider, then Actor.
 *
 * The middle store is the whole point. It used to be spelled `data_ov002_021091d4`,
 * an unnamed placeholder, which is why this class read as a direct Platform child.
 * It is daObjKaitendai_c's vtable, and the ROM's RTTI says so.
 */
#include "RotatingPlatformWf.h"

RotatingPlatformWf::~RotatingPlatformWf()
{
}
