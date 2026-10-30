/* The 0x10-byte grid func_ov007_020c73f0 builds; names as in
 * func_ov007_020c7240. */
typedef struct Ov007Grid {
    int columns;        /* 0x00 */
    int rows;           /* 0x04 */
    void **rowLists;    /* 0x08: one per row, columns points each */
    void **columnLists; /* 0x0c: one per column, rows points each */
} Ov007Grid;

/* Clears a grid. */
void func_ov007_020c7348(Ov007Grid *grid) {
    grid->rows = 0;
    grid->columns = grid->rows;
    grid->columnLists = 0;
    grid->rowLists = grid->columnLists;
}
