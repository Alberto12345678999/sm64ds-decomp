#include "Ov007Display.h"

extern int func_ov007_020c3df4(int heapName, void *size);

/* Allocates a character record (the menu's alloc hook) and fills it. */
Ov007CharRecord *func_ov007_020c3550(const void *tiles, int width, int height, int is8bpp) {
    Ov007CharRecord *rec =
        (Ov007CharRecord *)func_ov007_020c3df4(0, (void *)sizeof(Ov007CharRecord));
    rec->tiles = tiles;
    rec->width = width;
    rec->height = height;
    rec->is8bpp = is8bpp;
    rec->reserved = 0;
    return rec;
}
