//cpp
/* NitroSDK wm_system.c WM_ReadStatus: copy the status block ARM7 shares
 * (0x930 bytes, invalidated from the data cache first) into statusBuf.
 * WM_ERRCODE_ILLEGAL_STATE (3) before WM_Init, WM_ERRCODE_INVALID_PARAM
 * (6) for a null statusBuf, else WM_ERRCODE_SUCCESS. */
#include "types.h"
#include "CP15.h"

extern "C" {

extern int WM_GetSystemWork(void);
extern int WMi_CheckInitialized(void);
extern void MultiCopy32Bytes(int *src, int *dst, int len);

/* NitroSDK WMArm9Buf, as far as this function reads it. */
struct WMArm9Buf {
    void *WM7;   /* 0x00 */
    int *status; /* 0x04 -- the block ARM7 keeps up to date */
};

int WM_ReadStatus(int *statusBuf) {
    WMArm9Buf *sys = (WMArm9Buf *)WM_GetSystemWork();
    int result = WMi_CheckInitialized();
    if (result != 0)
        return result;
    if (statusBuf == 0)
        return 6;
    CP15::InvalidateDataCache((u32)sys->status, 0x930);
    MultiCopy32Bytes(sys->status, statusBuf, 0x930);
    return 0;
}
}
