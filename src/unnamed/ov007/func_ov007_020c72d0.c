extern void func_ov007_020c7804(void *list);

/* The 0x10-byte grid func_ov007_020c73f0 builds; names as in
 * func_ov007_020c7240. */
typedef struct Ov007Grid {
    int columns;        /* 0x00 */
    int rows;           /* 0x04 */
    void **rowLists;    /* 0x08: one per row, columns points each */
    void **columnLists; /* 0x0c: one per column, rows points each */
} Ov007Grid;

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
