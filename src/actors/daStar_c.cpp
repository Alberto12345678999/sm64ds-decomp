//cpp
/* daStar_c / daStarBase_c -- the Power Star, the silver star, and the marker
 * that spawns one.
 *
 * ROM evidence: _ZTS8daStar_c at ov002:0x0210aa00, _ZTI8daStar_c at
 * 0x0210aa24, base word _ZTI12dEnemyBase_c at 0x021081c0.
 * _ZTS12daStarBase_c at 0x0210aa30, _ZTI12daStarBase_c at 0x0210aa18,
 * base word _ZTI8dActor_c at 0x0208e390. The run is 0x020e6c40..0x020ebe5c.
 *
 * daStar_c's out-of-line destructor is the key function. Under
 * `#pragma defer_codegen off` it emits D1 at 0x020e6c40 and D0 at
 * 0x020e6c90, then a D2 the cartridge does not keep. daStarBase_c's
 * destructor is inline; the odr-use at the end of this file emits D1 at
 * 0x020e6cf4 then D0 at 0x020e6d34. That odr-use is not in the ROM.
 * defer_codegen stays on for the rest, so those bodies are written in
 * reverse source order and come out in ROM order. Do not reorder.
 *
 * Leftover: func_ov002_020e9d18 keeps the masked
 * `(((int)c + 0x4a2) & ~0ULL)` stores. A plain halfword store there loses
 * the address rematerialization. func_ov002_020e8398 loads that halfword
 * volatile: opt_common_subs off cannot be bracketed without poisoning the
 * neighbours, and opt_strength_reduction off does not change the
 * multiplies. func_ov002_020e8244 stays free. Its first parameter is the
 * output vector, not the star. Fix12-by-value callees stay mangled names.
 * The address is the method name.
 *
 */

#include "daStar_c.h"
#include "daStarBase_c.h"
#include "types.h"
#include "common.h"
#include "dBgCh_Lin.h"
#include "dBgCh_Gnd.h"
#include "decl_Animation.h"
#include "decl_dBgCh_Actr.h"
#include "decl_Actor.h"
#include "Player.h"
#include "SharedFilePtr.h"

/* Local shadow declarations carried from the legacy files verbatim.
 * NOT reconciled against real project headers -- check include/*.h for
 * each of these before compiling; a real header should usually win. */
/* shadow struct 'BCA_File' */
struct BCA_File;

/* shadow struct 'Vec3' */
struct Vec3 { int x, y, z; };

/* shadow typedef 'Sub' */
typedef struct SubSt {
    unsigned char _pad[0x96];
    u16 state;      /* 0x96 */
    unsigned char _pad2;
    s8 flag;        /* 0x99 */
} SubSt;

/* shadow struct 'Self' */
struct Self {
    char pad[0x5c];
    int x, y, z; // 0x5c,0x60,0x64
};

/* shadow struct 'Callback' */
struct Callback;

/* shadow typedef 's64' */
typedef long long s64;

/* shadow struct 'Obj' */
struct Obj {
    char pad5c[0x5c];
    int f5c;
    int f60;
    int f64;
    char pad68[0x4b4 - 0x68];
    void *f4b4;
};

/* shadow namespace 'Particle' */
namespace Particle {
struct Callback;
struct System {
    static System *New(unsigned int a, unsigned int b, int c, int d, int e,
                       const Vector3 *p, Callback *cb);
};
/* Signature deliberately copied from the local declaration above: the
   ROM name carries by-value class parameters (e.g. Fix12<int>), which
   mwccarm passes differently at the call site, so declaring the true
   types breaks the byte match. See notes/mwccarm-codegen.md 6az. */
extern "C" System * _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(unsigned int a, unsigned int b, int c, int d, int e, const Vector3 *p, Callback *cb);

}

/* shadow struct 'M48' */
struct M48 { int w[12]; };

/* shadow struct 'V3' */
struct V3 { int x, y, z; };

/* shadow struct 'dExtShadowModel_c' */
struct dExtShadowModel_c;

/* shadow struct 'Matrix4x3' */
struct Matrix4x3;

/* shadow struct 'Bits' */
struct Bits {
    u16 b0 : 1;
    u16 b1 : 1;
    u16 b2 : 1;
};

/* shadow typedef 'u64' */
typedef unsigned long long u64;

/* shadow typedef 'ObjB' (renamed: two other shards spell incompatible 'Obj'
 * layouts; this table shape serves func_ov002_020e9af4 only) */
typedef struct ObjB {
    u8 pad0[0x94];
    s16 x94;
    u8 pad1[0x438 - 0x96];
    u8* x438;
    int x43c;
    u8 pad2[0x49b - 0x440];
    u8 x49b;
    u8 pad3[0x4a1 - 0x49c];
    u8 x4a1;
    u16 x4a2;
} ObjB;

/* shadow struct 'BF' */
struct BF { u16 pad : 7; u16 b7 : 1; u16 b8 : 1; u16 b9 : 1; u16 rest : 6; };

/* shadow struct 'Vec1' */
struct Vec1 { s32 a; };

/* shadow struct 'Thing' */
struct Thing { int x; };

/* shadow struct 'Sub' */
struct SubV5 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5(Thing *t);
};

/* shadow typedef 'Mtx' */
typedef struct Mtx { int m[12]; } Mtx;

/* shadow struct 'C' */
struct C { char pad[0x800]; };

/* shadow typedef 'void' */
typedef void (C::*PMF)();

/* shadow struct 'SharedFilePtr' */
/* Resource-handle layout {id, ptr}: the ROM name has no recoverable fields,
 * so shards that read the second word spell this local overlay (legacy
 * daStar_c InitResources proved it byte-identical). */
struct SharedFilePtrRaw { u32 id; void *ptr; };

/* Two-pointer table entry (second word is the file): func_ov002_020e6df8's
 * shard proved this layout byte-identical for data_ov002_02110944. */
struct Anim2 { void *a; void *b; };
extern Anim2 data_ov002_02110944;

/* TUBUILD CONFLICT -- alternate body of struct 'Flags', from the legacy file for func_ov002_020e86ec, NOT applied:
struct Flags { unsigned short b0 : 1, b1 : 1, b2 : 1, b3 : 1, fld : 2; };
*/

/* TUBUILD CONFLICT -- alternate body of struct 'Flags', from the legacy file for func_ov002_020e88a8, NOT applied:
struct Flags { unsigned short b0 : 1, b1 : 1, b2 : 1, b3 : 1, fld : 2; };
*/

/* TUBUILD CONFLICT -- alternate body of typedef 'Vec3', from the legacy file for func_ov002_020e947c, NOT applied:
typedef struct { int x, y, z; } Vec3;
*/

/* TUBUILD CONFLICT -- alternate body of typedef 'Sub', from the legacy file for func_ov002_020e9af4, NOT applied:
typedef struct Sub {
    u8 pad[0x8e];
    s16 x8e;
} Sub;
*/

/* TUBUILD CONFLICT -- alternate body of struct 'Obj', from the legacy file for _ZN8daStar_c6RenderEv, NOT applied:
struct Obj {
    char pad80[0x80];
    Thing arg80;          /* +0x80 (passed by address) *\/
    char padb0[0xb0 - 0x84];
    unsigned int fb0;      /* +0xb0 *\/
    char pad30c[0x30c - 0xb4];
    Sub sub30c;            /* +0x30c *\/
    char pad370[0x370 - 0x310];
    Sub sub370;            /* +0x370 *\/
    char pad4a2[0x4a2 - 0x374];
    unsigned short b0 : 1;  /* +0x4a2 bit 0 *\/
    unsigned short b1 : 1;  /* bit 1 *\/
    unsigned short b2 : 1;  /* bit 2 *\/
};
*/

/* TUBUILD CONFLICT -- alternate body of struct 'Vec3', from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied:
struct Vec3 { s32 x, y, z; };
*/

#define U8(o) (*(u8 *)(t + (o)))
#define S8(o) (*(s8 *)(t + (o)))
#define U16(o) (*(u16 *)(t + (o)))
#define S32(o) (*(s32 *)(t + (o)))
#define LU32(o) (*(u32 *)((int)(t + (o))))
#define LU16(o) (*(u16 *)((int)(t + (o))))

extern "C" {
/* ModelAnim::SetAnim, called with a scalar speed. */
void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *self, void *f, int a, int b, unsigned short d);
extern char data_02082714[];
extern int func_0203d024(struct Vector3*, struct Vector3*);
extern void DeathTable_ClearBit(int);
extern void FUN_0202a130(void);
extern void UnloadSilverStarAndNumber(void);
extern int _ZN8dActor_c11UntrackStarERa(void*, signed char*);
extern char data_ov002_02110934[];
extern void* _ZN8dActor_c15FindWithActorIDEjPS_(unsigned int, void*);
extern void _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj(void *self, void *actor, const void *v, int d, int e, u32 f, u32 g);
extern int Vec3_Dist(void*, void*);
extern unsigned int data_0209b454;
extern void _ZN13SharedFilePtr7ReleaseEv(void *h);
extern int data_ov002_0210da28[];
extern void *_ZN5Model8LoadFileER13SharedFilePtr(void *f);
extern void _ZN8dActor_c11SpawnNumberERK7Vector3jbtPS_(void* self, struct Vector3* pos, unsigned int n, int flag, unsigned short t, void* src);
extern signed char data_0209f310[];
extern "C" signed char NumRedCoins(void);
extern "C" char *_ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as(unsigned int a, unsigned int b, void *pos, void *dir, int e, int f);
extern unsigned char data_0209f2d8;
extern char* _ZN8dActor_c10FindWithIDEj(unsigned int id);
extern char *_ZN8dActor_c13SpawnSoundObjEj(void *thiz, unsigned int id);
extern void func_02035860(void* o, void* src);
extern int RandomIntInternal(int* seed);
extern int data_0209e650;
extern void *data_0209f318;
extern void _ZN6Camera9SetFlag_3Ev(void *cam);
extern unsigned char IsAreaShowing(int idx);
extern short Vec3_HorzAngle(const Vector3* a, const Vector3* b);
extern short data_02082214[];
extern void func_02012694(int a, void* p);
extern void _ZN5dCc_c5ClearEv(char* t);
extern void _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(unsigned int id, int a, int b, int d);
extern int _ZN9Animation8FinishedEv(void* anim);
extern void func_ov002_020e8244(void *out, char *b);
extern "C" void SubVec3(Vector3* a, Vector3* b, Vector3* c);
extern "C" void AddVec3(Vector3* a, Vector3* b, Vector3* c);
extern void Matrix4x3_FromTranslation(void* m, int x, int y, int z);
extern void Matrix4x3_ApplyInPlaceToRotationY(void* mF, s16 angY);
extern void MulMat4x3Mat4x3(void* out, void* a, void* b);
extern void Vec3_LslInPlace(void* v, int sh);
extern struct M48 data_020a0e68;
extern Mtx IDENTITY_MATRIX4X3;
extern int _ZN8dActor_c19DropShadowRadHeightER17dExtShadowModel_cR9Matrix4x35Fix12IiES5_j(char *self, struct dExtShadowModel_c *sm, struct Matrix4x3 *m, int fix, int t, u32 f);
extern void Vec3_Asr(struct Vector3* d, struct Vector3* s, int sh);
extern void Matrix4x3_FromRotationY(void* m, int angle);
extern void _ZN7fBase_c18MarkForDestructionEv(char* c);
extern void _ZN8dActor_c24KillAndTrackInDeathTableEv(char* c);
extern void _ZN5Event8ClearBitEj(unsigned int b);
extern int _ZNK10dBgCh_Actr12TouchesWaterEv(void* c);
extern void _ZN10dBgCh_Actr19StartDetectingWaterEv(void* c);
extern void *_ZN9dBgCh_GndC1Ev(void* r);
extern void _ZN9dBgCh_GndD1Ev(void* r);
extern void _ZN5dBgCh19StartDetectingWaterEv(void* r);
extern void _ZN9dBgCh_Gnd12SetObjAndPosERK7Vector3P8dActor_c(void* r, struct Vector3* p, void* a);
extern int _ZN9dBgCh_Gnd10DetectClsnEv(void* r);
extern int SurfaceInfo_TestFlag0x20(void* p);
extern int data_0209f32c;
extern char* _ZNK10dBgCh_Actr14GetFloorResultEv(void* c);
extern int func_02037e38(void* p);
extern int func_02037e58(void* p);
extern char* _ZN8dActor_c13ClosestPlayerEv(void* self);
extern signed char data_0209f2f8;
extern void SetStarMarker(int i, int v1, int v2);
extern int IsStarCollectedInCurLevel(int starID);
extern int data_0209f40c[];
extern u8 data_0209f208;
extern unsigned char data_0209f264;
int _ZN6Player9IsOnShellEv(void* p);
void func_02012790(int a);
int _ZN6Player17SetNoControlStateEhih(void* p, int a, int b, int d);
void _ZN7Message11PrepareTalkEv(void);
void _ZN5Event6SetBitEj(u32 a);
void GiveVsStars(int idx, int delta);
void CollectStarInCurLevel(int i);
void _ZN8dActor_c17TrackInDeathTableEv(void* a);
int SublevelToLevel(int i);
int _ZN8SaveData13GetCoinRecordEj(u32 i);
s16 NumCoins(void);
void _ZN8SaveData21SetCoinRecordIfHigherEah(int a, u8 b);
void _ZN6Player4HealEi(void* p, int a);
extern u8 data_0209f228;
extern u8 data_0209f2ac;
extern s16 data_0209f358[];
extern u8 data_0209d684;
extern int _ZN5Event6GetBitEj(unsigned int bit);
/* local extern: ROM calls the mangled name with no arg, reusing r0 as `this`. */
extern void _ZN12daStarBase_c7CollectEv(void);
extern int _ZN4cstd4sqrtEy(u64 v);
extern int Vec3_HorzDist(const Vec3* a, const Vec3* b);
extern s16 GetAngleToCamera(int i);
extern u8 *data_0209f344;
extern void _ZN12dEnemyBase_c12UpdateWMClsnER10dBgCh_Actrj(void* c, void* wm, unsigned int n);
extern int _ZNK10dBgCh_Actr8IsOnWallEv(void* wm);
extern short _ZN8dActor_c12ReflectAngleE5Fix12IiES1_s(void* c, Fix12i a, Fix12i b, short ang);
extern int _ZNK10dBgCh_Actr13JustHitGroundEv(void* wm);
extern int _ZNK10dBgCh_Actr10IsOnGroundEv(void* wm);
extern void _ZN5Sound17ChangeMusicVolumeEj5Fix12IiE(u32, int);
extern int _ZN6Player12GetTalkStateEv(void*);
extern void _ZN7Message13DisplaySavingEt(u16);
extern void _ZN7Message7EndTalkEv(void);
extern int func_ov002_020c6e14(void*);
extern u8 data_0209d660;
extern void EndKuppaScript(void);
extern s8 data_0209f310[];
extern "C" signed char data_0209f310[];
extern int NumVsStarsObtained(void);
extern int _Z14ApproachLinearRiii(int *v, int target, int step);
/* Actor overlay for func_ov002_020e7e24 only (its legacy shard typed the
 * object with this local layout; the shared dActor_c header has no obj). */
struct ActorObj {
    char pad[0x49e];
    unsigned char obj; /* 0x49e */
};
/* Bit overlay at +0x4a2 shared by the Star shards (their legacy spellings
 * agree on b0..b3/fld; see the TUBUILD CONFLICT notes for the wording). */
struct Flags { unsigned short b0 : 1, b1 : 1, b2 : 1, b3 : 1, fld : 2; };
extern char data_ov002_0211092c;
extern char data_ov002_0211093c;
extern char data_ov002_02110924[];
extern SharedFilePtrRaw data_ov002_02110964;
extern SharedFilePtr data_ov002_0210d9a8;
struct SubM {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void m(int);
};
extern void _ZN5dCc_c6UpdateEv(void *p);
extern int _ZN12dEnemyBase_c14UpdateYoshiEatER10dBgCh_Actr(char *c, char *clsn);
extern void func_ov002_020d718c(void *p);
extern void _ZN8dActor_c9UpdatePosEP5dCc_c(char *c, void *clsn);
extern void _ZN10dCcAcPos_c21SetPosRelativeToActorERK7Vector3(char *c, const void *v);
extern int data_ov002_0210aa0c[3];
extern PMF data_ov002_021109d8[];
extern int _ZN9ModelBase7SetFileEP8BMD_Fileii(void *self, void *f, int a, int b);
extern int _ZN17dExtShadowModel_c12InitCylinderEv(void *self);
extern int _ZN8dActor_c18GetBitInDeathTableEv(void *self);
extern u8 data_0209f220;
extern s32 data_0209cef0;
extern s32 data_02092138;
extern SharedFilePtrRaw data_ov002_0211094c;
extern SharedFilePtrRaw data_ov002_02110954;
extern SharedFilePtrRaw data_ov002_0211095c;
extern void _ZN9Animation8LoadFileER13SharedFilePtr(void *f);
extern void LoadSilverStarAndNumber(void);
extern void _ZN10dBgCh_Actr4InitEP8dActor_c5Fix12IiES3_P10Vector3_16S5_(
void *self, void *actor, s32 a, s32 b, void *p1, void *p2);
extern void _ZN10dBgCh_Actr13SetLimMovFlagEv(void *self);
extern s32 IsStarCollected(s32 level, s32 idx);
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c15FindWithActorIDEjPS_, from the legacy file for func_ov002_020e7554, NOT applied: extern char* _ZN8dActor_c15FindWithActorIDEjPS_(u32 actorID, char* prev); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c10FindWithIDEj, from the legacy file for func_ov002_020e7554, NOT applied: extern char* _ZN8dActor_c10FindWithIDEj(u32 id); */
/* TUBUILD CONFLICT -- alternate declaration of data_0209b454, from the legacy file for func_ov002_020e763c, NOT applied: extern int data_0209b454; */
/* TUBUILD CONFLICT -- alternate declaration of _ZN6Camera9SetLookAtERK7Vector3, from the legacy file for func_ov002_020e7934, NOT applied: extern void _ZN6Camera9SetLookAtERK7Vector3(void* cam, const Vector3* v); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN6Camera6SetPosERK7Vector3, from the legacy file for func_ov002_020e7934, NOT applied: extern void _ZN6Camera6SetPosERK7Vector3(void* cam, const Vector3* v); */
/* TUBUILD CONFLICT -- alternate declaration of Vec3_Dist, from the legacy file for func_ov002_020e7934, NOT applied: extern int Vec3_Dist(const Vector3* a, const Vector3* b); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE, from the legacy file for func_ov002_020e7fcc, NOT applied: extern u32 _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE( u32 slot, u32 effect, Fix12i x, Fix12i y, Fix12i z, const void* rot, struct Callback* cb); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_, from the legacy file for func_ov002_020e7fcc, NOT applied: extern void _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(u32 effect, Fix12i x, Fix12i y, Fix12i z); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN9Animation8FinishedEv, from the legacy file for func_ov002_020e8098, NOT applied: extern "C" int _ZN9Animation8FinishedEv(void* anim); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e8244, from the legacy file for func_ov002_020e8098, NOT applied: extern "C" void func_ov002_020e8244(Vector3* out, char* self); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE, from the legacy file for func_ov002_020e8098, NOT applied: extern "C" void* _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE( unsigned int a, unsigned int b, int c, int d, int e, const void* f, void* g); */
/* TUBUILD CONFLICT -- alternate declaration of SubVec3, from the legacy file for func_ov002_020e8244, NOT applied: extern void SubVec3(struct V3* a, struct V3* b, struct V3* c); */
/* TUBUILD CONFLICT -- alternate declaration of AddVec3, from the legacy file for func_ov002_020e8244, NOT applied: extern void AddVec3(struct V3* a, struct V3* b, struct V3* c); */
/* TUBUILD CONFLICT -- alternate declaration of data_0209b454, from the legacy file for func_ov002_020e8618, NOT applied: extern int data_0209b454; */
/* TUBUILD CONFLICT -- alternate declaration of _ZN9Animation8FinishedEv, from the legacy file for func_ov002_020e8618, NOT applied: extern int _ZN9Animation8FinishedEv(char* a); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c11UntrackStarERa, from the legacy file for func_ov002_020e8618, NOT applied: extern void _ZN8dActor_c11UntrackStarERa(char* c, signed char* p); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e9448, from the legacy file for func_ov002_020e88a8, NOT applied: extern void func_ov002_020e9448(void* self); */
/* TUBUILD CONFLICT -- alternate declaration of Vec3_Dist, from the legacy file for func_ov002_020e88a8, NOT applied: extern int Vec3_Dist(struct Vector3* a, struct Vector3* b); */
/* TUBUILD CONFLICT -- alternate declaration of Vec3_HorzAngle, from the legacy file for func_ov002_020e88a8, NOT applied: extern short Vec3_HorzAngle(struct Vector3* a, struct Vector3* b); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c10FindWithIDEj, from the legacy file for func_ov002_020e8abc, NOT applied: extern void *_ZN8dActor_c10FindWithIDEj(unsigned int id); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN7fBase_c18MarkForDestructionEv, from the legacy file for func_ov002_020e8abc, NOT applied: extern void _ZN7fBase_c18MarkForDestructionEv(void *self); */
/* TUBUILD CONFLICT -- alternate declaration of func_02035860, from the legacy file for func_ov002_020e8abc, NOT applied: extern void func_02035860(char *o, void *src); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e9464, from the legacy file for func_ov002_020e8abc, NOT applied: extern void func_ov002_020e9464(char *p); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e9448, from the legacy file for func_ov002_020e8abc, NOT applied: extern void func_ov002_020e9448(unsigned char *p); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e9464, from the legacy file for func_ov002_020e8e80, NOT applied: extern void func_ov002_020e9464(char* c); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c10FindWithIDEj, from the legacy file for func_ov002_020e8ef0, NOT applied: void* _ZN8dActor_c10FindWithIDEj(u32 id); */
/* TUBUILD CONFLICT -- alternate declaration of LinkSilverStarAndStarMarker, from the legacy file for func_ov002_020e8ef0, NOT applied: void LinkSilverStarAndStarMarker(void* a, void* b); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN5dCc_c5ClearEv, from the legacy file for func_ov002_020e8ef0, NOT applied: void _ZN5dCc_c5ClearEv(void* c); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e9630, from the legacy file for func_ov002_020e8ef0, NOT applied: int func_ov002_020e9630(char* c); */
/* TUBUILD CONFLICT -- alternate declaration of IsStarCollectedInCurLevel, from the legacy file for func_ov002_020e8ef0, NOT applied: int IsStarCollectedInCurLevel(int i); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e9464, from the legacy file for func_ov002_020e8ef0, NOT applied: void func_ov002_020e9464(char* c); */
/* TUBUILD CONFLICT -- alternate declaration of data_0209f2d8, from the legacy file for func_ov002_020e8ef0, NOT applied: extern u8 data_0209f2d8; */
/* TUBUILD CONFLICT -- alternate declaration of data_0209b454, from the legacy file for func_ov002_020e8ef0, NOT applied: extern u32 data_0209b454; */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c10FindWithIDEj, from the legacy file for func_ov002_020e930c, NOT applied: extern void* _ZN8dActor_c10FindWithIDEj(unsigned int id); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e8ef0, from the legacy file for func_ov002_020e930c, NOT applied: extern int func_ov002_020e8ef0(void* a, void* b); */
/* TUBUILD CONFLICT -- alternate declaration of Vec3_HorzAngle, from the legacy file for func_ov002_020e947c, NOT applied: extern short Vec3_HorzAngle(const Vec3* a, const Vec3* b); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c10FindWithIDEj, from the legacy file for func_ov002_020e9590, NOT applied: extern "C" dActor_c* _ZN8dActor_c10FindWithIDEj(unsigned int id); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c15FindWithActorIDEjPS_, from the legacy file for func_ov002_020e9590, NOT applied: extern "C" dActor_c* _ZN8dActor_c15FindWithActorIDEjPS_(unsigned int actorID, dActor_c* prev); */
/* TUBUILD CONFLICT -- alternate declaration of LinkSilverStarAndStarMarker, from the legacy file for func_ov002_020e9590, NOT applied: extern "C" void LinkSilverStarAndStarMarker(void* a, void* b); */
/* TUBUILD CONFLICT -- alternate declaration of SublevelToLevel, from the legacy file for func_ov002_020e9630, NOT applied: extern int SublevelToLevel(int i); */
/* TUBUILD CONFLICT -- alternate declaration of GiveVsStars, from the legacy file for func_ov002_020e96a0, NOT applied: extern void GiveVsStars(int idx, int delta); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e8244, from the legacy file for func_ov002_020e96a0, NOT applied: extern void func_ov002_020e8244(int *out, char *c); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c11SpawnNumberERK7Vector3jbtPS_, from the legacy file for func_ov002_020e96a0, NOT applied: extern void _ZN8dActor_c11SpawnNumberERK7Vector3jbtPS_(char *c, int *pos, int num, int b, int t, char *p); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c11UntrackStarERa, from the legacy file for func_ov002_020e96a0, NOT applied: extern void _ZN8dActor_c11UntrackStarERa(char *c, signed char *p); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e7e58, from the legacy file for func_ov002_020e96a0, NOT applied: extern void func_ov002_020e7e58(char *c); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN7fBase_c18MarkForDestructionEv, from the legacy file for func_ov002_020e96a0, NOT applied: extern void _ZN7fBase_c18MarkForDestructionEv(char *c); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c24KillAndTrackInDeathTableEv, from the legacy file for func_ov002_020e96a0, NOT applied: extern void _ZN8dActor_c24KillAndTrackInDeathTableEv(char *c); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c10FindWithIDEj, from the legacy file for func_ov002_020e9840, NOT applied: extern void *_ZN8dActor_c10FindWithIDEj(unsigned int id); */
/* TUBUILD CONFLICT -- alternate declaration of func_02012694, from the legacy file for func_ov002_020e9840, NOT applied: extern void func_02012694(unsigned int id, const struct Vector3 *v); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e9448, from the legacy file for func_ov002_020e9840, NOT applied: extern void func_ov002_020e9448(unsigned char *p); */
/* TUBUILD CONFLICT -- alternate declaration of data_0209f2d8, from the legacy file for func_ov002_020e9840, NOT applied: extern u8 data_0209f2d8; */
/* TUBUILD CONFLICT -- alternate declaration of _ZN5Sound17ChangeMusicVolumeEj5Fix12IiE, from the legacy file for func_ov002_020e9d18, NOT applied: extern void _ZN5Sound17ChangeMusicVolumeEj5Fix12IiE(u32 a, int vol); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN9Animation8FinishedEv, from the legacy file for func_ov002_020e9d18, NOT applied: extern int _ZN9Animation8FinishedEv(char *anim); */
/* TUBUILD CONFLICT -- alternate declaration of GiveVsStars, from the legacy file for func_ov002_020e9d18, NOT applied: extern void GiveVsStars(int idx, int n); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e8244, from the legacy file for func_ov002_020e9d18, NOT applied: extern void func_ov002_020e8244(Vec3 *t, char *c); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c11SpawnNumberERK7Vector3jbtPS_, from the legacy file for func_ov002_020e9d18, NOT applied: extern void _ZN8dActor_c11SpawnNumberERK7Vector3jbtPS_(char *self, Vec3 *vec, int n, u32 b, int t, int actor); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e8618, from the legacy file for func_ov002_020e9d18, NOT applied: extern void func_ov002_020e8618(char *c); */
/* TUBUILD CONFLICT -- alternate declaration of func_02012790, from the legacy file for func_ov002_020e9d18, NOT applied: extern void func_02012790(int n); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e9630, from the legacy file for func_ov002_020e9d18, NOT applied: extern int func_ov002_020e9630(char *c); */
/* TUBUILD CONFLICT -- alternate declaration of data_0209f2d8, from the legacy file for func_ov002_020e9d18, NOT applied: extern u8 data_0209f2d8; */
/* TUBUILD CONFLICT -- alternate declaration of data_0209f2d8, from the legacy file for func_ov002_020ea3a4, NOT applied: extern "C" unsigned char data_0209f2d8; */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e8ef0, from the legacy file for func_ov002_020ea410, NOT applied: extern void func_ov002_020e8ef0(void*, u32); */
/* TUBUILD CONFLICT -- alternate declaration of func_02012790, from the legacy file for func_ov002_020ea420, NOT applied: extern void func_02012790(int id); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c11UntrackStarERa, from the legacy file for func_ov002_020ea420, NOT applied: extern void _ZN8dActor_c11UntrackStarERa(char *self, char *p); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e930c, from the legacy file for func_ov002_020ea420, NOT applied: extern void func_ov002_020e930c(char *self); */
/* TUBUILD CONFLICT -- alternate declaration of data_0209b454, from the legacy file for func_ov002_020ea420, NOT applied: extern int data_0209b454; */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e9464, from the legacy file for func_ov002_020ea7ac, NOT applied: extern void func_ov002_020e9464(char *p); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e7d08, from the legacy file for func_ov002_020ea7ac, NOT applied: extern void func_ov002_020e7d08(char *p); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c10FindWithIDEj, from the legacy file for func_ov002_020ea824, NOT applied: extern int _ZN8dActor_c10FindWithIDEj(unsigned int id); */
/* TUBUILD CONFLICT -- alternate declaration of Vec3_HorzDist, from the legacy file for func_ov002_020ea824, NOT applied: extern int Vec3_HorzDist(char* a, char* b); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e9448, from the legacy file for func_ov002_020ea824, NOT applied: extern void func_ov002_020e9448(char* c); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e81e0, from the legacy file for func_ov002_020ea824, NOT applied: extern void func_ov002_020e81e0(char* c); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e7e24, from the legacy file for func_ov002_020ea824, NOT applied: extern void func_ov002_020e7e24(char* c); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e7d08, from the legacy file for func_ov002_020ea824, NOT applied: extern void func_ov002_020e7d08(char* c); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c10FindWithIDEj, from the legacy file for func_ov002_020ea90c, NOT applied: char* _ZN8dActor_c10FindWithIDEj(unsigned int id); */
/* TUBUILD CONFLICT -- alternate declaration of Vec3_HorzDist, from the legacy file for func_ov002_020ea90c, NOT applied: s32 Vec3_HorzDist(const Vector3* a, const Vector3* b); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e81e0, from the legacy file for func_ov002_020ea90c, NOT applied: void func_ov002_020e81e0(char* a0); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e7e24, from the legacy file for func_ov002_020ea90c, NOT applied: void func_ov002_020e7e24(char* a0); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e7d08, from the legacy file for func_ov002_020ea90c, NOT applied: void func_ov002_020e7d08(char* a0); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e947c, from the legacy file for func_ov002_020ea90c, NOT applied: extern "C" void func_ov002_020e947c(char* a0, Vector3 v, int a2); */
/* TUBUILD CONFLICT -- alternate declaration of data_0209b454, from the legacy file for func_ov002_020ea9d0, NOT applied: extern s32 data_0209b454; */
/* TUBUILD CONFLICT -- alternate declaration of data_0209f2f8, from the legacy file for func_ov002_020ea9d0, NOT applied: extern s8 data_0209f2f8; */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e9590, from the legacy file for func_ov002_020ea9d0, NOT applied: extern void func_ov002_020e9590(void *self); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN7fBase_c18MarkForDestructionEv, from the legacy file for func_ov002_020ea9d0, NOT applied: extern void _ZN7fBase_c18MarkForDestructionEv(void *self); */
/* TUBUILD CONFLICT -- alternate declaration of func_02012694, from the legacy file for func_ov002_020ea9d0, NOT applied: extern void func_02012694(u32 id, void *v); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e9448, from the legacy file for func_ov002_020ea9d0, NOT applied: extern void func_ov002_020e9448(void *p); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c10FindWithIDEj, from the legacy file for func_ov002_020ea9d0, NOT applied: extern char *_ZN8dActor_c10FindWithIDEj(u32 id); */
/* TUBUILD CONFLICT -- alternate declaration of Vec3_HorzDist, from the legacy file for func_ov002_020ea9d0, NOT applied: extern s32 Vec3_HorzDist(void *a, void *b); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e947c, from the legacy file for func_ov002_020ea9d0, NOT applied: extern void func_ov002_020e947c(void *c, struct Vector3 *p, s32 n); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e8dd8, from the legacy file for func_ov002_020ea9d0, NOT applied: extern s32 func_ov002_020e8dd8(void *self); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c10FindWithIDEj, from the legacy file for _ZN12daStarBase_c16OnPendingDestroyEv, NOT applied: extern void* _ZN8dActor_c10FindWithIDEj(unsigned int id); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c11UntrackStarERa, from the legacy file for _ZN8daStar_c16CleanupResourcesEv, NOT applied: extern "C" void _ZN8dActor_c11UntrackStarERa(void* self, signed char* star); */
/* TUBUILD CONFLICT -- alternate declaration of Matrix4x3_FromTranslation, from the legacy file for _ZN12daStarBase_c8BehaviorEv, NOT applied: extern void Matrix4x3_FromTranslation(void *m, int x, int y, int z); */
/* TUBUILD CONFLICT -- alternate declaration of Matrix4x3_FromRotationY, from the legacy file for _ZN12daStarBase_c8BehaviorEv, NOT applied: extern void Matrix4x3_FromRotationY(void *m, int ang); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c19DropShadowRadHeightER17dExtShadowModel_cR9Matrix4x35Fix12IiES5_j, from the legacy file for _ZN12daStarBase_c8BehaviorEv, NOT applied: extern void _ZN8dActor_c19DropShadowRadHeightER17dExtShadowModel_cR9Matrix4x35Fix12IiES5_j( */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c10FindWithIDEj, from the legacy file for _ZN12daStarBase_c8BehaviorEv, NOT applied: extern char *_ZN8dActor_c10FindWithIDEj(unsigned int id); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN5dCc_c5ClearEv, from the legacy file for _ZN12daStarBase_c8BehaviorEv, NOT applied: extern void _ZN5dCc_c5ClearEv(void *p); */
/* TUBUILD CONFLICT -- alternate declaration of data_0209f208, from the legacy file for _ZN12daStarBase_c8BehaviorEv, NOT applied: extern unsigned char data_0209f208; */
/* TUBUILD CONFLICT -- alternate declaration of data_0209f344, from the legacy file for _ZN12daStarBase_c8BehaviorEv, NOT applied: extern unsigned char *data_0209f344; */
/* TUBUILD CONFLICT -- alternate declaration of IDENTITY_MATRIX4X3, from the legacy file for _ZN12daStarBase_c8BehaviorEv, NOT applied: extern Mtx IDENTITY_MATRIX4X3; */
/* TUBUILD CONFLICT -- alternate declaration of _ZN5dCc_c5ClearEv, from the legacy file for _ZN8daStar_c8BehaviorEv, NOT applied: extern void _ZN5dCc_c5ClearEv(char *c); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN5dCc_c6UpdateEv, from the legacy file for _ZN8daStar_c8BehaviorEv, NOT applied: extern void _ZN5dCc_c6UpdateEv(char *c); */
/* TUBUILD CONFLICT -- alternate declaration of data_0209b454, from the legacy file for _ZN8daStar_c8BehaviorEv, NOT applied: extern int data_0209b454; */
/* TUBUILD CONFLICT -- alternate declaration of _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj, from the legacy file for _ZN12daStarBase_c13InitResourcesEv, NOT applied: extern void _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj(void *self, void *actor, const void *v, int d, int e, u32 f, u32 g); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as, from the legacy file for _ZN12daStarBase_c13InitResourcesEv, NOT applied: extern void *_ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as(u32 a, u32 b, const void *v, const void *v16, int e, int f); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN5Model8LoadFileER13SharedFilePtr, from the legacy file for _ZN12daStarBase_c13InitResourcesEv, NOT applied: extern void *_ZN5Model8LoadFileER13SharedFilePtr(void *fp); */
/* TUBUILD CONFLICT -- alternate declaration of IsStarCollectedInCurLevel, from the legacy file for _ZN12daStarBase_c13InitResourcesEv, NOT applied: extern int IsStarCollectedInCurLevel(u8 x); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN7fBase_c18MarkForDestructionEv, from the legacy file for _ZN12daStarBase_c13InitResourcesEv, NOT applied: extern void _ZN7fBase_c18MarkForDestructionEv(void *self); */
/* TUBUILD CONFLICT -- alternate declaration of data_ov002_0210d9a8, from the legacy file for _ZN12daStarBase_c13InitResourcesEv, NOT applied: extern char data_ov002_0210d9a8; */
/* TUBUILD CONFLICT -- alternate declaration of data_ov002_0211092c, from the legacy file for _ZN12daStarBase_c13InitResourcesEv, NOT applied: extern SharedFilePtr data_ov002_0211092c; */
/* TUBUILD CONFLICT -- alternate declaration of data_0209f2d8, from the legacy file for _ZN12daStarBase_c13InitResourcesEv, NOT applied: extern u8 data_0209f2d8; */
/* TUBUILD CONFLICT -- alternate declaration of data_0209f2f8, from the legacy file for _ZN12daStarBase_c13InitResourcesEv, NOT applied: extern s8 data_0209f2f8; */
/* TUBUILD CONFLICT -- alternate declaration of data_0209f2d8, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern u8 data_0209f2d8; */
/* TUBUILD CONFLICT -- alternate declaration of data_0209f2f8, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern s8 data_0209f2f8; */
/* TUBUILD CONFLICT -- alternate declaration of data_ov002_0210aa0c, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern struct Vec3 data_ov002_0210aa0c; */
/* TUBUILD CONFLICT -- alternate declaration of data_ov002_02110924, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern struct SharedFilePtr data_ov002_02110924; */
/* TUBUILD CONFLICT -- alternate declaration of data_ov002_02110934, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern struct SharedFilePtr data_ov002_02110934; */
/* TUBUILD CONFLICT -- alternate declaration of data_ov002_02110944, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern struct SharedFilePtr data_ov002_02110944; */
/* TUBUILD CONFLICT -- alternate declaration of data_ov002_02110964, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern struct SharedFilePtr data_ov002_02110964; */
/* TUBUILD CONFLICT -- alternate declaration of _ZN9ModelBase7SetFileEP8BMD_Fileii, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern s32 _ZN9ModelBase7SetFileEP8BMD_Fileii(void *self, void *f, s32 a, s32 b); */
/* TUBUILD CONFLICT -- alternate declaration of SublevelToLevel, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern s32 SublevelToLevel(s32 sub); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *self, void *f, s32 a, s32 spd, u32 g); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN17dExtShadowModel_c12InitCylinderEv, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern s32 _ZN17dExtShadowModel_c12InitCylinderEv(void *self); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern void _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj( */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern char *_ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as( */
/* TUBUILD CONFLICT -- alternate declaration of NumVsStarsObtained, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern s32 NumVsStarsObtained(void); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e9448, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern void func_ov002_020e9448(void *self); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN10dBgCh_Actr19StartDetectingWaterEv, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern void _ZN10dBgCh_Actr19StartDetectingWaterEv(void *self); */
/* TUBUILD CONFLICT -- alternate declaration of IsStarCollectedInCurLevel, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern s32 IsStarCollectedInCurLevel(u32 idx); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN7fBase_c18MarkForDestructionEv, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern void _ZN7fBase_c18MarkForDestructionEv(void *self); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e8dd8, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern void func_ov002_020e8dd8(void *self); */
/* TUBUILD CONFLICT -- alternate declaration of func_ov002_020e7d08, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern void func_ov002_020e7d08(void *self); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN5Event8ClearBitEj, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern void _ZN5Event8ClearBitEj(u32 bit); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c10FindWithIDEj, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern char *_ZN8dActor_c10FindWithIDEj(u32 id); */
/* TUBUILD CONFLICT -- alternate declaration of LinkSilverStarAndStarMarker, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern void LinkSilverStarAndStarMarker(void *a, void *b); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c18GetBitInDeathTableEv, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern s32 _ZN8dActor_c18GetBitInDeathTableEv(void *self); */
/* TUBUILD CONFLICT -- alternate declaration of _ZN8dActor_c24KillAndTrackInDeathTableEv, from the legacy file for _ZN8daStar_c13InitResourcesEv, NOT applied: extern void _ZN8dActor_c24KillAndTrackInDeathTableEv(void *self); */
}

/* The two destructor bodies are defined first so their D1/D0 groups lead the
 * object in ROM order. Under defer_codegen off each out-of-line destructor
 * emits its D1, D0 and a homeless D2 at the definition. With the deferred
 * queue still empty here both groups land before every deferred function;
 * placed later, the second class's group instead rides the deferred flush and
 * ends the object. (daKpa_c.cpp precedent.) */
#pragma defer_codegen off

/* -------------------------------------------------------------------------- */
/* ROM ordinals 0-1 -- _ZN8daStar_cD1Ev, 0x020e6c40 / _ZN8daStar_cD0Ev, 0x020e6c90 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_cD1Ev
// @symbol _ZN8daStar_cD0Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * One vtable store and 6 destructor calls, every one a consequence of
 * `struct daStar_c : dEnemyBase_c` and the members that declaration now types:
 * its own vptr, then dExtShadowModel_c (0x3d4), ModelAnim (0x370), ModelAnim (0x30c),
 * dBgCh_Actr (0x150),
 * dCcAcPos_c (0x110)
 * in reverse declaration order, then dEnemyBase_c::~dEnemyBase_c.
 *
 * This body is the evidence for the header. It was the hand-written C that
 * named those offsets in the first place, and `daStar_c_classInit_STAR` constructs the
 * same types at the same offsets.
 *
 * D0 is the DELETING destructor: destroy through this class and its bases, then
 * return the object to its heap. Nobody writes that; declaring `~daStar_c()`
 * is enough, because mwcc emits D2, D0 and D1 together and objisolate keeps the
 * one this file is bound to. The deallocation is an inline operator delete --
 * dEnemyBase_c's, reached because dEnemyBase_c is this class's IMMEDIATE base.
 */
#ifdef _MSC_VER
/* THE HOST NEEDS THE ROM'S FLAT D0 NAME, AND MSVC NEVER EMITS IT. MSVC
 * folds the Itanium destructor variants into the one ~daStar_c() it emits,
 * so compiling the definition below as well would define that symbol twice.
 * This arm spells out, in terms of it, what the deleting destructor this
 * file is enrolled for does: the D1 body, called qualified so it is a direct
 * call even where a header declares the destructor virtual, then the
 * class-specific operator delete. Nothing here reaches mwccarm: it builds
 * the `#else` arm and emits the ROM bytes it always emitted, and the object
 * is byte-identical either way. */
extern "C" daStar_c *_ZN8daStar_cD0Ev(daStar_c *thiz)
{
    thiz->daStar_c::~daStar_c();     /* the D1 body, through the one host symbol */
    daStar_c::operator delete(thiz);  /* the class-specific delete D0 ends with */
    return thiz;
}
#else
daStar_c::~daStar_c()
{
}
#endif

#pragma defer_codegen on

/* -------------------------------------------------------------------------- */
/* ROM ordinal 76 -- _ZN8daStar_c13InitResourcesEv, 0x020eb63c, size 0x820 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c13InitResourcesEv
/* recovered: named members + shared header, real C++ method */
s32 daStar_c::InitResources()
{
    char *t = (char *)((void *)this);
    s32 ret;
    s32 b;
    u32 p;
    u32 k;
    s32 kind;
    char *sp;
    s32 *q;
    struct Vec3 v;
    struct Vec3 v2;

    ret = 1;
    U16(0x4a2) = 0;
    U8(0x49c) = 0;
    U16(0x496) = 0xffff;
    U8(0x499) = (u8)S8(0xcc);
    S8(0x498) = -1;
    S32(0x80) = 0x1000;
    S32(0x84) = 0x1000;
    S32(0x88) = 0x1000;
    S32(0x434) = 0;
    S32(0x430) = 0;
    S32(0x4c0) = 0;
    S32(0x4bc) = S32(0x4c0);
    S32(0x4b8) = S32(0x4bc);
    S32(0x4b4) = S32(0x4b8);
    U16(0x492) = 0;
    U16(0x490) = 0;
    U8(0x49e) = 0xff;
    S32(0x478) = S32(0x5c);
    S32(0x47c) = S32(0x60);
    S32(0x480) = S32(0x64);
    U8(0x4a1) = 0;
    _ZN9Animation8LoadFileER13SharedFilePtr(&data_ov002_02110944);
    _ZN9Animation8LoadFileER13SharedFilePtr(&data_ov002_02110924);
    _ZN9Animation8LoadFileER13SharedFilePtr(&data_ov002_02110964);
    _ZN9Animation8LoadFileER13SharedFilePtr(&data_ov002_02110934);

    b = (s32)(*(u16 *)(t + 0xc) == 0xb2);
    if (b != 0) {
        if (_ZN9ModelBase7SetFileEP8BMD_Fileii(t + 0x30c, data_ov002_0211094c.ptr, 1, 1) == 0 ||
            _ZN9ModelBase7SetFileEP8BMD_Fileii(t + 0x370, data_ov002_0211095c.ptr, 1, 0x18) == 0)
            ret = 0;
    } else {
        LoadSilverStarAndNumber();
        if (_ZN9ModelBase7SetFileEP8BMD_Fileii(t + 0x30c, data_ov002_02110954.ptr, 1, 1) == 0 ||
            _ZN9ModelBase7SetFileEP8BMD_Fileii(t + 0x370, data_ov002_02110954.ptr, 1, 1) == 0)
            ret = 0;
    }

    p = *(u32 *)(t + 8);
    k = p & 0x7f;
    if (k == 0x7f) {
        ((daStar_c *)(t))->func_ov002_020e6edc();
        return ret;
    }
    if (k == 0x6f) {
        ((daStar_c *)(t))->func_ov002_020e6df8();
        return ret;
    }
    S32(0x43c) = (s32)((p >> 4) & 0xf);

    b = (s32)(*(u16 *)(t + 0xc) == 0xb2);
    if (b != 0) {
        if (data_0209f220 == (*(u32 *)(t + 8) & 0xf) || SublevelToLevel(data_0209f2f8) > 0xe)
            U8(0x49a) = 2;
        else
            U8(0x49a) = 0;
        if (S32(0x43c) == 6) {
            LoadSilverStarAndNumber();
            LU32(0xb0) |= 0x4000000;
        }
    } else {
        U8(0x49a) = 1;
    }

    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(t + 0x30c, data_ov002_02110964.ptr, 0x40000000, 0x1000, 0);
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(t + 0x370, data_ov002_02110964.ptr, 0x40000000, 0x1000, 0);
    if (_ZN17dExtShadowModel_c12InitCylinderEv(t + 0x3d4) == 0)
        return 0;

    v2.x = data_ov002_0210aa0c[0];
    v2.y = data_ov002_0210aa0c[1];
    v2.z = data_ov002_0210aa0c[2];
    _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj(
        t + 0x110, t, &v2, 0x64000, 0x96000, 0x100002, 0x8000);
    _ZN10dBgCh_Actr4InitEP8dActor_c5Fix12IiES3_P10Vector3_16S5_(t + 0x150, t, 0x50000, 0, 0, 0);
    _ZN10dBgCh_Actr13SetLimMovFlagEv(t + 0x150);
    U8(0x49d) = (u8)(*(u32 *)(t + 8) & 0xf);
    if (S32(0x43c) != 7 && S32(0x43c) != 3)
        LU16(0x4a2) |= 2;

    kind = S32(0x43c);
    if (kind == 0 || (u32)(kind - 5) <= 2) {
        S32(0x440) = 4;
        if (S32(0x43c) != 6) {
            b = (s32)(*(u16 *)(t + 0xc) == 0xb3);
            if (b != 0) {
                S32(0x9c) = -0x2000;
                S32(0xa0) = -0x28000;
            }
        } else {
            v.x = S32(0x5c);
            v.y = S32(0x60);
            v.z = S32(0x64);
            v.y = v.y + 0xa000;
            sp = _ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as(0xb4, 0x40, &v, 0, S8(0x499), -1);
            if (sp != 0) {
                S32(0x434) = *(s32 *)(sp + 4);
            } else {
                return 0;
            }
            if (NumVsStarsObtained() == 5) {
                S32(0x80) = 0x1000;
                S32(0x84) = 0x1000;
                S32(0x88) = 0x1000;
            } else {
                S32(0x80) = 0;
                S32(0x84) = 0;
                S32(0x88) = 0;
            }
        }
        if (S32(0x43c) != 0)
            LU32(0x128) |= 1;
    } else if (kind == 1) {
        S32(0x440) = 8;
        S32(0xa8) = 0x20000;
        ((daStar_c *)(t))->func_ov002_020e9448();
        U16(0x100) = 0xf;
        U16(0x494) = 0x32;
        _ZN10dBgCh_Actr19StartDetectingWaterEv(t + 0x150);
    } else if (kind == 2 || kind == 4) {
        S32(0x440) = 0;
        LU32(0x128) |= 1;
    } else {
        S32(0x440) = 9;
        LU16(0x4a2) |= 8;
        LU32(0x128) |= 1;
        if (U8(0x49a) != 1)
            U8(0x49a) = 2;
    }

    S32(0x444) = S32(0x440);
    S32(0x448) = S32(0x5c);
    S32(0x44c) = S32(0x60);
    S32(0x450) = S32(0x64);
    q = (s32 *)((int)(t + 0x448));
    S32(0x454) = q[0];
    S32(0x458) = q[1];
    S32(0x45c) = q[2];
    S32(0x484) = data_02092138;
    if ((((u32)(U16(0x4a2) << 30)) >> 31) == 0)
        LU32(0x128) |= 1;

    if (U8(0x49d) < 8 && S32(0x43c) != 5 && S32(0x43c) != 3 &&
        (s32)(data_0209f2d8 == 1) == 0 && IsStarCollectedInCurLevel(U8(0x49d)) != 0) {
        if (SublevelToLevel(data_0209f2f8) == 0x1d) {
            _ZN7fBase_c18MarkForDestructionEv(t);
            return 0;
        }
        LU16(0x4a2) |= 4;
    }

    if (S32(0x43c) == 0 || S32(0x43c) == 5 || S32(0x43c) == 7 || S32(0x43c) == 1)
        ((daStar_c *)((unsigned char *)t))->func_ov002_020e8dd8();
    ((daStar_c *)(t))->func_ov002_020e7d08();
    if (data_0209cef0 == 0) {
        _ZN5Event8ClearBitEj(0x1e);
        _ZN5Event8ClearBitEj(0x1d);
        if (S32(0x43c) != 3) {
            if ((s32)(data_0209f2d8 == 1) != 0 || (s32)(*(u16 *)(t + 0xc) == 0xb3) != 0) {
                sp = _ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as(
                    0xb4, 0x50, (struct Vec3 *)(t + 0x5c), 0, S8(0x499), -1);
                if (sp != 0) {
                    S32(0x434) = *(s32 *)(sp + 4);
                } else {
                    return 0;
                }
            }
        }
    }

    sp = _ZN8dActor_c10FindWithIDEj((u32)S32(0x434));
    if (sp != 0)
        ((daStarBase_c *)(sp))->LinkSilverStarAndStarMarker(t);
    if (data_0209f2f8 == 8 && U8(0x49d) == 7) {
        if (IsStarCollected(SublevelToLevel(8), 1) == 0 || data_0209f220 == 1) {
            _ZN7fBase_c18MarkForDestructionEv(t);
            return ret;
        }
    }
    if (data_0209f2f8 == 7 && U8(0x49d) == 2) {
        if (data_0209f220 == 1 || IsStarCollectedInCurLevel(1) == 0) {
            _ZN7fBase_c18MarkForDestructionEv(t);
            return 0;
        }
    }
    if (_ZN8dActor_c18GetBitInDeathTableEv(t) != 0 && U8(0x49d) == 1 && data_0209f2f8 == 0x2e) {
        _ZN8dActor_c24KillAndTrackInDeathTableEv(t);
        sp = _ZN8dActor_c10FindWithIDEj((u32)S32(0x434));
        if (sp != 0)
            ((daStarBase_c *)(sp))->LinkSilverStarAndStarMarker(0);
    }
    return ret;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 75 -- _ZN12daStarBase_c13InitResourcesEv, 0x020eb204, size 0x438 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN12daStarBase_c13InitResourcesEv
/* recovered: named members + shared header, real C++ method, declarations from a shared header */
/* recovered: named members + shared header, real C++ method */
int daStarBase_c::InitResources()
{
    Vector3 pos;
    Vector3 v0;
    Vector3 v4;
    Vector3 v5;
    u32 raw;
    u8 kind;
    int r3;

    raw = ((u32)param1 >> 4) & 0xf;
    kind = (u8)raw;
    mFlags = 0;
    v0.x = 0;
    v0.y = -0x50000;
    v0.z = 0;
    _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj(((char *)this) + 0xd4, ((char *)this), &v0, 0x50000, 0xa0000, 0x100002, 0x8000);
    dBgCh_Gnd ground;
    ground.StartDetectingWater();

    {
        s32 pyb = mPosY;
        s32 pz = mPosZ;
        s32 px = mPosX;
        s32 pyy = pyb + 0x1e000;
        pos.x = px;
        pos.y = pyy;
        pos.z = pz;
    }
    ground.SetObjAndPos(pos, this);
    if (ground.DetectClsn() != 0)
        mGroundY = ground.clsnY;

    r3 = 0;
    mStarID = (u8)(param1 & 0xf);
    mState = 0;

    if (kind == 6) {
        void *sp;
        sp = _ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as(0xb2, mStarID | 0x60, ((char *)this) + 0x5c, (void *)0, (s8)mAreaId, -1);
        if (sp != 0) {
            u16 *p = (u16 *)(((int)sp + 0x4a2));
            *p = (u16)(*p | 0x80);
        }
        _ZN9ModelBase7SetFileEP8BMD_Fileii(((char *)this) + 0x114, _ZN5Model8LoadFileER13SharedFilePtr(&data_ov002_0211093c), 1, 0x18);
        return 0;
    }

    if (kind == 4) {
        u8 *p;
        mState = 2;
        p = (u8 *)(((int)((char *)this) + 0x1db));
        *p = (u8)(*p | 2);
        v4.x = 0;
        v4.y = -0x50000;
        v4.z = 0;
        _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj(((char *)this) + 0xd4, ((char *)this), &v4, 0x50000, 0xa0000, 0x100004, 0);
        mAppearTimer = 0;
    } else if (kind == 5) {
        mState = 3;
        v5.x = 0;
        v5.y = -0x50000;
        v5.z = 0;
        _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj(((char *)this) + 0xd4, ((char *)this), &v5, 0x50000, 0xa0000, 1, 0);
    } else if (kind & 1) {
        mState = 1;
        if (kind & 2) {
            u8 *p = (u8 *)(((int)((char *)this) + 0x1db));
            *p = (u8)((*p & ~1) | 1);
        }
        {
            u8 *p = (u8 *)(((int)((char *)this) + 0x1db));
            *p = (u8)(*p | 8);
        }
    } else {
        u8 *p = (u8 *)(((int)((char *)this) + 0x1db));
        u8 nv = (u8)((((int)kind >> 1) & 1) ^ 1);
        *p = (u8)((*p & ~2) | ((nv & 1) << 1));
    }

    if (mState != 0) {
        _ZN5Model8LoadFileER13SharedFilePtr(&data_ov002_0210d9a8);
        if (_ZN9ModelBase7SetFileEP8BMD_Fileii(((char *)this) + 0x114, _ZN5Model8LoadFileER13SharedFilePtr(&data_ov002_0211092c), 1, 0x19) == 0) {
            return 0;
        }
    } else {
        if (_ZN9ModelBase7SetFileEP8BMD_Fileii(((char *)this) + 0x114, _ZN5Model8LoadFileER13SharedFilePtr(&data_ov002_0211093c), 1, 0x18) == 0) {
            return 0;
        }
    }

    if (_ZN17dExtShadowModel_c12InitCylinderEv((char *)&mShadowModel) == 0) {
        return 0;
    }

    if (((u32)(mFlags << 0x1e) >> 0x1f) == 0) {
        s32 *p = (s32 *)(((int)((char *)this) + 0xec));
        *p = *p | 1;
    }
    r3 = 0;
    mSpawnPos.x = mPosX;
    mSpawnPos.y = mPosY;
    mSpawnPos.z = mPosZ;
    mSpawnedActorID = r3;
    mSpawnedDeathTableID = -1;
    mHitActor = 0;

    if (data_0209f2d8 == 1)
        r3 = 1;
    if (r3 == 0 && SublevelToLevel((s8)data_0209f2f8) == 0x1d && IsStarCollectedInCurLevel(mStarID) != 0) {
        _ZN7fBase_c18MarkForDestructionEv(((char *)this));
        return 0;
    }
    if (_ZN8dActor_c18GetBitInDeathTableEv(((char *)this)) != 0) {
        _ZN7fBase_c18MarkForDestructionEv(((char *)this));
        return 0;
    }
    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 74 -- _ZN8daStar_c8BehaviorEv, 0x020eb05c, size 0x1a8 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c8BehaviorEv
/* recovered: named members + shared header, real C++ method, declarations from a shared header */
/* recovered: named members + shared header, real C++ method */
int daStar_c::Behavior()
{
    ((daStar_c *)(((char *)this)))->func_ov002_020e700c();
    unk_4a8 = 0;
    unk_4ac = 0;
    unk_4b0 = 0;

    if (_ZN12dEnemyBase_c14UpdateYoshiEatER10dBgCh_Actr(((char *)this), ((char *)this) + 0x150) != 0) {
        int state = unk_440;
        if (state >= 5 && state <= 7 && *(void **)((char *)&mEatingPlayer) != 0) {
            func_ov002_020d718c(*(void **)((char *)&mEatingPlayer));
            mEatingPlayer = 0;
            *(int *)((int)((char *)&mFlags)) &= ~0xe0000;
            ((daStar_c *)(((char *)this)))->func_ov002_020e84ec();
            _ZN5dCc_c5ClearEv((char *)&mdCc_c);
            return 1;
        }
        if ((data_0209b454 & 0x4000000) != 0) {
            if ((int)((mFlags & 0x4000000) != 0) != 0) {
                char *p = *(char **)((char *)&mEatingPlayer);
                if (p != 0)
                    *(int *)((int)(p + 0xb0)) |= 0x4000000;
            }
        }
        ((daStar_c *)(((char *)this)))->func_ov002_020e84ec();
        _ZN5dCc_c5ClearEv((char *)&mdCc_c);
        return 1;
    }

    mEatingPlayer = 0;
    ((daStar_c *)(((char *)this)))->func_ov002_020e763c();
    (((C *)((char *)this))->*data_ov002_021109d8[unk_440])();
    _ZN8dActor_c9UpdatePosEP5dCc_c(((char *)this), 0);
    ((daStar_c *)(((char *)this)))->func_ov002_020e84ec();
    _ZN5dCc_c5ClearEv((char *)&mdCc_c);
    {
        V3 v;
        v.x = data_ov002_0210aa0c[0];
        v.y = data_ov002_0210aa0c[1];
        v.z = data_ov002_0210aa0c[2];
        _ZN10dCcAcPos_c21SetPosRelativeToActorERK7Vector3(((char *)this) + 0x110, &v);
    }
    if (unk_49f == 0)
        _ZN5dCc_c6UpdateEv((char *)&mdCc_c);
    ((daStar_c *)(((char *)this)))->func_ov002_020e7eb8();
    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 73 -- _ZN12daStarBase_c8BehaviorEv, 0x020ead90, size 0x2cc */
/* -------------------------------------------------------------------------- */
// @symbol _ZN12daStarBase_c8BehaviorEv
/* recovered: named members + shared header, real C++ method */
/* The class header comes FIRST on purpose: it reaches math/Matrix.h, whose
   Matrix4x3 is the structured one, and include/common.h's flat spelling stands
   down behind the guard. mat4x3.t is only nameable this way round, and the two
   spellings are the same 0x30 bytes. */
/* recovered: declarations from a shared header */
int daStarBase_c::Behavior()
{
    if ((unsigned int)(mFlags << 0x1c) >> 0x1f) {
        if (mStarID == data_0209f344[data_0209f208]) {
            mAppearTimer = 0;
            if (((unsigned int)(mFlags << 0x1f) >> 0x1f) == 0) {
                *(unsigned char *)((((int)((char *)this)) + 0x1db)) |= 2;
                *(int *)((((int)((char *)this)) + 0xec)) &= ~1;
            }
        } else {
            mAppearTimer = 0x2a;
        }
        *(unsigned char *)((((int)((char *)this)) + 0x1db)) &= ~8;
    }
    if (mState != 0) {
        if (mAppearTimer != 0) {
            if (((unsigned int)(mFlags << 0x1e) >> 0x1f) == 0) {
                if (mStarID == data_0209f344[data_0209f208]) {
                    *(unsigned short *)((((int)((char *)this)) + 0x1d4)) -= 1;
                    if (mAppearTimer == 0) {
                        if (((unsigned int)(mFlags << 0x1f) >> 0x1f) == 0) {
                            *(unsigned char *)((((int)((char *)this)) + 0x1db)) |= 2;
                            *(int *)((((int)((char *)this)) + 0xec)) &= ~1;
                        }
                    }
                }
            }
        }
        Matrix4x3_FromTranslation(((char *)this) + 0x130, mPosX >> 3, mPosY >> 3,
                                  mPosZ >> 3);
    } else {
        *(short *)((((int)((char *)this)) + 0x8e)) += 0x400;
        Matrix4x3_FromRotationY(((char *)this) + 0x130, mAngleY);
        mModel.mat4x3.t.x = mPosX >> 3;
        mModel.mat4x3.t.y = mPosY >> 3;
        mModel.mat4x3.t.z = mPosZ >> 3;
    }
    if ((unsigned int)(mFlags << 0x1e) >> 0x1f) {
        *(Mtx *)((char *)&mShadowMtx) = IDENTITY_MATRIX4X3;
        mShadowMtx.t.x = mPosX >> 3;
        mShadowMtx.t.y = mPosY >> 3;
        mShadowMtx.t.z = mPosZ >> 3;
        {
            int d = mPosY - mGroundY;
            int rad = 0xa0000;
            if (mState != 0)
                rad = 0xc8000;
            _ZN8dActor_c19DropShadowRadHeightER17dExtShadowModel_cR9Matrix4x35Fix12IiES5_j(
                ((char *)this), (struct dExtShadowModel_c *)(((char *)this) + 0x164), (struct Matrix4x3 *)(((char *)this) + 0x18c), rad, d + 0x28000, 0xf);
        }
    }
    if (mState != 0) {
        if ((unsigned int)(mFlags << 0x1e) >> 0x1f) {
            /* Both are fields of the dCcAcPos_c at 0x0d4, which the cartridge's own
               ~daStarBase_c names (tools/dtor_members.py): 0x0f8 is +0x24,
               dCc_c::otherOwner, and 0x0f4 is +0x20, dCc_c::hitFlags. */
            if (mState != 2 && mdCcAcPos_c.otherOwner != 0) {
                char *a = _ZN8dActor_c10FindWithIDEj(mdCcAcPos_c.otherOwner);
                if (a != 0) {
                    if ((mdCcAcPos_c.hitFlags & 0x408000) != 0) {
                        mHitActor = (dActor_c *)a;
                        Collect();
                        return 1;
                    }
                }
            }
            _ZN5dCc_c5ClearEv((char *)&mdCcAcPos_c);
            _ZN5dCc_c6UpdateEv((char *)&mdCcAcPos_c);
        }
    }
    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 72 -- _ZN8daStar_c6RenderEv, 0x020eacf4, size 0x9c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c6RenderEv
/* recovered: named members + shared header, real C++ method */
/* Actor overlay for this method only (the file-scope 'Obj' names cover
 * incompatible layouts elsewhere): arg80/fb0/bitfields plus the two
 * SubV5 state slots whose m5 runs the landing-dust callback. */
struct ObjC {
    char pad80[0x80];
    Thing arg80;          /* +0x80 (passed by address) */
    char padb0[0xb0 - 0x84];
    unsigned int fb0;      /* +0xb0 */
    char pad30c[0x30c - 0xb4];
    SubV5 sub30c;            /* +0x30c */
    char pad370[0x370 - 0x310];
    SubV5 sub370;            /* +0x370 */
    char pad4a2[0x4a2 - 0x374];
    unsigned short b0 : 1;  /* +0x4a2 bit 0 */
    unsigned short b1 : 1;  /* bit 1 */
    unsigned short b2 : 1;  /* bit 2 */
};
int daStar_c::Render()
{
    int locked;
    if (((ObjC *)this)->arg80.x == 0) goto done;
    locked = (((ObjC *)this)->fb0 & 0x40000) != 0;
    if (locked) goto done;
    if (((ObjC *)this)->b1) goto callit;
done:
    return 1;
callit:
    if (!((ObjC *)this)->b2)
        ((ObjC *)this)->sub30c.m5(&((ObjC *)this)->arg80);
    else
        ((ObjC *)this)->sub370.m5(&((ObjC *)this)->arg80);
    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 71 -- _ZN12daStarBase_c6RenderEv, 0x020eacb8, size 0x3c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN12daStarBase_c6RenderEv
/* recovered: named members + shared header, real C++ method */
int daStarBase_c::Render()
{
    unsigned int b = mFlags;
    if ((b << 30) >> 31) {
        ((SubM *)((char *)&mModel))->m(0);
    }
    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 70 -- _ZN8daStar_c16CleanupResourcesEv, 0x020eac18, size 0xa0 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c16CleanupResourcesEv
/* recovered: named members + shared header, real C++ method, declarations from a shared header */
/* recovered: named members + shared header, real C++ method */
int daStar_c::CleanupResources()
{
    int b = (actorID == 0xb2);
    if (b) {
        int v = unk_43c;
        if (v != 8) {
            if (v == 6)
                UnloadSilverStarAndNumber();
            _ZN8dActor_c11UntrackStarERa(((char*)this), (signed char*)((char*)&unk_498));
        }
    } else {
        _ZN8dActor_c11UntrackStarERa(((char*)this), (signed char*)((char*)&unk_498));
        UnloadSilverStarAndNumber();
    }
    ((SharedFilePtr *)(&data_ov002_02110944))->Release();
    ((SharedFilePtr *)(&data_ov002_02110924))->Release();
    ((SharedFilePtr *)(&data_ov002_02110964))->Release();
    ((SharedFilePtr *)(&data_ov002_02110934))->Release();
    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 69 -- _ZN12daStarBase_c16CleanupResourcesEv, 0x020eabcc, size 0x4c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN12daStarBase_c16CleanupResourcesEv
/* recovered: named members + shared header, real C++ method, declarations from a shared header */
/* recovered: named members + shared header, real C++ method */
int daStarBase_c::CleanupResources()
{
    if (mState != 0) {
        ((SharedFilePtr *)(&data_ov002_0211092c))->Release();
        data_ov002_0210d9a8.Release();
    } else {
        ((SharedFilePtr *)(&data_ov002_0211093c))->Release();
    }
    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 68 -- _ZN12daStarBase_c16OnPendingDestroyEv, 0x020eab8c, size 0x40 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN12daStarBase_c16OnPendingDestroyEv
/* recovered: named members + shared header, real C++ method, declarations from a shared header */
/* recovered: named members + shared header, real C++ method */
void daStarBase_c::OnPendingDestroy()
{
    char* a = (char*)_ZN8dActor_c10FindWithIDEj(mSpawnedActorID);
    if (a == 0) return;
    if (*(short*)(a + 0xce) >= 0) return;
    DeathTable_ClearBit(mSpawnedDeathTableID);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 67 -- func_ov002_020ea9d0, 0x020ea9d0, size 0x1bc */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020ea9d0Ev
/* recovered: shared common types, declarations from a shared header */
/* recovered: shared common types */
void daStar_c::func_ov002_020ea9d0() {
    void * arg0 = (void *)this;
    char *c = (char *)arg0;
    char *other;
    s32 area;
    struct Vector3 *op;
    struct Vector3 v0;
    struct Vector3 v1;
    struct Vector3 v2;
    struct Vector3 v3;

    if (*(u8 *)(c + 0x49d) != 0) {
        ((daStar_c *)(c))->func_ov002_020e9590();
        if (*(s32 *)(c + 0x434) == 0) {
            _ZN7fBase_c18MarkForDestructionEv(c);
            return;
        }
    }
    *(u32 *)((int)(c + 0xb0)) |= 0x4000000;
    data_0209b454 |= 0x4000000;
    *(u16 *)(c + 0x496) = 0;
    func_02012694(0x57, c + 0x74);
    *(s32 *)(c + 0xa8) = 0x20000;
    ((daStar_c *)(c))->func_ov002_020e9448();
    other = _ZN8dActor_c10FindWithIDEj(*(u32 *)(c + 0x434));
    if (*(s32 *)(c + 0x43c) == 4) {
        if (other == 0 || Vec3_HorzDist((const Vec3 *)(c + 0x5c), (const Vec3 *)(other + 0x5c)) == 0) {
            *(s32 *)(c + 0xa8) = 0x18000;
            *(s32 *)(c + 0x440) = 3;
        } else {
            *(s32 *)(c + 0x440) = 2;
            op = (struct Vector3 *)((int)(other + 0x5c));
            *(struct Vec1 *)&v0.x = *(struct Vec1 *)&op->x;
            *(struct Vec1 *)&v0.y = *(struct Vec1 *)&op->y;
            *(struct Vec1 *)&v0.z = *(struct Vec1 *)&op->z;
            v0.y = v0.y + 0xc8000;
            area = data_0209f2f8;
            if (area == 0x11) {
                v1.x = v0.x;
                v1.y = v0.y;
                v1.z = v0.z;
                ((daStar_c *)(c))->func_ov002_020e947c(&v1, 0x64000);
            } else if (area == 0xb && *(u8 *)(c + 0x49d) == 3) {
                v2.x = v0.x;
                v2.y = v0.y;
                v2.z = v0.z;
                ((daStar_c *)(c))->func_ov002_020e947c(&v2, 0x46000);
            } else {
                v3.x = v0.x;
                v3.y = v0.y;
                v3.z = v0.z;
                ((daStar_c *)(c))->func_ov002_020e947c(&v3, 0x190000);
            }
        }
    } else {
        *(s32 *)(c + 0x440) = 1;
    }
    ((daStar_c *)((unsigned char *)c))->func_ov002_020e8dd8();
    ((daStar_c *)(c))->func_ov002_020e7e24();
    ((daStar_c *)(c))->func_ov002_020e7d08();
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 66 -- func_ov002_020ea90c, 0x020ea90c, size 0xc4 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020ea90cEv
void daStar_c::func_ov002_020ea90c() {
    char* self = (char*)this;
    if (*(s32*)(self + 0xa8) <= -0x20000) {
        char* other = _ZN8dActor_c10FindWithIDEj(*(unsigned int*)(self + 0x434));
        if (other == 0 || Vec3_HorzDist((const Vec3 *)(self + 0x5c), (const Vec3 *)(other + 0x5c)) == 0) {
            *(s32*)(self + 0xa8) = 0x18000;
            *(s32*)(self + 0x440) = 3;
        } else {
            Vector3* pp = (Vector3*)(other + 0x5c);
            Vector3 v;
            int yv;
            v.x = pp->x;
            yv = pp->y;
            *(volatile s32*)&v.y = yv;
            v.z = pp->z;
            v.y = yv + 0xc8000;
            /* By-value staging: the ROM caller copies v to its outgoing area
             * and passes the copy's address (r1 = sp+0xc at the bl). The TU
             * cannot spell the shard's by-value declaration (it collides with
             * the pointer form the other callers need), and copying the real
             * Vector3 would emit its declared-destructor cleanup, so the copy
             * is staged word-wise into plain ints -- proven byte-identical
             * in isolation. */
            int w[3];
            w[0] = v.x;
            w[1] = v.y;
            w[2] = v.z;
            ((daStar_c *)(self))->func_ov002_020e947c((Vector3*)w, 0x190000);
            *(s32*)(self + 0x440) = 2;
        }
    }
    ((daStar_c *)(self))->func_ov002_020e81e0();
    ((daStar_c *)(self))->func_ov002_020e7e24();
    ((daStar_c *)(self))->func_ov002_020e7d08();
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 65 -- func_ov002_020ea824, 0x020ea824, size 0xe8 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020ea824Ev
void daStar_c::func_ov002_020ea824() {
    char* c = (char*)this;
    char* o = (char*)_ZN8dActor_c10FindWithIDEj(*(unsigned int*)(c + 0x434));
    if (o == 0) { _ZN7fBase_c18MarkForDestructionEv(c); return; }
    if (Vec3_HorzDist((const Vec3 *)(c + 0x5c), (const Vec3 *)(o + 0x5c)) < *(int*)(c + 0x98)) {
        int* src = (int*)(o + 0x5c);
        int* yp = (int*)(c + 0x60);
        *(int*)(c + 0x5c) = src[0];
        *(int*)(c + 0x60) = src[1];
        *(int*)(c + 0x64) = src[2];
        *yp += 0xc8000;
        *(int*)(c + 0x98) = 0;
        *(int*)(c + 0xa8) = 0x18000;
        if (data_0209f2f8 == 0xb) {
            if (*(unsigned char*)(c + 0x49d) == 3) {
                *(int*)(c + 0xa8) = 0x10000;
                goto skip;
            }
        }
        *(int*)(c + 0xa8) = 0x18000;
    skip:
        ((daStar_c *)(c))->func_ov002_020e9448();
        *(int*)(c + 0x440) = 3;
    }
    ((daStar_c *)(c))->func_ov002_020e81e0();
    ((daStar_c *)(c))->func_ov002_020e7e24();
    ((daStar_c *)(c))->func_ov002_020e7d08();
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 64 -- func_ov002_020ea7ac, 0x020ea7ac, size 0x78 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020ea7acEv
void daStar_c::func_ov002_020ea7ac() {
    char* c = (char*)this;
  if(*(int*)(c+0xa8) <= -0x18000){
    ((daStar_c *)(c))->func_ov002_020e9464();
    *(int*)(((int)c + 0x128)) &= ~1;
  }else{
    if(*(int*)(c+0x9c) == 0){
      *(int*)(c+0x440) = 4;
      *(unsigned short*)(c+0x400+0x96) = 0x1d6;
    }else{
      ((daStar_c *)(c))->func_ov002_020e7e24();
    }
  }
  ((daStar_c *)(c))->func_ov002_020e81e0();
  ((daStar_c *)(c))->func_ov002_020e7d08();
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 63 -- func_ov002_020ea420, 0x020ea420, size 0x38c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020ea420Ev
void daStar_c::func_ov002_020ea420() {
    char * c = (char *)this;
    int spd;
    int spd2;
    int en;
    int lim;
    int step;

    if (*(int *)(c + 0x43c) == 6) {
        en = 0;
        if ((unsigned int)(*(u16 *)(c + 0x4a2) << 24) >> 31 == 0 && NumVsStarsObtained() == 5) {
            lim = 0x14;
            step = 0x100;
            en = 1;
        } else {
            if (((struct BF *)(c + 0x4a2))->b7 != 0 && ((struct BF *)(c + 0x4a2))->b8 != 0) {
                lim = 5;
                step = 0x200;
                en = 1;
            }
        }
        if (en != 0) {
            if (*(int *)(c + 0x80) != 0x1000 && (data_0209b454 & 0x4000000) == 0) {
                *(int *)(c + 0xb0) |= 0x4000000;
                data_0209b454 |= 0x4000000;
            } else if (*(int *)(c + 0x80) == 0x1000) {
                *(u16 *)(c + 0x492) = lim + 0xb;
                *(u16 *)(c + 0x4a2) |= 0x200;
                ((daStar_c *)c)->AddStarMarker();
                *(int *)(c + 0x128) &= ~1;
            }
            if (*(u16 *)(c + 0x492) < (unsigned int)lim) {
                *(u16 *)(c + 0x492) += 1;
                if (*(u16 *)(c + 0x492) == lim) {
                    if (*(u16 *)(c + 0x496) == 0xffff)
                        *(u16 *)(c + 0x496) = 0x64;
                }
            } else if (*(int *)(c + 0x80) != 0x1000) {
                spd = *(int *)(c + 0x80);
                if (*(u16 *)(c + 0x492) >= lim + 0xa) {
                    if (_Z14ApproachLinearRiii(&spd, 0x1000, step) != 0) {
                        ((daStar_c *)c)->AddStarMarker();
                        *(int *)(c + 0x128) &= ~1;
                    }
                } else {
                    *(u16 *)(c + 0x492) += 1;
                }
                {
                    int v = spd;
                    *(int *)(c + 0x80) = v;
                    *(int *)(c + 0x84) = v;
                    *(int *)(c + 0x88) = v;
                }
            } else {
                if ((unsigned int)(*(u16 *)(c + 0x4a2) << 24) >> 31 == 0)
                    *(u16 *)(c + 0x492) = 0x3d;
                else
                    *(u16 *)(c + 0x492) = 0;
            }
            if (*(u16 *)(c + 0x492) >= lim + 0xa &&
                (unsigned int)(*(u16 *)(c + 0x4a2) << 22) >> 31 == 0) {
                *(u16 *)(c + 0x4a2) |= 0x200;
                func_02012790(0x41);
            }
            *(u16 *)(c + 0x100) = 0;
        } else {
            *(int *)(c + 0x128) |= 1;
            if (*(u16 *)(c + 0x492) != 0) {
                *(u16 *)(c + 0x492) -= 1;
            } else if (*(int *)(c + 0x80) != 0) {
                int step2;
                if (*(u16 *)(c + 0x100) == 0)
                    func_02012790(0x42);
                spd2 = *(int *)(c + 0x80);
                if (*(u16 *)((int)(c + 0x100)) <= 0xf) {
                    *(u16 *)((int)(c + 0x100)) += 1;
                    step2 = 0;
                } else {
                    step2 = 0x100;
                }
                if (_Z14ApproachLinearRiii(&spd2, 0, step2) != 0) {
                    *(u16 *)(c + 0x4a2) &= ~0x200;
                    _ZN8dActor_c11UntrackStarERa(c, (signed char *)(c + 0x498));
                }
                {
                    int v2 = spd2;
                    *(int *)(c + 0x80) = v2;
                    *(int *)(c + 0x84) = v2;
                    *(int *)(c + 0x88) = v2;
                }
                if ((data_0209b454 & 0x4000000) == 0) {
                    *(int *)(c + 0xb0) |= 0x4000000;
                    data_0209b454 |= 0x4000000;
                    *(u16 *)(c + 0x496) = 0x64;
                }
            }
        }
    } else {
        int t = *(u16 *)(c + 0xc);
        t = t == 0xb3;
        if (t != false) {
            if (*(int *)(c + 0x60) <= *(int *)(c + 0x458)) {
                *(int *)(c + 0x60) = *(int *)(c + 0x458);
                *(int *)(c + 0xa8) = 0x10000;
            }
        } else {
            ((daStar_c *)(c))->func_ov002_020e7e14();
        }
    }
    ((daStar_c *)(c))->func_ov002_020e930c();
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 62 -- func_ov002_020ea410, 0x020ea410, size 0x10 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020ea410Ev
/* func_ov002_020ea410 @ 0x20ea410 (ov002) -- veneer: ldr r1,[r0,#0x438]; b func_ov002_020e8ef0. */
void daStar_c::func_ov002_020ea410() {
    void* a = (void*)this;
    ((daStar_c *)((char *)a))->func_ov002_020e8ef0((void *)*(u32*)((char*)a + 0x438));
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 61 -- func_ov002_020ea3a4, 0x020ea3a4, size 0x6c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020ea3a4Ev
int daStar_c::func_ov002_020ea3a4() {
    void* a = (void*)this;
  int b = (*(unsigned short*)((char*)a+0xc) == 0xb3);
  if (b != 0) {
    unsigned char idx = *(unsigned char*)((char*)*(void**)((char*)a+0x438)+0x6d8);
    *(int*)((char*)a+0x48c) = data_0209f310[idx] + 0x19;
  } else {
    int b2 = (data_0209f2d8 == 1);
    if (b2 != 0) *(int*)((char*)a+0x48c) = 0x4f;
    else *(int*)((char*)a+0x48c) = 0x22;
  }
  return *(int*)((char*)a+0x48c);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 60 -- func_ov002_020ea100, 0x020ea100, size 0x2a4 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020ea100Ev
#include "types.h"
extern "C" {
extern int _ZN6Player12Unk_020c9e5cEh(void *thisPtr, int state);
extern void _ZN5Sound17ChangeMusicVolumeEj5Fix12IiE(unsigned int a, int fixA);
extern int func_ov002_020ca0f4(void *player);
extern void GiveVsStars(int idx, int delta);

extern char data_ov002_02110924[];
extern unsigned char data_0209f2d8;
extern signed char data_0209f310[];

struct VObj {
    virtual void unk0();
};

/* opt_common_subs OFF was carried here from this shard's legacy file, but the
 * setting is file-global last-wins: left active it silently recompiles every
 * later section of the merged TU (it cost func_ov002_020e7934 its match).
 * Removed; ea100 must prove it still matches without it, or spell the effect
 * out in source (see Bowser func_ov060_02112bfc precedent). */
}

void daStar_c::func_ov002_020ea100() {
    char * c = (char *)this;
    char *common;
    int state;

    common = *(char **)(c + 0x438);
    state = ((daStar_c *)(c))->func_ov002_020e73ac();

    if (_ZN6Player12Unk_020c9e5cEh(common, state)) {
        if (state == 1 || state == 2) {
            ((daStar_c *)(c))->func_ov002_020e6fbc(0x14);
            *(u8 *)(c + 0x49c) = 1;
        } else if (state != 3) {
            ((daStar_c *)(c))->func_ov002_020e6fbc(0);
            *(u8 *)(c + 0x49c) = 2;
        }

        int *posY = (int *)(c + 0x60);

        *(int *)(c + 0x440) = 6;
        *(u16 *)(c + 0x4a2) &= ~4;
        *(u16 *)(c + 0x4a2) |= 2;
        *(u16 *)(c + 0x490) = 0;

        {
            int *src = (int *)(*(int *)(c + 0x438) + 0x5c);
            int *cache = (int *)(c + 0x454);
            *(int *)(c + 0x454) = src[0];
            *(int *)(c + 0x458) = src[1];
            *(int *)(c + 0x45c) = src[2];
            *(int *)(c + 0x5c) = cache[0];
            *(int *)(c + 0x60) = cache[1];
            *(int *)(c + 0x64) = cache[2];
            *posY += 0x1e000;
        }

        *(short *)(c + 0x94) = *(short *)(*(int *)(c + 0x438) + 0x8e);
        *(u16 *)(c + 0x8c) = 0;

        if (*(u8 *)(common + 0x703) != 0) {
            *(int *)(c + 0x80) = 0x3000;
            *(int *)(c + 0x84) = 0x3000;
            *(int *)(c + 0x88) = 0x3000;
        } else {
            *(int *)(c + 0x80) = 0x1000;
            *(int *)(c + 0x84) = 0x1000;
            *(int *)(c + 0x88) = 0x1000;
        }

        ((daStar_c *)(c))->func_ov002_020e9464();

        if (*(u8 *)(common + 0x706) != 0) {
            _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x30c, (void *)*(int *)(data_ov002_02110924 + 4), 0x40000000, 0x1000, 0);
        } else {
            _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x30c, data_ov002_02110944.b, 0x40000000, 0x1000, 0);
        }

        {
            struct VObj *vobj = (struct VObj *)(c + 0x3d4);
            { u16 *_p = (u16 *)(c + 0x4a2); *_p = (*_p & ~1) | 1; }
            vobj->unk0();
        }

        if (*(int *)(c + 0x43c) == 9) {
            _ZN5Sound17ChangeMusicVolumeEj5Fix12IiE(0, 0x7f000);
        }
    } else {
        if (func_ov002_020ca0f4(common) != 0) {
            int *posY2 = (int *)(c + 0x60);
            int *s = (int *)(*(int *)(c + 0x438) + 0x5c);
            *(int *)(c + 0x5c) = s[0];
            *(int *)(c + 0x60) = s[1];
            *(int *)(c + 0x64) = s[2];
            *posY2 += 0xc8000;
        } else {
            int ok = (data_0209f2d8 == 1);
            if (ok) {
                unsigned char idx = *(u8 *)(common + 0x6d8);
                if (data_0209f310[idx] != 0) {
                    GiveVsStars(idx, -1);
                }
            }
            *(int *)(c + 0x440) = 8;
            *(int *)(c + 0xa8) = 0x20000;
            *(int *)(c + 0x98) = 0xc000;
            ((daStar_c *)((unsigned char *)c))->func_ov002_020e9448();
            *(int *)(c + 0x128) &= ~1;
        }
    }

    *(int *)(c + 0x4b8) = 0;
    *(int *)(c + 0x4b4) = *(int *)(c + 0x4b8);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 59 -- func_ov002_020ea06c, 0x020ea06c, size 0x94 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020ea06cEv
extern "C" {
typedef int Fix12i;
extern void _ZN9Animation7AdvanceEv(void* a);
extern void _ZN5Sound17ChangeMusicVolumeEj5Fix12IiE(unsigned int a, Fix12i v);
}

void daStar_c::func_ov002_020ea06c() {
    char* c = (char*)this;
  int* s = (int*)(((int)*(void**)(c+0x438) + 0x5c));
  *(int*)(c+0x5c) = s[0];
  *(int*)(c+0x60) = s[1];
  *(int*)(c+0x64) = s[2];
  *(short*)(c+0x94) = *(short*)((char*)*(void**)(c+0x438) + 0x8e);
  *(int*)(c+0x440) = 7;
  *(short*)(c+0x490) = 0;
  *(unsigned char*)(c+0x49b) = 0;
  _ZN9Animation7AdvanceEv(c+0x35c);
  ((daStar_c *)(c))->func_ov002_020e8098();
  if (*(int*)(c+0x43c) == 9) {
    _ZN5Sound17ChangeMusicVolumeEj5Fix12IiE(0, 0x7f000);
  }
  ++*(unsigned char*)(((int)c + 0x4a1));
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 58 -- func_ov002_020e9d18, 0x020e9d18, size 0x354 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e9d18Ev
/* The player pointer at +0x438 is loaded as a char* wherever its +0x6d8 byte
   is read: with an int-typed load mwcc materializes 0x6d8 from the literal
   pool (ldr r0,[pc] / ldrb r2,[r1,r0]) instead of folding it, and the
   int-vs-char* loads in the second SpawnNumber call stop sharing one
   ldr [r5,#0x438]. */
void daStar_c::func_ov002_020e9d18() {
    char * c = (char *)this;
    u32 r2v;
    u32 b2;
    u32 st;
    Vec3 t1;
    Vec3 t2;
    int *src;

    src = (int *)(((int)*(int *)(c + 0x438) + 0x5c) & 0xFFFFFFFFFFFFFFFF);
    *(int *)(c + 0x5c) = src[0];
    *(int *)(c + 0x60) = src[1];
    *(int *)(c + 0x64) = src[2];
    *(s16 *)(c + 0x94) = *(s16 *)(*(int *)(c + 0x438) + 0x8e);
    if (*(int *)(c + 0x43c) == 9) {
        if (*(u8 *)(c + 0x4a1) < 0x78) {
            _ZN5Sound17ChangeMusicVolumeEj5Fix12IiE(0, 0x7f000);
            (*(u8 *)(((int)c + 0x4a1) & 0xFFFFFFFFFFFFFFFF))++;
        } else {
            _ZN5Sound17ChangeMusicVolumeEj5Fix12IiE(0x40, 0xcb33);
        }
    }
    if (_ZN9Animation8FinishedEv(c + 0x35c) != 0) {
        (*(u16 *)(((int)c + 0x490) & 0xFFFFFFFFFFFFFFFF))++;
    } else {
        ((daStar_c *)(c))->func_ov002_020e7eb4();
    }
    r2v = data_0209f2d8 == 1;
    if (r2v != false)
        goto modes;
    b2 = *(u16 *)(c + 0xc);
    b2 = b2 == 0xb3;
    if (b2 == false)
        goto big_else;
modes:
    {
        u32 tmp;
        u16 mode;
        tmp = *(u16 *)(c + 0xc);
        tmp = tmp == 0xb3;
        if (tmp != false)
            st = 1;
        else
            st = 0;
        mode = *(u16 *)(c + 0x490);
        if (mode == 1 && r2v == 0) {
            int idx = *(u8 *)(*(char **)(c + 0x438) + 0x6d8);
            if (data_0209f310[idx] == 4) {
                GiveVsStars(idx, 1);
                func_ov002_020e8244(&t1, c);
                _ZN8dActor_c11SpawnNumberERK7Vector3jbtPS_(c, (Vector3 *)&t1, 5, st, 0, (void *)(int)*(char **)(c + 0x438));
                ((daStar_c *)(c))->func_ov002_020e8618();
            }
        } else if (mode == 5) {
            int idx2 = *(u8 *)(*(char **)(c + 0x438) + 0x6d8);
            if (data_0209f310[idx2] == 5 && r2v == false)
                goto end;
            if (r2v == false)
                GiveVsStars(idx2, 1);
            func_ov002_020e8244(&t2, c);
            _ZN8dActor_c11SpawnNumberERK7Vector3jbtPS_(c, (Vector3 *)&t2,
                data_0209f310[*(u8 *)(*(char **)(c + 0x438) + 0x6d8)], st, 0,
                (void *)(int)*(char **)(c + 0x438));
            ((daStar_c *)(c))->func_ov002_020e8618();
        }
        goto end;
    }
big_else:
    {
        u32 st2;
        if (*(int *)(c + 0x43c) == 9) {
            st2 = 0x11;
LA:
        if (((u32)(*(u16 *)(c + 0x4a2) << 20) >> 30) == 0) {
            *(u16 *)(((int)c + 0x4a2) & 0xFFFFFFFFFFFFFFFF) =
                (*(u16 *)(((int)c + 0x4a2) & 0xFFFFFFFFFFFFFFFF) & ~0xc00) |
                ((data_0209d684 & 3) << 10);
            {
                u32 b3 = (u32)(*(u16 *)(c + 0x4a2) << 20) >> 30;
                if (b3 == 1) {
                    func_02012790(0x57);
                } else if (b3 != 2) {
                    *(u16 *)(((int)c + 0x4a2) & 0xFFFFFFFFFFFFFFFF) &= ~0xc00;
                } else {
                    func_02012790(0x5c);
                }
            }
        }
        *(u16 *)(c + 0x490) = 0xa;
        if (_ZN6Player12Unk_020c9e5cEh((void *)(*(int *)(c + 0x438)), st2) == 0) {
            *(u8 *)(c + 0x49b) = 2;
            *(int *)(c + 0x440) = 0xb;
            *(u16 *)(c + 0x490) = 0;
            *(int *)(((int)*(int *)(c + 0x438) + 0xb0) & 0xFFFFFFFFFFFFFFFF) &= ~0x4000000;
            EndKuppaScript();
        }
        _ZN9Animation7AdvanceEv(c + 0x35c);
        ((daStar_c *)(c))->func_ov002_020e8098();
        return;
        }
        if (*(u8 *)(c + 0x49d) == 0 || ((daStar_c *)(c))->func_ov002_020e9630() != 0) {
            st2 = 1;
            goto LA;
        }
        if (*(int *)(c + 0x444) == 9 || *(u8 *)(c + 0x49d) == 8)
            ((daStar_c *)(c))->func_ov002_020e8618();
    }
end:
    _ZN9Animation7AdvanceEv(c + 0x35c);
    ((daStar_c *)(c))->func_ov002_020e8098();
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 57 -- func_ov002_020e9af4, 0x020e9af4, size 0x224 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e9af4Ev
extern "C" {  /* .c-derived member: C linkage for the whole block */
/* Table-entry overlay for this shard only (the file-scope 'Sub' names cover
 * incompatible layouts elsewhere): func_ov002_020e9af4 reads word 0x8e. */
struct SubX8e {
    u8 pad[0x8e];
    s16 x8e;
};
}

void daStar_c::func_ov002_020e9af4() {
    ObjB* self = (ObjB*)this;
    if (self->x43c == 9) {
        if (self->x4a1 < 0x78) {
            _ZN5Sound17ChangeMusicVolumeEj5Fix12IiE(0, 0x7f000);
            (*(u8*)((int)self + 0x4a1))++;
        } else {
            _ZN5Sound17ChangeMusicVolumeEj5Fix12IiE(0x40, 0xcb33);
        }
    }
    self->x94 = ((SubX8e*)self->x438)->x8e;
    switch (self->x49b) {
    case 2:
        if (_ZN6Player12GetTalkStateEv(self->x438) == -1) {
            u32 t = ((u32)self->x4a2 << 20) >> 30;
            if (t == 1) {
                _ZN7Message13DisplaySavingEt(0x295);
                (*(u8*)((int)self + 0x49b))++;
                {
                    u16* p = (u16*)((int)self->x438 + 0x6ce);
                    *p = *p | 0x800;
                }
            } else if (t == 2) {
                (*(u8*)((int)self + 0x49b)) += 2;
                _ZN7Message7EndTalkEv();
            }
        }
        break;
    case 3:
        if (data_0209d660 == 0) {
            (*(u8*)((int)self + 0x49b))++;
        }
        break;
    case 4:
        if (func_ov002_020c6e14(self->x438) != 0) {
            (*(u8*)((int)self + 0x49b))++;
        } else {
            (*(u8*)((int)self + 0x49b)) += 2;
        }
        break;
    case 5:
        if (data_0209d660 == 0) {
            _ZN7Message7EndTalkEv();
            (*(u8*)((int)self + 0x49b))++;
        }
        break;
    case 6:
        {
            u16* p = (u16*)((int)self->x438 + 0x6ce);
            *p = *p & ~0x800;
        }
        {
            u16* q = (u16*)((int)self + 0x4a2);
            *q = *q & ~2;
        }
        ((daStar_c *)((char*)self))->func_ov002_020e8618();
        break;
    }
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 56 -- func_ov002_020e99e8, 0x020e99e8, size 0x10c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e99e8Ev
void daStar_c::func_ov002_020e99e8() {
    char* c = (char*)this;
  ((daStar_c *)(c))->func_ov002_020e8c34();
  *(int*)(c + 0x6c) = *(int*)(c + 0x60);
  _ZN12dEnemyBase_c12UpdateWMClsnER10dBgCh_Actrj(c, c + 0x150, 2);
  if (_ZNK10dBgCh_Actr8IsOnWallEv(c + 0x150)){
    *(short*)(c + 0x94) = _ZN8dActor_c12ReflectAngleE5Fix12IiES1_s(c, *(int*)(c + 0xe0), *(int*)(c + 0xe8), *(short*)(c + 0x94));
  }
  ((daStar_c *)(c))->func_ov002_020e86ec();
  if (_ZNK10dBgCh_Actr13JustHitGroundEv(c + 0x150)){
    ((daStar_c *)(c))->func_ov002_020e88a8();
  } else if (_ZNK10dBgCh_Actr10IsOnGroundEv(c + 0x150)){
    *(short*)(c + 0x94) = _ZN8dActor_c12ReflectAngleE5Fix12IiES1_s(c, *(int*)(c + 0xe0), *(int*)(c + 0xe8), *(short*)(c + 0x94));
    if ((((unsigned)*(unsigned short*)(c + 0x4a2) << 0x1a) >> 0x1e) == 2)
      *(int*)(c + 0xa8) = 0xe000;
    else
      *(int*)(c + 0xa8) = 0x17000;
  }
  {
    unsigned short* ctr = (unsigned short*)(c + 0x100);
    if (*ctr == 0){
      if ((((unsigned)*(unsigned short*)(c + 0x4a2) << 0x1c) >> 0x1f) == 0)
        ((daStar_c *)(c))->func_ov002_020e930c();
    } else {
      *ctr = *ctr - 1;
    }
  }
  ((daStar_c *)(c))->func_ov002_020e7d08();
  ((daStar_c *)(c))->func_ov002_020e7f2c();
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 55 -- func_ov002_020e9840, 0x020e9840, size 0x1a8 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e9840Ev
/* recovered: shared common types */
/* func_ov002_020e9840 at 0x020e9840 (ov002), size 0x1a8
 * Matched byte-for-byte with mwccarm 1.2/sp2p3.
 * flags: -O4,p -enum int -lang c99 -char signed -interworking -proc arm946e -gccext,on -msgstyle gcc
 */
void daStar_c::func_ov002_020e9840() {
    char * self = (char *)this;
    char *actor;

    actor = (char *)_ZN8dActor_c10FindWithIDEj(*(unsigned int *)(self + 0x434));
    if (actor == 0) {
        ((daStar_c *)(self))->func_ov002_020e9590();
        return;
    }
    if (actor == 0) return;

    if ((unsigned)(*(u16 *)(self + 0x4a2) << 30) >> 31 == 0) {
        if (*(u8 *)(self + 0x49d) != data_0209f344[data_0209f208]) return;
        if (*(u16 *)(actor + 0x1d4) != 0) return;

        *(u16 *)(self + 0x4a2) |= 2;
        ((daStar_c *)((unsigned char *)self))->func_ov002_020e8dd8();
        func_02012694(0x54, (struct Vector3 *)(self + 0x74));
        return;
    }

    if ((unsigned)(*(u8 *)(actor + 0x1db) << 31) >> 31 == 0) return;

    *(u16 *)(self + 0x4a2) &= ~8;
    *(u16 *)(self + 0x100) = 0xf;
    *(int *)(self + 0x440) = 8;
    *(int *)(self + 0xa8) = 0x20000;
    ((daStar_c *)((unsigned char *)self))->func_ov002_020e9448();

    *(int *)(self + 0x128) &= ~1;

    {
        int r0 = (data_0209f2d8 == 1) ? 1 : 0;
        int *r3 = *(int **)(actor + 0x1d0);
        if (r0 == 0) return;
        if (r3 == 0) return;

        *(u16 *)(self + 0x4a2) |= 8;
        *(int *)(self + 0x98) = 0xc000;
        *(s16 *)(self + 0x94) = GetAngleToCamera(*(u8 *)((char *)r3 + 0x6d8)) + 0x8000;
    }
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 54 -- func_ov002_020e9804, 0x020e9804, size 0x3c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e9804Ev
extern "C" {

}

void daStar_c::func_ov002_020e9804() {
    char * thiz = (char *)this;
    ((Animation *)(thiz + 0x35c))->Advance();
    ((daStar_c *)(thiz))->func_ov002_020e7fcc();
    if (!((Animation *)(thiz + 0x35c))->Finished()) return;
    ((fBase_c *)thiz)->MarkForDestruction();
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 53 -- func_ov002_020e96a0, 0x020e96a0, size 0x164 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e96a0Ev
void daStar_c::func_ov002_020e96a0() {
    char * c = (char *)this;
    int v[3];
    char *p;
    int *src;
    unsigned short t;

    *(unsigned short *)(((int)c + 0x490)) += 1;
    *(short *)(((int)c + 0x8e)) += 0x800;
    t = *(unsigned short *)(c + 0x490);
    if (t >= 0x1e) {
        if (t == 0x1e) {
            GiveVsStars(*(unsigned char *)(*(char **)(c + 0x438) + 0x6d8), 1);
            func_ov002_020e8244(v, c);
            p = *(char **)(c + 0x438);
            _ZN8dActor_c11SpawnNumberERK7Vector3jbtPS_(c, (Vector3 *)v, (unsigned int)data_0209f310[*(unsigned char *)(p + 0x6d8)], 1, 0, p);
            _ZN8dActor_c11UntrackStarERa(c, (signed char *)(c + 0x498));
        }
        *(unsigned short *)(((int)c + 0x4a2)) &= ~2;
        if (*(unsigned short *)(c + 0x490) < 0x64) return;
        ((daStar_c *)(c))->func_ov002_020e7e58();
        if ((int)(data_0209f2d8 == 1) != 0) {
            _ZN7fBase_c18MarkForDestructionEv(c);
        } else {
            _ZN8dActor_c24KillAndTrackInDeathTableEv(c);
        }
    } else {
        p = *(char **)(c + 0x438);
        src = (int *)(((int)p + 0x5c));
        *(int *)(c + 0x5c) = src[0];
        *(int *)(c + 0x60) = src[1];
        *(int *)(c + 0x64) = src[2];
        *(int *)(((int)c + 0x60)) += 0x104000;
        ((daStar_c *)(c))->func_ov002_020e8098();
    }
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 52 -- func_ov002_020e9630, 0x020e9630, size 0x70 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e9630Ev
int daStar_c::func_ov002_020e9630() {
    char * unused = (char *)this;
  int lv = SublevelToLevel(data_0209f2f8);
  if (lv == 0xf || lv == 0x10 || lv == 0x11 || lv == 0x12 ||
      lv == 0x13 || lv == 0x14 || lv == 0x1d)
    return 1;
  return 0;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 51 -- func_ov002_020e9590, 0x020e9590, size 0xa0 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e9590Ev
void daStar_c::func_ov002_020e9590() {
    char* self = (char*)this;
    dActor_c* found;
    if (_ZN8dActor_c10FindWithIDEj(*(unsigned int*)(self + 0x434)))
        return;
    found = 0;
    for (;;) {
        found = (dActor_c *)_ZN8dActor_c15FindWithActorIDEjPS_(0xb4, found);
        if (!found)
            return;
        if (*(unsigned char*)(self + 0x49d) == *(unsigned char*)((char*)found + 0x1d9)) {
            int v444 = *(int*)(self + 0x444);
            if (v444 == 9 && *(unsigned char*)((char*)found + 0x1d8))
                break;
            if (v444 == 9)
                continue;
            if (!*(unsigned char*)((char*)found + 0x1d8))
                break;
        }
    }
    *(int*)(self + 0x434) = *(int*)((char*)found + 4);
    ((daStarBase_c *)((char *)found))->LinkSilverStarAndStarMarker(self);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 50 -- func_ov002_020e947c, 0x020e947c, size 0x114 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e947cEP7Vector3i
void daStar_c::func_ov002_020e947c(Vector3 *p, int n) {
    void * c = (void *)this;
    int dy = ((int *)p)[1] - *(int*)((char *)c + 0x60);
    if (dy < 0)
        dy = -dy;
    {
        int s0 = _ZN4cstd4sqrtEy((u64)(s64)n);
        int s1 = _ZN4cstd4sqrtEy((u64)(s64)(n + dy));
        int s2 = _ZN4cstd4sqrtEy((u64)(s64)n);
        dy = (s0 * 0x32) / (s1 + s2);
    }
    {
        int left = -(n << 1);
        int den = dy * dy;
        n = 0x32 - dy;
        *(int*)((char *)c + 0x9c) = left / den;
    }
    if (((int *)p)[1] >= *(int*)((char *)c + 0x60)) {
        int v = *(int*)((char *)c + 0x9c);
        if (v < 0)
            v = -v;
        *(int*)((char *)c + 0xa8) = n * v;
    } else {
        int v = *(int*)((char *)c + 0x9c);
        if (v < 0)
            v = -v;
        *(int*)((char *)c + 0xa8) = (dy + 1) * v;
    }
    *(int*)((char *)c + 0xa0) = -0x32000;
    *(int*)((char *)c + 0x98) = Vec3_HorzDist((const Vec3*)((char *)c + 0x5c), (const Vec3*)p) / 50;
    *(short*)((char *)c + 0x94) = Vec3_HorzAngle((const Vector3*)((char *)c + 0x5c), (const Vector3*)p);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 49 -- func_ov002_020e9464, 0x020e9464, size 0x18 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e9464Ev
void daStar_c::func_ov002_020e9464() {
    char * p = (char *)this;
    *(int *)(p + 0xa8) = 0;
    *(int *)(p + 0x9c) = 0;
    *(int *)(p + 0xa0) = 0;
    *(int *)(p + 0x98) = 0;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 48 -- func_ov002_020e9448, 0x020e9448, size 0x1c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e9448Ev
void daStar_c::func_ov002_020e9448() {
    void * p = (void *)this;
  *(int*)(((unsigned char *)p) + 0x9c) = -0x1600;
  *(int*)(((unsigned char *)p) + 0xa0) = -0x20000;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 47 -- func_ov002_020e930c, 0x020e930c, size 0x13c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e930cEv
/* func_ov002_020e930c at 0x020e930c
 *
 * Matched byte-for-byte with mwccarm 1.2/sp2p3 (ov002).
 */
void daStar_c::func_ov002_020e930c() {
    void* self = (void*)this;
    char* a = (char*)self;
    void* o;
    char* b;
    int flags;
    unsigned int id;

    id = *(unsigned int*)(a + 0x134);
    if (id == 0) return;
    o = _ZN8dActor_c10FindWithIDEj(id);
    if (o == 0) return;
    b = (char*)o;

    flags = *(int*)(a + 0x130);
    if (flags & 0x400000) {
        if (*(u8*)(b + 0x709) != 0) return;
        if (_ZN5Event6GetBitEj(0x1e) != 0) return;
        if (((daStar_c *)((char *)self))->func_ov002_020e8ef0(o) == 0) return;
        if (*(int*)(a + 0x43c) != 6) return;
        if (_ZN8dActor_c10FindWithIDEj(*(unsigned int*)(a + 0x434)) == 0) return;
        _ZN12daStarBase_c7CollectEv();
    } else {
        if (flags & 0x8000) {
            if (*(u8*)(b + 0x709) != 0) return;
            if (_ZN5Event6GetBitEj(0x1e) != 0) return;
            if (*(int*)(a + 0x43c) != 6) return;
            if (_ZN8dActor_c10FindWithIDEj(*(unsigned int*)(a + 0x434)) == 0) return;
            _ZN12daStarBase_c7CollectEv();
        }
    }
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 46 -- func_ov002_020e8ef0, 0x020e8ef0, size 0x41c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e8ef0EPv
int daStar_c::func_ov002_020e8ef0(void* p) {
    char* c = (char*)this;
    void* found;
    int r5;
    int r4;
    int sb;

    *(u32*)(c + 0x440) = 0xa;
    found = _ZN8dActor_c10FindWithIDEj(*(u32*)(c + 0x434));
    if (found) {
        ((daStarBase_c *)((char *)found))->LinkSilverStarAndStarMarker((char *)0);
    }
    *(void**)(c + 0x438) = p;

    if (_ZN6Player9IsOnShellEv(p) != 0) {
        int b = (*(u16*)(c + 0xc) == 0xb3);
        if (b) {
            *(u32*)(c + 0x440) = 0xd;
            *(u16*)(((int)c + 0x4a2)) &= ~4;
            *(u16*)(c + 0x490) = 0;
            *(u32*)(c + 0x4b8) = 0;
            *(u32*)(c + 0x4b4) = *(u32*)(c + 0x4b8);
            func_02012790(0x2d);
            *(u32*)(((int)c + 0x128)) |= 1;
            _ZN5dCc_c5ClearEv(c + 0x110);
            ((daStar_c *)(c))->func_ov002_020e6fbc(0x14);
            *(u8*)(c + 0x49c) = 1;
            return 1;
        }
    }

    r5 = 0;
    r4 = ((daStar_c *)(c))->func_ov002_020e73ac();
    {
        if (r4 != 0) {
            int t1 = (data_0209f2d8 == 1);
            if (!t1) {
                int t2 = (*(u16*)(c + 0xc) == 0xb3);
                if (!t2) {
                    if (*(u32*)(c + 0x444) != 9) {
                        if (*(u8*)(c + 0x49d) == 0) {
                            sb = _ZN6Player17SetNoControlStateEhih(p, r4, 0x186, 0);
                            _ZN7Message11PrepareTalkEv();
                            r5 = 1;
                        } else if (((daStar_c *)(c))->func_ov002_020e9630() != 0) {
                            sb = _ZN6Player17SetNoControlStateEhih(p, r4, 0x187, 0);
                            _ZN7Message11PrepareTalkEv();
                            r5 = 1;
                        } else {
                            sb = _ZN6Player17SetNoControlStateEhih(p, r4, -1, 0);
                        }
                        goto after_sc;
                    }
                }
            }
        }
        sb = _ZN6Player17SetNoControlStateEhih(p, r4, -1, 0);
    after_sc:;

        if (sb == 0) {
            goto ret0;
        }

        {
            int b1 = (data_0209f2d8 == 1);
            if (!b1) {
                _ZN5Event6SetBitEj(0x1e);
            } else {
                GiveVsStars(*(u8*)((char*)p + 0x6d8), 1);
            }
        }
        if (r4 == 0) {
            _ZN5Event6SetBitEj(0x1d);
        }

        {
        int b2 = (data_0209f2d8 == 1);
        int b3;
        if (!b2 && !(b3 = (*(u16*)(c + 0xc) == 0xb3)) &&
            *(u8*)(c + 0x49d) < 8 &&
            *(u32*)(c + 0x444) != 9) {
            data_0209f228 = *(u8*)(c + 0x49d);
            if (IsStarCollectedInCurLevel(*(u8*)(c + 0x49d)) != 0) {
                data_0209f2ac = 0;
            } else {
                data_0209f2ac = 1;
            }
            CollectStarInCurLevel(*(u8*)(c + 0x49d));
            if (r5 != 0) {
                int lvl;
                if ((((u32)(*(u16*)(c + 0x4a2) << 0x13)) >> 0x1f) != 0 && found != 0) {
                    _ZN8dActor_c17TrackInDeathTableEv(found);
                }
                lvl = SublevelToLevel((signed char)data_0209f2f8);
                if (lvl <= 0xe) {
                    int rec = _ZN8SaveData13GetCoinRecordEj(lvl);
                    if (rec < NumCoins()) {
                        _ZN8SaveData21SetCoinRecordIfHigherEah(
                            lvl,
                            (u8)(data_0209f358[*(u8*)((char*)p + 0x6d8)] & 0xff));
                    }
                }
            }
        }
        }
    }

    if (*(u32*)(c + 0x444) == 9) {
        data_0209f208++;
    }
    func_02012790(0x2d);
    *(u32*)(c + 0x440) = 5;
    *(void**)(c + 0x438) = p;
    {
        int b4 = (data_0209f2d8 == 1);
        if (!b4) {
            void* pp = *(void**)(c + 0x438);
            *(u32*)(((int)pp + 0xb0)) |= 0x4000000;
            *(u32*)(((int)c + 0xb0)) |= 0x4000000;
            data_0209b454 |= 0x4000000;
        }
    }
    *(u32*)(((int)c + 0x128)) |= 1;
    _ZN5dCc_c5ClearEv(c + 0x110);
    {
        int b5 = (*(u16*)(c + 0xc) == 0xb2);
        if (b5 && r4 != 0) {
            _ZN6Player4HealEi(p, 0x880);
        }
    }
    ((daStar_c *)(c))->func_ov002_020e9464();
    data_0209d684 = 0;
    return 1;
ret0:
    return 0;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 45 -- _ZN8daStar_c13OnYoshiTryEatEv, 0x020e8ee8, size 0x8 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c13OnYoshiTryEatEv
/* recovered: renamed to Class_Method */
s32 daStar_c::OnYoshiTryEat() {
    return 4;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 44 -- _ZN8daStar_c13OnTurnIntoEggER6Player, 0x020e8edc, size 0xc */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c13OnTurnIntoEggER6Player
// recovered name: PowerStar_OnTurnIntoEgg
/* daStar_c::OnTurnIntoEgg -- vtable slot 19, verified against ov002 relocs.txt:
 * _ZTV8daStar_c (0x0210ab3c) + 0x4c -> 0x020e8edc, exactly this placeholder's
 * former address (former name func_ov002_020e8edc). The ROM body is a
 * tail-call veneer (`ldr ip, [pc]; bx ip`) to func_ov002_020e8e80, passing
 * `this`/`player` straight through unchanged.
 * Matched byte-for-byte with mwccarm 2004/b56 (ov002).
 */
void daStar_c::OnTurnIntoEgg(Player &player)
{
    return ((daStar_c *)((char *)this))->func_ov002_020e8e80((int)&player);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 43 -- func_ov002_020e8e80, 0x020e8e80, size 0x5c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e8e80Ei
void daStar_c::func_ov002_020e8e80(int a) {
    char* c = (char*)this;
    int* p;
    char* pl = _ZN8dActor_c10FindWithIDEj(*(unsigned int*)(c + 0x434));
    if (pl != 0)
        ((daStarBase_c *)(pl))->LinkSilverStarAndStarMarker(0);

    *(int*)(c + 0x438) = a;
    ((daStar_c *)(c))->func_ov002_020e9464();
    p = (int*)(c + 0xb0);
    *p = *p & ~0x40000;
    ((daStar_c *)(c))->func_ov002_020e8ef0((void *)a);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 42 -- func_ov002_020e8dd8, 0x020e8dd8, size 0xa8 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e8dd8Ev
int daStar_c::func_ov002_020e8dd8() {
    unsigned char * self = (unsigned char *)this;
  signed char g1 = data_0209f2f8;
  int t;
  if (g1 == 5)
  {
    if ((*((u8 *) (self + 0x49d))) == 5)
    {
      return;
    }
  }
  if (g1 == 0x16)
  {
    if ((*((u8 *) (self + 0x49d))) == 4)
    {
      if (data_0209f264 != 4)
      {
        return;
      }
      ((daStar_c *)self)->AddStarMarker();
      return;
    }
  }
  if ((*((u8 *) (self + 0x49a))) == 0)
  {
    t = *((int *) (self + 0x43c));
    if ((t != 2) && (t != 4))
    {
      return;
    }
  }
  ((daStar_c *)self)->AddStarMarker();
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 41 -- _ZN8daStar_c13AddStarMarkerEv, 0x020e8ca0, size 0x138 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c13AddStarMarkerEv
/* recovered: named members + shared header, real C++ method, declarations from a shared header */
/* recovered: named members + shared header, real C++ method */
void daStar_c::AddStarMarker()
{
    s8 i;
    if (unk_498 >= 0) return;
    for (i = 0; i < 0xc; i++) {
        if (data_0209f40c[(int)i] != 0) continue;

        if (unk_49a == 0) {
            if (((struct Bits*)((char*)&unk_4a2))->b2) {
                SetStarMarker((int)i, (int)((char*)this), 3);
            } else {
                SetStarMarker((int)i, (int)((char*)this), 2);
            }
        } else {
            if (unk_49a == 2) {
                if (((struct Bits*)((char*)&unk_4a2))->b2) goto setmark;
                {
                    int f43c = unk_43c;
                    if (f43c == 5 || f43c == 7) {
                        if (IsStarCollectedInCurLevel(unk_49d) != 0) goto setmark;
                    }
                }
                goto skipmark;
            setmark:
                unk_49a = 3;
            skipmark:;
            }
            SetStarMarker((int)i, (int)((char*)this), unk_49a);
        }

        unk_498 = i;
        if (unk_440 == 9) {
            if (data_0209f208 == 0) return;
        }
        FUN_0202a130();
        return;
    }
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 40 -- func_ov002_020e8c34, 0x020e8c34, size 0x6c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e8c34Ev
volatile unsigned int daStar_c::func_ov002_020e8c34() {
    void * a = (void *)this;
  int v;
  int y;
  v = *((int *) (((char *) a) + 0x5c));
  y = 0;
  if (y > v)
  {
    v = -v;
  }
  if (v <= 0x13880000)
  {
    v = *((int *) (((char *) a) + 0x64));
    if (v < y)
    {
      v = -v;
    }
    if (v <= 0x13880000)
    {
      y = *((int *) (((char *) a) + 0x60));
      if ((y >= (*((int *) (((char *) a) + 0x484)))) && (y <= 0x13880000))
      {
        return;
      }
    }
  }
  ((daStar_c *)((char *)a))->func_ov002_020e8abc();
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 39 -- func_ov002_020e8abc, 0x020e8abc, size 0x178 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e8abcEv
void daStar_c::func_ov002_020e8abc() {
    char * self = (char *)this;
    char *a;

    a = (char *)_ZN8dActor_c10FindWithIDEj(*(unsigned int *)(self + 0x434));
    if (a == 0) {
        _ZN7fBase_c18MarkForDestructionEv(self);
        return;
    }

    if (*(int *)(self + 0x444) == 9) {
        u16 *f;
        *(int *)(self + 0x5c) = *(int *)(self + 0x454);
        *(int *)(self + 0x60) = *(int *)(self + 0x458);
        *(int *)(self + 0x64) = *(int *)(self + 0x45c);
        func_02035860(self + 0x150, self + 0x5c);
        *(int *)(self + 0x440) = *(int *)(self + 0x444);
        ((daStar_c *)(self))->func_ov002_020e9464();
        *(int *)(self + 0x128) |= 1;
        f = (u16 *)(self + 0x4a2);
        *f &= ~2;
        *f |= 8;
        *f &= ~0x30;
        if (*(int *)(a + 8) & 0x20) {
            return;
        }
        {
            u8 *q = (u8 *)(a + 0x1db);
            *q &= ~1;
            *q |= 2;
        }
        *(int *)(a + 0x1d0) = 0;
        return;
    }

    {
        unsigned long fl = *(u16 *)(self + 0x4a2);
        if ((fl << 0x19) >> 0x1f) {
            ((daStar_c *)(self))->func_ov002_020e7454();
            return;
        }
    }

    *(int *)(self + 0x5c) = *(int *)(self + 0x454);
    *(int *)(self + 0x60) = *(int *)(self + 0x458);
    *(int *)(self + 0x64) = *(int *)(self + 0x45c);
    func_02035860(self + 0x150, self + 0x5c);
    *(int *)(self + 0x440) = *(int *)(self + 0x444);
    *(int *)(self + 0xa8) = 0x20000;
    ((daStar_c *)((unsigned char *)self))->func_ov002_020e9448();
    *(u16 *)(self + 0x100) = 0xf;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 38 -- func_ov002_020e88a8, 0x020e88a8, size 0x214 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e88a8Ev
/* recovered: shared common types, declarations from a shared header */
/* recovered: shared common types */
void daStar_c::func_ov002_020e88a8() {
    char* self = (char*)this;
    struct Vector3 v;
    struct Vector3 w;
    char* p;
    int r;

    if (((struct Flags*)(self + 0x4a2))->b3) {
        ((struct Flags*)((int)(self + 0x4a2)))->b3 = 0;
        *(unsigned short*)(self + 0x100) = 0;
    }
    func_02012694(0x55, self + 0x74);
    if (((struct Flags*)(self + 0x4a2))->fld == 2) {
        *(int*)(self + 0x98) = 0xc000;
        *(int*)(self + 0xa8) = 0xe000;
    } else {
        *(int*)(self + 0x98) = 0xc000;
        *(int*)(self + 0xa8) = 0x17000;
    }
    r = func_02037e38(_ZNK10dBgCh_Actr14GetFloorResultEv(self + 0x150) + 4);
    if (r == 1 || r == 9) {
        w.x = *(int*)(self + 0x448);
        w.y = *(int*)(self + 0x44c);
        w.z = *(int*)(self + 0x450);
        ((daStar_c *)(self))->func_ov002_020e947c(&w, 0xc8000);
        return;
    }
    if (r == 4 || r == 5) {
        ((daStar_c *)(self))->func_ov002_020e8abc();
        return;
    }
    ((daStar_c *)(self))->func_ov002_020e9448();
    *(int*)(self + 0x448) = *(int*)(self + 0x5c);
    *(int*)(self + 0x44c) = *(int*)(self + 0x60);
    *(int*)(self + 0x450) = *(int*)(self + 0x64);
    p = _ZN8dActor_c13ClosestPlayerEv(self);
    if (p == 0) return;
    {
        int* s = (int*)((int)(p + 0x5c));
        v.x = s[0];
        v.y = s[1];
        v.z = s[2];
    }
    if (Vec3_Dist((struct Vector3*)(self + 0x5c), &v) < 0x4b0000) {
        *(short*)(self + 0x94) = Vec3_HorzAngle(&v, (struct Vector3*)(self + 0x5c));
        if (*(int*)(self + 0xd8) >= *(short*)(data_02082714 + 0x56)) {
            if (data_0209f2f8 != 0x1d) return;
            if (func_02037e58(_ZNK10dBgCh_Actr14GetFloorResultEv(self + 0x150) + 4) != 5) return;
        }
        {
            short* a = (short*)((int)(((long long)(int)(self + 0x94)) | 0LL));
            *a = *a + 0x8000;
        }
    } else {
        char* q = _ZN8dActor_c14FarthestPlayerEv(self);
        if (q != 0) {
            q = q + 0x5c;
            *(short*)(self + 0x94) = Vec3_HorzAngle((struct Vector3*)(self + 0x5c), (struct Vector3*)q);
        }
    }
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 37 -- func_ov002_020e86ec, 0x020e86ec, size 0x1bc */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e86ecEv
/* recovered: shared common types, declarations from a shared header */
/* recovered: shared common types */
void daStar_c::func_ov002_020e86ec() {
    char* self = (char*)this;
    struct Vector3 v;
    char rc[0x54];
    int tx, ty, tz, ta;

    if (((struct Flags*)(self + 0x4a2))->fld < 2) {
        if (((struct Flags*)(self + 0x4a2))->fld != 1) {
            if (_ZNK10dBgCh_Actr12TouchesWaterEv(self + 0x150) == 0) return;
        }
        if (((struct Flags*)(self + 0x4a2))->fld == 0) {
            ((struct Flags*)((int)(self + 0x4a2)))->fld = 1;
            *(int*)(self + 0x60) = *(int*)(self + 0x6c);
            _ZN10dBgCh_Actr15ClearGroundFlagEv(self + 0x150);
            _ZN10dBgCh_Actr22ClearJustHitGroundFlagEv(self + 0x150);
            _ZN10dBgCh_Actr18StopDetectingWaterEv(self + 0x150);
        }
        _ZN9dBgCh_GndC1Ev(rc);
        _ZN5dBgCh19StartDetectingWaterEv(rc);
        ty = *(int*)(self + 0x60);
        tz = *(int*)(self + 0x64);
        tx = *(int*)(self + 0x5c);
        ta = ty + 0xa0000;
        v.x = tx;
        v.y = ta;
        v.z = tz;
        _ZN9dBgCh_Gnd12SetObjAndPosERK7Vector3P8dActor_c(rc, &v, self);
        if (_ZN9dBgCh_Gnd10DetectClsnEv(rc) != 0) {
            if (SurfaceInfo_TestFlag0x20(rc + 0x14) != 0) {
                *(int*)(self + 0x488) = *(int*)(rc + 0x44);
                data_0209f32c = *(int*)(self + 0x488);
                if (*(int*)(self + 0x488) >= *(int*)(self + 0x60) + 0x3c000) {
                    ((struct Flags*)((int)(self + 0x4a2)))->fld = 2;
                    *(int*)(self + 0x9c) = -0x700;
                    *(int*)(self + 0xa0) = -0x10000;
                    *(int*)(self + 0x98) = 0xc000;
                    *(int*)(self + 0xa8) = 0;
                }
            }
        }
        _ZN9dBgCh_GndD1Ev(rc);
    } else {
        if (data_0209f32c < *(int*)(self + 0x60) + 0x3c000) {
            ((struct Flags*)((int)(((long long)(int)(self + 0x4a2)) | 0LL)))->fld = 0;
            ((daStar_c *)(self))->func_ov002_020e9448();
            _ZN10dBgCh_Actr19StartDetectingWaterEv(self + 0x150);
        }
    }
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 36 -- func_ov002_020e8618, 0x020e8618, size 0xd4 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e8618Ev
void daStar_c::func_ov002_020e8618() {
    char* c = (char*)this;
  if(_ZN9Animation8FinishedEv(c+0x35c) == 0) return;
  ((daStar_c *)(c))->func_ov002_020e7e58();
  *(unsigned short*)(((int)c + 0x4a2)) &= ~2;
  _ZN8dActor_c11UntrackStarERa(c, (signed char*)(c+0x498));
  if((int)(data_0209f2d8 == 1) != 0){
    _ZN7fBase_c18MarkForDestructionEv(c);
  }else{
    _ZN8dActor_c24KillAndTrackInDeathTableEv(c);
  }
  *(int*)(((int)*(char**)(c+0x438) + 0xb0)) &= ~0x4000000;
  *(int*)(((int)c + 0xb0)) &= ~0x4000000;
  data_0209b454 &= ~0x4000000;
  _ZN5Event8ClearBitEj(0x1e);
  _ZN5Event8ClearBitEj(0x1d);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 35 -- func_ov002_020e84ec, 0x020e84ec, size 0x12c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e84ecEv
/* recovered: shared common types, declarations from a shared header */
/* recovered: shared common types */
void daStar_c::func_ov002_020e84ec() {
    char* self = (char*)this;
    struct Vector3 v;
    s16* ang;
    int t;

    if (*(int*)(self + 0x43c) == 8) {
        Vec3_Asr(&v, (struct Vector3*)(self + 0x5c), 3);
        Matrix4x3_FromTranslation(self + 0x328, v.x, v.y, v.z);
    } else if (*(void**)(self + 0xc8) != 0) {
        /* M48 overlay: the class headers above switch Matrix4x3 to the
         * structured math/Matrix.h spelling, whose struct-copy codegen
         * differs from the flat 12-word copy this shard proved. M48 is the
         * same 12 words; proven byte-identical in isolation. */
        *(struct M48*)(self + 0x328) = *(struct M48*)(*(char**)(self + 0xc8));
    } else if (!((struct Flags*)(self + 0x4a2))->b0) {
        ang = (s16*)((int)(self + 0x8e));
        t = *ang + 0xc00;
        *ang = t;
        Matrix4x3_FromRotationY(self + 0x328, *(s16*)(self + 0x8e));
        *(int*)(self + 0x34c) = *(int*)(self + 0x5c) >> 3;
        *(int*)(self + 0x350) = *(int*)(self + 0x60) >> 3;
        *(int*)(self + 0x354) = *(int*)(self + 0x64) >> 3;
    } else {
        Matrix4x3_FromRotationY(self + 0x328, *(s16*)(self + 0x94));
        *(int*)(self + 0x34c) = *(int*)(self + 0x5c) >> 3;
        *(int*)(self + 0x350) = (*(int*)(self + 0x60) + 0x32000) >> 3;
        *(int*)(self + 0x354) = *(int*)(self + 0x64) >> 3;
    }

    *(struct M48*)(self + 0x38c) = *(struct M48*)(self + 0x328);
    ((daStar_c *)(self))->func_ov002_020e8398();
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 34 -- func_ov002_020e8398, 0x020e8398, size 0x154 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e8398Ev
/* recovered: shared common types */
void daStar_c::func_ov002_020e8398() {
    char * c = (char *)this;
    int r2, rad, delta, r8, t;
    int flag2;

    if ((((unsigned int)*(unsigned short *)(c + 0x400 + 0xa2) << 30) >> 31) == 0)
        return;
    flag2 = *(int *)(c + 0xb0) & 0x40000;
    flag2 = flag2 != 0;
    if (flag2 != false)
        return;
    {
        /* Volatile: see the note above -- forces the ROM's separate reload. */
        int v2 = *(volatile unsigned short *)(c + 0x400 + 0xa2);
        unsigned int v3 = (unsigned int)(v2 << 31);
        v3 = v3 >> 31;
        if (v3 != 0)
            return;
    }

    r2 = *(int *)(c + 0x80);
    rad = r2 * 0x64;
    flag2 = *(unsigned short *)(c + 0xc);
    flag2 = flag2 == 0xb2;
    if (flag2 != false)
        rad = r2 * 0xa0;

    delta = *(int *)(c + 0x60) - *(int *)(c + 0x42c);
    if (delta <= 0x1000)
        delta = 0x1000;

    r8 = rad - (int)(((s64)delta * 0x180 + 0x800) >> 12);
    if (r8 < 0xa000)
        r8 = 0xa000;

    t = delta + 0x28000;

    *(struct M48*)(c + 0x3fc) = *(struct M48*)&IDENTITY_MATRIX4X3;

    *(int *)(c + 0x420) = *(int *)(c + 0x5c) >> 3;
    *(int *)(c + 0x424) = *(int *)(c + 0x60) >> 3;
    *(int *)(c + 0x428) = *(int *)(c + 0x64) >> 3;

    _ZN8dActor_c19DropShadowRadHeightER17dExtShadowModel_cR9Matrix4x35Fix12IiES5_j(c, (struct dExtShadowModel_c *)(c + 0x3d4), (struct Matrix4x3 *)(c + 0x3fc), r8, t, 0xf);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 33 -- func_ov002_020e8244, 0x020e8244, size 0x154 */
/* -------------------------------------------------------------------------- */
// @symbol func_ov002_020e8244
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov002_020e8244(void* out, char* b)
{
    struct M48 local;
    struct V3 zero;
    zero.x = 0;
    zero.y = 0;
    zero.z = 0;
    if (func_0203d024((struct Vector3*)(b + 0x4a8), (struct Vector3*)&zero) != 0) {
        ((int *)out)[0] = *(int*)(b + 0x4a8);
        ((int *)out)[1] = *(int*)(b + 0x4ac);
        ((int *)out)[2] = *(int*)(b + 0x4b0);
        return;
    }
    Matrix4x3_FromTranslation(&data_020a0e68, *(int*)(b + 0x5c), *(int*)(b + 0x60), *(int*)(b + 0x64));
    Matrix4x3_ApplyInPlaceToRotationY(&data_020a0e68, *(s16*)(b + 0x94));
    local = *(struct M48*)(*(char**)(b + 0x320));
    MulMat4x3Mat4x3(&local, &data_020a0e68, &data_020a0e68);
    *(int*)(b + 0x4a8) = data_020a0e68.w[9];
    *(int*)(b + 0x4ac) = data_020a0e68.w[10];
    *(int*)(b + 0x4b0) = data_020a0e68.w[11];
    SubVec3((struct Vector3*)(b + 0x4a8), (struct Vector3*)(b + 0x5c), (struct Vector3*)(b + 0x4a8));
    Vec3_LslInPlace((void*)(b + 0x4a8), 3);
    AddVec3((struct Vector3*)(b + 0x4a8), (struct Vector3*)(b + 0x5c), (struct Vector3*)(b + 0x4a8));
    {
        int* p = (int*)((int)(b + 0x4ac));
        *p = *(int*)(*(char**)(b + 0x31c) + 0xc) * 0xd + *p;
    }
    ((int *)out)[0] = *(int*)(b + 0x4a8);
    ((int *)out)[1] = *(int*)(b + 0x4ac);
    ((int *)out)[2] = *(int*)(b + 0x4b0);
}
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 32 -- func_ov002_020e81e0, 0x020e81e0, size 0x64 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e81e0Ev
/* recovered: shared common types */
extern "C" void *_ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
    int a0, unsigned int a1, int a2, int a3, int a4, void *a5, void *a6);
/* Actor overlay for func_ov002_020e81e0 only (its legacy shard typed the
 * object with this local layout; other shards spell incompatible 'Obj'). */
struct ObjD {
    char pad5c[0x5c];
    int f5c;
    int f60;
    int f64;
    char pad68[0x4b4 - 0x68];
    void *f4b4;
};
void daStar_c::func_ov002_020e81e0() {
    char * s = (char *)this;
    ObjD *self = (ObjD *)s;
    Vector3 v;
    v.x = self->f5c;
    v.y = self->f60;
    v.z = self->f64;
    v.y += 0xd000;
    self->f4b4 = Particle::_ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(*(volatile unsigned int *)&self->f4b4, 0x113, *(volatile int *)&v.x, *(volatile int *)&v.y, v.z, 0, 0);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 31 -- func_ov002_020e8098, 0x020e8098, size 0x148 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e8098Ev
/* recovered: shared common types */
void daStar_c::func_ov002_020e8098() {
    char* self = (char*)this;
    Vector3 vc;
    Vector3 v;
    if (_ZN9Animation8FinishedEv(self + 0x35c)) return;
    func_ov002_020e8244(&v, self);
    vc.x = v.x;
    vc.y = v.y;
    vc.z = v.z;
    if (*(int*)(self + 0x440) != 0xd)
        vc.y = v.y + 0x32000;
    SubVec3(&vc, (Vector3*)(self + 0x5c), &vc);
    vc.x = (int)(((s64)vc.x * *(int*)(self + 0x80) + 0x800) >> 0xc);
    vc.y = (int)(((s64)vc.y * *(int*)(self + 0x84) + 0x800) >> 0xc);
    vc.z = (int)(((s64)vc.z * *(int*)(self + 0x88) + 0x800) >> 0xc);
    AddVec3(&vc, (Vector3*)(self + 0x5c), &vc);
    *(void**)(self + 0x4b4) = _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
        *(unsigned int*)(self + 0x4b4), 0x115, vc.x, vc.y, vc.z, 0, 0);
    *(void**)(self + 0x4b8) = _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
        *(unsigned int*)(self + 0x4b8), 0x116, vc.x, vc.y, vc.z, 0, 0);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 30 -- func_ov002_020e7fcc, 0x020e7fcc, size 0xcc */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e7fccEv
/* recovered: shared common types, declarations from a shared header */
/* recovered: shared common types */
void daStar_c::func_ov002_020e7fcc() {
    char* c = (char*)this;
    void* obj;
    struct Vector3 v1;
    struct Vector3 v2;

    obj = *(void**)(c + 0x31c);

    if (!_ZN9Animation8FinishedEv(c + 0x35c)
        && (u32)((*(u32*)(c + 0x364) << 4) >> 0x10) >= 2
        && *(int*)((char*)obj + 0xc) != 0) {
        func_ov002_020e8244(&v1, c);
        *(u32*)(c + 0x4b4) = (u32)_ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
            *(u32*)(c + 0x4b4), 0x2f, v1.x, v1.y, v1.z, 0, 0);
        return;
    }

    if (!_ZNK9Animation12WillHitFrameEi(c + 0x35c, 0x75)) return;
    func_ov002_020e8244(&v2, c);
    _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(0x30, v2.x, v2.y, v2.z);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 29 -- func_ov002_020e7f2c, 0x020e7f2c, size 0xa0 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e7f2cEv
void daStar_c::func_ov002_020e7f2c() {
    char* c = (char*)this;
    volatile s32 x, y, zvar;
    s32 z, yraw;

    if (*(u16 *)((char*)c + 0x400 + 0x94) == 0)
        return;
    (*(u16 *)(c + 0x494))--;
    if (*(u16 *)((char*)c + 0x400 + 0x94) == 0)
        *(u32 *)(c + 0x4bc) = 0;
    x = *(s32 *)(c + 0x5c);
    yraw = *(s32 *)(c + 0x60);
    y = yraw;
    {
        s32 zraw = *(s32 *)(c + 0x64);
        s32 yadj = yraw + 0xd000;
        z = zraw;
        zvar = zraw;
        y = yadj;
    }
    *(u32 *)(c + 0x4bc) = (u32)_ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
        *(volatile u32 *)(c + 0x4bc), 0x114, x, y, z, 0, 0);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 28 -- func_ov002_020e7eb8, 0x020e7eb8, size 0x74 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e7eb8Ev
/* recovered: shared common types */
#include "common.h"
void daStar_c::func_ov002_020e7eb8() {
    char* c = (char*)this;
  Vector3 v;
  int b = (*(unsigned short*)(c+0xc) == 0xb3);
  if (b == 0) return;
  func_ov002_020e8244(&v, c);
  *(int*)(c+0x4c0) = (int)_ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
    *(int*)(c+0x4c0), 0x10e, v.x, v.y, v.z, 0, 0);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 27 -- func_ov002_020e7eb4, 0x020e7eb4, size 0x4 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e7eb4Ev
void daStar_c::func_ov002_020e7eb4() {
    char * c = (char *)this;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 26 -- func_ov002_020e7e58, 0x020e7e58, size 0x5c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e7e58Ev
#include "fBase_c.h"

extern "C" {
char* _ZN8dActor_c10FindWithIDEj(unsigned int);
}

void daStar_c::func_ov002_020e7e58() {
    char* c = (char*)this;
  unsigned int id;
  void* a;
  if(*(unsigned char*)(c+0x49c)==0) return;
  id=*(unsigned int*)(c+0x430);
  if(id==0) return;
  a=_ZN8dActor_c10FindWithIDEj(id);
  if(a!=0){
    if(*(unsigned char*)(c+0x49c)==1) *(short*)((char*)a+0xde)=0;
    else ((fBase_c*)a)->MarkForDestruction();
  }
  *(int*)(c+0x430)=0;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 25 -- func_ov002_020e7e24, 0x020e7e24, size 0x34 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e7e24Ev
void daStar_c::func_ov002_020e7e24() {
    void * thiz = (void *)this;
    if (((struct ActorObj *)thiz)->obj != 0xff)
        return;
    if (_ZN8dActor_c13SpawnSoundObjEj(thiz, 6))
        ((struct ActorObj *)thiz)->obj = 0x78;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 24 -- func_ov002_020e7e14, 0x020e7e14, size 0x10 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e7e14Ev
/* func_ov002_020e7e14 at 0x020e7e14
 *
 * Matched byte-for-byte with mwccarm 1.2/sp2p3 (overlay ov002).
 */
int daStar_c::func_ov002_020e7e14() {
    char * r0 = (char *)this;
    *(unsigned char *)(r0 + 0x49e) = 0xff;
    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 23 -- _ZN12daStarBase_c7CollectEv, 0x020e7d84, size 0x90 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN12daStarBase_c7CollectEv
void daStarBase_c::Collect()
{
    func_02012694(0x53, (char *)this + 0x74);
    {
        unsigned char* f = &mFlags;
        *f = (*f & ~1) | 1;
        *f &= ~2;
    }
    _ZN5dCc_c5ClearEv((char *)&mdCcAcPos_c);
    _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(0x12c, mPosX, mPosY, mPosZ);
    _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(0x12d, mPosX, mPosY, mPosZ);
    _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(0x12e, mPosX, mPosY, mPosZ);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 22 -- func_ov002_020e7d08, 0x020e7d08, size 0x7c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e7d08Ev
/* recovered: shared common types */
void daStar_c::func_ov002_020e7d08() {
    void * s = (void *)this;
    Self *self = (Self *)s;
    dBgCh_Gnd rc;
    Vector3 v;
    v.x = self->x;
    v.y = self->y;
    v.z = self->z;
    v.y += 0x32000;
    rc.SetObjAndPos(v, 0);
    rc.mProbeHeight = 0x3e8000;
    if (rc.DetectClsn())
        *(int*)((char*)self + 0x42c) = rc.clsnY;
    else
        *(int*)((char*)self + 0x42c) = 0x7fffffff;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 21 -- func_ov002_020e7c90, 0x020e7c90, size 0x78 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e7c90EPv
extern "C" {
extern void _ZN6Camera9SetLookAtERK7Vector3(void* cam, void* v);
extern void _ZN6Camera6SetPosERK7Vector3(void* cam, void* v);
}

int daStar_c::func_ov002_020e7c90(void* cam) {
    char* c = (char*)this;
  char* a = 0;
  for(;;){
    a = (char *)_ZN8dActor_c15FindWithActorIDEjPS_(0xb1, a);
    if(a == 0) break;
    if(*(unsigned char*)(c+0x49d) == (*(unsigned int*)(a+8) & 0xf)){
      _ZN6Camera9SetLookAtERK7Vector3(cam, c+0x5c);
      _ZN6Camera6SetPosERK7Vector3(cam, a+0x5c);
      return 1;
    }
  }
  return 0;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 20 -- func_ov002_020e7934, 0x020e7934, size 0x35c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e7934EPv
/* recovered: shared common types */
void daStar_c::func_ov002_020e7934(void* cam) {
    char* self = (char*)this;
    Vector3 vec[2];
    int flag;
    int dist;
    unsigned int r6 = 0;

    vec[0].x = *(int*)(self + 0x5c);
    vec[0].y = *(int*)(self + 0x60);
    vec[0].z = *(int*)(self + 0x64);
    _ZN6Camera9SetLookAtERK7Vector3(cam, &vec[0]);

    vec[0].y += 0xc8000;
    vec[1] = vec[0];
    dist = Vec3_Dist(&vec[0], (Vector3*)(self + 0x46c));

    unsigned short mode = *(unsigned short*)(self + 0x496);
    flag = (((mode == 100 && (dist > 0x3e8000 || dist < 0x1f4000)) ||
             (mode != 100 && dist > 0x3e8000)) &&
            IsAreaShowing(*(signed char*)(self + 0x499))) ? 1 : 0;

    while (1) {
        if (r6 >= 0x10)
            vec[0].y -= 0x258000;
        else if (r6 >= 0xc)
            vec[0].y -= 0x12c000;
        else if (r6 >= 8)
            vec[0].y += 0x258000;
        else if (r6 >= 4)
            vec[0].y += 0x12c000;

        if (flag) {
            short ang = Vec3_HorzAngle(&vec[0], (Vector3*)(self + 0x46c));
            int k = (unsigned short)(short)(ang + ((r6 & 3) << 14)) >> 4;
            vec[0].x = data_02082214[k * 2] * 1000 + vec[0].x;
            vec[0].z = data_02082214[k * 2 + 1] * 1000 + vec[0].z;
            _ZN6Camera6SetPosERK7Vector3(cam, &vec[0]);
        } else {
            if (!IsAreaShowing(*(signed char*)(self + 0xcc)))
                return;
            short ang = Vec3_HorzAngle(&vec[0], (Vector3*)(self + 0x46c));
            int k = (unsigned short)(short)(ang + ((r6 & 3) << 14)) >> 4;
            vec[0].x += (int)(((long long)dist * data_02082214[k * 2] + 0x800) >> 12);
            vec[0].z += (int)(((long long)dist * data_02082214[k * 2 + 1] + 0x800) >> 12);
            _ZN6Camera6SetPosERK7Vector3(cam, &vec[0]);
        }

        if (!IsAreaShowing(*(signed char*)(self + 0xcc)))
            return;

        {
            dBgCh_Lin rl;
            Vector3 a;
            Vector3 b;
            a.x = *(int*)(self + 0x5c);
            a.y = *(int*)(self + 0x60);
            a.z = *(int*)(self + 0x64);
            b.x = vec[0].x;
            b.y = vec[0].y;
            b.z = vec[0].z;
            rl.SetObjAndLine(a, b, (dActor_c*)self);
            if (rl.DetectClsn()) {
                r6 = (r6 + 1) & 0xff;
                vec[0] = vec[1];
                if (r6 >= 0x14) {
                    _ZN6Camera6SetPosERK7Vector3(cam, (Vector3*)(self + 0x46c));
                    return;
                }
                continue;
            }
            return;
        }
    }
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 19 -- func_ov002_020e763c, 0x020e763c, size 0x2f8 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e763cEv
void daStar_c::func_ov002_020e763c() {
    char * self = (char *)this;
    Vec3 v;
    void *cam;

    if ((data_0209b454 & 0x4000000) == 0)
        return;

    if (((SubSt *)(self + 0x400))->state == 0xffff)
        return;

    v.x = *(int *)(self + 0x5c);
    cam = data_0209f318;
    v.y = *(int *)(self + 0x60);
    v.z = *(int *)(self + 0x64);

    switch (((SubSt *)(self + 0x400))->state) {
    case 0:
    {
        int *s1 = (int *)(((int)cam + 0x80));
        int *s2 = (int *)(((int)cam + 0x8c));
        *(int *)(self + 0x460) = s1[0];
        *(int *)(self + 0x464) = s1[1];
        *(int *)(self + 0x468) = s1[2];
        *(int *)(self + 0x46c) = s2[0];
        *(int *)(self + 0x470) = s2[1];
        *(int *)(self + 0x474) = s2[2];
    }
        ((daStar_c *)(self))->func_ov002_020e7c90(cam);
        _ZN6Camera9SetFlag_3Ev(cam);
        if (((daStar_c *)(self))->func_ov002_020e7c90(cam) == 0)
            ((daStar_c *)(self))->func_ov002_020e7934(cam);
        *(u16 *)(((int)self + 0x496)) += 1;
        break;
    case 1:
        if (*(int *)(self + 0x440) != 2)
            return;
        _ZN6Camera9SetLookAtERK7Vector3(cam, &v);
        break;
    case 0x64:
    {
        int *s1 = (int *)(((int)cam + 0x80));
        int *s2 = (int *)(((int)cam + 0x8c));
        *(int *)(self + 0x460) = s1[0];
        *(int *)(self + 0x464) = s1[1];
        *(int *)(self + 0x468) = s1[2];
        *(int *)(self + 0x46c) = s2[0];
        *(int *)(self + 0x470) = s2[1];
        *(int *)(self + 0x474) = s2[2];
    }
        _ZN6Camera9SetFlag_3Ev(cam);
        if (((daStar_c *)(self))->func_ov002_020e7c90(cam) == 0)
            ((daStar_c *)(self))->func_ov002_020e7934(cam);
        *(u16 *)(((int)self + 0x496)) += 1;
        break;
    case 0x65:
        _ZN6Camera9SetLookAtERK7Vector3(cam, &v);
        if (*(int *)(self + 0x80) == 0x1000 || *(int *)(self + 0x80) == 0)
            ((SubSt *)(self + 0x400))->state = 0x1b6;
        break;
    case 0x1f4:
        _ZN6Camera9SetLookAtERK7Vector3(cam, (Vec3 *)(self + 0x460));
        _ZN6Camera6SetPosERK7Vector3(cam, (Vec3 *)(self + 0x46c));
        *(u16 *)(((int)self + 0x496)) += 1;
        break;
    case 0x1f5:
        *(int *)(((int)cam + 0x154)) &= ~8;
        *(int *)(((int)self + 0xb0)) &= ~0x4000000;
        data_0209b454 &= ~0x4000000;
        ((SubSt *)(self + 0x400))->state = 0xffff;
        *(s8 *)(self + 0xcc) = ((SubSt *)(self + 0x400))->flag;
        break;
    default:
        *(u16 *)(((int)self + 0x496)) += 1;
        break;
    }
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 18 -- func_ov002_020e7554, 0x020e7554, size 0xe8 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e7554Ev
void daStar_c::func_ov002_020e7554() {
    void * s = (void *)this;
    char *c = (char *)s;
    char* found;
    char* arr[5] = {0};
    int cnt;
    unsigned int idx;

    found = 0;
    cnt = 0;
    do {
        found = (char *)_ZN8dActor_c15FindWithActorIDEjPS_(0xb4, found);
        if (found == 0) break;
        if ((*(u8*)(found + 0x1d8) == 3 && _ZN8dActor_c10FindWithIDEj(*(u32*)(found + 0x1cc)) == 0) ||
            (*(u8*)(found + 0x1d8) != 0 && (unsigned int)(*(u8*)(found + 0x1db) << 0x1f) >> 0x1f &&
             _ZN8dActor_c10FindWithIDEj(*(u32*)(found + 0x1cc)) == 0)) {
            arr[cnt] = found;
            cnt++;
        }
    } while (cnt < 5);

    idx = ((unsigned int)RandomIntInternal(&data_0209e650) >> 16) % (unsigned int)cnt;
    found = arr[idx];
    if (found == 0) return;
    *(u32*)(c + 0x434) = *(u32*)(found + 4);
    ((daStarBase_c *)(found))->LinkSilverStarAndStarMarker(c);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 17 -- func_ov002_020e7454, 0x020e7454, size 0x100 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e7454Ev
void daStar_c::func_ov002_020e7454() {
    char* self = (char*)this;
    char* a = _ZN8dActor_c10FindWithIDEj(*(unsigned int*)(self + 0x434));
    int* s;
    *(unsigned short*)((int)((unsigned long long)(unsigned)(self + 0x4a2))) &= ~0x30;
    s = (int*)((int)(a + 0x5c));
    *(int*)(self + 0x5c) = s[0];
    *(int*)(self + 0x60) = s[1];
    *(int*)(self + 0x64) = s[2];
    func_02035860(self + 0x150, self + 0x5c);
    if (*(unsigned char*)(a + 0x1d8) == 3) {
        *(int*)(self + 0x444) = *(unsigned char*)(a + 0x1da);
        *(int*)(self + 0x440) = *(int*)(self + 0x444);
        if (*(int*)(self + 0x440) != 4) return;
        ((daStar_c *)(self))->func_ov002_020e9464();
    } else {
        unsigned short* f;
        a = (char*)((int)(a + 0x1db));
        *(unsigned char*)a &= ~1;
        *(unsigned char*)a |= 2;
        *(int*)(self + 0x440) = 9;
        *(int*)((int)(self + 0x128)) |= 1;
        f = (unsigned short*)((int)(self + 0x4a2));
        *f &= ~2;
        *f |= 8;
    }
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 16 -- func_ov002_020e73ac, 0x020e73ac, size 0xa8 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e73acEv
// func_ov002_020e73ac at 0x020e73ac
// Matched byte-for-byte with mwccarm 1.2/sp2p3 (ov002).
int daStar_c::func_ov002_020e73ac() {
    char* arg = (char*)this;
    int c, a, b;
    unsigned char r2 = *(unsigned char*)(arg + 0x49d);
    if (r2 == 8) {
        return 3;
    }

    a = data_0209f2d8 == 1;
    if (a != false) {
        goto ret2;
    }
    b = *(unsigned short*)(arg + 0xc) == 0xb3;
    if (b != false) {
        goto ret2;
    }
    c = *(int*)(arg + 0x444);
    if (c == 9) {
ret2:
        return 2;
    }

    if (r2 == 0) {
        goto ret1;
    }
    if (((daStar_c *)(arg))->func_ov002_020e9630() == 0) {
        goto ret0;
    }
ret1:
    return 1;
ret0:
    return 0;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 15 -- _ZN12daStarBase_c27SpawnRedCoinStarIfNecessaryEv, 0x020e72d8, size 0xd4 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN12daStarBase_c27SpawnRedCoinStarIfNecessaryEv
/* recovered: named members + shared header, real C++ method */
void daStarBase_c::SpawnRedCoinStarIfNecessary()
{
  struct Vec3 v;
  char* star;
  int y;
  if(((unsigned int)mFlags << 29) >> 31) return;
  if(NumRedCoins() != 8) return;
  v.x = mPosX;
  y = mPosY;
  v.y = y;
  v.z = mPosZ;
  v.y = y + 0x78000;
  star = (char*)_ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as(0xb2, mStarID, &v, 0, mAreaId, -1);
  if(star == 0) return;
  ((daStar_c *)star)->AddStarMarker();
  *(unsigned short*)(((int)star + 0x4a2)) |= 0x1000;
  *(int*)(star+0x434) = uniqueID;
  *(unsigned char*)(((int)((char*)this) + 0x1db)) |= 4;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 14 -- func_ov002_020e7218, 0x020e7218, size 0xc0 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e7218EPci
/* recovered: shared common types, declarations from a shared header */
/* recovered: shared common types */
void daStar_c::func_ov002_020e7218(char* a, int gate) {
    char* c = (char*)this;
    if (gate == 0) {
        struct Vector3 pos[2];
        int b;
        int* v;
        v = (int*)((int)(a + 0x5c));
        pos[0].x = v[0];
        pos[0].y = v[1];
        pos[0].z = v[2];
        b = (*(unsigned short*)(c + 0xc) != 0xb2);
        b = (b != 0);
        pos[0].y = pos[0].y + 0xc8000;
        pos[1].x = pos[0].x;
        pos[1].z = pos[0].z;
        pos[1].y = pos[0].y;
        _ZN8dActor_c11SpawnNumberERK7Vector3jbtPS_(c, &pos[1], data_0209f310[*(unsigned char*)(a + 0x6d8)], b, 0x15, a);
    }
    *(unsigned short*)((int)(c + 0x4a2)) |= 0x40;
    ((daStar_c *)(c))->func_ov002_020e7554();
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 13 -- LinkSilverStarAndStarMarker, 0x020e71d4, size 0x44 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN12daStarBase_c27LinkSilverStarAndStarMarkerEPc
void daStarBase_c::LinkSilverStarAndStarMarker(char* b) {
    char* a = (char*)this;
  if (b != 0) {
    *(int*)(a + 0x1cc) = *(int*)(b + 4);
    *(unsigned char*)(a + 0x1da) = *(int*)(b + 0x440);
    short s = *(short*)(b + 0xce);
    if (s >= 0) *(short*)(a + 0x1d6) = s;
  } else {
    *(short*)(a + 0x1d6) = -1;
    *(int*)(a + 0x1cc) = 0;
  }
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 12 -- LoadSilverStarAndNumber, 0x020e71a8, size 0x2c */
/* -------------------------------------------------------------------------- */
// @symbol LoadSilverStarAndNumber
extern "C" {  /* .c-derived member: C linkage for the whole block */
void LoadSilverStarAndNumber(void)
{
    _ZN5Model8LoadFileER13SharedFilePtr(data_ov002_0210da28);
    _ZN5Model8LoadFileER13SharedFilePtr(&data_ov002_02110954);
}
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 11 -- UnloadSilverStarAndNumber, 0x020e717c, size 0x2c */
/* -------------------------------------------------------------------------- */
// @symbol UnloadSilverStarAndNumber
extern "C" {  /* .c-derived member: C linkage for the whole block */
void UnloadSilverStarAndNumber(void)
{
    _ZN13SharedFilePtr7ReleaseEv(data_ov002_0210da28);
    _ZN13SharedFilePtr7ReleaseEv(&data_ov002_02110954);
}
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 10 -- func_ov002_020e7104, 0x020e7104, size 0x78 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e7104Ei
/* The +0x496 store goes through byte-pointer arithmetic: with `(int)c + 0x496`
   mwcc materializes the offset from the literal pool and stores with a register
   index (strh r3,[r0,r1]); the cartridge splits it as add r0,r0,#0x400 /
   strh r1,[r0,#0x96]. The old u64 masks on the other three accesses were not
   load-bearing and are gone. */
void daStar_c::func_ov002_020e7104(int r1){
  void *s = this;
  char *c = (char *)s;
  if(r1==0){
    *(unsigned short*)(c + 0x4A2) &= ~0x100;
    if(data_0209b454 & 0x4000000) return;
    *(unsigned int*)(c + 0xB0) |= 0x4000000;
    data_0209b454 |= 0x4000000;
    *(unsigned short*)(c + 0x496) = 0x64;
    return;
  }
  *(unsigned short*)(c + 0x4A2) |= 0x100;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 9 -- func_ov002_020e7090, 0x020e7090, size 0x74 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e7090Ei
extern "C" {
extern void func_02012790(int a);
}

void daStar_c::func_ov002_020e7090(int arg) {
    char* c = (char*)this;
  *(int*)(c+0x438) = arg;
  *(int*)((*(int*)(c+0x438)+0xb0)) |= 0x4000000;
  *(int*)(((int)c+0xb0)) |= 0x4000000;
  data_0209b454 |= 0x4000000;
  ((daStar_c *)(c))->func_ov002_020e6fbc(0);
  *(unsigned char*)(c+0x49c) = 1;
  ((daStar_c *)(c))->func_ov002_020e9464();
  CollectStarInCurLevel(*(unsigned char*)(c+0x49d));
  func_02012790(0x2d);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 8 -- func_ov002_020e700c, 0x020e700c, size 0x84 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e700cEv
void daStar_c::func_ov002_020e700c() {
    char* c = (char*)this;
  void* o;
  if (*(unsigned char*)((char*)c+0x4a0)) return;
  o = _ZN8dActor_c15FindWithActorIDEjPS_(0x12, 0);
  while (o) {
    if (Vec3_Dist((char*)c+0x5c, (char*)o+0x5c) < 0xc8000) {
      *(unsigned char*)((char*)c+0x49f) = 1;
      *(void**)((char*)o+0x364) = c;
      break;
    }
    o = _ZN8dActor_c15FindWithActorIDEjPS_(0x12, o);
  }
  *(unsigned char*)((char*)c+0x4a0) = 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 7 -- func_ov002_020e6fbc, 0x020e6fbc, size 0x50 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e6fbcEi
extern "C" {
}

void daStar_c::func_ov002_020e6fbc(int arg) {
    char* c = (char*)this;
  if (*(void**)(c+0x430) != 0) return;
  char* s = _ZN8dActor_c13SpawnSoundObjEj(c, 4);
  if (s == 0) return;
  *(void**)(c+0x430) = *(void**)(s+4);
  *(int*)(s+0xd4) = ((daStar_c *)(c))->func_ov002_020ea3a4();
  *(int*)(s+0xd8) = arg;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 6 -- func_ov002_020e6edc, 0x020e6edc, size 0xe0 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e6edcEv
/* recovered: shared common types */
void daStar_c::func_ov002_020e6edc() {
    void * s = (void *)this;
    char *c = (char *)s;
    struct Vector3 v;
    u16* p;
    *(int*)(c+0x43c) = 8;
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c+0x30c, *(struct BCA_File**)(data_ov002_02110934+4), 0x40000000, 0x1000, 0);
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c+0x370, *(struct BCA_File**)(data_ov002_02110934+4), 0x40000000, 0x1000, 0);
    v.x = data_ov002_0210aa0c[0];
    v.y = data_ov002_0210aa0c[1];
    v.z = data_ov002_0210aa0c[2];
    _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj(c+0x110, (struct dActor_c*)c, &v, 0x64000, 0x96000, 1, 0);
    *(int*)(c+0x440) = 0xc;
    p = (u16*)(((int)c + 0x4a2));
    *p = (*p & ~1) | 1;
    *p |= 2;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 5 -- func_ov002_020e6df8, 0x020e6df8, size 0xe4 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e6df8Ev
// @symbol _ZN8daStar_c19func_ov002_020e6df8Ev
/* recovered: shared common types */
#include "common.h"
typedef int Fix12i;

struct BCA_File;
struct dActor_c;

extern int data_ov002_0210aa0c[3];

void daStar_c::func_ov002_020e6df8() {
    void * s = (void *)this;
  char *c = (char *)s;
  *(int*)(c + 0x43c) = 9;
  _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x30c, data_ov002_02110944.b, 0x40000000, 0x1000, 0);
  _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0x370, data_ov002_02110944.b, 0x40000000, 0x1000, 0);
  {
    Vector3 v;
    v.x = data_ov002_0210aa0c[0];
    v.y = data_ov002_0210aa0c[1];
    v.z = data_ov002_0210aa0c[2];
    _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj(
      c + 0x110, c, &v, 0x64000, 0x96000, 1, 0);
  }
  {
    unsigned short* p = (unsigned short*)(((int)c + 0x4a2));
    *p = (*p & ~1) | 1;
    *p = *p | 2;
  }
  *(unsigned char*)(c + 0x49d) = 6;
  *(int*)(c + 0x440) = 6;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 4 -- func_ov002_020e6d88, 0x020e6d88, size 0x70 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8daStar_c19func_ov002_020e6d88Ev
void daStar_c::func_ov002_020e6d88() {
    void* c = (void*)this;
  *(int*)((char*)c+0x80) = 0;
  *(int*)((char*)c+0x84) = 0;
  *(int*)((char*)c+0x88) = 0;
  *(unsigned short*)((int)c + 0x4a2) &= ~0x100;
  _ZN8dActor_c11UntrackStarERa(c, (signed char*)((int)c + 0x498));
  c = (void*)(int)(c);
  *(unsigned short*)((int)c + 0x4a2) &= ~0x200;
  *(unsigned short*)((char*)c+0x492) = 0;
  *(unsigned short*)((char*)c+0x100) = 0;
}

/* daStarBase_c's destructor is inline in the header. Out of line it emits
 * D2, D0, D1 and defer_codegen off does not flip it. An odr-use of delete
 * then the explicit destructor emits D1 then D0 immediately below this
 * function, which is what the cartridge has at 0x020e6cf4. The function
 * itself is not in the ROM. */
// @symbol _ZN12daStarBase_cD1Ev
// @symbol _ZN12daStarBase_cD0Ev
void force_daStarBase_c_dtor_order() {
    daStarBase_c *p = 0;
    delete p;
    p->~daStarBase_c();
    func_02012790(0);
}
