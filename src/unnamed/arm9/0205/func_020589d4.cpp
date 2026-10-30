//cpp
#include "IRQ.h"
#include "nitro/os/thread.h"

extern "C" {

/* The Nitro SDK's OSMutex, this SDK's layout (see func_02058b9c.c). */
struct OSMutex {
    u16 queue;        /* 0x00 */
    OSThread *thread; /* 0x04 -- the owner, 0 while free */
    s32 count;        /* 0x08 */
};

/* The Nitro SDK's OS_TryLockMutex: lock the mutex when it is free or the
 * current thread already owns it. This SDK's version does not link the
 * mutex into the owner's held-mutex list. */
int func_020589d4(struct OSMutex *mutex) {
    unsigned int saved = IRQ::Disable();
    OSThread *current = data_020a6134.current;
    int locked;
    if (mutex->thread == 0) {
        mutex->thread = current;
        mutex->count++;
        locked = 1;
    } else if (mutex->thread == current) {
        mutex->count++;
        locked = 1;
    } else {
        locked = 0;
    }
    IRQ::Restore(saved);
    return locked;
}
}
