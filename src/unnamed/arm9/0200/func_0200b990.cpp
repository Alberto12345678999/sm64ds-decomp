//cpp
#include "types.h"
#include "cstd.h"
#include "dBgCh_Lin.h"
#include "math/Approach.h"

extern "C" {

#include "nitro/fx/fx.h"

extern s16 Vec3_HorzAngle(const Vector3 *a, const Vector3 *b);
extern void func_0200897c(char *self, dBgCh_Lin *rc);
extern int AngleDiff(int a, int b);
extern signed char data_0209f2f8;

/* File-local views (the class headers are C++): only the fields this helper
 * touches. Camera names follow include/dCamera_c.h; the player's follow
 * include/dActor_c.h. */
typedef struct {
    u8 pad_000[0x8e];
    s16 mAngleY; /* 0x08e */
} PlayerView;

typedef struct {
    u8 pad_000[0x80];
    Vector3 lookAt; /* 0x080 */
    u8 pad_08c[0x84];
    PlayerView *mTargetPlayer; /* 0x110 */
    u8 pad_114[0x68];
    s16 mAngleY; /* 0x17c */
} CameraView;

void func_0200b990(char *self, char *arg1, int arg2)
{
    CameraView *cam = (CameraView *)self;
    Vector3 v;
    s16 angle;
    u8 b0, b1;
    int step;
    int rate;

    {
        int sz = (int)(*(s16 *)(arg1 + 6)) << 12;
        int sy = (int)(*(s16 *)(arg1 + 4)) << 12;
        int sx = (int)(*(s16 *)(arg1 + 2)) << 12;
        v.x = sx;
        v.y = sy;
        v.z = sz;
    }
    angle = Vec3_HorzAngle(&v, &cam->lookAt);

    rate = 8;
    b0 = *(u8 *)(arg1 + 0);
    if (b0 == 0) {
        b1 = *(u8 *)(arg1 + 1);
        if (b1 == 0xff) {
            signed char zone = data_0209f2f8;
            if (zone != 0x16 && zone != 0xa && zone != 0x10) {
                dBgCh_Lin rc;
                Vector3 lineB;
                func_0200897c(self, &rc);
                lineB.y = cam->lookAt.y;
                lineB.x = v.x;
                lineB.z = v.z;
                rc.SetObjAndLine(cam->lookAt, lineB, 0);
                if (rc.DetectClsn() != 0) {
                    Vector3 normal;
                    s16 a2;
                    rc.surface.CopyNormalTo(normal);
                    a2 = cstd::atan2(normal.x, normal.z);
                    if (AngleDiff(a2, angle) < 0x1800) angle = a2;
                }
            }
            step = 0x2000;
        } else {
            step = 0;
            rate = (data_0209f2f8 == 0x2d) ? 0x12 : 0xf;
        }
    } else {
        step = 0x6800;
    }

    {
        PlayerView *ptr = cam->mTargetPlayer;
        s16 target = ptr->mAngleY;
        s16 diff = (s16)(angle - target);
        if (diff < 0) {
            angle -= step;
        } else {
            angle += step;
        }
    }

    {
        int fixmul = FX_MUL(arg2, rate);
        ApproachLinear(cam->mAngleY, angle, (s16)fixmul);
    }
}
}
