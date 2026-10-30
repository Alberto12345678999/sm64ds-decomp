#include "Ov007Spring.h"

extern void func_ov007_020c7560(Ov007PointList *list, int stiffness, int damping);

/* Runs func_ov007_020c7560's spring step along every row, then every
 * column. */
void func_ov007_020c7240(Ov007Grid *grid, int stiffness, int damping) {
    int i;
    for (i = 0; i < grid->rows; i++) {
        func_ov007_020c7560(grid->rowLists[i], stiffness, damping);
    }
    for (i = 0; i < grid->columns; i++) {
        func_ov007_020c7560(grid->columnLists[i], stiffness, damping);
    }
}
