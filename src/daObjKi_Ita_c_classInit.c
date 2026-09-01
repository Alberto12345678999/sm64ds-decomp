// @symbol daObjKi_Ita_c_classInit
/* recovered: vtable identified, declarations from a shared header */
#include "decl_ActorBase.h"
#include "decl_Platform.h"
#include "decl_common.h"
extern int _ZTV17daObjFloatBoard_c[];
extern int _ZTV23FloatOnWaterPlatformJrb[];
/* recovered: vtable identified */
/* vtable identified: VT0 = _ZTV17daObjFloatBoard_c */
/* Reconstructed source-style name: SM64DS proves daObjKi_Ita_c through RTTI,
 * allocation size, most-derived vtable identity, and the KI_ITA registry
 * profile; later EAD lineage supplies classInit. Exact original spelling is
 * not preserved. The project's FloatOnWaterPlatformJrb implementation aliases
 * remain unchanged. Historical alias: FloatOnWaterPlatformJrb_Spawn. */
int *daObjKi_Ita_c_classInit(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(840);
    if (p) {
        _ZN10dBgActor_cC2Ev(p);
        p[0] = (int)_ZTV17daObjFloatBoard_c;
        p[0] = (int)_ZTV23FloatOnWaterPlatformJrb;
    }
    return p;
}
