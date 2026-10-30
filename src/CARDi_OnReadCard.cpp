//cpp
#include "IRQ.h"

extern "C" {

extern void func_02059f58(int x);
extern void CARDi_ReadEnd(void);
extern void CARDi_SetCardDma(void);

typedef struct {
    char pad[0x18];
    int f18;
    int f1c;
    int f20;
    int f24;
} G;

extern G cardi_common;

#define g (&cardi_common)
void CARDi_OnReadCard(void)
{
    g->f18 += 0x200;
    g->f1c += 0x200;
    g->f20 -= 0x200;
    if (g->f20 == 0) {
        func_02059f58(g->f24);
        IRQ::DisableIRQs(0x80000);
        IRQ::ClearInterrupts(0x80000);
        CARDi_ReadEnd();
    } else {
        CARDi_SetCardDma();
    }
}
}
