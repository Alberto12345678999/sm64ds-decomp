#include "daObjWc_Obj02_c.h"
// @symbol daObjWc_Obj02_c_classInit
/* recovered: globals resolved, declarations from a shared header */
#include "decl_ActorBase.h"
#include "decl_Platform.h"
#include "decl_common.h"
/* recovered: globals resolved */
/* resolved: VT = _ZTV15daObjWc_Obj02_c */
/* Reconstructed source-style name: SM64DS proves daObjWc_Obj02_c through RTTI,
 * allocation size, vtable identity, and the WC_OBJ02 registry profile; later
 * EAD lineage supplies classInit. Exact original spelling is not preserved.
 * The project's daObjWc_Obj02_c implementation aliases remain unchanged. Historical
 * alias: ArrowLift_Spawn. */
int *daObjWc_Obj02_c_classInit(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(sizeof(struct daObjWc_Obj02_c));
    if (p) { _ZN10dBgActor_cC2Ev(p); p[0] = (int)_ZTV15daObjWc_Obj02_c; }
    return p;
}
