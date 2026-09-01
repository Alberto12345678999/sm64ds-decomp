//cpp
// @symbol _ZN17daObjKm3_Dorifu_cD1Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * Three vtable stores and five destructor calls, every one a consequence of
 * `struct daObjKm3_Dorifu_c : daObjDorifu_c : dBgActor_c`: its own vptr, then
 * daObjDorifu_c's, then that class's dBgW_KcMbg[5] at 0x4b0 and Model[5]
 * at 0x320 through __destroy_arr, then dBgActor_c's vptr and dBgActor_c's own
 * dBgW_KcMbg and Model, then dActor_c. The two arrays are declared in
 * include/daObjDorifu_c.h, so the empty body reproduces them.
 */
#include "daObjKm3_Dorifu_c.h"

daObjKm3_Dorifu_c::~daObjKm3_Dorifu_c()
{
}
