//cpp
#include "GX.h"
#include "Ov007Display.h"

extern "C" {

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
void func_ov007_020c33d0(Ov007CharRecord *rec, int target, unsigned int offset) {
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
