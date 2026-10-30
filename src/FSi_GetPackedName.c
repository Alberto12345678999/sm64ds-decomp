#include "types.h"

/* NitroSDK FS_archive.c FSi_GetPackedName: pack an archive name of at most
 * 3 characters into a word, 8 bits per character, folding 'A'..'Z' to lower
 * case and stopping at a NUL. The byte is read unsigned, as the SDK's
 * MI_ReadByte reads it: the build uses -char signed. */
u32 FSi_GetPackedName(const char *name, int name_len) {
    u32 ret = 0;
    if (name_len <= 3) {
        int i = 0;
        if (name_len > 0) {
            int shift = 0;
            do {
                u32 c = (u8)name[i];
                u32 lc;
                if (c == 0)
                    break;
                lc = c - 'A';
                if (lc <= 'Z' - 'A')
                    lc = lc + 'a';
                else
                    lc = lc + 'A';
                i++;
                ret |= lc << shift;
                shift += 8;
            } while (i < name_len);
        }
    }
    return ret;
}
