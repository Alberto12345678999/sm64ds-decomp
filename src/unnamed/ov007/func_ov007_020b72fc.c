/* The 0x48-byte 2D display record func_ov007_020b7594 builds; names as
 * there, only the slots this file writes. */
typedef struct Ov007Display {
    char pad_00[0x38];
    int spriteBankCount; /* 0x38 */
    int spriteBanks;     /* 0x3c: func_ov007_020c9688 banks */
} Ov007Display;

extern int func_ov007_020c3d40(int, int);

/* Sizes the sprite-bank table (func_ov007_020b6d40 asks for 6), zeroed.
 * c keeps the tree's char * spelling; `d` is the typed view. */
void func_ov007_020b72fc(char *c, int n) {
    Ov007Display *d = (Ov007Display *)c;
    d->spriteBankCount = n;
    d->spriteBanks = func_ov007_020c3d40(0, n << 2);
}
