#include "types.h"

/* NitroSDK WBT (wireless block transfer): start the command the application
 * queued. When no command is running (cmd.command == 0) and one is queued,
 * the queued 0x9c-byte WBTCommand is copied over the running one, given the
 * next command counter, and its first request is sent; the queue slot is then
 * cleared. Commands: 2 REQ_SYNC, 4 REQ_GET_BLOCK, 6 REQ_GET_BLOCKINFO,
 * 10 REQ_USER_DATA. A block (or block-info) request first resets each target
 * peer's receive bitmap: GET_BLOCK into the caller's buffer and bitmap
 * tables, GET_BLOCKINFO into the peer record's own bitmap words.
 *
 * Field names follow func_02064554's WBTCommand / WBTPeerRecord views; the
 * get union is the layout WBT_GetBlock (func_02065730) builds. */
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
            u32 block_id;           /* 0x14 */
            u32 recv_data_size;     /* 0x18 */
            u8 *recv_buf_table[16]; /* 0x1c -- per aid */
            u32 *pkt_bmp_table[16]; /* 0x5c -- per aid */
        } get;
        struct {
            u8 data[9]; /* 0x14 */
            u8 size;    /* 0x1d */
        } user_data;
    } u;
} WBTCommand;

/* func_020647fc fills it: length, packet count, three cursors, then the
 * bitmap words and the receive buffer. */
typedef struct WBTPacketBitmap {
    s32 length; /* 0x00 */
    s32 count;  /* 0x04 */
    s32 pad_08[3];
    u32 *bitmap; /* 0x14 */
    u8 *buffer;  /* 0x18 */
} WBTPacketBitmap;

/* A peer's receive state for the running transfer. */
typedef struct WBTPeerRecv {
    WBTPacketBitmap pkt_bmp; /* 0x00 */
    u32 blockinfo_bits[10];  /* 0x1c -- GET_BLOCKINFO's bitmap words */
} WBTPeerRecv;

typedef struct WBTPeerRecord {
    u8 pad_00[0x24];
    WBTPeerRecv recv; /* 0x24 */
} WBTPeerRecord;

typedef struct WBTWork {
    WBTCommand cmd;        /* 0x000 -- the command running */
    WBTCommand queued_cmd; /* 0x09c -- the next one; command 0 = none */
    u8 pad_138[0x9c];
    WBTPeerRecord peer[16]; /* 0x1d4 -- indexed by aid */
} WBTWork;

#ifndef SM64DS_PLATFORM_PC
/* ROM layout under mwccarm: WBT_GetBlock's command is 0x9c bytes, a peer
 * record steps 0x68, and peer[] starts at 0x1d4. */
typedef char WBTCommand_size_must_be_0x9c[sizeof(WBTCommand) == 0x9c ? 1 : -1];
typedef char WBTPeerRecord_size_must_be_0x68[sizeof(WBTPeerRecord) == 0x68 ? 1 : -1];
typedef char WBTWork_peer_must_be_at_0x1d4[(int)&((WBTWork *)0)->peer == 0x1d4 ? 1 : -1];
#endif

extern void MultiCopy_Int(void *dst, void *src, int n);
extern void func_02065bf4(void);
extern int func_02065c1c(void);
extern int func_02065bc0(void);
extern int func_02065bd0(void);
extern int func_02064f54(char *q, int a, int b, int c, int d);
extern void func_020647fc(char *a, int b, void *c, int d);
extern int func_02064e18(char *q, int a, int b, int c, int d);
extern int func_02064cd8(char *q, int a, int b, int c, int d);
extern int func_02064a94(char *q, int a, int b, char *c, int d);

int func_02063718(char *p, char *q)
{
    WBTWork *work = (WBTWork *)p;
    int t;
    int ret = 0;
    WBTCommand *st = (WBTCommand *)((long long)(unsigned int)&work->queued_cmd);
    int b;
    int i;
    char *ptr;
    if (work->cmd.command != 0) return ret;
    if (st->command == 0) return ret;
    func_02065bf4();
    t = func_02065c1c();
    switch (st->command) {
    case 2:
        MultiCopy_Int(st, &work->cmd, sizeof(WBTCommand));
        work->cmd.my_cmd_counter = t;
        ret = func_02065bc0();
        b = func_02065bd0();
        ret = func_02064f54(q, work->cmd.target_bmp, work->cmd.my_cmd_counter, ret, b);
        break;
    case 6:
        MultiCopy_Int(st, &work->cmd, sizeof(WBTCommand));
        work->cmd.my_cmd_counter = t;
        ptr = (char *)&work->peer[0].recv;
        for (i = 0; i < 0x10; i++, ptr += sizeof(WBTPeerRecord)) {
            if ((work->cmd.target_bmp >> i) & 1)
                func_020647fc(ptr, work->cmd.u.get.recv_data_size,
                              ((WBTPeerRecv *)ptr)->blockinfo_bits,
                              (int)work->cmd.u.get.recv_buf_table[i]);
        }
        if (((WBTCommand *)((long long)(unsigned int)&work->queued_cmd))->command == 4)
            ret = func_02064e18(q, work->cmd.target_bmp, work->cmd.my_cmd_counter, work->cmd.u.get.block_id, 0);
        else
            ret = func_02064cd8(q, work->cmd.target_bmp, work->cmd.my_cmd_counter, work->cmd.u.get.block_id, 0);
        break;
    case 4:
        MultiCopy_Int(st, &work->cmd, sizeof(WBTCommand));
        work->cmd.my_cmd_counter = t;
        ptr = (char *)&work->peer[0].recv;
        for (i = 0; i < 0x10; i++, ptr += sizeof(WBTPeerRecord)) {
            if ((work->cmd.target_bmp >> i) & 1)
                func_020647fc(ptr, work->cmd.u.get.recv_data_size, work->cmd.u.get.pkt_bmp_table[i],
                              (int)work->cmd.u.get.recv_buf_table[i]);
        }
        if (((WBTCommand *)((long long)(unsigned int)&work->queued_cmd))->command == 4)
            ret = func_02064e18(q, work->cmd.target_bmp, work->cmd.my_cmd_counter, work->cmd.u.get.block_id, 0);
        else
            ret = func_02064cd8(q, work->cmd.target_bmp, work->cmd.my_cmd_counter, work->cmd.u.get.block_id, 0);
        break;
    case 0xa:
        MultiCopy_Int(st, &work->cmd, sizeof(WBTCommand));
        work->cmd.my_cmd_counter = t;
        ret = func_02064a94(q, work->cmd.target_bmp, work->cmd.my_cmd_counter, (char *)work->cmd.u.user_data.data,
                            work->cmd.u.user_data.size);
        break;
    }
    ((WBTCommand *)((long long)(unsigned int)&work->queued_cmd))->command = 0;
    return ret;
}
