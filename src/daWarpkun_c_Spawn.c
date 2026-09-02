// @symbol daWarpkun_c_Spawn
/* recovered: vtable identified, declarations from a shared header */
#include "decl_Actor.h"
#include "decl_ActorBase.h"
#include "decl_dCcAc_c.h"
#include "decl_common.h"
extern int _ZTV11daWarpkun_c[];
/* recovered: vtable identified */
/* vtable identified: VT0 = _ZTV11daWarpkun_c */
int *daWarpkun_c_Spawn(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(264);
    if (p) {
        _ZN8dActor_cC2Ev(p);
        p[0] = (int)_ZTV11daWarpkun_c;
        _ZN7dCcAc_cC1Ev((char *)p + 0xd4);
    }
    return p;
}
