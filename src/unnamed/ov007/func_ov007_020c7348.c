#include "Ov007Spring.h"

/* Clears a grid. */
void func_ov007_020c7348(Ov007Grid *grid) {
    grid->rows = 0;
    grid->columns = grid->rows;
    grid->columnLists = 0;
    grid->rowLists = grid->columnLists;
}
