#include "types.h"

#define LAUNDER(p) (p)

/* AddVec3 still defines its vector as its own struct Vec3;
   declared as defined, the call casts. */
struct Vec3;
extern void AddVec3(struct Vec3 *a, struct Vec3 *b, struct Vec3 *c);

/* Only the fields this function touches are named. */
typedef struct {
    int pad_00;
    int mode; /* 0x04 */
    u8 pad_08[0x34];
    int **tab; /* 0x3c */
    u8 pad_40[0x18];
    int i;          /* 0x58 */
    int j;          /* 0x5c */
    Vector3 offset; /* 0x60 */
    int pad_6c;
    Vector3 pos; /* 0x70 */
    u8 pad_7c[0x1c];
    Vector3 pos2; /* 0x98 */
    u8 pad_a4[0x14];
    int hi[2]; /* 0xb8 */
    int pad_c0;
    int lo[2]; /* 0xc4 */
} Self;

void func_ov007_020c5948(char *self, Vector3 *src) {
    Self *s = (Self *)self;
    int i;
    int j;
    int **tab;
    int *obj;
    int *vec;
    int mode;
    int *dst;
    int *hi;
    int *lo;

    i = s->i;
    if (i == -1)
        return;
    j = s->j;
    if (j == -1)
        return;

    tab = s->tab;
    obj = (*(int ***)tab[i])[j];
    vec = (int *)obj[0];

    obj[6] = 0;
    obj[5] = obj[6];
    obj[4] = obj[5];
    obj[3] = obj[4];
    obj[2] = obj[3];
    obj[1] = obj[2];

    vec[0] = src->x;
    vec[1] = src->y;

    mode = s->mode;
    switch (mode) {
    case 0:
        s->pos = *src;
        break;
    case 1:
        dst = (int *)(int)LAUNDER(&s->pos);
        hi = (int *)(int)LAUNDER(s->hi);
        lo = (int *)(int)LAUNDER(s->lo);
        AddVec3((struct Vec3 *)src, (struct Vec3 *)&s->offset, (struct Vec3 *)dst);
        if (hi[0] > dst[0])
            dst[0] = hi[0];
        if (lo[0] < dst[0])
            dst[0] = lo[0];
        if (hi[1] > dst[1])
            dst[1] = hi[1];
        if (lo[1] < dst[1])
            dst[1] = lo[1];
        break;
    case 2:
        s->pos2 = *src;
        break;
    }
}
