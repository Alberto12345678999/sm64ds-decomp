/* NitroSDK FS_overlay.c FS_UnloadOverlay: read the overlay's FSOverlayInfo
 * (func_0205df40, in FS_LoadOverlayInfo's place) and unload its image. */
extern int func_0205df40(void *ovi, int target, int id);
extern int FS_UnloadOverlayImage(void *ovi);

int FS_UnloadOverlay(int target, int id) {
    char ovi[0x24];
    if (!func_0205df40(ovi, target, id) || !FS_UnloadOverlayImage(ovi))
        return 0;
    return 1;
}
