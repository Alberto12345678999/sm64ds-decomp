#include "types.h"
#include "private/arm9_a1fc0_file_share.h"
extern u32 data_020a1fc0[];
extern void func_02041930(void);
extern void func_020650d8(int data, int length, int aid);
extern void func_02065050(int data, int length);

/* The file-sharing port receive callback. Once the work block is up
 * (mState): CONNECTED (7) lets the parent resend (func_02041930) unless a
 * send is in flight; DISCONNECTED (9) drops the child from the parent's
 * mConnectedBitmap; PORT_RECV (0x15) marks the sender connected and hands
 * its packet to the parent's handler (func_020650d8), or on a child to
 * func_02065050. */

/* NitroSDK WMPortRecvCallback, the fields read here: the offsets agree with
 * func_02062aa4.cpp's and func_02062bdc.cpp's view. */
typedef struct WMPortRecvCallback {
    u16 apiid;     /* 0x00 */
    u16 errcode;   /* 0x02 */
    u16 state;     /* 0x04 -- 7 CONNECTED, 9 DISCONNECTED, 0x15 PORT_RECV */
    u16 port;      /* 0x06 */
    void *recvBuf; /* 0x08 */
    u16 *data;     /* 0x0c */
    u16 length;    /* 0x10 -- bytes at data */
    u16 aid;       /* 0x12 -- the sender */
} WMPortRecvCallback;

void func_020417d0(char *p)
{
    WMPortRecvCallback *cb = (WMPortRecvCallback *)p;
    FileShareWork *g = FILE_SHARE_WORK;
    FileShareParentArea *base = (FileShareParentArea *)g->mArea;

    if (g->mState == 0)
        return;

    switch (cb->state) {
    case 7:
        if (g->mIsParent == 0)
            return;
        if (g->mSendBusy != 0)
            return;
        func_02041930();
        return;
    case 9:
        if (g->mIsParent == 0)
            return;
        base->mConnectedBitmap &= ~(1 << cb->aid);
        return;
    case 0x15: {
        s32 data = (s32)cb->data;
        u32 length = cb->length;
        if (g->mIsParent != 0) {
            u32 aid = cb->aid;
            base->mConnectedBitmap |= (1 << aid);
            func_020650d8(data, length, aid);
        } else {
            func_02065050(data, length);
        }
        return;
    }
    }
}
