#include "nitro/os/thread.h"

/* The Nitro SDK's OSMutex, this SDK's layout (see func_02058960.c). */
struct OSMutex {
    u16 queue;            /* 0x00 */
    u16 pad02;            /* 0x02 */
    OSThread *thread;     /* 0x04 -- the owner */
    s32 count;            /* 0x08 */
    struct OSMutex *prev; /* 0x0c */
    struct OSMutex *next; /* 0x10 */
};

/* local extern: no header declares os_mutex.c's functions yet. */
extern struct OSMutex *func_02058960(OSThread *thread);

/* The Nitro SDK's OSi_UnlockAllMutex: OS_ExitThread releases every mutex
 * the exiting thread still holds and wakes its waiters. */
void func_02058a44(OSThread *thread) {
    struct OSMutex *mutex;
    while (thread->mutexQueue.head != 0) {
        mutex = func_02058960(thread);
        mutex->count = 0;
        mutex->thread = 0;
        OS_WakeupThread(&mutex->queue);
    }
}
