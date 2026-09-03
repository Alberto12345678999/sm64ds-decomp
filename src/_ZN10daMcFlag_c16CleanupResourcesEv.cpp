//cpp
// @symbol _ZN10daMcFlag_c16CleanupResourcesEv
#include "daMcFlag_c.h"
#include "SharedFilePtr.h"

extern SharedFilePtr data_ov009_02113eb8;
extern SharedFilePtr data_ov009_02113eb0;

int daMcFlag_c::CleanupResources()
{
    data_ov009_02113eb8.Release();
    data_ov009_02113eb0.Release();
    return 1;
}
