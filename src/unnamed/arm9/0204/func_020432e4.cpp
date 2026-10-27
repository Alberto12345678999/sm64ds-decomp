//cpp
#include "fBase_c.h"

extern "C" {

/* The three Process callbacks are member-function-pointer constants in
 * .data. Under the old 1.2/sp2p3 pin this wrapper staged them through a
 * frame pointer and came out 0x84 bytes against the ROM's 0x78; under
 * 2004/b56 the real member-pointer call reproduces it. */
extern fBase_c::AfterProcessFunction data_02099e84;
extern fBase_c::BeforeProcessFunction data_02099e7c;
extern fBase_c::ProcessFunction data_02099e8c;
extern void func_0204302c(int id);

int func_020432e4(fBase_c *self) {
    /* The actor ID is taken before Process runs and handed to the
     * func_0204302c hook on a result of 1. */
    unsigned short id = self->actorID;
    int r = self->Process(data_02099e8c, data_02099e7c, data_02099e84);
    if (r == 1)
        func_0204302c(id);
    return r;
}
}
