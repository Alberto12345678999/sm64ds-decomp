#include "types.h"
/* Parent area at +0x440: a pool of three 0xcc0-byte nodes, each holding one
 * registered region. A node moves free -> busy (state 1, loading; func_02041b60)
 * -> ready (state 2; func_02041b24) -> busy (state 3, releasing; func_02041ae8)
 * -> free (state 0; func_02041a94). */
enum { FILE_SHARE_NODE_SIZE = 0xcc0 }; /* node slot stride; FileShareNode is its head */

typedef struct FileShareNode {
    struct FileShareNode *mNext; /* 0x00 -- list link (func_02041bbc moves nodes) */
    /* 0x04 -- func_020658c0 registers it (offset, size, 0x20-byte name,
     * data); func_02041c2c finds a node by its offset */
    u8 mRegion[0x34];
    /* 0x38 -- FS_InitFile here; func_02042254 opens, reads and closes the
     * region's file through it */
    u8 mFile[0x44];
    int mState; /* 0x7c -- 0 free, 1 loading, 2 ready, 3 releasing */
    /* 0x80 -- func_020412f0: +1 per child reading the region, -1 when it is
     * done; at 0 the node is released */
    int mRefCount;
    /* 0x84 -- func_020412f0: children asking for a region that is still
     * loading, by AID bit */
    int mWaitingChildren;
    /* 0x88 -- func_02042254 opens the file by it; func_020412f0 hands it to
     * the requesting child. Seeded per node below */
    int mFileId;
} FileShareNode;

typedef struct FileShareParentArea {
    /* 0x0000 -- one reply per AID: func_020412f0 fills it, func_02041d28 sets
     * its file id, func_02041e14 sends it */
    u8 mReplies[0x10][0xc];
    u8 mNodes[3][FILE_SHARE_NODE_SIZE]; /* 0x00c0 */
    FileShareNode *mFreeList;           /* 0x2700 */
    FileShareNode *mReadyList;          /* 0x2704 -- func_02041c2c searches it */
    FileShareNode *mBusyList;           /* 0x2708 -- func_02042254 loads its state-1 nodes */
    /* 0x270c -- children owed a reply, by AID bit (func_020412f0,
     * func_02041d28 set; func_02041e14 sends and clears) */
    int mReplyPending;
    u8 pad_2710[0x4];
    /* 0x2714 -- func_02041e14 sets it after a send and waits; the send
     * callback func_02042160 clears it */
    int mReplySending;
    /* 0x2718 -- by AID; bit 0 is the parent itself. func_020417d0 sets a
     * child's bit on connect and clears it on disconnect */
    int mConnectedBitmap;
    u8 pad_271c[0x4];
    /* 0x2720 -- func_020412f0: a request named another packet size;
     * func_02041e14 applies mNewPacketSize once mBusyCount is 0 */
    int mResizePending;
    /* 0x2724 -- nodes off the free list (func_02041b60 +1, func_02041a94 -1) */
    int mBusyCount;
    /* 0x2728 -- children to tell the new size, by AID bit (func_020412f0
     * sets, func_02041e14 sends) */
    int mResizeChildren;
    int mNewPacketSize; /* 0x272c -- func_02041e14 copies it to mParentPacketSize */
} FileShareParentArea;

/* Child area at +0x440. */
typedef struct FileShareChildArea {
    int ptrs[0x10];
    int zeros1[0x10];
    int zeros2[0x10];
    u8 pad_0c0[0xbb0];
    /* 0xc70 -- func_02041224 allocates it (about four bytes per packet of
     * mMaxReadSize); func_02040aa4 frees it */
    int mRecvWork;
    int mMaxReadSize; /* 0xc74 -- func_02041224 grows it to the largest read */
    /* 0xc78 -- func_02040f30: offset of the region being read, as the parent
     * registered it (the tables are 0x20000) */
    int mReadRegion;
} FileShareChildArea;

/* File-local view of the wireless file-sharing work block at data_020a1fc0
 * (0x0204 cluster, func_02040aa4 .. func_02042668). */
typedef struct FileShareWork {
    int mIsParent;         /* 0x00 -- a0; the parent builds the node pool at +0x440,
                              the child the receive tables; func_02041930 picks the
                              parent or child send from it */
    int mSendRequest;      /* 0x04 -- set by func_02040bb0/func_020418f0 before
                              func_02041930, which sends only while it is set */
    int mSendBusy;         /* 0x08 -- func_02041930: the port send returned 2 */
    int mState;            /* 0x0c -- 1 here, 2 once ready (func_02040bb0,
                              func_02040f30), 0 at shutdown (func_02040aa4) */
    int mStateCallback;    /* 0x10 -- a2; called with 0 when mState becomes 2 */
    int mAllocFunc;        /* 0x14 -- a3; (arg, size, 0) allocates, (arg, 0, ptr)
                              frees (func_02041224, func_02040aa4) */
    int mAllocArg;         /* 0x18 -- a4; first argument to mAllocFunc */
    int mReadRequest;      /* 0x1c -- child read in flight: func_02041a00 sets it,
                              func_02040f30 completes and clears it */
    int mTable;            /* 0x20 -- func_020424c0: the card header's FNT, FAT and
                              overlay tables, read into one allocation */
    int mTableSize;        /* 0x24 -- that allocation's size */
    int mParentPacketSize; /* 0x28 -- parent MP send size; func_02040f30 sets it
                              from the MP callback's parent size + 0xe */
    int mChildPacketSize;  /* 0x2c -- child MP send size, likewise */
    u16 mPort;             /* 0x30 -- a1; func_02061c88 registers the port
                              callback on it, func_02041930 sends on it */
    u8 pad_032[0x40e];
    u8 mArea[sizeof(FileShareParentArea)]; /* 0x440 -- FileShareParentArea or
                                              FileShareChildArea, by mIsParent */
} FileShareWork;

extern int _ZN3IRQ7DisableEv(void);
extern void _ZN3IRQ7RestoreEj(int);
extern void _ZN4CP1527FlushAndInvalidateDataCacheEjj(int, int);
extern void _ZN4CP1516DrainWriteBufferEv(void);
extern int func_02061c88(int a, int b, int c);
extern void Crash(void);
extern void func_0205d89c(int x);
extern void FS_InitFile(int *s);
extern void func_020652fc(int a, int b, int c);
extern void func_020424c0(void);
extern void func_0205a588(void *p, int v, int n);
extern int func_020658c0(void *node, int a1, void *a2, int a3, int arg5, int arg6);
extern void func_02042200(void);
extern void func_02041224(char *thiz, int n);
extern void func_02065234(int arg);

extern void func_020417d0(void);
extern void func_020412f0(void);
extern void func_02040f30(void);

extern int data_020a0f84;
extern int data_020a0f88;
extern char data_020a1fc0[];
extern char data_02082158[];

#pragma opt_strength_reduction off
void func_02040c34(int a0, int a1, int a2, int a3, int a4)
{
    FileShareWork *G = (FileShareWork *)data_020a1fc0;
    int state = _ZN3IRQ7DisableEv();
    if (data_020a0f84 != 0) {
        _ZN3IRQ7RestoreEj(state);
    } else {
        data_020a0f84 = 1;
        _ZN3IRQ7RestoreEj(state);

        G->mIsParent = a0;
        G->mPort = (u16)a1;
        G->mSendRequest = 0;
        G->mSendBusy = 0;
        G->mState = 1;
        G->mStateCallback = a2;
        G->mAllocFunc = a3;
        G->mAllocArg = a4;
        G->mReadRequest = 0;
        G->mTableSize = 0;
        G->mTable = 0;
        G->mParentPacketSize = 0;
        G->mChildPacketSize = 0xe;
        data_020a0f88 = 0;
        if (func_02061c88((u16)a1, (int)func_020417d0, 0) != 0)
            Crash();
        func_0205d89c(-1);

        if (G->mIsParent != 0) {
            {
                char *base = (char *)G->mArea;
                char *node;
                char *next;
                char *saved;
                char *zero;
                char *end;
                _ZN4CP1527FlushAndInvalidateDataCacheEjj((int)base, sizeof(FileShareParentArea));
                _ZN4CP1516DrainWriteBufferEv();
                saved = (char *)((FileShareParentArea *)base)->mNodes;
                zero = 0;
                node = saved;
                next = node + FILE_SHARE_NODE_SIZE;
                end = ((int)next & 1) ? (char *)((FileShareParentArea *)base)->mNodes[3]
                                      : (char *)((FileShareParentArea *)base)->mNodes[3];
                ((FileShareParentArea *)base)->mFreeList = (FileShareNode *)saved;
                if (next < end) {
                    do {
                        ((FileShareNode *)node)->mNext =
                            (FileShareNode *)(node + FILE_SHARE_NODE_SIZE);
                        FS_InitFile((int *)((FileShareNode *)node)->mFile);
                        ((FileShareNode *)node)->mRefCount = (int)zero;
                        ((FileShareNode *)node)->mState = (int)zero;
                        ((FileShareNode *)node)->mFileId =
                            (((int)node + 0xcc00cc0) - (int)saved) / 0xcc0;
                        node += FILE_SHARE_NODE_SIZE;
                    } while (node + FILE_SHARE_NODE_SIZE < end);
                }
                ((FileShareNode *)node)->mNext = 0;
                *(int*)(base + 0x2710) = 0;
                ((FileShareParentArea *)base)->mReplyPending = 0;
                ((FileShareParentArea *)base)->mReplySending = 0;
                ((FileShareParentArea *)base)->mReadyList = 0;
                ((FileShareParentArea *)base)->mBusyList = 0;
                G->mParentPacketSize = 0x200;
                ((FileShareParentArea *)base)->mConnectedBitmap = 1;
                *(int*)(base + 0x271c) = 0;
                ((FileShareParentArea *)base)->mResizePending = 0;
                ((FileShareParentArea *)base)->mResizeChildren = 0;
                ((FileShareParentArea *)base)->mBusyCount = 0;
                ((FileShareParentArea *)base)->mNewPacketSize = G->mParentPacketSize;
                _ZN4CP1527FlushAndInvalidateDataCacheEjj((int)base, sizeof(FileShareParentArea));
                _ZN4CP1516DrainWriteBufferEv();
                func_020652fc(G->mParentPacketSize, G->mChildPacketSize, (int)func_020412f0);
                func_020424c0();
            }
            {
                char *base = (char *)G->mArea;
                FileShareNode *nd;
                nd = ((FileShareParentArea *)base)->mFreeList;
                ((FileShareParentArea *)base)->mFreeList = nd->mNext;
                func_0205a588(nd, 0, FILE_SHARE_NODE_SIZE);
                /* mTableSize is read through data_020a1fc0, not G, here and in the
                   child branch: the G-> spelling comes out 8 bytes short */
                func_020658c0(nd->mRegion, 0x20000, data_02082158, G->mTable,
                              ((FileShareWork *)data_020a1fc0)->mTableSize, 0);
                nd->mNext = ((FileShareParentArea *)base)->mReadyList;
                ((FileShareParentArea *)base)->mReadyList = nd;
                nd->mRefCount = 1;
                func_02042200();
            }
        } else {
            char *base = (char *)G->mArea;
            FileShareChildArea *arr = (FileShareChildArea *)base;
            int i;
            char *p;
            _ZN4CP1527FlushAndInvalidateDataCacheEjj((int)base, sizeof(FileShareChildArea));
            _ZN4CP1516DrainWriteBufferEv();
            p = base + 0xc0;
            for (i = 0; i < 0x10; i++) {
                arr->ptrs[i] = (int)p;
                arr->zeros1[i] = 0;
                arr->zeros2[i] = 0;
                p += 0x28;
            }
            arr->mRecvWork = 0;
            arr->mReadRegion = 0;
            G->mParentPacketSize = 0x80;
            arr->mMaxReadSize = 0x100000;
            func_02041224(base, -1);
            G->mParentPacketSize = 0;
            func_020424c0();
            func_02041224(base, ((FileShareWork *)data_020a1fc0)->mTableSize);
            _ZN4CP1527FlushAndInvalidateDataCacheEjj((int)base, sizeof(FileShareChildArea));
            _ZN4CP1516DrainWriteBufferEv();
            func_02065234((int)func_02040f30);
        }
    }
    _ZN3IRQ7RestoreEj(state);
}
