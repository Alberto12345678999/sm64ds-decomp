#include "Ov007Spring.h"

extern void func_ov007_020c7560(void* p, int b, int c);

/* Runs func_ov007_020c7560's spring step with (b, d) along every row, then
 * every column. c keeps its char * spelling; `grid` is the typed view. */
void func_ov007_020c7240(char* c, int b, int d) {
    Ov007Grid *grid = (Ov007Grid *)c;
    int i;
    for (i = 0; i < grid->rows; i++) {
        func_ov007_020c7560(grid->rowLists[i], b, d);
    }
    for (i = 0; i < grid->columns; i++) {
        func_ov007_020c7560(grid->columnLists[i], b, d);
    }
}
