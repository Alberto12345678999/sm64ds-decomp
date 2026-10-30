#include "Ov007Display.h"

extern int func_ov007_020c3df4(int heapName, void *size);

/* Allocates a palette record (the menu's alloc hook) and fills it. */
Ov007Palette *func_ov007_020c3398(const void *colors, int colorCount) {
    Ov007Palette *pal = (Ov007Palette *)func_ov007_020c3df4(0, (void *)sizeof(Ov007Palette));
    pal->colors = colors;
    pal->colorCount = colorCount;
    pal->reserved = 0;
    return pal;
}
