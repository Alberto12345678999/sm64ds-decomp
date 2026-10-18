#include "common.h"
extern void *data_ov007_02104bd8;
extern void func_ov007_020bc47c(void *thiz);
extern int _ZN4cstd3divEii(int a, int b);
extern int InvMat4x3(int *src, int *dst); /* as defined */
extern void MulVec3Mat4x3(Vector3 *in, Matrix4x3 *mat, Vector3 *out);

/* Only the fields this function touches are named. */
typedef struct {
    u8 pad_00[0x44];
    Matrix4x3 mtx; /* 0x44 */
} Self;

typedef struct {
    u8 pad_00[0x34];
    Vector3 pos; /* 0x34 */
    u8 pad_40[0xc];
    short period; /* 0x4c */
    u8 pad_4e[0x46];
    int f94; /* 0x94 */
} Target;

void func_ov007_020bfbdc(void *self)
{
    Self *s = (Self *)self;
    Target *o = (Target *)((void **)data_ov007_02104bd8)[1];
    Vector3 vec;
    Matrix4x3 mat;

    func_ov007_020bc47c(o);
    o->period = (short)_ZN4cstd3divEii(0x5a0000, 0x168);
    o->f94 = 0;

    vec.y = 0;
    vec.x = 0;
    vec.z = 0xffffef9c;
    InvMat4x3((int *)&s->mtx, (int *)&mat);
    MulVec3Mat4x3(&vec, &mat, &o->pos);
}
