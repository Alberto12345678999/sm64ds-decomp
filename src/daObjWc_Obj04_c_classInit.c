// @symbol daObjWc_Obj04_c_classInit
/* recovered: vtable identified, globals resolved, declarations from a shared header */
#include "decl_ActorBase.h"
#include "decl_Model.h"
#include "decl_Platform.h"
#include "decl_common.h"
/* recovered: vtable identified, globals resolved */
/* resolved: VT0 = _ZTV15daObjWc_Obj04_c */
/* Reconstructed source-style name: SM64DS proves daObjWc_Obj04_c through RTTI,
 * allocation size, vtable identity, and the WC_OBJ04 registry profile; later
 * EAD lineage supplies classInit. Exact original spelling is not preserved.
 * The project's daObjWc_Obj04_c implementation aliases remain unchanged.
 * Historical alias: SwitchActivatedPlank_Spawn. */
int *daObjWc_Obj04_c_classInit(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(936);
    if (p) {
        _ZN10dBgActor_cC2Ev(p);
        p[0] = (int)_ZTV15daObjWc_Obj04_c;
        _ZN5ModelC1Ev((char *)p + 0x320);
    }
    return p;
}
