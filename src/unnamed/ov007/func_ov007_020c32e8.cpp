//cpp
#include "GX.h"

extern "C" {

/* The 8-byte palette record func_ov007_020c3398 builds; only the slots
 * this file reads. */
typedef struct Ov007Palette {
    const void *colors;        /* 0x00 */
    unsigned short colorCount; /* 0x04 */
} Ov007Palette;

/* Loads a palette record's colours into palette RAM at 0x20-byte row
 * `row`: target 0/1 the main engine's OBJ/BG palette, 2/3 the sub
 * engine's. `skip` moves the source on by bytes but shortens the copy by
 * colours; every ov007 caller passes 0. */
void func_ov007_020c32e8(char *c, int target, unsigned int row, int skip) {
    Ov007Palette *pal = (Ov007Palette *)c;
    unsigned int offset = row << 5;
    unsigned int size = (unsigned int)((pal->colorCount - skip) << 1);
    switch (target) {
    case 0:
        GX::LoadOBJPltt((const char *)pal->colors + skip, offset, size);
        break;
    case 1:
        GX::LoadBGPltt((const char *)pal->colors + skip, offset, size);
        break;
    case 2:
        GXS::LoadOBJPltt((const char *)pal->colors + skip, offset, size);
        break;
    case 3:
        GXS::LoadBGPltt((const char *)pal->colors + skip, offset, size);
        break;
    }
}
}
