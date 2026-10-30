/* PM_Init (the Nitro SDK's pm.c): the power-management PXI channel. */
#define PXI_FIFO_TAG_PM 8
#define PXI_PROC_ARM7 1

/* The four command slots at 0x020a8138, 8 bytes each: a reply-arrived flag and
   the caller's destination for the reply.

   The word at +4 used to carry its own symbol row, data_020a813c, because the
   only two accesses to it both reach it at that address: func_0205fb58 stores
   the caller's pointer there before sending, and func_0205fcfc dereferences it
   to deposit a 0x70..0x73 reply. One array, seen twice. Spelling it as this
   struct's second field makes mwcc fold the +4 into the pool literal and name
   data_020a8138 with a RELA addend of 4, which resolves to the same
   0x020a813c the config records.

   `reply` is a short *: func_0205fcfc stores a halfword through it. `flag` is
   set by that same callback when the reply lands, cleared by func_0205fb58
   before sending and by PM_Init for all four slots. Both names are coined. */
typedef struct {
    unsigned short flag;
    unsigned short pad;
    short *reply;
} PmEntry;

extern unsigned short data_020a8104; /* the init flag */
/* The PM channel's command record at 0x020a8114. Its extent is 0x10: the next
   labelled address is data_020a8124.

   `busy` is the channel's in-flight flag, and it is the one field the ROM
   explains outright: func_0205ff20 reads it under IRQ::Disable, returns 0 if
   it is set, otherwise stores 1 and returns 1 -- a test-and-set every command
   sender calls to claim the channel -- and func_0205ff08 spins until it clears
   again. PM_Init zeroes it along with w1.

   The three senders (func_0205f5fc, func_0205fb58, func_0205fbd0) stash their
   last two arguments in w1 and w2 before handing the command to func_0205f8b0;
   nothing recovered reads either word back, so they keep offset names. The
   tag-8 receive callback func_0205fcfc stores a cmd-0x67 reply through the
   pointer at +0xc, which is what replyDst is named for. Both coined names
   describe the observed use, not a recovered spelling. */
struct D020a8114 {
    int busy;
    int w1;
    int w2;
    int *replyDst;
};
extern struct D020a8114 data_020a8114;
extern PmEntry data_020a8138[4];
extern char data_020a8124;
extern int data_020a8110;
extern void func_0205fcfc(int tag, unsigned int data, int err); /* the tag-8 receive callback */
extern void PXI_Init(void);
/* PXI_IsCallbackReady and PXI_SetFifoRecvCallback (src/engine/pxi/PXI_Fifo.cpp). */
extern int PXI_IsCallbackReady(int tag, int proc);
extern void PXI_SetFifoRecvCallback(int tag, void *callback);
extern void func_02058b9c(char *p);

void PM_Init(void) {
    int i;
    if (data_020a8104 != 0)
        return;
    data_020a8104 = 1;
    data_020a8114.busy = 0;
    data_020a8114.w1 = 0;
    PXI_Init();
    while (PXI_IsCallbackReady(PXI_FIFO_TAG_PM, PXI_PROC_ARM7) == 0)
        ;
    PXI_SetFifoRecvCallback(PXI_FIFO_TAG_PM, (void *)func_0205fcfc);
    for (i = 0; i < 4; i++)
        data_020a8138[i].flag = 0;
    func_02058b9c(&data_020a8124);
    data_020a8110 = *(int *)0x27ffc3c;
}
