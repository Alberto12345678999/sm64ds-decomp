// @symbol daObjClockHuriko_c_Spawn
/* recovered: vtable identified, declarations from a shared header */
#include "decl_Actor.h"
#include "decl_ActorBase.h"
#include "decl_Model.h"
#include "decl_common.h"
extern int _ZTV18daObjClockHuriko_c[];
/* recovered: vtable identified */
/* vtable identified: VT0 = _ZTV18daObjClockHuriko_c */
int *daObjClockHuriko_c_Spawn(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(296);
    if (p) {
        _ZN8dActor_cC2Ev(p);
        p[0] = (int)_ZTV18daObjClockHuriko_c;
        _ZN5ModelC1Ev((char *)p + 0xd4);
    }
    return p;
}
