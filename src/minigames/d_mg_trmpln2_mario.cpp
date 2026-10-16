//cpp
/*
 * The two player-controlled Mario classes of the trampoline minigames,
 * dMgTrmpln2Mario_c and dMgTrmpln3DMario_c, with their helpers and the
 * object-adapter functions that follow them: 88 functions,
 * ov006 .text 0x020c8dd4..0x020cd744.
 *
 * ROM evidence: D1 0x020ca604 and constructor 0x020ca78c of
 * dMgTrmpln2Mario_c (filed under _ZN6Player29TryExitCharacterDoorWithIntroEv;
 * not a Player method -- it stores vptr data_ov006_0213b2e0 and constructs
 * a ModelAnim at +0x78, and the name stays because symbols.txt carries it);
 * D1 0x020ccfc8 and constructor 0x020cd12c of dMgTrmpln3DMario_c;
 * _ZTI17dMgTrmpln2Mario_c 0x0213b250, _ZTI18dMgTrmpln3DMario_c 0x0213b244,
 * beside dMgTrmpObjAdapter_c / dMgTrmpRingObjAdapter_c. No call runs from
 * one class's methods into the other's. Functions are written in ROM order
 * under defer_codegen off; do not reorder.
 *
 * Each function keeps its own namespace (ns_<address>) because the shards
 * declare the same names with different shapes; mangled-name callees are
 * declared once at global scope. Five two-word struct copies go through
 * the W2 array-member struct so the build keeps the load-load-store-store
 * order; the two file-global pragmas stay bracketed around their function.
 */

// leftovers: both classes stay free functions over char* -- no key function
// is defined as a real method here, so this TU emits no vtable/typeinfo
// (cartridge copies stay in the module's .data; only Vector3's trivial D1 is
// compiler-only output). The records are read through layout views,
// include/dMgTrmpln2Mario_c.h and dMgTrmpln3DMario_c.h, by the MARIO2() and
// MARIO3D() casts. The per-shard namespaces stay (independent decl shapes would
// collide). r5v/r4v are mContactOffset and mContactHalfWidth, which the drawn
// line writes.
#pragma defer_codegen off
#include "types.h"
#include "common.h"
#include "decl_common.h"
#include "decl_ModelAnim.h"
#include "dMgTrmpln2Mario_c.h"
#include "dMgTrmpln3DMario_c.h"
/* Typed access to the Mario records from the char* helpers below. */
#define MARIO2(p) ((dMgTrmpln2Mario_c *)(p))
#define MARIO3D(p) ((dMgTrmpln3DMario_c *)(p))
struct W2 { int w[2]; };
struct SharedFilePtr { void Release(); };
struct ModelAnim { ~ModelAnim(); };
struct dExtFrameCtrl_c { void Advance(); int WillHitFrame(int) const; };
struct Sound { static void PlayBank2_2D(unsigned int); };
bool ApproachLinear(short &value, short target, short step);
int ApproachLinear(int &r, int b, int c);

// ---- Trmp2Mario_GetVelocity
namespace ns_020c8dd4 {
extern "C" {
// @symbol Trmp2Mario_GetVelocity
int Trmp2Mario_GetVelocity(int p)
{
    return p + 60;
}
}
}
// ---- Trmp2Mario_Reset
namespace ns_020c8ddc {
extern "C" {
extern "C" int pmf_Trmp2Mario_StateMissed[2];
extern "C" int pmf_Trmp2Mario_StateHidden_4[2];

// @symbol Trmp2Mario_Reset
int Trmp2Mario_Reset(char *c)
{
    int *p;
    int *d;
    int result;
    int flag;

    p = MARIO2(c)->mState;
    d = pmf_Trmp2Mario_StateMissed;
    result = 0;
    flag = 1;
    if (p[0] == d[0]) {
        if (p[1] != d[1]) {
            if (MARIO2(c)->mState[0] != 0)
                goto after1;
        }
        flag = 0;
    }
after1:
    if (flag != 0) {
        p = MARIO2(c)->mState;
        d = pmf_Trmp2Mario_StateHidden_4;
        flag = 1;
        if (p[0] == d[0]) {
            if (p[1] != d[1]) {
                if (MARIO2(c)->mState[0] != 0)
                    goto after2;
            }
            flag = 0;
        }
    after2:
        if (flag != 0)
            result = 1;
    }
    return result;
}
}
}
// ---- Trmp2Mario_GetPrevPos
namespace ns_020c8e80 {
extern "C" {
// @symbol Trmp2Mario_GetPrevPos
int Trmp2Mario_GetPrevPos(int p)
{
    return p + 48;
}
}
}
// ---- Trmp2Mario_GetPos
namespace ns_020c8e88 {
extern "C" {
// @symbol Trmp2Mario_GetPos
int Trmp2Mario_GetPos(int p)
{
    return p + 36;
}
}
}
// ---- Trmp2Mario_Render
namespace ns_020c8e90 {
extern "C" {
extern int data_ov006_0212e02c[];
struct C { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void f(void*); };
// @symbol Trmp2Mario_Render
void Trmp2Mario_Render(char *o) {
    if (MARIO2(o)->mVisible == 0)
        return;
    struct C *p = (struct C *)(o + 0x78);
    p->f((void *)data_ov006_0212e02c);
}
}
}
// ---- Trmp2Mario_UpdateMatrix
namespace ns_020c8ecc {
/* recovered: shared common types */
extern "C" {

extern struct Matrix4x3 data_020a0e68;
void Matrix4x3_FromTranslation(struct Matrix4x3 *mF, int x, int y, int z);
void Matrix4x3_ApplyInPlaceToRotationY(struct Matrix4x3 *mF, short angY);
// @symbol Trmp2Mario_UpdateMatrix
void Trmp2Mario_UpdateMatrix(char *o) {
    Matrix4x3_FromTranslation(&data_020a0e68, MARIO2(o)->mPos.x, MARIO2(o)->mPos.y,
                              MARIO2(o)->mPos.z);
    Matrix4x3_ApplyInPlaceToRotationY(&data_020a0e68, MARIO2(o)->mRotY);
    *(struct Matrix4x3 *)(o + 0x94) = data_020a0e68;
}
}
}
// ---- Trmp2Mario_Update
namespace ns_020c8f20 {
typedef int Fix12;
struct Vector3_16f;
struct Callback;
struct System {
    static System* New(unsigned, unsigned, Fix12, Fix12, Fix12, const Vector3_16f*, Callback*);
};
/* Signature deliberately copied from the local declaration above: the
   ROM name carries by-value class parameters (e.g. Fix12<int>), which
   mwccarm passes differently at the call site, so declaring the true
   types breaks the byte match. See notes/mwccarm-codegen.md 6az. */
extern "C" System* _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(unsigned, unsigned, Fix12, Fix12, Fix12, const Vector3_16f*, Callback*);

extern "C" {
extern void Trmp2Mario_ApplyGravity(char *o);
extern void Trmp2Mario_UpdateMatrix(char *o);
extern int sTrmpAnimBounce;
}
System* System::New(unsigned, unsigned, Fix12, Fix12, Fix12, const Vector3_16f*, Callback*);

typedef void (*PMF)(void*);
struct Closure { int off; int adj; };

// @symbol Trmp2Mario_Update
extern "C" void Trmp2Mario_Update(char *o) {
    MARIO2(o)->mPrevPos.x = MARIO2(o)->mPos.x;
    MARIO2(o)->mPrevPos.y = MARIO2(o)->mPos.y;
    MARIO2(o)->mPrevPos.z = MARIO2(o)->mPos.z;
    if (MARIO2(o)->mState[0] != 0) {
        Closure* cl = (Closure*)(o + 0x70);
        void* tobj = o + (cl->adj >> 1);
        void (*fn)();
        if (cl->adj & 1)
            fn = *(void(**)())(*(char**)tobj + cl->off);
        else
            fn = (void(*)())cl->off;
        ((void(*)(void*))fn)(tobj);
    }
    Trmp2Mario_ApplyGravity(o);
    Fix12 v = (Fix12)(((long long)MARIO2(o)->mBounceVy * 0xb4b + 0x800) >> 12);
    if (MARIO2(o)->mVel.y > v) {
        if (*(int *)(o + 0xd8) == sTrmpAnimBounce) {
            MARIO2(o)->mParticleId =
                (int)_ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
                    MARIO2(o)->mParticleId, 0xf5, MARIO2(o)->mPos.x << 3, MARIO2(o)->mPos.y << 3,
                    MARIO2(o)->mPos.z << 3, 0, 0);
        }
    }
    Trmp2Mario_UpdateMatrix(o);
    ((dExtFrameCtrl_c*)(o + 0xc8))->Advance();
}
}
// ---- Trmp2Mario_ApplyGravity
namespace ns_020c9024 {
extern "C" {
extern int sTrmp2FallSpeed[];
int _Z14ApproachLinearRiii(int *a, int b, int c);
void AddVec3(void *dst, void *a, void *b);
// @symbol Trmp2Mario_ApplyGravity
void Trmp2Mario_ApplyGravity(char *o) {
    _Z14ApproachLinearRiii((int *)(o + 0x40), sTrmp2FallSpeed[0], MARIO2(o)->mGravityStep);
    AddVec3(o + 0x24, o + 0x3c, o + 0x24);
}
}
}
// ---- Trmp2Mario_StateKnockedOut
namespace ns_020c905c {
extern "C" {
extern void Trmp2Mario_EnterHidden(char *o);
// @symbol Trmp2Mario_StateKnockedOut
void Trmp2Mario_StateKnockedOut(char *o) {
    if (MARIO2(o)->mPos.y >= -0x120000)
        return;
    MARIO2(o)->mVel.y = 0;
    Trmp2Mario_EnterHidden(o);
}
}
}
// ---- Trmp2Mario_EnterByKind
namespace ns_020c9098 {
typedef int Fix12;
struct BCA_File;
struct ModelAnim {
    void SetAnim(BCA_File *f, int a, Fix12 b, unsigned int c);
};
/* Signature deliberately copied from the local declaration above: the
   ROM name carries by-value class parameters (e.g. Fix12<int>), which
   mwccarm passes differently at the call site, so declaring the true
   types breaks the byte match. See notes/mwccarm-codegen.md 6az. */
extern "C" void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *, BCA_File *f, int a, Fix12 b, unsigned int c);


extern "C" {
extern int pmf_Trmp2Mario_StateHidden_5[2];
extern int pmf_Trmp2Mario_StateRespawnWait[2];
extern int data_ov006_02140540[];
extern int pmf_Trmp2Mario_StateKnockedOut[2];
extern void Trmp2Mario_EnterHidden(char *c);
extern void D3D_PlaySeAtX(int a, int b);
}

// @symbol Trmp2Mario_EnterByKind
extern "C" void Trmp2Mario_EnterByKind(char *c)
{
    int *p;
    int *d;

    p = MARIO2(c)->mState;
    d = pmf_Trmp2Mario_StateHidden_5;
    if (p[0] == d[0]) {
        if (p[1] != d[1]) {
            if (MARIO2(c)->mState[0] != 0)
                goto check2;
        }
        return;
    }
check2:
    p = MARIO2(c)->mState;
    d = pmf_Trmp2Mario_StateRespawnWait;
    if (p[0] == d[0]) {
        if (p[1] != d[1]) {
            if (MARIO2(c)->mState[0] != 0)
                goto body;
        }
        Trmp2Mario_EnterHidden(c);
        return;
    }
body:
    MARIO2(c)->mGravityStep = 0x100;
    MARIO2(c)->mVel.x = 0;
    MARIO2(c)->mVel.y = 0x2000;
    D3D_PlaySeAtX(0x1c9, MARIO2(c)->mPos.x);
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj((ModelAnim *)(c + 0x78), (BCA_File *)data_ov006_02140540[0], 0, 0x800, 0);
    *(int *)(c + 0xd0) = 0;
    {
        int a = pmf_Trmp2Mario_StateKnockedOut[0];
        int b = pmf_Trmp2Mario_StateKnockedOut[1];
        MARIO2(c)->mState[0] = b ? a : a;
        MARIO2(c)->mState[1] = b;
    }
}
}
// ---- Trmp2Mario_StateBounce
namespace ns_020c91ac {

extern "C" {
void Trmp2Mario_EnterFall(void *c);
/* local extern: the call passes an untyped this, so it cannot use the header method. */
int _ZNK15dExtFrameCtrl_c12WillHitFrameEi(void *thisPtr, int frame);
void D3D_PlaySeAtX(int a0, int a1);
void Camera_ProjectToScreen16(void *a0, void *a1, short *a2);
int _Z14ApproachLinearRiii(int *v, int step, int rate);
void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *thisPtr, void *file, int i, int fix, unsigned int flags);
void Sound_PlayBank1Panned(int a0, int a1, int a2);
}

extern "C" int sTrmpAnimBounce;
extern "C" void *sMgMainCamera;
extern "C" int data_ov006_02140574;
extern "C" int sTrmp2RiseSpeedMax;
extern "C" void *data_ov006_0213b22c[];
extern "C" int sTrmp2FallSpeed;

struct VtObj {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void m4();
};

// @symbol Trmp2Mario_StateBounce
extern "C" void Trmp2Mario_StateBounce(char *c) {
    int v24;

    if (MARIO2(c)->mVel.y <= 0) {
        Trmp2Mario_EnterFall(c);
        return;
    }

    if (*(int *)(c + 0xd8) == sTrmpAnimBounce) {
        if (_ZNK15dExtFrameCtrl_c12WillHitFrameEi((void *)(c + 0xc8), 0xc) != 0 ||
            _ZNK15dExtFrameCtrl_c12WillHitFrameEi((void *)(c + 0xc8), 0x18) != 0) {
            D3D_PlaySeAtX(0x1b5, MARIO2(c)->mPos.x);
        }
    }

    Camera_ProjectToScreen16(sMgMainCamera, (void *)(c + 0x24), MARIO2(c)->mScreenPos);

    v24 = MARIO2(c)->mPos.x;

    if (v24 >= -0x68000) goto L5c;
    if (MARIO2(c)->mVel.x < 0)
        goto L70;

L5c:
    if (v24 <= 0x68000) goto L230;
    if (MARIO2(c)->mVel.x <= 0)
        goto L230;

L70:
    {
        int v = v24;
        if (v < -0x90000) v = -0x90000;
        else if (v > 0x90000) v = 0x90000;
        MARIO2(c)->mPos.x = v;
    }

    if (*(s16 *)(c + 0x22) != 0) goto L1a4;
    if (_Z14ApproachLinearRiii((int *)(c + 0x64), 5, 1) != 0) goto L1a4;
    {
        int t;

        MARIO2(c)->mAnim = 2;
        _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj((void *)(c + 0x78),
                                                    *(void **)data_ov006_0213b22c[MARIO2(c)->mAnim],
                                                    0x40000000, 0x800, 0);

        *(int *)(c + 0xd0) = 0;
        Sound_PlayBank1Panned(0, MARIO2(c)->mAnim, MARIO2(c)->mPos.x);

        t = (int)(((long long)(-MARIO2(c)->mVel.x) * 0x1200 + 0x800) >> 12);
        if (t < -0x1400) t = -0x1400;
        else if (t > 0x1400) t = 0x1400;
        MARIO2(c)->mVel.x = t;

        *(int *)(((int)c + 0x40)) +=
            (int)(((long long)data_ov006_02140574 * 0x400 + 0x800) >> 12);

        {
            int v40 = sTrmp2RiseSpeedMax;
            if (MARIO2(c)->mVel.y <= v40)
                v40 = MARIO2(c)->mVel.y;
            MARIO2(c)->mVel.y = v40;
        }
    }
    goto L260;

L1a4:
    {
    int t = (int)(((long long)(-MARIO2(c)->mVel.x) * 0xf00 + 0x800) >> 12);
    int v40;
    int hi;
    int lo;

    MARIO2(c)->mVel.x = t;

    t = MARIO2(c)->mPos.x;
    if (t < -0x68000)
        t = -0x68000;
    else if (t > 0x68000)
        t = 0x68000;
    MARIO2(c)->mPos.x = t;

    hi = sTrmp2RiseSpeedMax;
    lo = sTrmp2FallSpeed;
    v40 = MARIO2(c)->mVel.y;
    if (v40 < lo) {
        v40 = lo;
    } else {
        if (v40 <= hi)
            hi = v40;
        v40 = hi;
    }
    MARIO2(c)->mVel.y = v40;
    }
    goto L260;

L230:
    if (MARIO2(c)->mContact == 3) {
        ((VtObj *)c)->m4();
        *(int *)(((int)c + 0x3c)) *= -1;
    }

L260:
    {
    int v = MARIO2(c)->mVel.x;
    if (v > 0x2000) {
        ApproachLinear(MARIO2(c)->mRotY, 0x2000, 0xc00);
    } else if (v < -0x2000) {
        ApproachLinear(MARIO2(c)->mRotY, -0x2000, 0xc00);
    } else {
        ApproachLinear(MARIO2(c)->mRotY, (short)v, 0xc00);
    }
}
}
}
// ---- Trmp2Mario_BounceOffLineA
namespace ns_020c94e0 {

extern "C" {
int DotVec3(const Vector3 *a, const Vector3 *b);
void Vec3_MulScalar(Vector3 *out, const Vector3 *in, int scale);
void SubVec3(Vector3 *a, Vector3 *b, Vector3 *c);
void AddVec3(Vector3 *a, Vector3 *b, Vector3 *c);
int _ZN4cstd4fdivEii(int a, int b);
void *_ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
    unsigned int a, unsigned int b, int fx1, int fx2, int fx3, const void *vec, void *cb);
void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *thisPtr, void *file, int i, int fix, unsigned int flags);
void Sound_PlayBank1Panned(int a0, int a1, int a2);
int D3D_PlaySeAtX(int a, int b);
void Trmp2Mario_StateBounce(char *c);
}

extern "C" int sTrmp2RiseSpeedMax;
extern "C" int sTrmp2GravityStep;
extern "C" int pmf_Trmp2Mario_StateAppearWait_2[2];
extern "C" void *sTrmpAnimBounce;
extern "C" int pmf_Trmp2Mario_StateBounce_2[2];

struct VtObj {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void m4();
};


// @symbol Trmp2Mario_BounceOffLineA
extern "C" void Trmp2Mario_BounceOffLineA(char *c)
{
    Vector3 tmp, tmp2, tmp3;
    int r5v, r4v, dot, scale, fdivr, v, fx, cur;

    r5v = MARIO2(c)->mContactOffset;
    r4v = MARIO2(c)->mContactHalfWidth;
    if (r5v < 0) r5v = -r5v;
    {
        int *src = (int *)(c + 4);
        tmp.x = src[0]; tmp.y = src[1]; tmp.z = src[2];
    }

    dot = DotVec3(&MARIO2(c)->mVel, &tmp);
    scale = (int)(((long long)dot * 0x1400 + 0x800) >> 12);
    Vec3_MulScalar(&tmp2, &tmp, scale);
    SubVec3(&MARIO2(c)->mVel, &tmp2, &MARIO2(c)->mVel);

    fdivr = _ZN4cstd4fdivEii(r4v, r4v + r5v);
    scale = (int)(((long long)sTrmp2RiseSpeedMax * fdivr + 0x800) >> 12);
    Vec3_MulScalar(&tmp3, &tmp, scale);
    AddVec3(&MARIO2(c)->mVel, &tmp3, &MARIO2(c)->mVel);

    v = MARIO2(c)->mVel.x;
    if (v < -0x3000) v = -0x3000;
    else if (v > 0x3000) v = 0x3000;
    MARIO2(c)->mVel.x = v;

    fx = (int)(((long long)sTrmp2RiseSpeedMax * 0xc00 + 0x800) >> 12);
    cur = MARIO2(c)->mVel.y;
    if (cur >= fx) fx = cur;
    MARIO2(c)->mVel.y = fx;

    MARIO2(c)->mGravityStep = sTrmp2GravityStep;

    {
        Vector3_16 vec16;
        int y = tmp.y;
        int z = tmp.z;
        int x = tmp.x;
        vec16.x = (s16)x;
        vec16.y = (s16)y;
        char *bp = c + 0x70;
        int *s = (int *)(bp);
        vec16.z = (s16)(z + (int)((unsigned)bp - (unsigned)bp));

        int *q = pmf_Trmp2Mario_StateAppearWait_2;
        if (s[0] != q[0] || (s[1] != q[1] && MARIO2(c)->mState[0] != 0)) {

            _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
                0, 0xf3, (MARIO2(c)->mPos.x) << 3, (MARIO2(c)->mPos.y) << 3,
                (MARIO2(c)->mPos.z) << 3, &vec16, 0);
            _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
                0, 0xf4, (MARIO2(c)->mPos.x) << 3, (MARIO2(c)->mPos.y) << 3,
                (MARIO2(c)->mPos.z) << 3, &vec16, 0);
            MARIO2(c)->mParticleId =
                (int)_ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
                    *(unsigned int *)(c + 0x5c), 0xf5, (MARIO2(c)->mPos.x) << 3,
                    (MARIO2(c)->mPos.y) << 3, (MARIO2(c)->mPos.z) << 3, 0, 0);
        }
    }

    MARIO2(c)->mBounceVy = MARIO2(c)->mVel.y;
    ((VtObj *)c)->m4();
    MARIO2(c)->mWallBumpTimer = 0;
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj((void *)(c + 0x78), sTrmpAnimBounce, 0x40000000,
                                                0x800, 0);
    *(int *)(c + 0xd0) = 0;
    Sound_PlayBank1Panned(0, 4, MARIO2(c)->mPos.x);
    D3D_PlaySeAtX(0x1b5, MARIO2(c)->mPos.x);
    *(int *)(c + 0x68) = 0;
    {
        int a = pmf_Trmp2Mario_StateBounce_2[0];
        int b = pmf_Trmp2Mario_StateBounce_2[1];
        a = b ? a : a;
        MARIO2(c)->mState[0] = a;
        MARIO2(c)->mState[1] = b;
    }
    Trmp2Mario_StateBounce(c);
}
}
// ---- Trmp2Mario_StateWallBounce
namespace ns_020c97bc {

extern "C" {
void Trmp2Mario_EnterFall(void *c);
void Camera_ProjectToScreen16(void *a0, void *a1, short *a2);
int _Z14ApproachLinearRiii(int *v, int step, int rate);
void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *thisPtr, void *file, int i, int fix, unsigned int flags);
void Sound_PlayBank1Panned(int a0, int a1, int a2);
}

extern "C" void *sMgMainCamera;
extern "C" int data_ov006_02140574;
extern "C" int sTrmp2RiseSpeedMax;
extern "C" void *data_ov006_0213b22c[];
extern "C" int sTrmp2FallSpeed;

struct VtObj {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void m4();
};

// @symbol Trmp2Mario_StateWallBounce
extern "C" void Trmp2Mario_StateWallBounce(char *c) {
    int v24;

    if (MARIO2(c)->mVel.y <= 0) {
        Trmp2Mario_EnterFall(c);
        return;
    }

    Camera_ProjectToScreen16(sMgMainCamera, (void *)(c + 0x24), MARIO2(c)->mScreenPos);

    v24 = MARIO2(c)->mPos.x;

    if (v24 >= -0x68000) goto L5c;
    if (MARIO2(c)->mVel.x < 0)
        goto L70;

L5c:
    if (v24 <= 0x68000) goto L230;
    if (MARIO2(c)->mVel.x <= 0)
        goto L230;

L70:
    {
        int v = v24;
        if (v < -0x90000) v = -0x90000;
        else if (v > 0x90000) v = 0x90000;
        MARIO2(c)->mPos.x = v;
    }

    if (*(s16 *)(c + 0x22) != 0) goto L1a4;
    if (_Z14ApproachLinearRiii((int *)(c + 0x64), 5, 1) != 0) goto L1a4;
    {
        int t = (int)(((long long)(-MARIO2(c)->mVel.x) * 0x1200 + 0x800) >> 12);
        int v40;

        if (t < -0x1400) t = -0x1400;
        else if (t > 0x1400) t = 0x1400;
        MARIO2(c)->mVel.x = t;

        *(int *)(((int)c + 0x40)) +=
            (int)(((long long)data_ov006_02140574 * 0x400 + 0x800) >> 12);

        v40 = sTrmp2RiseSpeedMax;
        if (MARIO2(c)->mVel.y <= v40)
            v40 = MARIO2(c)->mVel.y;
        MARIO2(c)->mVel.y = v40;

        MARIO2(c)->mAnim = 2;
        _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj((void *)(c + 0x78),
                                                    *(void **)data_ov006_0213b22c[MARIO2(c)->mAnim],
                                                    0x40000000, 0x800, 0);

        *(int *)(c + 0xd0) = 0;
        Sound_PlayBank1Panned(0, MARIO2(c)->mAnim, MARIO2(c)->mPos.x);
    }
    goto L260;

L1a4:
    {
    int t = (int)(((long long)(-MARIO2(c)->mVel.x) * 0xf00 + 0x800) >> 12);
    int pos;
    int hi;
    int lo;
    int v40;

    MARIO2(c)->mVel.x = t;

    pos = MARIO2(c)->mPos.x;
    if (pos < -0x68000)
        pos = -0x68000;
    else if (pos > 0x68000)
        pos = 0x68000;
    MARIO2(c)->mPos.x = pos;

    hi = sTrmp2RiseSpeedMax;
    lo = sTrmp2FallSpeed;
    v40 = MARIO2(c)->mVel.y;
    if (v40 < lo) {
        v40 = lo;
    } else {
        if (v40 <= hi)
            hi = v40;
        v40 = hi;
    }
    MARIO2(c)->mVel.y = v40;
    }
    goto L260;

L230:
    if (MARIO2(c)->mContact == 3) {
        ((VtObj *)c)->m4();
        *(int *)(((int)c + 0x3c)) *= -1;
    }

L260:
    {
    int v = MARIO2(c)->mVel.x;
    if (v > 0x2000) {
        ApproachLinear(MARIO2(c)->mRotY, 0x2000, 0xc00);
    } else if (v < -0x2000) {
        ApproachLinear(MARIO2(c)->mRotY, -0x2000, 0xc00);
    } else {
        ApproachLinear(MARIO2(c)->mRotY, (short)v, 0xc00);
    }
}
}
}
// ---- Trmp2Mario_BounceOffLineB
namespace ns_020c9aa0 {
/* recovered: shared common types, declarations from a shared header */
/* recovered: shared common types */


extern "C" {
int DotVec3(const Vector3 *a, const Vector3 *b);
void Vec3_MulScalar(Vector3 *out, const Vector3 *in, int scale);
void SubVec3(Vector3 *a, Vector3 *b, Vector3 *c);
void AddVec3(Vector3 *a, Vector3 *b, Vector3 *c);
int _ZN4cstd4fdivEii(int a, int b);
void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *thisPtr, void *file, int i, int fix, unsigned int flags);
void Sound_PlayBank1Panned(int a0, int a1, int a2);
void Trmp2Mario_StateWallBounce(char *c);
}


struct VtObj {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void m4();
};

// @symbol Trmp2Mario_BounceOffLineB
extern "C" void Trmp2Mario_BounceOffLineB(char *c)
{
    Vector3 tmp;
    Vector3 tmp2;
    Vector3 tmp3;
    int r5v;
    int r4v;
    int dot;
    int scale;
    int fdivr;
    int vx;

    r5v = MARIO2(c)->mContactOffset;
    r4v = MARIO2(c)->mContactHalfWidth;
    if (r5v < 0) r5v = -r5v;
    {
        int *src = (int *)(c + 4);
        tmp.x = src[0];
        tmp.y = src[1];
        tmp.z = src[2];
    }

    dot = DotVec3(&MARIO2(c)->mVel, &tmp);
    scale = (int)(((long long)dot * 0x1200 + 0x800) >> 12);
    Vec3_MulScalar(&tmp2, &tmp, scale);
    SubVec3(&MARIO2(c)->mVel, &tmp2, &MARIO2(c)->mVel);

    fdivr = _ZN4cstd4fdivEii(r4v, r4v + r5v);
    scale = (int)(((long long)data_ov006_02140574 * fdivr + 0x800) >> 12);
    Vec3_MulScalar(&tmp3, &tmp, scale);
    AddVec3(&MARIO2(c)->mVel, &tmp3, &MARIO2(c)->mVel);

    vx = MARIO2(c)->mVel.x;
    if (vx < -0x2800) vx = -0x2800;
    else if (vx > 0x2800) vx = 0x2800;
    MARIO2(c)->mVel.x = vx;

    {
        int fx = (int)(((long long)data_ov006_02140574 * 0x600 + 0x800) >> 12);
        int cur = MARIO2(c)->mVel.y;
        if (cur >= fx) fx = cur;
        MARIO2(c)->mVel.y = fx;
    }

    MARIO2(c)->mGravityStep = sTrmp2GravityStep;
    ((VtObj *)c)->m4();

    MARIO2(c)->mWallBumpTimer = 0;
    if (MARIO2(c)->mAnim != 0) {
        MARIO2(c)->mAnim = 0;
    } else {
        MARIO2(c)->mAnim = 1;
    }

    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(
        (void *)(c + 0x78), *(void **)data_ov006_0213b22c[MARIO2(c)->mAnim], 0x40000000, 0x800, 0);

    *(int *)(c + 0xd0) = 0;
    Sound_PlayBank1Panned(0, MARIO2(c)->mAnim, MARIO2(c)->mPos.x);

    {
        int a = pmf_Trmp2Mario_StateWallBounce_2[0];
        int b = pmf_Trmp2Mario_StateWallBounce_2[1];
        a = b ? a : a;
        MARIO2(c)->mState[0] = a;
        MARIO2(c)->mState[1] = b;
    }
    Trmp2Mario_StateWallBounce(c);
}
}
// ---- Trmp2Mario_EnterBounce
namespace ns_020c9c8c {
typedef int Fix12;
struct BCA_File;
struct ModelAnim {
    void SetAnim(BCA_File *f, int a, Fix12 b, unsigned int c);
};
/* Signature deliberately copied from the local declaration above: the
   ROM name carries by-value class parameters (e.g. Fix12<int>), which
   mwccarm passes differently at the call site, so declaring the true
   types breaks the byte match. See notes/mwccarm-codegen.md 6az. */
extern "C" void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *, BCA_File *f, int a, Fix12 b, unsigned int c);

struct Pair { int a, b; };

struct Obj {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void slot4();
};

extern "C" {
extern int sTrmp2GravityStep;
extern int data_ov006_02140574;
extern BCA_File *sTrmpAnimBounce;
extern Pair pmf_Trmp2Mario_StateBounce;
extern void D3D_PlaySeAtX(int a, int b);
extern void Trmp2Mario_StateBounce(char *c);
}

// @symbol Trmp2Mario_EnterBounce
extern "C" void Trmp2Mario_EnterBounce(char *c) {
    Obj *o = (Obj *)c;
    int a, b;
    MARIO2(c)->mGravityStep = sTrmp2GravityStep;
    MARIO2(c)->mVel.y = (int)(((long long)data_ov006_02140574 * 0xc00 + 0x800) >> 12);
    MARIO2(c)->mBounceVy = MARIO2(c)->mVel.y;
    o->slot4();
    MARIO2(c)->mWallBumpTimer = 0;
    MARIO2(c)->mAnim = 0;
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj((ModelAnim *)(c + 0x78), sTrmpAnimBounce,
                                                0x40000000, 0x800, 0);
    *(int *)(c + 0xd0) = 0;
    D3D_PlaySeAtX(0x110, MARIO2(c)->mPos.x);
    D3D_PlaySeAtX(0x1b5, MARIO2(c)->mPos.x);
    *(int *)(c + 0x68) = 0;
    a = pmf_Trmp2Mario_StateBounce.a;
    b = pmf_Trmp2Mario_StateBounce.b;
    MARIO2(c)->mState[0] = b ? a : a;
    MARIO2(c)->mState[1] = b;
    Trmp2Mario_StateBounce(c);
}
}
// ---- Trmp2Mario_StateRespawnWait
namespace ns_020c9d7c {
extern "C" {
/* best near-miss div=2 @ mwccarm 1.2/sp2p3 */
extern int RandomIntInternal(int *seed);
extern void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *thiz, void *bca, int a, int fix, unsigned int b);
extern void Trmp2Mario_EnterFall(void *c);
extern "C" int data_0209e650;
extern "C" int data_ov006_021405a4;
extern "C" void *data_ov006_02140580;

// @symbol Trmp2Mario_StateRespawnWait
void Trmp2Mario_StateRespawnWait(char *c) {
    unsigned int r;
    int tbl;
    MARIO2(c)->mTimer -= 1;
    if (MARIO2(c)->mTimer == 0) {
        MARIO2(c)->mPos.y = 0x100000;
        r = ((unsigned int)RandomIntInternal(&data_0209e650) & 0x7fffffff) >> 0x13;
        MARIO2(c)->mPos.x = ((int)r - 0x800) * 0xc0;
        MARIO2(c)->mVel.y = 0;
        tbl = data_ov006_021405a4;
        r = ((unsigned int)RandomIntInternal(&data_0209e650) & 0x7fffffff) >> 0x13;
        MARIO2(c)->mVel.x = (int)(((long long)(((int)r - 0x800) << 1) * tbl + 0x800) >> 12);
        _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x78, data_ov006_02140580, 0x40000000,
                                                    0x800, 0);
        MARIO2(c)->mPrevPos.x = MARIO2(c)->mPos.x;
        MARIO2(c)->mPrevPos.y = MARIO2(c)->mPos.y;
        MARIO2(c)->mPrevPos.z = MARIO2(c)->mPos.z;
        Trmp2Mario_EnterFall(c);
    } else {
        MARIO2(c)->mPos.y = 0x100000;
        MARIO2(c)->mVel.y = 0;
    }
}
}
}
// ---- Trmp2Mario_EnterRespawnWait
namespace ns_020c9e7c {
extern "C" {

extern void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *, void *, int, unsigned int, int);
extern "C" void *data_ov006_02140580;
struct Vec2i { int x; int y; };
extern "C" struct Vec2i pmf_Trmp2Mario_StateRespawnWait_2;
// @symbol Trmp2Mario_EnterRespawnWait
void Trmp2Mario_EnterRespawnWait(unsigned char *c) {
    MARIO2(c)->mTimer = 0x3c;
    MARIO2(c)->mPos.y = 0x100000;
    MARIO2(c)->mPrevPos.x = MARIO2(c)->mPos.x;
    MARIO2(c)->mPrevPos.y = MARIO2(c)->mPos.y;
    MARIO2(c)->mPrevPos.z = MARIO2(c)->mPos.z;
    MARIO2(c)->mVel.y = 0;
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x78, data_ov006_02140580, 0x40000000, 0x800,
                                                0);
    *(W2 *)(c + 0x70) = *(W2 *)&pmf_Trmp2Mario_StateRespawnWait_2;
}
}
}
// ---- Trmp2Mario_StateMissed
namespace ns_020c9efc {
typedef long long s64;
extern "C" {
extern void Puff_Spawn(int a, int b);
}
extern "C" {
extern void Trmp2Mario_EnterRespawnWait(void *p);
}
extern "C" int data_ov006_02140598;
extern "C" int data_ov006_0213b0f0;

struct Obj {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
};

// @symbol Trmp2Mario_StateMissed
extern "C" void Trmp2Mario_StateMissed(char *c) {
    *(short *)(((int)c + 0x6c)) = *(short *)(((int)c + 0x6c)) - 1;
    if (MARIO2(c)->mTimer == 0) {
        Puff_Spawn(MARIO2(c)->mScreenPos[0], 0xc0);
        data_ov006_02140598 = data_ov006_02140598 - 1;
        ApproachLinear(data_ov006_0213b0f0, 0, 1);
        Sound::PlayBank2_2D(0x130);
        ((Obj *)c)->v4();
        MARIO2(c)->mWallBumpTimer = 0;
        Trmp2Mario_EnterRespawnWait(c);
    } else {
        int v = MARIO2(c)->mVel.x;
        MARIO2(c)->mVel.x = (int)(((s64)v * 0xc00 + 0x800) >> 12);
        int x = MARIO2(c)->mPos.x;
        if (x < -0x6c000)
            MARIO2(c)->mPos.x = -0x6c000;
        else if (x > 0x6c000)
            MARIO2(c)->mPos.x = 0x6c000;
    }
}
}
// ---- Trmp2Mario_EnterMissed
namespace ns_020c9fe4 {
extern "C" {
extern void D3D_PlaySeAtX(int a, int b);
extern void _ZN5Sound12PlayBank2_2DEj(unsigned int);
extern void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void*, void*, int, int, unsigned int);
extern int data_ov006_0213b0f0[];
extern void *data_ov006_02140540;
extern double pmf_Trmp2Mario_StateMissed_2;
void Trmp2Mario_EnterMissed(char *c);
// @symbol Trmp2Mario_EnterMissed
void Trmp2Mario_EnterMissed(char *c) {
    if (data_ov006_0213b0f0[0] > 1)
        D3D_PlaySeAtX(0x1ca, MARIO2(c)->mPos.x);
    else
        _ZN5Sound12PlayBank2_2DEj(0x1c9);
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x78, *(void**)&data_ov006_02140540, 0, 0x800, 0);
    MARIO2(c)->mTimer = 0x28;
    *(double *)(c + 0x70) = pmf_Trmp2Mario_StateMissed_2;
}
}
}
// ---- Trmp2Mario_StateFall
namespace ns_020ca070 {

extern "C" {
void Trmp2Mario_BounceOffLineB(char *c);
void Trmp2Mario_BounceOffLineA(char *c);
void Camera_ProjectToScreen16(void *a0, void *a1, short *a2);
int _Z14ApproachLinearRiii(int *v, int step, int rate);
void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *thisPtr, void *file, int i, int fix, unsigned int flags);
void Sound_PlayBank1Panned(int a0, int a1, int a2);
void Trmp2Mario_EnterMissed(char *c);
}

extern "C" void *sMgMainCamera;
extern "C" void *data_ov006_0213b22c[];

struct S8 { int a, b; };
extern "C" S8 pmf_Trmp2Mario_StateWallBounce;

struct VtObj {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void m4();
};

// @symbol Trmp2Mario_StateFall
extern "C" void Trmp2Mario_StateFall(char *c) {
    u16 state = MARIO2(c)->mContact;
    int v24;

    if (state == 1) {
        Trmp2Mario_BounceOffLineB(c);
        return;
    }
    if (state == 2) {
        Trmp2Mario_BounceOffLineA(c);
        return;
    }

    Camera_ProjectToScreen16(sMgMainCamera, (void *)(c + 0x24), MARIO2(c)->mScreenPos);

    v24 = MARIO2(c)->mPos.x;

    if (v24 >= -0x68000) goto L5c;
    if (MARIO2(c)->mVel.x < 0)
        goto L70;

L5c:
    if (v24 <= 0x68000) goto L230;
    if (MARIO2(c)->mVel.x <= 0)
        goto L230;

L70:
    {
        int v = v24;
        if (v < -0x90000) v = -0x90000;
        else if (v > 0x90000) v = 0x90000;
        MARIO2(c)->mPos.x = v;
    }

    *(int *)(((int)c + 0x3c)) *= -1;
    if (MARIO2(c)->mVel.y <= -0x800)
        goto L260;

    if (*(s16 *)(c + 0x22) != 0) goto L1a4;
    if (_Z14ApproachLinearRiii((int *)(c + 0x64), 5, 1) != 0) goto L1a4;
    {
        MARIO2(c)->mVel.y = 0x800;
        MARIO2(c)->mAnim = 2;
        _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj((void *)(c + 0x78),
                                                    *(void **)data_ov006_0213b22c[MARIO2(c)->mAnim],
                                                    0x40000000, 0x800, 0);

        *(int *)(c + 0xd0) = 0;
        Sound_PlayBank1Panned(0, MARIO2(c)->mAnim, MARIO2(c)->mPos.x);

        {
            long long ll = *(long long *)&pmf_Trmp2Mario_StateWallBounce;
            MARIO2(c)->mState[0] = (int)ll;
            MARIO2(c)->mState[1] = (int)((unsigned long long)ll >> 32);
        }
    }
    return;

L1a4:
    {
    int t = (int)(((long long)(-MARIO2(c)->mVel.x) * 0xf00 + 0x800) >> 12);
    int pos;

    MARIO2(c)->mVel.x = t;

    pos = MARIO2(c)->mPos.x;
    if (pos < -0x68000)
        pos = -0x68000;
    else if (pos > 0x68000)
        pos = 0x68000;
    MARIO2(c)->mPos.x = pos;
    }
    goto L260;

L230:
    if (MARIO2(c)->mContact == 3) {
        ((VtObj *)c)->m4();
        *(int *)(((int)c + 0x3c)) *= -1;
    }

L260:
    {
    int v = MARIO2(c)->mVel.x;
    if (v > 0x2000) {
        ApproachLinear(MARIO2(c)->mRotY, 0x2000, 0xc00);
    } else if (v < -0x2000) {
        ApproachLinear(MARIO2(c)->mRotY, -0x2000, 0xc00);
    } else {
        ApproachLinear(MARIO2(c)->mRotY, (short)v, 0xc00);
    }
    }

        if (MARIO2(c)->mPos.y >= -0xc8000)
            return;

        Trmp2Mario_EnterMissed(c);
    }
}
// ---- Trmp2Mario_EnterFall
namespace ns_020ca2ec {
extern "C" {
typedef struct { int a, b; } S8;
extern "C" S8 pmf_Trmp2Mario_StateFall;
extern void Trmp2Mario_StateFall(void *self);

// @symbol Trmp2Mario_EnterFall
void Trmp2Mario_EnterFall(void *self) {
    *(W2 *)((char *)self + 0x70) = *(W2 *)&pmf_Trmp2Mario_StateFall;
    Trmp2Mario_StateFall(self);
}
}
}
// ---- Trmp2Mario_StateAppearWait
namespace ns_020ca310 {
extern "C" int _Z15ApproachLinear2Rsss(short&, short, short);
extern "C" void Trmp2Mario_EnterBounce(char *, int);
// @symbol Trmp2Mario_StateAppearWait
extern "C" void Trmp2Mario_StateAppearWait(char *c) {
    if (_Z15ApproachLinear2Rsss(MARIO2(c)->mTimer, 0, 1) == 0) {
        MARIO2(c)->mPos.y = 0;
        return;
    }
    MARIO2(c)->mPos.y = 0;
    MARIO2(c)->mPrevPos.x = MARIO2(c)->mPos.x;
    MARIO2(c)->mPrevPos.y = MARIO2(c)->mPos.y;
    MARIO2(c)->mPrevPos.z = MARIO2(c)->mPos.z;
    MARIO2(c)->mVisible = 1;
    Trmp2Mario_EnterBounce(c, 1);
}
}
// ---- Trmp2Mario_EnterAppearWait
namespace ns_020ca374 {
extern "C" {
struct S2{int w[2];};
extern "C" struct S2 pmf_Trmp2Mario_StateAppearWait;
// @symbol Trmp2Mario_EnterAppearWait
void Trmp2Mario_EnterAppearWait(char *o, short v) {
    MARIO2(o)->mTimer = v;
    MARIO2(o)->mGravityStep = 0;
    *(struct S2 *)(o + 0x70) = pmf_Trmp2Mario_StateAppearWait;
}
}
}
// ---- Trmp2Mario_StateHidden
namespace ns_020ca39c {
extern "C" {
// @symbol Trmp2Mario_StateHidden
void Trmp2Mario_StateHidden(int *p) {
    p[10] = 0;
}
}
}
// ---- Trmp2Mario_EnterHidden
namespace ns_020ca3a8 {
typedef int Fix12;
struct BCA_File;
struct ModelAnim { int pad; void SetAnim(BCA_File *f, int a, Fix12 b, unsigned int c); };
/* Signature deliberately copied from the local declaration above: the
   ROM name carries by-value class parameters (e.g. Fix12<int>), which
   mwccarm passes differently at the call site, so declaring the true
   types breaks the byte match. See notes/mwccarm-codegen.md 6az. */
extern "C" void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *, BCA_File *f, int a, Fix12 b, unsigned int c);

extern "C" {
extern int data_020a0ebc[];
extern int data_ov006_02140564[];
extern double pmf_Trmp2Mario_StateHidden_3;
}

// @symbol Trmp2Mario_EnterHidden
extern "C" void Trmp2Mario_EnterHidden(char *c) {
    MARIO2(c)->mVisible = 0;
    MARIO2(c)->mPos.y = 0;
    MARIO2(c)->mPos.x = 0;
    MARIO2(c)->mPos.z = 0;
    MARIO2(c)->mVel.x = data_020a0ebc[0];
    MARIO2(c)->mVel.y = data_020a0ebc[1];
    MARIO2(c)->mVel.z = data_020a0ebc[2];
    MARIO2(c)->mGravityStep = 0;
    MARIO2(c)->mWallBumpTimer = 0;
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj((ModelAnim *)(c + 0x78), (BCA_File *)data_ov006_02140564[0], 0, 0x800, 0);
    *(double *)(c + 0x70) = pmf_Trmp2Mario_StateHidden_3;
}
}
// ---- Trmp2Mario_Load
namespace ns_020ca430 {
extern "C" {
typedef struct { int w[2]; } SharedFilePtr;
typedef struct BMD_File BMD_File;

extern "C" SharedFilePtr data_ov006_021405f8;
extern "C" SharedFilePtr data_ov006_02140608;
extern "C" SharedFilePtr data_ov006_021405d0;
extern "C" SharedFilePtr data_ov006_02140628;
extern "C" SharedFilePtr data_ov006_02140618;
extern "C" SharedFilePtr data_ov006_02140638;
extern "C" SharedFilePtr data_ov006_021405f0;
extern "C" SharedFilePtr data_ov006_021405e8;
extern "C" SharedFilePtr data_ov006_02140600;
extern "C" SharedFilePtr data_ov006_021405e0;
extern "C" SharedFilePtr data_ov006_02140610;
extern "C" SharedFilePtr data_ov006_021405d8;
extern "C" SharedFilePtr data_ov006_02140620;
extern "C" SharedFilePtr data_ov006_02140630;

extern "C" void* data_ov006_02140590;
extern "C" void* data_ov006_02140560;
extern "C" void* data_ov006_02140580;
extern "C" void* data_ov006_021405c0;
extern "C" void* data_ov006_0214054c;
extern "C" void* data_ov006_02140564;
extern "C" void* data_ov006_021405a0;
extern "C" void* data_ov006_0214057c;
extern "C" void* data_ov006_0214056c;
extern "C" void* data_ov006_02140568;
extern "C" void *sTrmpAnimBounce;
extern "C" void* data_ov006_02140540;
extern "C" void* data_ov006_021405c4;

extern "C" char *sMgMainCamera;

extern BMD_File* _ZN5Model8LoadFileER13SharedFilePtr(SharedFilePtr* f);
/* local extern: the call passes an untyped this, so it cannot use the header method. */
extern void* _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(SharedFilePtr* f);
extern int _ZN9ModelBase7SetFileEP8BMD_Fileii(void* self, BMD_File* f, int a, int b);
extern void Camera_ProjectToScreen16(char* p, void* q, short* s);
extern void func_02016a14(void* self, int a, int b);
extern void func_02016a04(void* self, int a);
extern void Trmp2Mario_EnterHidden(char *c);

// @symbol Trmp2Mario_Load
int Trmp2Mario_Load(char* c)
{
    BMD_File* f;
    int ret;

    f = _ZN5Model8LoadFileER13SharedFilePtr(&data_ov006_021405f8);
    data_ov006_02140590 = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_02140608);
    data_ov006_02140560 = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_021405d0);
    data_ov006_02140580 = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_02140628);
    data_ov006_021405c0 = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_02140618);
    data_ov006_0214054c = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_02140638);
    data_ov006_02140564 = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_021405f0);
    data_ov006_021405a0 = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_021405e8);
    data_ov006_0214057c = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_02140600);
    data_ov006_0214056c = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_021405e0);
    data_ov006_02140568 = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_02140610);
    sTrmpAnimBounce = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_021405d8);
    data_ov006_02140540 = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_02140620);
    data_ov006_021405c4 = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_02140630);
    ret = _ZN9ModelBase7SetFileEP8BMD_Fileii(c + 0x78, f, 1, -1);
    MARIO2(c)->mAnim = 0;
    if (sMgMainCamera != 0)
        Camera_ProjectToScreen16(sMgMainCamera, c + 0x24, MARIO2(c)->mScreenPos);
    MARIO2(c)->mGravityStep = 0;
    func_02016a14(c + 0x78, 0x73ff, 0);
    func_02016a04(c + 0x78, 0x3e52);
    Trmp2Mario_EnterHidden(c);
    return ret;
}
}
}
// ---- Trmp2Mario_Destruct
namespace ns_020ca604 {
extern "C" SharedFilePtr data_ov006_021405f8, data_ov006_02140608, data_ov006_021405d0,
    data_ov006_02140628, data_ov006_02140618, data_ov006_02140638, data_ov006_021405f0,
    data_ov006_021405e8, data_ov006_02140600, data_ov006_021405e0, data_ov006_02140610,
    data_ov006_021405d8, data_ov006_02140620, data_ov006_02140630;
extern "C" int data_ov006_02140590, data_ov006_02140560, data_ov006_02140580, data_ov006_021405c0,
    data_ov006_0214054c, data_ov006_02140564, data_ov006_021405a0, data_ov006_0214057c,
    data_ov006_0214056c, data_ov006_02140568, sTrmpAnimBounce, data_ov006_02140540,
    data_ov006_021405c4;
extern "C" int data_ov006_0213b2e0;
extern "C" int data_ov006_0213b3e0;
extern "C" int data_ov006_0213b3c4;

// @symbol Trmp2Mario_Destruct
extern "C" void* Trmp2Mario_Destruct(int* c)
{
    *c = (int)&data_ov006_0213b2e0;
    data_ov006_021405f8.Release();
    data_ov006_02140608.Release();
    data_ov006_021405d0.Release();
    data_ov006_02140628.Release();
    data_ov006_02140618.Release();
    data_ov006_02140638.Release();
    data_ov006_021405f0.Release();
    data_ov006_021405e8.Release();
    data_ov006_02140600.Release();
    data_ov006_021405e0.Release();
    data_ov006_02140610.Release();
    data_ov006_021405d8.Release();
    data_ov006_02140620.Release();
    data_ov006_02140630.Release();
    data_ov006_02140590 = 0;
    data_ov006_02140560 = 0;
    data_ov006_02140580 = 0;
    data_ov006_021405c0 = 0;
    data_ov006_0214054c = 0;
    data_ov006_02140564 = 0;
    data_ov006_021405a0 = 0;
    data_ov006_0214057c = 0;
    data_ov006_0214056c = 0;
    data_ov006_02140568 = 0;
    sTrmpAnimBounce = 0;
    data_ov006_02140540 = 0;
    data_ov006_021405c4 = 0;
    ((ModelAnim*)((char*)c+0x78))->~ModelAnim();
    *c = (int)&data_ov006_0213b3e0;
    *c = (int)&data_ov006_0213b3c4;
    return c;
}
}
// ---- _ZN6Player29TryExitCharacterDoorWithIntroEv
namespace ns__ZN6Player29TryExitCharacterDoorWithIntroEv {
/* NOT a Player method, despite the name. ov006, 0x020ca78c.
 *
 * The shape is a constructor, not a state handler: it calls a base routine,
 * stores a vptr into [this+0], then runs a member constructor at this+0x78.
 * Player's own constructors are _ZN6PlayerC1Ev / C3Ev in ov002, and Player's
 * ModelAnims live at 0xf0 and 0x174 -- not 0x78, which on a real Player is
 * dActor_c's mCamSpacePosY.
 *
 * This file was the only evidence for Player.h's `mModelAnim2` at 0x078, so
 * that field can now be dropped and the offset returned to dActor_c.
 *
 * The vptr it stores is the invented symbol data_ov006_0213b2e0, which carries no address --
 * a separate problem, left alone here.
 *
 * Detached from Player.h; see SlotB2_Hide.cpp.
 */
extern "C" int data_ov006_0213b2e0[];

// @symbol _ZN6Player29TryExitCharacterDoorWithIntroEv
extern "C" int *_ZN6Player29TryExitCharacterDoorWithIntroEv(int *self)
{
    TrmpRingObjAdapter_Construct(self);
    self[0] = (int)data_ov006_0213b2e0;
    _ZN9ModelAnimC1Ev((char *)self + 0x78);
    return self;
}
}
// ---- Trmp2Mario_Hide
namespace ns_020ca7b8 {
extern "C" {
// Scans sTrmp2MarioCount entries (stride 0xdc) from sTrmp2Marios:
// returns 0 if any entry's pair at +0x70 mismatches pmf_Trmp2Mario_StateHidden_2
// (y-mismatch tolerated when x is 0), else 1. Leaf, no callees.
typedef struct Ent {
    char _pad0[0x70];  // 0x00
    int x;             // 0x70
    int y;             // 0x74
    char _pad78[0x64]; // 0x78 (stride 0xdc)
} Ent;

extern "C" int sTrmp2MarioCount;
extern "C" Ent *sTrmp2Marios;
extern "C" int pmf_Trmp2Mario_StateHidden_2[2];

// @symbol Trmp2Mario_Hide
int Trmp2Mario_Hide(void) {
    int i;
    for (i = 0; i < sTrmp2MarioCount; i++) {
        int *v = (int *)(&sTrmp2Marios[i].x);
        volatile int *q = (volatile int *)pmf_Trmp2Mario_StateHidden_2;
        if (v[0] != pmf_Trmp2Mario_StateHidden_2[0] || (v[1] != q[1] && sTrmp2Marios[i].x != 0))
            return 0;
    }
    return 1;
}
}
}
// ---- Trmp2Mario_EnterAll
namespace ns_020ca840 {
extern "C" {
extern void Trmp2Mario_EnterByKind(char* o);
extern void Trmp2Mario_UpdateMatrix(char* o);
extern "C" int sTrmp2MarioCount;
extern "C" int sTrmp2FallSpeed;
extern "C" int sTrmp2GravityStep;
extern "C" int data_ov006_021405ac;
extern "C" char *sTrmp2Marios;

// @symbol Trmp2Mario_EnterAll
void Trmp2Mario_EnterAll(void) {
    int i, n, off;
    n = sTrmp2MarioCount;
    sTrmp2GravityStep = 0x100;
    sTrmp2FallSpeed = -0x4800;
    data_ov006_021405ac = 1;

    i = 0;
    if (n > 0) {
        off = 0;
        do {
            Trmp2Mario_EnterByKind(sTrmp2Marios + off);
            Trmp2Mario_UpdateMatrix(sTrmp2Marios + off);
            n = sTrmp2MarioCount;
            i++;
            off += 0xdc;
        } while (i < n);
    }
}
}
}
// ---- Trmp2Mario_MoveToStart
namespace ns_020ca8e0 {
extern "C" int sTrmp2MarioTarget;
extern "C" int sTrmp2MarioCount;
extern "C" char *sTrmp2Marios;
extern "C" int pmf_Trmp2Mario_StateHidden[2];
extern "C" int data_ov006_021405a4;
extern "C" void _Z14ApproachLinearRiii(int& ref, int to, int step);
extern "C" void Trmp2Mario_EnterAppearWait(char *o, short v);
extern "C" void Trmp2Mario_UpdateMatrix(char* o);

// @symbol Trmp2Mario_MoveToStart
extern "C" void Trmp2Mario_MoveToStart(void) {
  char* base;
  char* e;
  int i;
  int q0;
  int count;

  _Z14ApproachLinearRiii(sTrmp2MarioCount, sTrmp2MarioTarget, 1);
  i = 0;
  count = sTrmp2MarioCount;
  if (count <= 0)
    return;

  base = sTrmp2Marios;
  e = base;
  q0 = pmf_Trmp2Mario_StateHidden[0];
  for (;;) {

    int* v = (int*)(e + 0x70);
    volatile int *q = (volatile int *)pmf_Trmp2Mario_StateHidden;
    if (v[0] == q0 && (v[1] == q[1] || *(int*)(e + 0x70) == 0)) {

        Trmp2Mario_EnterAppearWait(base + i * 0xdc, (short)(i * 0x14));
        *(int *)(sTrmp2Marios + i * 0xdc + 0x24) = 0;
        *(int *)(sTrmp2Marios + i * 0xdc + 0x3c) =
            (int)(((long long)data_ov006_021405a4 * ((i << 11) - 0x1000) + 0x800) >> 12);
        Trmp2Mario_UpdateMatrix(sTrmp2Marios + i * 0xdc);
        return;
    }

    i++;
    e += 0xdc;
    if (i < count) continue;
    break;
  }

}
}
// ---- Trmp2Mario_PlaceAtStart
namespace ns_020caa08 {
extern "C" {
extern "C" int sTrmp2MarioCount;
extern "C" char *sTrmp2Marios;
extern "C" int data_ov006_021405a4;
extern void Trmp2Mario_EnterAppearWait(char *o, short v);
extern void Trmp2Mario_UpdateMatrix(char *o);

// @symbol Trmp2Mario_PlaceAtStart
void Trmp2Mario_PlaceAtStart(void)
{
    int n;
    int i;
    n = sTrmp2MarioCount;
    if (n > 3) n = 3;
    for (i = 0; i < n; i++) {
        Trmp2Mario_EnterAppearWait(sTrmp2Marios + i * 0xdc, (short)(i * 0x14));
        *(int *)(sTrmp2Marios + i * 0xdc + 0x24) = i * 0x10000 - 0x20000;
        *(int *)(sTrmp2Marios + i * 0xdc + 0x3c) =
            (int)(((long long)data_ov006_021405a4 * (i * 0x800 - 0x1000) + 0x800) >> 0xc);
        Trmp2Mario_UpdateMatrix(sTrmp2Marios + i * 0xdc);
    }
}
}
}
// ---- Trmp2Mario_DrawAll
namespace ns_020caadc {
extern "C" {
typedef struct { int x, y, z; } Vec3;
extern void func_0203cd80(Vec3* m, short angle);
extern void func_0203ccd4(Vec3* m, short angle);
extern void Trmp2Mario_Render(char* o);
extern void Puff_DrawAll(void);
extern "C" int sTrmp2MarioCount;
extern "C" char *sTrmp2Marios;

// @symbol Trmp2Mario_DrawAll
void Trmp2Mario_DrawAll(void) {
  Vec3 v; Vec3 w;
  int i, n, off;
  v.x=0; v.y=0; v.z=0xfffff008;
  func_0203cd80(&v, -0x2000); func_0203ccd4(&v, -0x3000);
  *(volatile unsigned*)0x40004c8 = (((short)v.x >> 3) & 0x3ff) | ((((short)v.y >> 3) & 0x3ff) << 10) | ((((short)v.z >> 3) & 0x3ff) << 20);
  w.x=0; w.y=0; w.z=0xfffff008;
  func_0203cd80(&w, -0x2000);
  *(volatile unsigned*)0x40004c8 = ((((short)w.x >> 3) & 0x3ff) | ((((short)w.y >> 3) & 0x3ff) << 10) | ((((short)w.z >> 3) & 0x3ff) << 20)) | 0x40000000;
  *(volatile unsigned*)0x40004cc = 0x7fff;
  *(volatile unsigned*)0x40004cc = 0x40007fff;

  n = sTrmp2MarioCount;
  i = 0;
  if (n > 0) {
    off = 0;
    do {
        Trmp2Mario_Render(sTrmp2Marios + off);
        n = sTrmp2MarioCount;
        i++;
        off += 0xdc;
    } while (i < n);
  }
  Puff_DrawAll();
}
}
}
// ---- Trmp2Mario_UpdateAll
namespace ns_020cac30 {
/* ov006, 0x020cac30, size 0x6c. Held the name
 * _ZN6Player12St_Null_InitEv until that symbol was moved to ov002, where an
 * eight-byte `return 1` sits at the same shared address and is reached from
 * ov002's Player::State pointer-to-member table. This function is reached
 * instead by two direct arm_calls from ov006 (module:overlay(6)) and touches
 * no Player field, so nothing here was ever Player's. Back to a placeholder
 * name until its own class is identified.
 */
extern "C" {
extern int sTrmp2MarioCount;
extern char *sTrmp2Marios;
void Trmp2Mario_Update(void*);
void TrmpItem_UpdateWithJumper(void*,int);
void Puff_UpdateAll(void);
// @symbol Trmp2Mario_UpdateAll
void Trmp2Mario_UpdateAll(void){
  int i=0;
  if (sTrmp2MarioCount > 0) {
      int off = 0;
      do {
          Trmp2Mario_Update(sTrmp2Marios + off);
          TrmpItem_UpdateWithJumper(sTrmp2Marios + off, i);
          i++;
          off += 0xdc;
      } while (i < sTrmp2MarioCount);
  }
  Puff_UpdateAll();
}
}
}
// ---- Trmp2Mario_ResetAll
namespace ns_020cac9c {
extern "C" {
void Trmp2Mario_SetTuning(int sz);
void Trmp2Mario_EnterHidden(char *c);
void Trmp2Mario_UpdateMatrix(char* o);
void Puff_ClearAll(int a0, int a1);
extern "C" int sTrmp2MarioTarget;
extern "C" int data_ov006_0213b0f0;
extern "C" int data_ov006_02140598;
extern "C" int data_ov006_021405ac;
extern "C" char *sTrmp2Marios;

// @symbol Trmp2Mario_ResetAll
void Trmp2Mario_ResetAll(void){
    int i;
    int off;
    Trmp2Mario_SetTuning(0x1000);
    data_ov006_0213b0f0 = 3;
    data_ov006_02140598 = 0;
    data_ov006_021405ac = 0;
    if (sTrmp2MarioTarget > 0) {
        i = 0;
        off = 0;
        do {
            Trmp2Mario_EnterHidden(sTrmp2Marios + off);
            Trmp2Mario_UpdateMatrix(sTrmp2Marios + off);
            i++;
            off += 0xdc;
        } while (i < sTrmp2MarioTarget);
    }
    Puff_ClearAll(0, 0);
}
}
}
// ---- Trmp2Mario_SetTuning
namespace ns_020cad3c {
extern "C" {
extern int func_020531a4(int a);
extern "C" int sTrmp2FallSpeed;
extern "C" int sTrmp2GravityStep;
extern "C" int data_ov006_0214053c;
extern "C" int data_ov006_02140574;
extern "C" int sTrmp2RiseSpeedMax;
extern "C" int data_ov006_021405a4;

// @symbol Trmp2Mario_SetTuning
void Trmp2Mario_SetTuning(int a)
{
    int v;
    if (a > 0x2800) a = 0x2800;
    v = func_020531a4(a);
    sTrmp2FallSpeed = (int)(((long long)v * -0x1c00 + 0x800) >> 12);
    sTrmp2GravityStep = (int)(((long long)a * 0xc0 + 0x800) >> 12);
    data_ov006_0214053c = (int)(((long long)v * 0xe00 + 0x800) >> 12);
    data_ov006_02140574 = (int)(((long long)v * 0x5800 + 0x800) >> 12);
    sTrmp2RiseSpeedMax = (int)(((long long)v * 0x6000 + 0x800) >> 12);
    data_ov006_021405a4 = (int)(((long long)v * 0x180 + 0x800) >> 12);
}
}
}
// ---- Trmp2Mario_InitPool
namespace ns_020cae9c {
extern "C" {
extern int Trmp2Mario_Load(int p);
extern "C" int sTrmp2MarioCount;
extern "C" int sTrmp2MarioTarget;
extern "C" int sTrmp2Marios;
extern "C" int sTrmpJumpers[];
extern "C" int data_ov006_02140968[];

// @symbol Trmp2Mario_InitPool
int Trmp2Mario_InitPool(int base, int n)
{
    int i;
    int off;

    sTrmp2MarioCount = n;
    sTrmp2MarioTarget = n;
    sTrmp2Marios = base;

    i = 0;
    if (i < n) {
        off = i;
        do {
            int p;
            if (Trmp2Mario_Load(sTrmp2Marios + off) == 0)
                return 0;
            p = sTrmp2Marios + off;
            if (i < 5)
                sTrmpJumpers[i] = p;
            if (i < 5) data_ov006_02140968[i] = p;
            off = off + 0xdc;
            n = sTrmp2MarioCount;
            i++;
        } while (i < n);
    }
    return 1;
}
}
}
// ---- Trmp3DMario_GetVelocity
namespace ns_020caf44 {
extern "C" {
// @symbol Trmp3DMario_GetVelocity
int Trmp3DMario_GetVelocity(int p)
{
    return p + 52;
}
}
}
// ---- Trmp3DMario_IsMissed
namespace ns_020caf4c {
extern "C" {
extern "C" int pmf_Trmp3DMario_StateMissed[];
// @symbol Trmp3DMario_IsMissed
int Trmp3DMario_IsMissed(int *r0) {
    int* p = (int*)(((int)r0 + 0x64));
    int *g = pmf_Trmp3DMario_StateMissed;
    int lr = 1;
    if (p[0] == g[0]) {
        if (p[1] == g[1] || r0[0x19] == 0) lr = 0;
    }
    return lr;
}
}
}
// ---- Trmp3DMario_GetPrevPos
namespace ns_020cafa4 {
extern "C" {
// @symbol Trmp3DMario_GetPrevPos
int Trmp3DMario_GetPrevPos(int p)
{
    return p + 40;
}
}
}
// ---- Trmp3DMario_GetPos
namespace ns_020cafac {
extern "C" {
// @symbol Trmp3DMario_GetPos
int Trmp3DMario_GetPos(int p)
{
    return p + 28;
}
}
}
// ---- Trmp3DMario_Render
namespace ns_020cafb4 {
extern "C" {
extern int data_ov006_0212e038[];
struct C { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void f(void*); };
// @symbol Trmp3DMario_Render
void Trmp3DMario_Render(char *o) {
  struct C *p = (struct C*)(o+0x6c);
  p->f((void*)data_ov006_0212e038);
}
}
}
// ---- Trmp3DMario_UpdateMatrix
namespace ns_020cafdc {
/* recovered: shared common types */
extern "C" {

extern struct Matrix4x3 data_020a0e68;
void Matrix4x3_FromTranslation(struct Matrix4x3 *mF, int x, int y, int z);
void Matrix4x3_ApplyInPlaceToRotationY(struct Matrix4x3 *mF, short angY);
// @symbol Trmp3DMario_UpdateMatrix
void Trmp3DMario_UpdateMatrix(char *o) {
    Matrix4x3_FromTranslation(&data_020a0e68, MARIO3D(o)->mPos.x, MARIO3D(o)->mPos.y,
                              MARIO3D(o)->mPos.z);
    Matrix4x3_ApplyInPlaceToRotationY(&data_020a0e68, MARIO3D(o)->mRotY);
    *(struct Matrix4x3 *)(o + 0x88) = data_020a0e68;
}
}
}
// ---- Trmp3DMario_Update
namespace ns_020cb030 {
typedef int Fix12;
struct Vector3_16f;
struct Callback;
struct System {
    static System* New(unsigned, unsigned, Fix12, Fix12, Fix12, const Vector3_16f*, Callback*);
};
/* Signature deliberately copied from the local declaration above: the
   ROM name carries by-value class parameters (e.g. Fix12<int>), which
   mwccarm passes differently at the call site, so declaring the true
   types breaks the byte match. See notes/mwccarm-codegen.md 6az. */
extern "C" System* _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(unsigned, unsigned, Fix12, Fix12, Fix12, const Vector3_16f*, Callback*);

extern "C" {
/* The ROM's relocation at 0x020cb088 targets 0x020cb134, not 0x020c9024.
   The byte gate could not object: a bl is a relocation, which match.py
   compares as a wildcard, so either callee passes. */
extern void Trmp3DMario_ApplyGravity(char *o);
extern void Trmp3DMario_UpdateMatrix(char *o);
extern int sTrmpAnimBounce;
}
System* System::New(unsigned, unsigned, Fix12, Fix12, Fix12, const Vector3_16f*, Callback*);

typedef void (*PMF)(void*);
struct Closure { int off; int adj; };

// @symbol Trmp3DMario_Update
extern "C" void Trmp3DMario_Update(char *o) {
    MARIO3D(o)->mPrevPos.x = MARIO3D(o)->mPos.x;
    MARIO3D(o)->mPrevPos.y = MARIO3D(o)->mPos.y;
    MARIO3D(o)->mPrevPos.z = MARIO3D(o)->mPos.z;
    if (MARIO3D(o)->mState[0] != 0) {
        Closure* cl = (Closure*)(o + 0x64);
        void* tobj = o + (cl->adj >> 1);
        void (*fn)();
        if (cl->adj & 1)
            fn = *(void(**)())(*(char**)tobj + cl->off);
        else
            fn = (void(*)())cl->off;
        ((void(*)(void*))fn)(tobj);
    }
    Trmp3DMario_ApplyGravity(o);
    Fix12 v = (Fix12)(((long long)MARIO3D(o)->mBounceVy * 0xb4b + 0x800) >> 12);
    if (MARIO3D(o)->mVel.y > v) {
        if (*(int *)(o + 0xcc) == sTrmpAnimBounce) {
            MARIO3D(o)->mParticleId =
                (int)_ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
                    MARIO3D(o)->mParticleId, 0xf5, MARIO3D(o)->mPos.x << 3, MARIO3D(o)->mPos.y << 3,
                    MARIO3D(o)->mPos.z << 3, 0, 0);
        }
    }
    Trmp3DMario_UpdateMatrix(o);
    ((dExtFrameCtrl_c*)(o + 0xbc))->Advance();
}
}
// ---- Trmp3DMario_ApplyGravity
namespace ns_020cb134 {
extern "C" {
extern int sTrmp3DFallSpeed[];
int _Z14ApproachLinearRiii(int *a, int b, int c);
void AddVec3(void *dst, void *a, void *b);
// @symbol Trmp3DMario_ApplyGravity
void Trmp3DMario_ApplyGravity(char *o) {
    _Z14ApproachLinearRiii((int *)(o + 0x38), sTrmp3DFallSpeed[0], MARIO3D(o)->mGravityStep);
    AddVec3(o + 0x1c, o + 0x34, o + 0x1c);
}
}
}
// ---- Trmp3DMario_StateKnockedOut
namespace ns_020cb16c {
extern "C" {
extern int Trmp3DMario_EnterOffstage(void *c);
// @symbol Trmp3DMario_StateKnockedOut
void Trmp3DMario_StateKnockedOut(int *c) {
    if (*(int *)((char *)c + 0x20) >= -0x120000)
        return;
    *(int *)((char *)c + 0x38) = 0;
    Trmp3DMario_EnterOffstage(c);
}
}
}
// ---- Trmp3DMario_EnterByKind
namespace ns_020cb1a8 {
typedef int Fix12;
struct BCA_File;
struct ModelAnim {
  void SetAnim(BCA_File *f, int a, Fix12 b, unsigned int c);
};
/* Signature deliberately copied from the local declaration above: the
   ROM name carries by-value class parameters (e.g. Fix12<int>), which
   mwccarm passes differently at the call site, so declaring the true
   types breaks the byte match. See notes/mwccarm-codegen.md 6az. */
extern "C" void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *, BCA_File *f, int a, Fix12 b, unsigned int c);


extern "C" {
extern int pmf_Trmp3DMario_StateOffstage_4[2];
extern int pmf_Trmp3DMario_StateGoal_2[2];
extern int data_ov006_02140540[];
extern int pmf_Trmp3DMario_StateKnockedOut[2];
}

// @symbol Trmp3DMario_EnterByKind
extern "C" void Trmp3DMario_EnterByKind(char *c)
{
    int *p;
    int *d;

    p = MARIO3D(c)->mState;
    d = pmf_Trmp3DMario_StateOffstage_4;
    if (p[0] == d[0]) {
        if (p[1] != d[1]) {
            if (MARIO3D(c)->mState[0] != 0)
                goto check2;
        }
        return;
    }
check2:
    p = MARIO3D(c)->mState;
    d = pmf_Trmp3DMario_StateGoal_2;
    if (p[0] == d[0]) {
        if (p[1] != d[1]) {
            if (MARIO3D(c)->mState[0] != 0)
                goto body;
        }
        return;
    }
body:
    MARIO3D(c)->mGravityStep = 0x100;
    MARIO3D(c)->mVel.x = 0;
    MARIO3D(c)->mVel.y = 0x2000;
    Sound::PlayBank2_2D(0x1c9);
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj((ModelAnim *)(c + 0x6c), (BCA_File *)data_ov006_02140540[0], 0, 0x800, 0);
    *(int *)(c + 0xc4) = 0;
    {
        int a = pmf_Trmp3DMario_StateKnockedOut[0];
        int b = pmf_Trmp3DMario_StateKnockedOut[1];
        MARIO3D(c)->mState[0] = b ? a : a;
        MARIO3D(c)->mState[1] = b;
    }
}
}
// ---- Trmp3DMario_StateGoal
namespace ns_020cb2b4 {
extern "C" {
typedef struct { int m0, m4, m8; } Triple;

extern "C" int data_ov006_021405c8[];
extern "C" int data_ov006_0214054c;
extern "C" void *data_ov006_02140564;
extern "C" int sTrmpComboCount;
extern "C" int data_ov006_0214058c;
extern "C" int data_ov006_0214055c;
extern "C" char *sMgSubCamera;
extern "C" char *sMgMainCamera;
extern "C" int data_ov006_02140584;
extern "C" Triple data_ov006_02140778[];
extern "C" Triple data_020a0ebc;

extern void _Z11UpdateAngleRssis(short *, short, int, short);
/* local extern: the call passes an untyped this, so it cannot use the header method. */
extern int _ZN15dExtFrameCtrl_c8FinishedEv(void *);
extern void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *, void *, int, int, unsigned int);
extern void _Z14ApproachLinearRiii(int *, int, int);
extern void _Z15ApproachLinear2Rsss(short *, short, short);
extern void func_02012718(int, int);
extern void Camera_ProjectToScreen(char *, void *, int *, int *);
extern int Mg_GetTopScreenYOffset(void);
extern void TrmpFx_Spawn(int, int);
extern void Trmp3DMario_EnterOffstage(char *);

// @symbol Trmp3DMario_StateGoal
void Trmp3DMario_StateGoal(void *self) {
    char *c = (char *)self;
    int va, vb;
    short idx;
    int lim;
    int u;
    int i;

    idx = *(short *)(c + 0x52);
    lim = data_ov006_021405c8[idx];
    if (*(int *)(c + 0x20) <= lim) {
        *(int *)(c + 0x20) = lim;
        *(int *)(c + 0x38) = 0;
    }

    if (*(int *)(c + 0xcc) == data_ov006_0214054c) {
        _Z11UpdateAngleRssis((short *)(c + 0x4a), 0, 2, 0x1000);
        if (_ZN15dExtFrameCtrl_c8FinishedEv(c + 0xbc) == 0)
            return;
        _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x6c, data_ov006_02140564, 0, 0x800, 0);
        return;
    }

    if (*(int *)(c + 0x1c) > 0) {
        _Z14ApproachLinearRiii((int *)(c + 0x34), 0x4000, 0x800);
        _Z15ApproachLinear2Rsss((short *)(c + 0x4a), 0x4000, 0x1000);
    } else {
        _Z14ApproachLinearRiii((int *)(c + 0x34), -0x4000, 0x800);
        _Z15ApproachLinear2Rsss((short *)(c + 0x4a), -0x4000, 0x1000);
    }

    u = *(int *)(c + 0x1c);
    if (u <= 0x90000 && u >= -0x90000)
        return;

    func_02012718(0x1be, 0x100000);
    _Z14ApproachLinearRiii(&sTrmpComboCount, 0x270f, 1);
    data_ov006_0214058c -= 1;
    data_ov006_0214055c -= 1;

    if (*(int *)(c + 0x20) > 0) {
        Camera_ProjectToScreen(sMgSubCamera, c + 0x1c, &va, &vb);
        vb = vb - (Mg_GetTopScreenYOffset() + 0xc0);
    } else {
        Camera_ProjectToScreen(sMgMainCamera, c + 0x1c, &va, &vb);
    }
    vb -= 0x20;
    TrmpFx_Spawn(vb << 12, (short)sTrmpComboCount);

    data_ov006_02140584 += 1;
    if (data_ov006_02140584 >= 6)
        data_ov006_02140584 = 0;

    i = data_ov006_02140584;
    {
        Triple *p = &data_ov006_02140778[i];
        *(int *)(c + 0x1c) = p->m0;
        *(int *)(c + 0x20) = p->m4;
        *(int *)(c + 0x24) = p->m8;
    }
    *(int *)(c + 0x34) = data_020a0ebc.m0;
    *(int *)(c + 0x38) = data_020a0ebc.m4;
    *(int *)(c + 0x3c) = data_020a0ebc.m8;

    Trmp3DMario_EnterOffstage(c);
}
}
}
// ---- Trmp3DMario_EnterGoal
namespace ns_020cb528 {
typedef short s16;
typedef int Fix12;
struct ModelAnim { void SetAnim(void* bca, int b, Fix12 c, unsigned int d); };
/* Signature deliberately copied from the local declaration above: the
   ROM name carries by-value class parameters (e.g. Fix12<int>), which
   mwccarm passes differently at the call site, so declaring the true
   types breaks the byte match. See notes/mwccarm-codegen.md 6az. */
extern "C" void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *, void* bca, int b, Fix12 c, unsigned int d);

extern "C" {
void Sound_PlayBank1Panned(int a0, char* a1, void* a2);
void Trmp3DMario_StateGoal(char *c);
extern int data_ov006_021405c8[];
extern void *data_ov006_0214054c;
extern int pmf_Trmp3DMario_StateGoal[];
extern int data_ov006_0214055c[];
}
// @symbol Trmp3DMario_EnterGoal
extern "C" void Trmp3DMario_EnterGoal(char *c) {
    int a, b;
    MARIO3D(c)->mPos.y = data_ov006_021405c8[MARIO3D(c)->mHeightRow];
    MARIO3D(c)->mVel.x = 0;
    MARIO3D(c)->mVel.y = 0;
    Sound_PlayBank1Panned(0, (char*)0x10, *(void**)(c+0x1c));
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj((ModelAnim*)(c+0x6c), data_ov006_0214054c, 0x40000000, 0x800, 0);
    data_ov006_0214055c[0] = data_ov006_0214055c[0] + 1;
    a = pmf_Trmp3DMario_StateGoal[0];
    b = pmf_Trmp3DMario_StateGoal[1];
    MARIO3D(c)->mState[0] = b ? a : a;
    MARIO3D(c)->mState[1] = b;
    Trmp3DMario_StateGoal(c);
}
}
// ---- Trmp3DMario_StateLand
namespace ns_020cb5c4 {
extern "C" {
extern "C" int data_ov006_021405c8[];
extern "C" int data_ov006_021405c0;
extern "C" short data_ov006_02140538;
extern void _Z14ApproachLinearRiii(int* p, int b, int c);
extern int _Z14ApproachLinearRsss(short *value, short target, short step);
/* local extern: the call passes an untyped this, so it cannot use the header method. */
extern int _ZN15dExtFrameCtrl_c8FinishedEv(void* a);
extern void Trmp3DMario_EnterGoal(char *c);
extern void Trmp3DMario_EnterOnLedge(char *c);

// @symbol Trmp3DMario_StateLand
void Trmp3DMario_StateLand(char *c) {
    _Z14ApproachLinearRiii((int *)(c + 0x20), data_ov006_021405c8[MARIO3D(c)->mHeightRow], 0x4000);
    if (MARIO3D(c)->mPos.x > 0)
        _Z14ApproachLinearRsss((short*)(c + 0x4a), 0x4000, 0x1000);
    else
        _Z14ApproachLinearRsss((short*)(c + 0x4a), -0x4000, 0x1000);
    MARIO3D(c)->mVel.x = 0;
    MARIO3D(c)->mVel.y = 0;
    if (*(int*)(c + 0xcc) != data_ov006_021405c0) return;
    if (_ZN15dExtFrameCtrl_c8FinishedEv(c + 0xbc) == 0) return;
    if (MARIO3D(c)->mHeightRow == data_ov006_02140538)
        Trmp3DMario_EnterGoal(c);
    else
        Trmp3DMario_EnterOnLedge(c);
}
}
}
// ---- Trmp3DMario_EnterLand
namespace ns_020cb690 {
struct ModelAnim { void SetAnim(void* bca, int b, int c, unsigned int d); };
/* Signature deliberately copied from the local declaration above: the
   ROM name carries by-value class parameters (e.g. Fix12<int>), which
   mwccarm passes differently at the call site, so declaring the true
   types breaks the byte match. See notes/mwccarm-codegen.md 6az. */
extern "C" void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *, void* bca, int b, int c, unsigned int d);

extern "C" {
void Sound_PlayBank1Panned(int a0, char* a1, void* a2);
void Trmp3DMario_StateLand(char *c);
extern int data_020a0ebc[];
extern int *data_ov006_021405c0;
struct W2 { int a, b; };
extern struct W2 pmf_Trmp3DMario_StateLand;
void Trmp3DMario_EnterLand(char *c);
}
// @symbol Trmp3DMario_EnterLand
void Trmp3DMario_EnterLand(char *c) {
    MARIO3D(c)->mVel.x = data_020a0ebc[0];
    MARIO3D(c)->mVel.y = data_020a0ebc[1];
    MARIO3D(c)->mVel.z = data_020a0ebc[2];
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj((ModelAnim*)(c+0x6c), (void*)data_ov006_021405c0, 0x40000000, 0x800, 0);
    Sound_PlayBank1Panned(0, (char*)0x17, *(void**)(c+0x1c));
    {
        int a = pmf_Trmp3DMario_StateLand.a;
        int b = pmf_Trmp3DMario_StateLand.b;
        MARIO3D(c)->mState[0] = b ? a : a;
        MARIO3D(c)->mState[1] = b;
    }
    int* p20 = (int*)(((int)c + 0x20));
    *p20 = *p20 + 0x20000;
    Trmp3DMario_StateLand(c);
}
}
// ---- Trmp3DMario_StateFallToLedge
namespace ns_020cb72c {
extern "C" {

extern void Trmp3DMario_EnterGoal(char *c);
extern void Trmp3DMario_EnterOnLedge(char *c);
extern int D3D_PlaySeAtX(int a, int b);
extern void Trmp3DMario_EnterOnGround(char *c);
extern "C" int data_ov006_021405c8[];
extern "C" short data_ov006_02140538;
// @symbol Trmp3DMario_StateFallToLedge
void Trmp3DMario_StateFallToLedge(char *c) {
    int v = MARIO3D(c)->mPos.x;
    if (v > 0) {
        short idx = MARIO3D(c)->mHeightRow;
        int cur = MARIO3D(c)->mPos.y;
        int *d = data_ov006_021405c8;
        if (cur <= d[idx]) {
            if (idx == data_ov006_02140538) {
                Trmp3DMario_EnterGoal(c);
            } else {
                Trmp3DMario_EnterOnLedge(c);
            }
            D3D_PlaySeAtX(0x1b4, MARIO3D(c)->mPos.x);
        } else {
            int lim = d[1] + 0x30000;
            if ((cur >= lim) && (idx == 1)) {
                MARIO3D(c)->mPos.y = lim;
            }
        }
    } else {
        if ((MARIO3D(c)->mPos.y) <= data_ov006_021405c8[0]) {
            D3D_PlaySeAtX(0x1b4, v);
            Trmp3DMario_EnterOnGround(c);
            return;
        }
    }
    {
        int w = MARIO3D(c)->mPos.x;
        if (w > 0x70000) {
            MARIO3D(c)->mPos.x = 0x70000;
            MARIO3D(c)->mVel.x = 0;
            return;
        }
        if (w < (-0x70000)) {
            MARIO3D(c)->mPos.x = -0x70000;
            MARIO3D(c)->mVel.x = 0;
        }
    }
}
}
}
// ---- Trmp3DMario_EnterFallToLedge
namespace ns_020cb814 {
extern "C" {
typedef struct { int a, b; } Pair2;
extern "C" Pair2 pmf_Trmp3DMario_StateFallToLedge;
extern void Trmp3DMario_StateFallToLedge(char *c);

// @symbol Trmp3DMario_EnterFallToLedge
void Trmp3DMario_EnterFallToLedge(char *c) {
    *(W2 *)(c + 0x64) = *(W2 *)&pmf_Trmp3DMario_StateFallToLedge;
    Trmp3DMario_StateFallToLedge(c);
}
}
}
// ---- Trmp3DMario_StateHardBounce
namespace ns_020cb838 {

extern "C" {
void Trmp3DMario_EnterFall(void *c);
void Camera_ProjectToScreen16(void *a0, void *a1, short *a2);
void Trmp3DMario_EnterFallToLedge(void *c);
void Trmp3DMario_EnterLand(void *c);
void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *thisPtr, void *file, int i, int fix, unsigned int flags);
void Sound_PlayBank1Panned(int a0, int a1, int a2);
void func_02012718(int a, int b);
int D3D_PlaySeAtX(int a, int b);
}

extern "C" void *sMgMainCamera;
extern "C" int data_ov006_021405c8[2];
extern "C" void *data_ov006_0213b22c[];
extern "C" int sTrmpAnimBounce;

struct VtObj {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void m4();
};

// @symbol Trmp3DMario_StateHardBounce
extern "C" void Trmp3DMario_StateHardBounce(char *c) {
    int v;

    if (MARIO3D(c)->mVel.y <= 0) {
        Trmp3DMario_EnterFall(c);
        return;
    }

    if (*(int *)(c + 0xcc) == sTrmpAnimBounce) {
        if (((dExtFrameCtrl_c *)(c + 0xbc))->WillHitFrame(0xc) ||
            ((dExtFrameCtrl_c *)(c + 0xbc))->WillHitFrame(0x18)) {
            D3D_PlaySeAtX(0x1b5, MARIO3D(c)->mPos.x);
        }
    }

    Camera_ProjectToScreen16(sMgMainCamera, (void *)(c + 0x1c), MARIO3D(c)->mScreenPos);

    v = MARIO3D(c)->mPos.x;

    if (v >= -0x5c000) goto L5c;
    if (MARIO3D(c)->mVel.x < 0)
        goto L70;

L5c:
    if (v <= 0x5c000) goto L1ac;
    if (MARIO3D(c)->mVel.x <= 0)
        goto L1ac;

L70:
    {
        int f0 = data_ov006_021405c8[0];
        int p = MARIO3D(c)->mPos.y;

        if (p > f0) {
            MARIO3D(c)->mHeightRow = 0;
            Trmp3DMario_EnterFallToLedge(c);
            return;
        }

        f0 -= 0x20000;
        if (p <= f0) goto Ld0;
        if (v <= 0) goto L134;
        MARIO3D(c)->mHeightRow = 0;
        Trmp3DMario_EnterLand(c);
        return;

    Ld0:
        if (v <= 0) goto L134;
        {
            int f1 = data_ov006_021405c8[1];
            int hi1 = f1 + 0x30000;

            if (p >= hi1) goto L134;
            if (p <= f1) goto L10c;
            MARIO3D(c)->mHeightRow = 1;
            Trmp3DMario_EnterFallToLedge(c);
            return;

        L10c:
            f1 -= 0x20000;
            if (p <= f1) goto L134;
            MARIO3D(c)->mHeightRow = 1;
            Trmp3DMario_EnterLand(c);
            return;
        }
    }

L134:
    if (MARIO3D(c)->mVel.y > 0) {
        MARIO3D(c)->mAnim = 2;
        _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(
            (void *)(c + 0x6c), *(void **)data_ov006_0213b22c[MARIO3D(c)->mAnim], 0x40000000, 0x800,
            0);

        *(int *)(c + 0xc4) = 0;
        Sound_PlayBank1Panned(0, MARIO3D(c)->mAnim, MARIO3D(c)->mPos.x);
    }

    func_02012718(0x1b3, MARIO3D(c)->mPos.x + 0x80000);
    *(int *)(((int)c + 0x34)) *= -1;
    goto L1dc;

L1ac:
    if (MARIO3D(c)->mContact == 3) {
        ((VtObj *)c)->m4();
        *(int *)(((int)c + 0x34)) *= -1;
    }

L1dc:
    {
    int r = MARIO3D(c)->mVel.x;
    if (r > 0x4000) {
        ApproachLinear(MARIO3D(c)->mRotY, 0x6000, 0xc00);
    } else if (r < -0x4000) {
        ApproachLinear(MARIO3D(c)->mRotY, -0x6000, 0xc00);
    } else {
        ApproachLinear(MARIO3D(c)->mRotY, (short)r, 0xc00);
    }
}
}
}
// ---- Trmp3DMario_BounceOffLineA
namespace ns_020cbaec {
/* recovered: shared common types, declarations from a shared header */
/* recovered: shared common types */
typedef short s16;




struct VtObj {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void m4();
};

extern "C" {
int DotVec3(const Vector3 *a, const Vector3 *b);
void Vec3_MulScalar(Vector3 *out, const Vector3 *in, int scale);
void SubVec3(Vector3 *a, Vector3 *b, Vector3 *c);
void AddVec3(Vector3 *a, Vector3 *b, Vector3 *c);
int _ZN4cstd4fdivEii(int a, int b);
void* _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
    unsigned int a, unsigned int b, int c, int d, int e, const void *f, void *g);
void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *thisPtr, void *file, int i, int fix, unsigned int flags);
void Sound_PlayBank1Panned(int a0, int a1, int a2);
int D3D_PlaySeAtX(int a, int b);
void Trmp3DMario_StateHardBounce(char *c);
}


// @symbol Trmp3DMario_BounceOffLineA
extern "C" void Trmp3DMario_BounceOffLineA(char *c)
{
    Vector3 tmp;
    Vector3 tmp2;
    Vector3 tmp4;
    int r5v;
    int r4v;
    int dot;
    int scale;
    int fdivr;

    r5v = MARIO3D(c)->mContactOffset;
    r4v = MARIO3D(c)->mContactHalfWidth;
    if (r5v < 0) r5v = -r5v;
    {
        int *src = (int *)(c + 4);
        tmp.x = src[0];
        tmp.y = src[1];
        tmp.z = src[2];
    }

    dot = DotVec3(&MARIO3D(c)->mVel, &tmp);
    scale = (int)(((long long)dot * 0x1400 + 0x800) >> 12);
    Vec3_MulScalar(&tmp2, &tmp, scale);
    SubVec3(&MARIO3D(c)->mVel, &tmp2, &MARIO3D(c)->mVel);

    fdivr = _ZN4cstd4fdivEii(r4v, r4v + r5v);

    MARIO3D(c)->mGravityStep = sTrmp3DGravityStep;

    {
        Vector3_16 v;
        v.x = (s16)tmp.x;
        v.y = (s16)tmp.y;
        v.z = (s16)tmp.z;

        _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
            0, 0xf3, MARIO3D(c)->mPos.x << 3, MARIO3D(c)->mPos.y << 3, MARIO3D(c)->mPos.z << 3, &v,
            0);
        _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
            0, 0xf4, MARIO3D(c)->mPos.x << 3, MARIO3D(c)->mPos.y << 3, MARIO3D(c)->mPos.z << 3, &v,
            0);
    }

    *(unsigned int *)(c + 0x54) =
        (unsigned int)_ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
            *(unsigned int *)(c + 0x54), 0xf5, MARIO3D(c)->mPos.x << 3, MARIO3D(c)->mPos.y << 3,
            MARIO3D(c)->mPos.z << 3, 0, 0);

    scale = (int)(((long long)data_ov006_02140570 * fdivr + 0x800) >> 12);
    Vec3_MulScalar(&tmp4, &tmp, scale);
    AddVec3(&MARIO3D(c)->mVel, &tmp4, &MARIO3D(c)->mVel);

    {
        int v = MARIO3D(c)->mVel.x;
        if (v < -0x1000) v = -0x1000;
        else if (v > 0x1000) v = 0x1000;
        MARIO3D(c)->mVel.x = v;
    }

    {
        int half = data_ov006_02140570 >> 1;
        int cur = MARIO3D(c)->mVel.y;
        if (cur >= half) half = cur;
        MARIO3D(c)->mVel.y = half;
    }

    MARIO3D(c)->mBounceVy = MARIO3D(c)->mVel.y;
    ((VtObj *)c)->m4();

    if (MARIO3D(c)->mAnim != 0) {
        MARIO3D(c)->mAnim = 0;
    } else {
        MARIO3D(c)->mAnim = 1;
    }

    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj((void *)(c + 0x6c), sTrmpAnimBounce, 0x40000000,
                                                0x800, 0);

    *(int *)(c + 0xc4) = 0;
    Sound_PlayBank1Panned(0, 4, MARIO3D(c)->mPos.x);

    D3D_PlaySeAtX(0x1b5, MARIO3D(c)->mPos.x);

    *(int *)(c + 0x5c) = 0;
    {
        int a = pmf_Trmp3DMario_StateHardBounce[0];
        int b = pmf_Trmp3DMario_StateHardBounce[1];
        a = b ? a : a;
        MARIO3D(c)->mState[0] = a;
        MARIO3D(c)->mState[1] = b;
    }
    Trmp3DMario_StateHardBounce(c);
}
}
// ---- Trmp3DMario_StateBounce
namespace ns_020cbd7c {

extern "C" {
void Trmp3DMario_EnterFall(void *c);
void Camera_ProjectToScreen16(void *a0, void *a1, short *a2);
void Trmp3DMario_EnterFallToLedge(void *c);
void Trmp3DMario_EnterLand(void *c);
void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *thisPtr, void *file, int i, int fix, unsigned int flags);
void Sound_PlayBank1Panned(int a0, int a1, int a2);
void func_02012718(int a, int b);
}

extern "C" void *sMgMainCamera;
extern "C" int data_ov006_021405c8[2];
extern "C" void *data_ov006_0213b22c[];

struct VtObj {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void m4();
};

// @symbol Trmp3DMario_StateBounce
extern "C" void Trmp3DMario_StateBounce(char *c) {
    int v;

    if (MARIO3D(c)->mVel.y <= 0) {
        Trmp3DMario_EnterFall(c);
        return;
    }

    Camera_ProjectToScreen16(sMgMainCamera, (void *)(c + 0x1c), MARIO3D(c)->mScreenPos);

    v = MARIO3D(c)->mPos.x;

    if (v >= -0x5c000) goto L5c;
    if (MARIO3D(c)->mVel.x < 0)
        goto L70;

L5c:
    if (v <= 0x5c000) goto L1ac;
    if (MARIO3D(c)->mVel.x <= 0)
        goto L1ac;

L70:
    {
        int f0 = data_ov006_021405c8[0];
        int p = MARIO3D(c)->mPos.y;

        if (p > f0) {
            MARIO3D(c)->mHeightRow = 0;
            Trmp3DMario_EnterFallToLedge(c);
            return;
        }

        f0 -= 0x20000;
        if (p <= f0) goto Ld0;
        if (v <= 0) goto L134;
        MARIO3D(c)->mHeightRow = 0;
        Trmp3DMario_EnterLand(c);
        return;

    Ld0:
        if (v <= 0) goto L134;
        {
            int f1 = data_ov006_021405c8[1];
            int hi1 = f1 + 0x30000;

            if (p >= hi1) goto L134;
            if (p <= f1) goto L10c;
            MARIO3D(c)->mHeightRow = 1;
            Trmp3DMario_EnterFallToLedge(c);
            return;

        L10c:
            f1 -= 0x20000;
            if (p <= f1) goto L134;
            MARIO3D(c)->mHeightRow = 1;
            Trmp3DMario_EnterLand(c);
            return;
        }
    }

L134:
    if (MARIO3D(c)->mVel.y > 0) {
        MARIO3D(c)->mAnim = 2;
        _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(
            (void *)(c + 0x6c), *(void **)data_ov006_0213b22c[MARIO3D(c)->mAnim], 0x40000000, 0x800,
            0);

        *(int *)(c + 0xc4) = 0;
        Sound_PlayBank1Panned(0, MARIO3D(c)->mAnim, MARIO3D(c)->mPos.x);
    }

    func_02012718(0x1b3, MARIO3D(c)->mPos.x + 0x80000);
    *(int *)(((int)c + 0x34)) *= -1;
    goto L1dc;

L1ac:
    if (MARIO3D(c)->mContact == 3) {
        ((VtObj *)c)->m4();
        *(int *)(((int)c + 0x34)) *= -1;
    }

L1dc:
    {
    int r = MARIO3D(c)->mVel.x;
    if (r > 0x4000) {
        ApproachLinear(MARIO3D(c)->mRotY, 0x4000, 0xc00);
    } else if (r < -0x4000) {
        ApproachLinear(MARIO3D(c)->mRotY, -0x4000, 0xc00);
    } else {
        ApproachLinear(MARIO3D(c)->mRotY, (short)r, 0xc00);
    }
}
}
}
// ---- Trmp3DMario_BounceOffLineB
namespace ns_020cbfd8 {
/* recovered: shared common types, declarations from a shared header */
/* recovered: shared common types */


extern "C" {
int DotVec3(const Vector3 *a, const Vector3 *b);
void Vec3_MulScalar(Vector3 *out, const Vector3 *in, int scale);
void SubVec3(Vector3 *a, Vector3 *b, Vector3 *c);
void AddVec3(Vector3 *a, Vector3 *b, Vector3 *c);
int _ZN4cstd4fdivEii(int a, int b);
void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(
    void *thisPtr, void *file, int i, int fix, unsigned int flags);
void Sound_PlayBank1Panned(int a0, int a1, int a2);
void Trmp3DMario_StateBounce(char *c);
}


struct VtObj {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void m4();
};

// @symbol Trmp3DMario_BounceOffLineB
extern "C" void Trmp3DMario_BounceOffLineB(char *c)
{
    Vector3 tmp;
    Vector3 tmp2;
    Vector3 tmp3;
    int r5v;
    int r4v;
    int dot;
    int scale;
    int fdivr;
    int vx;

    r5v = MARIO3D(c)->mContactOffset;
    r4v = MARIO3D(c)->mContactHalfWidth;
    if (r5v < 0) r5v = -r5v;

    {
        int *src = (int *)(c + 4);
        tmp.x = src[0];
        tmp.y = src[1];
        tmp.z = src[2];
    }

    dot = DotVec3(&MARIO3D(c)->mVel, &tmp);
    scale = (int)(((long long)dot * 0x1200 + 0x800) >> 12);
    Vec3_MulScalar(&tmp2, &tmp, scale);
    SubVec3(&MARIO3D(c)->mVel, &tmp2, &MARIO3D(c)->mVel);

    fdivr = _ZN4cstd4fdivEii(r4v, r4v + r5v);
    MARIO3D(c)->mGravityStep = sTrmp3DGravityStep;

    scale = (int)(((long long)data_ov006_02140578 * fdivr + 0x800) >> 12);
    Vec3_MulScalar(&tmp3, &tmp, scale);
    AddVec3(&MARIO3D(c)->mVel, &tmp3, &MARIO3D(c)->mVel);

    vx = MARIO3D(c)->mVel.x;
    if (vx < -0x1000) vx = -0x1000;
    else if (vx > 0x1000) vx = 0x1000;
    MARIO3D(c)->mVel.x = vx;

    {
        int half = data_ov006_02140578 >> 2;
        int cur = MARIO3D(c)->mVel.y;
        if (cur >= half) half = cur;
        MARIO3D(c)->mVel.y = half;
    }

    ((VtObj *)c)->m4();

    if (MARIO3D(c)->mAnim != 0) {
        MARIO3D(c)->mAnim = 0;
    } else {
        MARIO3D(c)->mAnim = 1;
    }

    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(
        (void *)(c + 0x6c), *(void **)data_ov006_0213b22c[MARIO3D(c)->mAnim], 0x40000000, 0x800, 0);

    *(int *)(c + 0xc4) = 0;
    Sound_PlayBank1Panned(0, MARIO3D(c)->mAnim, MARIO3D(c)->mPos.x);

    {
        int a = pmf_Trmp3DMario_StateBounce[0];
        int b = pmf_Trmp3DMario_StateBounce[1];
        a = b ? a : a;
        MARIO3D(c)->mState[0] = a;
        MARIO3D(c)->mState[1] = b;
    }

    Trmp3DMario_StateBounce(c);
}
}
// ---- Trmp3DMario_PickIdleAnim
namespace ns_020cc198 {
extern "C" {
int RandomIntInternal(int *seed);
void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(
    void *thisPtr, void *file, int i, int fix, unsigned int flags);
void Sound_PlayBank1Panned(int a0, int a1, int a2);
void Trmp3DMario_StateBounce(char *c);
}

extern "C" int sTrmp3DGravityStep;
extern "C" int data_0209e650;
extern "C" int data_ov006_02140558;
extern "C" int data_ov006_02140578;
extern "C" void *data_ov006_0213b22c[];
extern "C" int pmf_Trmp3DMario_StateBounce_2[2];

struct VtObj {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void m4();
};

// @symbol Trmp3DMario_PickIdleAnim
extern "C" void Trmp3DMario_PickIdleAnim(char *c)
{
    int *p38;
    int b;

    MARIO3D(c)->mGravityStep = sTrmp3DGravityStep;
    MARIO3D(c)->mVel.x =
        data_ov006_02140558 +
        (int)(((unsigned int)RandomIntInternal(&data_0209e650) & 0x7fffffff) >> 19);

    b = MARIO3D(c)->mPos.x;
    if (b > 0)
        MARIO3D(c)->mVel.x = -MARIO3D(c)->mVel.x;

    p38 = (int *)(c + 0x38);
    *p38 += (int)((((long long)data_ov006_02140578 << 11) + 0x800) >> 12);

    ((VtObj *)c)->m4();

    MARIO3D(c)->mAnim = 0;

    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(
        (void *)(c + 0x6c), *(void **)data_ov006_0213b22c[MARIO3D(c)->mAnim], 0x40000000, 0x800, 0);

    *(int *)(c + 0xc4) = 0;
    Sound_PlayBank1Panned(0, MARIO3D(c)->mAnim, MARIO3D(c)->mPos.x);

    {
        int a = pmf_Trmp3DMario_StateBounce_2[0];
        int b2 = pmf_Trmp3DMario_StateBounce_2[1];
        a = b2 ? a : a;
        MARIO3D(c)->mState[0] = a;
        MARIO3D(c)->mState[1] = b2;
    }

    Trmp3DMario_StateBounce(c);
}
}
// ---- Trmp3DMario_StateMissed
namespace ns_020cc2ac {
extern "C" {
typedef short s16;
extern void Puff_Spawn(int a, int b);
extern void _Z14ApproachLinearRiii(int *ref, int target, int step);
extern void _ZN5Sound12PlayBank2_2DEj(unsigned int x);
extern void Trmp3DMario_EnterOffstage(char *c);
extern "C" int data_ov006_0214058c;
extern "C" int data_ov006_0213b0ec;

// @symbol Trmp3DMario_StateMissed
void Trmp3DMario_StateMissed(char *c) {
    s16 *p = (s16 *)((int)c + 0x60);
    *p = *p - 1;
    if (MARIO3D(c)->mTimer == 0) {
        Puff_Spawn(MARIO3D(c)->mScreenPos[0], 0xc0);
        data_ov006_0214058c -= 1;
        _Z14ApproachLinearRiii(&data_ov006_0213b0ec, 0, 1);
        _ZN5Sound12PlayBank2_2DEj(0x130);
        Trmp3DMario_EnterOffstage(c);
        return;
    }
    MARIO3D(c)->mVel.x = (int)(((long long)MARIO3D(c)->mVel.x * 0xc00 + 0x800) >> 12);
    {
        int v = MARIO3D(c)->mPos.x;
        if (v < -0x6c000) {
            MARIO3D(c)->mPos.x = -0x6c000;
            return;
        }
        if (v > 0x6c000)
            MARIO3D(c)->mPos.x = 0x6c000;
    }
}
}
}
// ---- Trmp3DMario_EnterMissed
namespace ns_020cc37c {
extern "C" {
extern void D3D_PlaySeAtX(int a, int b);
extern void _ZN5Sound12PlayBank2_2DEj(unsigned int);
extern void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void*, void*, int, int, unsigned int);
extern int data_ov006_0213b0ec[];
extern void *data_ov006_02140540;
extern double pmf_Trmp3DMario_StateMissed_2;
void Trmp3DMario_EnterMissed(char *c);
// @symbol Trmp3DMario_EnterMissed
void Trmp3DMario_EnterMissed(char *c) {
    if (data_ov006_0213b0ec[0] > 1)
        D3D_PlaySeAtX(0x1ca, MARIO3D(c)->mPos.x);
    else
        _ZN5Sound12PlayBank2_2DEj(0x1c9);
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x6c, *(void**)&data_ov006_02140540, 0, 0x800, 0);
    MARIO3D(c)->mTimer = 0x28;
    *(double *)(c + 0x64) = pmf_Trmp3DMario_StateMissed_2;
}
}
}
// ---- Trmp3DMario_StateFall
namespace ns_020cc408 {

extern "C" {
void Trmp3DMario_BounceOffLineB(void *c);
void Trmp3DMario_BounceOffLineA(void *c);
void Camera_ProjectToScreen16(void *a0, void *a1, short *a2);
void Trmp3DMario_EnterFallToLedge(void *c);
void Trmp3DMario_EnterLand(void *c);
int D3D_PlaySeAtX(int a, int b);
void Trmp3DMario_EnterMissed(void *c);
}

extern "C" void *sMgMainCamera;
extern "C" int data_ov006_021405c8[2];

struct VtObj {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void m4();
};

// @symbol Trmp3DMario_StateFall
extern "C" void Trmp3DMario_StateFall(char *c) {
    int v;
    u16 state = MARIO3D(c)->mContact;

    if (state == 1) {
        Trmp3DMario_BounceOffLineB(c);
        return;
    }
    if (state == 2) {
        Trmp3DMario_BounceOffLineA(c);
        return;
    }

    Camera_ProjectToScreen16(sMgMainCamera, (void *)(c + 0x1c), MARIO3D(c)->mScreenPos);

    v = MARIO3D(c)->mPos.x;

    if (v >= -0x5c000) goto L5c;
    if (MARIO3D(c)->mVel.x < 0)
        goto L70;

L5c:
    if (v <= 0x5c000) goto L150;
    if (MARIO3D(c)->mVel.x <= 0)
        goto L150;

L70:
    {
        int f0 = data_ov006_021405c8[0];
        int p = MARIO3D(c)->mPos.y;

        if (p > f0) {
            MARIO3D(c)->mHeightRow = 0;
            Trmp3DMario_EnterFallToLedge(c);
            return;
        }

        f0 -= 0x20000;
        if (p <= f0) goto Ld0;
        if (v <= 0) goto L130;
        MARIO3D(c)->mHeightRow = 0;
        Trmp3DMario_EnterLand(c);
        return;

    Ld0:
        if (v <= 0) goto L130;
        {
            int f1 = data_ov006_021405c8[1];
            int hi1 = f1 + 0x30000;

            if (p >= hi1) goto L130;
            if (p <= f1) goto L10c;
            MARIO3D(c)->mHeightRow = 1;
            Trmp3DMario_EnterFallToLedge(c);
            return;

        L10c:
            f1 -= 0x20000;
            if (p <= f1) goto L130;
            MARIO3D(c)->mHeightRow = 1;
            Trmp3DMario_EnterLand(c);
            return;
        }
    }

L130:
    D3D_PlaySeAtX(0x1b3, v);
    *(int *)(((int)c + 0x34)) *= -1;
    goto L180;

L150:
    if (MARIO3D(c)->mContact == 3) {
        ((VtObj *)c)->m4();
        *(int *)(((int)c + 0x34)) *= -1;
    }

L180:
    {
    int r = MARIO3D(c)->mVel.x;
    if (r > 0x4000) {
        ApproachLinear(MARIO3D(c)->mRotY, 0x4000, 0xc00);
    } else if (r < -0x8000) {
        ApproachLinear(MARIO3D(c)->mRotY, -0x4000, 0xc00);
    } else {
        ApproachLinear(MARIO3D(c)->mRotY, (short)r, 0xc00);
    }
    }

        if (MARIO3D(c)->mPos.y >= -0xc8000)
            return;

        Trmp3DMario_EnterMissed(c);
    }
}
// ---- Trmp3DMario_EnterFall
namespace ns_020cc618 {
extern "C" {
typedef struct { u32 a, b; } Pair;

extern "C" Pair pmf_Trmp3DMario_StateFall;
extern void Trmp3DMario_StateFall(void *self);

// @symbol Trmp3DMario_EnterFall
void Trmp3DMario_EnterFall(void *self) {
    *(W2 *)((char *)self + 0x64) = *(W2 *)&pmf_Trmp3DMario_StateFall;
    Trmp3DMario_StateFall(self);
}
}
}
// ---- Trmp3DMario_StateWalkBack
namespace ns_020cc63c {
extern "C" {
extern "C" int data_ov006_021405c8[];
extern "C" int data_ov006_0214055c;
extern void Trmp3DMario_PickIdleAnim(int *c);
// @symbol Trmp3DMario_StateWalkBack
void Trmp3DMario_StateWalkBack(int *c) {
    short idx = *(short *)((char *)c + 0x52);
    *(int *)((char *)c + 0x20) = data_ov006_021405c8[idx];
    if (*(int *)((char *)c + 0x1c) >= 0x5bff8)
        return;
    data_ov006_0214055c--;
    Trmp3DMario_PickIdleAnim(c);
}
}
}
// ---- Trmp3DMario_EnterWalkBack
namespace ns_020cc698 {
extern "C" {
extern void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void*, void*, int, int, unsigned int);
extern int data_ov006_021405c8[];
extern void *data_ov006_02140564;
extern double pmf_Trmp3DMario_StateWalkBack;
void Trmp3DMario_EnterWalkBack(char *c);
// @symbol Trmp3DMario_EnterWalkBack
void Trmp3DMario_EnterWalkBack(char *c) {
    MARIO3D(c)->mGravityStep = 0;
    MARIO3D(c)->mPos.y = data_ov006_021405c8[MARIO3D(c)->mHeightRow];
    MARIO3D(c)->mPos.z = 0;
    MARIO3D(c)->mVel.x = -0x1800;
    MARIO3D(c)->mVel.y = 0;
    MARIO3D(c)->mVel.z = 0;
    MARIO3D(c)->mRotY = -0x4000;
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x6c, *(void**)&data_ov006_02140564, 0, 0x800, 0);
    *(double *)(c + 0x64) = pmf_Trmp3DMario_StateWalkBack;
}
}
}
// ---- Trmp3DMario_StateOnLedge
namespace ns_020cc724 {
extern "C" {
/* local extern: the call passes an untyped this, so it cannot use the header method. */
extern int _ZN15dExtFrameCtrl_c8FinishedEv(void *self);
extern void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *self, void *file, int i, int fix, u32 j);
extern int _Z14ApproachLinearRsss(short *value, short target, short step);
extern void Trmp3DMario_EnterWalkBack(char *c);

extern "C" void *data_ov006_021405c8[];
extern "C" void *data_ov006_0214057c;
extern "C" void *data_ov006_02140564;
extern "C" void *data_ov006_0214056c;
extern "C" void *data_ov006_02140568;

// @symbol Trmp3DMario_StateOnLedge
void Trmp3DMario_StateOnLedge(char *c) {
    *(void **)(c + 0x20) = data_ov006_021405c8[MARIO3D(c)->mHeightRow];

    if (*(void **)(c + 0xcc) == data_ov006_0214057c) {
        if (_ZN15dExtFrameCtrl_c8FinishedEv(c + 0xbc) != 0) {
            _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x6c, data_ov006_02140564, 0, 0x800, 0);
            return;
        }
    }

    if (*(void **)(c + 0xcc) == data_ov006_02140564) {
        if (MARIO3D(c)->mVel.x > 0) {
            if (MARIO3D(c)->mPos.x > 0x70000) {
                MARIO3D(c)->mPos.x = 0x70000;
                MARIO3D(c)->mVel.x = 0;
                _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x6c, data_ov006_0214056c, 0x40000000, 0x800, 0);
            }
            return;
        }
        if (_Z14ApproachLinearRsss((s16 *)(c + 0x4a), 0x4000, 0x800) != 0)
            MARIO3D(c)->mVel.x = 0x1000;
        return;
    }

    if (*(void **)(c + 0xcc) == data_ov006_0214056c) {
        if (_ZN15dExtFrameCtrl_c8FinishedEv(c + 0xbc) != 0) {
            _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x6c, data_ov006_02140568, 0x40000000, 0x800, 0);
            return;
        }
    }

    if (*(void **)(c + 0xcc) == data_ov006_02140568) {
        if (_ZN15dExtFrameCtrl_c8FinishedEv(c + 0xbc) != 0)
            Trmp3DMario_EnterWalkBack(c);
    }
}
}
}
// ---- Trmp3DMario_EnterOnLedge
namespace ns_020cc8c8 {
extern "C" {

typedef short s16;
typedef struct { int x, y; } G2;
extern void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *self, void *file, int a, int b, unsigned int u);
extern "C" int pmf_Trmp3DMario_StateFallToLedge_2[2];
extern "C" G2 pmf_Trmp3DMario_StateOnLedge;
extern "C" void *data_ov006_021405c8[];
extern "C" void *data_ov006_0214057c;
extern "C" void *data_ov006_02140564;
extern "C" int data_ov006_0214055c;

// @symbol Trmp3DMario_EnterOnLedge
void Trmp3DMario_EnterOnLedge(char *p) {
    int *cur;
    int *want;
    int z = 0;
    MARIO3D(p)->mGravityStep = z;
    *(void **)(p + 0x20) = data_ov006_021405c8[MARIO3D(p)->mHeightRow];
    MARIO3D(p)->mPos.z = z;
    MARIO3D(p)->mVel.x = z;
    MARIO3D(p)->mVel.y = z;
    MARIO3D(p)->mVel.z = z;
    cur = MARIO3D(p)->mState;
    want = pmf_Trmp3DMario_StateFallToLedge_2;
    if (cur[0] == want[0] && (cur[1] == want[1] || MARIO3D(p)->mState[0] == 0)) {
        _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(p + 0x6c, data_ov006_0214057c, 0x40000000, 0x800, 0);
    } else {
        _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(p + 0x6c, data_ov006_02140564, 0, 0x800, 0);
    }
    {
        int *ctr = &data_ov006_0214055c;
        int c = *ctr;
        *ctr = c + 1;
        *(W2 *)(p + 0x64) = *(W2 *)&pmf_Trmp3DMario_StateOnLedge;
    }
}
}
}
// ---- Trmp3DMario_StateWalkIn
namespace ns_020cc9b8 {
extern "C" {
extern "C" int data_ov006_021405c8;
extern void Trmp3DMario_PickIdleAnim(int *c);
// @symbol Trmp3DMario_StateWalkIn
void Trmp3DMario_StateWalkIn(int *c) {
    *(int *)((char *)c + 0x20) = data_ov006_021405c8;
    if (*(int *)((char *)c + 0x1c) <= -0x5c008)
        return;
    Trmp3DMario_PickIdleAnim(c);
}
}
}
#pragma push
#pragma optimize_for_size on
// ---- Trmp3DMario_EnterWalkIn
namespace ns_020cc9fc {
extern "C" {
extern int _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(char *anim, void *file, int a, int b, unsigned int u);
}
struct G2 { int w[2]; };
extern "C" int data_ov006_021405c8;
extern "C" struct G2 data_ov006_02140564;
extern "C" struct G2 pmf_Trmp3DMario_StateOnGround;
extern "C" int data_ov006_0214058c;
extern "C" struct G2 pmf_Trmp3DMario_StateWalkIn;

// @symbol Trmp3DMario_EnterWalkIn
extern "C" void Trmp3DMario_EnterWalkIn(char *c) {
    MARIO3D(c)->mGravityStep = 0;
    MARIO3D(c)->mPos.y = data_ov006_021405c8;
    MARIO3D(c)->mPos.z = 0;
    MARIO3D(c)->mPrevPos.x = MARIO3D(c)->mPos.x;
    MARIO3D(c)->mPrevPos.y = MARIO3D(c)->mPos.y;
    MARIO3D(c)->mPrevPos.z = MARIO3D(c)->mPos.z;
    MARIO3D(c)->mVel.x = 0x1800;
    MARIO3D(c)->mVel.y = 0;
    MARIO3D(c)->mVel.z = 0;
    MARIO3D(c)->mRotY = 0x4000;
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x6c, (void *)data_ov006_02140564.w[0], 0, 0x800, 0);
    int *s = (int *)((unsigned int)(unsigned long long)(c + 0x64) & 0xffffffffu);
    struct G2 *d = &pmf_Trmp3DMario_StateOnGround;
    if (s[0] != d->w[0] || (s[1] != d->w[1] && MARIO3D(c)->mState[0] != 0)) {
        data_ov006_0214058c += 1;
    }
    *(struct G2 *)(c + 0x64) = pmf_Trmp3DMario_StateWalkIn;
}
}
#pragma pop
// ---- Trmp3DMario_StateOnGround
namespace ns_020ccae0 {
extern "C" {
/* local extern: the call passes an untyped this, so it cannot use the header method. */
extern int _ZN15dExtFrameCtrl_c8FinishedEv(void *self);
extern void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *self, void *file, int i, int fix, u32 j);
extern int _Z14ApproachLinearRsss(short *value, short target, short step);
extern void Trmp3DMario_EnterWalkIn(char *c);

extern "C" void *data_ov006_021405c8;
extern "C" void *data_ov006_0214057c;
extern "C" void *data_ov006_02140564;
extern "C" void *data_ov006_0214056c;
extern "C" void *data_ov006_02140568;

// @symbol Trmp3DMario_StateOnGround
void Trmp3DMario_StateOnGround(char *c) {
    *(void **)(c + 0x20) = data_ov006_021405c8;

    if (*(void **)(c + 0xcc) == data_ov006_0214057c) {
        if (_ZN15dExtFrameCtrl_c8FinishedEv(c + 0xbc) != 0) {
            _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x6c, data_ov006_02140564, 0, 0x800, 0);
            return;
        }
    }

    if (*(void **)(c + 0xcc) == data_ov006_02140564) {
        if (MARIO3D(c)->mVel.x < 0) {
            if (MARIO3D(c)->mPos.x < -0x70000) {
                MARIO3D(c)->mPos.x = -0x70000;
                MARIO3D(c)->mVel.x = 0;
                _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x6c, data_ov006_0214056c, 0x40000000, 0x800, 0);
            }
            return;
        }
        if (_Z14ApproachLinearRsss((s16 *)(c + 0x4a), -0x4000, 0x800) != 0)
            MARIO3D(c)->mVel.x = -0x1000;
        return;
    }

    if (*(void **)(c + 0xcc) == data_ov006_0214056c) {
        if (_ZN15dExtFrameCtrl_c8FinishedEv(c + 0xbc) != 0) {
            _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x6c, data_ov006_02140568, 0x40000000, 0x800, 0);
            return;
        }
    }

    if (*(void **)(c + 0xcc) == data_ov006_02140568) {
        if (_ZN15dExtFrameCtrl_c8FinishedEv(c + 0xbc) != 0)
            Trmp3DMario_EnterWalkIn(c);
    }
}
}
}
// ---- Trmp3DMario_EnterOnGround
namespace ns_020ccc8c {
extern "C" {
struct BCA_File;
extern int data_ov006_021405c8;
extern struct BCA_File* data_ov006_0214057c;
extern double pmf_Trmp3DMario_StateOnGround_2;
}
extern "C" void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void* thiz, struct BCA_File* f, int frame, int speed, unsigned mode);
// @symbol Trmp3DMario_EnterOnGround
extern "C" void Trmp3DMario_EnterOnGround(char *c) {
    MARIO3D(c)->mGravityStep = 0;
    MARIO3D(c)->mPos.y = data_ov006_021405c8;
    MARIO3D(c)->mPos.z = 0;
    MARIO3D(c)->mVel.x = 0;
    MARIO3D(c)->mVel.y = 0;
    MARIO3D(c)->mVel.z = 0;
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x6c, data_ov006_0214057c, 0x40000000, 0x800, 0);
    *(double *)(c + 0x64) = pmf_Trmp3DMario_StateOnGround_2;
}
}
// ---- Trmp3DMario_IsOffstage
namespace ns_020ccd04 {
extern "C" {
extern "C" int pmf_Trmp3DMario_StateOffstage_3[];
// @symbol Trmp3DMario_IsOffstage
int Trmp3DMario_IsOffstage(int *r0) {
    int* p = (int *)(((int)r0 + 0x64));
    int *g = pmf_Trmp3DMario_StateOffstage_3;
    int ret = 1;
    if (p[0] == g[0]) {
        if (p[1] == g[1]) goto zero;
        if (r0[0x19] != 0) goto out;
    zero:
        ret = 0;
    }
out:
    return ret == 0;
}
}
}
// ---- Trmp3DMario_StateOffstage
namespace ns_020ccd64 {
extern "C" {
struct S { int w[1]; };
extern "C" struct S data_ov006_021405c8;
// @symbol Trmp3DMario_StateOffstage
void Trmp3DMario_StateOffstage(char *p) {
    *(struct S *)(p + 0x20) = data_ov006_021405c8;
}
}
}
// ---- Trmp3DMario_EnterOffstage
namespace ns_020ccd78 {
extern "C" {
extern int data_ov006_021405c8;
struct V3 { int a, b, c; };
extern struct V3 data_020a0ebc;
extern void *data_ov006_02140564;
struct G2 { int w[2]; };
extern struct G2 pmf_Trmp3DMario_StateOffstage_2;
void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *thiz, void *bca, int frame, int speed, unsigned int flags);
// @symbol Trmp3DMario_EnterOffstage
void Trmp3DMario_EnterOffstage(char *c) {
    MARIO3D(c)->mPos.y = data_ov006_021405c8;
    MARIO3D(c)->mPos.x = -0x90000;
    MARIO3D(c)->mPos.z = 0;
    MARIO3D(c)->mVel.x = data_020a0ebc.a;
    MARIO3D(c)->mVel.y = data_020a0ebc.b;
    MARIO3D(c)->mVel.z = data_020a0ebc.c;
    MARIO3D(c)->mGravityStep = 0;
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x6c, data_ov006_02140564, 0, 0x800, 0);
    *(struct G2 *)(c + 0x64) = pmf_Trmp3DMario_StateOffstage_2;
}
}
}
// ---- Trmp3DMario_Load
namespace ns_020cce0c {
extern "C" {
typedef struct { int w[2]; } SharedFilePtr;
typedef struct BMD_File BMD_File;

extern "C" SharedFilePtr data_ov006_021405f8;
extern "C" SharedFilePtr data_ov006_02140608;
extern "C" SharedFilePtr data_ov006_021405d0;
extern "C" SharedFilePtr data_ov006_02140628;
extern "C" SharedFilePtr data_ov006_02140618;
extern "C" SharedFilePtr data_ov006_02140638;
extern "C" SharedFilePtr data_ov006_021405f0;
extern "C" SharedFilePtr data_ov006_021405e8;
extern "C" SharedFilePtr data_ov006_02140600;
extern "C" SharedFilePtr data_ov006_021405e0;
extern "C" SharedFilePtr data_ov006_02140610;
extern "C" SharedFilePtr data_ov006_021405d8;
extern "C" SharedFilePtr data_ov006_02140620;

extern "C" void* data_ov006_02140590;
extern "C" void* data_ov006_02140560;
extern "C" void* data_ov006_02140580;
extern "C" void* data_ov006_021405c0;
extern "C" void* data_ov006_0214054c;
extern "C" void* data_ov006_02140564;
extern "C" void* data_ov006_021405a0;
extern "C" void* data_ov006_0214057c;
extern "C" void* data_ov006_0214056c;
extern "C" void* data_ov006_02140568;
extern "C" void *sTrmpAnimBounce;
extern "C" void* data_ov006_02140540;

extern "C" char *sMgMainCamera;

extern BMD_File* _ZN5Model8LoadFileER13SharedFilePtr(SharedFilePtr* f);
/* local extern: the call passes an untyped this, so it cannot use the header method. */
extern void* _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(SharedFilePtr* f);
extern int _ZN9ModelBase7SetFileEP8BMD_Fileii(void* self, BMD_File* f, int a, int b);
extern void Camera_ProjectToScreen16(char* p, void* q, short* s);
extern void func_02016a14(void* self, int a, int b);
extern void func_02016a04(void* self, int a);
extern void Trmp3DMario_EnterOffstage(char *c);

// @symbol Trmp3DMario_Load
int Trmp3DMario_Load(char* c)
{
    BMD_File* f;
    int ret;

    f = _ZN5Model8LoadFileER13SharedFilePtr(&data_ov006_021405f8);
    data_ov006_02140590 = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_02140608);
    data_ov006_02140560 = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_021405d0);
    data_ov006_02140580 = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_02140628);
    data_ov006_021405c0 = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_02140618);
    data_ov006_0214054c = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_02140638);
    data_ov006_02140564 = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_021405f0);
    data_ov006_021405a0 = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_021405e8);
    data_ov006_0214057c = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_02140600);
    data_ov006_0214056c = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_021405e0);
    data_ov006_02140568 = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_02140610);
    sTrmpAnimBounce = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_021405d8);
    data_ov006_02140540 = _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr(&data_ov006_02140620);
    ret = _ZN9ModelBase7SetFileEP8BMD_Fileii(c + 0x6c, f, 1, -1);
    MARIO3D(c)->mAnim = 0;
    if (sMgMainCamera != 0)
        Camera_ProjectToScreen16(sMgMainCamera, c + 0x1c, MARIO3D(c)->mScreenPos);
    MARIO3D(c)->mGravityStep = 0;
    func_02016a14(c + 0x6c, 0x6bff, 0);
    func_02016a04(c + 0x6c, 0x21d);
    Trmp3DMario_EnterOffstage(c);
    return ret;
}
}
}
// ---- Trmp3DMario_Destruct
namespace ns_020ccfc8 {
extern "C" SharedFilePtr data_ov006_021405f8, data_ov006_02140608, data_ov006_021405d0,
    data_ov006_02140628, data_ov006_02140618, data_ov006_02140638, data_ov006_021405f0,
    data_ov006_021405e8, data_ov006_02140600, data_ov006_021405e0, data_ov006_02140610,
    data_ov006_021405d8, data_ov006_02140620;
extern "C" int data_ov006_02140590, data_ov006_02140560, data_ov006_02140580, data_ov006_021405c0,
    data_ov006_0214054c, data_ov006_02140564, data_ov006_021405a0, data_ov006_0214057c,
    data_ov006_0214056c, data_ov006_02140568, sTrmpAnimBounce, data_ov006_02140540;
extern "C" int data_ov006_0213b2c4;
extern "C" int data_ov006_0213b3c4;

// @symbol Trmp3DMario_Destruct
extern "C" void* Trmp3DMario_Destruct(int* c)
{
    *c = (int)&data_ov006_0213b2c4;
    data_ov006_021405f8.Release();
    data_ov006_02140608.Release();
    data_ov006_021405d0.Release();
    data_ov006_02140628.Release();
    data_ov006_02140618.Release();
    data_ov006_02140638.Release();
    data_ov006_021405f0.Release();
    data_ov006_021405e8.Release();
    data_ov006_02140600.Release();
    data_ov006_021405e0.Release();
    data_ov006_02140610.Release();
    data_ov006_021405d8.Release();
    data_ov006_02140620.Release();
    data_ov006_02140590 = 0;
    data_ov006_02140560 = 0;
    data_ov006_02140580 = 0;
    data_ov006_021405c0 = 0;
    data_ov006_0214054c = 0;
    data_ov006_02140564 = 0;
    data_ov006_021405a0 = 0;
    data_ov006_0214057c = 0;
    data_ov006_0214056c = 0;
    data_ov006_02140568 = 0;
    sTrmpAnimBounce = 0;
    data_ov006_02140540 = 0;
    ((ModelAnim*)((char*)c+0x6c))->~ModelAnim();
    *c = (int)&data_ov006_0213b3c4;
    return c;
}
}
// ---- Trmp3DMario_Construct
namespace ns_020cd12c {
extern "C" {
/* recovered: vtable identified, declarations from a shared header */
extern "C" int data_ov006_0213b2c4[];
extern void TrmpObjAdapter_Construct(int *c);
/* recovered: vtable identified */
/* vtable identified: VT0 = data_ov006_0213b2c4 */
// @symbol Trmp3DMario_Construct
int *Trmp3DMario_Construct(int *t)
{
    TrmpObjAdapter_Construct(t);
    t[0] = (int)data_ov006_0213b2c4;
    _ZN9ModelAnimC1Ev((char *)t + 0x6c);
    return t;
}
}
}
// ---- Trmp3DMario_CountFinished
namespace ns_020cd158 {
extern "C" {
extern "C" int sTrmp3DMarioCount;
extern "C" char *sTrmp3DMarios;
extern "C" int pmf_Trmp3DMario_StateOffstage[];

// @symbol Trmp3DMario_CountFinished
int Trmp3DMario_CountFinished(void)
{
    int i = 0;
    char *e;
    int first;
    int n;
    int *b;
    n = sTrmp3DMarioCount;
    if (n > 0) {
        e = sTrmp3DMarios;
        b = pmf_Trmp3DMario_StateOffstage;
        first = b[0];
        do {
            int *p = (int *)((unsigned int)e + 0x64);
            if (p[0] == first) {
                if (p[1] == *(volatile int *)(b + 1)) goto next;
                if (*(volatile int *)(e + 0x64) == 0) goto next;
            }
            return 0;
        next:
            e += 0xd0;
            i++;
        } while (i < n);
    }
    return 1;
}
}
}
// ---- Trmp3DMario_StartAll
namespace ns_020cd1e0 {
extern "C" {
extern void Trmp3DMario_EnterByKind(void *p);
extern void Trmp3DMario_UpdateMatrix(char *o);
extern "C" int sTrmp3DMarioCount[];
extern "C" int sTrmp3DFallSpeed[];
extern "C" int sTrmp3DGravityStep[];
extern "C" char *sTrmp3DMarios[];

// @symbol Trmp3DMario_StartAll
void Trmp3DMario_StartAll(void)
{
    int i;
    int off;
    i = 0;
    sTrmp3DGravityStep[0] = 0x100;
    sTrmp3DFallSpeed[0] = -0x4800;
    if (sTrmp3DMarioCount[0] <= 0)
        return;
    off = 0;
    do {
        Trmp3DMario_EnterByKind(sTrmp3DMarios[0] + off);
        Trmp3DMario_UpdateMatrix(sTrmp3DMarios[0] + off);
        i++;
        off += 0xd0;
    } while (i < sTrmp3DMarioCount[0]);
}
}
}
#pragma push
#pragma opt_common_subs off
// ---- Trmp3DMario_DrawAll
namespace ns_020cd270 {
extern "C" {

extern void func_0203cd80(int *v, int a);
extern void func_0203ccd4(int *v, int a);
extern "C" int sTrmp3DMarioCount;
extern "C" char *sTrmp3DMarios;
extern void Trmp3DMario_Render(char *p);
extern void Puff_DrawAll(void);

// @symbol Trmp3DMario_DrawAll
void Trmp3DMario_DrawAll(void)
{
    int v[3];
    int w[3];

    v[0] = 0;
    v[1] = 0;
    v[2] = 0xfffff008;
    func_0203cd80(v, 0x2000);
    func_0203ccd4(v, 0);
    *(volatile int *)0x040004c8 =
        (((short)v[0] >> 3) & 0x3ff) |
        ((((short)v[1] >> 3) & 0x3ff) << 10) |
        ((((short)v[2] >> 3) & 0x3ff) << 20);

    w[0] = 0;
    w[1] = 0;
    w[2] = 0xfffff008;
    func_0203cd80(w, -0x2000);
    *(volatile int *)0x040004c8 =
        (((short)w[0] >> 3) & 0x3ff) |
        ((((short)w[1] >> 3) & 0x3ff) << 10) |
        ((((short)w[2] >> 3) & 0x3ff) << 20) | 0x40000000;

    {
        int i;
        for (i = 0; i < sTrmp3DMarioCount; i++)
            Trmp3DMario_Render(sTrmp3DMarios + i * 0xd0);
    }

    Puff_DrawAll();
}
}
}
#pragma pop
// ---- Trmp3DMario_UpdateAll
namespace ns_020cd39c {
extern "C" {
extern void Trmp3DMario_Update(char *p);
extern void Puff_UpdateAll(void);
extern "C" int sTrmp3DMarioCount;
extern "C" char *sTrmp3DMarios;
extern "C" int data_ov006_0214055c;
extern "C" int data_ov006_02142f60;

// @symbol Trmp3DMario_UpdateAll
void Trmp3DMario_UpdateAll(void)
{
    int i;
    for (i = 0; i < sTrmp3DMarioCount; i++)
        Trmp3DMario_Update(sTrmp3DMarios + i * 0xd0);
    if (data_ov006_0214055c != 0)
        data_ov006_02142f60 = 1;
    else
        data_ov006_02142f60 = 0;
    Puff_UpdateAll();
}
}
}
// ---- Trmp3DMario_ResetAll
namespace ns_020cd424 {
extern "C" {
extern int Trmp3DMario_SetTuning(int sz);
extern void Trmp3DMario_SetSpawnHeight(int n);
extern void Trmp3DMario_EnterOffstage(char *c);
extern void Trmp3DMario_UpdateMatrix(char *o);
extern void Puff_ClearAll(int a0, int a1);

extern "C" int sTrmp3DMarioCount;
extern "C" int data_ov006_0213b0ec;
extern "C" int sTrmpComboCount;
extern "C" int data_ov006_0214058c;
extern "C" int data_ov006_0214055c;
extern "C" char *sTrmp3DMarios;

// @symbol Trmp3DMario_ResetAll
void Trmp3DMario_ResetAll(unsigned int n, int arg1)
{
    int i;
    Trmp3DMario_SetTuning((n % 5 + n / 5) * 0x150 + 0x1000);
    Trmp3DMario_SetSpawnHeight(arg1);
    data_ov006_0213b0ec = 3;
    sTrmpComboCount = 0;
    data_ov006_0214058c = 0;
    data_ov006_0214055c = 0;
    for (i = 0; i < sTrmp3DMarioCount; i++) {
        Trmp3DMario_EnterOffstage(sTrmp3DMarios + i * 0xd0);
        Trmp3DMario_UpdateMatrix(sTrmp3DMarios + i * 0xd0);
    }
    Puff_ClearAll(0, 0);
}
}
}
// ---- Trmp3DMario_SetTuning
namespace ns_020cd510 {
extern "C" {
extern int func_020531a4(int a);
extern "C" int sTrmp3DFallSpeed;
extern "C" int sTrmp3DGravityStep;
extern "C" int data_ov006_02140558;
extern "C" int data_ov006_02140578;
extern "C" int data_ov006_02140570;

// @symbol Trmp3DMario_SetTuning
void Trmp3DMario_SetTuning(int a)
{
    int v;
    if (a > 0x2800) a = 0x2800;
    v = func_020531a4(a);
    sTrmp3DFallSpeed = (int)(((long long)v * -0x2400 + 0x800) >> 12);
    sTrmp3DGravityStep = (int)(((long long)a * 0xe0 + 0x800) >> 12);
    data_ov006_02140558 = (int)(((long long)v * 0xc00 + 0x800) >> 12);
    data_ov006_02140578 = (int)(((long long)v * 0x4800 + 0x800) >> 12);
    data_ov006_02140570 = (int)(((long long)v * 0x5400 + 0x800) >> 12);
}
}
}
// ---- Trmp3DMario_SetSpawnHeight
namespace ns_020cd62c {
extern "C" {
extern "C" int data_ov006_0212e024[];
extern "C" int data_ov006_021405c8[];
// @symbol Trmp3DMario_SetSpawnHeight
void Trmp3DMario_SetSpawnHeight(int n){
  data_ov006_021405c8[0]=data_ov006_0212e024[0]+(n<<12);
  data_ov006_021405c8[1]=data_ov006_0212e024[1]+(n<<12);
}
}
}
// ---- Trmp3DMario_InitPool
namespace ns_020cd658 {
extern "C" {
extern "C" int sTrmp3DMarioCount;
extern "C" unsigned char *sTrmp3DMarios;
extern "C" unsigned char *sTrmpJumpers[];
extern int Trmp3DMario_Load(unsigned char*);
// @symbol Trmp3DMario_InitPool
int Trmp3DMario_InitPool(unsigned char* a0,int a1){
  int i=0;
  int off;
  unsigned char* x;
  sTrmp3DMarioCount = a1;
  sTrmp3DMarios = a0;
  if(a1>0){
    off=0;
    do{
        if (Trmp3DMario_Load(sTrmp3DMarios + off) == 0)
            return 0;
        x = sTrmp3DMarios + off;
        if (i < 5)
            sTrmpJumpers[i] = x;
        i++;
        off += 0xd0;
    } while (i < sTrmp3DMarioCount);
  }
  return 1;
}
}
}
// ---- TrmpRingObjAdapter_Clear
namespace ns_020cd6d8 {
extern "C" {
extern void TrmpObjAdapter_Clear(short *p);
// @symbol TrmpRingObjAdapter_Clear
void TrmpRingObjAdapter_Clear(short *c){
  TrmpObjAdapter_Clear(c);
  *(short*)((char*)c+0x20)=0;
}
}
}
// ---- TrmpRingObjAdapter_Construct
namespace ns_020cd6f4 {
extern "C" {
extern void TrmpObjAdapter_Construct(int *c);
extern "C" int data_ov006_0213b3e0[];
// @symbol TrmpRingObjAdapter_Construct
int *TrmpRingObjAdapter_Construct(int *c){
  TrmpObjAdapter_Construct(c);
  *c=(int)data_ov006_0213b3e0;
  *(short*)((char*)c+0x20)=0;
  return c;
}
}
}
// ---- TrmpObjAdapter_Clear
namespace ns_020cd720 {
extern "C" {
// @symbol TrmpObjAdapter_Clear
void TrmpObjAdapter_Clear(short *p)
{
    p[12] = 0;
}
}
}
// ---- TrmpObjAdapter_Construct
namespace ns_020cd72c {
extern "C" {
extern "C" int data_ov006_0213b3c4[];
// @symbol TrmpObjAdapter_Construct
void TrmpObjAdapter_Construct(int *c){
  *c=(int)data_ov006_0213b3c4;
  *(short*)((char*)c+0x18)=0;
}
}
}
