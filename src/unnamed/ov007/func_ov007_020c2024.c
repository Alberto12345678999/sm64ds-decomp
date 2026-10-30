#include "Ov007Touch.h"

extern int data_ov007_02103240[];
extern char *func_ov007_020c3df4(int, int);
extern void func_ov007_020c2024(char *);

/* Builds the touch-panel record (include/Ov007Touch.h) from the heap at
 * data_ov007_02103240. */
char *func_ov007_020c2068(void) {
    char *p = func_ov007_020c3df4((int)data_ov007_02103240, sizeof(Ov007Touch));
    func_ov007_020c2024(p);
    return p;
}

/* Clears the touch record's counters, positions and flags; the samples are
 * left for func_ov007_020c1db0's first reading. c keeps the tree's char *
 * spelling; `t` is the typed view. */
void func_ov007_020c2024(char *c) {
    Ov007Touch *t = (Ov007Touch *)c;
    t->heldFrames = 0;
    t->releasedFrames = 0;
    t->countdown = 0;
    t->pressY = 0;
    t->pressX = t->pressY;
    t->releaseY = 0;
    t->releaseX = t->releaseY;
    t->dragY = 0;
    t->dragX = t->dragY;
    t->flags = 0;
    t->pad_40 = -1;
}
