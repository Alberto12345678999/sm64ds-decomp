#include "types.h"
extern char *data_020a9db4;
extern char *data_020a9db8;

extern int func_02061c20(int *arg);
extern void func_0206879c(int x, int kind);
extern int func_02061ce4(void *x);
extern int func_02063574(void *a, int b, int c, int d);
extern int func_020620b0(void *self, char *o);
extern int func_020635d8(void *a, int b);
extern int func_02061fdc(void *x);
extern int func_020625fc(void *arg0, int arg1, int arg2, int arg3, u16 arg4, u16 arg5, u16 arg6, int arg7, int arg8, int arg9, int arg10);
extern int func_0206a230(void);
extern int func_020621b8(void *x);

/* NitroSDK WM views over the wireless work buffer data_020a9db4 (0x3700 bytes,
 * carved by func_02068e4c); per-field evidence is in func_020690b0.c. SDK field
 * names where the SDK has one. File-local: keep this block textually identical
 * in every file that uses it. */
typedef struct {
    unsigned char bytes[0xc0];
} WmBssDesc; /* WMBssDesc */

typedef struct {
    unsigned short apiid;          /* 0x00 */
    unsigned short errcode;        /* 0x02 */
    unsigned short wlCmdID;        /* 0x04 */
    unsigned short wlResult;       /* 0x06 */
    unsigned short state;          /* 0x08 */
    unsigned short macAddress[3];  /* 0x0a, SDK u8[6] */
    unsigned short channel;        /* 0x10 */
    unsigned short linkLevel;      /* 0x12 */
    unsigned short ssidLength;     /* 0x14 */
    unsigned short ssid[16];       /* 0x16 */
    unsigned short gameInfoLength; /* 0x36 */
    unsigned short gameInfo[0x40]; /* 0x38, WMGameInfo */
} WmStartScanCallback;             /* WMStartScanCallback, 0xb8 */

typedef struct {
    unsigned short *userGameInfo;      /* 0x00 */
    unsigned short userGameInfoLength; /* 0x04 */
    unsigned short ggid[2];            /* 0x06 */
    unsigned short tgid;               /* 0x0a */
    unsigned short entryFlag;          /* 0x0c */
    unsigned short maxEntry;           /* 0x0e */
    unsigned short multiBootFlag;      /* 0x10 */
    unsigned short KS_Flag;            /* 0x12 */
    unsigned short CS_Flag;            /* 0x14 */
    unsigned short beaconPeriod;       /* 0x16 */
    unsigned short rsv[12];            /* 0x18 */
    unsigned short channel;            /* 0x30 */
    unsigned short parentMaxSize;      /* 0x32 */
    unsigned short childMaxSize;       /* 0x34 */
    unsigned short rsv2[5];            /* 0x36 */
} WmParentParam;                       /* WMParentParam, 0x40 */

typedef struct {
    unsigned char pad_000[0x17e];
    unsigned short child_bitmap; /* 0x17e */
    unsigned char pad_180[0x880];
} WmStatus; /* WMStatus, WM_ReadStatus's buffer */

typedef struct {
    WmBssDesc bssDesc;        /* 0x000 */
    WmStartScanCallback scan; /* 0x0c0 */
    unsigned char pad_178[8];
} WmParentRecord; /* one scanned parent, 0x180 */

typedef struct {
    unsigned char wmSysBuf[0x1300];    /* 0x0000 */
    WmParentParam parentParam;         /* 0x1300 */
    WmBssDesc scanBuf;                 /* 0x1340 */
    unsigned short parentMaxSize;      /* 0x1400 */
    unsigned short childMaxSize;       /* 0x1402 */
    char *sendBuf;                     /* 0x1404 */
    char *recvBuf;                     /* 0x1408 */
    void (*stateCallback)(char *);     /* 0x140c */
    unsigned char mpSending;           /* 0x1410 */
    unsigned char initialized;         /* 0x1411 */
    unsigned char pad_1412[6];         /* 0x1412 */
    WmStatus status;                   /* 0x1418 */
    unsigned short sendBufSize;        /* 0x1e18 */
    unsigned short recvBufSize;        /* 0x1e1a */
    void (*userCallback)(int, void *); /* 0x1e1c */
    int connectBssDesc;                /* 0x1e20 */
    unsigned short mode;               /* 0x1e24 */
    unsigned short resetting;          /* 0x1e26 */
    unsigned short mpStarted;          /* 0x1e28 */
    unsigned short childBitmap;        /* 0x1e2a */
    unsigned short mpContinuous;       /* 0x1e2c */
    unsigned char pad_1e2e[0xb2];      /* 0x1e2e */
    unsigned short parentCount;        /* 0x1ee0 */
    unsigned short aid;                /* 0x1ee2 */
    int scanContinue;                  /* 0x1ee4 */
    int scanNextChannel;               /* 0x1ee8 */
    int lastParentIndex;               /* 0x1eec */
    unsigned char pad_1ef0[0x10];      /* 0x1ef0 */
    WmParentRecord parents[16];        /* 0x1f00 */
} WmWork;                              /* 0x3700 */

#define WM_WORK ((WmWork *)data_020a9db4)

#define DISPATCH(a, b) WM_WORK->userCallback((a), (b))

void func_02069994(char *arg0)
{
    switch (*(u16 *)arg0) {
    case 0x0:
        if (*(u16 *)(arg0 + 2) == 0) {
            func_0206879c(0x83, func_02061c20((int *)&WM_WORK->status));
            func_0206879c(0x80, func_02061ce4((void*) func_02069994));
            func_0206879c(0x1D, func_02063574((void*) func_02069994, 0xFFFF, 0x28, 5));
            return;
        }
        DISPATCH(0x100, arg0);
        return;

    case 0x1D:
        if (*(u16 *)(arg0 + 2) == 0) {
            func_0206879c(7, func_020620b0((void *)func_02069994, (char *)&WM_WORK->parentParam));
            return;
        }
        DISPATCH(0x100, arg0);
        return;

    case 0x7:
        DISPATCH(0x15, arg0);
        func_0206879c(0x19, func_020635d8((void*) func_02069994, 1));
        return;

    case 0x19:
        if (*(u16 *)(arg0 + 2) == 0) {
            func_0206879c(8, func_02061fdc((void*) func_02069994));
            return;
        }
        DISPATCH(0x100, arg0);
        return;

    case 0x8:
        if (*(u16 *)(arg0 + 2) == 0) {
            switch (*(u16 *)(arg0 + 8)) {
            case 0:
                return;
            case 7:
                func_0206879c(0x83, func_02061c20((int *)&WM_WORK->status));
                WM_WORK->childBitmap = WM_WORK->status.child_bitmap;
                DISPATCH(0, arg0);
                /* WmStatus +0x10: a BOOL WM_ReadStatus fills in; which SDK
                   field it is isn't pinned down here, so it stays raw */
                if (*(int *)(data_020a9db4 + 0x1428) == 0) {
                    char *g8 = data_020a9db8;
                    if (*(int *)(g8 + 0x1324) == 0) {
                        int v = 1;
                        *(int *)(g8 + 0x1324) = 1;
                        if (WM_WORK->mpContinuous != 0) {
                            v = 0;
                        }
                        func_0206879c(0xE,
                                      func_020625fc((void *)func_02069994, (int)WM_WORK->recvBuf,
                                                    WM_WORK->recvBufSize, (int)WM_WORK->sendBuf,
                                                    WM_WORK->sendBufSize, (u16)v, 0, 0, 0, 1, 1));
                        return;
                    }
                }
                if (func_0206a230() == 0) {
                    return;
                }
                DISPATCH(0x19, (void *)0);
                return;
            case 9:
                func_0206879c(0x83, func_02061c20((int *)&WM_WORK->status));
                WM_WORK->childBitmap = WM_WORK->status.child_bitmap;
                DISPATCH(1, arg0);
                return;
            case 2:
                DISPATCH(0x1C, arg0);
                return;
            default:
                DISPATCH(0x100, arg0);
                return;
            }
        } else {
            DISPATCH(0x100, arg0);
            return;
        }

    case 0xE:
        *(int *)(data_020a9db8 + 0x1324) = 0;
        switch (*(u16 *)(arg0 + 4)) {
        case 0xA:
            WM_WORK->mpStarted = 1;
            DISPATCH(0x19, (void *)0);
            return;
        case 0xB:
            DISPATCH(3, *(void **)(arg0 + 8));
            return;
        default:
            DISPATCH(0x100, arg0);
            return;
        }

    case 0xF:
        WM_WORK->mpSending = 0;
        {
            u16 t = *(u16 *)(arg0 + 2);
            if (t == 0) {
                DISPATCH(2, arg0);
                DISPATCH(0x19, (void *)0);
                return;
            }
            if (t == 0xA) {
                DISPATCH(0x2A, arg0);
                return;
            }
            DISPATCH(0x13, arg0);
            DISPATCH(0x19, (void *)0);
            return;
        }

    case 0x1:
        if (*(u16 *)(arg0 + 2) == 0) {
            func_0206879c(2, func_020621b8((void*) func_02069994));
            return;
        }
        WM_WORK->resetting = 0;
        DISPATCH(0x100, arg0);
        return;

    case 0x2:
        if (*(u16 *)(arg0 + 2) == 0) {
            WM_WORK->initialized = 0;
            *(u16 *)(data_020a9db8 + 0x1316) = 0;
            DISPATCH(0x11, arg0);
            return;
        }
        WM_WORK->resetting = 0;
        DISPATCH(0x100, arg0);
        return;

    case 0xD:
        if (*(u16 *)(arg0 + 2) != 0) {
            return;
        }
        func_0206879c(0x83, func_02061c20((int *)&WM_WORK->status));
        WM_WORK->childBitmap = WM_WORK->status.child_bitmap;
        return;

    case 0x15:
        if (func_0206a230() == 0) {
            return;
        }
        DISPATCH(0x19, (void *)0);
        return;

    case 0x80:
        switch (*(u16 *)(arg0 + 4) - 0x10) {
        case 0:
            DISPATCH(0x1D, arg0);
            return;
        case 1:
            DISPATCH(0x1F, arg0);
            return;
        case 2:
            DISPATCH(0x20, arg0);
            return;
        case 3:
            DISPATCH(0x21, arg0);
            return;
        }
        break;

    default:
        DISPATCH(0x100, arg0);
        return;
    }
}
