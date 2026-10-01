// @symbol daDoor_c_classInit
/* recovered: vtable identified, declarations from a shared header */
#include "decl_Actor.h"
#include "decl_ActorBase.h"
#include "decl_ModelAnim.h"
#include "decl_common.h"
extern int _ZTV8daDoor_c[];
/* recovered: vtable identified */
/* vtable identified: VT0 = _ZTV8daDoor_c */
/* Reconstructed source-style name: SM64DS proves daDoor_c through RTTI,
 * allocation size, vtable identity, and the DOOR registry profile;
 * later EAD lineage supplies classInit. Exact original spelling is not
 * preserved. Historical alias: Door_Spawn. */
int *daDoor_c_classInit(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(328);
    if (p) {
        _ZN8dActor_cC2Ev(p);
        p[0] = (int)_ZTV8daDoor_c;
        _ZN9ModelAnimC1Ev((char *)p + 0xd4);
    }
    return p;
}
