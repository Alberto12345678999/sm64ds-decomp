//cpp
#include "types.h"
#include "IRQ.h"

extern "C" {

struct Obj {
    char pad[0x64];
    u32 unk64;
};

typedef struct {
    u32 *f0;            /* 0x00 */
    char pad4[0x24];    /* 0x04 */
    void (*cb)(void *); /* 0x28 */
    void *cb_arg;       /* 0x2c */
    char pad30[4];      /* 0x30 */
    u32 flags;          /* 0x34 */
    char pad38[4];      /* 0x38 */
    struct Obj obj;     /* 0x3c */
    char pada4[0x30];   /* 0xa4 */
    u16 fd4;            /* 0xd4 */
} G;

extern G cardi_common;

void OS_WakeupThread(u16 *self);
void OS_WakeupThreadDirect(struct Obj *self);

void CARDi_ReadEnd(void) {
    int gi = (int)&cardi_common;
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
        OS_WakeupThreadDirect(&g->obj);
    }
    IRQ::Restore(s);
    if (cb) {
        cb(arg);
    }
}
}
