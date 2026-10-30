//cpp
#include "IRQ.h"
#include "nitro/os/spinLock.h"

extern "C" {

extern int func_02058690(void);
extern int OS_IsRunOnEmulator(void);
extern int func_0205865c(void);
extern int data_0209a040; /* OSi_ConsoleTypeCache, initialised to -1 */

int OS_GetConsoleType(void) {
    if (data_0209a040 == -1) {
        int r4 = func_02058690();
        int flags;
        if (OS_IsRunOnEmulator())
            flags = r4 | 0x10000000;
        else if (func_0205865c())
            flags = r4 | 0x40000000;
        else if (r4 & 0x1000000)
            flags = r4 | 0x20000000;
        else
            flags = r4 | 0x80000000;
        data_0209a040 = flags | *(unsigned short *)0x27ffffa;
    }
    return data_0209a040;
}

int func_02058690(void) {
    int result;
    int done = 0;
    u16 lockID;
    int res;
    unsigned int irq;

    lockID = (u16)OS_GetLockID();
    result = done;

    do {
        res = -1;
        irq = IRQ::Disable();
        if ((OS_ReadOwnerOfLockCartridge() & OS_MAINP_LOCKED_FLAG) != 0 ||
            (res = OS_TryLockCartridge(lockID)) == 0) {
            if (*(unsigned int *)0x8000000 == 0x544e494e &&
                *(unsigned int *)0x8000004 == 0x4f444e45)
                result = 0x1000000;
            else
                result = 0x2000000;
            if (res == 0) {
                OS_UnlockCartridge(lockID);
                done = 1;
            }
        }
        IRQ::Restore(irq);
    } while (done == 0);

    return result;
}

int func_0205865c(void) {
    unsigned a;
    if (*(volatile unsigned short *)0x27ffc10 == 0)
        a = 0x27ff814;
    else
        a = 0x27ffc14;
    return *(volatile unsigned short *)a == 1;
}
}
