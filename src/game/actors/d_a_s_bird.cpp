//cpp
/* Castle grounds birds -- ov009/daSBird_c, profile SBIRD (BIRD 343).
 *
 * ov009 is mixed (DOCK_POLE / CASTLE_WATER / METAL_NET / FLAG / BIRD).
 * RTTI ov009:0x02113928 names daSBird_c; the debug table names SBIRD.
 * This is the flock, not the flag and not castle water.
 *
 * daSBird_c_classInit is reconstructed (RTTI daSBird_c, SBIRD registry).
 * Retail does not store that spelling. Historical alias: Bird_Spawn.
 *
 * Factory is `return new daSBird_c()`, through the inherited
 * fBase_c::operator new (`_ZN7fBase_cnwEm`). The destructor is out of line and is
 * defined in d_a_s_bird_head.cpp, below the hatch. Key function is
 * ~daSBird_c(), so that file emits D1/D0 and the class vtable and RTTI.
 * This TU does not.
 *
 * NOTES:
 * - Vec3_Asr / Vec3_Sub / LenVec3 have no shared header. Vec3_HorzLen
 *   and RandomIntInternal are in math/CalcLib.h, but on Vector3 / int *;
 *   this TU keeps its void * spellings.
 * - data_ov009_02113c20 / 02113c28 SharedFilePtr handles: sinit constructs
 *   them as file IDs 1080 / 1081; overlay .bss owns them. symbols.txt has
 *   no recovered names, so they are not coined.
 * - data_ov009_02113c48 is the 4-state PMF table this Behavior indexes;
 *   overlay .bss owns it. In table order its entries are StateSpawnFlock,
 *   StateWaitForPlayer, the free function func_ov009_0211145c, and
 *   StateFly. AttachToLeader is what the two spawn loops call on each
 *   follower.
 * - func_ov009_0211145c is matched on its own in
 *   src/unnamed/ov009/func_ov009_0211145c.cpp (enrolled complete,
 *   0x0211145c..0x021115d8), outside this TU's delinks span.
 *   D1/D0, AttachToLeader and StateFly sit below it in
 *   d_a_s_bird_head.cpp, so this TU's complete range is
 *   0x021115d8..0x02111a70.
 * - Vec3_Asr / Vec3_Sub / func_0201267c are declared with void *, so
 *   &mPosX and &mCamSpacePosX pass to them uncast.
 * - data_020a0e68 scratch matrix; data_02082214 sine table;
 *   data_0209e650 RNG; func_0201267c (sound 0x6a at mCamSpacePos).
 * - RandomIntInternal stays unsigned: signed % 400 changed codegen.
 * - S14: g_profile_SBIRD stays outside the licensed .text.
 * - common.h for Vector3_16 (Spawn rotation); included after the class
 *   header so dExtAnmModel_c's Matrix4x3 spelling wins.
 */

#include "daSBird_c.h"
#include "common.h"
#include "SharedFilePtr.h"
#include "Sound.h"
#include "math/Approach.h"

/* Resource handles this TU's static initializer constructs. The wrapper
 * spellings are reconstructed; constructor and destructor addresses, file
 * IDs, widths, and BSS order are the ROM's. */
struct SBirdModelFilePtr : SharedFilePtr {
    SBirdModelFilePtr(u32 fileID);
    ~SBirdModelFilePtr();
};

struct SBirdAnimationFilePtr : SharedFilePtr {
    SBirdAnimationFilePtr(u32 fileID);
    ~SBirdAnimationFilePtr();
};


typedef void (daSBird_c::*BirdState)();

/* State 2's target is a free function, not a member, so its descriptor
 * is a function-pointer/PMF pair. The first word carries the code
 * relocation; the second is zero, like every other descriptor. */
union SBirdFreeState {
    void (*fn)(daSBird_c *);
    BirdState pmf;
};

extern SBirdFreeState data_ov009_021138fc;

struct SBirdStateTable {
    BirdState slots[4];

    SBirdStateTable()
    {
        slots[0] = &daSBird_c::StateSpawnFlock;
        slots[1] = &daSBird_c::StateWaitForPlayer;
        slots[2] = data_ov009_021138fc.pmf;
        slots[3] = &daSBird_c::StateFly;
    }
};

struct BirdMtx {
    int w[12];
};

extern SBirdModelFilePtr data_ov009_02113c20;
extern SBirdAnimationFilePtr data_ov009_02113c28;
extern SBirdStateTable data_ov009_02113c48;
extern BirdMtx data_020a0e68;
extern s16 data_02082214[];
extern int data_0209e650;

/* local extern: math/CalcLib.h types these on Vector3 / int *, and this TU
   passes raw field addresses; RandomIntInternal must stay unsigned here. */
extern "C" {
extern unsigned int RandomIntInternal(void *rng);
extern void Vec3_Asr(void *dst, void *src, int n);
extern void Vec3_Sub(void *out, void *a, void *b);
extern s32 Vec3_HorzLen(void *v);
extern s32 LenVec3(void *v);
extern void Matrix4x3_FromTranslation(void *m, int x, int y, int z);
extern void Matrix4x3_ApplyInPlaceToRotationZ(void *m, s16 a);
extern void Matrix4x3_ApplyInPlaceToRotationY(void *m, s16 a);

/* State 2: a free function in ROM (src/unnamed/ov009/func_ov009_0211145c.cpp),
 * called through the state table. */
extern void func_ov009_0211145c(daSBird_c *bird);
}

extern int _ZTV9daSBird_c[];

// @symbol daSBird_c_classInit
extern "C" daSBird_c *daSBird_c_classInit()
{
    return new daSBird_c();
}

// @symbol _ZN9daSBird_c13InitResourcesEv
s32 daSBird_c::InitResources()
{
    BMD_File *modelFile = (BMD_File *)dExtSimpleModel_c::LoadFile(data_ov009_02113c20);
    mAnmModel.SetFile(modelFile, 1, 1);
    BCA_File *animFile = (BCA_File *)dExtFrameCtrl_c::LoadFile(data_ov009_02113c28);
    mAnmModel.SetAnim((BCA_File *)animFile, 0, 0x1000, 0);
    mShadowModel.InitCylinder();
    {
        int *p60 = &mPosY;
        int y = *p60;
        int zero = 0;
        *p60 = y + 0xa000;
        mVertAccel = zero;
        mTerminalVelocity = -0x32000;
        mIsLeader = 1;
        mOwnerID = uniqueID;
        mTargetPos.x = mPosX;
        mTargetPos.y = mPosY;
        mTargetPos.z = mPosZ;
        mState = zero;
    }
    return 1;
}

// @symbol _ZN9daSBird_c8BehaviorEv
s32 daSBird_c::Behavior()
{
    (this->*data_ov009_02113c48.slots[mState])();
    int tmp[3];
    Vec3_Asr(tmp, &mPosX, 3);
    Matrix4x3_FromTranslation(&data_020a0e68, tmp[0], tmp[1], tmp[2]);
    mAngleY = mPrevAngleY;
    Matrix4x3_ApplyInPlaceToRotationZ(&data_020a0e68, mAngleZ);
    Matrix4x3_ApplyInPlaceToRotationY(&data_020a0e68, mAngleY);
    *(BirdMtx *)((char *)&mAnmModel.mat4x3) = data_020a0e68;
    DropShadowRadHeight(mShadowModel, mAnmModel.mat4x3, 0x1e000, 0x7d0000, 0xf);
    mAnmModel.Advance();
    return 1;
}

// @symbol _ZN9daSBird_c6RenderEv
s32 daSBird_c::Render()
{
    mAnmModel.Render(0);
    return 1;
}

// @symbol _ZN9daSBird_c16OnPendingDestroyEv
void daSBird_c::OnPendingDestroy()
{
}

// @symbol _ZN9daSBird_c16CleanupResourcesEv
s32 daSBird_c::CleanupResources()
{
    data_ov009_02113c28.Release();
    data_ov009_02113c20.Release();
    return 1;
}

// @symbol _ZN9daSBird_c15StateSpawnFlockEv
/* State 0. A leader spawns (param1 & 0xf) - 1 followers scattered around it
   and aims the flock at the fixed target; every bird then waits in state 1. */
void daSBird_c::StateSpawnFlock() {
    if (mIsLeader) {
        int n = (int)param1 & 0xf;
        if (n > 1) {
            Vector3_16 rot = mPrevAngle;
            for (int i = 0; i < n - 1; i++) {
                Vector3 pos;
                pos.x = mPosX
                    + (int)((RandomIntInternal(&data_0209e650) % 400) - 0xa0)
                        * 4096;
                pos.y = mPosY;
                pos.z = mPosZ
                    + (int)((RandomIntInternal(&data_0209e650) % 400) - 0xa0)
                        * 4096;
                rot.y = (short)(rot.y
                    + (short)(RandomIntInternal(&data_0209e650) >> 16));
                void *a = dActor_c::Spawn(
                    0x157, 0, pos, &rot, mAreaId, -1);
                if (a)
                    ((daSBird_c *)a)->AttachToLeader(uniqueID);
            }
        }
        mTargetPos.x = -0x14000;
        mTargetPos.z = 0xff06a000;
    }
    mState = 1;
}

// @symbol _ZN9daSBird_c18StateWaitForPlayerEv
/* State 1. The leader waits for the closest player to come within 0x7d0 and
   chirps; a follower waits for its leader to take off. Then the bird picks a
   random pitch and enters state 3. */
void daSBird_c::StateWaitForPlayer() {
    if (mIsLeader) {
        char *p2 = (char *)ClosestPlayer();
        if (p2 != 0) {
            struct Vector3 copy;
            struct Vector3 diff;
            int len;
            Vec3_Sub(&diff, &mPosX, p2 + 0x5c);
            copy.x = diff.x;
            copy.y = diff.y;
            copy.z = diff.z;
            len = Vec3_HorzLen(&copy);
            if (len > 0x7d0000)
                return;
        }
        func_0201267c(0x6a, &mCamSpacePos);
    } else {
        daSBird_c *p = (daSBird_c *)dActor_c::FindWithID(mOwnerID);
        if (p == 0) {
            MarkForDestruction();
            return;
        }
        if (p->mState != 3)
            return;
    }
    mPrevAngleX = 5000
        - (unsigned int)RandomIntInternal(&data_0209e650) % 4000;
    mFlySpeed = 0x28000;
    mState = 3;
    mFlags &= ~0x10000;
}

/* Static-resource ownership (was the retired 0xcc handwritten initializer).
 * Definition order is the retail initializer's construction order: the
 * model handle (file 1080), the animation handle (file 1081). Their
 * registration nodes are compiler temporaries, like the PMF descriptors
 * the table initializer below materializes. */
SBirdModelFilePtr data_ov009_02113c20(1080);
SBirdAnimationFilePtr data_ov009_02113c28(1081);

/* PMF descriptors, in ROM address order. The table initializer above
 * copies them into the BSS state table in slot order. */
SBirdFreeState data_ov009_021138fc = { func_ov009_0211145c };

SBirdStateTable data_ov009_02113c48;
