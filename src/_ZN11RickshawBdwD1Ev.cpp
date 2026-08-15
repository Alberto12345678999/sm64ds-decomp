//cpp
// @symbol _ZN11RickshawBdwD1Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * THREE vtable stores and three destructor calls, every one a consequence of
 * `struct RickshawBdw : daObjKurumajiku_c : Platform`: its own vptr, then
 * daObjKurumajiku_c's and then Platform's -- both inlined, because both of those
 * destructors are defined in their class bodies -- then Platform's Model and
 * MovingMeshCollider, then Actor. The intermediate contributes no destructor
 * call of its own: its four carried IDs are plain u32s.
 */
#include "RickshawBdw.h"

RickshawBdw::~RickshawBdw()
{
}
