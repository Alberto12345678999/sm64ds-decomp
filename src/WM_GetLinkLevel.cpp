//cpp
#include "types.h"
#include "CP15.h"

extern "C" {

extern void *WM_GetSystemWork(void);
extern int WMi_CheckInitialized(void);

/* NitroSDK WMStatus and WMArm9Buf, the fields read here. This SDK's WMStatus
 * puts linkLevel and child_bitmap 4 bytes lower than pret's pokediamond
 * (0xbc, 0x182). */
typedef struct WMStatus {
    u16 state; /* 0x000 -- 9 MP_PARENT, 0xa MP_CHILD, 0xb DCF_CHILD */
    char pad_002[0xb8 - 0x2];
    u16 linkLevel; /* 0x0b8 -- WMLinkLevel, 0 (weakest) to 3 */
    char pad_0ba[0x17e - 0xba];
    u16 child_bitmap; /* 0x17e -- connected children, by AID bit */
} WMStatus;

typedef struct WMArm9Buf {
    char pad_00[4];
    WMStatus *status; /* 0x04 */
} WMArm9Buf;

/* NitroSDK wm_sync.c WM_GetLinkLevel, by body against pret's pokediamond
 * WM_sync.s: the radio link level, or 0 unless MP or DCF is running, as a
 * parent with at least one child or as a child. Each status field is
 * invalidated from the data cache before it is read. */
int WM_GetLinkLevel(void) {
    WMArm9Buf *sys = (WMArm9Buf *)WM_GetSystemWork();
    WMStatus *status;
    if (WMi_CheckInitialized())
        return 0;
    CP15::InvalidateDataCache((unsigned int)&sys->status->state, 2);
    status = sys->status;
    switch (status->state) {
    case 9:
        CP15::InvalidateDataCache((unsigned int)&status->child_bitmap, 2);
        status = sys->status;
        if (status->child_bitmap == 0)
            return 0;
        /* fall through */
    case 0xa:
    case 0xb:
        CP15::InvalidateDataCache((unsigned int)&status->linkLevel, 2);
        return sys->status->linkLevel;
    }
    return 0;
}
}
