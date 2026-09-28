//cpp
// @symbol _ZN14daChoro_Rock_c16CleanupResourcesEv

#include "daChoro_Rock_c.h"
#include "SharedFilePtr.h"

extern "C" SharedFilePtr data_ov080_021283c8;

s32 daChoro_Rock_c::CleanupResources()
{
    data_ov080_021283c8.Release();
    return 1;
}
