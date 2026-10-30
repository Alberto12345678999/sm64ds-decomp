#include "Ov007Display.h"

extern int func_ov007_020c3d40(int, int);

/* Sizes the character and palette tables (func_ov007_020b6d40 asks for 4
 * and 6), zeroed. */
void func_ov007_020b7320(Ov007Display *d, int a, int b) {
    d->characterCount = a;
    d->paletteCount = b;
    d->characters = (Ov007CharRecord **)func_ov007_020c3d40(0, a * sizeof(Ov007CharRecord *));
    d->palettes = (Ov007Palette **)func_ov007_020c3d40(0, b * sizeof(Ov007Palette *));
}
