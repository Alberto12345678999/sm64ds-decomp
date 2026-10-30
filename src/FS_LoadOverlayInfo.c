/* NitroSDK FS_overlay.c FS_LoadOverlayInfo, an older revision than pret's
 * (no FS_OpenFileFast/file_pos tail): while the ARM9 or ARM7 overlay table
 * is in memory ({address, length}, data_020a8064/data_020a806c), copy entry
 * `id` out of it and set the target; otherwise read it from the ROM through
 * FSi_LoadOverlayInfoCore, with the ROM archive (data_020a8074) and the ROM
 * header's ARM9/ARM7 overlay table regions (0x027ffe50, 0x027ffe58). The
 * game's own copy of this is func_02018c00. */
#include "nitro/fs/overlay.h"

struct FSArchive;
/* NitroSDK CARDRomRegion. */
struct CARDRomRegion {
    u32 offset;
    u32 length;
};

extern struct CARDRomRegion data_020a8064; /* fsi_ovt9 */
extern struct CARDRomRegion data_020a806c; /* fsi_ovt7 */
extern struct FSArchive data_020a8074;     /* fsi_arc_rom */
extern void CpuCopy8(void *dst, void *src, int n);
extern int FSi_LoadOverlayInfoCore(FSOverlayInfo *p_ovi, int target, int id, struct FSArchive *arc,
                                   u32 offset_arm9, u32 len_arm9, u32 offset_arm7, u32 len_arm7);

int FS_LoadOverlayInfo(FSOverlayInfo *p_ovi, int target, int id) {
    struct CARDRomRegion *pr = (target == 0) ? &data_020a8064 : &data_020a806c;
    u32 offset = pr->offset;
    if (offset != 0) {
        u32 pos = id << 5;
        if (pos >= pr->length)
            return 0;
        CpuCopy8((void *)(offset + pos), p_ovi, 0x20);
        p_ovi->target = target;
        return 1;
    }
    struct CARDRomRegion *ovt9 = (struct CARDRomRegion *)0x27ffe50;
    struct CARDRomRegion *ovt7 = (struct CARDRomRegion *)0x27ffe58;
    return FSi_LoadOverlayInfoCore(p_ovi, target, id, &data_020a8074, ovt9->offset, ovt9->length,
                                   ovt7->offset, ovt7->length);
}
