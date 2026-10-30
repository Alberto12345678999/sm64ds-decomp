/* Frees a sprite-bank cell's OAM attribute list, the cell's first word
 * (func_ov007_020c121c's per-cell free). */

extern int func_ov007_020c3d1c(int p);

int func_ov007_020c13f4(int *cell) {
    return func_ov007_020c3d1c(*cell);
}
