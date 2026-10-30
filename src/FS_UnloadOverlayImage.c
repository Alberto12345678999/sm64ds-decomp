/* NitroSDK FS_overlay.c FS_UnloadOverlayImage. */
#include "nitro/fs/overlay.h"

extern void FS_EndOverlay(FSOverlayInfo *p_ovi);

int FS_UnloadOverlayImage(FSOverlayInfo *p_ovi) {
    FS_EndOverlay(p_ovi);
    return 1;
}
