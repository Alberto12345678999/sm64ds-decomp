//cpp
#include "types.h"
#include "IRQ.h"
#include "nitro/os/thread.h"

extern "C" {

extern void func_020589ac(void* node, void* self);

/* The Nitro SDK's OSMutex, this SDK's layout (see func_02058b9c.c). */
struct OSMutex {
    u16 queue;        /* 0x00 -- threads waiting for the mutex */
    OSThread *thread; /* 0x04 -- the owner, 0 while free */
    s32 count;        /* 0x08 */
};

/* The Nitro SDK's OS_LockMutex: take the mutex, or sleep on its queue until
 * the owner releases it. A thread that already owns it locks it again. */
void func_02058b08(struct OSMutex *mutex) {
    u32 saved = IRQ::Disable();
    OSThread *current = data_020a6134.current;

    for (;;) {
        if (mutex->thread == 0) {
            mutex->thread = current;
            mutex->count++;
            func_020589ac(current, mutex);
            break;
        }
        if (mutex->thread == current) {
            mutex->count++;
            break;
        }
        current->mutex = mutex;
        OS_SleepThread(&mutex->queue);
        current->mutex = 0;
    }

    IRQ::Restore(saved);
}
}
