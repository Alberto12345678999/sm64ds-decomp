#include "Ov007Work.h"

extern void func_ov007_020ade14(void *node);
extern void func_ov007_020adbc8(void *slot);
extern void func_ov007_020b73b4(struct Ov007Display *d);
extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* Frees the nine item nodes, the eight layer slots and the display record. */
void func_ov007_020b6cd0(void) {
    int i;
    for (i = 0; i < 9; i++) {
        func_ov007_020ade14(WORK->itemNodes[i]);
    }
    for (i = 0; i < 8; i++) {
        func_ov007_020adbc8(WORK->layerSlots[i]);
    }
    func_ov007_020b73b4(WORK->display);
}
