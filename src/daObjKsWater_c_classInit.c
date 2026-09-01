// @symbol daObjKsWater_c_classInit
/* recovered: vtable identified, globals resolved, declarations from a shared header */
#include "decl_ActorBase.h"
#include "decl_Platform.h"
#include "decl_TextureTransformer.h"
#include "decl_common.h"
/* recovered: vtable identified, globals resolved */
/* resolved: VT0 = _ZTV9ShipWater */
/* Reconstructed source-style name: SM64DS proves daObjKsWater_c through RTTI,
 * allocation size, vtable identity, and the KS_MIZU registry profile; later
 * EAD lineage supplies classInit. Exact original spelling is not preserved.
 * Historical alias: ShipWater_Spawn. */
int *daObjKsWater_c_classInit(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(832);
    if (p) {
        _ZN10dBgActor_cC2Ev(p);
        p[0] = (int)_ZTV9ShipWater;
        _ZN18TextureTransformerC1Ev((char *)p + 0x320);
    }
    return p;
}
