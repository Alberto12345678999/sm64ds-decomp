//cpp
/* daSnowman_c, the snowman. ov081 0x02124090..0x02125ec0, 34 functions.
 *
 * The cartridge spells the class 11daSnowman_c. This file is that class and
 * nothing after it: daSnowman_c_classInit at 0x02125ec0 stays out.
 *
 * #pragma defer_codegen off lays .text down in source order, so this file is
 * ROM-ascending. One out-of-line destructor is the key function and emits
 * D1 then D0. common.h is first so its flat Matrix4x3 { s32 m[12]; } is the
 * one the matrix helpers index with .m.
 */

#pragma defer_codegen off

#include "common.h"
#include "daSnowman_c.h"
#include "SharedFilePtr.h"
#include "PathPtr.h"
#include "SaveData.h"

/* Eight-byte path handle. PathPtr.h's constructor would run on a local and
 * then the explicit C1 call would run it again, so this POD stands in. */
struct SnowPath { int a, b; };

/* func_ov081_02124dfc reads area, a spawned-actor id and a position through
 * offsets that are not dActor_c's own fields. */
struct SnowSpawnView {
    char pad0[0xcc];
    s8 areaID;
    char pad1[0x100 - 0xcd];
    s16 f100;
    char pad2[0x3fc - 0x102];
    u32 uniqueID;
    char pad3[0x408 - 0x400];
    s32 f408;
    char pad4[0x434 - 0x40c];
    Vector3 pos;
};

/* ModelAnim slot 3, called through the object's own vtable. */
struct Obj {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

/* State record: the pointer-to-member sits 8 bytes into the word at +0x3f8. */
struct C;
typedef int (C::*PMF)();
struct C { char pad[0x3f8]; PMF *pp; };

extern "C" {
extern char *_ZN8dActor_c10FindWithIDEj(unsigned int id);
extern int RandomIntInternal(int *seed);
extern void func_02012790(int);
extern void *_ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as(
    unsigned int, unsigned int, struct Vector3 *, const void *, int, int);
extern int data_0209e650;
extern s16 data_ov081_021289a4;
extern s16 data_ov081_021289a6;
extern s16 data_ov081_021289a8;
extern char data_ov081_02128e94;
extern char *_ZN8dActor_c22ClosestNonVanishPlayerEv(char *self);
extern s16 Vec3_HorzAngle(const struct Vector3 *v0, const struct Vector3 *v1);
extern void ApproachAngle(void *p, int target, int a, int b, int c);
extern int AngleDiff(int a, int b);
extern void _ZN10dCcAcPos_c21SetPosRelativeToActorERK7Vector3(void *c, void *v);
extern void func_ov002_020aea30(void *self, void *actor, void *collision);
extern s16 _ZN8dActor_c18HorzAngleToCPlayerEv(void *self);
extern void func_02012694(int a, void *p);
extern void _ZN12dEnemyBase_c20KillByInvincibleCharERK10Vector3_16R6Player5Fix12IiE(
    void *self, void *v, void *a);
extern void _ZN6Player4HurtERK7Vector3j5Fix12IiEjjj(
    void *p, void *v, u32 a, int f, u32 c, u32 d, u32 e);
extern Vector3 data_ov081_02128998;
extern unsigned char data_0209f21c[];
extern char *data_0209f394[];
extern int _ZNK10dBgCh_Actr10IsOnGroundEv(void *c);
extern void _Z14ApproachLinearRiii(int *ref, int target, int step);
extern int _ZN8dActor_c10SpawnCoinsERK7Vector3j5Fix12IiEs(
    void *a, Vector3 *v, unsigned n, Fix12i f, short s);
extern void _ZN8dActor_c24KillAndTrackInDeathTableEv(void *c);
extern unsigned _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
    unsigned a, unsigned b, int c, int d, int e, const void *f, void *g);
extern void *_ZN7PathPtrC1Ev(void *self);
extern void _ZN7PathPtr6FromIDEj(void *self, unsigned int id);
extern void _ZNK7PathPtr7GetNodeER7Vector3j(void *self, void *v, unsigned int i);
extern void Vec3_Sub(struct Vector3 *out, struct Vector3 *a, struct Vector3 *b);
extern int LenVec3(struct Vector3 *v);
extern Fix12i Vec3_Dist(const struct Vector3 *a, const struct Vector3 *b);
extern int _ZN4cstd4fdivEii(int a, int b);
extern void Vec3_MulScalar(struct Vector3 *out, struct Vector3 *in, int s);
extern void SubVec3(struct Vector3 *a, struct Vector3 *b, struct Vector3 *c);
extern void Vec3_Asr(int *d, int *s, int sh);
extern void Matrix4x3_FromTranslation(void *m, int x, int y, int z);
extern void Matrix4x3_ApplyInPlaceToRotationXYZExt(void *m, int x, int y, int z);
extern void MulMat4x3Mat4x3(void *dst, void *a, void *b);
extern void Matrix4x3_ApplyInPlaceToTranslation(void *m, int x, int y, int z);
extern void _ZN8dActor_c19DropShadowRadHeightER11ShadowModelR9Matrix4x35Fix12IiES5_j(
    void *self, void *sm, void *mtx, int a, int b, unsigned int g);
extern struct Matrix4x3 data_020a0e68;
extern void _ZN5Model6RenderEPK7Vector3(void *, void *);
extern int _ZN12dEnemyBase_c26UpdateKillByInvincibleCharER10dBgCh_ActrR9ModelAnimj(
    void *self, void *wm, void *anim, unsigned n);
extern int _ZN12dEnemyBase_c11UpdateDeathER10dBgCh_Actr(void *self, void *wm);
extern void _ZN8dActor_c9SetRangesE5Fix12IiES1_S1_S1_(void *self, int a, int b, int c, int d);
extern unsigned short DecIfAbove0_Short(unsigned short *p);
extern void _ZN8dActor_c9UpdatePosEP5dCc_c(void *self, void *cyl);
extern void _ZN12dEnemyBase_c12UpdateWMClsnER10dBgCh_Actrj(void *self, void *wm, unsigned n);
extern void _ZN5dCc_c5ClearEv(void *self);
extern void _ZN5dCc_c6UpdateEv(void *self);
extern void _ZN9Animation7AdvanceEv(void *self);
extern int _ZN9Animation8FinishedEv(void *self);
extern void *_ZN5Model8LoadFileER13SharedFilePtr(void *fp);
extern void _ZN9ModelBase7SetFileEP8BMD_Fileii(void *self, void *f, int a, int b);
extern void _ZN11ShadowModel12InitCylinderEv(void *self);
extern void *_ZN9Animation8LoadFileER13SharedFilePtr(void *fp);
extern int _ZN8dActor_c18GetBitInDeathTableEv(void *self);
extern void _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj(
    void *self, void *actor, const void *v, int d, int e, u32 f, u32 g);
extern void _ZN10dBgCh_Actr4InitEP8dActor_c5Fix12IiES3_P10Vector3_16S5_(
    void *self, void *actor, int b, int c, void *v16, int e);
extern void *_ZN8dActor_c13ClosestPlayerEv(void *actor);
extern int _ZN4cstd5atan2E5Fix12IiES1_(int a, int b);
extern void Matrix4x3_FromRotationY(void *m, int ang);
extern int Vec3_HorzLen(void *v);
extern void Matrix4x3_ApplyInPlaceToRotationX(void *m, short ang);
extern void MulVec3Mat4x3(void *a, void *m, void *b);
extern void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(
    void *self, void *bca, int a, int fix, unsigned int b);
extern int data_ov081_02128e34[];
extern char data_ov081_02128e44[];
extern char data_ov081_02128e54[];
extern char data_ov081_02128e64[];
extern char data_ov081_02128e74[];
extern char data_ov081_02128e84[];
extern char data_ov081_02128e24[];
extern void *data_ov081_02128e14;
extern char data_ov081_02128ea4[];
extern SharedFilePtr data_ov081_02128d90;
extern SharedFilePtr data_ov081_02128db0;
extern SharedFilePtr data_ov081_02128d88;
extern SharedFilePtr data_ov081_02128da0;
extern SharedFilePtr data_ov081_02128d98;
extern SharedFilePtr data_ov081_02128da8;
extern SharedFilePtr data_ov081_02128db8;
extern "C" void func_ov081_02124134(char* c);
extern "C" void func_ov081_0212423c(char* self, int idx);
extern "C" void func_ov081_021243cc(void* self);
extern "C" int func_ov081_021245e8(void* thiz);
extern "C" int func_ov081_021246a0(char* c);
extern "C" int func_ov081_0212479c(char *self);
extern "C" int func_ov081_02124894(char* c);
extern "C" int func_ov081_0212498c(char *c);
extern "C" int func_ov081_021249f4(char *c);
extern "C" int func_ov081_02124b08(char *c);
extern "C" int func_ov081_02124b98(char* c);
extern "C" int func_ov081_02124d14(char *c);
extern "C" int func_ov081_02124d50(char* c);
extern "C" int func_ov081_02124dfc(SnowSpawnView *self);
extern "C" int func_ov081_02124e64(char *c);
extern "C" int func_ov081_02124ec0(char *p);
extern "C" int func_ov081_02124f20(char *c);
extern "C" int func_ov081_02124f7c(char *thiz);
extern "C" int func_ov081_02125038(char* c);
extern "C" int func_ov081_02125068(char *c);
extern "C" int func_ov081_021250c8(char *c);
extern "C" int func_ov081_02125200(void);
extern "C" int func_ov081_02125208(char *c);
extern "C" int func_ov081_0212538c(char *c);
extern "C" int func_ov081_02125488(void *cv, void *pv);
extern "C" void func_ov081_021254d8(char *c);
}

// @symbol _ZN11daSnowman_cD1Ev
// @symbol _ZN11daSnowman_cD0Ev
daSnowman_c::~daSnowman_c()
{
}

// @symbol func_ov081_02124134
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov081_02124134(char* c){
  char* a;
  unsigned int id = *(unsigned int*)(c+0x3fc);
  if (id) {
    a = _ZN8dActor_c10FindWithIDEj(id);
    if (a) {
      *(int*)(a+0x9c) = -0x2000;
      *(int*)(a+0xa0) = -0x28000;
      *(int*)(c+0x3fc) = 0;
    }
  }
  id = *(unsigned int*)(c+0x400);
  if (id) {
    a = _ZN8dActor_c10FindWithIDEj(id);
    if (a) {
      unsigned int rv;
      *(int*)(a+0x9c) = -0x2000;
      rv = (unsigned int)RandomIntInternal(&data_0209e650);
      rv = (rv >> 8) & 0xf;
      *(short*)(a+0x92) = 0;
      *(short*)(a+0x94) = rv << 0xc;
      *(short*)(a+0x96) = 0;
      *(int*)(a+0xa4) = 0;
      *(int*)(a+0xa8) = 0x14000;
      *(int*)(a+0xac) = 0;
      *(int*)(a+0x98) = 0xa000;
      *(int*)(a+0xc8) = 0;
    }
    func_02012790(0xa);
    *(int*)(c+0x400) = 0;
  }
  if (*(int*)(c+0x41c) == 2) {
    _ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as(0xdf, 0x300, (struct Vector3*)(c+0x44c), 0, *(signed char*)(c+0xcc), -1);
  }
}
}

// @symbol func_ov081_0212423c
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov081_0212423c(char* self, int idx)
{
    char* player;
    struct Vector3 v;
    int ang;
    int off;
    s16* p8;
    s16* p6;
    s16* p4;
    s16* p414;
    int lim;

    player = _ZN8dActor_c22ClosestNonVanishPlayerEv(self);
    if (player == 0)
        return;

    {
        int* pp = (int*)(((int)(player + 0x5c)));
        int py = pp[1];
        int pz = pp[2];
        v.x = pp[0];
        v.y = py;
        v.z = pz;
    }
    ang = Vec3_HorzAngle((struct Vector3*)(self + 0x5c), &v);

    off = idx * 6;
    p8 = (s16*)((char*)&data_ov081_021289a8 + off);
    p6 = (s16*)((char*)&data_ov081_021289a6 + off);
    p4 = (s16*)((char*)&data_ov081_021289a4 + off);

    ApproachAngle((s16*)(self + 0x94), ang, *p4, *p6, *p8);

    if (idx != 1) {
        *(s16*)(self + 0x414) = 0;
        *(int*)(self + 0x410) = 0;
        goto second;
    }

    if (AngleDiff(ang, *(s16*)(self + 0x8e)) > 0x200) {
        p414 = (s16*)(((int)self + 0x414));
        lim = -0x2000;
        *p414 = *p414 - 0x100;
        if (*(s16*)(self + 0x400 + 0x14) >= lim)
            goto second;
        *(s16*)(self + 0x400 + 0x14) = (s16)lim;
    } else {
        goto full_tail;
    }

    {
        int* p410 = (int*)(((int)self + 0x410));
        *p410 = *p410 + 1;
    }
    if (*(int*)(self + 0x410) > 0x28) {
        *(int*)(self + 0x408) = *(s16*)(self + 0x8e) - ang;
        func_ov081_02125488(self, &data_ov081_02128e94);
        return;
    }
    goto second;

full_tail:
    *(int*)(self + 0x410) = 0;
    ApproachAngle((s16*)(((int)self + 0x414)), 0, 1, 0x500, 0x500);

second:
    ApproachAngle((s16*)(self + 0x8c), *(s16*)(self + 0x414), *p4, *p6, *p8);
    *(s16*)(self + 0x8e) = *(s16*)(self + 0x94);
}
}

// @symbol func_ov081_021243cc
extern "C" void func_ov081_021243cc(void* self)
{
    u8* c = (u8*)self;
    Vector3 v;
    v.x = data_ov081_02128998.x;
    v.y = data_ov081_02128998.y;
    v.z = data_ov081_02128998.z;
    _ZN10dCcAcPos_c21SetPosRelativeToActorERK7Vector3((void*)(c+0x110), &v);

    u32 id = *(u32*)(c+0x134);
    if (id == 0) return;
    void* found = _ZN8dActor_c10FindWithIDEj(id);
    if (found == 0) return;
    u8* f = (u8*)found;

    int hit;
    s32 flags = *(s32*)(c+0x130);
    hit = 0;

    if (flags & 0x2000) {
        *(s32*)(c+0x10c) = 2;
        func_ov002_020aea30(self, found, (void*)hit);
        *(u16*)(c+0x94) = (u16)(_ZN8dActor_c18HorzAngleToCPlayerEv(self) + 0x8000);
        hit = 1;
    }
    if (flags & 0x40000) {
        func_02012694(0xdb, (void*)(c+0x74));
        hit = 1;
        func_ov081_02125488(self, &data_ov081_02128e24);
    }
    int isbf = (int)(*(u16*)(f+0xc) == 0xbf);
    if (isbf) {
        if (*(u8*)(f+0x6fb) != 0) return;
        if (*(u8*)(f+0x6f9) == 1) {
            *(s32*)(c+0x10c) = 2;
            func_ov002_020aea30(self, found, 0);
            *(u16*)(c+0x94) = (u16)(_ZN8dActor_c18HorzAngleToCPlayerEv(self) + 0x8000);
            hit = 1;
        }
        if (flags & 0x10) {
            Vector3_16 vv;
            vv.x = (s16)-0x1200;
            vv.y = 0;
            vv.z = 0;
            _ZN12dEnemyBase_c20KillByInvincibleCharERK10Vector3_16R6Player5Fix12IiE(self, &vv, found);
            func_02012694(0x1d, (void*)(c+0x74));
            hit = 1;
        }
        if ((flags & 0x40) && *(s32*)(f+8) == 2) {
            *(s32*)(c+0x10c) = 2;
            func_ov002_020aea30(self, found, 0);
            *(u8*)(c+0x468) = 2;
            *(u16*)(c+0x94) = (u16)(_ZN8dActor_c18HorzAngleToCPlayerEv(self) + 0x8000);
            hit = 1;
        }
        if (hit == 0) {
            Vector3 hv;
            hv.x = *(s32*)(c+0x5c);
            hv.y = *(s32*)(c+0x60);
            hv.z = *(s32*)(c+0x64);
            _ZN6Player4HurtERK7Vector3j5Fix12IiEjjj(found, &hv, 2, 0xc000, 1, 0, 1);
        }
    }
    if (hit != 1) return;
    func_ov081_02124134((char *)self);
}

// @symbol func_ov081_021245e8
extern "C" {  /* .c-derived member: C linkage for the whole block */
int func_ov081_021245e8(void* thiz)
{
    char* sl = (char*)thiz;
    int min = 0x2710000;
    int i = 0;
    Vector3 v;
    *(int*)(sl + 0x40c) = -1;
    if ((int)data_0209f21c[0] > 0) {
        do {
            char* obj = data_0209f394[i];
            if (obj != 0) {
                int dist;
                int* s = (int*)(((long long)(obj + 0x5c)));
                v.x = s[0];
                v.y = s[1];
                v.z = s[2];
                dist = Vec3_Dist((Vector3*)(sl + 0x5c), &v);
                if (i == 0) {
                    min = dist;
                    *(int*)(sl + 0x40c) = 0;
                } else if (dist < min) {
                    min = dist;
                    *(int*)(sl + 0x40c) = i;
                }
            }
            i++;
        } while (i < (int)data_0209f21c[0]);
    }
    return min;
}
}

// @symbol func_ov081_021246a0
extern "C" {  /* .c-derived member: C linkage for the whole block */
int func_ov081_021246a0(char* c)
{
    Vector3 v;
    if (*(int*)(c + 0x41c) != 0 || _ZNK10dBgCh_Actr10IsOnGroundEv(c + 0x150) != 0) {
        _Z14ApproachLinearRiii((int*)(c + 0x80), 0x1700, 0x50);
        _Z14ApproachLinearRiii((int*)(c + 0x88), 0x1700, 0x50);
        _Z14ApproachLinearRiii((int*)(c + 0x84), 0, 0x50);
        _Z14ApproachLinearRiii((int*)(c + 0x45c), -0x4000, 0x199);
        if (*(u16*)(c + 0x100) == 0) *(u16*)(c + 0x100) = 0x14;
        if (*(int*)(c + 0x84) < 0x50) {
            if (*(u8*)(c + 0x469) == 0) {
                v.x = *(int*)(c + 0x5c);
                v.y = *(int*)(c + 0x60);
                v.z = *(int*)(c + 0x64);
                _ZN8dActor_c10SpawnCoinsERK7Vector3j5Fix12IiEs(c, &v, *(u8*)(c + 0x10a) + 1, 0xa000, 0);
            }
            func_ov081_02124134(c);
            _ZN8dActor_c24KillAndTrackInDeathTableEv(c);
        }
    }
    return 1;
}
}

// @symbol func_ov081_0212479c
extern "C" int func_ov081_0212479c(char *self)
{
    *(short*)(self + 0x414) = 0;
    *(int*)(self + 0x410) = 0;
    *(short*)(self + 0x100) = 0;
    if (*(int*)(self + 0x41c) == 0)
        *(int*)(self + 0x9c) = -0x2000;
    if (*(int*)(self + 0x400) != 0) {
        dActor_c *a = dActor_c::FindWithID(*(int*)(self + 0x400));
        if (a != 0) {
            char *t = (char*)a;
            *(int*)(t + 0x9c) = -0x2000;
            int rv = ((unsigned int)RandomIntInternal(&data_0209e650) >> 8) & 0xf;
            *(short*)(t + 0x92) = 0;
            *(short*)(t + 0x94) = rv << 0xc;
            *(short*)(t + 0x96) = 0;
            *(int*)(t + 0x98) = 0xa000;
            *(int*)(t + 0xa4) = 0;
            *(int*)(t + 0xa8) = 0x14000;
            *(int*)(t + 0xac) = 0;
            *(int*)(t + 0xc8) = 0;
        }
        func_02012790(0xa);
        *(int*)(self + 0x400) = 0;
    }
    if (*(int*)(self + 0x41c) == 2)
        dActor_c::Spawn(0xdf, 0x300, *(Vector3*)(self + 0x44c), 0,
                     *(signed char*)(self + 0xcc), -1);
    return 1;
}

// @symbol func_ov081_02124894
extern "C" {  /* .c-derived member: C linkage for the whole block */
int func_ov081_02124894(char* c)
{
    Vector3 v;
    /* Source written as (>0 ? sub : add) so mwccarm inversion emits the
       ROM's le/add arm first, then the unconditional sub arm. */
    if (*(int*)(c + 0x408) > 0)
        *(s16*)(((int)c + 0x414)) =
            *(s16*)(((int)c + 0x414)) - 0x200;
    else
        *(s16*)(((int)c + 0x414)) =
            *(s16*)(((int)c + 0x414)) + 0x200;

    {
        s16 *ang = (s16*)(((int)c + 0x94));
        *ang = *ang + *(s16*)((c + 0x400) + 0x14);
    }
    ApproachAngle((s16*)(c + 0x8c), -0x2800, 1, 0x500, 0x500);
    {
        int *p = (int*)(((int)c + 0x410));
        *p = *p + 1;
    }
    if (*(int*)(c + 0x410) <= 0x28) goto done;
    if (*(u8*)(c + 0x469) == 0) {
        v.x = *(int*)(c + 0x5c);
        v.y = *(int*)(c + 0x60);
        v.z = *(int*)(c + 0x64);
        _ZN8dActor_c10SpawnCoinsERK7Vector3j5Fix12IiEs(c, &v, *(u8*)(c + 0x10a) + 1, 0xa000, 0);
    }
    func_ov081_02124134(c);
    _ZN8dActor_c24KillAndTrackInDeathTableEv(c);
done:
    return 1;
}
}

// @symbol func_ov081_0212498c
extern "C" {  /* .c-derived member: C linkage for the whole block */
int func_ov081_0212498c(char *c){
 int id=*(int*)(c+0x3fc);
 if(id!=0){
   char *a=(char*)_ZN8dActor_c10FindWithIDEj(id);
   if(a!=0){
     *(int*)(a+0x9c) = -0x2000;
     *(int*)(a+0xa0) = -0x28000;
     *(int*)(c+0x3fc)=0;
   }
 }
 func_02012694(0xdb, c+0x74);
 *(short*)(c+0x414)=0;
 *(int*)(c+0x410)=0;
 return 1;
}
}

// @symbol func_ov081_021249f4
extern "C" {  /* .c-derived member: C linkage for the whole block */
int func_ov081_021249f4(char *c)
{
    struct Vector3 pos;
    void *cb;
    int t;

    pos.x = *(int *)(c + 0x44c);
    pos.y = *(int *)(c + 0x450);
    pos.z = *(int *)(c + 0x454);
    cb = 0;
    *(unsigned *)(c + 0x460) =
        _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
            *(unsigned *)(c + 0x460), 0x11d, pos.x, pos.y, pos.z, 0, cb ? &pos : 0);
    pos.y = pos.y + 0x1e000;
    *(unsigned *)(c + 0x464) =
        _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
            *(unsigned *)(c + 0x464), 0x11e, pos.x, pos.y, pos.z, 0, cb ? &pos : 0);

    if (*(int *)(c + 0x450) > *(int *)(c + 0x60)) {
        char *b = c + 0x400;
        ApproachAngle((short *)(c + 0x8c), *(short *)(b + 0x14), 1, 0x1000, 0x1000);
    }
    t = *(int *)(c + 0x450) - 0x118000;
    if (t > *(int *)(c + 0x60)) {
        *(int *)(c + 0x60) = t;
        *(int *)(c + 0xa8) = 0;
        *(int *)(c + 0x9c) = 0;
        func_ov081_02125488(c, data_ov081_02128e84);
    }
    {
        short *ang = (short *)(c + 0x94);
        *ang = (short)(*ang + 0x2000);
        *(short *)(c + 0x8e) = *(short *)(c + 0x94);
    }
    return 1;
}
}

// @symbol func_ov081_02124b08
extern "C" {  /* .c-derived member: C linkage for the whole block */
int func_ov081_02124b08(char *c)
{
    unsigned int id = *(unsigned int *)(c + 0x3fc);
    if (id != 0) {
        char *a = (char *)_ZN8dActor_c10FindWithIDEj(id);
        if (a != 0) {
            int n = 0x2000;
            *(int *)(a + 0x9c) = -n;
            n = 0x28000;
            *(int *)(a + 0xa0) = -n;
            *(int *)(c + 0x3fc) = 0;
        }
    }
    {
        int z = 0;
        int n;
        *(int *)(c + 0xa8) = 0xa000;
        n = 0x4000;
        *(int *)(c + 0x9c) = -n;
        {
            char *base = c + 0x400;
            *(short *)(base + 0x14) = z;
        }
        _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(
            c + 0x30c, *(void **)((char *)&data_ov081_02128da8 + 4), 0, 0x1000, z);
    }
    return 1;
}
}

// @symbol func_ov081_02124b98
extern "C" int func_ov081_02124b98(char* c) {
    Vector3 in, out, v[2];
    void* target;
    void* player;

    if (*(unsigned int*)(c + 0x3fc) != 0) {
        target = _ZN8dActor_c10FindWithIDEj(*(unsigned int*)(c + 0x3fc));
        if (target != 0) {
            *(int*)((char*)target + 0x5c) = *(int*)(c + 0x434);
            *(int*)((char*)target + 0x60) = *(int*)(c + 0x438);
            *(int*)((char*)target + 0x64) = *(int*)(c + 0x43c);
            if (((daSnowman_c *)c)->mModelAnim.WillHitFrame(0xa) != 0) {
                in.x = 0; in.y = 0; in.z = 0x1e000;
                out.x = 0; out.y = 0; out.z = 0;
                v[0].x = 0; v[0].y = 0; v[0].z = 0;
                player = _ZN8dActor_c13ClosestPlayerEv(c);
                if (player != 0) {
                    int angle;
                    int* q = (int*)(((int)player + 0x5c));
                    v[1].x = q[0];
                    v[1].y = q[1];
                    v[1].z = q[2];
                    v[0].x = v[1].x - *(int*)(c + 0x434);
                    v[0].y = v[1].y - *(int*)(c + 0x438);
                    v[0].z = v[1].z - *(int*)(c + 0x43c);
                    angle = _ZN4cstd5atan2E5Fix12IiES1_(v[0].x, v[0].z);
                    Matrix4x3_FromRotationY(&data_020a0e68, angle);
                    Matrix4x3_ApplyInPlaceToRotationX(&data_020a0e68,
                        (short)(-_ZN4cstd5atan2E5Fix12IiES1_(v[0].y, Vec3_HorzLen(&v[0]))));
                    MulVec3Mat4x3(&in, &data_020a0e68, &out);
                }
                out.y += 0x14000;
                *(int*)((char*)target + 0xa4) = out.x;
                *(int*)((char*)target + 0xa8) = out.y;
                *(int*)((char*)target + 0xac) = out.z;
                *(int*)((char*)target + 0x9c) = -0x2000;
                *(unsigned int*)(c + 0x3fc) = 0;
            }
        }
    }
    if (_ZN9Animation8FinishedEv(c + 0x35c) != 0) {
        func_ov081_02125488(c, &data_ov081_02128e14);
    }
    return 1;
}

// @symbol func_ov081_02124d14
/* Signature deliberately copied from the local declaration above: the
   ROM name carries by-value class parameters (e.g. Fix12<int>), which
   mwccarm passes differently at the call site, so declaring the true
   types breaks the byte match. See notes/mwccarm-codegen.md 6az. */
extern "C" int func_ov081_02124d14(char *c) {
    unsigned int flags = 0;
    BCA_File *file = (BCA_File *)(((int *)&data_ov081_02128db8)[1]);
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj((ModelAnim *)(c + 0x30c), file, 0x40000000, 0x1000, flags);
    return 1;
}

// @symbol func_ov081_02124d50
extern "C" int func_ov081_02124d50(char* c)
{
    char* r5 = (char*)dActor_c::FindWithID(*(unsigned int*)(c + 0x3fc));
    if (r5 != 0 && *(int*)(r5 + 0x9c) == 0) {
        func_ov081_0212423c(c, 1);
        *(int*)(r5 + 0x5c) = *(int*)(c + 0x434);
        *(int*)(r5 + 0x60) = *(int*)(c + 0x438);
        *(int*)(r5 + 0x64) = *(int*)(c + 0x43c);
    }

    if (*(unsigned short*)(c + 0x100) == 0) {
        func_ov081_02125488(c, data_ov081_02128e44);
        return 1;
    }

    if (func_ov081_021245e8(c) > 0x320000) {
        func_ov081_02125488(c, data_ov081_02128e64);
    }
    return 1;
}

// @symbol func_ov081_02124dfc
extern "C" {  /* .c-derived member: C linkage for the whole block */
int func_ov081_02124dfc(SnowSpawnView *self)
{
    dActor_c *a = (dActor_c *)_ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as(
        0xe0, 0, &self->pos, (const Vector3_16*)0, (s32)self->areaID, -1);
    if (a)
        self->uniqueID = *(u32*)((char*)a + 4);
    *(s16*)((char*)self + 0x100) = 0x64;
    self->f408 = 0;
    return 1;
}
}

// @symbol func_ov081_02124e64
extern "C" {  /* .c-derived member: C linkage for the whole block */
int func_ov081_02124e64(char *c){
  func_ov081_0212423c(c, 0);
  if(*(unsigned short*)(c+0x100)==0)
    func_ov081_02125488(c, data_ov081_02128e34);
  if(func_ov081_021245e8(c) > 0x320000)
    func_ov081_02125488(c, data_ov081_02128e64);
  return 1;
}
}

// @symbol func_ov081_02124ec0
extern "C" {  /* .c-derived member: C linkage for the whole block */
int func_ov081_02124ec0(char *p) {
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(p+0x30c, (void*)*(void **)((char *)&data_ov081_02128d98 + 4), 0, 0x1000, 0);
    if (*(int*)(p+0x41c) == 2)
        *(int*)(p+0xb0) = 0x18000002;
    else
        *(int*)(p+0xb0) = 0x10000002;
    *(short*)(p+0x100) = 0x14;
    return 1;
}
}

// @symbol func_ov081_02124f20
extern "C" {
int func_ov081_02124f20(char *c){
  if(*(int*)(c+0xa8) < 0){
    if(*(int*)(c+0x450) > *(int*)(c+0x60)){
      *(int*)(c+0xa8)=0;
      *(int*)(c+0x9c)=0;
      *(int*)(c+0x60)=*(int*)(c+0x450);
      func_ov081_02125488(c, &data_ov081_02128e14);
    }
  }
  func_ov081_0212423c(c, 0);
  return 1;
}
}

// @symbol func_ov081_02124f7c
extern "C" {  /* .c-derived member: C linkage for the whole block */
int func_ov081_02124f7c(char *thiz)
{
    int n;
    struct Vector3 pos;
    void *cb;

    *(int *)(thiz + 0xa8) = 0x3c000;
    n = 0x4000;
    *(int *)(thiz + 0x9c) = -n;
    func_02012694(0xdc, thiz + 0x74);
    pos.x = *(int *)(thiz + 0x44c);
    pos.y = *(int *)(thiz + 0x450);
    pos.z = *(int *)(thiz + 0x454);
    cb = 0;
    *(unsigned *)(thiz + 0x460) =
        _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
            *(unsigned *)(thiz + 0x460), 0x11a, pos.x, pos.y, pos.z, 0,
            cb ? &pos : 0);
    pos.y = pos.y + 0x1e000;
    *(unsigned *)(thiz + 0x464) =
        _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
            *(unsigned *)(thiz + 0x464), 0x11b, pos.x, pos.y, pos.z, 0,
            cb ? &pos : 0);
    return 1;
}
}

// @symbol func_ov081_02125038
extern "C" {
int func_ov081_02125038(char* c){
  if(func_ov081_021245e8(c) < 0x258000)
    func_ov081_02125488(c, &data_ov081_02128ea4);
  return 1;
}
}

// @symbol func_ov081_02125068
/* Signature deliberately copied from the local declaration above: the
   ROM name carries by-value class parameters (e.g. Fix12<int>), which
   mwccarm passes differently at the call site, so declaring the true
   types breaks the byte match. See notes/mwccarm-codegen.md 6az. */
extern "C" int func_ov081_02125068(char *c)
{
    int v = *(int *)(c + 0x41c);
    if (v != 2 && v != 3) {
        *(int *)(c + 0xb0) = 3;
    } else if (v == 2) {
        *(int *)(c + 0xb0) = 0x8000002;
    }
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj((ModelAnim *)(c + 0x30c), (BCA_File *)*(void **)((char *)&data_ov081_02128d98 + 4), 0, 0x1000, 0);
    return 1;
}

// @symbol func_ov081_021250c8
/* func_ov081_021250c8 at 0x021250c8
 *
 * Matched byte-for-byte with mwccarm 1.2/sp2p3 (ov081).
 */
extern "C" {  /* .c-derived member: C linkage for the whole block */
int func_ov081_021250c8(char *c) {
    struct SnowPath p;
    struct Vector3 node;
    struct Vector3 diff;
    struct Vector3 scaled;
    int len;

    if (_ZNK10dBgCh_Actr10IsOnGroundEv(c + 0x150)) {
        func_02012694(0xe5, c + 0x74);
        func_ov081_02125488(c, data_ov081_02128e54);
        _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x30c, *(void **)((char *)&data_ov081_02128da0 + 4), 0x40000000, 0x1000, 0);
        return 1;
    }

    _ZN7PathPtrC1Ev(&p);
    _ZN7PathPtr6FromIDEj(&p, *(unsigned int*)(c + 0x418));
    _ZNK7PathPtr7GetNodeER7Vector3j(&p, &node, *(unsigned int*)(c + 0x424));
    node.y = *(int*)(c + 0x60);
    Vec3_Sub(&diff, (struct Vector3*)(c + 0x5c), &node);
    len = LenVec3(&diff);
    ApproachAngle(c + 0x94, Vec3_HorzAngle((struct Vector3*)(c + 0x5c), &node), 1, 0x1000, 0x500);
    if (len == 0) goto epi;
    if (len > *(int*)(c + 0x458)) goto work;
epi:
    return 1;
work:
    {
        int q = _ZN4cstd4fdivEii(*(int*)(c + 0x458), len);
        Vec3_MulScalar(&scaled, &diff, q);
        SubVec3((struct Vector3*)(c + 0x5c), &scaled, (struct Vector3*)(c + 0x5c));
    }
    return 1;
}
}

// @symbol func_ov081_02125200
extern "C" {  /* .c-derived member: C linkage for the whole block */
int func_ov081_02125200(void)
{
    return 1;
}
}

// @symbol func_ov081_02125208
extern "C" {  /* .c-derived member: C linkage for the whole block */
int func_ov081_02125208(char *c) {
    struct SnowPath p;
    struct Vector3 node;
    int st;
    int z;
    int n;

    if (*(unsigned short*)(c + 0x100) != 0) {
        goto exit;
    }

    if (*(int*)(c + 0x408) == 1) {
        *(int*)(c + 0xa8) = 0x14000;
        n = 0x4000;
        *(int*)(c + 0x9c) = -n;
        *(int*)(c + 0x408) = 2;
        func_02012694(0xdd, c + 0x74);
    }

    _ZN7PathPtrC1Ev(&p);
    _ZN7PathPtr6FromIDEj(&p, *(unsigned int*)(c + 0x418));
    _ZNK7PathPtr7GetNodeER7Vector3j(&p, &node, *(unsigned int*)(c + 0x424));
    ApproachAngle(c + 0x94, Vec3_HorzAngle((struct Vector3*)(c + 0x5c), &node), 1, 0x1000, 0x500);

    if (AngleDiff(*(short*)(c + 0x94), Vec3_HorzAngle((struct Vector3*)(c + 0x5c), &node)) >= 0x100) {
        goto exit;
    }

    if (!_ZNK10dBgCh_Actr10IsOnGroundEv(c + 0x150)) {
        goto exit;
    }

    st = *(int*)(c + 0x408);
    if (st == 0) {
        goto label_118;
    }
    if (st != 1) {
        goto label_ec;
    }

    func_02012694(0xe5, c + 0x74);

label_ec:
    {
        int *pState = (int*)(((int)c + 0x408));
        *pState = *pState + 1;
        if (*(int*)(c + 0x408) < 0xb) {
            return 1;
        }
    }

label_118:
    z = 0;
    n = 0x4000;
    *(int*)(c + 0x408) = z;
    *(int*)(c + 0xa8) = 0x3a000;
    *(int*)(c + 0x9c) = -n;
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x30c, *(void **)((char *)&data_ov081_02128d88 + 4), 0x40000000, 0x1000, z);
    func_02012694(0xdd, c + 0x74);
    func_ov081_02125488(c, data_ov081_02128e74);

exit:
    return 1;
}
}

// @symbol func_ov081_0212538c
extern "C" {  /* .c-derived member: C linkage for the whole block */
int func_ov081_0212538c(char *c)
{
    struct SnowPath pp;
    struct Vector3 node;
    struct Vector3 diff;
    int len;

    _ZN7PathPtrC1Ev(&pp);
    _ZN7PathPtr6FromIDEj(&pp, *(unsigned int *)(c + 0x418));
    _ZNK7PathPtr7GetNodeER7Vector3j(&pp, &node, *(unsigned int *)(c + 0x424));
    node.y = *(int *)(c + 0x60);
    Vec3_Sub(&diff, (struct Vector3 *)(c + 0x5c), &node);
    len = LenVec3(&diff);
    *(int *)(c + 0x458) = 0xa000;
    *(int *)(c + 0x408) = 0;
    if (len == 0 || len <= *(int *)(c + 0x458)) {
        *(int *)(c + 0x5c) = node.x;
        *(int *)(c + 0x60) = node.y;
        *(int *)(c + 0x64) = node.z;
        (*(int *)(c + 0x424))++;
        if (*(int *)(c + 0x424) >= *(int *)(c + 0x420))
            *(int *)(c + 0x424) = 0;
        *(int *)(c + 0x408) = 1;
    }
    *(short *)(c + 0x100) = 0xa;
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(
        c + 0x30c, *(void **)((char *)&data_ov081_02128d98 + 4), 0, 0x1000, 0);
    return 1;
}
}

// @symbol func_ov081_02125488
extern "C" int func_ov081_02125488(void *cv, void *pv)
{
    C *c = (C *)cv;
    PMF *p = (PMF *)pv;
    c->pp = p;
    PMF *q = c->pp;
    if (*q == 0)
        return 1;
    return (c->**q)();
}

// @symbol func_ov081_021254d8
extern "C" void func_ov081_021254d8(char *c)
{
    int src[3], dst[3];
    int t;
    void *actor;

    ((Obj*)(c + 0x30c))->v3();

    src[0] = *(int*)(c + 0x5c);
    t = *(int*)(c + 0x60);
    src[1] = t;
    src[2] = *(int*)(c + 0x64);
    src[1] = t + *(int*)(c + 0x45c);
    Vec3_Asr(dst, src, 3);
    Matrix4x3_FromTranslation(&data_020a0e68, dst[0], dst[1], dst[2]);

    Matrix4x3_ApplyInPlaceToRotationXYZExt(&data_020a0e68,
        *(short*)(c + 0x8c), *(short*)(c + 0x8e), *(short*)(c + 0x90));
    *(struct Matrix4x3*)(c + 0x328) = data_020a0e68;

    if (*(unsigned int*)(c + 0x400) != 0) {
        *(int*)(c + 0x440) = 0;
        *(int*)(c + 0x444) = 0;
        *(int*)(c + 0x448) = 0;
        actor = (void*)_ZN8dActor_c10FindWithIDEj(*(unsigned int*)(c + 0x400));
        if (actor != 0) {
            MulMat4x3Mat4x3(*(char**)(c + 0x320) + 0xf0, c + 0x328, c + 0x3c8);

            *(int*)(c + 0x440) = data_020a0e68.m[9];
            *(int*)(c + 0x444) = data_020a0e68.m[10];
            *(int*)(c + 0x448) = data_020a0e68.m[11];
            *(int*)(((int)c + 0x440)) <<= 3;
            *(int*)(((int)c + 0x444)) <<= 3;
            *(int*)(((int)c + 0x448)) <<= 3;
            *(int*)((char*)actor + 0x5c) = *(int*)(c + 0x440);
            *(int*)((char*)actor + 0x60) = *(int*)(c + 0x444);
            *(int*)((char*)actor + 0x64) = *(int*)(c + 0x448);

            Matrix4x3_FromTranslation(&data_020a0e68, 0, 0x4000, 0);
            Matrix4x3_ApplyInPlaceToRotationXYZExt(&data_020a0e68, 0, 0x2000, 0);
            MulMat4x3Mat4x3(&data_020a0e68, c + 0x3c8, c + 0x3c8);
            *(void**)((char*)actor + 0xc8) = c + 0x3c8;
        }
    }

    *(int*)(c + 0x434) = 0;
    *(int*)(c + 0x438) = 0;
    *(int*)(c + 0x43c) = 0;
    data_020a0e68 = *(struct Matrix4x3*)(c + 0x328);
    MulMat4x3Mat4x3(*(char**)(c + 0x320) + 0x90, &data_020a0e68, &data_020a0e68);
    Matrix4x3_ApplyInPlaceToTranslation(&data_020a0e68, 0xc000, -0x1000, 0);

    *(int*)(c + 0x434) = data_020a0e68.m[9];
    *(int*)(c + 0x438) = data_020a0e68.m[10];
    *(int*)(c + 0x43c) = data_020a0e68.m[11];
    *(int*)(((int)c + 0x434)) <<= 3;
    *(int*)(((int)c + 0x438)) <<= 3;
    *(int*)(((int)c + 0x43c)) <<= 3;

    if (*(int*)(c + 0x41c) != 0)
        return;

    Matrix4x3_FromTranslation(&data_020a0e68,
        *(int*)(c + 0x5c) >> 3,
        (*(int*)(c + 0x60) - 0xe000) >> 3,
        *(int*)(c + 0x64) >> 3);
    *(struct Matrix4x3*)(c + 0x398) = data_020a0e68;
    _ZN8dActor_c19DropShadowRadHeightER11ShadowModelR9Matrix4x35Fix12IiES5_j(
        c, c + 0x370, c + 0x398, 0x78000, 0xc8000, 0xf);
}

// @symbol _ZN11daSnowman_c16CleanupResourcesEv
int daSnowman_c::CleanupResources()
{
    data_ov081_02128d90.Release();
    data_ov081_02128db0.Release();
    data_ov081_02128d98.Release();
    data_ov081_02128db8.Release();
    data_ov081_02128da8.Release();
    data_ov081_02128d88.Release();
    data_ov081_02128da0.Release();
    return 1;
}

// @symbol _ZN11daSnowman_c16OnPendingDestroyEv
void daSnowman_c::OnPendingDestroy()
{
}

// @symbol _ZN11daSnowman_c6RenderEv
int daSnowman_c::Render()
{
  int s=mType;
  if(s==3) return 1;
  if(s==2){
    if(mCapUniqueID)
      mModelAnim.HideMaterial(0,2);
    else
      mModelAnim.ShowMaterial(0,2);
  }
  _ZN5Model6RenderEPK7Vector3(((char *)this)+0x30c, ((char *)this)+0x80);
  return 1;
}

// @symbol _ZN11daSnowman_c8BehaviorEv
int daSnowman_c::Behavior()
{
    char* c = (char*)((C*)this);
    void* r5;
    char* p;
    if (mType == 3) {
        switch (*(unsigned char*)(c + 0x469)) {
        case 0:
            if (SaveData::HasPlayerLostCap()) *(unsigned char*)(c + 0x469) = 1;
            else *(unsigned char*)(c + 0x469) = 2;
            break;
        case 1:
            if (!SaveData::HasPlayerLostCap()) *(unsigned char*)(c + 0x469) = 2;
            break;
        case 2:
            if (SaveData::HasPlayerLostCap()) mType = 2;
            break;
        }
        return 1;
    }
    if (_ZN12dEnemyBase_c26UpdateKillByInvincibleCharER10dBgCh_ActrR9ModelAnimj(c, c + 0x150, c + 0x30c, 3)) return 1;
    if (*(int*)(c + 0x10c) != 0) {
        if (_ZN12dEnemyBase_c11UpdateDeathER10dBgCh_Actr(c, c + 0x150) && mType == 2) {
            _ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as(0xdf, 0x300, &mHomePos, 0, *(signed char*)(c + 0xcc), -1);
            mType = 0;
        }
        if (*(int*)(c + 0x10c) == 0 && *(unsigned char*)(c + 0x468) != 0) {
            func_02012694(0x166, c + 0x74);
            *(unsigned char*)(c + 0x468) = 0;
        }
        func_ov081_021254d8(c);
        return 1;
    }
    if (mType == 2
        && (char*)((C*)this)->pp != (char *)&data_ov081_02128e94
        && (char*)((C*)this)->pp != (char *)&data_ov081_02128e24
        && SaveData::HasPlayerLostCap()
        && mCapUniqueID == 0) {

        p = (char*)_ZN8dActor_c13ClosestPlayerEv(c);
        if (p != 0) {
            int param = 0xc;
            param = param | (*(unsigned char*)(p + 0x6d9) << 8);
            r5 = (void*)_ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as(
                0x10d, param, (Vector3*)(c + 0x5c), 0, *(signed char*)(c + 0xcc), -1);
            if (r5 != 0) {
                _ZN8dActor_c9SetRangesE5Fix12IiES1_S1_S1_(r5, 0x64000, 0xc8000, 0x1000000, 0x1000000);
                mCapUniqueID = *(int*)((char*)r5 + 4);
            }
        }

    }
    *(short*)(c + 0x8c) = *(short*)(c + 0x92);
    *(short*)(c + 0x8e) = *(short*)(c + 0x94);
    *(short*)(c + 0x90) = *(short*)(c + 0x96);
    DecIfAbove0_Short((unsigned short*)(c + 0x100));
    if (*(void**)((char*)((C*)this)->pp + 8) != 0) {
        PMF* p = ((C*)this)->pp + 1;
        (((C*)this)->**p)();
    }
    _ZN8dActor_c9UpdatePosEP5dCc_c(c, c + 0x110);
    if (mType == 0)
        _ZN12dEnemyBase_c12UpdateWMClsnER10dBgCh_Actrj(c, c + 0x150, 0);
    func_ov081_021254d8(c);
    if ((char*)((C*)this)->pp != (char *)&data_ov081_02128e84
        && (char*)((C*)this)->pp != (char *)&data_ov081_02128e64
        && (char*)((C*)this)->pp != (char *)&data_ov081_02128e94
        && (char*)((C*)this)->pp != (char *)&data_ov081_02128e24)
        func_ov081_021243cc(c);
    _ZN5dCc_c5ClearEv(c + 0x110);
    {
        p = (char*)_ZN8dActor_c13ClosestPlayerEv(c);
        if (p != 0 && *(unsigned char*)(p + 0x6fb) == 0)
            _ZN5dCc_c6UpdateEv(c + 0x110);
    }
    mModelAnim.speed = 0x1000;
    _ZN9Animation7AdvanceEv(c + 0x35c);
    return 1;
}

// @symbol _ZN11daSnowman_c13InitResourcesEv
int daSnowman_c::InitResources()
{
    Vector3 v;

    _ZN9ModelBase7SetFileEP8BMD_Fileii(((char *)this) + 0x30c,
        _ZN5Model8LoadFileER13SharedFilePtr(&data_ov081_02128db0), 1, -1);
    _ZN5Model8LoadFileER13SharedFilePtr(&data_ov081_02128d90);
    _ZN11ShadowModel12InitCylinderEv((char *)&(*(u8 *)&mShadowModel));
    _ZN9Animation8LoadFileER13SharedFilePtr(&data_ov081_02128d98);
    _ZN9Animation8LoadFileER13SharedFilePtr(&data_ov081_02128db8);
    _ZN9Animation8LoadFileER13SharedFilePtr(&data_ov081_02128da8);
    _ZN9Animation8LoadFileER13SharedFilePtr(&data_ov081_02128d88);
    _ZN9Animation8LoadFileER13SharedFilePtr(&data_ov081_02128da0);

    mPathId = (*(s32 *)&param1) & 0xff;
    mType = ((*(s32 *)&param1) & 0xff00) >> 8;
    if (mPathId == 0xff)
        mPathId = 0;
    if (mType == 0xff)
        mType = 0;

    mHomePos.x = mPosX;
    mHomePos.y = mPosY;
    mHomePos.z = mPosZ;

    if (_ZN8dActor_c18GetBitInDeathTableEv(((char *)this)) != 0) {
        if (mType == 2) {
            if (SaveData::HasPlayerLostCap() != 0) {
                _ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as(0xdf, 0x200,
                    &mHomePos, 0, mAreaId, -1);
            } else {
                _ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as(0xdf, 0x300,
                    &mHomePos, 0, mAreaId, -1);
            }
        }
        if (mType != 3)
            return 0;
    }

    mUniqueID_3fc = 0;
    mCapUniqueID = 0;

    if (mType == 0) {
        char pp[8];
        _ZN7PathPtrC1Ev(pp);
        _ZN7PathPtr6FromIDEj(pp, mPathId);
        mPathNodeCount = ((PathPtr *)pp)->NumNodes();
    }

    mScaleX = 0x1000;
    mScaleY = 0x1000;
    mScaleZ = 0x1000;
    mTerminalVelocity = -0xc8000;

    v.x = data_ov081_02128998.x;
    v.y = data_ov081_02128998.y;
    v.z = data_ov081_02128998.z;
    _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj(
        ((char *)this) + 0x110, ((char *)this), &v, 0x3c000, 0x96000, 0x200004, 0x42050);

    mAngleY = mPrevAngleY;
    mInitAngleY = mAngleY;
    _ZN10dBgCh_Actr4InitEP8dActor_c5Fix12IiES3_P10Vector3_16S5_(
        ((char *)this) + 0x150, ((char *)this), 0x14000, 0xf000, 0, 0);

    unk_108 = 1;
    unk_10a = 2;

    if (mType == 0) {
        char pp[8];
        _ZN7PathPtrC1Ev(pp);
        _ZN7PathPtr6FromIDEj(pp, mPathId);
        _ZNK7PathPtr7GetNodeER7Vector3j(pp, ((char *)this) + 0x5c, mPathNodeIndex);
        mPathNodeIndex = 1;
        mVertAccel = -0x2000;
        (*(s32 *)&mFlags) = 0x10000000;
        func_ov081_02125488(((char *)this), &data_ov081_02128e54);
    } else {
        *(s32 *)(((int)((char *)this) + 0x60)) -= 0x118000;
        func_ov081_02125488(((char *)this), &data_ov081_02128e84);
        if (mType == 3) {
            unk_108 = 0;
            unk_10a = 0;
            (*(s32 *)&mFlags) = 2;
        }
        if (mType == 2)
            (*(s32 *)&mFlags) = 0x8000002;
        else
            (*(s32 *)&mFlags) = 3;
    }

    return 1;
}

// @symbol _ZN11daSnowman_c16OnAimedAtWithEggEv
s32 daSnowman_c::OnAimedAtWithEgg() {
    return 622592;
}
