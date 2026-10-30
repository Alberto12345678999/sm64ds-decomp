#include "Ov007Spring.h"

extern void func_ov007_020c7804(void *list);

/* Binds the links of every row list, then every column list
 * (func_ov007_020c7804). */
void func_ov007_020c72d0(Ov007Grid *grid) {
    int i;
    for (i = 0; i < grid->rows; i++) {
        func_ov007_020c7804(grid->rowLists[i]);
    }
    for (i = 0; i < grid->columns; i++) {
        func_ov007_020c7804(grid->columnLists[i]);
    }
}
