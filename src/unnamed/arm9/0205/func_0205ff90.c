#include "nitro/os/spinLock.h"

extern void func_020600e0(int lockID, int target);

void func_0205ff90(u16 lockID) {
    OS_UnlockCard(lockID);
    func_020600e0(lockID, 1);
}
