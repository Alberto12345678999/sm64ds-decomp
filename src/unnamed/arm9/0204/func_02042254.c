#pragma opt_strength_reduction off

#include "private/arm9_a1fc0_file_share.h"

extern char data_02099e6c[];
extern int data_020a1fc0;
extern char data_020a2400[];

extern void *func_0205d23c(void *a, int b);
extern unsigned int _ZN3IRQ7DisableEv(void);
extern void _ZN3IRQ7RestoreEj(unsigned int saved);
extern void OS_SleepThread(unsigned short *self);
extern int func_0205d5e8(char *self, int a1, int a2, int a3, int a4);
extern int FS_ReadFile(char *a, char *b, int c);
extern void func_02041d28(char *base, void *node, int d);
extern int FS_CloseFile(char *self);
extern void func_02041a94(char *base, void *node);

/* The parent's loader thread: while the share is up (mState), take each node
 * off the busy list; a loading one (state 1) has its region's file opened
 * from the ROM archive (func_0205d5e8 = FS_OpenFileDirect over [0x8c,
 * 0x8c + 0x90), by mFileId), its first three 0x400-byte pages read into the
 * cache, and is handed to func_02041d28; a releasing one has its file closed
 * and goes back to the free list (func_02041a94). The arc local is the
 * archive func_0205d23c finds (by name, 3 characters). 0x8c / 0x90 (the
 * region's file offset and size; func_02041c64 matches a node by them) stay
 * raw: they fall in the header's pad_08c, and the header is not edited while
 * its consumers func_02040f30 / func_020412f0 are in an open PR. */
void func_02042254(void) {
    int i;
    FileShareNode *node;
    int arc = (int)func_0205d23c(data_02099e6c, 3);
    int b = 2;
    int c = 3;
    int d = 1;
    FileShareWork *work = (FileShareWork *)&data_020a1fc0;
    char *base = data_020a2400;

    while (1) {
        unsigned int irq = _ZN3IRQ7DisableEv();
        FileShareParentArea *area = (FileShareParentArea *)base;
        node = area->mBusyList;
        while (node == 0) {
            if (work->mState == 0) {
                _ZN3IRQ7RestoreEj(irq);
                return;
            }
            OS_SleepThread(0);
            node = area->mBusyList;
        }
        _ZN3IRQ7RestoreEj(irq);

        if (node->mState == 1) {
            char *sb = (char *)node; /* for 0x8c / 0x90, which have no header name */
            func_0205d5e8((char *)node->mFile, arc, *(int *)(sb + 0x8c),
                          *(int *)(sb + 0x8c) + *(int *)(sb + 0x90), node->mFileId);
            i = 0;
            {
                int val = 0;
                char *ptr = (char *)node->mPages;
                for (; i < 3; i++) {
                    node->mPageOffset[i] = val;
                    FS_ReadFile((char *)node->mFile, ptr, 0x400);
                    val += 0x400;
                    ptr += 0x400;
                }
            }
            node->mPrevSeqNo = 0;
            node->mLastRefillPage = b;
            node->mLoadingPage = c;
            irq = _ZN3IRQ7DisableEv();
            func_02041d28(base, node, d);
            _ZN3IRQ7RestoreEj(irq);
        } else {
            FS_CloseFile((char *)node->mFile);
            irq = _ZN3IRQ7DisableEv();
            func_02041a94(base, node);
            _ZN3IRQ7RestoreEj(irq);
        }
    }
}
