//cpp
#include "GX.h"

extern "C" {

/* The 0xc-byte character record func_ov007_020c3550 builds; only the slots
 * this file reads. */
typedef struct Ov007CharRecord {
    const void *tiles;    /* 0x00 */
    int is8bpp;           /* 0x04: 0x40-byte tiles when set, else 0x20 */
    unsigned char width;  /* 0x08: in tiles */
    unsigned char height; /* 0x09 */
} Ov007CharRecord;

/* The BG2/BG3 character loads of src/engine/gx/GXS.cpp, which keep their
 * func_ names there. */
void func_020560d4(const void *src, unsigned int offset, unsigned int size);
void func_02056014(const void *src, unsigned int offset, unsigned int count);
void func_020565b4(const void *src, unsigned int offset, unsigned int count);
void func_02056074(const void *src, unsigned int offset, unsigned int count);
void func_02055fb4(const void *src, unsigned int offset, unsigned int size);

/* Copies a character record's tiles to `offset` in one VRAM target: 0..4
 * the main engine's OBJ, BG0, BG1, BG2 and BG3 characters, 5..9 the sub
 * engine's. */
void func_ov007_020c33d0(char *c, int target, unsigned int offset) {
    Ov007CharRecord *rec = (Ov007CharRecord *)c;
    unsigned int tileSize = rec->is8bpp == 0 ? 0x20 : 0x40;
    unsigned int size = (unsigned int)rec->width * rec->height * tileSize;
    switch (target) {
    case 0:
        GX::LoadOBJ(rec->tiles, offset, size);
        break;
    case 1:
        GX::LoadBG0Char(rec->tiles, offset, size);
        break;
    case 2:
        GX::LoadBG1Char(rec->tiles, offset, size);
        break;
    case 3:
        func_020560d4(rec->tiles, offset, size);
        break;
    case 4:
        func_02056014(rec->tiles, offset, size);
        break;
    case 5:
        func_020565b4(rec->tiles, offset, size);
        break;
    case 6:
        GXS::LoadBG0Char(rec->tiles, offset, size);
        break;
    case 7:
        GXS::LoadBG1Char(rec->tiles, offset, size);
        break;
    case 8:
        func_02056074(rec->tiles, offset, size);
        break;
    case 9:
        func_02055fb4(rec->tiles, offset, size);
        break;
    }
}
}
