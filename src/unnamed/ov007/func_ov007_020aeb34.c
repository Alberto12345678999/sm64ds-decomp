#include "Ov007Item.h"

/* Puts the item at its home position plus the slide offset scaled by t
 * (Q12, clamped to 0..1). */
void func_ov007_020aeb34(Ov007Item *item, int t) {
    Ov007ItemLayout *layout = item->layout;
    int dx = layout->slideX << 12;
    if (t < 0x1000) {
        if (t <= 0)
            dx = 0;
        else
            dx = (int)(((s64)t * dx) >> 12);
    }
    int dy = layout->slideY << 12;
    if (t < 0x1000) {
        if (t <= 0)
            dy = 0;
        else
            dy = (int)(((s64)t * dy) >> 12);
    }
    item->posX = dx + (layout->homeX << 12);
    item->posY = dy + (layout->homeY << 12);
}
