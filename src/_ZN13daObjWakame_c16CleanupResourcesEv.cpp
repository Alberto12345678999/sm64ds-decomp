//cpp
// @symbol _ZN13daObjWakame_c16CleanupResourcesEv
#include "daObjWakame_c.h"
// recovered name: daObjWakame_c_CleanupResources
/* recovered: renamed to Class_Method, declarations from a shared header */
#include "decl_common.h"
/* recovered: renamed to Class_Method */
/* daObjWakame_c::CleanupResources - recovered from vtable slot identity */
extern "C" {
extern void _ZN13SharedFilePtr7ReleaseEv(void *);
extern int data_ov002_0210e0dc[];
}

s32 daObjWakame_c::CleanupResources() {
    _ZN13SharedFilePtr7ReleaseEv(data_ov002_0210e0dc);
    _ZN13SharedFilePtr7ReleaseEv(data_ov002_0210e0d4);
    return 1;
}
