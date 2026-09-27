//cpp
/* daObjRotateUpdownLift_c. ov091 0x02130f00..0x02131ba4, 11 functions.
 *
 * ROM name from _ZTS23daObjRotateUpdownLift_c. Both vtable labels share
 * 0x02134c5c. daObjRotateUpdownLift_c_classInit_HS_UPDOWN_LIFT at 0x02131ba4
 * and daObjRotateUpdownLift_c_classInit_UPDOWN_LIFT at 0x02131bdc stay out.
 *
 * #pragma defer_codegen off lays .text down in source order. One out-of-line
 * destructor emits D1 then D0.
 */

#pragma defer_codegen off

#include "daObjRotateUpdownLift_c.h"
#include "types.h"
#include "SharedFilePtr.h"
#include "dBgW.h"
#include "decl_Platform.h"
#include "dBgCh_Gnd.h"

/* Local shadow declarations carried from the legacy files verbatim.
 * NOT reconciled against real project headers -- check include/*.h for
 * each of these before compiling; a real header should usually win. */
/* shadow namespace 'Particle' */
namespace Particle {
struct System { static System* NewSimple(unsigned int, int, int, int); };
/* Signature deliberately copied from the local declaration above: the ROM
   name carries by-value class parameters (e.g. Fix12<int>), which mwccarm
   passes differently at the call site, so declaring the true types breaks
   the byte match. See notes/mwccarm-codegen.md 6az. */
extern "C" System* _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(unsigned int, int, int, int);
}

/* shadow namespace 'Sound' */
namespace Sound { void PlayBank3(unsigned int, const Vector3&); }

/* shadow struct 'Player' */
struct Player;

/* shadow struct 'V3' */
struct V3 { int x, y, z; };

/* shadow struct 'SFP' */
struct SFP { void *a, *b, *c; };

/* shadow struct 'Sub' */
struct Sub {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void doit(int);
};

/* shadow typedef 'Vec3' */
typedef Vector3 Vec3;

/* shadow enum 'Bool' */
enum Bool { FALSE, TRUE };

extern "C" {
void _ZN6Player16IncMegaKillCountEv(Player *);
void func_02012694(int a, void *b);
extern void Matrix4x3_FromRotationY(void *m, s16 ang);
extern int _ZN8dActor_c18DropShadowScaleXYZER11ShadowModelR9Matrix4x35Fix12IiES5_S5_j(void *self, void *sm, void *mtx, int a, int b, int d, unsigned int e);
extern s16 data_02082214[];
extern struct V3 data_ov091_02134bac;
extern struct V3 data_ov091_02134bd0;
extern struct V3 data_ov091_02134bb8;
extern struct V3 data_ov091_02134ba0;
extern void Matrix4x3_FromRotationXYZExt(void *, int, int, int);
extern struct SFP data_ov091_02134c30[];
extern struct SFP data_ov091_02134c34[];
extern void *_ZN8dActor_c15FindWithActorIDEjPS_(u32 id, void *p);
extern int Vec3_HorzDist(const Vec3 *a, const Vec3 *b);
extern int _ZN8dActor_c13DistToCPlayerEv(void *thiz);
extern int _ZN5Sound8PlayLongEjjjRK7Vector3s(u32 a, u32 b, u32 c, const Vec3 *pos, u32 e);
extern void MulVec3Mat4x3(void *src, void *m, void *dst);
extern void Vec3_Add(void *out, void *a, void *b);
extern void Vec3_Sub(Vec3 *out, Vec3 *a, Vec3 *b);
extern int LenVec3(Vec3 *v);
extern int _ZN4cstd4fdivEii(int a, int b);
extern void Vec3_MulScalar(Vec3 *out, const Vec3 *in, int scale);
extern void SubVec3(Vec3 *a, Vec3 *b, Vec3 *c);
extern void func_ov091_02131340(char *t);
extern void func_020393a4(int *p, int v);
extern void func_02039394(int *p, int v);
extern int _ZN10dBgActor_c13IsClsnInRangeE5Fix12IiES1_(void *thiz, int a, int b);
extern void _ZN10dBgActor_c19UpdateClsnPosAndRotEv(void *thiz);
extern char data_020a0e68[];
extern void _ZN8dActor_c9SetRangesE5Fix12IiES1_S1_S1_(void *self, int a, int b, int c, int d);
extern int _ZN11ShadowModel10InitCuboidEv(void *self);
extern int _ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as(unsigned int a, unsigned int b, void *pos, void *rot, int e, int f);
extern void *_ZN5Model8LoadFileER13SharedFilePtr(void *f);
extern void _ZN9ModelBase7SetFileEP8BMD_Fileii(void *self, void *bmd, int a, int b);
extern void *_ZN7dBgW_Kc8LoadFileER13SharedFilePtr(void *f);
extern void _ZN10dBgW_KcMbg7SetFileEP8KCL_FileRK9Matrix4x35Fix12IiEsR10CLPS_Block(void *self, void *kcl, void *mtx, int fix, short s, void *clps);
extern void func_020393d4(void *p, void *v);
extern signed char data_0209f2f8;
extern char data_ov091_02134cdc[];
extern char data_ov091_02134d1c[];
extern int data_ov091_021344e8[];
extern void *data_ov091_02134c38[];
extern void *_ZN4dBgW16UpdatePosAndAngsERS_P8dActor_cR5dBgPiR7Vector3P10Vector3_16S8_;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 0 -- _ZN23daObjRotateUpdownLift_cD1Ev, 0x02130f00, size 0x4c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN23daObjRotateUpdownLift_cD1Ev
// @symbol _ZN23daObjRotateUpdownLift_cD0Ev
daObjRotateUpdownLift_c::~daObjRotateUpdownLift_c()
{
}

#ifdef _MSC_VER
extern "C" daObjRotateUpdownLift_c *_ZN23daObjRotateUpdownLift_cD0Ev(daObjRotateUpdownLift_c *thiz)
{
    thiz->daObjRotateUpdownLift_c::~daObjRotateUpdownLift_c();
    daObjRotateUpdownLift_c::operator delete(thiz);
    return thiz;
}
#endif

/* -------------------------------------------------------------------------- */
/* ROM ordinal 2 -- func_ov091_02130fac, 0x02130fac, size 0xc4 */
/* -------------------------------------------------------------------------- */
// @symbol func_ov091_02130fac
extern "C" {
extern void Matrix4x3_FromRotationY(void*, short);
extern void MulVec3Mat4x3(void*, void*, void*);
extern void Vec3_Add(void*, void*, void*);
extern char data_020a0e68[];
extern char data_ov091_02134cdc[];
void func_ov091_02130fac(int c) {
    unsigned char *b = (unsigned char*)c;
    char tmp[0x18];
    *(char*)(b + 0x3a0) = 0;
    *(short*)(b + 0x8c) = *(short*)(b + 0x380);
    *(short*)(b + 0x8e) = *(short*)(b + 0x382);
    *(short*)(b + 0x90) = *(short*)(b + 0x384);
    *(int*)(b + 0x5c) = *(int*)(b + 0x388);
    *(int*)(b + 0x60) = *(int*)(b + 0x38c);
    *(int*)(b + 0x64) = *(int*)(b + 0x390);
    *(char*)(b + 0x394) = (char)(*(int*)(b + 8) & 0xf);
    Matrix4x3_FromRotationY((void*)data_020a0e68, *(short*)(b + 0x8e));
    MulVec3Mat4x3(
        (void*)(data_ov091_02134cdc + *(unsigned char*)(b + 0x395) * 0x78 + *(unsigned char*)(b + 0x394) * 0xc),
        (void*)data_020a0e68,
        (void*)tmp);
    Vec3_Add((void*)(tmp + 0xc), (void*)(b + 0x388), (void*)tmp);
    *(int*)(b + 0x5c) = *(int*)(tmp + 0xc);
    *(int*)(b + 0x60) = *(int*)(tmp + 0x10);
    *(int*)(b + 0x64) = *(int*)(tmp + 0x14);
}
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 3 -- _ZN23daObjRotateUpdownLift_c4KillEv, 0x02131070, size 0x8c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN23daObjRotateUpdownLift_c4KillEv
void daObjRotateUpdownLift_c::Kill()
{
    Particle::_ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(0xbb, mPosX, mPosY, mPosZ);
    Vector3 v = { mPosX, mPosY, mPosZ };
    PoofDustAt(v);
    Sound::PlayBank3(0xf, *(Vector3*)&mCamSpacePosX);
    mIsDead = 1;
    unk_31c = 0;
    if (mMeshCollider.IsEnabled()) {
        mMeshCollider.Disable();
    }
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 4 -- _ZN23daObjRotateUpdownLift_c15OnHitByMegaCharER6Player, 0x021310fc, size 0x64 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN23daObjRotateUpdownLift_c15OnHitByMegaCharER6Player
void daObjRotateUpdownLift_c::OnHitByMegaChar(Player &player)
{
    char *self = (char *)this;
    Player *p = &player;
    unsigned short h = *(unsigned short *)(self + 0xc);
    int eq = (h == 0x1e);
    if (eq) return;
    _ZN6Player16IncMegaKillCountEv(p);
    func_02012694(0x1e, self + 0x74);
    _ZN10dBgActor_c14KillByMegaCharER6Player(self, p);
    *(short *)(self + 0x8e) = *(short *)(self + 0x94);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 5 -- func_ov091_02131160, 0x02131160, size 0x1e0 */
/* -------------------------------------------------------------------------- */
// @symbol func_ov091_02131160
extern "C" {  /* .c-derived member: C linkage for the whole block */
int func_ov091_02131160(char *c) {
    struct V3 v0 = data_ov091_02134bac;
    struct V3 v1 = data_ov091_02134bd0;
    struct V3 v2 = data_ov091_02134bb8;
    struct V3 v3 = data_ov091_02134ba0;

    Matrix4x3_FromRotationY(c + 0x348, *(s16 *)(c + 0x8e));
    *(int *)(c + 0x36c) = *(int *)(c + 0x5c) >> 3;

    int idx = *(u16 *)(c + 0x8c) >> 4;
    int s = data_02082214[idx << 1];
    int sa = s < 0 ? -s : s;
    int scaled = (int)(((long long)sa * 0xa0000 + 0x800) >> 12);
    int b5 = *(u8 *)(c + 0x395);
    int base = (&v0.x)[b5];
    int sum = base + scaled;
    int py = *(int *)(c + 0x60);
    *(int *)(c + 0x370) = (py - sum) >> 3;
    *(int *)(c + 0x374) = *(int *)(c + 0x64) >> 3;

    int b5b = *(u8 *)(c + 0x395);
    int h = *(int *)(c + 0x60) - *(int *)(c + 0x37c);
    if (h <= 0x1000) h = 0x1000;
    int r3 = (&v3.x)[b5b];
    if (h + 0x100000 >= r3) r3 = h + 0x100000;
    *(int *)(c + 0xb4) = -((int)(h + ((unsigned)h >> 31)) >> 1);
    *(int *)(c + 0xb8) = (int)(r3 + ((unsigned)r3 >> 31)) >> 4;

    int r5 = (int)(((long long)h * 32 + 0x800) >> 12);
    int idx2 = *(u16 *)(c + 0x8c) >> 4;
    int b5c = *(u8 *)(c + 0x395);
    int a_arg = (&v1.x)[b5c] - r5;
    int s2 = data_02082214[(idx2 << 1) + 1];
    int fac = 0xa0000 - r5;
    if (s2 < 0) s2 = -s2;
    return _ZN8dActor_c18DropShadowScaleXYZER11ShadowModelR9Matrix4x35Fix12IiES5_S5_j(
        c, c + 0x320, c + 0x348, a_arg, h,
        (&v2.x)[b5c] + (int)(((long long)fac * s2 + 0x800) >> 12), 0xf);
}
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 6 -- func_ov091_02131340, 0x02131340, size 0x48 */
/* -------------------------------------------------------------------------- */
// @symbol func_ov091_02131340
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov091_02131340(char *t)
{
    Matrix4x3_FromRotationXYZExt(t + 0xf0, *(short *)(t + 0x8c), *(short *)(t + 0x8e), *(short *)(t + 0x90));
    *(int *)(t + 0x114) = *(int *)(t + 0x5c) >> 3;
    *(int *)(t + 0x118) = *(int *)(t + 0x60) >> 3;
    *(int *)(t + 0x11c) = *(int *)(t + 0x64) >> 3;
}
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 7 -- _ZN23daObjRotateUpdownLift_c16CleanupResourcesEv, 0x02131388, size 0x80 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN23daObjRotateUpdownLift_c16CleanupResourcesEv
int daObjRotateUpdownLift_c::CleanupResources()
{
  if(param1 == 0xffff) return 1;
  if(((dBgW *)((char *)&mMeshCollider))->IsEnabled())
    ((dBgW *)((char *)&mMeshCollider))->Disable();
  ((SharedFilePtr *)(data_ov091_02134c30[mVariant].a))->Release();
  ((SharedFilePtr *)(data_ov091_02134c34[mVariant].a))->Release();
  return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 8 -- _ZN23daObjRotateUpdownLift_c6RenderEv, 0x02131408, size 0x60 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN23daObjRotateUpdownLift_c6RenderEv
int daObjRotateUpdownLift_c::Render()
{
    if (mIsDead) return 1;
    if (param1 == 0xffff) return 1;
    ((struct Sub*)((char *)&mModel))->doit(0);
    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 9 -- _ZN23daObjRotateUpdownLift_c8BehaviorEv, 0x02131468, size 0x488 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN23daObjRotateUpdownLift_c8BehaviorEv
int daObjRotateUpdownLift_c::Behavior()
{
    Vec3 pos;
    Vec3 sp10;
    Vec3 sp1C;
    Vec3 sp28;
    Vec3 sp34;
    Vec3 sp40;
    Vec3 sp4C;
    Vec3 sp58;
    int r4;
    int r6;
    int r5;
    int len2;
    int len1;
    int fd;
    void *r8;

    if (mIsDead != 0) {
        return 1;
    }

    if (param1 == 0xffff) {
        int is1d;
        r4 = 1;
        is1d = actorID;
        is1d = (is1d == 0x1d);
        if (is1d != 0) {
            void *a;
            void *b;
            if (*(void **)((char *)&mPlatform0) == 0 || *(void **)((char *)&mPlatform1) == 0) {
                r8 = _ZN8dActor_c15FindWithActorIDEjPS_(0x1d, 0);
                if (r8 != 0) {
                    do {
                        if (r8 != (void *)((char *)this) &&
                            Vec3_HorzDist((Vec3 *)((char *)&mPosX), (Vec3 *)((char *)r8 + 0x5c)) < 0xa0000) {
                            if (*(void **)((char *)&mPlatform0) == 0) {
                                *(void **)((char *)&mPlatform0) = r8;
                            } else if (*(void **)((char *)&mPlatform1) == 0) {
                                *(void **)((char *)&mPlatform1) = r8;
                            }
                        }
                        r8 = _ZN8dActor_c15FindWithActorIDEjPS_(0x1d, r8);
                    } while (r8 != 0);
                }
            }
            a = *(void **)((char *)&mPlatform0);
            if (a != 0) {
                b = *(void **)((char *)&mPlatform1);
                if (b != 0) {
                    int b8;
                    if (*(u8 *)((char *)a + 0x3a0) != 0 && *(u8 *)((char *)b + 0x3a0) != 0) {
                        r4 = 0;
                    }
                    b8 = (mFlags & 8) ? 1 : 0;
                    if (b8 != 0) {
                        if (_ZN8dActor_c13DistToCPlayerEv(((char *)this)) > 0x7d0000) {
                            char *p398 = *(char **)((char *)&mPlatform0);
                            char *p39c;
                            if (*(u8 *)(p398 + 0x3a0) != 0) {
                                func_ov091_02130fac((int)p398);
                            }
                            p39c = *(char **)((char *)&mPlatform1);
                            if (*(u8 *)(p39c + 0x3a0) != 0) {
                                func_ov091_02130fac((int)p39c);
                            }
                        }
                    }
                }
            }
        }
        if (r4 != 0) {
            mSoundHandle = _ZN5Sound8PlayLongEjjjRK7Vector3s(
                mSoundHandle, 3, 0x8d, (Vec3 *)((char *)&mCamSpacePosX), 0);
        }
        return 1;
    }

    if (_ZN10dBgActor_c20UpdateKillByMegaCharEsss5Fix12IiE(((char *)this), 0x2000, 0, 0, 0) != 0) {
        return 1;
    }

    {
        int py;
        pos.x = mPosX;
        py = mPosY;
        pos.y = py;
        pos.z = mPosZ;
        pos.y = py - 0x14000;
    }
    dBgCh_Gnd ground;
    ground.SetObjAndPos(pos, 0);
    mGroundY = pos.y;
    if (ground.DetectClsn() != 0) {
        mGroundY = ground.clsnY;
    }

    r6 = 0;
    r5 = data_ov091_021344e8[mVariant];
    r4 = mWaypointIndex - 1;
    if (r4 < 0) {
        r4 = 9;
    }
    Matrix4x3_FromRotationY(data_020a0e68, mAngleY);
    MulVec3Mat4x3(data_ov091_02134cdc + mVariant * 0x78 + mWaypointIndex * 0xc,
                  data_020a0e68, &sp10);
    MulVec3Mat4x3(data_ov091_02134cdc + mVariant * 0x78 + r4 * 0xc,
                  data_020a0e68, &sp1C);
    Vec3_Add(&sp34, (Vec3 *)((char *)&mBasePosX), &sp10);
    Vec3_Sub(&sp28, (Vec3 *)((char *)&mPosX), &sp34);
    Vec3_Sub(&sp40, &sp10, &sp1C);
    len1 = LenVec3(&sp40);
    len2 = LenVec3(&sp28);
    fd = _ZN4cstd4fdivEii(len1 - len2, len1);
    {
        s16 *b300 = (s16 *)((char *)this + 0x300);
        int mul = *(s16 *)((char *)b300 + 0xa4);
        int base = *(s16 *)((char *)b300 + 0xa2);
        mAngleX = (s16)(base + (int)((short)(((long long)mul * fd + 0x800) >> 12)));
    }

    if (len2 == 0 || len2 <= r5) {
        Vec3_Add(&sp4C, (Vec3 *)((char *)&mBasePosX), &sp10);
        mPosX = sp4C.x;
        mPosY = sp4C.y;
        mPosZ = sp4C.z;
        {
            s16 *r2 = (s16 *)((char *)&mPitchBase);
            s16 *b300 = (s16 *)((char *)this + 0x300);
            r6 = 1;
            *r2 = (s16)(*r2 + *(s16 *)((char *)b300 + 0xa4));
        }
    } else {
        Vec3_MulScalar(&sp58, &sp28, _ZN4cstd4fdivEii(r5, len2));
        SubVec3((Vec3 *)((char *)&mPosX), &sp58, (Vec3 *)((char *)&mPosX));
    }

    if (r6 != 0) {
        u8 *p394 = (u8 *)((char *)&mWaypointIndex);
        *p394 = (u8)(*p394 + 1);
        if ((u32)mWaypointIndex >= 0xa) {
            mWaypointIndex = 0;
        }
        if ((u32)mWaypointIndex > 3 && (u32)mWaypointIndex < 8) {
            mPitchStep = 0x2000;
        } else {
            mPitchStep = 0;
        }
    }

    func_ov091_02131340(((char *)this));

    {
    int is1e = actorID;
    is1e = (is1e == 0x1e);
    if (is1e == 0) {
        func_ov091_02131160(((char *)this));
        func_020393a4((int *)((char *)&mMeshCollider), 0x150000);
        func_02039394((int *)((char *)&mMeshCollider), 0x1000);
        if (_ZN10dBgActor_c13IsClsnInRangeE5Fix12IiES1_(((char *)this), 0x150000, 0x1000) != 0) {
            _ZN10dBgActor_c19UpdateClsnPosAndRotEv(((char *)this));
        }
    } else {
        if (_ZN10dBgActor_c13IsClsnInRangeE5Fix12IiES1_(((char *)this), 0, 0) != 0) {
            _ZN10dBgActor_c19UpdateClsnPosAndRotEv(((char *)this));
        }
    }
    }

    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 10 -- _ZN23daObjRotateUpdownLift_c13InitResourcesEv, 0x021318f0, size 0x2b4 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN23daObjRotateUpdownLift_c13InitResourcesEv
int daObjRotateUpdownLift_c::InitResources()
{
    Vector3 v;
    Vector3 rotated;
    Vector3 posVec;
    Vector3 v2;
    unsigned char idx394, idx395;
    void *bmd;
    void *kcl;

    if (param1 == 0xffff) {
        int *p = (int*)(((int)((char *)this) + 0xb0));
        *p = *p & ~2;
        _ZN8dActor_c9SetRangesE5Fix12IiES1_S1_S1_(((char *)this), 0, 0x1000, 0, 0);
        return 1;
    }

    mBasePosX = mPosX;
    mBasePosY = mPosY;
    mBasePosZ = mPosZ;
    _ZN11ShadowModel10InitCuboidEv((char *)&mShadowModel);

    {
        enum Bool isSpecial;
        ((char *)this)[0x395] = 0;
        isSpecial = (enum Bool)(actorID == 0x1e);
        if (isSpecial) {
            ((char *)this)[0x395] = 2;
        } else if (data_0209f2f8 == 7) {
            ((char *)this)[0x395] = 1;
        }
    }

    ((char *)this)[0x394] = (unsigned char)(param1 & 0xf);

    if ((unsigned char)((char *)this)[0x394] == 2) {
        char *tbl = data_ov091_02134cdc;
        int s = 0x78;
        int i = (unsigned char)((char *)this)[0x395];
        Vec3_Add(&v, (Vector3*)((char *)&mBasePosX), (Vector3*)(tbl + i * s));
        i = (unsigned char)((char *)this)[0x395];
        v.y += *(int*)(data_ov091_02134d1c + i * s);
        _ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as(0x1d, 0xffff, &v, 0, mAreaId, -1);
    }

    Matrix4x3_FromRotationY(&data_020a0e68, mAngleY);

    {
        char *tbl = data_ov091_02134cdc;
        int s = 0x78;
        int i = (unsigned char)((char *)this)[0x395];
        idx394 = (unsigned char)((char *)this)[0x394];
        MulVec3Mat4x3((Vector3*)(tbl + i * s + idx394 * 0xc), &data_020a0e68, &rotated);
    }

    Vec3_Add(&v2, (Vector3*)((char *)&mBasePosX), &rotated);

    mPosX = v2.x;
    mPosY = v2.y;
    mPosZ = v2.z;

    idx395 = (unsigned char)((char *)this)[0x395];
    bmd = _ZN5Model8LoadFileER13SharedFilePtr(*(void**)((char*)data_ov091_02134c30 + idx395 * 0xc));
    _ZN9ModelBase7SetFileEP8BMD_Fileii(((char *)this) + 0xd4, bmd, 1, -1);

    func_ov091_02131340(((char *)this));
    _ZN10dBgActor_c19UpdateClsnPosAndRotEv(((char *)this));

    idx395 = (unsigned char)((char *)this)[0x395];
    kcl = _ZN7dBgW_Kc8LoadFileER13SharedFilePtr(*(void**)((char*)data_ov091_02134c34 + idx395 * 0xc));
    _ZN10dBgW_KcMbg7SetFileEP8KCL_FileRK9Matrix4x35Fix12IiEsR10CLPS_Block(
        ((char *)this) + 0x124, kcl, ((char *)this) + 0x2ec, 0x199, mAngleY,
        *(void**)((char*)data_ov091_02134c38 + idx395 * 0xc));

    func_020393d4(((char *)this) + 0x124, &_ZN4dBgW16UpdatePosAndAngsERS_P8dActor_cR5dBgPiR7Vector3P10Vector3_16S8_);

    posVec.x = mPosX;
    posVec.y = mPosY;
    posVec.z = mPosZ;
    posVec.y -= 0x14000;

    dBgCh_Gnd ground;
    ground.SetObjAndPos(posVec, 0);
    mGroundY = posVec.y;
    if (ground.DetectClsn())
        mGroundY = ground.clsnY;

    mSpawnAngleX = mAngleX;
    mSpawnAngleY = mAngleY;
    mSpawnAngleZ = mAngleZ;

    return 1;
}
