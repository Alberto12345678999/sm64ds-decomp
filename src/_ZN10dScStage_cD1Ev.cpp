//cpp
// @symbol _ZN10dScStage_cD1Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * Destroy through dScStage_c's own three fields -- dBgW_Kc at 0x91c, Model at
 * 0x86c, Particle::SysTracker at 0x50 -- in reverse declaration order, then
 * dScene_c (now inline-defined in dScene_c.h, so its vptr store and dBase_c's
 * inline in turn), then fBase_c's subobject destructor, called rather than
 * inlined because fBase_c's is not.
 */
#include "dScStage_c.h"

dScStage_c::~dScStage_c()
{
}
