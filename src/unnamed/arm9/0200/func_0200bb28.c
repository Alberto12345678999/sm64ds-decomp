#include "types.h"
// @symbol func_0200bb28
/* recovered: shared common types, declarations from a shared header */
#include "decl_common.h"
/* recovered: shared common types */
#include "common.h"
#include "PlayerInput.h"
#include "nitro/fx/fx.h"
extern u16 data_0209f49c[];
extern u16 data_0209f49e[];

extern u32 func_02012790(u32 a);
extern s32 ApproachAngle(s16* cur, s16 target, s32 div, s32 band, s32 step);
extern u16 DecIfAbove0_Short(u16* p);
extern int _Z14ApproachLinearRsss(short *value, short target, short step);
extern void Vec3_RotateYAndTranslate(s32* out, s32* in, s16 ang, s32* src);
extern s32 Math_Function_0203b14c(s32* p, s32 tgt, s32 rate, s32 lim, s32 step);
extern s32 _Z14ApproachLinearR7Vector3RKS_5Fix12IiE(s32* v, s32* t, s32 rate);

/* File-local views (the class headers are C++): only the fields this state
 * touches. Camera names follow include/dCamera_c.h; the player's follow
 * include/dActor_c.h. */
typedef struct {
    u8 pad_000[0x8e];
    s16 mAngleY; /* 0x08e */
} PlayerView;

/* GetViewObj's 0xe-byte record, as d_camera.cpp's CamViewObj reads it. A
   type-2 object supplies a yaw at +0xa; byte 1 zero means jump to it at once
   (here: snap mEasedAngleY and set mFlags bit 4, which places pos directly). */
typedef struct {
    u8 type;      /* 0x0 */
    u8 p1;        /* 0x1 */
    s16 x, y, z;  /* 0x2 */
    u8 pad_8[2];
    s16 angleY;   /* 0xa */
} CamViewObj;

typedef struct {
    u8 pad_000[0x80];
    struct Vector3 lookAt; /* 0x080 */
    struct Vector3 pos;    /* 0x08c */
    /* func_020089f8 copies mTargetPlayer->mPos here every frame. */
    struct Vector3 mTargetPos; /* 0x098 */
    u8 pad_0a4[0x6c];
    PlayerView *mTargetPlayer; /* 0x110 */
    u8 pad_114[0x30];
    char *mViewObj; /* 0x144 */
    u8 pad_148[0xc];
    u32 mFlags; /* 0x154 */
    u8 pad_158[0xc];
    u32 mTurnButtons; /* 0x164 */
    u8 pad_168[0x14];
    s16 mAngleY; /* 0x17c */
    u8 pad_17e[0x2];
    s16 mEasedAngleY;     /* 0x180 */
    s16 mBaseAngleY;      /* 0x182 */
    s16 mBaseAngleOffset; /* 0x184 */
    u8 pad_186[0x10];
    /* A countdown the states arm and run down: here the delay before a held
       turn input repeats. */
    u16 mStateTimer; /* 0x196 */
    u8 pad_198[0x6];
    s16 mBehindAngleY; /* 0x19e */
    u16 mRecentering;  /* 0x1a0 */
} CameraView;

#pragma opt_common_subs off
void func_0200bb28(char* c, char* a1)
{
    CameraView *cam = (CameraView *)c;
    CamViewObj *view = (CamViewObj *)a1;
    s32 flag4000;
    s32 sp_speed;
    struct Vector3 vsrc;
    struct Vector3 vin;
    struct Vector3 vout;
    s32* tbl;
    s32 comp;
    s32 m;

    cam->mFlags |= 0x1000;

    m = gActivePlayerSlot * 0x18;
    flag4000 = *(u16*)((char*)data_0209f49c + m) & 0x4000;

    if (flag4000 != 0 || cam->mRecentering != 0) {
        if (*(u16*)((char*)data_0209f49e + m) & 0x4000) {
            func_02012790(0x1a);
        }
        if (flag4000 != 0) {
            cam->mBehindAngleY = (s16)(cam->mTargetPlayer->mAngleY + 0x8000);
        }
        cam->mRecentering = (ApproachAngle(&cam->mEasedAngleY, cam->mBehindAngleY, 4, 0x400, 0x100) != 0);
        cam->mBaseAngleOffset = (s16)(cam->mEasedAngleY - cam->mBaseAngleY);
        cam->mBaseAngleOffset = (s16)((cam->mBaseAngleOffset + 0x1000) & -0x2000);
        cam->mFlags |= 0x60;
    } else {
        if (a1 != 0) {
            if (view->type == 2 && a1 != cam->mViewObj) {
                cam->mBaseAngleY = (s16)(view->angleY + 0x8000);
                if (view->p1 == 0) {
                    cam->mEasedAngleY = cam->mBaseAngleY;
                    cam->mFlags |= 4;
                }
                cam->mBaseAngleOffset = 0;
                cam->mViewObj = a1;
            }
        } else {
            cam->mViewObj = 0;
        }
        if (!(cam->mFlags & 0x60)) {
            s32 m2;
            s32 f1;
            DecIfAbove0_Short(&cam->mStateTimer);
            m2 = gActivePlayerSlot * 0x18;
            f1 = *(u16*)((char*)data_0209f49c + m2) & 0x300;
            if (f1 != 0) {
                s32 f2 = *(u16*)((char*)data_0209f49e + m2) & 0x300;
                if (f2 != 0) {
                    cam->mTurnButtons = f2;
                } else if (!(cam->mTurnButtons & f1)) {
                    f2 = f1;
                    cam->mTurnButtons = f1;
                }
                if (f2 != 0 || cam->mStateTimer == 0) {
                    u32 dir = cam->mTurnButtons;
                    if (dir & 0x200) {
                        cam->mBaseAngleOffset -= 0x2000;
                        cam->mFlags |= 0x20;
                    } else if (dir & 0x100) {
                        cam->mBaseAngleOffset += 0x2000;
                        cam->mFlags |= 0x40;
                    }
                    cam->mStateTimer = 0x14;
                }
            }
        }
        _Z14ApproachLinearRsss(&cam->mEasedAngleY, (s16)(cam->mBaseAngleY + cam->mBaseAngleOffset), 0x800);
    }

    tbl = (cam->mFlags & 2) ? data_02086d50 : data_02086cc8;
    sp_speed = tbl[1];
    func_0200c9e0(c, &sp_speed, &sp_speed);
    comp = FX_MUL(tbl[0], sp_speed);
    vsrc.x = 0;
    vsrc.z = 0;
    vsrc.y = comp;
    {
        s32 t0 = tbl[0];
        vsrc.z = _ZN4cstd4sqrtEy((s64)t0 * t0 - (s64)comp * comp);
    }
    {
        s32 tz = cam->mTargetPos.z;
        s32 ty = cam->lookAt.y;
        s32 tx = cam->mTargetPos.x;
        vin.x = tx;
        vin.y = ty;
        vin.z = tz;
    }
    Vec3_RotateYAndTranslate(&vout.x, &vin.x, cam->mEasedAngleY, &vsrc.x);
    if (cam->mFlags & 4) {
        cam->pos.x = vout.x;
        cam->pos.y = vout.y;
        cam->pos.z = vout.z;
    }
    Math_Function_0203b14c(&cam->pos.y, vout.y, 0x300, 0x18000, 0x100);
    vout.y = cam->pos.y;
    if (_Z14ApproachLinearR7Vector3RKS_5Fix12IiE(&cam->pos.x, &vout.x,
                                                 flag4000 != 0 ? 0xc0000 : 0x40000) != 0 &&
        flag4000 == 0) {
        cam->mFlags &= ~0x60;
    }
    cam->mAngleY = cam->mEasedAngleY;
}