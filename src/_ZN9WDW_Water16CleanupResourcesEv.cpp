//cpp
// @symbol _ZN9WDW_Water16CleanupResourcesEv
/* recovered: named members + shared header, real C++ method, declarations from a shared header */
#include "decl_common.h"
/* recovered: named members + shared header, real C++ method */
#include "WDW_Water.h"
#include "SharedFilePtr.h"
#include "dBgW.h"
extern int daObjWc_Obj07_c_ClsnFile[];
extern int daObjWc_Obj07_c_ModelFile[];

int WDW_Water::CleanupResources()
{
    if (((dBgW *)((char *)&(*(u8 *)&mMeshCollider)))->IsEnabled()) {
        ((dBgW *)((char *)&(*(u8 *)&mMeshCollider)))->Disable();
    }
    ((SharedFilePtr *)(daObjWc_Obj07_c_ModelFile))->Release();
    ((SharedFilePtr *)(daObjWc_Obj07_c_ClsnFile))->Release();
    return 1;
}
