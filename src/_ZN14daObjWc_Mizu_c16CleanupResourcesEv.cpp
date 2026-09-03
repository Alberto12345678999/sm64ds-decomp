//cpp
// @symbol _ZN14daObjWc_Mizu_c16CleanupResourcesEv
/* recovered: named members + shared header, real C++ method, declarations from a shared header */
#include "decl_common.h"
/* recovered: named members + shared header, real C++ method */
#include "daObjWc_Mizu_c.h"
#include "SharedFilePtr.h"
#include "dBgW.h"
extern int daObjWc_Obj07_c_ClsnFile[];
extern int daObjWc_Obj07_c_ModelFile[];

int daObjWc_Mizu_c::CleanupResources()
{
    if (((dBgW *)((char *)&(*(u8 *)&mMeshCollider)))->IsEnabled()) {
        ((dBgW *)((char *)&(*(u8 *)&mMeshCollider)))->Disable();
    }
    ((SharedFilePtr *)(daObjWc_Obj07_c_ModelFile))->Release();
    ((SharedFilePtr *)(daObjWc_Obj07_c_ClsnFile))->Release();
    return 1;
}
