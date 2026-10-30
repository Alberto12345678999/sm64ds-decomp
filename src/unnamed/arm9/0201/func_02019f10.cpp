//cpp
#include "types.h"
#include "CP15.h"
#include "IRQ.h"
#include "nitro/os/thread.h"
#include "nitro/spi/pm.h"

extern "C" {

enum IPCStatus { IPC_SUCCESS = 0, IPC_ERROR = -1, IPC_FIFO_FULL = -2 };

extern enum IPCStatus PXI_SendWordByFifo(u32 arg0, u32 arg1, u32 arg2);
extern int func_02040714(void);
extern void func_02040724(void);
extern void func_0201a4d0(void);
extern unsigned char data_0209d4e4;
extern char data_02086214[];

void func_0201a028(void) {
    for (;;) {
        IRQ::Disable();
        CP15::WaitForInterrupt();
    }
}

void func_02019ff4(void) {
    while (PXI_SendWordByFifo(0xd, 2, 0) != 0) {
    }
    func_0201a028();
}

void func_02019f64(void *arg) {
    int r;
    if (data_0209d4e4 != 0) {
        PM_ForceToPowerOff();
        func_02019ff4();
        return;
    }
    PMi_SendLEDPatternCommand(3);
    PMi_SetLED(1);
    r = func_02040714();
    if (r != 0 && r != 1) {
        do {
            func_02040724();
            func_0201a4d0();
            r = func_02040714();
            if (r == 0)
                break;
        } while (r != 1);
    }
    PMi_SendLEDPatternCommand(1);
    PMi_SetLED(1);
    func_02019ff4();
}

/* The thread sits in the top 0x94 bytes (one OSThread) of the 0x4000
   bytes below data_02086214, and its 0x3f6c-byte stack runs down from
   there through the rest. */
int func_02019f10(void) {
    OSThread *thread = (OSThread *)data_02086214 - 1;
    OS_CreateThread(thread, func_02019f64, 0, thread, 0x3f6c, 0);
    OS_WakeupThreadDirect(thread);
    return 0;
}
}
