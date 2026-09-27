//cpp
/* Production translation unit for ov064/daWater_Ring_c.
 * 14 function(s), .text 0x02119a58..0x0211a1b0.
 * The factory daWater_Ring_c_classInit at 0x0211a1b0 is the next function
 * and stays out. One out-of-line destructor emits D1 then D0;
 * `#pragma defer_codegen off` lays .text down in source order.
 */

#pragma defer_codegen off

#include "common.h"
#include "daWater_Ring_c.h"
#include "SharedFilePtr.h"
#include "TextureTransformer.h"

struct C;
typedef int (C::*PMF)();
extern "C" int func_ov064_02119ecc(C *c, PMF *p);

struct BehC;
typedef void (BehC::*BehPMF)();

extern "C" {
extern int data_ov064_0211c944;
extern int data_ov064_0211c3d0[3];
extern s16 data_02082214[];
extern char data_ov002_0210d6dc[];
extern char data_ov064_0211c954[];
extern SharedFilePtr data_ov002_0210da10;

void _ZN10dCcAcPos_c21SetPosRelativeToActorERK7Vector3(void *t, const Vector3 &v);
void *_ZN8dActor_c10FindWithIDEj(unsigned int id);
s16 Vec3_VertAngle(const Vector3 *v1, const Vector3 *v0);
int AngleDiff(int a, int b);
short _ZN8dActor_c18HorzAngleToCPlayerEv(void *t);
void _ZN6Player4HealEi(void *p, int amt);
void _Z14ApproachLinearRiii(int *p, int b, int c);
void _ZN7fBase_c18MarkForDestructionEv(void *self);
unsigned short DecIfAbove0_Short(unsigned short *p);
void _ZN8dActor_c9UpdatePosEP5dCc_c(char *self, char *cc);
void _ZN5dCc_c5ClearEv(char *c);
void _ZN5dCc_c6UpdateEv(char *c);
void _ZN9Animation7AdvanceEv(char *c);
struct BMD_File *_ZN5Model8LoadFileER13SharedFilePtr(void *fp);
int _ZN9ModelBase7SetFileEP8BMD_Fileii(char *self, struct BMD_File *f, int a, int b);
void _ZN18TextureTransformer7PrepareER8BMD_FileR8BTA_File(struct BMD_File *f, struct BTA_File *b);
void _ZN18TextureTransformer7SetFileER8BTA_Filei5Fix12IiEj(char *self, struct BTA_File *b, int a, int fix, u32 f);
void _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj(char *self, struct dActor_c *a, struct Vector3 *v, int r, int h, u32 f1, u32 f2);
void Vec3_Asr(struct Vector3 *d, struct Vector3 *s, int sh);
void Matrix4x3_FromTranslation(void *m, int x, int y, int z);
void Matrix4x3_ApplyInPlaceToRotationXYZExt(void *m, int x, int y, int z);
void _ZN9ModelBase12ApplyOpacityEjj(void *m, unsigned int opacity, unsigned int unused);
extern struct Matrix4x3 data_020a0e68;
}

// @symbol _ZN14daWater_Ring_cD1Ev
// @symbol _ZN14daWater_Ring_cD0Ev
daWater_Ring_c::~daWater_Ring_c()
{
}

// @symbol func_ov064_02119afc
extern "C" void func_ov064_02119afc(char *c)
{
    Vector3 hv;
    Vector3 v;
    char *a;
    int b;
    u32 id;

    *(int *)(c + 0x368) = 0x1000;
    v = *(Vector3 *)data_ov064_0211c3d0;
    _ZN10dCcAcPos_c21SetPosRelativeToActorERK7Vector3(c + 0x110, v);
    id = *(u32 *)(c + 0x134);
    if (id == 0) return;
    a = (char *)_ZN8dActor_c10FindWithIDEj(id);
    if (a == 0) return;
    b = (*(u16 *)(a + 0xc) == 0xbf);
    if (b == 0) return;
    {
        u32 base = ((u32)a + 0x5c) & 0xFFFFFFFFFFFFFFFFull;
        hv.x = *(int *)base;
        hv.y = *(int *)(base + 4);
        hv.z = *(int *)(base + 8);
    }
    if (AngleDiff(*(s16 *)(c + 0x8c), Vec3_VertAngle((Vector3 *)(c + 0x5c), &hv)) >= 0x3000)
        return;
    if (*(int *)(c + 0x37c) != 1) goto Lcheck;
    if (((*(s16 *)(c + 0x388) >> 16) & 1) != ((_ZN8dActor_c18HorzAngleToCPlayerEv(c) >> 16) & 1))
        goto Lpassed;
Lcheck:
    if (*(int *)(c + 0x37c) == 1) goto Lkeep;
Lpassed:
    if (*(int *)(c + 0x37c) == 1)
        _ZN6Player4HealEi(a, 0x100);
    *(int *)(c + 0x368) = 0x4000;
    func_ov064_02119ecc((C *)c, (PMF *)&data_ov064_0211c944);
    return;
Lkeep:
    *(s16 *)(c + 0x388) = _ZN8dActor_c18HorzAngleToCPlayerEv(c);
    return;
}

// @symbol func_ov064_02119c60
extern "C" int func_ov064_02119c60(char *c)
{
    unsigned char *p = (unsigned char *)(c + 0x380);
    *p -= 2;
    if (*(unsigned char *)(c + 0x380) < 2)
        *(unsigned char *)(c + 0x380) = 2;
    _Z14ApproachLinearRiii((int *)(c + 0x80), 0x3000, 0x199);
    *(int *)(c + 0x88) = *(int *)(c + 0x80);
    *(int *)(c + 0x84) = *(int *)(c + 0x88);
    if (*(unsigned short *)(c + 0x100) == 0 || *(int *)(c + 0x80) >= 0x2ffd)
        _ZN7fBase_c18MarkForDestructionEv(c);
    return 1;
}

// @symbol func_ov064_02119ce4
extern "C" int func_ov064_02119ce4(char *c) {
    *(unsigned char *)(c + 0x380) = 0x1f;
    *(short *)(c + 0x100) = 0x64;
    int r2 = *(int *)(c + 0x37c);
    if ((unsigned)(r2 - 1) <= 1) {
        char *r1 = *(char **)(c + 0x38c);
        if (r1 != 0) {
            if (r2 == 1) {
                *(char **)(r1 + 0x3a8) = c;
            } else {
                *(char **)(r1 + 0x31c) = c;
            }
        }
    }
    return 1;
}

// @symbol func_ov064_02119d28
extern "C" int func_ov064_02119d28(char *c) {
    int spd;
    func_ov064_02119afc(c);
    if (*(u16 *)(c + 0x100) < 0x1e) {
        if (*(u8 *)(c + 0x380) >= 2) {
            u8 *p = (u8 *)(((int)c + 0x380));
            *p = *p - 1;
        }
    }
    spd = (*(int *)(c + 0x37c) == 1) ? 0x333 : 0x199;
    {
        int *q = (int *)(((int)c + 0x374));
        *q = *q + 0x1000;
    }
    {
        s16 a = *(int *)(c + 0x374);
        int idx = ((u16)a >> 4) * 2;
        int fr = (int)((((s64)data_02082214[idx] << 10) + 0x800) >> 12);
        int v = fr + *(int *)(c + 0x384);
        _Z14ApproachLinearRiii((int *)(c + 0x384), 0x2000, spd);
        _Z14ApproachLinearRiii((int *)(c + 0x80), v, spd);
    }
    {
        int *q = (int *)(((int)c + 0x378));
        *q = *q + 0x800;
    }
    {
        s16 b = *(int *)(c + 0x378);
        int idx2 = ((u16)b >> 4) * 2;
        s16 *w = (s16 *)(((int)c + 0x92));
        *w = *w + (int)((((s64)data_02082214[idx2] << 8) + 0x800) >> 12);
    }
    *(int *)(c + 0x88) = *(int *)(c + 0x80);
    *(int *)(c + 0x84) = *(int *)(c + 0x88);
    if (*(u16 *)(c + 0x100) == 0 || *(u8 *)(c + 0x380) <= 1)
        _ZN7fBase_c18MarkForDestructionEv(c);
    return 1;
}

// @symbol func_ov064_02119ea0
extern "C" s32 func_ov064_02119ea0(char *c) {
    *(s16 *)(c + 0x100) = 0xc8;
    s32 angle = _ZN8dActor_c18HorzAngleToCPlayerEv(c);
    *(s16 *)(c + 0x388) = (s16)angle;
    return 1;
}

struct C { char pad[0x370]; PMF *pp; };
// @symbol func_ov064_02119ecc
extern "C" int func_ov064_02119ecc(C *c, PMF *p) { c->pp = p; PMF *q = c->pp; if (*q == 0) return 1; return (c->**q)(); }

// @symbol func_ov064_02119f1c
extern "C" void func_ov064_02119f1c(char *c) {
    struct Vector3 v;
    Vec3_Asr(&v, (struct Vector3 *)(c + 0x5c), 3);
    Matrix4x3_FromTranslation(&data_020a0e68, v.x, v.y, v.z);
    Matrix4x3_ApplyInPlaceToRotationXYZExt(&data_020a0e68, *(short *)(c + 0x8c), *(short *)(c + 0x8e), *(short *)(c + 0x90));
    _ZN9ModelBase12ApplyOpacityEjj(c + 0x30c, *(unsigned char *)(c + 0x380), 1);
    *(struct Matrix4x3 *)(c + 0x328) = data_020a0e68;
}

// @symbol _ZN14daWater_Ring_c16CleanupResourcesEv
int daWater_Ring_c::CleanupResources()
{
    ((SharedFilePtr *)(&data_ov002_0210da10))->Release();
    return 1;
}

// @symbol _ZN14daWater_Ring_c16OnPendingDestroyEv
void daWater_Ring_c::OnPendingDestroy()
{
}

// @symbol _ZN14daWater_Ring_c6RenderEv
int daWater_Ring_c::Render()
{
    ((TextureTransformer *)&mTextureTransformer)->Update(mModel.data);
    mModel.Render((const Vector3 *)&mScaleX);
    return 1;
}

// @symbol _ZN14daWater_Ring_c8BehaviorEv
int daWater_Ring_c::Behavior()
{
    DecIfAbove0_Short((unsigned short *)((char *)&mStateTimer));
    char *obj = *(char **)((char *)&unk_370);
    if (*(int *)(obj + 8) != 0) {
        BehPMF *p = (BehPMF *)(obj + 8);
        BehC *c = (BehC *)((char *)this);
        (c->**p)();
    }
    _ZN8dActor_c9UpdatePosEP5dCc_c(((char *)this), ((char *)this) + 0x110);
    mAngleX = mPrevAngleX;
    mAngleY = mPrevAngleY;
    mAngleZ = mPrevAngleZ;
    func_ov064_02119f1c(((char *)this));
    _ZN5dCc_c5ClearEv((char *)&mdCcAcPos_c);
    _ZN5dCc_c6UpdateEv((char *)&mdCcAcPos_c);
    _ZN9Animation7AdvanceEv((char *)&mTextureTransformer);
    return 1;
}

// @symbol _ZN14daWater_Ring_c13InitResourcesEv
int daWater_Ring_c::InitResources()
{
    struct BMD_File *f = _ZN5Model8LoadFileER13SharedFilePtr(&data_ov002_0210da10);
    if (_ZN9ModelBase7SetFileEP8BMD_Fileii(((char *)this) + 0x30c, f, 1, -1) == 0)
        return 0;

    unk_37c = param1 & 0xff;
    if (unk_37c > 2 || unk_37c == 0xff)
    {
        unk_37c = 0;
    }

    _ZN18TextureTransformer7PrepareER8BMD_FileR8BTA_File(*(struct BMD_File **)((char *)&data_ov002_0210da10 + 4), (struct BTA_File *)data_ov002_0210d6dc);
    _ZN18TextureTransformer7SetFileER8BTA_Filei5Fix12IiEj(((char *)this) + 0x35c, (struct BTA_File *)data_ov002_0210d6dc, 0, 0x1000, 0);

    mTextureTransformer.speed = 0x1000;
    mScaleX = 0x1000;
    mScaleY = 0x1000;
    mScaleZ = 0x1000;

    int *src = data_ov064_0211c3d0;
    Vector3 v;
    v.x = src[0];
    v.y = src[1];
    v.z = src[2];
    _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj(((char *)this) + 0x110, (struct dActor_c *)((char *)this), &v, 0x88000, 0xe8000, 0x800006, 0);

    unk_380 = 0x1f;
    func_ov064_02119ecc((C *)this, (PMF *)data_ov064_0211c954);
    return 1;
}
