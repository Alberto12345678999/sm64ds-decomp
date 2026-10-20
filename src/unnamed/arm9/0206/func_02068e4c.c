#include "types.h"
extern int _ZN3IRQ7DisableEv(void);
extern void _ZN3IRQ7RestoreEj(int state);
extern void MultiStore_Int(int val, int *dst, int len);
extern void MultiStore16(int val, char *dst, int nbytes);
extern void CpuCopy8(u16 *a, char *b, int c);
extern int func_02069038(void);
extern char *data_020a9db8;
extern int data_020a9db4;
extern short data_020a9db0;
extern u16 *data_0209a084;
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

int func_02068e4c(int a0, u16 *a1, int a2, int a3, u16 a4, int a5)
{
  volatile unsigned short fill_s;
  volatile int fill_i;
  /* base1 (the WmWork) and base2 are byte pointers, not ints: every WmWork
     store below (parentMaxSize, sendBufSize, sendBuf, ...) is add-high /
     small-offset on the cartridge (add r0,r7,#0x1e00 / strh r3,[r0,#0x18]),
     which mwcc only emits for pointer arithmetic. With int bases each offset
     is materialized from the literal pool and stored through a register
     index, 15 words longer. */
  char *base1;
  char *base2;
  int irq;
  if ((data_020a9db8 != 0) && ((*((u16 *) (data_020a9db8 + 0x1316))) != 0))
  {
    return 2;
  }
  base1 = (char *) ((a0 + 0x1f) & (~0x1f));
  base2 = (char *) (((int) base1 + sizeof(WmWork) + 0x1f) & (~0x1f));
  irq = _ZN3IRQ7DisableEv();
  fill_i = 0;
  data_020a9db0 = (short) a5;
  data_020a9db4 = (int) base1;
  data_020a9db8 = base2;
  MultiStore_Int(fill_i, (int *) base1, sizeof(WmWork));
  fill_s = 0;
  MultiStore16(fill_s, base2, 0x1340);
  /* 0x1e30 and 0x1e38 sit in WmWork.pad_1e2e: nothing else in these files
     reads them back (and the two copies overlap), so they stay raw */
  {
    int i = 0;
    u16 *dst = (u16 *) (base1 + 0x1e30);
    u16 *rp = a1;
    u16 v;
    do
    {
      v = *((rp + i) + 1);
      if (v == 0)
      {
        break;
      }
      i++;
      *(dst++) = v;
    }
    while (i < 0xa);
  }
  {
    u16 *dst = (u16 *) (base1 + 0x1e38);
    int j = 0;
    do
    {
      u16 *ptr = data_0209a084;
      if ((*ptr) == 0)
      {
        break;
      }
      data_0209a084 = ptr + 1;
      j++;
      *(dst++) = *ptr;
    }
    while (j < 0x10);
  }
  CpuCopy8(a1, base2 + 0x1300, 0x16);
  ((WmWork *) base1)->parentMaxSize = 0x100;
  ((WmWork *) base1)->childMaxSize = 8;
  ((WmWork *) base1)->sendBufSize = 0;
  ((WmWork *) base1)->recvBufSize = 0;
  ((WmWork *) base1)->mpContinuous = 1;
  ((WmWork *) base1)->sendBuf = base2;
  ((WmWork *) base1)->recvBuf = base2 + 0x400;
  {
    WmParentParam *hdr = &((WmWork *) base1)->parentParam;
    hdr->CS_Flag = 1;
    hdr->KS_Flag = 0;
    hdr->ggid[0] = (short) a2;
    hdr->ggid[1] = (short) a3;
    hdr->tgid = (short) a4;
    hdr->entryFlag = 1;
    hdr->multiBootFlag = 0;
    hdr->beaconPeriod = (u16) (func_02069038() + 0xc8);
    hdr->maxEntry = 0xf;
  }
  ((WmWork *) base1)->mpSending = 0;
  ((WmWork *) base1)->initialized = 0;
  *((int *) (base2 + 0x1324)) = 0;
  _ZN3IRQ7RestoreEj(irq);
  *((u16 *) (base2 + 0x1316)) = 1;
  return 0;
}
