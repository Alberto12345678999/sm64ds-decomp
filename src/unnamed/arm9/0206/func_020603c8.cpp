//cpp
#include "types.h"
#include "nitro/os/thread.h"
extern "C" {
extern char cardi_common[];
void func_02060364(int arg);
void func_020607e8(void* thiz);
}
namespace IRQ { unsigned int Disable(); void Restore(unsigned int); }

struct Sched {
    char pad00[0x28];
    int d;      // 0x28
    int e;      // 0x2c
    char pad30[0x34-0x30];
    u32 flags;  // 0x34
    char pad38[0xd4-0x38];
    u16 sub; // 0xd4
};

extern "C" void func_020603c8(int arg)
{
    Sched* g = (Sched*)cardi_common;
    unsigned int irq = IRQ::Disable();
    if (g->flags & 4) {
        do {
            OS_SleepThread(&g->sub);
        } while (g->flags & 4);
    }
    u32* fp = (u32*)((unsigned long long)((int)g + 0x34));
    *fp |= 4;
    IRQ::Restore(irq);
    func_02060364(arg);
    g->d = 0;
    g->e = 0;
    *(OSThread **)(cardi_common + 0xd0) = data_020a6134.current;
    func_020607e8(g);
}
