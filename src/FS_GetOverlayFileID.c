/* NitroSDK FS_overlay.c FS_GetOverlayFileID: the overlay's FSFileID, the
 * ROM archive (data_020a8074, the archive FSi_InitRom registers as "rom")
 * and the header's file_id. struct Pair is FSFileID. */
#include "nitro/fs/overlay.h"

struct FSArchive;

struct Pair {
    void *arc;
    int file_id;
};

extern struct FSArchive data_020a8074; /* fsi_arc_rom */

void FS_GetOverlayFileID(struct Pair *dst, const FSOverlayInfo *p_ovi) {
    struct Pair ret;
    ret.arc = &data_020a8074;
    ret.file_id = p_ovi->header.file_id;
    *dst = ret;
}
