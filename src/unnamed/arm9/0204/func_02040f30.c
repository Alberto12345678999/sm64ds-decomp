#include "types.h"
#include "private/arm9_a1fc0_file_share.h"
typedef struct {
    u32 kind : 4;
    u32 chan : 4;
    u32 flag : 24;
    u32 word4;
    u8 byte8;
} Cmd;

/* The NitroSDK WBTCommand this WBT callback receives; layout and names as in
 * func_02064554.c. command 2 is REQ_SYNC, 4 REQ_GET_BLOCK, 6
 * REQ_GET_BLOCKINFO, 0xc SYSTEM_CALLBACK (event 0xa, REQ_USER_DATA). */
typedef struct WBTCommand {
    s32 command;              /* 0x00 */
    s32 event;                /* 0x04 */
    u16 target_bmp;           /* 0x08 */
    u16 peer_bmp;             /* 0x0a */
    u8 my_cmd_counter;        /* 0x0c */
    u8 peer_cmd_counter;      /* 0x0d */
    s16 result;               /* 0x0e */
    void (*callback)(char *); /* 0x10 */
    union {
        struct {
            s16 num_of_list;      /* 0x14 */
            s16 peer_packet_size; /* 0x16 */
            s16 my_packet_size;   /* 0x18 */
        } sync;
        struct {
            u8 data[9]; /* 0x14 */
            u8 size;    /* 0x1d */
        } user_data;
    } u;
} WBTCommand;

/* The FSFile a child read is for (FileShareWork.mReadRequest, set by
 * func_02041a00). This ROM's FSFile has its prop union at 0x1c and its arg
 * union at 0x2c (see func_0205c264.c); names follow the SDK's FSFile. */
typedef struct FSFile {
    char pad_00[8];
    void *arc; /* 0x08 -- FS_NotifyArchiveAsyncEnd (func_0205cd5c) takes it */
    char pad_0c[0x1c];
    u32 pos; /* 0x28 -- prop.file.pos */
    u32 dst; /* 0x2c -- arg.readfile.dst */
    char pad_30[4];
    u32 len; /* 0x34 -- arg.readfile.len */
} FSFile;

extern int func_02065a4c(int x);
extern void func_02065788(u16 type, u32 arg1, const void *src, u32 arg3);
extern void func_02041a00(int x);
extern void func_02065730(u16 type, u32 arg1, const void *src1, u32 arg3, const void *src2,
                          u32 extra);
extern void _ZN4CP1527FlushAndInvalidateDataCacheEjj(u32 a, u32 b);
extern int func_020423dc(int *r6);
extern int func_020656d4(u16 arg0, const void *arg1, int arg2, u32 arg3);
extern void func_020657d0(u16 id, void *obj);
extern void func_0205cd5c(void *self, int arg);
extern void func_02042160(void);
extern void func_02040f30(void *arg0);
extern char data_020a1fc0[];
extern char data_020a2400[];
void func_02040f30(void *arg0) {
    WBTCommand *cmdp = (WBTCommand *)arg0;
    FileShareChildArea *child;
    int idx;
    int type;
    idx = func_02065a4c(cmdp->peer_bmp);
    type = cmdp->command;
    child = (FileShareChildArea *)data_020a2400;
    switch (type) {
    case 2:
        if (cmdp->target_bmp != 0) {
            return;
        }
        FILE_SHARE_WORK->mParentPacketSize = cmdp->u.sync.peer_packet_size + 0xe;
        FILE_SHARE_WORK->mChildPacketSize = cmdp->u.sync.my_packet_size + 0xe;
        if (FILE_SHARE_WORK->mState != 2) {
            func_02065788((u16)1, 0, (const void *)child->ptrs, (u32)func_02040f30);
            return;
        }
        {
            int request = FILE_SHARE_WORK->mReadRequest;
            if (request != 0) {
                func_02041a00(request);
            }
        }
        return;

    case 6:
        child->zeros1[idx] = FILE_SHARE_WORK->mTable;
        func_02065730((u16)1, 0x20000, (const void *)child->zeros1,
                      (u32)FILE_SHARE_WORK->mTableSize, (const void *)child->zeros2,
                      (u32)func_02040f30);
        return;

    case 4:
        if (cmdp->target_bmp != 0) {
            return;
        }
        if ((FILE_SHARE_WORK->mState != 2) != 0) {
            _ZN4CP1527FlushAndInvalidateDataCacheEjj((u32)FILE_SHARE_WORK->mTable,
                                                     (u32)FILE_SHARE_WORK->mTableSize);
            func_020423dc((int *)FILE_SHARE_WORK->mTable);
            {
                FILE_SHARE_WORK->mState = 2;
                {
                    int fn = FILE_SHARE_WORK->mStateCallback;
                    if (fn != 0) {
                        ((void (*)(int))fn)(0);
                    }
                }
            }
            return;
        }
        {
            u32 w4;
            int c;
            w4 = child->mReadRegion;
            Cmd cmd;
            cmd.kind = 2;
            cmd.flag = 1;
            c = FILE_SHARE_WORK->mParentPacketSize;
            cmd.word4 = w4;
            cmd.chan = (u8)(c >> 8);
            cmd.byte8 = (u8)c;
            func_020656d4((u16)1, &cmd, 9, (u32)func_02042160);
        }
        return;

    case 0xc: {
        Cmd *m;
        if (cmdp->event != 0xa) {
            return;
        }
        m = (Cmd *)cmdp->u.user_data.data;
        switch (m->kind) {
        case 1:
            if (m->flag == 0) {
                func_020657d0((u16)1, (void *)func_02040f30);
                return;
            }
            child->mReadRegion = m->word4;
            child->zeros1[idx] = ((FSFile *)FILE_SHARE_WORK->mReadRequest)->dst;
            func_02065730((u16)1, child->mReadRegion, (const void *)child->zeros1,
                          ((FSFile *)FILE_SHARE_WORK->mReadRequest)->len,
                          (const void *)child->zeros2, (u32)func_02040f30);
            return;

        case 3: {
            FSFile *p = (FSFile *)FILE_SHARE_WORK->mReadRequest;
            void *a0 = p->arc;
            FILE_SHARE_WORK->mReadRequest = 0;
            p->pos += p->len;
            func_0205cd5c(a0, 0);
            return;
        }
        }

        return;
    }
    }
}
