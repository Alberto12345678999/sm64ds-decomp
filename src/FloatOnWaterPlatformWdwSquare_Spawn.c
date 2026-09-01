// @symbol daObjWcObj01_c_classInit
/* recovered: vtable identified, declarations from a shared header */
#include "decl_ActorBase.h"
#include "decl_Platform.h"
#include "decl_common.h"
extern int _ZTV17daObjFloatBoard_c[];
extern int _ZTV29FloatOnWaterPlatformWdwSquare[];
/* recovered: vtable identified */
/* vtable identified: VT0 = _ZTV17daObjFloatBoard_c */
/* Reconstructed source-style name: SM64DS proves daObjWcObj01_c through RTTI,
 * allocation size, vtable identity, and the WC_OBJ01 registry profile; later
 * EAD lineage supplies classInit. Exact original spelling is not preserved.
 * The project's FloatOnWaterPlatformWdwSquare implementation aliases remain
 * unchanged. Historical alias: FloatOnWaterPlatformWdwSquare_Spawn. */
int *daObjWcObj01_c_classInit(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(840);
    if (p) {
        _ZN10dBgActor_cC2Ev(p);
        p[0] = (int)_ZTV17daObjFloatBoard_c;
        p[0] = (int)_ZTV29FloatOnWaterPlatformWdwSquare;
    }
    return p;
}
