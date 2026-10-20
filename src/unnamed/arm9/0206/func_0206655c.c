#include "types.h"

/* File-local mirror of include/private/arm9_a9db8_mb_parent.h (the multiboot
 * parent work data_020a9db8 points at): same names and offsets, with the parts
 * this function does not touch left as padding. */
typedef struct MbChildRequest {
    u32 mGameId;     /* 0x00 */
    u8  mUser[0x16]; /* 0x04 */
    u16 mVersion;    /* 0x1a */
    u8  mFileNo;     /* 0x1c */
    u8  pad_1d[0x3];
} MbChildRequest;

typedef struct MbParentFile {
    u8  mHeader[0x59c];    /* 0x000 */
    u8  mBlockTable[0x14]; /* 0x59c */
    u8 *mGameInfo;        /* 0x5b0 */
    s32 mSrcAddr;         /* 0x5b4 */
    u16 mCurrentBlock;    /* 0x5b8 */
    u16 mRequestedBlock;  /* 0x5ba */
    u16 mChildBitmap;     /* 0x5bc */
    u16 mEntryBitmap;     /* 0x5be */
    u16 mEntryChanged;    /* 0x5c0 */
    u8  mActive;          /* 0x5c2 */
    u8  pad_5c3[0x1];
} MbParentFile;

typedef struct MbParentWork {
    u8  pad_0000[0x1340];
    u8  mChildUser[15][0x16];          /* 0x1340 */
    u16 mChildVersion[15];             /* 0x148a */
    u32 mChildGameId[15];              /* 0x14a8 */
    u8  pad_14e4[0x4];
    s32 mChildState[15];               /* 0x14e8 */
    u8  mFileCount;                    /* 0x1524 */
    u8  mCurrentFile;                  /* 0x1525 */
    s8  mChildFile[15];                /* 0x1526 */
    u8  mChildCount;                   /* 0x1535 */
    u16 mChildEntryBitmap;             /* 0x1536 */
    MbChildRequest mChildRequest[15];  /* 0x1538 */
    u32 mChildRequestPieces[15];       /* 0x1718 */
    u16 mChildResponse[15];            /* 0x1754 */
    u8  pad_1772[0x1788 - 0x1772];
    MbParentFile mFiles[16];           /* 0x1788 */
} MbParentWork;

/* The game record a file was registered with (MbParentFile.mGameInfo). */
typedef struct MbGameInfo {
    u8  pad_00[0x14];
    u32 mGameId;     /* 0x14 -- matched against the child's mChildGameId */
    u8  mMaxPlayers; /* 0x18 -- entries (parent included) at or past it are refused */
} MbGameInfo;

extern MbParentWork *data_020a9db8;

extern void func_02065c2c(u8 *a, u8 *b);
extern int func_02065de4(void *a, u32 b);
extern void CpuCopy8(void *src, void *dst, int n);
extern int func_02066fec(u32 a, int b, int c);
extern u16 func_02065ef8(u16 a, u16 b);

void func_0206655c(void *arg0, u32 arg1)
{
    u8 buf[0x38];
    int phase;
    int idx;
    u8 cnt;
    u8 physIdx;
    MbParentWork *rec;
    MbGameInfo *p;
    u8 bidx;
    u16 flags;
    u32 bit;
    u8 pi;
    u8 *b;
    u16 *fld;
    int gv;
    u8 *cp;
    u32 i;

    func_02065c2c((u8 *)arg0 + 0xa, buf);
    if (arg1 == 0)
        return;
    if (arg1 > 0xf)
        return;

    idx = arg1 - 1;
    phase = data_020a9db8->mChildState[idx];

    switch (buf[0]) {
    case 7:
        if (phase == 2 && func_02065de4(buf, arg1) == 1) {
            i = arg1 - 1;
            CpuCopy8(&data_020a9db8->mChildRequest[i], buf + 0x14, 0x1d);
            data_020a9db8->mChildGameId[i] = *(int *)(buf + 0x14);
            data_020a9db8->mChildVersion[i] = *(u16 *)(buf + 0x2e);
            CpuCopy8(buf + 0x18, data_020a9db8->mChildUser[i], 0x16);
            {
                u8 *pp = data_020a9db8->mChildUser[i];
                *pp = (u8)((*pp & ~0xf0) | (((u8)arg1 & 0xf) << 4));
            }
            func_02066fec(arg1, 0xa, (int)(buf + 0x18));
        }
        if (phase != 0xa)
            return;
        cnt = 0;
        physIdx = data_020a9db8->mChildRequest[idx].mFileNo;
        /* have/disp gotos kept: an inline session predicate grows it (0x554); only an
           || chain assigning rec/p inside the condition matches */
        /* The file record is reached by stepping the work pointer a whole
           MbParentFile per index and naming mFiles[0] from there; indexing
           mFiles[physIdx] directly builds the address differently. The same
           holds for every stepped mFiles[0] access below. */
        if (physIdx < 0x10) {
            rec = (MbParentWork *)((u8 *)data_020a9db8 + physIdx * sizeof(MbParentFile));
            if (rec->mFiles[0].mActive != 0) {
                p = (MbGameInfo *)rec->mFiles[0].mGameInfo;
                gv = data_020a9db8->mChildGameId[idx];
                if (gv == p->mGameId)
                    goto have;
            }
        }
        data_020a9db8->mChildResponse[idx] = 4;
        goto disp;
    have:
        flags = rec->mFiles[0].mEntryBitmap;
        for (bidx = 0; (u32)bidx < 0x10; bidx++) {
            if ((1 << bidx) & flags)
                cnt++;
        }
        if ((u32)cnt >= (u32)p->mMaxPlayers) {
            data_020a9db8->mChildResponse[idx] = 0;
            func_02066fec(arg1, 0xb, 0);
            return;
        }
    disp:
        /* b + 0x54 is mChildResponse[idx]; the ROM builds it as 0x1700 + 0x54,
           and naming the member folds that split and moves bytes. */
        b = (u8 *)data_020a9db8 + idx * 2 + 0x1700;
        switch (*(u16 *)(b + 0x54)) {
        case 3:
            bit = 1u << arg1;
            if (data_020a9db8->mChildEntryBitmap & bit)
                return;
            cp = &data_020a9db8->mChildCount;
            (*cp)++;
            fld = &data_020a9db8->mChildEntryBitmap;
            *fld = (u16)(*fld | bit);
            data_020a9db8->mChildFile[arg1 - 1] = physIdx;
            fld = &((MbParentWork *)((u8 *)data_020a9db8 + physIdx * sizeof(MbParentFile)))->mFiles[0].mEntryBitmap;
            *fld = (u16)(*fld | bit);
            fld = &((MbParentWork *)((u8 *)data_020a9db8 + physIdx * sizeof(MbParentFile)))->mFiles[0].mEntryChanged;
            *fld = (u16)(*fld | bit);
            data_020a9db8->mChildResponse[arg1 - 1] = 0;
            func_02066fec(arg1, 5, 0);
            return;
        case 4:
            *(u16 *)(b + 0x54) = 0;
            func_02066fec(arg1, 4, 0);
            return;
        }
        return;

    case 8:
        if (phase == 5) {
            func_02066fec(arg1, 0xe, 0);
            return;
        }
        if (phase != 0xe)
            return;
        if (data_020a9db8->mChildResponse[idx] != 2)
            return;
        pi = data_020a9db8->mChildFile[idx];
        fld = &((MbParentWork *)((u8 *)data_020a9db8 + pi * sizeof(MbParentFile)))->mFiles[0].mChildBitmap;
        *fld = (u16)(*fld | (1u << arg1));
        ((MbParentWork *)((u8 *)data_020a9db8 + pi * sizeof(MbParentFile)))->mFiles[0].mCurrentBlock = 0;
        data_020a9db8->mChildResponse[idx] = 0;
        func_02066fec(arg1, 6, 0);
        return;

    case 9:
        if (phase != 6)
            return;
        pi = data_020a9db8->mChildFile[idx];
        if (pi == 0xff)
            return;
        data_020a9db8->mFiles[pi].mRequestedBlock =
            func_02065ef8(data_020a9db8->mFiles[pi].mRequestedBlock, *(u16 *)(buf + 2));
        return;

    case 10:
        if (phase == 6) {
            pi = data_020a9db8->mChildFile[idx];
            if (pi == 0xff)
                return;
            fld = &((MbParentWork *)((u8 *)data_020a9db8 + pi * sizeof(MbParentFile)))->mFiles[0].mChildBitmap;
            *fld = (u16)(*fld & ~(1u << arg1));
            func_02066fec(arg1, 7, 0);
            return;
        }
        if (phase != 7)
            return;
        b = (u8 *)data_020a9db8 + idx * 2 + 0x1700;
        if (*(u16 *)(b + 0x54) != 5)
            return;
        *(u16 *)(b + 0x54) = 0;
        func_02066fec(arg1, 8, 0);
        return;

    case 11:
        break;
    }
}
