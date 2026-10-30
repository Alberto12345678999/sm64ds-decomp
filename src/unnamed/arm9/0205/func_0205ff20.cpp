//cpp
#include "types.h"
#include "IRQ.h"
#include "nitro/spi/pm.h"

extern "C" {

/* PMi_Lock by shape: claim the channel; 0 if it is already held. */
u32 func_0205ff20(void) {
    u32 saved = IRQ::Disable();
    u32 r2 = data_020a8114.lock;
    if (r2 != 0) {
        IRQ::Restore(saved);
        return 0;
    }
    data_020a8114.lock = 1;
    IRQ::Restore(saved);
    return 1;
}
}
