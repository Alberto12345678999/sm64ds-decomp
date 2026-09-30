//cpp
/**
 * Endless BGM / fog controller (registry profile MUGEN_BGM).
 *
 * param1 == 1 steers data_0208e434 from the rotated offset; otherwise it
 * drives Fog depth/color from the rotated offset, star count and
 * data_0209caa0[0x41], then keeps Sound sub 0x2e playing while
 * func_ov100_02144f84 gates mHorzSpeed.
 *
 * This TU owns text only: ov002 delinks no .data here, so the _ZTV / _ZTI /
 * _ZTS group the class names is compiler-only output, compared against the
 * cartridge's own copies at ov002 0x0210b584 / 0x0210b544 / 0x0210b550.
 *
 * deslop
 * Leftover: Fog::Init, Sound::PlaySub, Vec3_Sub, Vec3_RotateYAndTranslate,
 *   AngleDiff and NumStars stay spelled as mangled/extern-C free functions.
 *   Fog::Init takes Fix12<int> by value; a real method call homes the
 *   argument and size-DIFFs the caller (notes/mwccarm-codegen.md 6az).
 * Leftover: func_ov002_020f1c20 keeps its C-ABI cartridge name. It is this
 *   TU's own fog accessor (returns sMugenFog when sMugenArea matches),
 *   not a vtable slot.
 * Leftover: data_ov002_02110af0 / 02110af4 / 02110af8 are this TU's stored
 *   area, angle and Fog instance; data_0209f250 / 0209f394 / 020a0ebc /
 *   0209caa0 / 0209f318 / 0208e434 / 02092120 are arm9 scene state this TU
 *   does not own.
 * Leftover: g_profile_MUGEN_BGM lives outside this TU.
 */

/* Includes: union of the legacy files'. decl_common.h carries the sMugen
 * area/angle/fog externs and the mangled ABI seam used below. */
#include "daMugenBGM_c.h"
#include "types.h"
#include "decl_common.h"

extern "C" {
extern signed char data_ov002_02110af0;
extern signed char data_02092120;
extern void *data_ov002_02110af8;
void Vec3_Sub(int* out, int* a, int* b);
void Vec3_RotateYAndTranslate(int* out, int* in, short angle, int* src);
u32 NumStars(void);
int AngleDiff(int a, int b);
void _ZN3Fog4InitEt5Fix12IiES1_(void* thiz, unsigned short a, int b, int d);
int func_ov100_02144f84(void);
int _ZN5Sound7PlaySubEjjj5Fix12IiEb(u32 a, u32 b, u32 c, int d, int e);
extern u8 data_0209f250;
extern char* data_0209f394[];
extern int data_020a0ebc[];
extern u8 data_0209caa0[];
extern char* data_0209f318;
void* _Znwj(unsigned int);
}

extern int _ZTV12daMugenBGM_c[];
/* -------------------------------------------------------------------------- */
/* ROM ordinal 8 -- daMugenBGM_c_classInit, 0x020f1f40, size 0x30. Folded
   factory (S2): hand-rolled fBase_cnwEj + dActor_c C2 + vptr punch is
   `return new daMugenBGM_c`. Inherits fBase_c::operator new. */
/* -------------------------------------------------------------------------- */
// @symbol daMugenBGM_c_classInit
extern "C" daMugenBGM_c *daMugenBGM_c_classInit(void)
{
    return new daMugenBGM_c;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 7 -- _ZN12daMugenBGM_c13InitResourcesEv, 0x020f1eb4, size 0x8c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN12daMugenBGM_c13InitResourcesEv
int daMugenBGM_c::InitResources()
{
    void* p;
    /* The param1 mask reads through a const view of `this`: `param1 &= 0xf`
       makes mwcc CSE the +8 field address into r1 (add r1,r4,#8 / ldr r0,[r1] /
       str r0,[r1]) and the function grows a word; the cartridge re-issues
       ldr/str [r4,#8]. Same lever as dScMgPachinko2_c::OnYoshiTryEat. */
    const daMugenBGM_c* ro = this;
    param1 = ro->param1 & 0xf;
    if (param1 != 1) {
        data_ov002_02110af4 = mAngleY;
        p = _Znwj(0x28);
        data_ov002_02110af8 = p;
        if (p != 0) {
            _ZN3Fog4InitEt5Fix12IiES1_(p, 0, 0x700, 0xd00);
        }
        data_ov002_02110af0 = mAreaId;
    }
    mAreaId = -1;
    mAngleY = -mAngleY;
    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 6 -- _ZN12daMugenBGM_c8BehaviorEv, 0x020f1c64, size 0x250 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN12daMugenBGM_c8BehaviorEv
int daMugenBGM_c::Behavior()
{
    int vol;
    int flag;
    int depth;
    int color;
    int diff[3];
    int rotated[3];

    Vec3_Sub(diff, (int*)(data_0209f394[data_0209f250] + 0x5c), (int*)&mPosX);
    Vec3_RotateYAndTranslate(rotated, data_020a0ebc, mAngleY, diff);

    if (param1 == 1) {
        int z = rotated[2];
        int x = rotated[0];
        int az = (z < 0) ? -z : z;
        if (x < 0) x = -x;
        if (x < 0x320000) {
            int y = rotated[1];
            if (y > -0x12c000 && y < 0x5dc000 && az > 0x32000 && az < 0xc8000)
                data_0208e434 = (z < 0) ? 2 : -1;
        }
        return 1;
    }

    depth = 0xffff;
    vol = 0x7f;
    color = depth;
    flag = 0;

    if (NumStars() < 0x50 || data_0209caa0[0x41] != 0) {
        int x = rotated[0];
        color = 0xd00;
        if (x < 0) x = -x;
        if (x < 0x200000) {
            int y = rotated[1];
            if (y > -0x32000 && y < 0x1000000 && rotated[2] < 0) {
                int d;
                vol = 0;
                flag = 0x7f;
                d = AngleDiff(mAngleY, *(s16*)(data_0209f318 + 0x17c)) - 0x2000;
                if (d < 0)
                    d = 0;
                else if (d > 0x4000)
                    d = 0x4000;
                depth = (int)(((s64)rotated[2] * (0x40 - (d >> 8)) + 0x800) >> 12) + 0xffff;
                if (depth < 0x700)
                    depth = 0x700;
            }
        }
    }

    {
        void* fog = data_ov002_02110af8;
        if (fog != 0)
            _ZN3Fog4InitEt5Fix12IiES1_(fog, 0, (u16)depth, color);
    }

    if (mHorzSpeed == 0) {
        if (func_ov100_02144f84() == 0)
            return 1;
        mHorzSpeed = 1;
    }

    if (_ZN5Sound7PlaySubEjjj5Fix12IiEb(0x2e, vol, flag, 0x1451, 0) != 0) {
        if (flag == 0)
            mHorzSpeed = 0;
    }
    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 5 -- _ZN12daMugenBGM_c6RenderEv, 0x020f1c5c, size 0x8 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN12daMugenBGM_c6RenderEv
int daMugenBGM_c::Render()
{
    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 4 -- _ZN12daMugenBGM_c16OnPendingDestroyEv, 0x020f1c58, size 0x4 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN12daMugenBGM_c16OnPendingDestroyEv
void daMugenBGM_c::OnPendingDestroy()
{
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 3 -- _ZN12daMugenBGM_c16CleanupResourcesEv, 0x020f1c50, size 0x8 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN12daMugenBGM_c16CleanupResourcesEv
int daMugenBGM_c::CleanupResources()
{
    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 2 -- func_ov002_020f1c20, 0x020f1c20, size 0x30 */
/* -------------------------------------------------------------------------- */
// @symbol func_ov002_020f1c20
extern "C" {  /* .c-derived member: C linkage for the whole block */
int func_ov002_020f1c20(void)
{
    if (data_ov002_02110af0 == data_02092120)
        return (int)data_ov002_02110af8;
    return 0;
}
}

/* -------------------------------------------------------------------------- */
/* ROM ordinals 0-1 -- D1 0x020f1bc4 then D0 0x020f1be8. Single out-of-line
   definition emits both variants; the homeless D2 is deadstripped.
   Same arrangement as src/actors/daObjBk_Botaosi_c.cpp. */
/* -------------------------------------------------------------------------- */
// @symbol _ZN12daMugenBGM_cD1Ev
// @symbol _ZN12daMugenBGM_cD0Ev
daMugenBGM_c::~daMugenBGM_c()
{
}
