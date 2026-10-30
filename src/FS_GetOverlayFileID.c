/* NitroSDK FS_overlay.c FS_GetOverlayFileID: the overlay's FSFileID, the
 * ROM archive (data_020a8074, the archive FSi_InitRom registers as "rom")
 * and the header's file_id. struct Pair is FSFileID. */
struct Pair {
    void *arc;
    int file_id;
};

/* FSOverlayInfo's header, up to file_id */
struct OverlayHeader {
    int id;               /* 0x00 */
    void *ram_address;    /* 0x04 */
    int ram_size;         /* 0x08 */
    int bss_size;         /* 0x0c */
    void *sinit_init;     /* 0x10 */
    void *sinit_init_end; /* 0x14 */
    int file_id;          /* 0x18 */
};

extern int data_020a8074;

void FS_GetOverlayFileID(struct Pair *dst, void *ovi) {
    const struct OverlayHeader *header = ovi;
    struct Pair ret;
    ret.arc = &data_020a8074;
    ret.file_id = header->file_id;
    *dst = ret;
}
