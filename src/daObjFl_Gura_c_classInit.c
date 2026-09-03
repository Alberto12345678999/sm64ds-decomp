// @symbol daObjFl_Gura_c_classInit
/* recovered: vtable identified, declarations from a shared header */
#include "decl_ActorBase.h"
#include "decl_Platform.h"
#include "decl_common.h"
extern int _ZTV15daObjGuragura_c[];
extern int _ZTV14daObjFl_Gura_c[];
/* recovered: vtable identified */
/* vtable identified: VT0 = _ZTV15daObjGuragura_c */
/* Reconstructed source-style name: SM64DS proves daObjFl_Gura_c through RTTI,
 * allocation size, most-derived vtable identity, and the FL_GURA registry
 * profile; later EAD lineage supplies classInit. Exact original spelling is
 * not preserved. Historical alias: TiltingPlatformLll_Spawn. */
int *daObjFl_Gura_c_classInit(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(848);
    if (p) {
        _ZN10dBgActor_cC2Ev(p);
        p[0] = (int)_ZTV15daObjGuragura_c;
        p[0] = (int)_ZTV14daObjFl_Gura_c;
    }
    return p;
}
