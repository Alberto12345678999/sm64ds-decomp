#include "types.h"
extern int WM_CheckStateEx(int a, int b);
extern void func_02062024(void *o);
extern void WM_SetCallbackTable(int i, int val);
extern void _ZN4CP1514FlushDataCacheEjj(u32 a, u32 b);
extern int WM_SendCommand(int a, int b, void *c);

/* File-local copy of include/WmWork.h's WmParentParam (NitroSDK
 * WMParentParam as this ROM's SDK revision lays it out), same names. */
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

/* NitroSDK WM_SetParentParameter(callback, pparaBuf): refuse user game info
 * without a buffer and MP sizes that, with the key-sharing overhead, pass
 * 0x200 bytes; then flush the parameter block (and the game info) and send
 * the command. */
int func_020620b0(int self, char *o)
{
    WmParentParam *param = (WmParentParam *)o;
    int r;
    u16 ksFlag;
    r = WM_CheckStateEx(1, 2);
    if (r != 0) return r;
    if (o == 0) return 6;
    if (param->userGameInfoLength != 0) {
        if (param->userGameInfo == 0) return 6;
    }
    ksFlag = param->KS_Flag;
    if (param->parentMaxSize + (ksFlag != 0 ? 0x2a : 0) > 0x200 ||
        param->childMaxSize + (ksFlag != 0 ? 6 : 0) > 0x200)
        return 6;
    func_02062024(o);
    WM_SetCallbackTable(7, self);
    _ZN4CP1514FlushDataCacheEjj((u32)o, sizeof(WmParentParam));
    if (param->userGameInfoLength != 0) {
        _ZN4CP1514FlushDataCacheEjj((u32)param->userGameInfo, param->userGameInfoLength);
    }
    r = WM_SendCommand(7, 1, o);
    if (r == 0) return 2;
    return r;
}
