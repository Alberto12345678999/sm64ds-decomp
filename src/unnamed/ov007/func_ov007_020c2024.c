#include "Ov007Touch.h"

extern int data_ov007_02103240[];
extern void *func_ov007_020c3df4(int heapName, int size);
extern void func_ov007_020c2024(Ov007Touch *t);

/* Builds the touch-panel record (include/Ov007Touch.h) from the heap at
 * data_ov007_02103240. */
Ov007Touch *func_ov007_020c2068(void) {
    Ov007Touch *t = func_ov007_020c3df4((int)data_ov007_02103240, sizeof(Ov007Touch));
    func_ov007_020c2024(t);
    return t;
}

/* Clears the touch record's counters, positions and flags; the samples are
 * left for func_ov007_020c1db0's first reading. */
void func_ov007_020c2024(Ov007Touch *t) {
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
