//cpp
// @symbol _ZN15daObjWc_Obj05_c16CleanupResourcesEv
#include "daObjWc_Obj05_c.h"
// recovered name: daObjWc_Obj05_c_CleanupResources
/* recovered: renamed to Class_Method, declarations from a shared header */
#include "decl_common.h"
/* recovered: renamed to Class_Method */
/* daObjWc_Obj05_c::CleanupResources - recovered from vtable slot identity */
extern "C" {
extern void _ZN13SharedFilePtr7ReleaseEv(void *);
extern int data_ov029_0211428c[];
}

s32 daObjWc_Obj05_c::CleanupResources() {
    void * t = (void *)this;
    if (_ZN4dBgW9IsEnabledEv((char *)t + 0x124)) {
        _ZN4dBgW7DisableEv((char *)t + 0x124);
    }
    _ZN13SharedFilePtr7ReleaseEv(data_ov029_0211428c);
    _ZN13SharedFilePtr7ReleaseEv(data_ov029_02114284);
    return 1;
}
