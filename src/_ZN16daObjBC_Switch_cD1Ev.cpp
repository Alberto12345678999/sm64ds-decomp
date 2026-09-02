//cpp
// @symbol _ZN16daObjBC_Switch_cD1Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * Two vtable stores and three destructor calls, every one a consequence of
 * `struct daObjBC_Switch_c : dBgActor_c`: its own vptr, then dBgActor_c's -- inlined,
 * because dBgActor_c's destructor is defined in its class body -- then
 * dBgActor_c's Model and dBgW_KcMbg, then dActor_c. This class adds no
 * member with a destructor of its own.
 */
#include "daObjBC_Switch_c.h"

daObjBC_Switch_c::~daObjBC_Switch_c()
{
}
