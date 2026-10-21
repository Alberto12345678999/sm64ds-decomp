// @symbol func_ov007_020c5188
/* recovered: shared common types, declarations from a shared header */
#include "decl_common.h"
/* recovered: shared common types */
#include "common.h"
#include "nitro/fx/fx.h"
extern void AddVec3(struct Vector3 *a, struct Vector3 *b, struct Vector3 *c);

#define DIVR(x) FX_MUL(x, -1000)

/* The 0xd0-byte touch picker func_ov007_020c690c builds; names as in that
 * file and func_ov007_020c684c, only the slots this function touches. The
 * a5 table at +0x18 (six ints, handed in pairs to func_ov007_020c7560 and
 * func_ov007_020c7b2c) and the per-group links at +0x40/+0x44 have no name
 * yet and stay raw on `sb`. */
typedef struct Ov007Picker {
    char pad_00[4];
    int mode;       /* 0x04: 2 = link mode, posPoint and link are stepped too */
    int groupCount; /* 0x08 */
    char pad_0c[0x10];
    char *params; /* 0x1c: a4 of func_ov007_020c690c; +4 is the step stride */
    char pad_20[0x14];
    int **groupLinks; /* 0x34: per group, one link per point */
    char pad_38[4];
    int **pointLists; /* 0x3c: per group */
    char pad_40[0x2c];
    int *posPoint; /* 0x6c: the Point over pos */
    Vector3 pos;   /* 0x70 */
    char pad_7c[0xc];
    Vector3 posOffset; /* 0x88: added to pos for the steps, then pos is restored */
    char pad_94[0x10];
    int link; /* 0xa4: from the anchor Point to posPoint */
    char pad_a8[0x10];
    Vector3 boundsMin; /* 0xb8: every point is clamped to [boundsMin, boundsMax] */
    Vector3 boundsMax; /* 0xc4 */
} Ov007Picker;

void func_ov007_020c5188(char *sb, int arg1)
{
    Ov007Picker *self = (Ov007Picker *)sb;
    int p;
    int oc;
    int count;
    int stride;
    int fp;
    int r8;
    int start_fp;
    int start_r8;
    int v18;
    int v1c;
    int v20;
    struct Vector3 backup;
    int *min;
    int *max;

    p = arg1;
    stride = *(int *)(self->params + 4);
    count = 1 << p;
    backup = self->pos;
    min = &self->boundsMin.x;
    max = &self->boundsMax.x;
    AddVec3(&self->posOffset, &self->pos, &self->pos);

    oc = 0;
    if (count > 0) {
        start_fp = 0;
        start_r8 = 0;
        v18 = 0;
        v1c = 0x7d0;
        v20 = 0;
        do {
            fp = start_fp;
            if (self->groupCount > 0) {
                do {
                    int *r5 = self->pointLists[fp];
                    func_ov007_020c7560(r5, ((int *)*(void **)(sb + 0x18))[0], ((int *)*(void **)(sb + 0x18))[1]);
                    if (fp >= 1) {
                        func_ov007_020c7b2c((int)((void **)*(void **)(sb + 0x40))[fp], ((int *)*(void **)(sb + 0x18))[4], ((int *)*(void **)(sb + 0x18))[5]);
                        func_ov007_020c7b2c((int)((void **)*(void **)(sb + 0x44))[fp], ((int *)*(void **)(sb + 0x18))[4], ((int *)*(void **)(sb + 0x18))[5]);
                    }
                    r8 = start_r8;
                    if (r5[1] > 0) {
                        do {
                            int *node = ((int **)r5[0])[r8];
                            func_ov007_020c7b2c(self->groupLinks[fp][r8],
                                                ((int *)*(void **)(sb + 0x18))[2],
                                                ((int *)*(void **)(sb + 0x18))[3]);
                            func_ov007_020c81a0(node, stride, p);
                            {
                                int *pt = (int *)node[0];
                                if (min[0] > pt[0]) {
                                    pt[0] = min[0];
                                    node[1] = DIVR(node[1]);
                                } else if (max[0] < pt[0]) {
                                    pt[0] = max[0];
                                    node[1] = DIVR(node[1]);
                                }
                            }
                            {
                                int *pt = (int *)node[0];
                                if (min[1] > pt[1]) {
                                    pt[1] = min[1];
                                    node[2] = DIVR(node[2]);
                                } else if (max[1] < pt[1]) {
                                    pt[1] = max[1];
                                    node[2] = DIVR(node[2]);
                                }
                            }
                            r8++;
                        } while (r8 < r5[1]);
                    }
                    fp++;
                } while (fp < self->groupCount);
            }
            if (self->mode == 2) {
                self->posPoint[6] = v18;
                self->posPoint[5] = self->posPoint[6];
                self->posPoint[4] = self->posPoint[5];
                func_ov007_020c7b2c(self->link, 0xbb8, v1c);
                func_ov007_020c831c(self->posPoint, v20, p);
            }
            oc++;
        } while (oc < count);
    }

    self->pos = backup;
}
