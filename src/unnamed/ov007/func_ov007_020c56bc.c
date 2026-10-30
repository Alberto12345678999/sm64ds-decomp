extern int func_ov007_020c3ba8(int n);
#pragma opt_propagation off

typedef struct {
    int x, y, z;
} Vec3;

/* A link between two points; names as in func_ov007_020c6314. */
typedef struct Ov007Link {
    void *from; /* 0x0 */
    void *to;   /* 0x4 */
    int length; /* 0x8 */
    int dir[3]; /* 0xc: the rest offset from `to` to `from` */
} Ov007Link;

/* A point list as func_ov007_020c798c builds it; only the count. */
typedef struct Ov007PointList {
    void **items; /* 0x0 */
    int count;    /* 0x4 */
} Ov007PointList;

/* The 0xd0-byte touch picker func_ov007_020c690c builds; names as in that
 * file and func_ov007_020c684c, only the slots this function touches. */
typedef struct Ov007Picker {
    char pad_00[8];
    int groupCount; /* 0x08 */
    char pad_0c[0x20];
    Vec3 **groupPointCopies; /* 0x2c */
    char pad_30[4];
    Ov007Link ***groupLinks; /* 0x34: per group, one link per point from posPoint */
    char pad_38[4];
    Ov007PointList **pointLists; /* 0x3c: per group */
    char pad_40[0x3c];
    Vec3 restPos; /* 0x7c */
} Ov007Picker;

/* Jitters the rest offsets (dir x/y) of the groups' per-point links. Each
 * link is picked with chance percent / 100 (func_ov007_020c3ba8(1000) <
 * percent * 10) and given an offset in [-rangeX, rangeX) x [-rangeY,
 * rangeY), times scale. mode 0 sets dir to it, 1 adds it to dir, 2 adds it
 * to the point's offset from restPos. */
void func_ov007_020c56bc(char *sl, int mode, int percent, int rangeX, int rangeY, int scale) {
    Ov007Picker *self = (Ov007Picker *)sl;
    int i, j;
    int threshold, minX, spanX, minY, spanY;
    int *dir;
    int dx;
    int offset;

    i = 0;
    if (self->groupCount <= 0)
        return;

    /* offset holds percent * 10 first; threshold computed straight from
     * percent is 8 bytes longer under opt_propagation off. */
    offset = percent * 10;
    minX = -rangeX;
    minY = -rangeY;
    threshold = offset - 1;
    spanX = rangeX - minX;
    spanY = rangeY - minY;

    do {
        j = 0;
        if (self->pointLists[i]->count > 0) {
            offset = 0;
            do {
                int dy;

                if (func_ov007_020c3ba8(1000) <= threshold) {
                    dir = self->groupLinks[i][j]->dir;
                    dx = scale * (minX + func_ov007_020c3ba8(spanX));
                    dy = scale * (minY + func_ov007_020c3ba8(spanY));

                    switch (mode) {
                    case 0:
                        dir[0] = dx;
                        dir[1] = dy;
                        break;
                    case 1:
                        dir[0] += dx;
                        dir[1] += dy;
                        break;
                    case 2:
                        dir[0] = dx + (self->restPos.x -
                                       ((Vec3 *)((char *)self->groupPointCopies[i] + offset))->x);
                        dir[1] = dy + (self->restPos.y -
                                       ((Vec3 *)((char *)self->groupPointCopies[i] + offset))->y);
                        break;
                    }
                }

                offset += 0xc;
                j++;
            } while (j < self->pointLists[i]->count);
        }
        i++;
    } while (i < self->groupCount);
}
