//cpp
#include "IRQ.h"
#include "nitro/os/thread.h"

extern "C" {

extern void func_02058988(void *list, char *node);

/* NitroSDK OS_UnlockMutex(mutex): when the current thread owns the mutex,
 * drop one lock; on the last, take it off the thread's mutex list
 * (func_02058988), clear the owner and wake the waiters. OSMutex carries
 * func_02058b9c.c's names. */
typedef struct OSMutex {
    unsigned short queue;    /* 0x00 -- threads waiting for the mutex */
    struct OSThread *thread; /* 0x04 -- the owner, 0 while free */
    int count;               /* 0x08 -- times the owner has locked it */
} OSMutex;

void func_02058a94(char *obj) {
    OSMutex *mutex = (OSMutex *)obj;
    unsigned int saved = IRQ::Disable();
    OSThread *current = data_020a6134.current;
    if (mutex->thread == current) {
        if (--mutex->count == 0) {
            func_02058988(current, obj);
            mutex->thread = 0;
            OS_WakeupThread(&mutex->queue);
        }
    }
    IRQ::Restore(saved);
}
}
