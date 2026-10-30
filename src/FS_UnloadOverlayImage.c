/* NitroSDK FS_overlay.c FS_UnloadOverlayImage: func_0205dc7c sits where pret
 * has FS_EndOverlay. */
#include "nitro/fs/overlay.h"

extern void func_0205dc7c(void *p_ovi);

int FS_UnloadOverlayImage(FSOverlayInfo *p_ovi) {
    func_0205dc7c(p_ovi);
    return 1;
}
