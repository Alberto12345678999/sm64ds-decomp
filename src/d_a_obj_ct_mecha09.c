// @symbol daObjCtMecha09_c_classInit
/* recovered: vtable identified, globals resolved, declarations from a shared header */
#include "decl_ActorBase.h"
#include "decl_Platform.h"
#include "decl_ShadowModel.h"
#include "decl_common.h"
/* recovered: vtable identified, globals resolved */
/* resolved: VT0 = _ZTV16daObjCtMecha09_c */
/* Reconstructed source-style name: SM64DS proves daObjCtMecha09_c through
 * RTTI, allocation size, vtable identity, and the CT_MECHA09 registry profile;
 * later EAD lineage supplies classInit. Exact original spelling is not
 * preserved. Historical aliases: TTC_MovingBeam, TTC_MovingBeam_Spawn. */
int *daObjCtMecha09_c_classInit(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(908);
    if (p) {
        _ZN10dBgActor_cC2Ev(p);
        p[0] = (int)_ZTV16daObjCtMecha09_c;
        _ZN11ShadowModelC1Ev((char *)p + 0x334);
    }
    return p;
}
