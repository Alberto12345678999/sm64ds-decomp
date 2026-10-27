//cpp
#include "types.h"
#include "cstd.h"
#include "dBgCh_Lin.h"
#include "math/CalcLib.h"

extern "C" {

extern int func_ov002_020ca270(char* p);
extern void Vec3_Sub(Vector3 *out, Vector3 *a, Vector3 *b);
extern int LenVec3(Vector3 *v);
extern void Vec3_MulScalarInPlace(Vector3 *v, int s);
extern void Vec3_Add(Vector3 *out, Vector3 *a, Vector3 *b);
extern void func_0200897c(char* self, dBgCh_Lin* rc);
extern int DotVec3(const Vector3 *a, const Vector3 *b);
extern int AngleDiff(int a, int b);

/* File-local view of dCamera_c (include/dCamera_c.h is C++): the fields this
 * collision step touches, with the header's names. */
typedef struct {
    u8 pad_000[0x80];
    Vector3 lookAt; /* 0x080 */
    Vector3 pos;    /* 0x08c */
    /* func_020089f8 copies mTargetPlayer->mPos here every frame. */
    Vector3 mTargetPos; /* 0x098 */
    u8 pad_0a4[0x30];
    /* Last frame's pos (Behavior copies it here before moving). */
    Vector3 mPrevPos; /* 0x0d4 */
    /* The wall func_02009e70's line last hit: this function ignores a new
       hit whose normal faces the same way as mWallNormal or which lies
       within 0x80000 of mWallPos. */
    Vector3 mWallPos;    /* 0x0e0 */
    Vector3 mWallNormal; /* 0x0ec */
    u8 pad_0f8[0x18];
    char *mTargetPlayer; /* 0x110 */
    u8 pad_114[0x40];
    u32 mFlags; /* 0x154 */
    u8 pad_158[0x2e];
    /* The yaw func_020091f8 eases mAngleY toward. */
    s16 mTargetAngleY; /* 0x186 */
    u8 pad_188[0x18];
    /* Nonzero while the camera swings to the yaw behind the player. */
    u16 mRecentering; /* 0x1a0 */
    u8 pad_1a2[4];
    /* Set when a new mTargetAngleY is chosen, cleared on arrival; the
       push-in below clears it too. */
    u8 mTurningToTarget; /* 0x1a6 */
} CameraView;

#ifndef SM64DS_PLATFORM_PC
typedef char CameraView_turning_must_be_at_0x1a6[(int)&((CameraView *)0)->mTurningToTarget == 0x1a6
                                                     ? 1
                                                     : -1];
#endif

/* The target player's actor ID, as include/dActor_c.h's C view places it. */
typedef struct {
    u8 pad_000[0xc];
    u16 actorID; /* 0x00c */
} ActorView;

int func_02008cb4(char* c)
{
    CameraView *cam = (CameraView *)c;
    Vector3 v0;
    Vector3 dir1;
    Vector3 end1;
    Vector3 n1;
    Vector3 dir2;
    Vector3 end2;
    Vector3 n2;
    Vector3 diff;
    int vy;
    int vz;
    int vx;
    int scale;
    int len;
    int d;

    {
        char *p = cam->mTargetPlayer;
        int b = ((ActorView *)p)->actorID;
        b = b == 0xbf;
        if (b != false) {
            if (func_ov002_020ca270(p) != 0)
                return 0;
        }
    }

    scale = 0x200;
    if (cam->mFlags & 0x40200) {
        vz = cam->mTargetPos.z;
        vy = cam->mTargetPos.y + 0x82500;
        vx = cam->mTargetPos.x;
        v0.x = vx;
        v0.y = vy;
        v0.z = vz;
        Vec3_Sub(&dir1, &cam->pos, &v0);
        len = LenVec3(&dir1);
        if (len != 0) {
            Vec3_MulScalarInPlace(&dir1, cstd::fdiv(0x100000, len));
            Vec3_Add(&end1, &cam->pos, &dir1);
            dBgCh_Lin rc1;
            func_0200897c(c, &rc1);
            rc1.SetObjAndLine(end1, v0, 0);
            if (rc1.DetectClsn() != 0) {
                rc1.surface.CopyNormalTo(n1);
                if (DotVec3(&cam->mWallNormal, &n1) > 0) {
                    cam->mFlags &= ~0x80000;
                    return 0;
                }
                Vector3 cp1 = rc1.GetClsnPos();
                if (Vec3_Dist(&cam->mWallPos, &cp1) < 0x80000) {
                    cam->mFlags &= ~0x80000;
                    return 0;
                }
                {
                    u32 f = cam->mFlags;
                    if ((f & 0x40000) && cam->mTurningToTarget != 0 && !(f & 0x80100)) {
                        int a = cstd::atan2(n1.x, n1.z);
                        if (AngleDiff(a, cstd::atan2(cam->mWallNormal.x, cam->mWallNormal.z)) >
                            0x6000) {
                            cam->mTargetAngleY += 0x8000;
                            cam->mFlags |= 0x80000;
                        }
                    }
                }
            }
        }
        scale = 0x1000;
    }

    {
        u32 f = cam->mFlags;
        if (f & 0x80100) {
            vz = cam->mTargetPos.z;
            vy = (f & 0x100) ? cam->pos.y : 0x82500 + cam->mTargetPos.y;
            vx = cam->mTargetPos.x;
            v0.x = vx;
            v0.y = vy;
            v0.z = vz;
        } else {
            scale = 0x1000;
            v0.x = cam->mPrevPos.x;
            v0.y = cam->mPrevPos.y;
            v0.z = cam->mPrevPos.z;
        }
    }

    Vec3_Sub(&dir2, &cam->pos, &v0);
    len = LenVec3(&dir2);
    if (len == 0) {
        cam->mFlags &= ~0x80000;
        return 0;
    }
    Vec3_MulScalarInPlace(&dir2, cstd::fdiv(0x60000, len));
    Vec3_Add(&end2, &cam->pos, &dir2);
    dBgCh_Lin rc2;
    func_0200897c(c, &rc2);
    rc2.SetObjAndLine(v0, end2, 0);
    if (rc2.DetectClsn() == 0) {
        cam->mFlags &= ~0x80000;
        return 0;
    }
    if (!(cam->mFlags & 0x80100)) {
        int t;
        rc2.surface.CopyNormalTo(n2);
        t = n2.y;
        if (t < 0) t = -t;
        if (t > 0xb50) {
            return 0;
        }
    }
    d = Vec3_Dist(&cam->pos, &cam->lookAt);
    Vec3_MulScalarInPlace(&dir2, scale);
    Vector3 cp2 = rc2.GetClsnPos();
    Vector3 np;
    Vec3_Sub(&np, &cp2, &dir2);
    cam->pos.x = np.x;
    cam->pos.y = np.y;
    cam->pos.z = np.z;
    Vec3_Sub(&diff, &cam->pos, &cam->lookAt);
    if (LenVec3(&diff) >= d) {
        Vec3_MulScalarInPlace(&diff, cstd::fdiv(d, LenVec3(&diff)));
        Vector3 cl;
        Vec3_Add(&cl, &cam->lookAt, &diff);
        cam->pos.x = cl.x;
        cam->pos.y = cl.y;
        cam->pos.z = cl.z;
    }
    if (cam->mTurningToTarget != 0 || cam->mRecentering != 0) {
        cam->mTurningToTarget = 0;
        cam->mRecentering = 0;
    }
    cam->mFlags &= ~0x80000;
    return 1;
}
}
