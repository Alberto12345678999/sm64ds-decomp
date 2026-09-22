//cpp
// @symbol _ZN21daObjWlKoopaShutter_c16CleanupResourcesEv
#include "daObjWlKoopaShutter_c.h"
// recovered name: daObjWlKoopaShutter_c_CleanupResources
/* recovered: renamed to Class_Method, declarations from a shared header */
#include "decl_common.h"
extern int BowserShutter_ClsnFile[];
/* recovered: renamed to Class_Method */
/* daObjWlKoopaShutter_c::CleanupResources - recovered from vtable slot identity */
extern "C" {
extern void _ZN13SharedFilePtr7ReleaseEv(void *);
extern int BowserShutter_ModelFile[];
}

s32 daObjWlKoopaShutter_c::CleanupResources() {
    void * t = (void *)this;
    if (_ZN4dBgW9IsEnabledEv((char *)t + 0x124)) {
        _ZN4dBgW7DisableEv((char *)t + 0x124);
    }
    _ZN13SharedFilePtr7ReleaseEv(BowserShutter_ModelFile);
    _ZN13SharedFilePtr7ReleaseEv(BowserShutter_ClsnFile);
    return 1;
}
