//cpp
#include "types.h"
#include "private/arm9_a9db8_mb_parent.h"
#include "IRQ.h"

extern "C" {

/* The SDK's pPwork; char * is the spelling the other MB parent files share. */
extern char *data_020a9db8;

/* NitroSDK mb_parent.c: store the parent state callback with interrupts
 * off. */
void MB_CommSetParentStateCallback(u32 callback) {
    u32 saved = IRQ::Disable();
    ((MbParentWork *)data_020a9db8)->mParentCallback = callback;
    IRQ::Restore(saved);
}
}
