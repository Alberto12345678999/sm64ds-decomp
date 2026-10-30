//cpp
#include "types.h"
#include "AsyncJob.h"
#include "Memory.h"

extern "C" {

extern void OS_CreateThread(void *c, int f, int a, int p, unsigned int s, unsigned int x);
extern void OS_SetThreadStackWarningOffset(void *c, unsigned int v);
extern void OS_WakeupThreadDirect(void *c);
extern unsigned char data_0209d4f8;
extern int data_0209d518;
extern char data_0209d5b8[];

#pragma opt_common_subs off
#pragma opt_propagation off
int func_0201a244(AsyncJobCallback callback, int argument, int priority, int stackBase,
                  int stackSize) {
    int stack;
    int size;
    if (data_0209d4f8 != 0) {
        callback(argument);
        return 1;
    }
    data_0209d4f8 = 1;
    size = stackSize;
    stack = stackBase;
    if (stackBase == 0) {
        stack = (int)Memory::Allocate(size, -4);
        data_0209d518 = stack;
    }
    /* The unreconstructed OS thread API still takes its entry as a 32-bit address. */
    OS_CreateThread(data_0209d5b8, (int)callback, argument, stack + size, size, priority);
    OS_SetThreadStackWarningOffset(data_0209d5b8, 0x400);
    OS_WakeupThreadDirect(data_0209d5b8);
    return 0;
}
}
