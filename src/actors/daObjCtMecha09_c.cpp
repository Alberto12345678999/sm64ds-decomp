//cpp
/* daObjCtMecha09_c, Tick Tock Clock's moving beam (CT_MECHA09).
 *
 * Matched run ov065 0x0211bbdc..0x0211bf04: the destructor,
 * func_ov065_0211bc88, CleanupResources, Render, and Behavior.
 * InitResources at 0x0211bf04 is not complete and stays in its own file.
 * daObjCtMecha09_c_classInit at 0x0211c040 is outside this run.
 *
 * The out-of-line destructor is the key function, so this TU emits the
 * vtable and RTTI. Under `#pragma defer_codegen off` it comes out D1, D0,
 * then a D2 the cartridge has no home for, and .text follows source order.
 */

#pragma defer_codegen off

#include "daObjCtMecha09_c.h"
#include "SharedFilePtr.h"

extern "C" {
extern void Matrix4x3_FromRotationY(void* m, int angle);
extern void _ZN8dActor_c18DropShadowScaleXYZER11ShadowModelR9Matrix4x35Fix12IiES5_S5_j(
    void* a, void* sm, void* m, int f1, int f2, int f3, unsigned int j);
extern SharedFilePtr data_ov065_0211d9cc;
extern SharedFilePtr data_ov065_0211d9d4;
u16 DecIfAbove0_Short(u16 *p);
int RandomIntInternal(int *seed);
void _ZN8dActor_c9UpdatePosEP5dCc_c(void *self, void *clsn);
void _ZN10dBgActor_c21UpdateModelPosAndRotYEv(void *self);
int _ZN10dBgActor_c13IsClsnInRangeE5Fix12IiES1_(void *self, int a, int b);
void _ZN10dBgActor_c19UpdateClsnPosAndRotEv(void *self);
extern u8 data_0209f2c0;
extern s32 data_ov065_0211d520[];
extern s32 data_0209e650[];
}

// @symbol _ZN16daObjCtMecha09_cD1Ev
// @symbol _ZN16daObjCtMecha09_cD0Ev
/* The compiler writes the body: this class's vtable, then dBgActor_c's
 * inlined destructor, then the mesh collider and the model. */
daObjCtMecha09_c::~daObjCtMecha09_c()
{
}

// @symbol func_ov065_0211bc88
/* Drops the beam's shadow when it is close enough to the ground sample. */
extern "C" void func_ov065_0211bc88(char* c)
{
  int d = *(int*)(c + 0x60) - *(int*)(c + 0x330);
  if (d < 0) d = -d;
  if (d > 0x7d0000) return;
  Matrix4x3_FromRotationY(c + 0x35c, *(short*)(c + 0x8e));
  *(int*)(c + 0x380) = *(int*)(c + 0x5c) >> 3;
  *(int*)(c + 0x384) = (*(int*)(c + 0x330) + 0x1000) >> 3;
  *(int*)(c + 0x388) = *(int*)(c + 0x64) >> 3;
  _ZN8dActor_c18DropShadowScaleXYZER11ShadowModelR9Matrix4x35Fix12IiES5_S5_j(c, c + 0x334, c + 0x35c, 0x1e0000, 0x32000, 0xfa000, 0xf);
}

// @symbol _ZN16daObjCtMecha09_c16CleanupResourcesEv
int daObjCtMecha09_c::CleanupResources()
{
    if (mMeshCollider.IsEnabled())
        mMeshCollider.Disable();
    data_ov065_0211d9d4.Release();
    data_ov065_0211d9cc.Release();
    return 1;
}

// @symbol _ZN16daObjCtMecha09_c6RenderEv
int daObjCtMecha09_c::Render()
{
    mModel.Render(0);
    return 1;
}

// @symbol _ZN16daObjCtMecha09_c8BehaviorEv
/* Clock setting data_0209f2c0 picks a vertical speed from data_ov065_0211d520.
 * Setting 2 rerolls direction and a countdown; the last five frames of a leg
 * hold the beam still. Travel is clamped to [mStartPosY, mEndPosY]. */
int daObjCtMecha09_c::Behavior()
{
    char *c = (char *)this;
    u8 idx = data_0209f2c0;
    s32 v = *(signed char *)(c + 0x300 + 0x28);
    *(s32 *)(c + 0xa8) = v * data_ov065_0211d520[idx];

    if (idx == 2) {
        if (DecIfAbove0_Short((u16 *)(c + 0x32a)) == 0) {
            u16 rnd = (u32)RandomIntInternal(data_0209e650) >> 16;
            if (rnd >= 0x7fff) {
                *(signed char *)(c + 0x328) = 1;
            } else {
                *(signed char *)(c + 0x328) = -1;
            }
            int r = rnd % 6 + 1;
            *(u16 *)(c + 0x300 + 0x2a) = r * 0x1e;
            *(u16 *)(c + 0x300 + 0x2c) = *(u16 *)(c + 0x300 + 0x2a);
        } else {
            int a = *(u16 *)(c + 0x300 + 0x2c);
            int b = *(u16 *)(c + 0x300 + 0x2a);
            if (b >= a - 5) {
                *(s32 *)(c + 0xa8) = 0;
            }
        }
    }

    _ZN8dActor_c9UpdatePosEP5dCc_c(c, 0);

    {
        int y = *(s32 *)(c + 0x60);
        int lo = *(s32 *)(c + 0x320);
        int hi = *(s32 *)(c + 0x324);
        int in = 0;
        if (y >= lo)
            in = (y <= hi);
        if (in == 0) {
            *(s32 *)(c + 0x60) = (y < lo) ? lo : ((y > hi) ? hi : y);
            *(signed char *)(c + 0x328) = -*(signed char *)(c + 0x300 + 0x28);
        }
    }

    _ZN10dBgActor_c21UpdateModelPosAndRotYEv(c);
    func_ov065_0211bc88(c);
    if (_ZN10dBgActor_c13IsClsnInRangeE5Fix12IiES1_(c, 0, 0) != 0)
        _ZN10dBgActor_c19UpdateClsnPosAndRotEv(c);
    return 1;
}
