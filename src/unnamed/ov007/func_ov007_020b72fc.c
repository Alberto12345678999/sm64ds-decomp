#include "Ov007Display.h"

extern int func_ov007_020c3d40(int, int);

/* Sizes the sprite-bank table (func_ov007_020b6d40 asks for 6), zeroed. */
void func_ov007_020b72fc(Ov007Display *d, int n) {
    d->spriteBankCount = n;
    d->spriteBanks = (Ov007SpriteBank **)func_ov007_020c3d40(0, n * sizeof(Ov007SpriteBank *));
}
