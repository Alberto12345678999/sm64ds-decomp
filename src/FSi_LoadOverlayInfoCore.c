/* NitroSDK FS_overlay.c FSi_LoadOverlayInfoCore, an older revision than
 * pret's (it stops after reading the header; there is no file_pos): pick the
 * ARM9 or ARM7 overlay table region, bounds-check entry `id`, open the table
 * directly in the archive (func_0205d5e8, FS_OpenFileDirect's body), read
 * the 0x20-byte header, and set the target. */
#include "nitro/fs/overlay.h"

extern void FS_InitFile(void *s);
extern int func_0205d5e8(void *s, int b, int c, int d, int e);
extern int FS_ReadFile(void *s, void *b, int c);
extern int FS_CloseFile(void *self);

int FSi_LoadOverlayInfoCore(FSOverlayInfo *p_ovi, int target, int id, int arc, int offset_arm9,
                            int len_arm9, int offset_arm7, int len_arm7) {
    char file[0x48];
    int pos;
    int offset;
    int length;
    if (target == 0) {
        length = len_arm9;
        offset = offset_arm9;
    } else {
        length = len_arm7;
        offset = offset_arm7;
    }
    pos = id << 5;
    if ((unsigned int)pos >= (unsigned int)length)
        return 0;
    FS_InitFile(file);
    func_0205d5e8(file, arc, offset + pos, offset + length, -1);
    FS_ReadFile(file, p_ovi, 0x20);
    FS_CloseFile(file);
    p_ovi->target = target;
    return 1;
}
