/* NitroSDK FS_overlay.c FS_UnloadOverlay: read the overlay's FSOverlayInfo
 * and unload its image. */
#include "nitro/fs/overlay.h"

extern int FS_LoadOverlayInfo(FSOverlayInfo *p_ovi, int target, int id);
extern int FS_UnloadOverlayImage(FSOverlayInfo *p_ovi);

int FS_UnloadOverlay(int target, int id) {
    FSOverlayInfo ovi;
    if (!FS_LoadOverlayInfo(&ovi, target, id) || !FS_UnloadOverlayImage(&ovi))
        return 0;
    return 1;
}
