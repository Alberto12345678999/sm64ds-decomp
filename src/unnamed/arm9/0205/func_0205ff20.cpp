//cpp
#include "types.h"
#include "IRQ.h"

extern "C" {

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

u32 func_0205ff20(void) {
    u32 saved = IRQ::Disable();
    u32 r2 = data_020a8114.busy;
    if (r2 != 0) {
        IRQ::Restore(saved);
        return 0;
    }
    data_020a8114.busy = 1;
    IRQ::Restore(saved);
    return 1;
}
}
