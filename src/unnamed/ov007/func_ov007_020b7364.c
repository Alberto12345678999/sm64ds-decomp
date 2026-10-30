#include "Ov007BgLayer.h"

/* The 0x48-byte 2D display record func_ov007_020b7594 builds; names as
 * there, only the slots this file reads. */
typedef struct Ov007Display {
    char pad_00[8];
    Ov007BgList *bgListMain; /* 0x08 */
    Ov007BgList *bgListSub;  /* 0x0c */
} Ov007Display;

extern void func_ov007_020c03b0(Ov007BgList *list);

/* Applies the main and sub BG layer lists (func_ov007_020c03b0). */
void func_ov007_020b7364(Ov007Display *d) {
    func_ov007_020c03b0(d->bgListMain);
    func_ov007_020c03b0(d->bgListSub);
}
