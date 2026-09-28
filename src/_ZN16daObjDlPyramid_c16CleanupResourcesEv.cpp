//cpp
// @symbol _ZN16daObjDlPyramid_c16CleanupResourcesEv
/* recovered: named members + shared header, real C++ method, declarations from a shared header */
#include "decl_common.h"
/* recovered: named members + shared header, real C++ method */
#include "daObjDlPyramid_c.h"
#include "SharedFilePtr.h"
#include "dBgW.h"
extern int data_ov024_02113968[];

int daObjDlPyramid_c::CleanupResources()
{
    ((dBgW *)((char *)&(*(u8 *)&mMeshCollider)))->Disable();
    ((SharedFilePtr *)(data_ov024_02113968))->Release();
    ((SharedFilePtr *)(data_ov024_02113960))->Release();
    return 1;
}
