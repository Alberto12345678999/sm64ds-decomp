//cpp
namespace Particle {
struct Callback;
}
struct Vector3_16f;
/**
 * Bullet Bill (profile KILLER), fired by daObjBkKillerdai_c.
 *
 * State 0 flies: it hangs in the barrel for 40 frames, shivers for ten,
 * then fires with a smoke trail, homing on the player's yaw while farther
 * than 300.0 away, and blows up after 150 frames or on the first wall that
 * is not its own launcher. State 1 is being shot down: it pitches over and
 * rises for 90 frames before bursting. Behavior runs the state out of a
 * pointer-to-member table and resolves the cylinder's hit: a mega character
 * destroys it outright, a qualifying attack knocks it into state 1, and a
 * player who is not wearing the vanish cap (Player::mIsVanish) takes the
 * hit and does the same.
 *
 * daKlr_c_classInit is reconstructed (RTTI daKlr_c, KILLER registry).
 * Retail does not store that spelling. Historical alias: BulletBill_Spawn.
 *
 * FUNCTION ORDER IS THE REVERSE OF THE ROM'S -- mwccarm emits one .text
 * section per function in the reverse of source order.
 *
 * leftovers:
 * - func_ov079_0212682c, func_ov079_02126794 and func_ov079_02126704
 *   keep address names: the two state-table methods have no recovered
 *   name evidence, and the pose helper is a plain free function.
 * - Player::Hurt takes Fix12<int> by value, so it stays mangled
 *   (notes/mwccarm-codegen.md 6az);
 *   dBgCh_Actr::GetWallResult has no header decl.
 * - func_0200f760, func_0201267c, func_02012694 and Vec3_Add keep linker
 *   names. data_ov079_02128300 / 021282f0 are the model handles, in
 *   overlay data this TU does not own.
 * - MatrixWords keeps the one 0x30-byte mat4x3 block copy; Matrix4x3's
 *   own memberwise assignment comes out 0x18 bytes longer.
 */

#include "daKlr_c.h"
#include "decl_common.h"
#include "SharedFilePtr.h"
#include "Player.h"
#include "Sound.h"
#include "dBgPi.h"
#include "dBgCh_Actr.h"
#include "math/Approach.h"

struct BMD_File;

extern "C" {
extern SharedFilePtr data_ov079_02128300;
extern SharedFilePtr data_ov079_021282f0;

void func_0200f760(dActor_c *self, dCc_c *cc);
void func_02012694(u32 id, const Vector3 *pos);
void Vec3_Add(Vector3 *out, const Vector3 *a, const Vector3 *b);

namespace Particle {
struct System {
    static void *NewSimple(u32 id, int x, int y, int z);
    static int New(unsigned, unsigned, int, int, int, const ::Vector3_16f *, Callback *);
};
}
int d_a_klrNewHold(u32 uniqueID, u32 effectID, int x, int y, int z, void *dir, void *callback);
/* Parameter names keep this TU's @NNN. */
typedef void BgchInitAt_(dBgCh_Actr *self, dActor_c *actor, int radius, int height, Vector3_16 *a,
                         Vector3_16 *b);

void func_ov079_02126704(daKlr_c *self);
}


/* Indexed by mState: [0] func_ov079_0212682c, [1] func_ov079_02126794.
   Defined at the end of this file so it does not insert a function into .text. */
typedef void (daKlr_c::*KlrStateFunc)();
extern KlrStateFunc data_ov079_021282e0[2];

struct MatrixWords { s32 w[12]; };

enum {
    kPlayerActorID = 0xbf,
    kBurstParticle = 0x8f,
    kSmokeParticle = 0x90,
};

// @symbol daKlr_c_classInit
extern "C" daKlr_c *daKlr_c_classInit()
{
    return new daKlr_c();
}

// @symbol _ZN7daKlr_c13InitResourcesEv
s32 daKlr_c::InitResources()
{
    dExtSimpleModel_c::LoadFile(data_ov079_02128300);
    dExtSimpleModel_c::LoadFile(data_ov079_021282f0);
    if (mModel.SetFile((BMD_File *)data_ov079_02128300.filePtr, 1, -1) == 0)
        return 0;
    if (mModel2.SetFile((BMD_File *)data_ov079_021282f0.filePtr, 1, -1) == 0)
        return 0;
    if (mShadow.InitCylinder() == 0)
        return 0;
    {
        Vector3 offset;
        offset.x = 0;
        offset.y = -0x50000;
        offset.z = 0;
        mCylClsn.Init(this, offset, 0x78000, 0xa0000, 0x200005, 0x3c0);
    }
    mState = 0;
    mStateTimer = 0;
    mWallClsn.Init(this, 0x32000, 0, 0, 0);
    mSmokeTrailID = 0;
    return 1;
}

// @symbol _ZN7daKlr_c8BehaviorEv
s32 daKlr_c::Behavior()
{
    int flags;
    u32 which;
    u32 id;

    func_0200f760(this, &mCylClsn);
    UpdatePos(0);

    which = (u32)mState;
    (this->*data_ov079_021282e0[which])();

    id = mCylClsn.otherOwner;
    if (id != 0) {
        flags = mCylClsn.hitFlags;
        if (flags & 0x10) {
            ((Player *)FindWithID(id))->IncMegaKillCount();
            Particle::System::NewSimple(kBurstParticle, mPosX, mPosY, mPosZ);
            MarkForDestruction();
            func_02012694(0x78, &mCamSpacePos);
        } else if (flags & 0x3c0) {
            mState = 1;
            Sound::PlayBank0(0xb5, mCamSpacePos);
        } else {
            dActor_c *o = FindWithID(id);
            if (o != 0) {
                int isPlayer = o->actorID == kPlayerActorID;
                if (isPlayer) {
                    if (!((Player *)o)->mIsVanish) {
                        Vector3 pos;
                        pos.x = mPosX;
                        pos.y = mPosY;
                        pos.z = mPosZ;
                        ((Player *)o)->Hurt(pos, 3, 0xc000, 1, 0, 1);
                        mState = 1;
                        Sound::PlayBank0(0xb5, mCamSpacePos);
                    }
                }
            }
        }
    }

    /* The frame counter is bumped through an unsigned view of the field;
       a plain mStateTimer++ misses by one word. */
    {
        u16 *timer = (u16 *)&mStateTimer;
        *timer = *timer + 1;
        if (which != (u32)mState)
            *timer = 0;
    }

    func_ov079_02126704(this);

    mCylClsn.Clear();
    {
        Vector3 offset;
        offset.x = 0;
        offset.y = -0x50000;
        offset.z = 0;
        mCylClsn.SetPosRelativeToActor(offset);
    }
    mCylClsn.Update();

    mPrevAngleX = mAngleX;
    mPrevAngleY = mAngleY;
    mPrevAngleZ = mAngleZ;
    return 1;
}

// @symbol _ZN7daKlr_c6RenderEv
s32 daKlr_c::Render()
{
    mModel.Render(0);
    mModel2.Render(0);
    return 1;
}

// @symbol _ZN7daKlr_c16CleanupResourcesEv
s32 daKlr_c::CleanupResources()
{
    data_ov079_02128300.Release();
    data_ov079_021282f0.Release();
    return 1;
}

// @symbol _ZN7daKlr_c19func_ov079_0212682cEv
/* State 0: wait in the barrel, shiver, then fly. */
void daKlr_c::func_ov079_0212682c()
{
    Vector3 nose;
    u16 timer = this->mStateTimer;
    if (timer < 40) {
        this->mHorzSpeed = 0x3000;
        return;
    }
    if (timer < 50) {
        if ((int)timer % 2)
            this->mHorzSpeed = 0x3000;
        else
            this->mHorzSpeed = -0x3000;
        return;
    }
    this->UpdateWMClsn(this->mWallClsn, 0);
    this->mHorzSpeed = -0x1e000;
    this->UpdatePosWithHorzSpeedAndAng();
    Vec3_Add(&nose, &this->mPos, (Vector3 *)&this->mSpeedX);
    this->mSmokeTrailID =
        Particle::System::New(this->mSmokeTrailID, kSmokeParticle, nose.x, nose.y, nose.z, 0, 0);
    this->mHorzSpeed = 0x1e000;
    if (this->DistToCPlayer() > 0x12c000)
        ApproachLinear(this->mPrevAngleY, this->HorzAngleToCPlayer(), 0x200);
    this->mAngleY = this->mPrevAngleY;
    if ((u16)this->mStateTimer == 50) {
        func_0201267c(0xd4, &this->mCamSpacePos);
        this->mCylClsn.flags &= ~1;
    }
    {
        int hit = 0;
        if ((u16)this->mStateTimer > 150)
            hit = 1;
        if (this->mWallClsn.IsOnWall() != 0) {
            dBgPi *wall = this->mWallClsn.GetWallResult();
            if (wall->GetClsnID() != (u32)-1) {
                if (dActor_c::FindWithID(wall->GetClsnID()) != this->mLauncher)
                    hit = 1;
            } else {
                hit = 1;
            }
        }
        if (hit == 0)
            return;
    }
    if ((u16)this->mStateTimer > 150) {
        func_02012694(0x79, &this->mCamSpacePos);
        this->PoofDust();
    } else {
        func_02012694(0x78, &this->mCamSpacePos);
        Particle::System::NewSimple(kBurstParticle, nose.x, nose.y, nose.z);
    }
    this->MarkForDestruction();
}

// @symbol _ZN7daKlr_c19func_ov079_02126794Ev
/* State 1: shot down -- pitch over and climb, then burst after 90 frames. */
void daKlr_c::func_ov079_02126794()
{
    if ((u16)this->mStateTimer == 0) {
        this->mHorzSpeed = -0x1e000;
        this->mCylClsn.flags |= 1;
    }
    this->mAngleX += 0x2000;
    this->mPosY += 0x14000;
    if ((u16)this->mStateTimer <= 90)
        return;
    Particle::System::NewSimple(kBurstParticle, this->mPosX, this->mPosY, this->mPosZ);
    func_02012694(0x78, &this->mCamSpacePos);
    this->MarkForDestruction();
}

// @symbol func_ov079_02126704
/* Pose both models from the actor and drop the shadow under them. */
extern "C" void func_ov079_02126704(daKlr_c *self)
{
    Matrix4x3_FromRotationXYZExt(&self->mModel.mat4x3, self->mAngleX, self->mAngleY, self->mAngleZ);
    self->mModel.mat4x3.t.x = self->mPosX >> 3;
    self->mModel.mat4x3.t.y = self->mPosY >> 3;
    self->mModel.mat4x3.t.z = self->mPosZ >> 3;
    /* One 0x30-byte block copy. Matrix4x3's own assignment goes member by
       member through Vector3 and comes out 0x18 bytes longer. */
    *(MatrixWords *)&self->mModel2.mat4x3 = *(MatrixWords *)&self->mModel.mat4x3;
    self->DropShadowRadHeight(self->mShadow, self->mModel.mat4x3, 0x50000, 0x50000, 0xf);
}

// @symbol _ZN7daKlr_c16OnAimedAtWithEggEv
int daKlr_c::OnAimedAtWithEgg()
{
    return 0;
}

// @symbol _ZN7daKlr_cD1Ev
// @symbol _ZN7daKlr_cD0Ev
/* NOT WRITTEN HERE ON PURPOSE. The inline destructor in the header
   emits D1 then D0 -- the cartridge's order -- and no D2. */

/* Behavior indexes this by mState. The compiler copies the two
   pointer-to-member descriptors into it at overlay load. */
KlrStateFunc data_ov079_021282e0[2] = {
    &daKlr_c::func_ov079_0212682c,
    &daKlr_c::func_ov079_02126794,
};
