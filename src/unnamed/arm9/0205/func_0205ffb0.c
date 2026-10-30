#include "nitro/os/spinLock.h"

extern void func_02060188(int lockID, int target);

void func_0205ffb0(u16 lockID) {
    func_02060188(lockID, 1);
    OS_TryLockCard(lockID);
}
