//cpp
/* Production translation unit for ov002/daObjPowerUpItem_c.
 * 18 function(s), .text 0x020b9148..0x020b9e0c. The power-flower pickup.
 *
 * NAME: _ZTS18daObjPowerUpItem_c is the cartridge type name; the tree's coined
 * spelling was PowerFlower (same vtable, ov002 0x02109800).
 *
 * The out-of-line destructor is the key function, so this TU emits _ZTV/_ZTI/
 * _ZTS. Under `#pragma defer_codegen off` it comes out D1 (0x020b9148), D0
 * (0x020b9198), then a D2 the cartridge has no home for; the same pragma lays
 * .text down in source order, so this file is ROM-ascending.
 * daObjPowerUpItem_c_classInit (0x020b9e0c) stays out of this TU.
 *
 * common.h comes before the class header so the flat Matrix4x3 stands. The
 * two matrix copies were matched against that spelling; Matrix4x3.t is not
 * used. The class header still precedes decl_common.h.
 */

#pragma defer_codegen off

#include "common.h"
#include "daObjPowerUpItem_c.h"
#include "SharedFilePtr.h"
#include "SaveData.h"
#include "fBase_c.h"
#include "dCc_c.h"
#include "decl_SaveData.h"
#include "decl_common.h"
#include "dBgCh_Gnd.h"

struct Vector3_16f;
struct Callback;
typedef struct { int x, y, z; } V3;
struct RG { char a[0x14]; int detect[15]; };

struct FlowerDispatch;
typedef void (FlowerDispatch::*FlowerPMF)();
struct FlowerEntry { FlowerPMF pmf[2]; int extra; };
extern FlowerEntry data_ov002_021097bc[];
struct FlowerDispatch { char pad[0x3c0]; int idx; };

int ApproachLinear(int&, int, int);
namespace cstd { int fdiv(int, int); }

extern "C" {
extern u8 DecIfAbove0_Byte(u8* p);
extern void _ZN7fBase_c18MarkForDestructionEv(void* p);
extern void* _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
    u32 id, u32 a, int x, int y, int z, const struct Vector3_16f* rot, struct Callback* cb);
extern signed short data_02082214[];
extern void _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(unsigned int, int, int, int);
extern void func_02012694(unsigned int id, const Vector3 *v);
extern void *data_0209f318;
extern void func_0203568c(int *p, int v);
extern void func_02035684(int *p, int v);
extern void dBgCh_Actr_UpdateContinuous_Veneer(void* p);
extern int _ZNK10dBgCh_Actr12TouchesWaterEv(void* self);
extern void *_ZN9dBgCh_GndC1Ev(struct RG*);
extern void _ZN9dBgCh_Gnd12SetObjAndPosERK7Vector3P8dActor_c(struct RG*, const Vector3*, void*);
extern int _ZN9dBgCh_Gnd10DetectClsnEv(struct RG*);
extern void _ZN9dBgCh_GndD1Ev(struct RG*);
extern void _ZN10dBgCh_Actr18StopDetectingWaterEv(void* self);
extern int _ZNK10dBgCh_Actr10IsOnGroundEv(void* self);
extern int func_0200fccc(char* s, int r1);
extern int _ZN6Player15IsCollectingCapEv(void* p);
extern void _ZN6Player16InitWingFeathersEb(void* p, int b);
extern void _ZN6Player16InitBalloonMarioEv(void* p);
extern void _ZN6Player14InitMetalWarioEv(void* p);
extern void _ZN6Player15InitVanishLuigiEv(void* p);
extern void _ZN6Player13InitFireYoshiEv(void* p);
extern int _ZN8dActor_c19DropShadowRadHeightER11ShadowModelR9Matrix4x35Fix12IiES5_j(
    char* self, ShadowModel* sm, struct Matrix4x3* m, int fix, int t, u32 f);
extern void Matrix4x3_FromRotationY(void* m, int angle);
extern void *gPFlowerCloseModelFile[];
extern void *gPFlowerOpenModelFile[];
extern int _ZN9ModelBase7SetFileEP8BMD_Fileii(void *self, void *f, int a, int b);
extern int _ZN11ShadowModel12InitCylinderEv(void *self);
extern void _ZN7dCcAc_c4InitEP8dActor_c5Fix12IiES3_jj(
    void *self, void *act, Fix12i a, Fix12i b, unsigned int c2, unsigned int d);
extern void _ZN10dBgCh_Actr4InitEP8dActor_c5Fix12IiES3_P10Vector3_16S5_(
    void *self, void *act, Fix12i a, Fix12i b, void *d, void *e);
extern void _ZN10dBgCh_Actr19StartDetectingWaterEv(void *self);
}

// @symbol _ZN18daObjPowerUpItem_cD1Ev
// @symbol _ZN18daObjPowerUpItem_cD0Ev
daObjPowerUpItem_c::~daObjPowerUpItem_c()
{
}

// @symbol func_ov002_020b91fc
extern "C" void func_ov002_020b91fc(char* c)
{
    int f;
    V3 pos;

    do {
        if (*(int*)(c + 8) == 0xffff) break;
        if (DecIfAbove0_Byte((u8*)(c + 0x3ca)) != 0) break;
        f = *(int*)(c + 0xb0);
        if ((int)((f & 0x40000) != 0) != 0) break;
        if ((int)((f & 0x20000) != 0) != 0) break;
        _ZN7fBase_c18MarkForDestructionEv(c);
    } while (0);

    {
        int z = *(int*)(c + 0x64);
        int x = *(int*)(c + 0x5c);
        int y = *(int*)(c + 0x60) + 0x82000;
        ((int*)&pos)[0] = x;
        ((int*)&pos)[1] = y;
        ((int*)&pos)[2] = z;
        *(void**)(c + 0x3c4) = _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
            *(u32*)(c + 0x3c4), 0x104,
            ((int*)&pos)[0], ((int*)&pos)[1], ((int*)&pos)[2],
            0, 0);
    }
}

// @symbol func_ov002_020b92b8
extern "C" void func_ov002_020b92b8(int *p)
{
    p[241] = 0;
}

// @symbol func_ov002_020b92c4
extern "C" void func_ov002_020b92c4(void* c) {
    if (DecIfAbove0_Byte((unsigned char*)((char*)c + 0x3cb))) {
        int a = (int)(*(unsigned char*)((char*)c + 0x3cb)) << 12;
        int fdivResult = cstd::fdiv(a, 0x1c000);
        unsigned short hw = *(unsigned short*)((char*)c + 0x3c8);
        int idx = hw >> 4;
        signed short odd = data_02082214[idx * 2 + 1];
        int t1 = (int)(((long long)odd * fdivResult + 0x800) >> 12);
        int u1 = (int)(((long long)t1 * 0x332 + 0x800) >> 12);
        int v1 = u1 + 0xffa;
        int w1 = (int)(((long long)v1 * 0xfa0 + 0x800) >> 12);
        *(int*)((char*)c + 0x84) = w1;
        signed short even = data_02082214[idx * 2];
        int t2 = (int)(((long long)even * fdivResult + 0x800) >> 12);
        int u2 = (int)(((long long)t2 * 0x332 + 0x800) >> 12);
        int v2 = u2 + 0xffa;
        int w2 = (int)(((long long)v2 * 0xfa0 + 0x800) >> 12);
        *(int*)((char*)c + 0x80) = w2;
        // materialized base for halfword at offset >= 0x100
        short* p = (short*)(((int)c + 0x3c8));
        *p = *p + 0x2000;
    } else {
        int ret = ApproachLinear(*(int*)((char*)c + 0x84), 0xfa0, 0x199);
        if (ret) {
            func_ov002_020b9704((char*)c, 2);
        }
    }
}

// @symbol func_ov002_020b9450
extern "C" void func_ov002_020b9450(char *c)
{
    Vector3 pos;
    int x = *(int *)(c + 0x5c);
    int y = *(int *)(c + 0x60) + 0x82000;
    int z = *(int *)(c + 0x64);
    ((int *)&pos)[0] = x;
    ((int *)&pos)[1] = y;
    ((int *)&pos)[2] = z;
    _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(
        0x102, ((int *)&pos)[0], ((int *)&pos)[1], ((int *)&pos)[2]);
    func_02012694(0x7d, (const Vector3 *)(c + 0x74));
    *(int *)(c + 0x3c4) = 0;
    *(short *)(c + 0x8e) = *(short *)((char *)data_0209f318 + 0x17c);
    *(char *)(c + 0x3cb) = 0x1b;
}

// @symbol func_ov002_020b94c4
extern "C" void func_ov002_020b94c4(char* c)
{
    struct RG rg;
    Vector3 pos;
    int a;
    int mag;
    int y;
    s16 delta;
    s16 X;
    int gy;
    int diff;

    *(u32*)(c + 0x3c4) = (u32)_ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
        *(u32*)(c + 0x3c4), 0x103, *(int*)(c + 0x5c), *(int*)(c + 0x60), *(int*)(c + 0x64), 0, 0);

    a = *(int*)(c + 0xa8);
    mag = (a < 0) ? -a : a;
    y = (int)(((s64)mag * 0x120000 + 0x800) >> 12);
    X = (s16)(y / 4096);
    delta = 0x250;
    if (X > 0)
        delta += X;
    if (a > 0)
        *(s16*)(c + 0x8e) += delta;
    else
        *(s16*)(c + 0x8e) -= delta;

    func_0203568c((int*)(c + 0x200), 0x3c000);
    func_02035684((int*)(c + 0x200), 0x3c000);
    ((dActor_c*)c)->UpdatePos((dCc_c*)(c + 0x1cc));
    dBgCh_Actr_UpdateContinuous_Veneer((void*)(c + 0x200));

    if (_ZNK10dBgCh_Actr12TouchesWaterEv((void*)(c + 0x200))) {
        pos.x = *(int*)(c + 0x5c);
        pos.y = *(int*)(c + 0x60);
        pos.z = *(int*)(c + 0x64);
        _ZN9dBgCh_GndC1Ev(&rg);
        _ZN9dBgCh_Gnd12SetObjAndPosERK7Vector3P8dActor_c(&rg, &pos, 0);
        if (_ZN9dBgCh_Gnd10DetectClsnEv(&rg)) {
            gy = rg.detect[12];
            pos.y = gy;
            diff = *(int*)(c + 0x60) - gy;
            if (diff < 0)
                diff = -diff;
            if (diff > 0x64000) {
                ((dActor_c*)c)->SmallPoofDust();
                _ZN7fBase_c18MarkForDestructionEv(c);
                _ZN9dBgCh_GndD1Ev(&rg);
                return;
            }
            _ZN10dBgCh_Actr18StopDetectingWaterEv((void*)(c + 0x200));
        } else {
            ((dActor_c*)c)->SmallPoofDust();
            _ZN7fBase_c18MarkForDestructionEv(c);
            _ZN9dBgCh_GndD1Ev(&rg);
            return;
        }
        _ZN9dBgCh_GndD1Ev(&rg);
        return;
    }

    if (!_ZNK10dBgCh_Actr10IsOnGroundEv((void*)(c + 0x200)))
        return;
    func_0200fccc(c, 1);
    func_ov002_020b9704(c, 1);
}

// @symbol func_ov002_020b96c0
extern "C" void func_ov002_020b96c0(char* c){
  func_02012694(0x7c, (const Vector3*)(c+0x74));
  *(int*)(c+0x3c4)=0;
  *(int*)(c+0x9c)=0xfffff998;
  *(int*)(c+0xa0)=-0xf000;
  *(int*)(c+0xa8)=0xd000;
}

// @symbol func_ov002_020b9704
extern "C" void func_ov002_020b9704(char *raw, int i) {
  FlowerDispatch *c = (FlowerDispatch *)raw;
  c->idx = i;
  int j = c->idx;
  (c->*data_ov002_021097bc[j].pmf[0])();
}

// @symbol func_ov002_020b9750
extern "C" void func_ov002_020b9750(char *raw) {
  FlowerDispatch *c = (FlowerDispatch *)raw;
  int j = c->idx;
  (c->*data_ov002_021097bc[j].pmf[1])();
}

// @symbol func_ov002_020b979c
extern "C" void func_ov002_020b979c(char* self) {
    char* other;
    u32 id = *(u32*)(self + 0x1f0);
    if (id == 0) return;

    other = (char*)dActor_c::FindWithID(id);
    if (other == 0) return;

    {
        int b = (int)(*(u16*)(other + 0xc) == 0xbf);
        if (b == 0) return;
    }

    if (_ZN6Player15IsCollectingCapEv(other) != 0) return;

    {
        char* p = *(char**)(other + 0x358);
        int t = (int)(p != 0);
        if (t != 0) {
            int b = (int)(*(u16*)(p + 0xc) == 0x10b);
            if (b != 0) return;
        }
    }

    {
        u32 flags = *(u32*)(self + 0xb0);
        int t = (int)((flags & 0x20000) != 0);
        if (t != 0) {
            *(u8*)(self + 0x3ca) = 0x64;
            return;
        }
    }

    switch (*(int*)(other + 8)) {
    case 0:
        if (*(int*)(self + 8) == 1) {
            _ZN6Player16InitWingFeathersEb(other, 1);
        } else {
            _ZN6Player16InitBalloonMarioEv(other);
        }
        _ZN7fBase_c18MarkForDestructionEv(self);
        return;
    case 2:
        _ZN6Player14InitMetalWarioEv(other);
        _ZN7fBase_c18MarkForDestructionEv(self);
        return;
    case 1:
        _ZN6Player15InitVanishLuigiEv(other);
        _ZN7fBase_c18MarkForDestructionEv(self);
        return;
    case 3:
        if (*(char**)(other + 0x360) != 0) {
            char* p = *(char**)(other + 0x360);
            if (*(u16*)(p + 0xc) == 0x10c) return;
        }
        _ZN6Player13InitFireYoshiEv(other);
        _ZN7fBase_c18MarkForDestructionEv(self);
        return;
    }
}

// @symbol func_ov002_020b993c
extern "C" int func_ov002_020b993c(char* c)
{
    int r3;
    int b = (int)((*(int*)(c + 0xb0) & 0x40000) != 0);
    if (b != 0) return b;
    *(struct Matrix4x3*)(c+0x19c) = *(struct Matrix4x3*)(c+0x140);
    *(int*)(c+0x1c4) = *(int*)(c+0x3bc) >> 3;
    r3 = 0x78000;
    if (*(int*)(c+0x3c0) == 0) {
        int d = *(int*)(c+0x60) - *(int*)(c+0x3bc);
        if (d <= 0x1000) d = 0x1000;
        r3 = 0x64000 - (int)(((s64)d * 0x180 + 0x800) >> 12);
        if (r3 < 0x3c000) r3 = 0x3c000;
    }
    return _ZN8dActor_c19DropShadowRadHeightER11ShadowModelR9Matrix4x35Fix12IiES5_j(c, (ShadowModel*)(c+0x174), (struct Matrix4x3*)(c+0x19c), r3, 0x3c000, 0xf);
}

// @symbol func_ov002_020b9a1c
extern "C" void func_ov002_020b9a1c(char* t){
  Matrix4x3_FromRotationY(t+0x140, *(short*)(t+0x8e));
  *(int*)(t+0x164) = *(int*)(t+0x5c) >> 3;
  *(int*)(t+0x168) = *(int*)(t+0x60) >> 3;
  *(int*)(t+0x16c) = *(int*)(t+0x64) >> 3;
  *(struct Matrix4x3*)(t+0xf0) = *(struct Matrix4x3*)(t+0x140);
}

// @symbol _ZN18daObjPowerUpItem_c16CleanupResourcesEv
s32 daObjPowerUpItem_c::CleanupResources()
{
    ((SharedFilePtr *)gPFlowerCloseModelFile)->Release();
    ((SharedFilePtr *)gPFlowerOpenModelFile)->Release();
    return 1;
}

// @symbol _ZN18daObjPowerUpItem_c6RenderEv
int daObjPowerUpItem_c::Render()
{
  int f = (int)((mFlags & 0x40000) != 0);
  if (f != 0) return 1;
  unsigned char st = mLifeTimer;
  if (st < 0x2d && (st & 1)) return 1;
  switch (mState) {
  case 0: mModel1.Render((const Vector3 *)&mScaleX); break;
  case 1: mModel2.Render((const Vector3 *)&mScaleX); break;
  case 2: mModel2.Render((const Vector3 *)&mScaleX); break;
  }
  return 1;
}

// @symbol _ZN18daObjPowerUpItem_c8BehaviorEv
int daObjPowerUpItem_c::Behavior()
{
    int b = (int)((mFlags & 0x40000) != 0);
    if (b != 0) return 1;
    mScaleX = 0xfa0;
    mScaleY = 0xfa0;
    mScaleZ = 0xfa0;
    func_ov002_020b9750(((char*)this));
    func_ov002_020b979c(((char*)this));
    func_ov002_020b9a1c(((char*)this));
    func_ov002_020b993c(((char*)this));
    ((dCc_c *)&mdCcAc_c)->Clear();
    ((dCc_c *)&mdCcAc_c)->Update();
    if (SaveData::HasPlayerLostCap()) {
        ((dActor_c *)(((char*)this)))->SmallPoofDust();
        ((fBase_c *)(((char*)this)))->MarkForDestruction();
    }
    return 1;
}

// @symbol _ZN18daObjPowerUpItem_c13InitResourcesEv
int daObjPowerUpItem_c::InitResources()
{
    struct Vector3 pos;
    short *angp;

    Model::LoadFile(*(SharedFilePtr *)gPFlowerCloseModelFile);
    Model::LoadFile(*(SharedFilePtr *)gPFlowerOpenModelFile);
    if (_ZN9ModelBase7SetFileEP8BMD_Fileii(((char *)this) + 0x124, gPFlowerOpenModelFile[1], 1, -1) == 0)
        return 0;
    if (_ZN9ModelBase7SetFileEP8BMD_Fileii(((char *)this) + 0xd4, gPFlowerCloseModelFile[1], 1, -1) == 0)
        return 0;
    if (_ZN11ShadowModel12InitCylinderEv((char *)&mShadowModel) == 0)
        return 0;

    mVertAccel = -0x668;
    mTerminalVelocity = -0xf000;
    func_ov002_020b9a1c(((char *)this));

    mScaleX = 0xfa0;
    mScaleY = 0xfa0;
    mScaleZ = 0xfa0;

    _ZN7dCcAc_c4InitEP8dActor_c5Fix12IiES3_jj(((char *)this) + 0x1cc, ((char *)this), 0x32000, 0x64000, 0x800002, 0x8000);
    _ZN10dBgCh_Actr4InitEP8dActor_c5Fix12IiES3_P10Vector3_16S5_(((char *)this) + 0x200, ((char *)this), 0x3c000, 0x3c000, 0, 0);
    _ZN10dBgCh_Actr19StartDetectingWaterEv((char *)&mWithMeshClsn);

    pos.x = mPosX;
    pos.y = mPosY;
    pos.z = mPosZ;
    pos.y += 0x14000;
    dBgCh_Gnd ground;
    ground.SetObjAndPos(pos, 0);
    mGroundY = pos.y;
    if (ground.DetectClsn())
        mGroundY = ground.clsnY;
    mLifeTimer = 0xb4;

    if (param1 == 0xffff) {
        if (*(int *)((char *)((dActor_c *)this)->ClosestPlayer() + 8) == 1 && _ZN8SaveData16HasPlayerLostCapEv() == 0) {
            func_ov002_020b9704(((char *)this), 2);
        } else {
            return 0;
        }
    } else {
        func_ov002_020b9704(((char *)this), 0);
    }
    angp = (short *)(int)((char *)&mAngleY);
    *angp = *angp - 0x4000;
    return 1;
}

// @symbol _ZN18daObjPowerUpItem_c13OnYoshiTryEatEv
s32 daObjPowerUpItem_c::OnYoshiTryEat()
{
    return 5;
}
