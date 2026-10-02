//cpp
// @symbol _ZN16daObjFl_Puzzle_c16CleanupResourcesEv
/* recovered: named members + shared header, real C++ method, declarations from a shared header */
#include "decl_common.h"
/* recovered: named members + shared header, real C++ method */
#include "daObjFl_Puzzle_c.h"
#include "SharedFilePtr.h"
#include "dBgW.h"
extern void *data_ov064_0211adc8[];
extern void *data_ov064_0211c800;

int daObjFl_Puzzle_c::CleanupResources()
{
    unsigned char idx;
    ((dBgW *)((char *)&mMeshCollider))->Disable();
    idx = *(unsigned char *)((char *)&mType);
    ((SharedFilePtr *)(data_ov064_0211adc8[idx]))->Release();
    ((SharedFilePtr *)(&data_ov064_0211c800))->Release();
    return 1;
}
