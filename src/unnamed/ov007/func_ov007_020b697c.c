#include "Ov007Work.h"

extern void *func_ov007_020b3f20(int n);
extern void *func_ov007_020b2308(void *a, int b);

extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* Builds the 11 textures of the BMD that func_ov007_020b3f20 loads as file
 * 0x16. */
void func_ov007_020b697c(void) {
    int i;
    void *n = func_ov007_020b3f20(0x16);
    for (i = 0; i < 0xb; i++) {
        WORK->textures[i] = func_ov007_020b2308(n, i);
    }
}
