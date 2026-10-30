#include "Ov007Spring.h"

extern void func_ov007_020c831c(Ov007Follower *f, int damping, int shift);

/* Integrates every point of the list (func_ov007_020c831c). */
void func_ov007_020c7504(Ov007PointList *list, int damping, int shift) {
    int i;
    for (i = 0; i < list->count; i++) {
        func_ov007_020c831c(list->items[i], damping, shift);
    }
}
