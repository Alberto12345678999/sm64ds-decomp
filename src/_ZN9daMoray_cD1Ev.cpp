//cpp
// @symbol _ZN9daMoray_cD1Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * One array cleanup, four member destructors and the chain into dEnemyBase_c, all of
 * it reverse declaration order out of daMoray_c.h.
 *
 * The array at 0x448 is Vector3[7] -- the ROM destroys it with
 * __cxa_vec_cleanup(ptr, 7, 0xc, _ZN7Vector3D1Ev), and 0xc is sizeof(Vector3).
 */
#include "daMoray_c.h"

daMoray_c::~daMoray_c()
{
}
