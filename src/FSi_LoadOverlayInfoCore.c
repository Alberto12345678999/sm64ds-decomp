/* NitroSDK FS_overlay.c FSi_LoadOverlayInfoCore, an older revision than
 * pret's (it stops after reading the header; there is no file_pos): pick the
 * ARM9 or ARM7 overlay table region, bounds-check entry `id`, open the table
 * directly in the archive (FS_OpenFileDirect), read the 0x20-byte header,
 * and set the target. */
#include "nitro/fs/overlay.h"

struct FSArchive;

extern void FS_InitFile(void *s);
extern int FS_OpenFileDirect(char *p_file, struct FSArchive *p_arc, u32 image_top, u32 image_bottom,
                             u32 file_index);
extern int FS_ReadFile(void *s, void *b, int c);
extern int FS_CloseFile(void *self);

int FSi_LoadOverlayInfoCore(FSOverlayInfo *p_ovi, int target, int id, struct FSArchive *arc,
                            u32 offset_arm9, u32 len_arm9, u32 offset_arm7, u32 len_arm7) {
    char file[0x48];
    u32 pos;
    u32 offset;
    u32 length;
    if (target == 0) {
        length = len_arm9;
        offset = offset_arm9;
    } else {
        length = len_arm7;
        offset = offset_arm7;
    }
    pos = id << 5;
    if (pos >= length)
        return 0;
    FS_InitFile(file);
    FS_OpenFileDirect(file, arc, offset + pos, offset + length, -1);
    FS_ReadFile(file, p_ovi, 0x20);
    FS_CloseFile(file);
    p_ovi->target = target;
    return 1;
}
