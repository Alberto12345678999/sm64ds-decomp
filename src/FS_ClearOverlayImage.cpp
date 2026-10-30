//cpp
/* NitroSDK FS_overlay.c FS_ClearOverlayImage: invalidate the I- and D-cache
 * over the overlay's whole region (image and bss), then zero the bss after
 * the image. */
#include "types.h"
#include "CP15.h"
#include "nitro/fs/overlay.h"

extern "C" {

void func_0205a588(u32 dst, u32 val, u32 size);

void FS_ClearOverlayImage(FSOverlayInfo *p_ovi) {
    u32 im_start = (u32)p_ovi->header.ram_address;
    u32 ram_size = p_ovi->header.ram_size;
    u32 bss_size = p_ovi->header.bss_size;
    u32 total_size = ram_size + bss_size;
    CP15::InvalidateInstructionCache(im_start, total_size);
    CP15::InvalidateDataCache(im_start, total_size);
    func_0205a588(im_start + ram_size, 0, total_size - ram_size);
}
}
