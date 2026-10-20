extern void func_02068834(int v);
extern int func_02062240(int a, int b, int c);
extern int func_02061ce4(int x);
extern char *data_020a9db4;
extern unsigned short data_020a9db0;

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

int func_02068d08(void)
{
    WmWork *base;
    int ret;
    base = WM_WORK;
    base->mpStarted = 0;
    WM_WORK->childBitmap = 0;
    WM_WORK->resetting = 0;
    *(short *)(data_020a9db4 + 0x1e48) = 0; /* in WmWork.pad_1e2e: no reader here */
    func_02068834(0xa);
    do {
        ret = func_02062240((int)WM_WORK->wmSysBuf,
                            (int)WM_WORK->stateCallback,
                            data_020a9db0);
    } while (ret == 4);
    if (ret != 2) return 8;
    func_02061ce4((int)WM_WORK->stateCallback);
    WM_WORK->initialized = 1;
    return 0;
}
