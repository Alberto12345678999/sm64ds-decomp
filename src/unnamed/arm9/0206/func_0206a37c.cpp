//cpp
/* func_0206a37c at 0x0206a37c
 *
 * Matched byte-for-byte with mwccarm 1.2/sp2p3 (arm9 main).
 */
#include "IRQ.h"
#include "nitro/os/spinLock.h"

extern "C" {

void func_0206a37c(u16 lockID, int *p) {
    if (p[0] == 0)
        OS_UnLockCartridge(lockID);
    IRQ::Restore(p[1]);
}
}
