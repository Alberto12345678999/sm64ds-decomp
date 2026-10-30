//cpp
#include "Memory.h"
#include "nitro/os/thread.h"

extern "C" {

extern unsigned char data_0209d4f8;
extern OSThread data_0209d5b8;
extern void *data_0209d518;

int func_0201a1bc(void)
{
    if (data_0209d4f8 == 0) return 1;
    if (OS_IsThreadTerminated(&data_0209d5b8) == 0)
        return 0;
    if (data_0209d518 != 0) {
        Memory::Deallocate(data_0209d518);
        data_0209d518 = 0;
    }
    data_0209d4f8 = 0;
    return 1;
}
}
