//cpp
/* daWater_Hakidasi_c: a water spout that spawns WATER_RING actors (registry profile
 * WATER_HAKIDASI, ov064).
 * 11 functions, .text 0x02119330..0x02119a18.
 *
 * ROM evidence: _ZTS18daWater_Hakidasi_c is "18daWater_Hakidasi_c" at ov064
 * 0x0211c2f8; _ZTI at 0x0211c2ec reads [__si_class_type_info, that string,
 * _ZTI12dEnemyBase_c]. The vtable's address point is 0x0211c334; the word
 * before it is that _ZTI. The tree previously called the class JetStream
 * (coined; the actors it spawns are WATER_RINGs, not jets).
 *
 * The out-of-line destructor is the key function, so this TU emits _ZTV/_ZTI/
 * _ZTS. Under `#pragma defer_codegen off` it comes out D1 (0x02119330), D0
 * (0x02119368), then a D2 the cartridge has no home for (manifest: deadstrip);
 * the same pragma lays .text down in source order, so this file is
 * ROM-ascending.
 *
 * Known limits:
 * - The factory daWater_Hakidasi_c_classInit (0x02119a18) stays a
 *   one-function C source.
 * - `#pragma opt_strength_reduction off` is required inside
 *   func_ov064_021193b4 and is turned back on right after it: the pragma is
 *   file-global and the later members matched without it.
 * - func_ov064_021193b4 keeps its M() launders, the volatile rot block and
 *   `m1 = -1` as found; they were needed to match.
 * - The player is read through raw offsets (0x5c..0x64 position, 0x6f9
 *   Player::mIsMetal); Player.h is not pulled into this TU.
 * - The spawned ring's fields at 0xa4, 0xac and 0x38c have no member yet.
 * - Particle::System::New and dCcAc_c::Init stay mangled extern "C" calls,
 *   with Fix12<int> spelled as int (see InitResources).
 */

#include "daWater_Hakidasi_c.h"
#include "SharedFilePtr.h"

#pragma defer_codegen off

struct Vec3 { int x, y, z; };
struct Vec3_16 { s16 x, y, z; };

typedef int Fix12i;

struct C;
typedef int (C::*PMF)();
struct C { char pad[0x300]; PMF *pp; };

namespace Model { void LoadFile(SharedFilePtr& f); }

extern "C" {
extern void Matrix4x3_FromRotationY(void *m, s16 angle);
extern void Matrix4x3_ApplyInPlaceToRotationX(void *m, s16 angX);
extern void MulVec3Mat4x3(struct Vec3 *in, void *m, struct Vec3 *out);
extern int _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
    int a, int b, int x, int y, int z, int f, int cb);
extern void func_02012790(int a);
extern int data_020a0e68;
extern int SublevelToLevel(int);
extern int data_ov064_0211c934;
extern int IsStarCollected(int r0, int r1);
extern void _ZN7dCcAc_c4InitEP8dActor_c5Fix12IiES3_jj(
    void *, dActor_c *a, Fix12i b, int c, unsigned int d, unsigned int e);
unsigned short DecIfAbove0_Short(unsigned short *p);
}

extern SharedFilePtr data_ov002_0210da10;
extern SharedFilePtr data_ov002_0210d9a8;
extern signed char data_0209f2f8;
extern unsigned char data_0209f220;

/* Identity, but it keeps the address expression from being folded into the access. */
#define M(p) (p)

/* D0 is the deleting destructor: it destroys through this class and its
 * bases, which is why more than one vptr store appears, then frees through an
 * inline operator delete, which is why nothing here mentions a heap. */
// @symbol _ZN18daWater_Hakidasi_cD1Ev
// @symbol _ZN18daWater_Hakidasi_cD0Ev
daWater_Hakidasi_c::~daWater_Hakidasi_c()
{
}

/* Per-frame update. Moves a non-metal player's position while within
 * 0x3e8000 of the spout, spawns a WATER_RING (actor 0xf4) every 0x50 frames
 * (recording its uniqueID in the mSpawnedIDs buffer), and counts the rings the
 * player passes, as reported in mPassedRing, in spawn order. At a count of 5 it
 * waits 0x1e frames, spawns a STAR (actor 0xb2) and sets mRingsPassed to 0xa. */
// @symbol func_ov064_021193b4
extern "C" {
int func_ov064_021193b4(daWater_Hakidasi_c *self)
{
    struct Vec3_16 rot;
    struct Vec3 vec;
    struct Vec3 delta;
    struct Vec3 rewardPos;
    struct Vec3 hitPos1;
    struct Vec3 hitPos2;
    char *player;
    int dist;
    dActor_c *ring;
    int i;
    dActor_c *hit;
    int uid;
    int *playerPos;
    int px, py, pz;
    int *headp;
    int *hitsp;
    int *slotp;
    int *timerp;
    int *posp;
    u16 ax, ay, az;
    s16 tx;
    int m1;

    player = (char *)self->ClosestPlayer();
    if (player != 0 && *(u8 *)(player + 0x6f9) == 0) {     /* Player::mIsMetal */
        dist = self->DistToCPlayer();
        if (dist < 0x3e8000) {
            dist = (0x3e8000 - dist) / 30;
            vec.x = 0;
            vec.y = 0;
            vec.z = dist;
            delta.x = 0;
            delta.y = 0;
            delta.z = 0;
            Matrix4x3_FromRotationY(&data_020a0e68, (s16)(self->HorzAngleToCPlayer() + 0x8000));
            Matrix4x3_ApplyInPlaceToRotationX(&data_020a0e68, -0x4000);
            MulVec3Mat4x3(&vec, &data_020a0e68, &delta);
            playerPos = (int *)(int)M(player + 0x5c);
            px = playerPos[0];
            vec.x = px;
            py = playerPos[1];
            vec.y = py;
            pz = playerPos[2];
            vec.z = pz;
            {
                int newX = px + delta.x;
                vec.y = py + delta.y;
                vec.z = pz + delta.z;
                vec.x = newX;
                *(int *)(player + 0x5c) = newX;
                *(int *)(player + 0x60) = vec.y;
                *(int *)(player + 0x64) = vec.z;
            }
        }
        self->mdCcAc_c.Clear();
        self->mdCcAc_c.dCc_c::Update();
        if (dist > 0x7d0000 && self->mRingsPassed < 5) {
            self->mRingsPassed = 0;
        }
    }

    if (self->unk_318 == 0) {
        self->mParticle = _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
            self->mParticle, 0x138, self->mPosX, self->mPosY, self->mPosZ, 0, 0);
        if (self->mRingsPassed < 5) {
            if (*(u16 *)&self->mStateTimer == 0) {
                ax = *(volatile u16 *)&self->mAngleX;
                ay = *(volatile u16 *)&self->mAngleY;
                {
                    volatile struct Vec3_16 *vr = &rot;
                    vr->x = ax;
                    vr->y = ay;
                    az = *(u16 *)&self->mAngleZ;
                    tx = (s16)vr->x;
                    m1 = -1;
                    vr->z = az;
                    tx = (s16)(tx + 0x4000);
                    vr->x = (u16)tx;
                }
                ring = dActor_c::Spawn(0xf4, 2, *(Vector3 *)&self->mPosX, (Vector3_16 *)&rot, self->mAreaId, -1);
                if (ring != 0) {
                    self->mSpawnedIDs[self->mSpawnedHead] = ring->uniqueID;
                    headp = (int *)(int)M(&self->mSpawnedHead);
                    *headp = *headp + 1;
                    if (self->mSpawnedHead >= 0x14) {
                        self->mSpawnedHead = 0;
                    }
                    *(daWater_Hakidasi_c **)((char *)ring + 0x38c) = self;
                    *(int *)((char *)ring + 0xa4) = 0;
                    ring->mVertSpeed = 0x5000;
                    *(int *)((char *)ring + 0xac) = 0;
                }
                self->mStateTimer = 0x50;
            }
            hit = self->mPassedRing;
            if (hit != 0) {
                if (self->mRingsPassed == 0) {
                    uid = hit->uniqueID;
#pragma opt_strength_reduction off
                    for (i = 0; i < 0x14; i++) {
                        u32 slot = self->mSpawnedIDs[i];
                        if (slot == uid) {
                            self->mMatchedSlot = i;
                            hitsp = (int *)(int)M(&self->mRingsPassed);
                            *hitsp = *hitsp + 1;
                            func_02012790(0x25);
                            hit = self->mPassedRing;
                            posp = (int *)(int)M(&hit->mPosX);
                            hitPos1.x = posp[0];
                            hitPos1.y = posp[1];
                            hitPos1.z = posp[2];
                            self->SpawnNumber(*(Vector3 *)&hitPos1, self->mRingsPassed, 0, 0, 0);
                            self->mPassedRing = 0;
                            return 1;
                        }
                    }
                } else {
                    slotp = (int *)(int)M(&self->mMatchedSlot);
                    *slotp = *slotp + 1;
                    if (self->mMatchedSlot >= 0x14) {
                        self->mMatchedSlot = 0;
                    }
                    {
                        uid = self->mPassedRing->uniqueID;
                        i = self->mMatchedSlot;
                        while (1) {
                            u32 slot = self->mSpawnedIDs[i];
                            if (slot == uid) {
                                hitsp = (int *)(int)M(&self->mRingsPassed);
                                *hitsp = *hitsp + 1;
                                func_02012790(0x25);
                                hit = self->mPassedRing;
                                posp = (int *)(int)M(&hit->mPosX);
                                hitPos2.x = posp[0];
                                hitPos2.y = posp[1];
                                hitPos2.z = posp[2];
                                self->SpawnNumber(*(Vector3 *)&hitPos2, self->mRingsPassed, 0, 0, 0);
                                self->mPassedRing = 0;
                                return 1;
                            }
                            break;
                        }
                    }
                }
                self->mRingsPassed = 0;
                self->mMatchedSlot = 0;
                self->mPassedRing = 0;
            }
        }
    } else {
        self->mParticle = _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
            self->mParticle, 0x7b, self->mPosX, self->mPosY, self->mPosZ, 0, 0);
    }

    if (self->mRingsPassed == 5) {
        timerp = (int *)(int)M(&self->mRewardTimer);
        rewardPos.x = self->mPosX;
        rewardPos.y = self->mPosY;
        rewardPos.z = self->mPosZ;
        rewardPos.y = rewardPos.y - 0x64000;
        *timerp = *timerp + 1;
        if (self->mRewardTimer > 0x1e) {
            dActor_c::Spawn(0xb2, self->unk_314 | 0x40, *(Vector3 *)&rewardPos, (Vector3_16 *)&self->mAngleX, self->mAreaId, -1);
            self->mRingsPassed = 0xa;
        }
    }
    return 1;
}
}

#pragma opt_strength_reduction on

/* Clears the hit actor, the ring head, the matched slot and the ring. */
// @symbol func_ov064_021197fc
extern "C" int func_ov064_021197fc(daWater_Hakidasi_c *self) {
    int i = 0;
    self->mPassedRing = 0;
    self->mSpawnedHead = i;
    self->mMatchedSlot = i;
    for (int v = i; i < 20; i++) {
        self->mSpawnedIDs[i] = v;
    }
    return 1;
}

// @symbol func_ov064_0211982c
extern "C" int func_ov064_0211982c(C *c, PMF *p) { c->pp = p; PMF *q = c->pp; if (*q == 0) return 1; return (c->**q)(); }

// @symbol func_ov064_0211987c
extern "C" void func_ov064_0211987c(void *c)
{
}

/* Gives back the two shared files the spout renders from. Both live in ov002,
 * not in this overlay: the class borrows models the always-resident module
 * owns, so the handles are released rather than freed. */
// @symbol _ZN18daWater_Hakidasi_c16CleanupResourcesEv
s32 daWater_Hakidasi_c::CleanupResources()
{
    data_ov002_0210da10.Release();
    data_ov002_0210d9a8.Release();
    return 1;
}

/* Empty: the ROM body is a single `bx lr`. The override exists to suppress
 * whatever the base does on pending destroy. */
// @symbol _ZN18daWater_Hakidasi_c16OnPendingDestroyEv
void daWater_Hakidasi_c::OnPendingDestroy()
{
}

/* `mov r0,#1; bx lr` and nothing else: the class draws nothing of its own
 * from the render slot. */
// @symbol _ZN18daWater_Hakidasi_c6RenderEv
s32 daWater_Hakidasi_c::Render()
{
    return 1;
}

/* The state pointer at 0x300 is daWater_Hakidasi_c::State (see the header),
 * the same shape and treatment as Bullet::Behavior. */
// @symbol _ZN18daWater_Hakidasi_c8BehaviorEv
s32 daWater_Hakidasi_c::Behavior()
{
  DecIfAbove0_Short((unsigned short*)&mStateTimer);
  State* h = mState;
  /* Reads the handler's pointer word directly rather than as `&h->mMain`:
     taking the ADDRESS of a pointer-to-member makes mwcc materialise the whole
     8-byte pmf. Reading one to CALL it is free. */
  if (*(int*)((char*)h + 8) != 0) {
    (this->*(h->mMain))();
  }
  mAngleX = mPrevAngleX;
  mAngleY = mPrevAngleY;
  mAngleZ = mPrevAngleZ;
  func_ov064_0211987c(this);
  return 1;
}

// @symbol _ZN18daWater_Hakidasi_c13InitResourcesEv
/* Signature of _ZN7dCcAc_c4InitEP8dActor_c5Fix12IiES3_jj deliberately keeps
   Fix12<int> as a plain int: mwccarm passes that class by value differently
   when the parameter is spelled as the real type. See notes/mwccarm-codegen.md 6az. */
s32 daWater_Hakidasi_c::InitResources()
{
    Model::LoadFile(data_ov002_0210da10);
    Model::LoadFile(data_ov002_0210d9a8);
    unk_314 = (param1 >> 0xc) & 0xf;
    unk_318 = param1 & 1;
    if ((param1 & 0xf) > 1) unk_318 = 0;
    if (data_0209f2f8 == 8 && (data_0209f220 == 1 || IsStarCollected(SublevelToLevel(8), 1) == 0)) {
        return 0;
    }
    _ZN7dCcAc_c4InitEP8dActor_c5Fix12IiES3_jj(&mdCcAc_c, (dActor_c*)this, 0xc8000, 0x190000, 0x800004, 0);
    func_ov064_0211982c((C *)this, (PMF *)&data_ov064_0211c934);
    return 1;
}
