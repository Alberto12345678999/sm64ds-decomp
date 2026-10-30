#include "types.h"
#include "nitro/os/spinLock.h"
extern void _ZN3IRQ11SetFIQStateEb(s32 state);
extern void _ZN3IRQ11SetIRQStateEb(s32 state);

/* func_0206ce90 - configure IRQ/FIQ state from flags bitfield */
void func_0206ce90(u32 flags)
{
    if (flags & 0x20) {
        OS_UnLockCartridge(0x70);
    }
    _ZN3IRQ11SetFIQStateEb(flags & 2);
    _ZN3IRQ11SetIRQStateEb(flags & 1);
}