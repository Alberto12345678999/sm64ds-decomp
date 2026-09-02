//cpp
// @symbol _ZN15daObjWc_Obj04_cD1Ev
/* recovered: real C++ complete-object destructor -- the compiler emits the
 * whole body.
 *
 * The cartridge's D1 stores _ZTV15daObjWc_Obj04_c where our compiler spells
 * its own class vtable; those are two names for one address (ov029
 * 0x021141a0), EAD's internal name and the tree's English one, so the
 * difference was only ever in the source. It then destroys mModel2 (+0x320)
 * before the base step -- reverse declaration order -- and the inlined empty
 * ~dBgActor_c() stores _ZTV10dBgActor_c and destroys mMeshCollider (+0x124)
 * and mModel (+0xd4) before running dActor_c::D2. That sequence is exactly
 * what an empty body with daObjWc_Obj04_c : dBgActor_c compiles to;
 * nothing below mentions a member or a vtable.
 */
#include "daObjWc_Obj04_c.h"

daObjWc_Obj04_c::~daObjWc_Obj04_c()
{
}
