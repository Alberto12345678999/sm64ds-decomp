//cpp
#include "types.h"
#include "IRQ.h"
#include "nitro/os/thread.h"

extern "C" {

typedef struct {
    u32 *f0;            /* 0x00 */
    char pad4[0x24];    /* 0x04 */
    void (*cb)(void *); /* 0x28 */
    void *cb_arg;       /* 0x2c */
    char pad30[4];      /* 0x30 */
    u32 flags;          /* 0x34 */
    char pad38[4];      /* 0x38 */
    OSThread thread;    /* 0x3c -- the card task thread */
    char padd0[4];      /* 0xd0 */
    u16 fd4;            /* 0xd4 */
} G;

extern G data_020a8180;

void func_02060e38(void) {
    int gi = (int)&data_020a8180;
    G *g = (G *)gi;
    void (*cb)(void *) = g->cb;
    void *arg = g->cb_arg;
    u32 s;
    u32 *pf;

    *g->f0 = 0;
    s = IRQ::Disable();
    pf = (u32 *)((gi + 0x34));
    {
        u32 val = *pf;
        val &= ~0xc;
        *pf = val;
    }
    OS_WakeupThread(&g->fd4);
    if (g->flags & 0x10) {
        OS_WakeupThreadDirect(&g->thread);
    }
    IRQ::Restore(s);
    if (cb) {
        cb(arg);
    }
}
}
