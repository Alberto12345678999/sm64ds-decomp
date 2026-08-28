#include "types.h"
// @symbol _ZN8Particle25EndingStarGlitterCallback8OnUpdateERNS_6SystemEb
/* recovered: named members + shared header, declarations from a shared header */
#include "decl_common.h"
/* recovered: named members + shared header */
#include "Particle__EndingStarGlitterCallback.h"
typedef int Bool;

/* forward declarations */

extern int _ZN5dPa_c7level_c16simpleCallback_c8OnUpdateERN8Particle6SystemEb(void* cb, void* sys, Bool active);


int _ZN8Particle25EndingStarGlitterCallback8OnUpdateERNS_6SystemEb(void* cb, void* sys, Bool active)
{
    func_0204dab4(sys, (char*)cb + 8, 0x40, 0, (void*)func_02022260);
    return _ZN5dPa_c7level_c16simpleCallback_c8OnUpdateERN8Particle6SystemEb(cb, sys, active);
}
