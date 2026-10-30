//cpp
#include "IRQ.h"
#include "nitro/os/spinLock.h"

extern "C" {

extern void WaitByLoop(int n);

void func_0206a3a4(u16 lockID, int *out) {
    for (;;) {
        out[1] = IRQ::Disable();
        out[0] = OS_ReadOwnerOfLockCartridge() & OS_MAINP_LOCKED_FLAG;
        if (out[0] != 0)
            return;
        if (OS_TryLockCartridge(lockID) == 0)
            return;
        IRQ::Restore(out[1]);
        WaitByLoop(1);
    }
}
}
