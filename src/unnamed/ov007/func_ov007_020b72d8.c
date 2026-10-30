#include "Ov007Display.h"

extern int func_ov007_020c3d40(const char *, int);

/* Sizes the BG layer table (func_ov007_020b6d40 asks for 8), zeroed. */
void func_ov007_020b72d8(Ov007Display *d, int n) {
    d->bgLayerCount = n;
    d->bgLayers = (Ov007BgLayer **)func_ov007_020c3d40(0, n * sizeof(Ov007BgLayer *));
}
