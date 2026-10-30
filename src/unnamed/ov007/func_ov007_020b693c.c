#include "Ov007Work.h"

extern struct Ov007ItemView *func_ov007_020b4c04(int i);
extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* Builds the 0x18 item views. */
void func_ov007_020b693c(void) {
    int i;
    for (i = 0; i < 0x18; i++) {
        WORK->itemViews[i] = func_ov007_020b4c04(i);
    }
}
