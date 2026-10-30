/* NitroSDK FS_overlay.c FS_LoadOverlayInfo, an older revision than pret's
 * (no FS_OpenFileFast/file_pos tail): while the ARM9 or ARM7 overlay table
 * is in memory ({address, length}, data_020a8064/data_020a806c), copy entry
 * `id` out of it and set the target; otherwise read it from the ROM through
 * FSi_LoadOverlayInfoCore, with the ROM archive (data_020a8074) and the ROM
 * header's ARM9/ARM7 overlay table regions (0x027ffe50, 0x027ffe58). The
 * game's own copy of this is func_02018c00. */
#include "nitro/fs/overlay.h"

extern int data_020a8064[2];
extern int data_020a806c[2];
extern int data_020a8074;
extern void CpuCopy8(void *dst, void *src, int n);
extern int FSi_LoadOverlayInfoCore(FSOverlayInfo *p_ovi, int target, int id, void *arc,
                                   int offset_arm9, int len_arm9, int offset_arm7, int len_arm7);

int FS_LoadOverlayInfo(FSOverlayInfo *p_ovi, int target, int id) {
    int *pr = (target == 0) ? data_020a8064 : data_020a806c;
    int offset = pr[0];
    if (offset != 0) {
        int pos = id << 5;
        if ((unsigned int)pos >= (unsigned int)pr[1])
            return 0;
        CpuCopy8((void *)(offset + pos), p_ovi, 0x20);
        p_ovi->target = target;
        return 1;
    }
    int *ovt9 = (int *)0x27ffe50;
    int *ovt7 = (int *)0x27ffe58;
    return FSi_LoadOverlayInfoCore(p_ovi, target, id, &data_020a8074, ovt9[0], ovt9[1], ovt7[0],
                                   ovt7[1]);
}
