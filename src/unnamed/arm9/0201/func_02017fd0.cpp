//cpp
#include "types.h"
#include "CP15.h"

extern "C" {

/* The head of NitroSDK's FSOverlayInfo (see LoadOverlay.c), as far as this
   reads it. */
typedef struct {
    u32 id;            /* +0 */
    void *ram_address; /* +4 */
    u32 ram_size;      /* +8 */
    u32 bss_size;      /* +c */
} CodeRegion;

extern void MultiStore_Int(u32 val, void *dst, u32 size);

/* Poison an unloaded overlay's RAM (UnloadOverlay): invalidate both caches
   over its code and bss, then fill them with 0xe6000010, an ARM undefined
   instruction, so a stale call into it traps. */
void func_02017fd0(CodeRegion *rgn) {
    u32 ramSize;
    u32 bssSize;
    void *ptr;
    u32 len;
    volatile u32 fillVal;

    ramSize = rgn->ram_size;
    bssSize = rgn->bss_size;
    ptr = rgn->ram_address;
    len = ramSize + bssSize;

    CP15::InvalidateInstructionCache((u32)ptr, len);
    CP15::InvalidateDataCache((u32)ptr, len);

    fillVal = 0xe6000010;
    MultiStore_Int(fillVal, ptr, len);
}
}
