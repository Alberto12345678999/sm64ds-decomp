/* The 0x48-byte 2D display record func_ov007_020b7594 builds; names as
 * there, only the slots this file writes. */
typedef struct Ov007Display {
    char pad_00[0x30];
    int bgLayerCount; /* 0x30 */
    int bgLayers;     /* 0x34: func_ov007_020c95fc layers */
} Ov007Display;

extern int func_ov007_020c3d40(int, int);

/* Sizes the BG layer table (func_ov007_020b6d40 asks for 8), zeroed.
 * c keeps the tree's char * spelling; `d` is the typed view. */
void func_ov007_020b72d8(char *c, int n) {
    Ov007Display *d = (Ov007Display *)c;
    d->bgLayerCount = n;
    d->bgLayers = func_ov007_020c3d40(0, n << 2);
}
