//cpp
#include "types.h"
#include "CP15.h"

extern "C" {

/* NitroSDK wm_mp.c WM_StartMPEx(callback, recvBuf, recvBufSize, sendBuf,
 * sendBufSize, mpFreq, defaultRetryCount, minPollBmpMode, singlePacketMode,
 * fixFreqMode, ignoreFatalError): pret's pokediamond WM_mp.s has the same
 * eleven arguments, and its WMi_StartMP makes the same checks. In this older
 * SDK one function does both: in PARENT or CHILD (7, 8) with MP not started
 * (else 3), it checks recvBufSize against WM_GetMPReceiveBufferSize and
 * 64-byte alignment and sendBufSize against WM_GetMPSendBufferSize and
 * 32-byte alignment (6). Then it sends API 0xe (START_MP) with recvBufSize
 * in halfwords. */
extern int *WM_GetSystemWork(void);
extern int WM_CheckStateEx(int a, int b, int c);
extern int WM_GetMPReceiveBufferSize(void);
extern int WM_GetMPSendBufferSize(void);
extern void WM_SetCallbackTable(int i, int val);
extern int WM_SendCommand(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j,
                          int k, int l);

int WM_StartMPEx(int arg0, int arg1, int arg2, int arg3, u16 arg4, u16 arg5, u16 arg6, int arg7,
                 int arg8, int arg9, int arg10) {
    int *base;
    int r;

    base = WM_GetSystemWork();
    r = WM_CheckStateEx(2, 7, 8);
    if (r != 0)
        return r;
    CP15::InvalidateDataCache((unsigned int)(base[1] + 0x10), 4);
    if (((int *)base[1])[4] == 1)
        return 3;
    if (arg2 < WM_GetMPReceiveBufferSize())
        return 6;
    if (arg2 & 0x3f)
        return 6;
    if (arg4 < WM_GetMPSendBufferSize())
        return 6;
    if (arg4 & 0x1f)
        return 6;
    WM_SetCallbackTable(0xe, arg0);
    r = WM_SendCommand(0xe, 0xa, arg1, (unsigned int)arg2 >> 1, arg3, arg4, arg5, arg6, arg7, arg8,
                       arg9, arg10);
    if (r == 0)
        r = 2;
    return r;
}
}
