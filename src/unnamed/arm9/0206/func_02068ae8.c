#include "types.h"
#pragma opt_strength_reduction off
extern u32 _ZN3IRQ7DisableEv(void);
extern void _ZN3IRQ7RestoreEj(u32 prev);

extern char *data_020a9db4;
extern char *data_020a9db8;

extern void MultiStore16(u16 val, char *dst, int nbytes);
extern void func_020672a4(u32 val);
extern void func_0205a588(void *dst, int val, u32 size);
extern void func_020684a8(void);
extern int func_02068d08(void);

extern void func_02066a94(int arg0, char *arg1);
extern void func_02069994(char *arg0);

/* Views over the wireless (NitroSDK WM) work buffer data_020a9db4: 0x3700
 * bytes, 32-byte aligned and zeroed by func_02068e4c. Field names follow the
 * NitroSDK structures where the SDK names them; the rest are named from the
 * reads and writes in func_02068*.c / func_02069*.c / func_0206a230.c.
 * File-local on purpose: keep this block textually identical in every user. */
typedef struct {
    u8 bytes[0xc0];
} WmBssDesc; /* WMBssDesc: WM_StartScan's scanBuf, WM_StartConnect's pInfo */

typedef struct {
    u16 apiid;           /* 0x00 */
    u16 errcode;         /* 0x02 */
    u16 wlCmdID;         /* 0x04 */
    u16 wlResult;        /* 0x06 */
    u16 state;           /* 0x08 */
    u16 macAddress[3];   /* 0x0a: SDK u8[6]; compared here as halfwords */
    u16 channel;         /* 0x10 */
    u16 linkLevel;       /* 0x12 */
    u16 ssidLength;      /* 0x14 */
    u16 ssid[16];        /* 0x16 */
    u16 gameInfoLength;  /* 0x36 */
    u16 gameInfo[0x40];  /* 0x38: WMGameInfo */
} WmStartScanCallback;   /* 0xb8, the MultiCopyHalf length */

typedef struct {
    u16 *userGameInfo;        /* 0x00 */
    u16 userGameInfoLength;   /* 0x04 */
    u16 ggid[2];              /* 0x06: low, high halfword */
    u16 tgid;                 /* 0x0a */
    u16 entryFlag;            /* 0x0c: WM_ATTR_FLAG_ENTRY (1) */
    u16 maxEntry;             /* 0x0e */
    u16 multiBootFlag;        /* 0x10: WM_ATTR_FLAG_MB (2) */
    u16 KS_Flag;              /* 0x12: WM_ATTR_FLAG_KS (4) */
    u16 CS_Flag;              /* 0x14: WM_ATTR_FLAG_CS (8) */
    u16 beaconPeriod;         /* 0x16 */
    u16 rsv[12];              /* 0x18 */
    u16 channel;              /* 0x30 */
    u16 parentMaxSize;        /* 0x32 */
    u16 childMaxSize;         /* 0x34 */
    u16 rsv2[5];              /* 0x36 */
} WmParentParam;              /* 0x40, WM_SetParentParameter's flush length */

typedef struct {
    u8 pad_000[0x17e];
    u16 child_bitmap;    /* 0x17e: copied to WmWork.childBitmap after WM_ReadStatus */
    u8 pad_180[0x880];
} WmStatus;              /* 0xa00 of buffer reserved for WM_ReadStatus */

typedef struct {
    WmBssDesc bssDesc;            /* 0x000: DMA'd from WmWork.scanBuf */
    WmStartScanCallback scan;     /* 0x0c0: copied from the PARENT_FOUND callback */
    u8 pad_178[8];
} WmParentRecord;                 /* 0x180 */

typedef struct {
    u8 wmSysBuf[0x1300];                /* 0x0000: WM_Initialize's work buffer */
    WmParentParam parentParam;          /* 0x1300 */
    WmBssDesc scanBuf;                  /* 0x1340 */
    u16 parentMaxSize;                  /* 0x1400 */
    u16 childMaxSize;                   /* 0x1402 */
    char *sendBuf;                      /* 0x1404: WM_StartMP sendBuf */
    char *recvBuf;                      /* 0x1408: WM_StartMP recvBuf */
    void (*stateCallback)(char *);      /* 0x140c */
    u8 mpSending;                       /* 0x1410 */
    u8 initialized;                     /* 0x1411 */
    u8 pad_1412[6];
    WmStatus status;                    /* 0x1418: WM_ReadStatus buffer */
    u16 sendBufSize;                    /* 0x1e18 */
    u16 recvBufSize;                    /* 0x1e1a */
    void (*userCallback)(int, void *);  /* 0x1e1c */
    int connectBssDesc;                 /* 0x1e20: WM_StartConnect pInfo */
    u16 mode;                           /* 0x1e24: 1 parent, 2 child */
    u16 resetting;                      /* 0x1e26 */
    u16 mpStarted;                      /* 0x1e28 */
    u16 childBitmap;                    /* 0x1e2a */
    u16 mpContinuous;                   /* 0x1e2c */
    u8 pad_1e2e[0xb2];
    u16 parentCount;                    /* 0x1ee0 */
    u16 aid;                            /* 0x1ee2 */
    int scanContinue;                   /* 0x1ee4 */
    int scanNextChannel;                /* 0x1ee8 */
    int lastParentIndex;                /* 0x1eec */
    u8 pad_1ef0[0x10];
    WmParentRecord parents[16];         /* 0x1f00 */
} WmWork;                               /* 0x3700 */

#define WM_WORK ((WmWork *)data_020a9db4)

int func_02068ae8(int param0)
{
    u32 saved;
    volatile u16 sp0;
    volatile u16 sp2;
    u32 cb;
    int i;
    int result;

    saved = _ZN3IRQ7DisableEv();

    WM_WORK->parentParam.channel = param0;

    cb = *(u32 *)(data_020a9db8 + 0x1000 + 0x4e4);

    sp0 = 0;
    MultiStore16(sp0, data_020a9db8 + 0x1340, 0x60a0);

    func_020672a4(cb);

    *(int *)(data_020a9db8 + 0x1000 + 0x318) = WM_WORK->parentMaxSize - 6;
    *(int *)(data_020a9db8 + 0x1000 + 0x31c) = WM_WORK->childMaxSize - 2;
    *(int *)(data_020a9db8 + 0x1000 + 0x320) = 30 / (WM_WORK->childMaxSize - 2);

    for (i = 0; i < 0xf; i++) {
        *(int *)(data_020a9db8 + 0x1000 + 0x4e8 + i * 4) = 0;
        *(s8 *)(data_020a9db8 + 0x1000 + 0x526 + i) = -1;
    }
    *(u8 *)(data_020a9db8 + 0x1000 + 0x524) = 0;

    sp2 = 0;
    MultiStore16(sp2, data_020a9db8 + 0x1788, 0x5c40);

    func_0205a588(data_020a9db8 + 0x1754, 0, 0x1e);

    WM_WORK->mode = 1;
    WM_WORK->userCallback = (void (*)(int, void *))func_02066a94;
    WM_WORK->stateCallback = func_02069994;

    WM_WORK->parentParam.parentMaxSize = WM_WORK->parentMaxSize;
    WM_WORK->sendBufSize =
        (WM_WORK->parentParam.parentMaxSize + 0x23) & ~0x1f;

    WM_WORK->parentParam.childMaxSize = WM_WORK->childMaxSize;
    WM_WORK->recvBufSize =
        (((WM_WORK->parentParam.childMaxSize + 0xe) * 0xf + 0x29) & ~0x1f) << 1;

    func_020684a8();
    result = func_02068d08();

    _ZN3IRQ7RestoreEj(saved);

    return result;
}
