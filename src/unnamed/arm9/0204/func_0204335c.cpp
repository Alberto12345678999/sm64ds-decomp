//cpp
#include "fBase_c.h"

extern "C" {

/* The three Process callbacks are member-function-pointer constants in
 * .data. Under the old 1.2/sp2p3 pin this wrapper staged them through a
 * frame pointer and came out 0x68 bytes against the ROM's 0x5c; under
 * 2004/b56 the real member-pointer call reproduces it. */
extern fBase_c::AfterProcessFunction data_02099e94;
extern fBase_c::BeforeProcessFunction data_02099ec4;
extern fBase_c::ProcessFunction data_02099ebc;

int func_0204335c(void *self) {
    return ((fBase_c *)self)->Process(data_02099ebc, data_02099ec4, data_02099e94);
}
}
