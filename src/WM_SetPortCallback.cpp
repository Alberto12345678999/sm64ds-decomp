//cpp
#include "IRQ.h"

extern "C" {

extern int WMi_CheckInitialized(void);
extern char *WM_GetSystemWork(void);

/* WM_GetSystemWork's WMArm9Buf, the per-port tables this function fills,
 * with NitroSDK's names (WmDataSharingSetDataCallback, the data-sharing send callback,
 * looks its argument up in the second one by port). */
typedef struct WMArm9Buf {
    char pad_00[0xac];
    void *portCallbackTable[16];    /* 0x0ac */
    void *portCallbackArgument[16]; /* 0x0ec */
} WMArm9Buf;

/* NitroSDK wm_sync.c WM_SetPortCallback: store port's receive callback
 * and its argument, with interrupts off. ILLEGAL_STATE (3) before WM_Init
 * (WMi_CheckInitialized), else WM_ERRCODE_SUCCESS. */
int WM_SetPortCallback(int port, int callback, int arg) {
    int token = IRQ::Disable();
    int r = WMi_CheckInitialized();
    if (r != 0) {
        IRQ::Restore(token);
        return r;
    }
    {
        WMArm9Buf *sys = (WMArm9Buf *)WM_GetSystemWork();
        sys->portCallbackTable[port] = (void *)callback;
        sys->portCallbackArgument[port] = (void *)arg;
    }
    IRQ::Restore(token);
    return 0;
}
}
