//cpp
/* NitroSDK wm_system.c WM_SetIndCallback: install callback for the
 * indications ARM7 sends outside any request's own callback, with
 * interrupts off. WM_ERRCODE_ILLEGAL_STATE (3) before WM_Init, else
 * WM_ERRCODE_SUCCESS. */
#include "IRQ.h"

extern "C" {

extern int WMi_CheckInitialized(void);
extern void *WM_GetSystemWork(void);

/* NitroSDK WMArm9Buf, as far as this function writes it. */
struct WMArm9Buf {
    char pad_00[0xa8];
    int indCallback; /* 0xa8 */
};

int WM_SetIndCallback(int callback) {
    int enabled = IRQ::Disable();
    int result = WMi_CheckInitialized();
    if (result != 0) {
        IRQ::Restore(enabled);
        return result;
    }
    ((WMArm9Buf *)WM_GetSystemWork())->indCallback = callback;
    IRQ::Restore(enabled);
    return 0;
}
}
