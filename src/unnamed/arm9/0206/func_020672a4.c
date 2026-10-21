#include "types.h"
extern u32 _ZN3IRQ7DisableEv(void);
extern void _ZN3IRQ7RestoreEj(u32 prev);

/* File-local mirror of include/private/arm9_a9db8_mb_parent.h's MbParentWork
 * (the multiboot parent work data_020a9db8 points at), the one field set
 * here. 0x14e4 is the header's pad_14e4: this function stores it,
 * func_02066fb0 calls it with (child, state, arg) when it is not null, and
 * func_02068ae8 saves it across its clear of the work and puts it back
 * through this function -- NitroSDK's parent_callback. */
typedef struct MbParentWork {
    u8 pad_0000[0x14e4];
    u32 mParentCallback; /* 0x14e4 */
} MbParentWork;

extern char *data_020a9db8; /* 0x020a9db8 */

/* NitroSDK MB_CommSetParentStateCallback(callback): store the parent state
 * callback with interrupts off. */
void func_020672a4(u32 val) {
    u32 r4 = val;
    u32 saved = _ZN3IRQ7DisableEv();
    ((MbParentWork *)data_020a9db8)->mParentCallback = r4;
    _ZN3IRQ7RestoreEj(saved);
}
