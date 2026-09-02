//cpp
// @symbol _ZN20daObjWanwanShutter_c16CleanupResourcesEv
/* recovered: named members + shared header, real C++ method, declarations from a shared header */
#include "decl_common.h"
/* recovered: named members + shared header, real C++ method */
#include "daObjWanwanShutter_c.h"
#include "SharedFilePtr.h"
#include "dBgW.h"
extern int data_ov014_021149b8[];
extern int data_ov014_021149c0[];

int daObjWanwanShutter_c::CleanupResources()
{
    if (((dBgW *)((char *)&(*(u8 *)&mMeshCollider)))->IsEnabled()) {
        ((dBgW *)((char *)&(*(u8 *)&mMeshCollider)))->Disable();
    }
    ((SharedFilePtr *)(data_ov014_021149c0))->Release();
    ((SharedFilePtr *)(data_ov014_021149b8))->Release();
    return 1;
}
