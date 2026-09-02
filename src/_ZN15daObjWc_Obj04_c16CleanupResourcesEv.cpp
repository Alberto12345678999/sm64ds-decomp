//cpp
// @symbol _ZN15daObjWc_Obj04_c16CleanupResourcesEv
/* recovered: named members + shared header, real C++ method, declarations from a shared header */
#include "decl_common.h"
/* recovered: named members + shared header, real C++ method */
#include "daObjWc_Obj04_c.h"
#include "SharedFilePtr.h"
#include "dBgW.h"
extern int data_ov029_02114324[];
extern int data_ov029_0211432c[];

int daObjWc_Obj04_c::CleanupResources()
{
    if (((dBgW *)((char *)&mMeshCollider))->IsEnabled()) {
        ((dBgW *)((char *)&mMeshCollider))->Disable();
    }
    ((SharedFilePtr *)(data_ov029_0211432c))->Release();
    ((SharedFilePtr *)(data_ov029_02114324))->Release();
    return 1;
}
