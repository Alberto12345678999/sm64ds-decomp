//cpp
#include "types.h"
#include "cstd.h"
#include "dBgCh_Gnd.h"

extern "C" {

#include "nitro/fx/fx.h"
typedef struct Entry3 { int a, b, c; } Entry3;

extern int LenVec3(Vector3 *v);
extern void Vec3_Sub(Vector3 *out, Vector3 *a, Vector3 *b);
extern void Vec3_MulScalarInPlace(int *v, int s);
extern void Vec3_Add(Vector3 *out, Vector3 *a, Vector3 *b);
extern int func_020092c4(int self, Vector3 *out, Vector3 *target);
extern short Vec3_HorzAngle(const Vector3 *a, const Vector3 *b);

extern Entry3 data_02086f58[];

/* File-local view of dCamera_c (include/dCamera_c.h is C++): the fields this
 * helper touches. */
typedef struct {
    char pad_000[0x80];
    Vector3 lookAt; /* 0x080 */
    Vector3 pos;    /* 0x08c */
    /* func_020089f8 copies mTargetPlayer->mPos here every frame. */
    Vector3 mTargetPos; /* 0x098 */
    char pad_0a4[0xb0];
    int mFlags; /* 0x154 */
    char pad_158[0x24];
    short mAngleY; /* 0x17c */
} CameraView;

void func_0200b798(char *self, short *a1, int arg2)
{
    CameraView *cam = (CameraView *)self;
    Vector3 pos;
    Vector3 v1;
    Vector3 v2;
    Vector3 v3;
    Vector3 v4;
    int idx;
    Entry3 *e;
    int len;
    int limit;
    int scale;
    int c;
    int sum;

    idx = *((unsigned char *)a1 + 1);
    if (idx == 0xff) idx = 0;

    e = &data_02086f58[idx];
    {
        int tz = a1[3] << 12;
        int ty = a1[2] << 12;
        int tx = a1[1] << 12;
        pos.x = tx;
        pos.y = ty;
        pos.z = tz;
    }

    dBgCh_Gnd ray;
    ray.SetObjAndPos(pos, 0);
    if (ray.DetectClsn() != 0) {
        pos.y -= ray.clsnY;
    }

    sum = arg2 + pos.y;
    {
        int sz = cam->mTargetPos.z;
        int sx = cam->mTargetPos.x;
        int dz = sz - pos.z;
        int dx = sx - pos.x;
        int dy = sum - pos.y;
        v1.x = dx;
        v1.y = dy;
        v1.z = dz;
    }
    c = e->c;
    v2.y = sum;
    v2.x = pos.x + FX_MUL(v1.x, c);
    v2.z = pos.z + FX_MUL(v1.z, c);

    len = LenVec3(&v1);
    if (len < 0x220000) {
        v2.y += 0x220000 - len;
    }

    Vec3_Sub(&v3, &v2, &cam->lookAt);
    v1.x = v3.x;
    v1.y = v3.y;
    v1.z = v3.z;
    len = LenVec3(&v1);

    limit = e->a;
    if (cam->mFlags & 0xc00)
        limit = e->b;

    if (len > limit) {
        scale = cstd::fdiv(limit, len);
        Vec3_MulScalarInPlace((int *)&v1, scale);
        Vec3_Add(&v4, &cam->lookAt, &v1);
        v2.x = v4.x;
        v2.y = v4.y;
        v2.z = v4.z;
    }

    if (cam->mFlags & 4) {
        cam->pos.x = v2.x;
        cam->pos.y = v2.y;
        cam->pos.z = v2.z;
    } else {
        func_020092c4((int)self, &cam->pos, &v2);
    }

    cam->mAngleY = Vec3_HorzAngle(&cam->lookAt, &cam->pos);
}
}
