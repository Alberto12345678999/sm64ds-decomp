//cpp
#include "types.h"
#include "CP15.h"

extern "C" {

extern int WM_GetSystemWork(void);
extern int WM_CheckStateEx(int count, int a, int b, int c, int d, int e);
extern void WM_SetCallbackTable(int i, int val);
extern int WM_SendCommand(int a, int b, int c);

/* NitroSDK wm_standard.c WM_Disconnect(callback, aid), by body against pret's
 * pokediamond WM_standard.s: in a connected state, a parent (7, 9) cuts child
 * aid (1..15 and connected, else 6 or 7) and a child (aid 0) its parent. It
 * sends API 0xd (DISCONNECT) with 1 << aid. */
int WM_Disconnect(int self, unsigned int idx) {
    int h;
    int* o;
    int r;
    h = WM_GetSystemWork();
    r = WM_CheckStateEx(5, 7, 9, 8, 0xa, 0xb);
    if (r != 0) return r;
    o = *(int**)(h + 4);
    {
        u16 v = *(u16*)o;
        if (v == 7 || v == 9) {
            if (idx < 1 || idx > 0xf)
                return 6;
            CP15::InvalidateDataCache((u32)o + 0x17e, 2);
            if ((*(u16*)((char*)*(int**)(h + 4) + 0x17e) & (1u << idx)) == 0) return 7;
        } else {
            if (idx != 0) return 6;
        }
    }
    WM_SetCallbackTable(0xd, self);
    r = WM_SendCommand(0xd, 1, 1u << idx);
    if (r == 0) return 2;
    return r;
}
}
