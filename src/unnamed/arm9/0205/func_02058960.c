#include "nitro/os/thread.h"

/* The Nitro SDK's OSMutex, this SDK's layout: the wait queue is a 16-bit
 * mask of thread ids, as everywhere in this os_thread.c. */
struct OSMutex {
    u16 queue;            /* 0x00 */
    u16 pad02;            /* 0x02 */
    OSThread *thread;     /* 0x04 -- the owner */
    s32 count;            /* 0x08 */
    struct OSMutex *prev; /* 0x0c -- the owner's held-mutex list */
    struct OSMutex *next; /* 0x10 */
};

/* Unlinks and returns the first mutex a thread holds (pret's
 * OSi_RemoveMutexLinkFromQueue, which takes the queue rather than the thread
 * and checks for an empty list). */
struct OSMutex *func_02058960(OSThread *thread) {
    struct OSMutex *mutex = thread->mutexQueue.head;
    struct OSMutex *next = mutex->next;
    if (next == 0)
        thread->mutexQueue.tail = 0;
    else
        next->prev = 0;
    thread->mutexQueue.head = next;
    return mutex;
}
