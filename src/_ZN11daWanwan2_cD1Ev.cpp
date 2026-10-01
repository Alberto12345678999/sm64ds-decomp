//cpp
// @symbol _ZN11daWanwan2_cD1Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * One vtable store and ten teardowns, every one a consequence of
 * `struct daWanwan2_c : dEnemyBase_c` and the members that declaration types. Six of
 * them are arrays, and the compiler's own loops reproduce the ROM's __cxa_vec_cleanup
 * calls with the same counts and strides -- which is what makes this body the
 * evidence for the header rather than a transcription of it.
 */
#include "daWanwan2_c.h"

daWanwan2_c::~daWanwan2_c()
{
}
