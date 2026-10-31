#include "types.h"
#include "private/arm9_a1fc0_file_share.h"

/* data_020a1fc0 under FileShareWork's names (arm9_a1fc0_file_share.h). Kept
 * as a local object type: the packet size reads through
 * ((FileShareWork *)&data_020a1fc0) take one more register. */
typedef struct {
    int mIsParent;         /* 0x00 */
    int pad04[9];          /* 0x04..0x27 */
    int mParentPacketSize; /* 0x28 */
    int mChildPacketSize;  /* 0x2c */
    char pad30[0x410];     /* 0x30..0x43f */
    char mArea[0x2730];    /* 0x440 -- FileShareParentArea */
} Globals;

extern int func_020659a0(int a, int b);
extern int func_020656d4(u16 arg0, const void *arg1, int arg2, u32 arg3);
extern void func_02042160();
extern Globals data_020a1fc0;

void func_02041e14(void)
{
    FileShareParentArea *s = (FileShareParentArea *)((FileShareWork *)&data_020a1fc0)->mArea;
    FileShareMsg cmd;
    FileShareMsg cmd2;

    if (data_020a1fc0.mIsParent == 0) {
        return;
    }
    if (s->mReplySending != 0) {
        return;
    }

    s->mReplyPending &= s->mConnectedBitmap;
    s->mReplyGroup &= s->mConnectedBitmap;
    s->mOpenChildren &= s->mConnectedBitmap;
    s->mResizeChildren &= s->mConnectedBitmap;

    if (s->mResizePending != 0 && s->mBusyCount == 0) {
        int v = s->mNewPacketSize;
        int childSize = data_020a1fc0.mChildPacketSize;
        int snd;

        s->mResizePending = 0;
        data_020a1fc0.mParentPacketSize = v;
        func_020659a0(v, childSize);

        snd = s->mResizeChildren;
        if (snd == 0) {
            return;
        }
        cmd.mKind = 1;
        cmd.mFlag = 0;
        cmd.mFileId = 0;
        cmd.mPacketSizeHigh = (u8)(data_020a1fc0.mParentPacketSize >> 8);
        cmd.mPacketSizeLow = (u8)data_020a1fc0.mParentPacketSize;
        func_020656d4((u16)snd, &cmd, 9, (u32)func_02042160);
        s->mReplySending = 1;
        s->mResizeChildren = 0;
    } else {
        int mask;
        FileShareMsg *found;
        int cond;
        int i;
        int pri;
        int bit;
        FileShareMsg *p;
        u8 k;
        int c;
        int w4;

        mask = s->mReplyPending;
        if (mask == 0) {
            return;
        }
        pri = s->mReplyGroup;
        found = 0;
        cond = (pri != 0 && pri == (pri & mask));
        if (cond) {
            mask = pri;
        } else {
            mask &= ~pri;
        }

        p = (FileShareMsg *)s->mReplies;
        i = 0;
        for (;;) {
            bit = 1 << i;
            if (bit > mask) {
                break;
            }
            if (bit & mask) {
                if (found == 0) {
                    found = p;
                } else if (found->mKind != p->mKind || found->mFileId != p->mFileId) {
                    mask &= ~bit;
                }
            }
            p++;
            i++;
        }

        if (cond && mask != pri) {
            s->mReplyGroup = 0;
        }
        if (found == 0) {
            return;
        }

        switch (found->mKind) {
        case 0:
            found->mKind = 1;
            break;
        case 2:
            found->mKind = 3;
            s->mOpenChildren &= ~mask;
            break;
        }

        k = found->mKind;
        w4 = found->mFileId;
        c = data_020a1fc0.mParentPacketSize;
        cmd2.mKind = k;
        cmd2.mFlag = 1;
        cmd2.mFileId = w4;
        cmd2.mPacketSizeHigh = (u8)(c >> 8);
        cmd2.mPacketSizeLow = (u8)c;
        func_020656d4((u16)mask, &cmd2, 9, (u32)func_02042160);
        s->mReplySending = 1;
        s->mReplyPending &= ~mask;
    }
}
