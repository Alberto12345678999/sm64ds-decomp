// @symbol func_ov006_020cd12c
/* recovered: vtable identified, declarations from a shared header */
#include "decl_ModelAnim.h"
#include "decl_common.h"
extern int _ZTV18dMgTrmpln3DMario_c[];
extern void func_ov006_020cd72c(int *c);
/* recovered: vtable identified */
/* vtable identified: VT0 = _ZTV18dMgTrmpln3DMario_c */
int *func_ov006_020cd12c(int *t)
{
    func_ov006_020cd72c(t);
    t[0] = (int)_ZTV18dMgTrmpln3DMario_c;
    _ZN9ModelAnimC1Ev((char *)t + 0x6c);
    return t;
}
