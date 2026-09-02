//cpp
// @symbol _ZN16daObjBC_Switch_c16CleanupResourcesEv
/* recovered: named members + shared header, real C++ method
 *
 * Disables the collider if it is still enabled -- so a second cleanup is
 * harmless -- then releases the model and collision files.
 */
#include "daObjBC_Switch_c.h"
#include "decl_common.h"

extern "C" {
extern int daObjBC_Switch_c_ClsnFile[];
extern int daObjBC_Switch_c_ModelFile[];
extern void _ZN13SharedFilePtr7ReleaseEv(void *);
}

int daObjBC_Switch_c::CleanupResources()
{
    if (_ZN4dBgW9IsEnabledEv(&mMeshCollider)) {
        _ZN4dBgW7DisableEv(&mMeshCollider);
    }
    _ZN13SharedFilePtr7ReleaseEv(daObjBC_Switch_c_ModelFile);
    _ZN13SharedFilePtr7ReleaseEv(daObjBC_Switch_c_ClsnFile);
    return 1;
}
