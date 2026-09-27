//cpp
/* daWater_Tatumaki_c. ov026 text 0x02111aa0..0x021121bc.
 * The factory stays in src/d_a_water_tatumaki.c.
 *
 * Functions are in ROM order. #pragma defer_codegen off makes the one
 * out-of-line destructor emit D1 then D0; the trailing D2 has no ROM home.
 *
 * The five func_ov026_* functions are this class's state machine. The ROM
 * keeps no name for them, so they stay extern "C" free functions taking the
 * object explicitly; func_ov026_02111ee0 installs a State, and the others are
 * the enter/execute halves the State records point at.
 */

#pragma defer_codegen off

#include "daWater_Tatumaki_c.h"
#include "dActor_c.h"
#include "common.h"
#include "Player.h"
#include "SharedFilePtr.h"
#include "TextureTransformer.h"
#include "private/mtx43.h"

/* The two SharedFilePtr globals, the BTA file and the two State records.
   Spelt the way the ov026 static initializer and include/decl_common.h
   declare them, so every declaration of each symbol agrees; the functions
   below view them through the real types. */
extern int data_ov026_02113f0c[];   /* model: SharedFilePtr */
extern int data_ov026_02113f04[];   /* texture animation: SharedFilePtr */
extern BTA_File data_ov026_02112f40;
extern int data_ov026_02113f2c;     /* State: spin in place */
extern void *data_ov026_02113f3c;   /* State: drag the player down */

#define MODEL_FILE_PTR (*(SharedFilePtr *)data_ov026_02113f0c)
#define ANIM_FILE_PTR  (*(SharedFilePtr *)data_ov026_02113f04)
#define STATE_SPIN     ((const daWater_Tatumaki_c::State *)&data_ov026_02113f2c)
#define STATE_DRAG     ((const daWater_Tatumaki_c::State *)&data_ov026_02113f3c)

/* The loaded file behind a SharedFilePtr is its second word. */
#define LOADED_FILE(ptr) ((void *)((int *)&(ptr))[1])

extern "C" {
extern void Matrix4x3_FromRotationY(Matrix4x3 *m, int angle);
extern void Matrix4x3_ApplyInPlaceToRotationX(Matrix4x3 *m, short angX);
extern void Matrix4x3_FromTranslation(Matrix4x3 *m, int x, int y, int z);
extern void Matrix4x3_ApplyInPlaceToRotationXYZExt(Matrix4x3 *m, short rx, short ry, short rz);
extern void MulVec3Mat4x3(Vector3 *in, Matrix4x3 *m, Vector3 *out);
extern void Vec3_Asr(void *dst, void *src, int n);
extern short Vec3_HorzAngle(const Vector3 *a, const Vector3 *b);
extern int Vec3_HorzDist(const Vector3 *a, const Vector3 *b);
extern int Vec3_Dist(const Vector3 *a, const Vector3 *b);
extern unsigned short DecIfAbove0_Short(unsigned short *p);
extern void KillPlayer(void);
extern Matrix4x3 data_020a0e68;
/* local extern: Particle::System::New takes Fix12<int> by value and has no
   declaration in include/Particle__System.h; see src/actors/daDgr_c.cpp. */
extern int _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
    unsigned int uniqueID, unsigned int effectID, int x, int y, int z, void *dir, void *callback);
/* local extern: these three take a Fix12<int> by value. Fix12 has no
   converting constructor, and building one as an aggregate at the call puts
   the constant in .rodata and moves the argument setup (measured: three
   unlicensed .rodata words, InitResources and func_ov026_02111b24 DIFF). */
extern int _Z14ApproachLinearR7Vector3RKS_5Fix12IiE(Vector3 &value, const Vector3 &target, int step);
extern void _ZN18TextureTransformer7SetFileER8BTA_Filei5Fix12IiEj(TextureTransformer *self, BTA_File &file, int flags, int speed, u32 startFrame);
extern void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(ModelAnim *self, BCA_File *file, int flags, int speed, u32 startFrame);
}

void ApproachLinear2(s16 &value, s16 target, s16 step);
void ApproachLinear(int &value, int target, int step);

extern "C" int func_ov026_02111ee0(daWater_Tatumaki_c *self, const daWater_Tatumaki_c::State *state);

// @symbol _ZN18daWater_Tatumaki_cD1Ev
daWater_Tatumaki_c::~daWater_Tatumaki_c()
{
}

// @symbol _ZN18daWater_Tatumaki_cD0Ev
/* D0 is emitted from the destructor above. */

// @symbol func_ov026_02111b24
/* Execute, drag state: swing the player round the funnel and down it; once
   the player is below the centre, kill them. */
extern "C" int func_ov026_02111b24(daWater_Tatumaki_c *self)
{
    Vector3 target;
    Vector3 offset;
    volatile s32 pv[3];     /* the ROM stores the player's position here and never reads it */
    Player *player;

    target.x = 0;
    target.y = 0;
    target.z = 0;
    offset.x = 0;
    offset.y = 0;
    offset.z = 0;
    target.z = self->mPullRadius;
    player = self->ClosestPlayer();
    if (player) {
        Matrix4x3_FromRotationY(&data_020a0e68, self->mPullAngle);
        MulVec3Mat4x3(&target, &data_020a0e68, &offset);
        target.x = self->mCenter.x;
        target.y = self->mCenter.y;
        target.z = self->mCenter.z;
        ApproachLinear2(self->mPullSpin, 0x1000, 0x200);
        ApproachLinear(self->mPullRadius, 0x100, 0x1000);
        ApproachLinear(self->mPullHeight, self->mCenter.y - 0x64000, 0x4000);
        self->mPullAngle += self->mPullSpin;
        target.y = self->mPullHeight;
        target.x += offset.x;
        target.z += offset.z;
        _Z14ApproachLinearR7Vector3RKS_5Fix12IiE(self->mPullPos, target, 0x1e000);
        player->mPosX = self->mPullPos.x;
        player->mPosY = self->mPullPos.y;
        player->mPosZ = self->mPullPos.z;
        {
            int ang = self->HorzAngleToCPlayer() + 0x8000;
            player->mAngleX = -0x2000;
            player->mAngleY = ang;
            player->mAngleZ = 0;
        }
        {
            const Vector3 *playerPos = (const Vector3 *)&player->mPosX;
            pv[0] = playerPos->x;
            pv[1] = playerPos->y;
            pv[2] = playerPos->z;
            if (self->mCenter.y > playerPos->y) {
                if (self->mPlayerKilled == 0) {
                    KillPlayer();
                    self->mPlayerKilled = 1;
                }
            }
        }
    }
    return 1;
}

// @symbol func_ov026_02111cb4
/* Enter, drag state: pick the player up where they stand. */
extern "C" int func_ov026_02111cb4(daWater_Tatumaki_c *self)
{
    Player *player = self->ClosestPlayer();
    if (player) {
        const Vector3 *playerPos = (const Vector3 *)&player->mPosX;
        Vector3 pos;
        pos.x = playerPos->x;
        pos.y = playerPos->y;
        pos.z = playerPos->z;
        self->mPullAngle = Vec3_HorzAngle((Vector3 *)&self->mPosX, &pos);
        self->unk_190 = 0;
        self->mPullHeight = 0;
        self->mPullRadius = 0;
        self->mPullPos.x = pos.x;
        self->mPullPos.y = pos.y;
        self->mPullPos.z = pos.z;
        self->mPullHeight = pos.y;
        self->mPullRadius = Vec3_HorzDist(&self->mCenter, &pos);
    }
    return 1;
}

// @symbol func_ov026_02111d4c
/* Execute, spin state: capture a player who reaches the centre, and draw in
   one who is merely near. Metal Mario is too heavy to be drawn in. */
extern "C" int func_ov026_02111d4c(daWater_Tatumaki_c *self)
{
    Player *player = self->ClosestPlayer();
    if (player != 0) {
        Vector3 pos;
        {
            const Vector3 *playerPos = (const Vector3 *)&player->mPosX;
            pos = *playerPos;
        }

        if (Vec3_HorzDist(&self->mCenter, &pos) <= 0x12c000) {
            int dy = self->mCenter.y - pos.y;
            if (dy < 0) dy = -dy;
            if (dy <= 0x12c000) {
                player->EnterWhirlpool();
                func_ov026_02111ee0(self, STATE_DRAG);
                return 1;
            }
        }

        if (player->mIsMetal == 0) {
            int dist = Vec3_Dist(&self->mCenter, &pos);
            if (dist < 0x44c000) {
                Vector3 pull;
                Vector3 out;
                int speed;
                speed = 0x44c000;
                speed -= dist;
                speed = speed / 35;
                pull.x = 0;
                pull.y = 0;
                pull.z = speed;
                out.x = 0;
                out.y = 0;
                out.z = 0;

                Matrix4x3_FromRotationY(&data_020a0e68, (short)(self->HorzAngleToCPlayer() + 0x8000));
                Matrix4x3_ApplyInPlaceToRotationX(&data_020a0e68, 0x2000);
                MulVec3Mat4x3(&pull, &data_020a0e68, &out);

                {
                    const Vector3 *playerPos = (const Vector3 *)&player->mPosX;
                    pull = *playerPos;
                }
                pull.x += out.x;
                pull.y += out.y;
                pull.z += out.z;
                player->mPosX = pull.x;
                player->mPosY = pull.y;
                player->mPosZ = pull.z;
            }
        }
    }
    return 1;
}

// @symbol func_ov026_02111ed8
/* Enter, spin state: nothing to set up. */
extern "C" int func_ov026_02111ed8(void)
{
    return 1;
}

// @symbol func_ov026_02111ee0
/* Install a state and run its enter half, if it has one. */
extern "C" int func_ov026_02111ee0(daWater_Tatumaki_c *self, const daWater_Tatumaki_c::State *state)
{
    self->mState = state;
    const daWater_Tatumaki_c::State *s = self->mState;
    if (s->enter == 0) return 1;
    return (self->*s->enter)();
}

// @symbol func_ov026_02111f30
/* Rebuild the model matrix from the position and angles. */
extern "C" void func_ov026_02111f30(daWater_Tatumaki_c *self)
{
    Vector3 pos;
    Vec3_Asr(&pos, (Vector3 *)&self->mPosX, 3);
    Matrix4x3_FromTranslation(&data_020a0e68, pos.x, pos.y, pos.z);
    Matrix4x3_ApplyInPlaceToRotationXYZExt(&data_020a0e68,
        self->mAngleX, self->mAngleY, self->mAngleZ);
    /* Copied as twelve flat words: a Matrix4x3 assignment copies the
       Matrix3x3 and the Vector3 separately, and the ROM has one three-pass
       ldm/stm block move. */
    *(Mtx43 *)&self->mModelAnim.mat4x3 = *(Mtx43 *)&data_020a0e68;
}

// @symbol _ZN18daWater_Tatumaki_c16CleanupResourcesEv
int daWater_Tatumaki_c::CleanupResources()
{
    MODEL_FILE_PTR.Release();
    ANIM_FILE_PTR.Release();
    return 1;
}

// @symbol _ZN18daWater_Tatumaki_c16OnPendingDestroyEv
void daWater_Tatumaki_c::OnPendingDestroy()
{
}

// @symbol _ZN18daWater_Tatumaki_c6RenderEv
int daWater_Tatumaki_c::Render()
{
    mTextureTransformer.Update(mModelAnim.data);
    mModelAnim.Render(0);
    return 1;
}

// @symbol _ZN18daWater_Tatumaki_c8BehaviorEv
int daWater_Tatumaki_c::Behavior()
{
    volatile int v[3];      /* particle position: spilled, then reloaded as arguments */
    int x, y, z;

    DecIfAbove0_Short((unsigned short *)&mStateTimer);
    if (mState->execute != 0) {
        (this->*mState->execute)();
    }
    UpdatePos(0);

    x = mPosX;
    v[0] = x;
    y = mPosY;
    v[1] = y;
    z = mPosZ;
    v[2] = z;
    y += 0x384000;
    v[1] = y;

    mParticleID = _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
        *(volatile u32 *)&mParticleID, 0x139, v[0], v[1], z, 0, 0);

    mAngleX = mPrevAngleX;
    mAngleY = mPrevAngleY;
    mAngleZ = mPrevAngleZ;

    func_ov026_02111f30(this);
    mTextureTransformer.Advance();
    mModelAnim.Advance();
    return 1;
}

// @symbol _ZN18daWater_Tatumaki_c13InitResourcesEv
int daWater_Tatumaki_c::InitResources()
{
    BMD_File *model = (BMD_File *)Model::LoadFile(MODEL_FILE_PTR);
    mModelAnim.SetFile(model, 1, -1);

    Animation::LoadFile(ANIM_FILE_PTR);

    TextureTransformer::Prepare(*(BMD_File *)LOADED_FILE(MODEL_FILE_PTR), data_ov026_02112f40);
    _ZN18TextureTransformer7SetFileER8BTA_Filei5Fix12IiEj(&mTextureTransformer, data_ov026_02112f40, 0, 0x1000, 0);

    mTextureTransformer.speed = 0x1000;
    mModelAnim.speed = 0x1000;

    mCenter.x = mPosX;
    mCenter.y = mPosY;
    mCenter.z = mPosZ;
    mCenter.y -= 0x64000;

    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(&mModelAnim, (BCA_File *)LOADED_FILE(ANIM_FILE_PTR), 0, 0x1000, 0);

    func_ov026_02111ee0(this, STATE_SPIN);
    return 1;
}
