//cpp
// @symbol _ZN11daBookGen_c16CleanupResourcesEv
/* recovered: named members + shared header, real C++ method */
#include "daBookGen_c.h"
class SharedFilePtr {
public:
    void Release();
};

extern "C" {
extern void UnloadBlueCoinModel(void *c);
}
extern int data_ov020_02114aa0;
extern int data_ov020_02114ab8;

int daBookGen_c::CleanupResources()
{
    ((SharedFilePtr *)&data_ov020_02114aa0)->Release();
    ((SharedFilePtr *)&data_ov020_02114ab8)->Release();
    UnloadBlueCoinModel(((char *)this));
    return 1;
}
