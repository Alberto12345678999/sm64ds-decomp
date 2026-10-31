#include "types.h"
#include "private/arm9_a1fc0_file_share.h"
extern char data_020a1fc0[];
extern void func_020418f0(void);
/* int, not its definition's u16: this call site zero-extends the result
   itself, and a u16 return drops that (0xcc bytes, not 0xd0) */
extern int func_02065138(int buf, int size);
/* int, not its definition's void: this call site takes r0 as a result,
   the same way it takes func_02065138's */
extern int func_020650a0(int buf, int size);
extern int WM_SetMPDataToPort(int a0, int a1, int a2, int a3, u16 a4, u16 a5);

/* Send the pending file-sharing packet on mPort: func_02065138 (parent) or
 * func_020650a0 (child), by mIsParent, builds it in the buffer at +0x40 with
 * that side's packet size as the limit, then WM_SetMPDataToPort sends it to AIDs
 * 0xffff with func_020418f0 as the callback. FileShareWork names come from
 * arm9_a1fc0_file_share.h; +0x40 is inside the header's pad_032 and stays
 * raw. */
void func_02041930(void)
{
    char *g = data_020a1fc0;
    FileShareWork *work = (FileShareWork *)g;
    int f0 = work->mIsParent;
    u16 a;
    u16 r;
    if (f0 != 0)
        a = (u16)work->mParentPacketSize;
    else
        a = (u16)work->mChildPacketSize;
    if (work->mSendRequest == 0)
        return;
    {
        char *sub = g + 0x40;
        if (f0 != 0)
            r = (u16)func_02065138((int)sub, a);
        else
            r = (u16)func_020650a0((int)sub, a);
        work->mSendBusy =
            (WM_SetMPDataToPort((int)func_020418f0, (int)sub, r, 0xffff, work->mPort, 3) == 2) ? 1
                                                                                               : 0;
    }
    /* re-read through the symbol: `work->mSendBusy` changes the .text bytes */
    work->mSendRequest = (FILE_SHARE_WORK->mSendBusy == 0) ? 1 : 0;
}
