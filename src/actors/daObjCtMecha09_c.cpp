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

/* Fix12-by-value calls keep their raw ABI declarations (header forms take
 * Fix12<int> by value, which cannot be called with literals; see
 * include/dActor_c.h). */
extern "C" {
extern void Matrix4x3_FromRotationY(Matrix4x3 *matrix, int angle);
extern void _ZN8dActor_c18DropShadowScaleXYZER11ShadowModelR9Matrix4x35Fix12IiES5_S5_j(
    dActor_c *actor, ShadowModel *shadow, Matrix4x3 *matrix,
    int scaleX, int scaleY, int scaleZ, u32 opacity);
extern int _ZN10dBgActor_c13IsClsnInRangeE5Fix12IiES1_(dBgActor_c *self, int a, int b);
extern SharedFilePtr data_ov065_0211d9cc;
extern SharedFilePtr data_ov065_0211d9d4;
extern u16 DecIfAbove0_Short(u16 *p);
extern int RandomIntInternal(int *seed);
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
extern "C" void func_ov065_0211bc88(daObjCtMecha09_c *self)
{
    int d = self->mPosY - self->mGroundY;
    if (d < 0) d = -d;
    if (d > 0x7d0000) return;
    Matrix4x3_FromRotationY(&self->mShadowMat, self->mAngleY);
    self->mShadowMat.t.x = self->mPosX >> 3;
    self->mShadowMat.t.y = (self->mGroundY + 0x1000) >> 3;
    self->mShadowMat.t.z = self->mPosZ >> 3;
    _ZN8dActor_c18DropShadowScaleXYZER11ShadowModelR9Matrix4x35Fix12IiES5_S5_j(
        self, &self->mShadowModel, &self->mShadowMat, 0x1e0000, 0x32000, 0xfa000, 0xf);
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
    u8 setting = data_0209f2c0;
    mVertSpeed = mDirection * data_ov065_0211d520[setting];

    if (setting == 2) {
        if (DecIfAbove0_Short(&mLegTimer) == 0) {
            u16 rnd = (u32)RandomIntInternal(data_0209e650) >> 16;
            if (rnd >= 0x7fff)
                mDirection = 1;
            else
                mDirection = -1;
            mLegTimer = (rnd % 6 + 1) * 30;
            mLegLength = mLegTimer;
        } else if (mLegTimer >= mLegLength - 5) {
            mVertSpeed = 0;
        }
    }

    UpdatePos(0);

    {
        int y = mPosY;
        int lo = mStartPosY;
        int hi = mEndPosY;
        int in = 0;
        if (y >= lo)
            in = (y <= hi);
        if (in == 0) {
            mPosY = (y < lo) ? lo : ((y > hi) ? hi : y);
            mDirection = -mDirection;
        }
    }

    UpdateModelPosAndRotY();
    func_ov065_0211bc88(this);
    if (_ZN10dBgActor_c13IsClsnInRangeE5Fix12IiES1_(this, 0, 0) != 0)
        UpdateClsnPosAndRot();
    return 1;
}
