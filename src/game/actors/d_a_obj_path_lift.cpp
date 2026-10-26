//cpp
/* ov100/daObjPathLift_c -- PATH_LIFT (31).
 *
 * SM64DS proves daObjPathLift_c through RTTI (_ZTI/_ZTS at ov100
 * 0x02148538/0x02148544), the PATH_LIFT registry profile, and the factory's
 * allocation/vptr shape. ov100 is mixed; this is the path lift, not STAR_DOOR
 * / daStarGate_c. Historical project alias: PathLift.
 *
 * mwccarm emits ordinary function sections in reverse source order.
 * classInit is this TU's highest ROM address (0x02147328), so it comes
 * first, ahead of InitResources. The inline destructor declared in
 * daObjPathLift_c emits the retail D1/D0 pair itself and emits no leaf D2
 * body.
 *
 * deslop
 * classInit is `return new daObjPathLift_c()`. dPathLiftActor_c's implicit
 *   constructor inlines into it (dBgActor_c C2, the base vptr, mModels,
 *   mPath), then the leaf vptr and mShadowModel, which is the ROM's
 *   sequence. The emitted dBgActor_c and dPathLiftActor_c D2 helpers have
 *   no ROM home and are deadstripped in the manifest.
 * Leftover: data_0209f2f8 == 13 is a level-ID check (the current
 *   level); data_0209f2d8 == 1 is the mode-1 check used tree-wide.
 */

#include "daObjPathLift_c.h"
#include "dBgCh_Gnd.h"
#include "SharedFilePtr.h"
#include "nitro/fx/fx.h"

extern "C" {
extern CLPS_Block data_ov002_0210d7d4;
extern void func_ov100_02146e70(daObjPathLift_c *self);
extern int func_ov100_0214700c(daObjPathLift_c *self);

extern void Matrix4x3_FromRotationY(Matrix4x3 *m, short ang);
extern void Matrix4x3_FromRotationXYZExt(Matrix4x3 *dst, int a, int b, int c2);
extern short data_02082214[];
extern signed char data_0209f2f8;
extern unsigned char data_0209f2d8;
extern Fix12i Vec3_Dist(const Vector3 *a, const Vector3 *b);
extern unsigned char DecIfAbove0_Byte(unsigned char *p);
extern void func_020393a4(dBgW_KcMbg *p, int v);
extern void func_02039394(dBgW_KcMbg *p, int v);
extern void func_020393d4(dBgW_KcMbg *p, void *v);

/* By-value Fix12<int> is wall 6az: constructing wrapper arguments adds stack
   traffic the ROM does not have. Keep the register-level spelling. */
extern void hold_d_a_obj_path_lift(dBgW_KcMbg *self, void *kcl, const Matrix4x3 *mtx, int scale,
                                   short angY, CLPS_Block *clps);
}

/* The fifth parameter is a signed short, not an unsigned int. Declared
   `unsigned int` this mangles _ZN5Sound8PlayLongEjjjRK7Vector3j. */
namespace Sound {
unsigned int PlayLong(unsigned int, unsigned int, unsigned int,
                      const Vector3 &, short);
}

extern SharedFilePtr data_ov002_0210d9f0;

/* File-scope objects at the end of this file construct the two resource
 * handles (model file 0x9c0d, collision file 0x9c0e). mwcc emits
 * __sinit_d_a_obj_path_lift.cpp from those definitions. The wrapper names
 * are local; the handle constructors and destructors are the ROM
 * resource-family functions, aliased in the manifest. */
struct PathLiftModelFile : SharedFilePtr {
    PathLiftModelFile(u32 fileID);
    ~PathLiftModelFile();
};

struct PathLiftCollisionFilePtr : SharedFilePtr {
    PathLiftCollisionFilePtr(u32 fileID);
    ~PathLiftCollisionFilePtr();
};

extern PathLiftModelFile data_ov100_02148a54;
extern PathLiftCollisionFilePtr data_ov100_02148a5c;

// @symbol daObjPathLift_c_classInit
extern "C" daObjPathLift_c *daObjPathLift_c_classInit()
{
    return new daObjPathLift_c();
}

// @symbol _ZN15daObjPathLift_c13InitResourcesEv
int daObjPathLift_c::InitResources()
{
    Vector3 pos;
    dExtSimpleModel_c::LoadFile(data_ov002_0210d9f0);
    mModel.SetFile((BMD_File *)dExtSimpleModel_c::LoadFile(data_ov100_02148a54), 1, -1);
    mShadowModel.InitCuboid();
    func_ov100_0214700c(this);
    UpdateClsnPosAndRot();
    ((dBgW_KcMbg *)(&mMeshCollider))
        ->dBgW_KcMbg::SetFile((KCL_File *)(dBgW_Kc::LoadFile(data_ov100_02148a5c)), *(&mClsnMat),
                              0x1000, mAngleY, *(&data_ov002_0210d7d4));
    func_020393d4(
        &mMeshCollider,
        (void *)&dBgW::UpdatePosAndAngs);
    mPathSpeed = 0xa000;
    mHorzSpeed = mPathSpeed;
    BaseInitResources();
    mPathDirection = 1;
    pos.x = mPosX;
    pos.y = mPosY;
    pos.z = mPosZ;
    pos.y -= 0x14000;
    {
        dBgCh_Gnd rg;
        int b;
        rg.SetObjAndPos(pos, 0);
        mGroundY = pos.y;
        if (rg.DetectClsn() != 0)
            mGroundY = rg.clsnY;
        mRespawnAfterFall = 1;
        b = (data_0209f2d8 == 1);
        if (b)
            mTimer = 0xb4;
    }
    return 1;
}

// @symbol _ZN15daObjPathLift_c8BehaviorEv
int daObjPathLift_c::Behavior()
{
    UpdatePathModels();
    BaseBehavior();
    if (Vec3_Dist(&mPos, &mPrevPos) != 0) {
        if (DecIfAbove0_Byte(&mTimer) == 0) {
            mSoundHandle = Sound::PlayLong(mSoundHandle, 3, 0x82, mCamSpacePos, 0);
        }
    }
    func_ov100_0214700c(this);
    UpdateClsnPosAndRot();
    func_ov100_02146e70(this);
    func_020393a4(&mMeshCollider, 0x150000);
    func_02039394(&mMeshCollider, 0x1000);
    int b = (int)(data_0209f2d8 == 1);
    if (b != 0) {
        if (mMeshCollider.IsEnabled() == 0) {
            mMeshCollider.Enable(this);
        }
    } else {
        IsClsnInRange(0, 0);
    }
    return 1;
}

// @symbol _ZN15daObjPathLift_c6RenderEv
int daObjPathLift_c::Render()
{
    unsigned short h = mWaitTimer;
    if (h < 0x5a) {
        if (h & 1)
            return 1;
    }
    RenderPathModels();
    mModel.Render(0);
    return 1;
}

// @symbol _ZN15daObjPathLift_c16CleanupResourcesEv
int daObjPathLift_c::CleanupResources()
{
    if (mMeshCollider.IsEnabled()) {
        mMeshCollider.Disable();
    }
    data_ov002_0210d9f0.Release();
    data_ov100_02148a54.Release();
    data_ov100_02148a5c.Release();
    return 1;
}

// @symbol func_ov100_0214700c
extern "C" int func_ov100_0214700c(daObjPathLift_c *self)
{
    Matrix4x3_FromRotationXYZExt(
        &self->mModel.mat4x3, self->mAngleX, self->mAngleY, 0);
    self->mModel.mat4x3.t.x = self->mPosX >> 3;
    self->mModel.mat4x3.t.y = self->mPosY >> 3;
    int z = self->mPosZ >> 3;
    self->mModel.mat4x3.t.z = z;
    return z;
}

// @symbol func_ov100_02146e70
extern "C" void func_ov100_02146e70(daObjPathLift_c *self)
{
    int scaleZ;
    int yOff;
    int groundDepth;
    int idx;
    int sinVal;
    int cosVal;
    int t;

    if (data_0209f2f8 == 13)
        return;
    if (self->mGroundY > self->mPosY)
        return;

    groundDepth = (self->mPosY - self->mGroundY) + 0x64000;

    idx = (unsigned short)self->mAngleX >> 4;
    sinVal = data_02082214[idx << 1];
    yOff = FX_MUL(sinVal, 0x17c000);
    if (yOff < 0)
        yOff = -yOff;
    cosVal = data_02082214[(idx << 1) + 1];
    scaleZ = FX_MUL(cosVal, 0x17c000);
    if (scaleZ < 0)
        scaleZ = -scaleZ;

    Matrix4x3_FromRotationY((Matrix4x3 *)self->mShadowMat, self->mAngleY);
    self->mShadowMat[9] = self->mPosX >> 3;
    self->mShadowMat[10] = (self->mPosY - yOff) >> 3;
    self->mShadowMat[11] = self->mPosZ >> 3;

    t = data_0209f2d8 == 1;
    if (t != false) {
        self->DropShadowScaleXYZ(self->mShadowModel, *(Matrix4x3 *)self->mShadowMat, 0x118000,
                                 0x7d0000, scaleZ, 0xf);
    } else {
        self->DropShadowScaleXYZ(self->mShadowModel, *(Matrix4x3 *)self->mShadowMat, 0x118000,
                                 groundDepth, scaleZ, 0xf);
    }
}
// @symbol _ZN15daObjPathLift_cD1Ev
// @symbol _ZN15daObjPathLift_cD0Ev
/* -------------------------------------------------------------------------- */
/* ROM ordinals 0 and 1 -- the destructor group.                              */
/* Both come from the `~daObjPathLift_c() {}` in the header: the compiler     */
/* writes the group, and only the INLINE form writes it in the cartridge's    */
/* order. An out-of-line definition here emits D2, D0, D1 instead, which is   */
/* why this class's destructor is declared with a body and defined nowhere    */
/* in this file. mwcc still emits _ZTV15daObjPathLift_c for it, so the        */
/* vtable and the RTTI records stay comparable to the cartridge -- see this   */
/* TU's compiler_only_output rows, which check every one of them and then     */
/* discard the copy dsd already delinks.                                     */
/* -------------------------------------------------------------------------- */

/* Static-init globals (was the handwritten __sinit_ov100_02147d7c shard).
 * Definition order is the retail initializer's construction order: the
 * model handle (file 0x9c0d), then the collision handle (file 0x9c0e). */
PathLiftModelFile data_ov100_02148a54(0x9c0d);
PathLiftCollisionFilePtr data_ov100_02148a5c(0x9c0e);
