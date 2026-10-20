#include "types.h"
/* func_020690b0 @ 0x020690b0 (arm9, size 0x868)   [mwccarm 1.2/sp2p3, 2004/b56]
 * Wireless (WM) child-side callback: scan, connect, then start MP. Each
 * PARENT_FOUND result lands in WmWork.parents[]: the record's first 0xc0 bytes
 * are the WMBssDesc DMA'd from the scan buffer, and +0xc0 is a copy of the
 * 0xb8-byte WMStartScanCallback itself (macAddress at +0xa, gameInfoLength at
 * +0x36, gameInfo at +0x38). An earlier banner called that copy a WMBssDesc;
 * the MultiCopyHalf source (the callback) and length (0xb8) say otherwise.
 */
extern char *data_020a9db4;
extern char *data_020a9db8;
extern u16 data_020a9db0;
extern char data_020a9dc0[];

extern int func_020621b8(void *fn);
extern void func_0206879c(int a, int b);
extern int func_02061c20(void *p);
extern int func_02063574(void *fn, int a, int b, int c);
extern int func_02061ee4(void *fn, void *p);
extern int func_02061e38(void *fn, int a, int b);
extern int func_02061c88(int a, void *fn, int c);
extern int func_020625fc(void *fn, int a, u16 b, int c, u16 d, u16 e, int f,
                         int g, int h, int i, int j);
extern int func_0206a230(void);
extern int func_0206a29c(void *p);
extern int func_02068a74(void);
extern void func_02069918(void);
extern void _ZN4CP1519InvalidateDataCacheEjj(u32 addr, u32 n);
extern void DMASyncHalfTransfer(u32 ch, void *src, void *dst, u32 n);
extern void MultiCopyHalf(void *src, void *dst, u32 n);

void func_020690b0(char *arg0);

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

/* WMScanParam (data_020a9dc0), WM_StartScan's argument; func_0206a29c steps
 * its channel through the allowed-channel mask. */
typedef struct {
    WmBssDesc *scanBuf;  /* 0x0 */
    u16 channel;         /* 0x4 */
    u16 maxChannelTime;  /* 0x6 */
    u16 bssid[3];        /* 0x8: SDK u8[6]; all 0xffff = any parent */
} WmScanParam;

#define SCAN_PARAM ((WmScanParam *)data_020a9dc0)

/* Leading fields of WMStartConnectCallback. */
typedef struct {
    u16 apiid;     /* 0x0 */
    u16 errcode;   /* 0x2 */
    u16 wlCmdID;   /* 0x4 */
    u16 wlResult;  /* 0x6 */
    u16 state;     /* 0x8 */
    u16 aid;       /* 0xa */
} WmStartConnectCallback;

/* The 0x80-byte WMGameInfo, copied as one struct. */
typedef struct {
    u16 w[0x40];
} GameInfo;

static inline void RecordScannedParent(WmWork *const w, char *arg0) {
    WmStartScanCallback *const cb = (WmStartScanCallback *)arg0;
    WmParentRecord *tbl = w->parents;
    int i;
    for (i = 0; i < w->parentCount; i++) {
        if (cb->macAddress[0] == tbl[i].scan.macAddress[0] &&
            cb->macAddress[1] == tbl[i].scan.macAddress[1] &&
            cb->macAddress[2] == tbl[i].scan.macAddress[2]) {
            tbl[i].scan.gameInfoLength = cb->gameInfoLength;
            *(GameInfo *)tbl[i].scan.gameInfo = *(GameInfo *)cb->gameInfo;
            _ZN4CP1519InvalidateDataCacheEjj((u32)&w->parents[i], 0xc0);
            DMASyncHalfTransfer(data_020a9db0, &w->scanBuf, &w->parents[i], 0xc0);
            w->lastParentIndex = i;
            return;
        }
    }
    if (i < 0x10) {
        w->parentCount = i + 1;
        MultiCopyHalf(arg0, &tbl[i].scan, 0xb8);
        _ZN4CP1519InvalidateDataCacheEjj((u32)&w->parents[i], 0xc0);
        DMASyncHalfTransfer(data_020a9db0, &w->scanBuf, &w->parents[i], 0xc0);
        w->lastParentIndex = i;
    }
}

#define DISPATCH(a, b) w->userCallback((a), (b))

void func_020690b0(char *arg0)
{
    WmWork *const w = (WmWork *)data_020a9db4;

    if (w->resetting != 0) {
        if (*(u16 *)arg0 == 1) {
            if (*(u16 *)(arg0 + 2) == 0) {
                func_0206879c(2, func_020621b8((void *)func_020690b0));
                return;
            }
            w->resetting = 0;
            DISPATCH(0x100, arg0);
            return;
        }
        if (*(u16 *)arg0 != 2) return;
        if (*(u16 *)(arg0 + 2) == 0) {
            w->initialized = 0;
            *(u16 *)(data_020a9db8 + 0x1300 + 0x16) = 0;
            DISPATCH(0x11, arg0);
            return;
        }
        w->resetting = 0;
        DISPATCH(0x100, arg0);
        return;
    }

    switch (*(u16 *)arg0) {
    case 0:
        if (*(u16 *)(arg0 + 2) == 0) {
            DISPATCH(0x15, arg0);
            func_0206879c(0x83, func_02061c20(&w->status));
            func_0206879c(0x1d, func_02063574((void *)func_020690b0, 0xffff, 0x28, 5));
            return;
        }
        DISPATCH(0x100, arg0);
        return;

    case 0x1d:
        if (*(u16 *)(arg0 + 2) == 0) {
            SCAN_PARAM->scanBuf = &w->scanBuf;
            if (SCAN_PARAM->channel == 0) SCAN_PARAM->channel = 1;
            if (SCAN_PARAM->maxChannelTime == 0) SCAN_PARAM->maxChannelTime = 0xc8;
            SCAN_PARAM->bssid[0] = 0xffff;
            SCAN_PARAM->bssid[1] = 0xffff;
            SCAN_PARAM->bssid[2] = 0xffff;
            w->scanContinue = 1;
            w->scanNextChannel = 1;
            func_0206879c(0xa, func_02061ee4((void *)func_020690b0, data_020a9dc0));
            return;
        }
        DISPATCH(0x100, arg0);
        return;

    case 0xa:
        if (*(u16 *)(arg0 + 2) == 0) {
            switch (*(u16 *)(arg0 + 8)) {
            case 3:
                return;
            case 5:
                RecordScannedParent(w, arg0);
                DISPATCH(4, arg0);
                if (w->scanContinue == 0) return;
                if (w->scanNextChannel != 0 && func_0206a29c(data_020a9dc0) == 0)
                    func_0206879c(2, func_02068a74());
                func_0206879c(0xa, func_02061ee4((void *)func_020690b0, data_020a9dc0));
                return;
            case 4:
                DISPATCH(5, arg0);
                if (w->scanContinue == 0) return;
                if (w->scanNextChannel != 0 && func_0206a29c(data_020a9dc0) == 0)
                    func_0206879c(2, func_02068a74());
                func_0206879c(0xa, func_02061ee4((void *)func_020690b0, data_020a9dc0));
                return;
            default:
                DISPATCH(0x100, arg0);
                return;
            }
        } else {
            DISPATCH(0x100, arg0);
        }
        return;

    case 0xb:
        if (*(u16 *)(arg0 + 2) == 0) {
            func_0206879c(0xc, func_02061e38((void *)func_020690b0,
                                             w->connectBssDesc, 0));
            return;
        }
        DISPATCH(0x100, arg0);
        return;

    case 0xc:
        if (*(u16 *)(arg0 + 2) == 0) {
            switch (*(u16 *)(arg0 + 8)) {
            case 6:
                return;
            case 7:
                w->aid = ((WmStartConnectCallback *)arg0)->aid;
                DISPATCH(6, arg0);
                w->childBitmap = 1;
                if (func_02061c88(1, (void *)func_02069918, 0) != 0) return;
                func_0206879c(0xe, func_020625fc((void *)func_020690b0,
                                                 (int)w->recvBuf,
                                                 w->recvBufSize,
                                                 (int)w->sendBuf,
                                                 w->sendBufSize,
                                                 (u16)(w->mpContinuous == 0),
                                                 0, 0, 0, 1, 1));
                return;
            case 9:
                DISPATCH(0xa, arg0);
                w->childBitmap = 0;
                return;
            default:
                DISPATCH(0x100, arg0);
                return;
            }
        } else {
            w->parentCount = 0;
            DISPATCH(0xb, arg0);
        }
        return;

    case 0xe:
        switch (*(u16 *)(arg0 + 4)) {
        case 0xa:
            w->mpStarted = 1;
            if (func_0206a230() == 0) return;
            DISPATCH(0x19, 0);
            return;
        case 0xc:
            return;
        case 0xd:
            return;
        default:
            DISPATCH(0x100, arg0);
            return;
        }

    case 0xf:
        w->mpSending = 0;
        if (*(u16 *)(arg0 + 2) == 0)
            DISPATCH(8, arg0);
        else if (*(u16 *)(arg0 + 2) == 9)
            DISPATCH(0x29, arg0);
        else
            DISPATCH(0x12, arg0);
        DISPATCH(0x19, 0);
        return;

    case 0x15:
        if (func_0206a230() == 0) return;
        DISPATCH(0x19, 0);
        return;

    case 0x80:
        return;

    default:
        DISPATCH(0x100, arg0);
        return;
    }
}
