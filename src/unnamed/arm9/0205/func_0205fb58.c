#include "types.h"
extern int func_0205ff20(int a, int b, int c, int d);
extern void func_0205f8b0(int param);

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

/* The four command slots at 0x020a8138, 8 bytes each. The halfword at +0 is
   the reply-arrived flag: PM_Init clears all four, func_0205fb58 clears one
   before sending, and the tag-8 receive callback func_0205fcfc sets it when
   cmds 0x70..0x73 answer. The word at +4 carries its own label,
   data_020a813c, which func_0205fcfc dereferences as a short * to store the
   reply -- so the two symbols are one array seen twice. Unifying them is a
   separate reconstruction; this type stops at the layout all three consumers
   already agree on. */
typedef struct {
    unsigned short flag;
    unsigned short pad;
    int arg;
} PmEntry;
extern PmEntry data_020a8138[];

int func_0205fb58(int a, int b, int c, int d)
{
    int z;
    if (!func_0205ff20(a, b, c, d))
        return 1;
    z = 0;
    data_020a8138[a].flag = (u16)z;
    data_020a8114.w1 = c;
    data_020a8114.w2 = d;
    data_020a8138[a].arg = b;
    func_0205f8b0((a & 0xff) | 0x3006500);
    return z;
}
