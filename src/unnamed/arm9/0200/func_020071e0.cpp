//cpp
// @symbol _ZN7Vector3D1Ev
/* Camera state. The Vector3 locals emit Vector3::~Vector3 as the next
 * .text section, the cartridge copy at 0x020072c0. func_020072c4 is a
 * different state and stays its own TU. The marker names that emitted
 * symbol; its body is the inline destructor in include/types.h.
 */
#include "types.h"
#include "math/Approach.h"

extern "C" {
extern void Vec3_RotateYAndTranslate(Vector3 *out, const Vector3 *trans, short ang,
                                     const Vector3 *add);
extern void func_02007c9c(const Vector3 *v0, const Vector3 *v1, int *outDist, short *outVertAng,
                          short *outHorzAng);
extern void func_02007c14(Vector3 *res, const Vector3 *trans, int mag, short ang, short angY);
extern int func_02007cec(void *a, void *b, int c);
extern void func_02007d0c(Vector3 *self, const Vector3 *src, int sx, int sy, int sz);
}

/* File-local views (the class headers are C++): only the fields this state
 * touches. Camera names follow include/dCamera_c.h; the player's follow
 * include/dActor_c.h (mPos spans its mPosX..mPosZ). */
typedef struct {
    u8 pad_000[0x5c];
    Vector3 mPos; /* 0x05c */
    u8 pad_068[0x26];
    s16 mAngleY; /* 0x08e */
} PlayerView;

typedef struct {
    u8 pad_000[0x80];
    Vector3 lookAt; /* 0x080 */
    Vector3 pos;    /* 0x08c */
    u8 pad_098[0x18];
    Vector3 savedLookAt; /* 0x0b0 */
    Vector3 savedPos;    /* 0x0bc */
    u8 pad_0c8[0x48];
    PlayerView *mTargetPlayer; /* 0x110 */
} CameraView;

extern "C" int func_020071e0(char *self) {
    CameraView *cam = (CameraView *)self;
    Vector3 va, vb;
    int dist;
    short ang, angY;
    /* Camera word 0x170 stays raw: other states read it as a height
       (func_020080b0), so it has no one role. Here it is a speed. */
    ApproachLinear(*((int *)(self + 0x170)), 0x5a000, 0x2800);
    {
        PlayerView *o = cam->mTargetPlayer;
        short a = (short)(o->mAngleY + 0x8000);
        const Vector3 *trans = &o->mPos;
        Vec3_RotateYAndTranslate(&va, trans, a, &cam->savedLookAt);
        Vec3_RotateYAndTranslate(&vb, trans, a, &cam->savedPos);
    }
    func_02007c9c(&va, &cam->pos, &dist, &ang, &angY);
    ApproachLinear(dist, 0, *(int *)(self + 0x170));
    func_02007c14(&cam->pos, &va, dist, ang, angY);
    func_02007cec(&cam->pos, &va, 0x28);
    func_02007d0c(&cam->lookAt, &vb, 0x800, 0xccc, 0x800);
    return 1;
}
