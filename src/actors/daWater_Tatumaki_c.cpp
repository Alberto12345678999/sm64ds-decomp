//cpp
/* daWater_Tatumaki_c. ov026 text 0x02111aa0..0x021121bc.
 * The factory stays in src/d_a_water_tatumaki.c.
 *
 * Functions are in ROM order. #pragma defer_codegen off makes the one
 * out-of-line destructor emit D1 then D0; the trailing D2 has no ROM home.
 */

#pragma defer_codegen off

#include "daWater_Tatumaki_c.h"
#include "dActor_c.h"
#include "decl_common.h"
#include "common.h"
#include "SharedFilePtr.h"
#include "TextureTransformer.h"

struct Vec3 {
    int x;
    int y;
    int z;
};

struct Player {
    char pad[0x5c];
    Vector3 pos;
    char pad2[0x6f9 - 0x68];
    unsigned char flag6f9;
    void EnterWhirlpool();
};

struct FilePtr4 { int a; void *file; };
extern int data_ov026_02113f0c[];
extern int data_ov026_02113f04[];
extern BTA_File data_ov026_02112f40;

struct FlatMat4x3 { s32 m[12]; };
extern FlatMat4x3 data_020a0e68;

extern "C" {
extern void *_ZN8dActor_c13ClosestPlayerEv(void *self);
extern int _ZN8dActor_c18HorzAngleToCPlayerEv(void *self);
extern void Matrix4x3_FromRotationY(void *m, int angle);
extern void Matrix4x3_ApplyInPlaceToRotationX(void *m, short angX);
extern void Matrix4x3_FromTranslation(void *m, int x, int y, int z);
extern void Matrix4x3_ApplyInPlaceToRotationXYZExt(void *m, short rx, short ry, short rz);
extern void MulVec3Mat4x3(const Vector3 *in, const void *m, Vector3 *out);
extern void Vec3_Asr(void *dst, void *src, int n);
extern short Vec3_HorzAngle(struct Vec3 *a, struct Vec3 *b);
extern int Vec3_HorzDist(const Vector3 *a, const Vector3 *b);
extern int Vec3_Dist(const Vector3 *a, const Vector3 *b);
extern void _Z15ApproachLinear2Rsss(s16 *v, s16 target, s16 step);
extern void _Z14ApproachLinearRiii(int *v, int target, int step);
extern void _Z14ApproachLinearR7Vector3RKS_5Fix12IiE(Vec3 *v, Vec3 *target, int step);
extern unsigned short DecIfAbove0_Short(unsigned short *p);
extern void _ZN8dActor_c9UpdatePosEP5dCc_c(void *thiz, void *cc);
extern void *_ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
    unsigned int a, unsigned int b, int fx, int t1, int t2, int s4, int s5);
extern void _ZN9Animation7AdvanceEv(void *thiz);
extern struct BMD_File *_ZN5Model8LoadFileER13SharedFilePtr(struct SharedFilePtr &);
extern void _ZN9ModelBase7SetFileEP8BMD_Fileii(void *thisp, struct BMD_File *, int, int);
extern void _ZN9Animation8LoadFileER13SharedFilePtr(struct SharedFilePtr &);
extern void _ZN18TextureTransformer7PrepareER8BMD_FileR8BTA_File(struct BMD_File &, struct BTA_File &);
extern void _ZN18TextureTransformer7SetFileER8BTA_Filei5Fix12IiEj(void *thisp, struct BTA_File &, int, int, unsigned int);
extern void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *thisp, struct BCA_File *, int, int, unsigned int);
}

struct Ee0;
typedef int (Ee0::*Ee0PMF)();
struct Ee0 { char pad[0x110]; Ee0PMF *pp; };

typedef int (*dummy)();
class BehC;
typedef int (BehC::*BehPMF)();
class BehC { public: int d; };

struct Sub { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void m(int); };
struct Base { char pad[0x114]; Sub sub; };

// @symbol _ZN18daWater_Tatumaki_cD1Ev
daWater_Tatumaki_c::~daWater_Tatumaki_c()
{
}

// @symbol _ZN18daWater_Tatumaki_cD0Ev
/* D0 is emitted from the destructor above. */

// @symbol func_ov026_02111b24
extern "C" int func_ov026_02111b24(char *self)
{
    Vec3 v1;
    Vec3 v2;
    volatile Vec3 pv;
    char *player;

    v1.x = 0;
    v1.y = 0;
    v1.z = 0;
    v2.x = 0;
    v2.y = 0;
    v2.z = 0;
    v1.z = *(int *)(self + 0x198);
    player = (char *)_ZN8dActor_c13ClosestPlayerEv(self);
    if (player) {
        Matrix4x3_FromRotationY(&data_020a0e68, *(s16 *)(self + 0x1b4));
        MulVec3Mat4x3((const Vector3 *)&v1, &data_020a0e68, (Vector3 *)&v2);
        v1.x = *(int *)(self + 0x1a8);
        v1.y = *(int *)(self + 0x1ac);
        v1.z = *(int *)(self + 0x1b0);
        _Z15ApproachLinear2Rsss((s16 *)(self + 0x1b6), 0x1000, 0x200);
        _Z14ApproachLinearRiii((int *)(self + 0x198), 0x100, 0x1000);
        _Z14ApproachLinearRiii((int *)(self + 0x194), *(int *)(self + 0x1ac) - 0x64000, 0x4000);
        {
            s16 *q = (s16 *)(int)(self + 0x1b4);
            *q += *(s16 *)(self + 0x1b6);
        }
        v1.y = *(int *)(self + 0x194);
        v1.x += v2.x;
        v1.z += v2.z;
        _Z14ApproachLinearR7Vector3RKS_5Fix12IiE((Vec3 *)(self + 0x19c), &v1, 0x1e000);
        *(int *)(player + 0x5c) = *(int *)(self + 0x19c);
        *(int *)(player + 0x60) = *(int *)(self + 0x1a0);
        *(int *)(player + 0x64) = *(int *)(self + 0x1a4);
        {
            int ang = _ZN8dActor_c18HorzAngleToCPlayerEv(self) + 0x8000;
            *(s16 *)(player + 0x8c) = -0x2000;
            *(s16 *)(player + 0x8e) = ang;
            *(s16 *)(player + 0x90) = 0;
        }
        {
            int *pp = (int *)(int)(player + 0x5c);
            pv.x = pp[0];
            pv.y = pp[1];
            pv.z = pp[2];
            if (*(int *)(self + 0x1ac) > pp[1]) {
                if (*(int *)(self + 0x18c) == 0) {
                    KillPlayer();
                    *(int *)(self + 0x18c) = 1;
                }
            }
        }
    }
    return 1;
}

// @symbol func_ov026_02111cb4
extern "C" int func_ov026_02111cb4(char *c)
{
    char *p = (char *)_ZN8dActor_c13ClosestPlayerEv(c);
    if (p)
    {
        struct Vec3 *sp = (struct Vec3 *)(((int)p + 0x5c));
        struct Vec3 t;
        t.x = sp->x;
        t.y = sp->y;
        t.z = sp->z;
        *((short *)(c + 0x1b4)) = Vec3_HorzAngle((struct Vec3 *)(c + 0x5c), &t);
        *((int *)(c + 0x190)) = 0;
        *((int *)(c + 0x194)) = 0;
        *((int *)(c + 0x198)) = 0;
        *((int *)(c + 0x19c)) = t.x;
        *((int *)(c + 0x1a0)) = t.y;
        *((int *)(c + 0x1a4)) = t.z;
        *((int *)(c + 0x194)) = t.y;
        *((int *)(c + 0x198)) = Vec3_HorzDist((const Vector3 *)(c + 0x1a8), (const Vector3 *)&t);
    }
    return 1;
}

// @symbol func_ov026_02111d4c
extern "C" int func_ov026_02111d4c(char *c)
{
    Player *pl = ((dActor_c *)c)->ClosestPlayer();
    if (pl != 0) {
        Vector3 v;
        Vector3 *p0 = (Vector3 *)((int)pl + 0x5c);
        v = *p0;

        if (Vec3_HorzDist((Vector3 *)(c + 0x1a8), &v) <= 0x12c000) {
            int e = *(int *)(c + 0x1ac) - v.y;
            if (e < 0) e = -e;
            if (e <= 0x12c000) {
                pl->EnterWhirlpool();
                func_ov026_02111ee0(c, &data_ov026_02113f3c);
                return 1;
            }
        }

        if (pl->flag6f9 == 0) {
            int dd = Vec3_Dist((Vector3 *)(c + 0x1a8), &v);
            if (dd < 0x44c000) {
                Vector3 m;
                Vector3 out;
                int q;
                q = 0x44c000;
                q -= dd;
                q = q / 35;
                m.x = 0;
                m.y = 0;
                m.z = q;
                out.x = 0;
                out.y = 0;
                out.z = 0;

                Matrix4x3_FromRotationY(&data_020a0e68, (short)(((dActor_c *)c)->HorzAngleToCPlayer() + 0x8000));
                Matrix4x3_ApplyInPlaceToRotationX(&data_020a0e68, 0x2000);
                MulVec3Mat4x3(&m, &data_020a0e68, &out);

                Vector3 *p1 = (Vector3 *)((int)((int)pl) + 0x5c);
                m = *p1;
                m.x += out.x;
                m.y += out.y;
                m.z += out.z;
                pl->pos = m;
            }
        }
    }
    return 1;
}

// @symbol func_ov026_02111ed8
extern "C" int func_ov026_02111ed8(void)
{
    return 1;
}

// @symbol func_ov026_02111ee0
extern "C" int func_ov026_02111ee0(void *cv, void *pv)
{
    Ee0 *c = (Ee0 *)cv;
    Ee0PMF *p = (Ee0PMF *)pv;
    c->pp = p;
    Ee0PMF *q = c->pp;
    if (*q == 0) return 1;
    return (c->**q)();
}

// @symbol func_ov026_02111f30
extern "C" void func_ov026_02111f30(char *c)
{
    int v[3];
    Vec3_Asr(v, c + 0x5c, 3);
    Matrix4x3_FromTranslation(&data_020a0e68, v[0], v[1], v[2]);
    Matrix4x3_ApplyInPlaceToRotationXYZExt(&data_020a0e68,
        *(short *)(c + 0x8c), *(short *)(c + 0x8e), *(short *)(c + 0x90));
    *(FlatMat4x3 *)(c + 0x130) = data_020a0e68;
}

// @symbol _ZN18daWater_Tatumaki_c16CleanupResourcesEv
int daWater_Tatumaki_c::CleanupResources()
{
    ((SharedFilePtr *)data_ov026_02113f0c)->Release();
    ((SharedFilePtr *)data_ov026_02113f04)->Release();
    return 1;
}

// @symbol _ZN18daWater_Tatumaki_c16OnPendingDestroyEv
void daWater_Tatumaki_c::OnPendingDestroy()
{
}

// @symbol _ZN18daWater_Tatumaki_c6RenderEv
int daWater_Tatumaki_c::Render()
{
 ((TextureTransformer *)((char *)((Base *)this) + 0x178))->Update(*(ModelComponents *)((char *)((Base *)this) + 0x11c)); Sub *b = &((Base *)this)->sub; b->m(0); return 1;
}

// @symbol _ZN18daWater_Tatumaki_c8BehaviorEv
int daWater_Tatumaki_c::Behavior()
{
    volatile int v[3];
    int x, y, z;

    DecIfAbove0_Short((unsigned short *)((char *)&mStateTimer));
    {
        char *obj = *(char **)((char *)&unk_110);
        if (*(int *)(obj + 8) != 0) {
            BehPMF *pp = (BehPMF *)(obj + 8);
            ((BehC *)((char *)this)->**pp)();
        }
    }
    _ZN8dActor_c9UpdatePosEP5dCc_c(((char *)this), 0);

    x = mPosX;
    v[0] = x;
    y = mPosY;
    v[1] = y;
    z = mPosZ;
    v[2] = z;
    y += 0x384000;
    v[1] = y;

    *(void **)((char *)&unk_1b8) = _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
        *(volatile unsigned int *)((char *)&unk_1b8), 0x139, v[0], v[1], z, 0, 0);

    mAngleX = mPrevAngleX;
    mAngleY = mPrevAngleY;
    mAngleZ = mPrevAngleZ;

    func_ov026_02111f30(((char *)this));
    _ZN9Animation7AdvanceEv((char *)&mTextureTransformer);
    _ZN9Animation7AdvanceEv((char *)(Animation *)&mModelAnim);
    return 1;
}

// @symbol _ZN18daWater_Tatumaki_c13InitResourcesEv
int daWater_Tatumaki_c::InitResources()
{
    struct BMD_File *bmd = _ZN5Model8LoadFileER13SharedFilePtr(*(struct SharedFilePtr *)data_ov026_02113f0c);
    _ZN9ModelBase7SetFileEP8BMD_Fileii(((char *)this) + 0x114, bmd, 1, -1);

    _ZN9Animation8LoadFileER13SharedFilePtr(*(struct SharedFilePtr *)data_ov026_02113f04);

    _ZN18TextureTransformer7PrepareER8BMD_FileR8BTA_File(*(struct BMD_File *)((struct FilePtr4 *)data_ov026_02113f0c)->file, data_ov026_02112f40);
    _ZN18TextureTransformer7SetFileER8BTA_Filei5Fix12IiEj(((char *)this) + 0x178, data_ov026_02112f40, 0, 0x1000, 0);

    /* +0x0c inside the TextureTransformer, which names only `file` at +0x10;
       reached through the member rather than absorbed into it. */
    *(Fix12i *)((char *)&mTextureTransformer + 0xc) = 0x1000;
    mModelAnim.speed = 0x1000;

    unk_1a8 = mPosX;
    unk_1ac = mPosY;
    unk_1b0 = mPosZ;
    *(int *)(((int)((char *)this) + 0x1ac)) -= 0x64000;

    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(((char *)this) + 0x114, (struct BCA_File *)((struct FilePtr4 *)data_ov026_02113f04)->file, 0, 0x1000, 0);

    func_ov026_02111ee0(((char *)this), &data_ov026_02113f2c);
    return 1;
}
