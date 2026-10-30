#include "types.h"
#include "nitro/os/spinLock.h"

extern void CpuSet(void* src, void* dst, u32 ctrl);
extern u8 data_020a9de0[];

void func_0206a5c0(void) {
    u32 local = 0;
    CpuSet(&local, data_020a9de0, 0x5000001);
    *(u16 *)(data_020a9de0 + 2) = (u16)OS_GetLockID();
}
