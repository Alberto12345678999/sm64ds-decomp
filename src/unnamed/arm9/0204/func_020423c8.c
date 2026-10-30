#include "nitro/os/thread.h"

/* A worker thread; its 0x400-byte stack is data_020a11e4, just below it
 * (func_02042200 creates it). */
extern OSThread data_020a15e4;

void func_020423c8(void) {
    OS_WakeupThreadDirect(&data_020a15e4);
}
