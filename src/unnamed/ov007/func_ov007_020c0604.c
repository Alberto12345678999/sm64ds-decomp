#include "Ov007BgLayer.h"

extern int *func_ov007_020c3df4(int, int);
extern void func_ov007_020c05e4(int *);

/* Builds an empty BG layer list for `engines` and `mask`. */
int *func_ov007_020c0604(int engines, int mask) {
    Ov007BgList *list = (Ov007BgList *)func_ov007_020c3df4(0, sizeof(Ov007BgList));
    func_ov007_020c05e4((int *)list);
    list->engines = engines;
    list->mask = mask;
    return (int *)list;
}
