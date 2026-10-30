#include "Ov007Spring.h"

extern void func_ov007_020c7d60(Ov007Link *link, int stiffness, int damping);
extern void func_ov007_020c7c60(Ov007Link *link, int stiffness, int damping);
extern void func_ov007_020c7b2c(Ov007Link *link, int stiffness, int damping);
extern void func_ov007_020c7a84(Ov007Link *link, int stiffness, int damping);

/* One spring step over every link of the list, with the step its
 * springMode picks: 0 holds the rest length, 1 the rest offset, 2 is the
 * x/y spring and 3 the z-only one. stiffness and damping are Q12. */
void func_ov007_020c7560(Ov007PointList *list, int stiffness, int damping) {
    int n;
    int i;
    if (list->count <= 1) {
        n = 0;
    } else {
        n = list->count - ((list->flags & 2) ? 0 : 1);
    }
    switch (list->springMode) {
    case 0:
        for (i = 0; i < n; i++)
            func_ov007_020c7d60(list->links[i], stiffness, damping);
        break;
    case 1:
        for (i = 0; i < n; i++)
            func_ov007_020c7c60(list->links[i], stiffness, damping);
        break;
    case 2:
        for (i = 0; i < n; i++)
            func_ov007_020c7b2c(list->links[i], stiffness, damping);
        break;
    case 3:
        for (i = 0; i < n; i++)
            func_ov007_020c7a84(list->links[i], stiffness, damping);
        break;
    }
}
