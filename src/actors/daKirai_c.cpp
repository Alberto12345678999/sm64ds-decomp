//cpp
/* daKirai_c, ov060 0x02118438..0x02118cbc.
 * daKirai_c_classInit stays out.
 */

#include "daKirai_c.h"
#include "common.h"
#include "SharedFilePtr.h"

/* Per-member opt brackets bind only when codegen is not deferred, and that
 * also lays .text down in source order. The file is therefore ROM-ascending. */
#pragma defer_codegen off

extern "C" {
extern void ClearSpikeBomb(int idx);
extern char *_ZN8dActor_c15FindWithActorIDEjPS_(unsigned int id, char *p);
extern int Vec3_HorzLen(const Vector3 *v);
extern int Vec3_Dist(const Vector3 *a, const Vector3 *b);
extern void _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(unsigned int id, int x, int y, int z);
extern void func_02012694(int a, void* b);
extern void _ZN8dActor_c10EarthquakeERK7Vector35Fix12IiE(void* self, struct Vector3* v, int f);
extern void Matrix4x3_FromTranslation(void* m, int x, int y, int z);
extern void _ZN9ModelBase12ApplyOpacityEjj(void* thiz, unsigned int opacity, unsigned int unused);
extern void *_ZN8dActor_c13ClosestPlayerEv(void *self);
extern char *_ZN8dActor_c10FindWithIDEj(unsigned int id);
extern void _ZN6Player4HurtERK7Vector3j5Fix12IiEjjj(void* self, struct Vector3* v, unsigned int b, int c, unsigned int d, unsigned int e, unsigned int f);
extern void _ZN5dCc_c5ClearEv(void* p);
extern void _ZN10dCcAcPos_c21SetPosRelativeToActorERK7Vector3(void* p, void* v);
extern void _ZN5dCc_c6UpdateEv(void* p);
extern void *_ZN5Model8LoadFileER13SharedFilePtr(void *sfp);
extern void _ZN9ModelBase7SetFileEP8BMD_Fileii(void *thiz, void *f, int a, int b);
extern void _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj(
    void *thiz, void *actor, const Vector3 &v, int radius, int height, unsigned a, unsigned b);
extern short Vec3_HorzAngle(const Vector3 *v0, const Vector3 *v1);
extern int AddSpikeBomb(void *p);
extern char data_ov060_0211b1c4;
extern int data_ov060_0211b1d8[];
}

struct V3 { int x, y, z; };

struct Sub {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void m(int);
};

typedef struct {
    char _pad0[0x80];
    int scaleX;    /* +0x080 */
    int scaleY;    /* +0x084 */
    int scaleZ;    /* +0x088 */
    char _pad1[0xb0];
    u32 flags;     /* +0x13c */
    char _pad2[0x6c];
    u16 timer;     /* +0x1ac */
} Work;

enum Bool { FALSE, TRUE };

// @symbol _ZN9daKirai_cD1Ev
// @symbol _ZN9daKirai_cD0Ev
daKirai_c::~daKirai_c()
{
}

extern "C" {
// @symbol func_ov060_021184bc
void func_ov060_021184bc(char *c)
{
    int i;
    int j;
    unsigned int id;
    char *a;

    ClearSpikeBomb(*(int *)(c + 0x1a8));
    *(int *)(((int)c + 0x13c)) |= 1;
    *(int *)(c + 0x170) = 3;
    a = 0;
    for (i = 0; i < 8; i++)
        ((int *)(c + 0x188))[i] = 0;
    j = 0;
    id = 0x11c;
    while (1) {
        a = _ZN8dActor_c15FindWithActorIDEjPS_(id, a);
        if (a == 0)
            break;
        if (a != c) {
            ((int *)(c + 0x188))[j] = *(int *)(a + 4);
            j++;
            if (j == 8)
                break;
        }
    }
}

// @symbol func_ov060_02118544
int func_ov060_02118544(char *c, void *v) {
    int h, r2;
    if (*(int*)(c + 0x170) != 0) return 0;
    h = Vec3_HorzLen((Vector3 *)v);
    r2 = *(int*)(c + 0x180);
    if (h >= r2 - 0x12c000 && h <= r2 + 0x12c000) {
        if (Vec3_Dist((Vector3 *)(c + 0x174), (Vector3 *)v) < *(int*)(c + 0x184)) return 1;
    }
    return 0;
}

// @symbol func_ov060_021185c4
void func_ov060_021185c4(char* c)
{
    struct Vector3 v;
    *(int*)(c + 0x170) = 1;
    _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(0xa8, *(int*)(c + 0x5c), *(int*)(c + 0x60), *(int*)(c + 0x64));
    _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(0xa9, *(int*)(c + 0x5c), *(int*)(c + 0x60), *(int*)(c + 0x64));
    _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(0xaa, *(int*)(c + 0x5c), *(int*)(c + 0x60), *(int*)(c + 0x64));
    _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(0xab, *(int*)(c + 0x5c), *(int*)(c + 0x60), *(int*)(c + 0x64));
    _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(0xac, *(int*)(c + 0x5c), *(int*)(c + 0x60), *(int*)(c + 0x64));
    func_02012694(0x2f, c + 0x74);
    v.x = *(int*)(c + 0x5c);
    v.y = *(int*)(c + 0x60);
    v.z = *(int*)(c + 0x64);
    _ZN8dActor_c10EarthquakeERK7Vector35Fix12IiE(c, &v, 0x7d0000);
    *(short*)(c + 0x1ac) = 0;
    func_ov060_021184bc(c);
}

// @symbol func_ov060_02118690
void func_ov060_02118690(char* c) {
    Matrix4x3_FromTranslation(c + 0xf0, *(int*)(c + 0x5c) >> 3, *(int*)(c + 0x60) >> 3, *(int*)(c + 0x64) >> 3);
    _ZN9ModelBase12ApplyOpacityEjj(c + 0xd4, (unsigned char)((int)*(unsigned char*)(c + 0x1ae) >> 3), 1);
}

// @symbol func_ov060_021186d8
void func_ov060_021186d8(unsigned char* c) {
    *(int*)(c + 0x80) = 0x1000;
    *(int*)(c + 0x84) = 0x1000;
    *(int*)(c + 0x88) = 0x1000;
    *(unsigned char*)(c + 0x1ae) = 0xff;
    *(int*)(c + 0x170) = 0;
    (*(int *)(((int)c + 0x13c))) &= ~1;
    *(short*)(c + 0x1ac) = 0;
    *(int*)(c + 0x1a8) = AddSpikeBomb(c);
}

#pragma opt_strength_reduction off
#pragma opt_common_subs off
// @symbol func_ov060_02118728
void func_ov060_02118728(char *c)
{
    struct Vector3 v;
    void *player;
    char *bestActor;
    char *actor;
    int best;
    int i;

    player = _ZN8dActor_c13ClosestPlayerEv(c);
    if (((*(int *)(c + 0xb0) & 8) ? 1 : 0) == 0) return;
    if (player == 0) return;

    {
        struct Vector3 *pp = (struct Vector3 *)((int)player + 0x5c);
        v.x = pp->x;
        v.y = pp->y;
        v.z = pp->z;
    }
    best = Vec3_Dist((struct Vector3 *)(c + 0x5c), &v);
    bestActor = c;

    for (i = 0; i < 8; i++) {
        int id = *(int *)(c + (i << 2) + 0x188);
        if (id == 0) continue;
        actor = (char *)_ZN8dActor_c10FindWithIDEj(id);
        if (actor != 0) {
            if (*(int *)(actor + 0x170) != 3) return;
            if (((*(int *)(actor + 0xb0) & 8) ? 1 : 0) == 0) continue;
            {
                int d = Vec3_Dist(&v, (struct Vector3 *)(actor + 0x5c));
                if (d < best) {
                    best = d;
                    bestActor = actor;
                }
            }
        } else {
            *(int *)(c + (i << 2) + 0x188) = 0;
        }
    }
    func_ov060_021186d8((unsigned char *)bestActor);
}
#pragma opt_common_subs on
#pragma opt_strength_reduction on

// @symbol func_ov060_02118834
void func_ov060_02118834(char *c)
{
    unsigned short h = *(unsigned short*)(c + 0x100 + 0xac);
    int ip = h * 9;
    int v = (ip << 12) / 14 + 0x1000;
    *(int*)(c + 0x80) = v;
    *(int*)(c + 0x84) = v;
    *(int*)(c + 0x88) = v;
    *(unsigned char *)(((int)c + 0x1ae)) -= 0xa;
    if (*(unsigned char*)(c + 0x1ae) < 0xa) *(unsigned char*)(c + 0x1ae) = 0;
    *(int *)(((int)c + 0x60)) += *(int*)(c + 0xa8);
    if (*(unsigned short*)(c + 0x100 + 0xac) == 0x1c) func_ov060_021184bc(c);
    *(unsigned short *)(((int)c + 0x1ac)) += 1;
}

// @symbol func_ov060_021188e8
void func_ov060_021188e8(char* c)
{
    Work* w = (Work*)c;
    int scale;
    (*(u32*)(c + 0x13c)) |= 1;
    scale = (w->timer * 9 << 12) / 14 + 0x1000;
    w->scaleX = scale;
    w->scaleY = scale;
    w->scaleZ = scale;
    if (w->timer == 0x1c)
        func_ov060_021184bc(c);
    (*(u16*)(c + 0x1ac))++;
}

// @symbol func_ov060_02118970
void func_ov060_02118970(char* c)
{
    char* a;
    struct Vector3 v1, v2;
    enum Bool isType;
    unsigned int id;
    id = *(unsigned int*)(c + 0x148);
    if (id == 0) return;
    a = _ZN8dActor_c10FindWithIDEj(id);
    if (a == 0) return;
    isType = (enum Bool)(*(unsigned short*)(a + 0xc) == 0xbf);
    if (!isType) return;
    _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(0xa8, *(int*)(c + 0x5c), *(int*)(c + 0x60), *(int*)(c + 0x64));
    _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(0xa9, *(int*)(c + 0x5c), *(int*)(c + 0x60), *(int*)(c + 0x64));
    _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(0xaa, *(int*)(c + 0x5c), *(int*)(c + 0x60), *(int*)(c + 0x64));
    _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(0xab, *(int*)(c + 0x5c), *(int*)(c + 0x60), *(int*)(c + 0x64));
    _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(0xac, *(int*)(c + 0x5c), *(int*)(c + 0x60), *(int*)(c + 0x64));
    func_02012694(0x2f, c + 0x74);
    v1.x = *(int*)(c + 0x5c);
    v1.y = *(int*)(c + 0x60);
    v1.z = *(int*)(c + 0x64);
    _ZN8dActor_c10EarthquakeERK7Vector35Fix12IiE(c, &v1, 0x7d0000);
    v2.x = *(int*)(c + 0x5c);
    v2.y = *(int*)(c + 0x60);
    v2.z = *(int*)(c + 0x64);
    _ZN6Player4HurtERK7Vector3j5Fix12IiEjjj(a, &v2, 2, 0xc000, 1, 0, 1);
    func_ov060_021184bc(c);
}
}

// @symbol _ZN9daKirai_c16CleanupResourcesEv
int daKirai_c::CleanupResources()
{
    ((SharedFilePtr *)(&data_ov060_0211b1c4))->Release();
    return 1;
}

// @symbol _ZN9daKirai_c6RenderEv
int daKirai_c::Render()
{
    if (mStateIndex != 0) return 1;
    if (mOpacity < 8) return 1;
    ((Sub*)((unsigned char*)&mModel))->m(0);
    return 1;
}

// @symbol _ZN9daKirai_c8BehaviorEv
int daKirai_c::Behavior()
{
  int idx = mStateIndex;
  char* ent = (char*)&data_ov060_0211b1d8[idx*2];
  int adj = *(int*)(ent+4);
  char* self = ((char*)this) + (adj>>1);
  void* fn;
  if(adj&1){ void* vt=*(void**)self; fn=*(void**)((char*)vt + *(int*)ent); }
  else fn=*(void**)ent;
  ((void(*)(char*))fn)(self);
  func_ov060_02118690(((char*)this));
  _ZN5dCc_c5ClearEv((char*)&mdCcAcPos_c);
  struct V3 v;
  v.x = 0;
  v.y = -0x96000;
  v.z = 0;
  _ZN10dCcAcPos_c21SetPosRelativeToActorERK7Vector3(((char*)this)+0x124, &v);
  _ZN5dCc_c6UpdateEv((char*)&mdCcAcPos_c);
  return 1;
}

// @symbol _ZN9daKirai_c13InitResourcesEv
int daKirai_c::InitResources()
{
    Vector3 v;
    Vector3 z;
    void *file;
    int *p178;
    int t;

    file = _ZN5Model8LoadFileER13SharedFilePtr(&data_ov060_0211b1c4);
    _ZN9ModelBase7SetFileEP8BMD_Fileii(((char *)this) + 0xd4, file, 1, -1);
    v.x = 0;
    v.y = -0x96000;
    v.z = 0;
    _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj(
        ((char *)this) + 0x124, ((char *)this), v, 0x96000, 0x12c000, 0x204004, 0);
    mScaleX = 0x1000;
    mScaleY = 0x1000;
    mScaleZ = 0x1000;
    mOpacity = 0xff;
    z.x = 0;
    z.y = 0;
    z.z = 0;
    Vec3_HorzAngle(&z, (const Vector3 *)((char *)&mPosX));
    p178 = (int *)((char *)&mHomePosY);
    mHomeYOffset = 0x2ee000;
    t = mPosX;
    /* materialize r0 = ((char *)this)+0x5c between load and store */
    {
        Vector3 *pos = (Vector3 *)((char *)&mPosX);
        (void)pos;
    }
    mHomePosX = t;
    mHomePosY = mPosY;
    mHomePosZ = mPosZ;
    *p178 = *p178 + (mHomeYOffset >> 3);
    mHomeHorzDist = Vec3_HorzLen((const Vector3 *)((char *)&mPosX));
    mStateIndex = 0;
    mSlotIndex = AddSpikeBomb(((char *)this));
    return 1;
}
