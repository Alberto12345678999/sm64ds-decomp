//cpp
/* daMoray_c, the Jolly Roger Bay eel (MORAY).
 * 15 function(s), .text 0x021115c0..0x02112588.
 *
 * NAME: _ZTS9daMoray_c is "9daMoray_c" at ov016 0x021148c8; _ZTI at
 * 0x021148d4; the vtable address point is 0x02114958. The tree previously
 * called the class Unagi.
 *
 * D1 (0x021111a0) and D0 (0x02111208) stay shards. func_ov016_02111284,
 * func_ov016_02111534 and BookSwitch_Spawn sit between those destructors
 * and this run, so the destructor is not defined here. The factory
 * daMoray_c_classInit (0x02112588) is the next TU.
 *
 * `#pragma defer_codegen off` lays .text down in source order, so this
 * file is ROM-ascending, and it binds the two member pragmas:
 * opt_propagation off on func_ov016_021119ec, opt_strength_reduction off
 * on Render. common.h is first so the flat Matrix4x3 (m[12]) stands;
 * func_ov016_02111c40 reads m[9], m[10] and m[11].
 */

#include "common.h"
#include "daMoray_c.h"
#include "SharedFilePtr.h"
#include "decl_PathPtr.h"

#pragma defer_codegen off

/* decl_common.h types these file symbols as char[] and declares
 * func_ov016_02111c40(void *). Neither agrees with this TU, so the few
 * names the members actually took from that header are repeated here. */
extern "C" {
int AngleDiff(int a, int b);
int SublevelToLevel(int sub);
void func_ov016_02111284(void *actor);
extern char data_ov016_02114d7c;
extern void *data_ov016_02114d8c;
extern void *data_ov016_02114d9c;
extern void *data_ov016_02114dac;
}

extern SharedFilePtr data_ov016_02114d38;
extern SharedFilePtr data_ov016_02114d20;
extern SharedFilePtr data_ov016_02114d30;
extern SharedFilePtr data_ov016_02114d28;

struct MorayState;
typedef int (MorayState::*MorayPMF)();
struct MorayState { char pad[0x34c]; MorayPMF *pp; };
extern "C" int func_ov016_02111bf0(MorayState *c, MorayPMF *p);


extern "C" {
// @symbol func_ov016_021115c0
extern void *_ZN7PathPtrC1Ev(void* self);
extern void _ZN7PathPtr6FromIDEj(void* self, unsigned int id);
extern void _ZNK7PathPtr7GetNodeER7Vector3j(void* self, void* out, unsigned int idx);
extern short Vec3_HorzAngle(const void* a, const void* b);
extern void _Z14ApproachLinearRsss(short* p, short a, short b);
extern short Vec3_VertAngle(const void* a, const void* b);
extern void Vec3_Sub(void* out, void* a, void* b);
extern int LenVec3(void* v);
extern int _ZN4cstd4fdivEii(int a, int b);
extern void Vec3_MulScalar(void* out, void* v, int s);
extern void SubVec3(void* a, void* b, void* c);
extern void func_02012694(int a, void* p);




#define LA(p) ((void*)(unsigned long)((unsigned long)(p)))

int func_ov016_021115c0(char* c)
{
    char pp[8];
    struct Vector3 node;
    struct Vector3 diff;
    struct Vector3 scaled;
    int len;
    short ha;

    _ZN7PathPtrC1Ev(pp);
    _ZN7PathPtr6FromIDEj(pp, *(unsigned*)(c + 0x404));
    _ZNK7PathPtr7GetNodeER7Vector3j(pp, &node, *(unsigned*)(c + 0x410));

    ha = Vec3_HorzAngle(c + 0x5c, &node);
    {
        int d = AngleDiff(ha, *(short*)(c + 0x94));
        int s = d + ((unsigned)d >> 31);
        *(short*)((char*)LA(c + 0x400) + 0x26) = (short)(s >> 1);
    }
    _Z14ApproachLinearRsss((short*)(c + 0x94), ha, 0x80);

    _Z14ApproachLinearRsss((short*)(c + 0x92), Vec3_VertAngle(c + 0x5c, &node), 0x80);

    Vec3_Sub(&diff, c + 0x5c, &node);
    len = LenVec3(&diff);
    if (len == 0 || len <= 0xa000) {
        if (*(int*)(c + 0x408) == 1 && *(int*)(c + 0x410) == 0) {
            *(int*)(c + 0x410) = 1;
            func_ov016_02111bf0((MorayState *)c, (MorayPMF *)&data_ov016_02114d7c);
            return 1;
        }
        {
            int* q = (int*)LA(c + 0x410);
            *q = *q + 1;
        }
        if (*(int*)(c + 0x410) >= *(int*)(c + 0x40c))
            *(int*)(c + 0x410) = 0;
        func_02012694(0xfa, c + 0x74);
    } else {
        Vec3_MulScalar(&scaled, &diff, _ZN4cstd4fdivEii(0xa000, len));
        SubVec3(c + 0x5c, &scaled, c + 0x5c);
    }
    return 1;
}
}

extern "C" {
extern void _ZN14BlendModelAnim7SetAnimER8BCA_Fileii5Fix12IiEt(void*, void*, int, int, int, unsigned short);
int func_ov016_02111718(char *c){
  _ZN14BlendModelAnim7SetAnimER8BCA_Fileii5Fix12IiEt(c+0x350, ((void **)&data_ov016_02114d30)[1], 8, 0, 0x1000, 0);
  return 1;
}
}

// @symbol func_ov016_02111758
extern "C" {

extern void Matrix4x3_FromRotationY(struct Matrix4x3 *m, short angY);
extern void Matrix4x3_ApplyInPlaceToRotationX(struct Matrix4x3 *m, short angX);
extern void MulVec3Mat4x3(const Vector3 *v, const struct Matrix4x3 *m, Vector3 *out);
extern void _Z14ApproachLinearR7Vector3RKS_5Fix12IiE(Vector3 *cur, const Vector3 *tgt, int step);
extern int _ZN9Animation8FinishedEv(void *self);
extern unsigned char data_0209f220;
extern struct Matrix4x3 data_020a0e68;

int func_ov016_02111758(char *c) {
    Vector3 in;
    Vector3 out;
    in.x = 0; in.y = 0; in.z = 0;
    out.x = 0; out.y = 0; out.z = 0;
    unsigned int t = (unsigned int)(*(int*)(c + 0x3a8)) << 4 >> 0x10;
    if (t >= 0x15 && t <= 0x3c) {
        if (data_0209f220 == 1) {
            in.z = 0x2bc000;
        } else {
            in.z = 0x1f4000;
        }
        Matrix4x3_FromRotationY(&data_020a0e68, *(short*)(c + 0x8e));
        Matrix4x3_ApplyInPlaceToRotationX(&data_020a0e68, *(short*)(c + 0x8c));
        MulVec3Mat4x3(&in, &data_020a0e68, &out);
        out.x += *(int*)(c + 0x3f0);
        out.y += *(int*)(c + 0x3f4);
        out.z += *(int*)(c + 0x3f8);
        _Z14ApproachLinearR7Vector3RKS_5Fix12IiE((Vector3*)(c + 0x5c), &out, 0x14000);
    }
    if (_ZN9Animation8FinishedEv(c + 0x3a0)) {
        *(int*)(c + 0x98) = 0;
        func_ov016_02111bf0((MorayState *)c, (MorayPMF *)&data_ov016_02114dac);
    }
    return 1;
}
}

typedef int Fix12i;
struct BCA_File;
struct BlendModelAnim;
extern "C" {
void _ZN14BlendModelAnim7SetAnimER8BCA_Fileii5Fix12IiEt(void*, void*, int, int, Fix12i, unsigned short);
void func_02012694(int, void*);
int func_ov016_02111860(char* c){
  void* anim = (void*)((void **)&data_ov016_02114d20)[1];
  _ZN14BlendModelAnim7SetAnimER8BCA_Fileii5Fix12IiEt(c+0x350, anim, 8, 0x40000000, 0x1000, 0);
  func_02012694(0xfa, c+0x74);
  return 1;
}
}

// @symbol func_ov016_021118b4
extern "C" {

extern int Vec3_Dist(const Vector3 *a, const Vector3 *b);
extern void *data_ov016_02114dbc;

int func_ov016_021118b4(char *c) {
    Vector3 in;
    Vector3 out;
    in.x = 0; in.y = 0; in.z = 0;
    out.x = 0; out.y = 0; out.z = 0;
    in.z = 0x76c000;
    Matrix4x3_FromRotationY(&data_020a0e68, *(short*)(c + 0x8e));
    Matrix4x3_ApplyInPlaceToRotationX(&data_020a0e68, *(short*)(c + 0x8c));
    MulVec3Mat4x3(&in, &data_020a0e68, &out);
    out.x += *(int*)(c + 0x3f0);
    out.y += *(int*)(c + 0x3f4);
    out.z += *(int*)(c + 0x3f8);
    _Z14ApproachLinearR7Vector3RKS_5Fix12IiE((Vector3*)(c + 0x5c), &out, 0x14000);
    if (Vec3_Dist((Vector3*)(c + 0x5c), &out) < 0x14000) {
        func_02012694(0xfa, c + 0x74);
        func_ov016_02111bf0((MorayState *)c, (MorayPMF *)&data_ov016_02114dbc);
    }
    return 1;
}
}

extern "C" {
int func_ov016_02111994(char* c){
  *(int*)(c+0x400)=0;
  ((void (*)(int, void *, int))func_02012694)(0xfa, c+0x74, 0);
  _ZN14BlendModelAnim7SetAnimER8BCA_Fileii5Fix12IiEt(c+0x350, (void*)((void **)&data_ov016_02114d28)[1], 8, 0, 0x1000, 0);
  return 1;
}
}

extern "C" {
#pragma push
#pragma opt_propagation off
// @symbol func_ov016_021119ec
typedef short s16;



extern void* _ZN8dActor_c13ClosestPlayerEv(void* self);
extern s16 _ZN8dActor_c18HorzAngleToCPlayerEv(void* self);
extern int Vec3_HorzDist(const void* a, const void* b);



int func_ov016_021119ec(char* c)
{
    void* player;
    struct Vector3 playerPos;
    struct Vector3 local;
    struct Vector3 world;
    int thrHorz;
    int thrVert;
    int thrAng;
    unsigned char stage;
    int zero;
    int dy;

    if (Vec3_Dist((const Vector3 *)(c + 0x5c), (const Vector3 *)(c + 0x3f0)) > 0xa000) {
        _Z14ApproachLinearR7Vector3RKS_5Fix12IiE((Vector3 *)(c + 0x5c), (const Vector3 *)(c + 0x3f0), 0x5000);
        return 1;
    }

    *(int*)(c + 0x5c) = *(int*)(c + 0x3f0);
    *(int*)(c + 0x60) = *(int*)(c + 0x3f4);
    *(int*)(c + 0x64) = *(int*)(c + 0x3f8);

    player = _ZN8dActor_c13ClosestPlayerEv(c);
    if (player != 0) {
        int* p = (int*)LA((char*)player + 0x5c);

        /* ACDB order: x,y,z then stage — colors y/z as r2 and stage as r1 */
        playerPos.x = p[0];
        playerPos.y = p[1];
        playerPos.z = p[2];
        stage = data_0209f220;

        thrHorz = 0x3e8000;
        thrAng = 0x3300;
        thrVert = 0x418000;
        thrVert += 0x3e8000;

        if (stage == 1) {
            zero = 0;
            local.z = zero;
            local.z = 0x64000;
            local.x = zero;
            local.y = zero;
            world.x = zero;
            world.y = zero;
            world.z = zero;
            thrHorz = 0x495000;
            thrVert = 0x6ee000;
            Matrix4x3_FromRotationY(&data_020a0e68, *(s16*)(c + 0x8e));
            Matrix4x3_ApplyInPlaceToRotationX(&data_020a0e68, *(s16*)(c + 0x8c));
            MulVec3Mat4x3(&local, &data_020a0e68, &world);
            world.x += *(int*)(c + 0x3f0);
            world.y += *(int*)(c + 0x3f4);
            world.z += *(int*)(c + 0x3f8);
            if (Vec3_Dist(&playerPos, &world) < 0x224000)
                func_ov016_02111bf0((MorayState *)c, (MorayPMF *)&data_ov016_02114d9c);
        }

        if (AngleDiff(_ZN8dActor_c18HorzAngleToCPlayerEv(c), *(s16*)(c + 0x8e)) < thrAng) {
            if (Vec3_HorzDist(c + 0x5c, &playerPos) < thrHorz) {
                dy = *(int*)(c + 0x60) - playerPos.y;
                if (dy < 0)
                    dy = -dy;
                if (dy < thrVert)
                    func_ov016_02111bf0((MorayState *)c, (MorayPMF *)&data_ov016_02114d9c);
            }
        }
    }
    return 1;
}
#pragma pop
}

extern "C" {
int func_ov016_02111bac(char* c){
  *(int*)(c+0x400)=0;
  _ZN14BlendModelAnim7SetAnimER8BCA_Fileii5Fix12IiEt(c+0x350, ((void **)&data_ov016_02114d28)[1], 8, 0, 0x1000, 0);
  return 1;
}
}

extern "C" int func_ov016_02111bf0(MorayState *c, MorayPMF *p) { c->pp = p; MorayPMF *q = c->pp; if (*q == 0) return 1; return (c->**q)(); }

extern "C" {
// @symbol func_ov016_02111c40

extern void Vec3_Asr(struct Vector3 *d, struct Vector3 *s, int sh);
extern void Matrix4x3_FromTranslation(void *m, int x, int y, int z);
extern void Matrix4x3_ApplyInPlaceToRotationZXYExt(void *m, s16 x, s16 y, s16 z);
extern void MulMat4x3Mat4x3(void *m1, void *m0, void *mF);
extern void *_ZN8dActor_c10FindWithIDEj(u32 id);
extern void Matrix4x3_ApplyInPlaceToRotationXYZExt(void *m, s16 x, s16 y, s16 z);

void func_ov016_02111c40(char *c)
{
    struct Vector3 in;
    struct Vector3 out;
    struct Vector3 asr;
    int zero[1];
    int i;
    char *bone;
    int base;
    int *pos;
    Matrix4x3 *mat_src;
    Matrix4x3 *scratch;
    void *found;
    int off424;
    char *p400;
    u32 id;
    Matrix4x3 *scratch1;
    Matrix4x3 *scratch0;

    Vec3_Asr(&asr, (struct Vector3 *) (c + 0x5c), 3);
    Matrix4x3_FromTranslation(&data_020a0e68, asr.x, asr.y, asr.z);
    in.z = 0;
    in.z = -0x190000;
    in.x = 0;
    in.y = 0;
    scratch0 = &data_020a0e68;
    out.x = 0;
    out.y = 0;
    out.z = 0;
    Matrix4x3_FromRotationY(&data_020a0e68, *((s16 *) (c + 0x8e)));
    scratch1 = &data_020a0e68;
    MulVec3Mat4x3(&in, scratch1, &out);
    Matrix4x3_FromTranslation(&data_020a0e68, ((*((int *) (c + 0x5c))) + out.x) >> 3, (*((int *) (c + 0x60))) >> 3,
                              ((*((int *) (c + 0x64))) + out.z) >> 3);
    Matrix4x3_ApplyInPlaceToRotationZXYExt(&data_020a0e68, *((s16 *) (c + 0x8c)), *((s16 *) (c + 0x8e)),
                                           *((s16 *) (c + 0x90)));
    *((Matrix4x3 *) (c + 0x36c)) = data_020a0e68;
    p400 = c + 0x400;
    off424 = 0x424;
    _Z14ApproachLinearRsss((s16 *) (c + off424), *((s16 *) (p400 + 0x26)), 0x40);
    i = 0;
    scratch = &data_020a0e68;
    mat_src = (Matrix4x3 *) (c + 0x36c);
    *((s16 *) (c + 0x422)) = *((s16 *) (c + 0x424));
    bone = c;
    base = i;
    pos = (int *) (c + 0x448);
    zero[0] = i;
    do {
        Matrix4x3 *dst;
        *((int *) (bone + 0x448)) = zero[0];
        *((int *) (bone + 0x44c)) = zero[0];
        *((int *) (bone + 0x450)) = zero[0];
        dst = &data_020a0e68;
        *dst = *mat_src;
        MulMat4x3Mat4x3(((char *) (*((void **) (c + 0x364)))) + base, dst, dst);
        pos[0] = *((int *) (((char *) dst) + 0x24));
        pos[1] = *((int *) (((char *) dst) + 0x28));
        pos[2] = *((int *) (((char *) dst) + 0x2c));
        *((int *) (bone + 0x448)) = *((int *) (bone + 0x448)) << 3;
        *((int *) (bone + 0x44c)) = *((int *) (bone + 0x44c)) << 3;
        *((int *) (bone + 0x450)) = *((int *) (bone + 0x450)) << 3;
        bone += 0xc;
        base += 0x30;
        pos += 3;
        i++;
    } while (i < 7);
    id = *((u32 *) (c + 0x49c));
    if (id == 0) {
        return;
    }
    found = _ZN8dActor_c10FindWithIDEj(id);
    if (found == 0) {
        return;
    }
    *((int *) (c + 0x43c)) = 0;
    *((int *) (c + 0x440)) = 0;
    *((int *) (c + 0x444)) = 0;
    MulMat4x3Mat4x3(((char *) (*((void **) (c + 0x364)))) + 0xc0, c + 0x36c, c + 0x3c0);
    Matrix4x3_FromTranslation(scratch0, 0x28000, 0, 0);
    Matrix4x3_ApplyInPlaceToRotationXYZExt(&data_020a0e68, 0x4000, -0x8000, *((s16 *) (c + 0x416)));
    MulMat4x3Mat4x3(&data_020a0e68, c + 0x3c0, c + 0x3c0);
    {
        void *live = (void *) (c + 0x3c0);
        data_020a0e68 = *(Matrix4x3 *) (c + 0x3c0);
        *(int *) (c + 0x43c) = data_020a0e68.m[9];
        *(int *) (c + 0x440) = data_020a0e68.m[10];
        *(int *) (c + 0x444) = data_020a0e68.m[11];
        *(int *) (((int) c + 0x43c)) <<= 3;
        *(int *) (((int) c + 0x440)) <<= 3;
        *(int *) (((int) c + 0x444)) <<= 3;
        *((void **) (((char *) found) + 0xc8)) = live;
    }
}
}

// @symbol _ZN9daMoray_c16CleanupResourcesEv


extern "C" {
}

s32 daMoray_c::CleanupResources()
{
    data_ov016_02114d38.Release();
    data_ov016_02114d20.Release();
    data_ov016_02114d30.Release();
    data_ov016_02114d28.Release();
    return 1;
}

// @symbol _ZN9daMoray_c16OnPendingDestroyEv


void daMoray_c::OnPendingDestroy()
{
}

#pragma push
#pragma opt_strength_reduction off
// @symbol _ZN9daMoray_c6RenderEv


struct MorayRenderStep {
    s32 unk_00;
    s32 unk_04;
    s32 angleScale;
};

extern "C" {
void func_020167a4(BlendModelAnim *model);
void func_0204531c(ModelComponents *data, s32 weight);
extern MorayRenderStep data_ov016_02114908[];
}


s32 daMoray_c::Render()
{
    int i;
    MorayRenderStep *step;
    char *bone;

    func_020167a4(&mBlendModelAnim);
    bone = (char *)mBlendModelAnim.data.bones + 0x34;
    step = data_ov016_02114908;
    for (i = 1; i < 7; i++) {
        s16 movement = mSegmentAngle[i];
        u16 *angle = (u16 *)(bone + 0x1e);
        *angle = *angle + (u16)(s16)(movement * step->angleScale);
        step++;
        bone += 0x34;
    }
    func_0204531c(&mBlendModelAnim.data, mBlendModelAnim.blendWeight);
    mBlendModelAnim.Model::Render(0);
    return 1;
}
#pragma pop

// @symbol _ZN9daMoray_c8BehaviorEv
struct C;
typedef void (C::*StateFn)();

extern "C" u16 DecIfAbove0_Short(u16* p);
extern "C" void _ZN8dActor_c9UpdatePosEP5dCc_c(void* self, void* cc);
extern "C" void _ZN7fBase_c18MarkForDestructionEv(void* self);
extern "C" void* _ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as(unsigned a, unsigned b, const Vector3& pos, const Vector3_16* rot, int e, int f);
extern "C" void _ZN5dCc_c5ClearEv(void* self);
extern "C" void _ZN5dCc_c6UpdateEv(void* self);
extern "C" void _ZN14BlendModelAnim7AdvanceEv(void* self);

struct Disp { int unused[2]; StateFn pmf; };



int daMoray_c::Behavior()
{
    void* found;
    unsigned id;

    DecIfAbove0_Short((u16*)((char*)&mStateTimer));
    {
        Disp* d = *(Disp**)((char*)&mState);
        if (d->pmf) {
            (((C*)((char*)this))->*(d->pmf))();
        }
    }
    _ZN8dActor_c9UpdatePosEP5dCc_c(((char*)this), ((char*)this) + 0x110);
    mAngleX = mPrevAngleX;
    mAngleY = mPrevAngleY;
    mAngleZ = mPrevAngleZ;
    func_ov016_02111c40(((char*)this));

    id = *(unsigned*)((char*)&mStarUniqueID);
    if (id != 0) {
        found = _ZN8dActor_c10FindWithIDEj(id);
        if (found == 0)
            goto clear_id;
        if (mVariant == 1) {
            void* cp = _ZN8dActor_c13ClosestPlayerEv(((char*)this));
            if (cp != 0) {
                if (Vec3_Dist(&mStarPos, (const Vector3 *)((char*)cp + 0x5c)) < 0xfa000) {
                    _ZN7fBase_c18MarkForDestructionEv(found);
                    {
                        int param = mAreaId;
                        int m1 = -1;
                        _ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as(
                            0xb2, mStarParam | 0x40,
                            mStarPos, (Vector3_16*)0,
                            param, m1);
                    }
                    mStarUniqueID = 0;
                    goto after_first;
                }
            }
        }
        goto after_first;
    clear_id:
        mStarUniqueID = 0;
    after_first:
        if (mStarUniqueID != 0) {

        int x = mStarPos.x;
        int off = 0x416;
        *(int*)((char*)found + 0x5c) = x;
        short* r = (short*)LA(((char*)this) + off);
        *(int*)((char*)found + 0x60) = mStarPos.y;
        *(int*)((char*)found + 0x64) = mStarPos.z;
        *r += 0x1000;

        }
    }

    func_ov016_02111284(((char*)this));
    _ZN5dCc_c5ClearEv((char*)&mdCcAcPos_c1);
    _ZN5dCc_c6UpdateEv((char*)&mdCcAcPos_c1);
    if (data_0209f220 == 1 && *(void**)((char*)&mState) != &data_ov016_02114dbc) {
        _ZN5dCc_c5ClearEv((char*)&mdCcAcPos_c2);
        _ZN5dCc_c6UpdateEv((char*)&mdCcAcPos_c2);
    }
    _ZN14BlendModelAnim7AdvanceEv((char*)&mBlendModelAnim);
    return 1;
}

// @symbol _ZN9daMoray_c13InitResourcesEv
struct V3 { int x, y, z; };
struct PathPtr { char b[8]; };

extern "C" {
extern void* _ZN5Model8LoadFileER13SharedFilePtr(void* fp);
extern void _ZN9ModelBase7SetFileEP8BMD_Fileii(char* m, void* f, int a, int b);
extern void* _ZN9Animation8LoadFileER13SharedFilePtr(void* fp);
extern void _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj(char* self, char* actor, struct V3* pos, int r3, int sp0, int sp4, int sp8);
extern int IsStarCollected(int a, int b);
extern void _ZN8dActor_c9SetRangesE5Fix12IiES1_S1_S1_(char* a, int r1, int r2, int r3, int sp0);

extern struct V3 data_ov016_02114d4c;
}

int daMoray_c::InitResources()
{
    PathPtr path1;
    PathPtr path2;
    PathPtr path3;
    V3 node;
    V3 v1;
    V3 v2;
    int i;
    void* f;
    char* spawned;

    f = _ZN5Model8LoadFileER13SharedFilePtr(&data_ov016_02114d38);
    _ZN9ModelBase7SetFileEP8BMD_Fileii(((char*)this) + 0x350, f, 1, -1);
    _ZN9Animation8LoadFileER13SharedFilePtr(&data_ov016_02114d20);
    _ZN9Animation8LoadFileER13SharedFilePtr(&data_ov016_02114d30);
    _ZN9Animation8LoadFileER13SharedFilePtr(&data_ov016_02114d28);

    mPathID = param1 & 0xff;
    mVariant = (param1 >> 8) & 0xf;
    mStarParam = (param1 >> 0xc) & 0xf;
    if (mVariant == 0xff)
        mVariant = 0;
    if (mPathID < 0)
        mPathID = 0;

    _ZN7PathPtrC1Ev(&path1);
    _ZN7PathPtr6FromIDEj(&path1, mPathID);
    mPathNodeCount = _ZNK7PathPtr8NumNodesEv(&path1);

    mHomePosX = mPosX;
    mHomePosY = mPosY;
    mHomePosZ = mPosZ;
    mTerminalVelocity = -0x1e000;
    v1 = data_ov016_02114d4c;
    _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj(
        ((char*)this) + 0x110, ((char*)this), &v1, 0x32000, 0x50000, 0x200004, 0);
    v2 = data_ov016_02114d4c;
    _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj(
        ((char*)this) + 0x150, ((char*)this), &v2, 0x32000, 0x50000, 0x200000, 0);

    _ZN7PathPtrC1Ev(&path2);
    _ZN7PathPtr6FromIDEj(&path2, mPathID);
    mPathNodeIndex = 1;
    mStarUniqueID = 0;
    mBlendModelAnim.speed = 0x1000;

    if (data_0209f220 == 1)
        goto check_param2;
    if (IsStarCollected(SublevelToLevel(8), 1) != 0)
        goto stage2_path;

check_param2:
    if (mVariant != 2)
        goto ret0_a;
    /* u64-mask forces add r2,r4,#0x3f4 materialization (ROM shape) */
    *(int*)(((int)((char*)this) + 0x3f4)) -= 0x80000;
    mPathNodeIndex = 8;
    if (mPathNodeIndex >= mPathNodeCount)
        mPathNodeIndex = 4;
    mPosY = mHomePosY;
    func_ov016_02111bf0((MorayState *)(char *)this, (MorayPMF *)&data_ov016_02114d8c);
    goto tail;
ret0_a:
    return 0;

stage2_path:
    if (data_0209f220 == 2)
        goto check_param1;
    if (IsStarCollected(SublevelToLevel(8), 2) != 0)
        goto check_param0;

check_param1:
    if (mVariant != 1)
        goto ret0_b;
    spawned = (char *)_ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as(
        0xb2, mStarParam | 0x50, *(Vector3 *)(((char*)this) + 0x5c), (Vector3_16 *)0,
        mAreaId, -1);
    if (spawned != 0) {
        mStarUniqueID = *(int*)(spawned + 4);
        *(int*)(spawned + 0xb0) = 0;
        _ZN8dActor_c9SetRangesE5Fix12IiES1_S1_S1_(spawned, 0, 0x3e8000, 0x1f40000, 0x1f40000);
    }
    func_ov016_02111bf0((MorayState *)(char *)this, (MorayPMF *)&data_ov016_02114d8c);
    goto tail;
ret0_b:
    return 0;

check_param0:
    if (mVariant != 0)
        goto ret0_c;
    _ZN7PathPtrC1Ev(&path3);
    _ZN7PathPtr6FromIDEj(&path3, mPathID);
    _ZNK7PathPtr7GetNodeER7Vector3j(&path3, ((char*)this) + 0x5c, 0);
    _ZNK7PathPtr7GetNodeER7Vector3j(&path3, ((char*)this) + 0x5c, 1);
    mPrevAngleY = Vec3_HorzAngle(((char*)this) + 0x5c, (char*)&node);
    mAngleY = mPrevAngleY;
    func_ov016_02111bf0((MorayState *)(char *)this, (MorayPMF *)&data_ov016_02114dbc);
    goto tail;
ret0_c:
    return 0;

tail:
    for (i = 0; i < 7; i++) {
        /* array index form -> add r0,r4,ip,lsl#1 (not strength-reduced i*2) */
        mSegmentAngle[i] = 0;
        mSegmentAngle[7] = 0;
        mSegmentPos[i].x = mPosX;
        mSegmentPos[i].y = mPosY;
        mSegmentPos[i].z = mPosZ;
    }
    mInitAngleX = mAngleX;
    mInitAngleY = mAngleY;
    mInitAngleZ = mAngleZ;
    return 1;
}
