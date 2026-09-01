// @symbol daObjKm3_Kuruma_c_classInit
/* recovered: vtable identified, declarations from a shared header */
#include "decl_ActorBase.h"
#include "decl_Platform.h"
#include "decl_common.h"
extern int _ZTV13daObjKuruma_c[];
extern int _ZTV17daObjKm3_Kuruma_c[];
/* recovered: vtable identified. Factory for daObjKm3_Kuruma_c (paired by vtable
   address; see include/daObjKm3_Kuruma_c.h). */
/* Reconstructed source-style name: SM64DS proves daObjKm3_Kuruma_c through
 * RTTI, allocation size, vtable identity, and the KM3_KURUMA registry profile;
 * later EAD lineage supplies classInit. Exact original spelling is not
 * preserved. Historical alias: RickshawPlatformBs_Spawn. */
int *daObjKm3_Kuruma_c_classInit(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(800);
    if (p) {
        _ZN10dBgActor_cC2Ev(p);
        p[0] = (int)_ZTV13daObjKuruma_c;
        p[0] = (int)_ZTV17daObjKm3_Kuruma_c;
    }
    return p;
}
