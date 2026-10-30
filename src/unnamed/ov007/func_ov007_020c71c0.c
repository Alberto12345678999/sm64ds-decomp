#include "Ov007Spring.h"

extern void func_ov007_020c80c8(Ov007Follower *f, int damping, int shift);

/* Integrates every grid point along z (func_ov007_020c80c8), row by row. */
void func_ov007_020c71c0(Ov007Grid *grid, int damping, int shift) {
    int j, i;
    for (i = 0; i < grid->rows; i++)
        for (j = 0; j < grid->columns; j++)
            func_ov007_020c80c8(grid->rowLists[i]->items[j], damping, shift);
}
