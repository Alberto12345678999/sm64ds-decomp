#include "types.h"
u16 WM_GetAllowedChannel(void);

typedef struct {
    char pad[4];
    u16 f4;
} Obj;

/* Step a WMScanParam's channel (+4) to the next channel in the allowed mask
   (WM_GetAllowedChannel), counting 1..16 and wrapping. Returns 0 when no channel is
   allowed. When the current channel is the only one allowed it is left as
   it is. func_020690b0 calls it between scans when scanNextChannel is set. */
int func_0206a29c(Obj *self) {
    u16 mask;
    u16 v;
    u16 i;
    u16 cur;
    mask = WM_GetAllowedChannel();
    if (mask == 0) return 0;
    cur = self->f4;
    i = 0;
    v = cur;
    do {
        if (mask & (1 << (v - 1))) {
            if (cur != v) {
                self->f4 = v;
                break;
            }
        }
        i = i + 1;
        v = (v == 0x10) ? 1 : v + 1;
    } while (i < 0x10);
    return 1;
}
