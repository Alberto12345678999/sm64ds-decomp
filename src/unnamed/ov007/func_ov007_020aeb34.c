typedef long long s64;

/* The 10-byte layout row func_ov007_020aea6c's item points at; names as in
 * func_ov007_020b5bf0. */
typedef struct Ov007ItemLayout {
    unsigned short kind; /* 0x0 */
    short homeX;         /* 0x2 */
    short homeY;         /* 0x4 */
    short slideX;        /* 0x6 */
    short slideY;        /* 0x8 */
} Ov007ItemLayout;

/* The 0x2c-byte record func_ov007_020aea6c allocates; names as in
 * func_ov007_020ae810, only the slots this file touches. */
typedef struct Ov007Item {
    char pad_00[8];
    int posX; /* 0x08: Q12 */
    int posY; /* 0x0c */
    char pad_10[0x14];
    Ov007ItemLayout *layout; /* 0x24 */
} Ov007Item;

/* Puts the item at its home position plus the slide offset scaled by t
 * (Q12, clamped to 0..1). c keeps the callers' char * spelling; `item` is
 * the typed view. */
void func_ov007_020aeb34(char *c, int t) {
    Ov007Item *item = (Ov007Item *)c;
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
