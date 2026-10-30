//cpp
#include "Heap.h"

extern "C" {

extern void OS_InitTick(void);
extern void OS_InitAlarm(void);
typedef void (*OSExceptionHandler)(u32 context, void *arg);
extern void OS_SetUserExceptionHandler(OSExceptionHandler handler, void *arg);
extern void func_0201a054(void);
extern void func_020197b8(void);

/* The game's exception handler: it takes the context and ignores arg. */
extern void func_0201a03c(int context);
extern int data_020a621c;
extern mHeap::Heap_t *data_020a0e9c;

void main(void) {
    OS_InitTick();
    OS_InitAlarm();
    OS_SetUserExceptionHandler((OSExceptionHandler)func_0201a03c, &data_020a621c);
    data_020a0e9c->SetNodeID(2);
    func_0201a054();
    data_020a0e9c->SetNodeID(3);
    func_020197b8();
}
}
