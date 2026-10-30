#include "Ov007BgLayer.h"

/* The 0x48-byte 2D display record func_ov007_020b7594 builds; names as
 * there. */
typedef struct Ov007Display {
    void *oamListMain;   /* 0x00 */
    void *oamListSub;    /* 0x04 */
    Ov007BgList *bgListMain; /* 0x08 */
    Ov007BgList *bgListSub;  /* 0x0c */
    void *oamMain;       /* 0x10 */
    void *oamSub;        /* 0x14 */
    int transitionCount; /* 0x18 */
    void **transitions;  /* 0x1c */
    int characterCount;  /* 0x20 */
    void **characters;   /* 0x24 */
    int paletteCount;    /* 0x28 */
    void **palettes;     /* 0x2c */
    int bgLayerCount;    /* 0x30 */
    void **bgLayers;     /* 0x34 */
    int spriteBankCount; /* 0x38 */
    void **spriteBanks;  /* 0x3c */
    int oamNodeCount;    /* 0x40 */
    void **oamNodes;     /* 0x44 */
} Ov007Display;

typedef char Ov007Display_size_must_be_0x48[sizeof(Ov007Display) == 0x48 ? 1 : -1];

/* The menu's free hook and the per-record frees; the long-branch veneers
 * (func_ov007_020c105c, 020c05f8, 020c8b04, 020c3544, 020c338c, 020c0a9c)
 * all tail-call func_ov007_020c3d1c. */
extern void func_ov007_020c3d1c(void *p);
extern void func_ov007_020c105c(void *p);
extern void func_ov007_020c05f8(void *p);
extern void func_ov007_020c8b04(void *p);
extern void func_ov007_020c3544(void *p);
extern void func_ov007_020c338c(void *p);
extern void func_ov007_020c121c(void *p);
extern void func_ov007_020c1180(void *p);
extern void func_ov007_020c0a9c(void *p);

/* Frees the display record and everything its tables hold. */
void func_ov007_020b73b4(Ov007Display *d) {
    void **arr;
    int i;

    func_ov007_020c3d1c(d->oamMain);
    func_ov007_020c3d1c(d->oamSub);
    func_ov007_020c105c(d->oamListMain);
    func_ov007_020c105c(d->oamListSub);
    func_ov007_020c05f8(d->bgListMain);
    func_ov007_020c05f8(d->bgListSub);

    if (d->transitionCount > 0) {
        arr = d->transitions;
        for (i = 0; i < d->transitionCount; i++)
            if (arr[i])
                func_ov007_020c8b04(arr[i]);
        func_ov007_020c3d1c(arr);
    }

    if (d->characterCount > 0) {
        arr = d->characters;
        for (i = 0; i < d->characterCount; i++)
            if (arr[i])
                func_ov007_020c3544(arr[i]);
        func_ov007_020c3d1c(arr);
    }

    if (d->paletteCount > 0) {
        arr = d->palettes;
        for (i = 0; i < d->paletteCount; i++)
            if (arr[i])
                func_ov007_020c338c(arr[i]);
        func_ov007_020c3d1c(arr);
    }

    if (d->spriteBankCount > 0) {
        arr = d->spriteBanks;
        for (i = 0; i < d->spriteBankCount; i++)
            if (arr[i])
                func_ov007_020c121c(arr[i]);
        func_ov007_020c3d1c(arr);
    }

    if (d->oamNodeCount > 0) {
        arr = d->oamNodes;
        for (i = 0; i < d->oamNodeCount; i++)
            if (arr[i])
                func_ov007_020c1180(arr[i]);
        func_ov007_020c3d1c(arr);
    }

    if (d->bgLayerCount > 0) {
        arr = d->bgLayers;
        for (i = 0; i < d->bgLayerCount; i++)
            if (arr[i])
                func_ov007_020c0a9c(arr[i]);
        func_ov007_020c3d1c(arr);
    }

    func_ov007_020c3d1c(d);
}
