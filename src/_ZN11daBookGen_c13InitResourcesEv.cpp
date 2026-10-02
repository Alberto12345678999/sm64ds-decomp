//cpp
#include "Model.h"
// @symbol _ZN11daBookGen_c13InitResourcesEv
/* recovered: named members + shared header, real C++ method, declarations from a shared header */
#include "decl_common.h"
/* recovered: named members + shared header, real C++ method */
#include "daBookGen_c.h"
extern int data_ov020_02114ab8[];
extern "C" {
extern void LoadBlueCoinModel(void *);
}
extern int data_ov020_02114aa0[];

int daBookGen_c::InitResources()
{
    mSpawnTimer = 0;
    Model::LoadFile(*(SharedFilePtr *)data_ov020_02114aa0);
    Model::LoadFile(*(SharedFilePtr *)data_ov020_02114ab8);
    LoadBlueCoinModel(((char *)this));
    return 1;
}
