#include "Ov007Display.h"

extern void func_ov007_020c03b0(Ov007BgList *list);

/* Applies the main and sub BG layer lists (func_ov007_020c03b0). */
void func_ov007_020b7364(Ov007Display *d) {
    func_ov007_020c03b0(d->bgListMain);
    func_ov007_020c03b0(d->bgListSub);
}
