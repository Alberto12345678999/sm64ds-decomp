/* NitroSDK FS_overlay.c FS_UnloadOverlayImage: func_0205dc7c sits where pret
 * has FS_EndOverlay. */
extern void func_0205dc7c(void *ovi);
int FS_UnloadOverlayImage(void *ovi) {
    func_0205dc7c(ovi);
    return 1;
}
