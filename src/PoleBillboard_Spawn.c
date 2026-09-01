// @symbol daObjBkBillboard_c_classInit
/* recovered: vtable identified, declarations from a shared header */
#include "decl_Actor.h"
#include "decl_ActorBase.h"
#include "decl_Model.h"
#include "decl_common.h"
extern int _ZTV13PoleBillboard[];
/* recovered: vtable identified */
/* vtable identified: VT0 = _ZTV13PoleBillboard */
/* Reconstructed source-style name: SM64DS proves daObjBkBillboard_c through
 * RTTI, allocation size, vtable identity, and the BK_BILLBOARD registry
 * profile; later EAD lineage supplies classInit. Exact original spelling is
 * not preserved. The project's PoleBillboard implementation aliases remain
 * unchanged. Historical alias: PoleBillboard_Spawn. */
int *daObjBkBillboard_c_classInit(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(292);
    if (p) {
        _ZN8dActor_cC2Ev(p);
        p[0] = (int)_ZTV13PoleBillboard;
        _ZN5ModelC1Ev((char *)p + 0xd4);
    }
    return p;
}
