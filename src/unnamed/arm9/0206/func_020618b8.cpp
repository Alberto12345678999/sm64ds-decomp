#include "types.h"
extern void *WM_GetSystemWork(void);
extern int func_0206152c(void);
extern void _ZN4CP1519InvalidateDataCacheEjj(unsigned int addr, unsigned int n);

/* NitroSDK WMStatus and WMArm9Buf, the fields read here; the names follow
 * func_02061ab0's views (status at +0x04) and include/WmWork.h's WmStatus
 * (child_bitmap at 0x17e). */
typedef struct WMStatus {
    u16 state; /* 0x000 -- 9 MP_PARENT, 0xa MP_CHILD, 0xb DCF_CHILD */
    char pad_002[0xb8 - 0x2];
    /* 0x0b8 -- the AIDs MP data can go to (medium: the SDK's name for
     * the MP-ready bitmap; only this function reads it) */
    u16 mp_readyBitmap;
    char pad_0ba[0x17e - 0xba];
    u16 child_bitmap; /* 0x17e -- connected children, by AID bit */
} WMStatus;

typedef struct WMArm9Buf {
    char pad_00[4];
    WMStatus *status; /* 0x04 */
} WMArm9Buf;

/* The AIDs MP data can go to (NitroSDK's MP-ready AID query, medium): 0
 * unless MP is running, as a parent with at least one child or as a child;
 * each status field is invalidated from the data cache before it is read. */
int func_020618b8(void)
{
    WMArm9Buf *sys = (WMArm9Buf *)WM_GetSystemWork();
    WMStatus *status;
    if (func_0206152c())
        return 0;
    _ZN4CP1519InvalidateDataCacheEjj((unsigned int)&sys->status->state, 2);
    status = sys->status;
    switch (status->state) {
    case 9:
        _ZN4CP1519InvalidateDataCacheEjj((unsigned int)&status->child_bitmap, 2);
        status = sys->status;
        if (status->child_bitmap == 0)
            return 0;
        /* fall through */
    case 0xa:
    case 0xb:
        _ZN4CP1519InvalidateDataCacheEjj((unsigned int)&status->mp_readyBitmap, 2);
        return sys->status->mp_readyBitmap;
    }
    return 0;
}
