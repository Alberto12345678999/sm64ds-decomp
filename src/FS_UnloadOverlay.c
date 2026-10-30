/* NitroSDK FS_overlay.c FS_UnloadOverlay: read the overlay's FSOverlayInfo
 * and unload its image. func_0205df40 is the SDK's FS_LoadOverlayInfo (an
 * older revision of pret's body); func_02018c00 is the game's own copy. */
#include "nitro/fs/overlay.h"

extern int func_0205df40(void *p_ovi, int target, int id);
extern int FS_UnloadOverlayImage(FSOverlayInfo *p_ovi);

int FS_UnloadOverlay(int target, int id) {
    FSOverlayInfo ovi;
    if (!func_0205df40(&ovi, target, id) || !FS_UnloadOverlayImage(&ovi))
        return 0;
    return 1;
}
