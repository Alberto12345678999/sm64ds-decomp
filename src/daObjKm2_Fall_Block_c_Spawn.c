// @symbol daObjKm2_Fall_Block_c_Spawn
/* recovered: vtable identified, declarations from a shared header */
#include "decl_ActorBase.h"
#include "decl_Platform.h"
#include "decl_common.h"
extern int _ZTV21daObjKm2_Fall_Block_c[];
extern int _ZTV16daObjFallBlock_c[];
/* recovered: vtable identified */
/* vtable identified: VT0 = _ZTV16daObjFallBlock_c */
int *daObjKm2_Fall_Block_c_Spawn(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(844);
    if (p) {
        _ZN10dBgActor_cC2Ev(p);
        p[0] = (int)_ZTV16daObjFallBlock_c;
        p[0] = (int)_ZTV21daObjKm2_Fall_Block_c;
    }
    return p;
}
