// @symbol daObjKm2_Fall_Block_c_classInit
/* recovered: vtable identified, declarations from a shared header */
#include "decl_ActorBase.h"
#include "decl_Platform.h"
#include "decl_common.h"
extern int _ZTV12FallBlockBfs[];
extern int _ZTV16daObjFallBlock_c[];
/* recovered: vtable identified */
/* vtable identified: VT0 = _ZTV16daObjFallBlock_c */
/* Reconstructed source-style name: SM64DS proves daObjKm2_Fall_Block_c
 * through RTTI, allocation size, vtable identity, and the KM2_KUZURE registry
 * profile; later EAD lineage supplies classInit. Exact original spelling is
 * not preserved. The project's FallBlockBfs implementation alias remains
 * unchanged. Historical alias: FallBlockBfs_Spawn. */
int *daObjKm2_Fall_Block_c_classInit(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(844);
    if (p) {
        _ZN10dBgActor_cC2Ev(p);
        p[0] = (int)_ZTV16daObjFallBlock_c;
        p[0] = (int)_ZTV12FallBlockBfs;
    }
    return p;
}
