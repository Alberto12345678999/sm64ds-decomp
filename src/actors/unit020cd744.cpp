//cpp
/*
 * ov006 .text 0x020cd744..0x020cf2fc, 39 functions: the lower part of the
 * linker unit that runs 0x020cd744..0x020d1018. It starts where the promoted
 * dMgTrmpln2Mario_c TU ends. The ROM carries no RTTI, vtable or static
 * initialiser that names a type in this run, and no source or note names it,
 * so it keeps the unit<addr> name and the functions keep their address names.
 *
 * Where the claim stops: the unit continues past 0x020cf2fc, but
 * func_ov006_020cf2fc (0x45c) does not match yet, so it stays cartridge bytes
 * and this file stops below it. The 19 functions above it (0x020cf758 to
 * 0x020d1018, func_ov006_020d01e0 among them) stay one-function sources until
 * it matches.
 *
 * Data the run touches: globals the dMgTrmpln2Mario_c TU also uses
 * (0x021405a8..0x021405b4), the score words d_s_mg_trampoline2 also uses
 * (0x02140818, 0x02140828, 0x02140830), its own bss 0x02140808..0x0214095c
 * (function-local statics with guard words), and words in 0x0212e070..0x0212e0f0
 * and 0x0213b31c..0x0213b3a4.
 *
 * Folded from 39 one-function shards, func_ov006_020cd744 through
 * func_ov006_020cf124. Their provenance is the same as any other loose shard
 * here: each was matched on its own against the pinned compiler. The
 * boundaries inside the run could not be proven, so it is folded as the part
 * of the tu_map unit below the unmatched function.
 *
 * Layout of this file: each former one-function source keeps its own
 * namespace block, because their local struct views and extern declarations
 * disagree with each other and unifying them changes code generation. The
 * functions and the externs they use are extern "C", so the namespaces change
 * no symbol. Definitions are in ROM order, lowest address first, under
 * defer_codegen off. func_ov006_020cdc8c keeps its opt_propagation off and
 * func_ov006_020cf124 its opt_strength_reduction off as push/pop brackets.
 *
 * The empty Vector3 destructor from include/types.h is emitted here for the
 * Vector3 locals; it is licensed as a deadstrip duplicate of the arm9 copy.
 */
#include "types.h"
#include "decl_common.h"
#include "common.h"

#pragma defer_codegen off

extern int ApproachLinear(int &, int, int);
struct BMD_File; struct BTA_File;
struct ModelBase { void SetFile(BMD_File*, int, int); };
struct Model : ModelBase { void SetPolygonID(int); };
struct TextureTransformer { static void Prepare(BMD_File&, BTA_File&); void SetFile(BTA_File&, int, int, unsigned int); };

// ---- func_ov006_020cd744.c ----
namespace s020cd744 {
extern "C" extern void _Z14ApproachLinearRiii(int* a, int b, int c);
extern "C" extern int _Z15ApproachLinear2Riii(int* a, int b, int c);
extern "C" {extern int data_ov006_02140828;}

extern "C" void func_ov006_020cd744(char* c) {
    _Z14ApproachLinearRiii((int*)(c + 0x68), 0x1200, 0x80);
    _Z14ApproachLinearRiii((int*)(c + 0x70), 0x1200, 0x80);
    _Z14ApproachLinearRiii((int*)(c + 0x6c), 0x20000, 0x400);
    if (_Z15ApproachLinear2Riii((int*)(c + 0x9c), 0, 1) == 0) return;
    *(int*)(c + 0x84) = 0;
    _Z14ApproachLinearRiii(&data_ov006_02140828, 0, 1);
}
}

// ---- func_ov006_020cd7b8.c ----
namespace s020cd7b8 {
extern "C" extern void func_ov006_020bfff8(void* a, void* b, int* c, int* d);
extern "C" extern int func_ov004_020b04c0(void);
extern "C" extern void func_ov006_020ef05c(int a, int b, int c);
extern "C" {extern void* data_ov006_02141a50;}
extern "C" {extern void* data_ov006_02141a40;}
struct P2 { int w[2]; };
extern "C" {extern struct P2 data_ov006_0213b32c;}

extern "C" void func_ov006_020cd7b8(char* c, int arg1)
{
    int v0, v1;
    if (*(int*)(c + 0xc) > 0) {
        func_ov006_020bfff8(data_ov006_02141a50, (void*)(c + 8), &v0, &v1);
        v1 = v1 - (func_ov004_020b04c0() + 0xc0);
    } else {
        func_ov006_020bfff8(data_ov006_02141a40, (void*)(c + 8), &v0, &v1);
    }
    func_ov006_020ef05c(v0 << 0xc, v1 << 0xc, (short)arg1);
    *(struct P2*)c = data_ov006_0213b32c;
}
}

// ---- func_ov006_020cd864.c ----
namespace s020cd864 {
// @symbol func_ov006_020cd864
/* recovered: shared common types, declarations from a shared header */
/* recovered: shared common types */
extern "C" extern void *_ZN7Vector3D1Ev(void *object);

extern "C" extern void func_020731dc(void *object, void *destructor, void **node);

extern "C" void func_ov006_020cd864(char* arg) {
  struct Vector3 a;
  struct Vector3 b;
  struct Vector3 c;
  if ((data_ov006_02140820 & 1) == 0) {
    data_ov006_02140938.x = 0;
    data_ov006_02140938.y = 0x1000;
    data_ov006_02140938.z = 0;
    func_020731dc(&data_ov006_02140938, (void *)_ZN7Vector3D1Ev, &data_ov006_02140920);
    data_ov006_02140820 |= 1;
  }
  if ((data_ov006_02140840 & 1) == 0) {
    data_ov006_02140884.x = 0;
    data_ov006_02140884.y = 0;
    data_ov006_02140884.z = 0x1000;
    func_020731dc(&data_ov006_02140884, (void *)_ZN7Vector3D1Ev, &data_ov006_0214086c);
    data_ov006_02140840 |= 1;
  }
  func_0203cc28((int*)(arg + 0x38), 0x100);
  func_0203ce80(&a, (struct Vector3*)(arg + 0x38));
  func_0203cf00(&b, (struct Vector3*)(arg + 0x38), &data_ov006_02140884);
  *(int*)(arg + 0x44) = b.x;
  *(int*)(arg + 0x48) = b.y;
  *(int*)(arg + 0x4c) = b.z;
  func_0203ce80(&c, (struct Vector3*)(arg + 0x44));
  Quaternion_FromVector3((int*)(arg + 0x74), &data_ov006_02140938, (struct Vector3*)(arg + 0x38));
  Quaternion_Normalize((int*)(arg + 0x74));
  func_ov006_020cdc38(arg);
}
}

// ---- func_ov006_020cd98c.c ----
namespace s020cd98c {
struct S{int w[2];};
extern "C" {extern struct S data_ov006_0213b36c;}
extern "C" void func_ov006_020cd98c(int *c){
  *(short*)((char*)c+0x9a)=0;
  *(struct S*)c=data_ov006_0213b36c;
}
}

// ---- func_ov006_020cd9b0.c ----
namespace s020cd9b0 {
typedef struct { int x, y, z; } Vec3;
extern "C" extern void func_020731dc(void *object, void *destructor, void **node);
extern "C" extern void func_0203cc28(int *p, int angle);
extern "C" extern void func_0203ce80(Vec3* dst, Vec3* src);
extern "C" extern void func_0203cf00(Vec3 *out, Vec3 *a, Vec3 *b);
extern "C" extern void Quaternion_FromVector3(int* q, Vec3* axis, Vec3* v);
extern "C" extern void Quaternion_Normalize(int *q);
extern "C" extern void *_ZN7Vector3D1Ev(void *object);

extern "C" {extern int data_ov006_02140834;}
extern "C" {extern Vec3 data_ov006_021408c0;}
extern "C" {extern int data_ov006_021408b4;}
extern "C" {extern int data_ov006_0214083c;}
extern "C" {extern Vec3 data_ov006_021408e4;}
extern "C" {extern int data_ov006_021408d8;}

extern "C" void func_ov006_020cd9b0(char* self)
{
    Vec3 a, b, c, d;

    if (!(data_ov006_02140834 & 1)) {
        data_ov006_021408c0.x = 0;
        data_ov006_021408c0.y = 0x1000;
        data_ov006_021408c0.z = 0;
        func_020731dc(&data_ov006_021408c0, (void *)&_ZN7Vector3D1Ev, (void**)&data_ov006_021408b4);
        data_ov006_02140834 |= 1;
    }
    if (!(data_ov006_0214083c & 1)) {
        data_ov006_021408e4.x = 0;
        data_ov006_021408e4.y = 0;
        data_ov006_021408e4.z = 0x1000;
        func_020731dc(&data_ov006_021408e4, (void *)&_ZN7Vector3D1Ev, (void**)&data_ov006_021408d8);
        data_ov006_0214083c |= 1;
    }
    func_0203cc28((int*)(self + 0x38), 0x100);
    func_0203ce80(&a, (Vec3*)(self + 0x38));
    func_0203cf00(&b, (Vec3*)(self + 0x38), &data_ov006_021408e4);
    *(int*)(self + 0x44) = b.x;
    *(int*)(self + 0x48) = b.y;
    *(int*)(self + 0x4c) = b.z;
    func_0203ce80(&c, (Vec3*)(self + 0x44));
    Quaternion_FromVector3((int*)(self + 0x74), &data_ov006_021408c0, (Vec3*)(self + 0x38));
    Quaternion_Normalize((int*)(self + 0x74));
}
}

// ---- func_ov006_020cdad0.c ----
namespace s020cdad0 {
struct S { int w[2]; };
extern "C" {extern struct S data_ov006_0213b31c;}
extern "C" void func_ov006_020cdad0(char *p) { *(struct S *)(p + 0x0) = data_ov006_0213b31c; }
}

// ---- func_ov006_020cdaec.c ----
namespace s020cdaec {
// @symbol func_ov006_020cdaec
/* recovered: shared common types, declarations from a shared header */
/* recovered: shared common types */
extern "C" extern void *_ZN7Vector3D1Ev(void *object);

extern "C" extern void func_020731dc(void *object, void *destructor, void **node);

extern "C" void func_ov006_020cdaec(char* arg) {
  struct Vector3 a;
  struct Vector3 b;
  struct Vector3 c;
  if ((data_ov006_02140808 & 1) == 0) {
    data_ov006_02140860.x = 0;
    data_ov006_02140860.y = 0x1000;
    data_ov006_02140860.z = 0;
    func_020731dc(&data_ov006_02140860, (void *)_ZN7Vector3D1Ev, &data_ov006_0214095c);
    data_ov006_02140808 |= 1;
  }
  if ((data_ov006_02140810 & 1) == 0) {
    data_ov006_02140890.x = 0;
    data_ov006_02140890.y = 0;
    data_ov006_02140890.z = 0x1000;
    func_020731dc(&data_ov006_02140890, (void *)_ZN7Vector3D1Ev, &data_ov006_02140878);
    data_ov006_02140810 |= 1;
  }
  func_0203cc28((int*)(arg + 0x38), 0x100);
  func_0203ce80(&a, (struct Vector3*)(arg + 0x38));
  func_0203cf00(&b, (struct Vector3*)(arg + 0x38), &data_ov006_02140890);
  *(int*)(arg + 0x44) = b.x;
  *(int*)(arg + 0x48) = b.y;
  *(int*)(arg + 0x4c) = b.z;
  func_0203ce80(&c, (struct Vector3*)(arg + 0x44));
  Quaternion_FromVector3((int*)(arg + 0x74), &data_ov006_02140860, (struct Vector3*)(arg + 0x38));
  Quaternion_Normalize((int*)(arg + 0x74));
  func_ov006_020cdc8c(arg);
}
}

// ---- func_ov006_020cdc14.c ----
namespace s020cdc14 {
struct S{int w[2];}; extern "C" {extern struct S data_ov006_0213b394;}
extern "C" void func_ov006_020cdc14(char*c){*(short*)(c+0x9a)=0x2000;*(struct S*)c=data_ov006_0213b394;}
}

// ---- func_ov006_020cdc38.c ----
namespace s020cdc38 {
extern "C" void func_ov006_020cdc38(void *arg0)
{
    *(u16 *)((char *)arg0 + 0x9a) += 0x100;
    if (*(u16 *)((char *)arg0 + 0x9a) & 0x8000) {
        *(s32 *)((char *)arg0 + 0x30) = 0xc00;
    } else {
        *(s32 *)((char *)arg0 + 0x30) = -0xc00;
    }
}
}

// ---- func_ov006_020cdc68.c ----
namespace s020cdc68 {
struct S{int w[2];}; extern "C" {extern struct S data_ov006_0213b38c;}
extern "C" void func_ov006_020cdc68(char*c){*(short*)(c+0x9a)=0;*(struct S*)c=data_ov006_0213b38c;}
}

// ---- func_ov006_020cdc8c.c ----
namespace s020cdc8c {
extern "C" extern int _ZN4cstd4fdivEii(int a, int b);

#pragma push
#pragma opt_propagation off
extern "C" void func_ov006_020cdc8c(char *self)
{
    int d;
    int v;
    int base = 0x400;
    u16 *pa = (u16 *)(self + 0x9a);

    *pa = *pa + 0x40;

    d = *(s32 *)(self + 0xc) - 0x74000;
    if (d < 0)
        d = -d;
    v = (_ZN4cstd4fdivEii(d, 0x4c000) >> 3) + base;

    if (*(u16 *)(self + 0x9a) & 0x4000)
        *(s32 *)(self + 0x2c) = v;
    else
        *(s32 *)(self + 0x2c) = -v;
}
#pragma pop
}

// ---- func_ov006_020cdce4.c ----
namespace s020cdce4 {
struct S{int w[2];}; extern "C" {extern struct S data_ov006_0213b384;}
extern "C" void func_ov006_020cdce4(char*c){*(short*)(c+0x9a)=0x2000;*(struct S*)c=data_ov006_0213b384;}
}

// ---- func_ov006_020cdd08.c ----
namespace s020cdd08 {
typedef struct { int x, y, z; } Vec3;
extern "C" extern void func_020731dc(void *object, void *destructor, void **node);
extern "C" extern void func_0203cc28(int *p, int angle);
extern "C" extern void func_0203ce80(Vec3* dst, Vec3* src);
extern "C" extern void func_0203cf00(Vec3 *out, Vec3 *a, Vec3 *b);
extern "C" extern void Quaternion_FromVector3(int* q, Vec3* axis, Vec3* v);
extern "C" extern void Quaternion_Normalize(int *q);
extern "C" extern void *_ZN7Vector3D1Ev(void *object);

extern "C" {extern int data_ov006_02140824;}
extern "C" {extern Vec3 data_ov006_021408fc;}
extern "C" {extern int data_ov006_021408f0;}
extern "C" {extern int data_ov006_0214080c;}
extern "C" {extern Vec3 data_ov006_02140914;}
extern "C" {extern int data_ov006_02140908;}

extern "C" void func_ov006_020cdd08(char* self)
{
    Vec3 a, b, c, d;

    if (!(data_ov006_02140824 & 1)) {
        data_ov006_021408fc.x = 0;
        data_ov006_021408fc.y = 0x1000;
        data_ov006_021408fc.z = 0;
        func_020731dc(&data_ov006_021408fc, (void *)&_ZN7Vector3D1Ev, (void**)&data_ov006_021408f0);
        data_ov006_02140824 |= 1;
    }
    if (!(data_ov006_0214080c & 1)) {
        data_ov006_02140914.x = 0;
        data_ov006_02140914.y = 0;
        data_ov006_02140914.z = 0x1000;
        func_020731dc(&data_ov006_02140914, (void *)&_ZN7Vector3D1Ev, (void**)&data_ov006_02140908);
        data_ov006_0214080c |= 1;
    }
    func_0203cc28((int*)(self + 0x38), 0x100);
    func_0203ce80(&a, (Vec3*)(self + 0x38));
    func_0203cf00(&b, (Vec3*)(self + 0x38), &data_ov006_02140914);
    *(int*)(self + 0x44) = b.x;
    *(int*)(self + 0x48) = b.y;
    *(int*)(self + 0x4c) = b.z;
    func_0203ce80(&c, (Vec3*)(self + 0x44));
    Quaternion_FromVector3((int*)(self + 0x74), &data_ov006_021408fc, (Vec3*)(self + 0x38));
    Quaternion_Normalize((int*)(self + 0x74));
}
}

// ---- func_ov006_020cde28.c ----
namespace s020cde28 {
struct S{int w[2];}; extern "C" {extern struct S data_ov006_0213b39c;}
extern "C" void func_ov006_020cde28(char*c){*(int*)(c+0x30)=0;*(struct S*)c=data_ov006_0213b39c;}
}

// ---- func_ov006_020cde4c.c ----
namespace s020cde4c {
extern "C" void func_ov006_020cde4c(char*c){
int v=*(int*)(c+0xc);
if(v>0x80000){*(int*)(c+0x30)=-0x1000;return;}
if(v<-0x60000)*(int*)(c+0x30)=0x1000;
}
}

// ---- func_ov006_020cde7c.c ----
namespace s020cde7c {
struct S{int w[2];}; extern "C" {extern struct S data_ov006_0213b35c;}
extern "C" void func_ov006_020cde7c(char*c){*(int*)(c+0x30)=0x1000;*(struct S*)c=data_ov006_0213b35c;}
}

// ---- func_ov006_020cdea0.c ----
namespace s020cdea0 {
extern "C" {extern int data_ov006_0212e07c[];}
extern "C" {extern int data_ov006_0212e088[];}
extern "C" void func_ov006_020cdea0(char *c) {
  int idx = *(short *)(c + 0x96);
  if (*(int *)(c + 8) > data_ov006_0212e07c[idx]) {
    *(int *)(c + 0x2c) = -data_ov006_0212e088[idx];
    return;
  }
  if (*(int *)(c + 8) < -data_ov006_0212e07c[idx]) {
    *(int *)(c + 0x2c) = data_ov006_0212e088[idx];
  }
}
}

// ---- func_ov006_020cdeec.c ----
namespace s020cdeec {
extern "C" {extern int data_ov006_0212e088[];}
struct S2 { int w[2]; };
extern "C" {extern struct S2 data_ov006_0213b354;}
extern "C" void func_ov006_020cdeec(char *c) {
  int idx = *(short *)(c + 0x96);
  *(int *)(c + 0x2c) = data_ov006_0212e088[idx];
  *(struct S2 *)c = data_ov006_0213b354;
}
}

// ---- func_ov006_020cdf1c.c ----
namespace s020cdf1c {
extern "C" void func_ov006_020cdf1c(void)
{
}
}

// ---- func_ov006_020cdf20.c ----
namespace s020cdf20 {
struct S { int w[2]; };
extern "C" {extern struct S data_ov006_0213b34c;}
extern "C" void func_ov006_020cdf20(char *p) { *(struct S *)(p + 0x0) = data_ov006_0213b34c; }
}

// ---- func_ov006_020cdf3c.c ----
namespace s020cdf3c {
/* func_ov006_020cdf3c at 0x020cdf3c
 *
 * Matched byte-for-byte with mwccarm 1.2/sp2p3 (ov006).
 */
extern "C" extern int _Z14ApproachLinearRiii(int* a, int b, int c);
extern "C" extern void func_ov006_020cdeec(char* c);
extern "C" extern void func_ov006_020cde7c(char* c);
extern "C" extern void func_ov006_020cde28(char* c);
extern "C" extern void func_ov006_020cdf20(char* c);
extern "C" extern void func_ov006_020cdce4(char* c);
extern "C" extern void func_ov006_020cdc68(char* c);
extern "C" extern void func_ov006_020cdad0(char* c);
extern "C" extern void func_ov006_020cdc14(char* c);
extern "C" extern void func_ov006_020cd98c(char* c);

extern "C" void func_ov006_020cdf3c(char* c)
{
    int a = _Z14ApproachLinearRiii((int*)(c + 0x6c), 0x1000, 0xc0);
    int b = _Z14ApproachLinearRiii((int*)(c + 0x68), 0x1000, 0x180);
    int d = _Z14ApproachLinearRiii((int*)(c + 0x70), 0x1000, 0x180);
    int e = _Z14ApproachLinearRiii((int*)(c + 0x88), 0x800, 0x60);
    if (a == 0) return;
    if (b == 0) return;
    if ((d & e) == 0) return;
    switch (*(short*)(c + 0x98)) {
    case 1: func_ov006_020cdeec(c); break;
    case 2: func_ov006_020cde7c(c); break;
    case 3: func_ov006_020cde28(c); break;
    case 0: func_ov006_020cdf20(c); break;
    case 4: func_ov006_020cdce4(c); break;
    case 6: func_ov006_020cdc68(c); break;
    case 8: func_ov006_020cdad0(c); break;
    case 5: func_ov006_020cdc14(c); break;
    case 7: func_ov006_020cd98c(c); break;
    }
}
}

// ---- func_ov006_020ce0ac.cpp ----
namespace s020ce0ac {
extern "C" {extern int data_ov006_02140838;}
extern "C" {extern int data_ov006_02140828;}
struct S2 { int w[2]; };
extern "C" {extern struct S2 data_ov006_0213b344;}
extern "C" void func_ov006_020ce0ac(char *c) {
  ApproachLinear(data_ov006_02140828, data_ov006_02140838, 1);
  *(char *)(c + 0x9c) = 0x1f;
  *(int *)(c + 0x2c) = 0;
  *(int *)(c + 0x30) = 0;
  *(int *)(c + 0x34) = 0;
  *(struct S2 *)c = data_ov006_0213b344;
}
}

// ---- func_ov006_020ce108.cpp ----
namespace s020ce108 {
// @symbol func_ov006_020ce108
/* recovered: shared common types, declarations from a shared header */
/* recovered: shared common types */


extern "C" {
extern void Vec3_Sub(Vector3 *out, Vector3 *a, Vector3 *b);
extern void Vec3_MulScalar(Vector3 *out, const Vector3 *in, int scale);
extern void AddVec3(Vector3 *a, Vector3 *b, Vector3 *c);
extern void SubVec3(Vector3 *a, Vector3 *b, Vector3 *c);
extern int LenVec3(Vector3 *v);
extern int DotVec3(const Vector3 *a, const Vector3 *b);
extern int NormalizeVec3IfNonZero(Vector3 *v);
extern void Vec3_MulScalarInPlace(Vector3 *v, int s);

extern "C" {extern Vector3 data_020a0ebc;}
}

struct Obj {
    virtual Vector3 *m00();
    virtual void m04();
    virtual Vector3 *m08();
};

extern "C" void func_ov006_020ce108(char *a, Obj *o)
{
    Vector3 vA;
    Vector3 vB;
    Vector3 vC;
    Vector3 acc;
    Vector3 scaled;
    Vector3 vD;
    Vector3 diff;
    Vector3 t1;
    Vector3 t2;
    Vector3 t3;
    Vector3 *p1;
    int dot44;
    Vector3 *p2;
    int lenA;
    int lenB;
    int dot38;

    {
        int *g = data_ov006_0213b33c;
        int f0 = *(int *)a;
        if (f0 == g[0]) {
            if (*(int *)(a + 4) == g[1])
                return;
            if (f0 == 0)
                return;
        }
    }

    p1 = o->m00();
    p2 = o->m08();

    acc = data_020a0ebc;
    Vec3_Sub(&diff, p1, (Vector3 *)(a + 8));
    vB = diff;
    vA = diff;
    vC = diff;

    Vec3_MulScalar(&scaled, (Vector3 *)(a + 0x44), data_ov006_0212e070[*(short *)(a + 0x96)]);
    AddVec3(&vA, &scaled, &vA);
    SubVec3(&vB, &scaled, &vB);

    vA.y += 0xE000;
    vB.y += 0xE000;
    vA.y >>= 1;
    vB.y >>= 1;

    lenA = LenVec3(&vA);
    lenB = LenVec3(&vB);
    dot44 = DotVec3(&vC, (Vector3 *)(a + 0x44));
    dot38 = DotVec3(&vC, (Vector3 *)(a + 0x38));

    if (lenA < 0xE000 && NormalizeVec3IfNonZero(&vA) != 0) {
        Vec3_MulScalarInPlace(&vA, 0xE000 - lenA);
        vA.y <<= 1;
        Vec3_MulScalar(&t1, &vA, *(int *)(a + 0x88));
        AddVec3(p1, &t1, p1);
        AddVec3(&acc, &vA, &acc);
        *(short *)(((int)o + 0x22)) += 1;
    } else if (lenB < 0xE000 && NormalizeVec3IfNonZero(&vB) != 0) {
        Vec3_MulScalarInPlace(&vB, 0xE000 - lenB);
        vB.y <<= 1;
        Vec3_MulScalar(&t2, &vB, *(int *)(a + 0x88));
        AddVec3(p1, &t2, p1);
        AddVec3(&acc, &vB, &acc);
        *(short *)(((int)o + 0x22)) += 1;
    }

    Vec3_MulScalar(&t3, &acc, 0x100);
    AddVec3(p2, &t3, p2);

    {
        int x = p2->x;
        if (x < -0x1000)
            x = -0x1000;
        else if (x > 0x1000)
            x = 0x1000;
        p2->x = x;
    }

    {
        int mx = data_ov006_021405a8[0];
        int mn = data_ov006_021405b4[0];
        int y = p2->y;
        if (y >= mn) {
            if (y <= mx)
                mx = y;
            mn = mx;
        }
        p2->y = mn;
    }

    if ((dot38 < 0 ? -dot38 : dot38) >= 0xE000)
        return;

    if (dot44 < 0)
        dot44 = -dot44;
    if (dot44 >= data_ov006_0212e070[*(short *)(a + 0x96)])
        return;

    Vec3_MulScalar(&vD, (Vector3 *)(a + 0x38), 0x70);
    if (dot38 > 0)
        Vec3_MulScalarInPlace(&vD, -0x1000);
    {
        int t = vD.y;
        if (t > 0x80)
            t = 0x80;
        vD.y = t;
    }
    AddVec3(p2, &vD, p2);
}
}

// ---- func_ov006_020ce46c.c ----
namespace s020ce46c {
extern "C" {extern int data_ov006_021405ac;}
extern "C" {extern int data_ov006_02140838;}
extern "C" {extern char *data_ov006_0214082c;}
extern "C" {extern int data_ov006_02140818;}
extern "C" {extern int data_ov006_02140830;}

extern "C" extern void func_ov006_020ce108(char *a, void *o);
extern "C" extern int func_ov006_020ce674(char *a, void *o, int arg1);
extern "C" extern void _Z14ApproachLinearRiii(int *p, int target, int step);
extern "C" extern void func_ov006_020e6e3c(int a, int b);
extern "C" extern void func_ov006_02122b88(int c);
extern "C" extern void func_ov006_020cd7b8(char *c, unsigned short arg1);

#define ELEM ((char *)data_ov006_0214082c + i * 0x1d0)

extern "C" void func_ov006_020ce46c(void *thiz, int arg1)
{
    char *sb = (char *)thiz;
    int i;
    int j;
    int step;
    int v;
    int count7;

    if (data_ov006_021405ac != 0)
        return;
    *(unsigned short *)(sb + 0x22) = 0;

    for (i = 0; i < data_ov006_02140838; i++) {
        if (*(int *)(ELEM + 0x84) == 0)
            continue;
        func_ov006_020ce108(ELEM, sb);
        if (func_ov006_020ce674(ELEM, sb, arg1) == 0)
            continue;
        _Z14ApproachLinearRiii(&data_ov006_02140818, 0x270f, 1);
        v = *(unsigned short *)(sb + 0x20);
        step = 100;
        count7 = (v > 6) ? 6 : v;
        for (j = 0; j < count7; j++)
            step <<= 1;
        switch (v) {
        case 0:
            func_ov006_020e6e3c(0x131, *(int *)(ELEM + 8));
            break;
        case 1:
            func_ov006_020e6e3c(0x132, *(int *)(ELEM + 8));
            break;
        case 2:
            func_ov006_020e6e3c(0x133, *(int *)(ELEM + 8));
            break;
        case 3:
            func_ov006_020e6e3c(0x134, *(int *)(ELEM + 8));
            break;
        case 4:
        default:
            func_ov006_020e6e3c(0x135, *(int *)(ELEM + 8));
            break;
        }
        _Z14ApproachLinearRiii(&data_ov006_02140830, 0xf423f, step);
        func_ov006_02122b88(*(unsigned short *)(sb + 0x20));
        func_ov006_020cd7b8(ELEM, (short)step);
        (*(unsigned short *)(sb + 0x20))++;
    }
}
}

// ---- func_ov006_020ce674.c ----
namespace s020ce674 {
struct V2 { int x, y; };

#define AT(p, off) ((void*)(int)((char*)(p) + (off)))

extern "C" extern void func_ov006_020ce8a0(char* self, void* other, struct V2* a, struct V2* b);
extern "C" extern void Vec2_Sub(struct V2* o, struct V2* a, struct V2* b);
extern "C" extern int func_0203d524(struct V2* a, struct V2* b);
extern "C" {extern int data_ov006_0212e070[];}
extern "C" {extern int data_ov006_0213b324[2];}
extern "C" {extern int data_ov006_0213b334[2];}

extern "C" int func_ov006_020ce674(char* self, void* other) {
    struct V2 a, b, n, t0, d, e, f, g, h, i;
    int f0 = *(int*)self;
    int s0, s1, s2, s3;
    int result;

    {
        int *p324 = (int *)AT(data_ov006_0213b324, 0);
        int *p334;
        if ((f0 == p324[0] && (*(int*)(self + 4) == p324[1] || f0 == 0)) ||
            (p334 = (int *)AT(data_ov006_0213b334, 0),
             f0 == p334[0] && (*(int*)(self + 4) == p334[1] || f0 == 0)))
            return 0;
    }

    result = 0;
    func_ov006_020ce8a0(self, other, &a, &b);

    {
        int *dp = (int *)AT(data_ov006_0212e070, 0);
        n.x = -dp[*(short*)(self + 0x96)];
        n.y = 0;
        t0.x = dp[*(short*)(self + 0x96)];
        t0.y = 0;
    }

    Vec2_Sub(&d, &t0, &n);
    Vec2_Sub(&e, &a, &n);
    Vec2_Sub(&f, &b, &n);
    s0 = func_0203d524(&d, &e);
    s1 = func_0203d524(&d, &f);
    if (s0 < -1) s0 = -1; else if (s0 > 1) s0 = 1;
    if (s1 < -1) s1 = -1; else if (s1 > 1) s1 = 1;
    if (s0 * s1 > 0) goto done;
    if (s0 == 0 && s1 == 0) goto done;

    Vec2_Sub(&g, &a, &b);
    d = g;
    Vec2_Sub(&h, &t0, &a);
    e = h;
    Vec2_Sub(&i, &n, &a);
    f = i;
    s2 = func_0203d524(&d, &e);
    s3 = func_0203d524(&d, &f);
    if (s2 < -1) s2 = -1; else if (s2 > 1) s2 = 1;
    if (s3 < -1) s3 = -1; else if (s3 > 1) s3 = 1;
    if (s2 * s3 < 0 && (s2 != 0 || s3 != 0)) result = 1;
done:
    return result;
}
}

// ---- func_ov006_020ce8a0.cpp ----
namespace s020ce8a0 {
// @symbol func_ov006_020ce8a0
/* recovered: shared common types */

extern "C" void Vec3_Sub(struct Vector3* out, struct Vector3* a, struct Vector3* b);
extern "C" int DotVec3(struct Vector3* a, struct Vector3* b);

struct Obj {
  virtual struct Vector3* GetA();
  virtual struct Vector3* GetB();
};

extern "C" void func_ov006_020ce8a0(char* self, struct Obj* o, int* outR5, int* outR4){
  struct Vector3 a, b, sa, sb;
  struct Vector3* p;
  int t;
  p=o->GetA();
  a.x=p->x; a.y=p->y; a.z=p->z;
  p=o->GetB();
  b.x=p->x; b.y=p->y; b.z=p->z;
  Vec3_Sub(&sa,&a,(struct Vector3*)(self+8));
  Vec3_Sub(&sb,&b,(struct Vector3*)(self+0x14));
  sa.y += 0xc000;
  t=DotVec3((struct Vector3*)(self+0x38),&sa);
  outR5[0]=DotVec3((struct Vector3*)(self+0x44),&sa);
  outR5[1]=t;
  t=DotVec3((struct Vector3*)(self+0x50),&sb);
  outR4[0]=DotVec3((struct Vector3*)(self+0x5c),&sb);
  outR4[1]=t;
}
}

// ---- func_ov006_020ce988.cpp ----
namespace s020ce988 {
// @symbol func_ov006_020ce988
/* recovered: shared common types */

extern "C" {
void Matrix4x3_FromQuaternion(const void* q, struct Matrix4x3* mF);
void Matrix4x3_FromTranslation(struct Matrix4x3* m, int x, int y, int z);
void MulMat4x3Mat4x3(struct Matrix4x3* a, struct Matrix4x3* b, struct Matrix4x3* out);
void _ZN18TextureTransformer6UpdateER15ModelComponents(void* t, void* mc);
void _ZN9ModelBase12ApplyOpacityEjj(void* mb, unsigned int opacity, unsigned int unused);
}
extern "C" {extern struct Matrix4x3 data_020a0e68;}

struct VtO { int dummy[0x14/4]; void (*f)(void*, void*); };

extern "C" void func_ov006_020ce988(char* c){
    struct Matrix4x3 tmp;
    Matrix4x3_FromQuaternion(c+0x74, &tmp);
    Matrix4x3_FromTranslation(&data_020a0e68, *(int*)(c+8), *(int*)(c+0xc), *(int*)(c+0x10));
    MulMat4x3Mat4x3(&tmp, &data_020a0e68, &data_020a0e68);
    *(struct Matrix4x3*)(*(char**)(c+0x190) + 0x1c) = data_020a0e68;
    _ZN18TextureTransformer6UpdateER15ModelComponents(c+0x194, *(char**)(c+0x190) + 8);
    _ZN9ModelBase12ApplyOpacityEjj(*(void**)(c+0x190), *(unsigned char*)(c+0x9c), 0);
    {
        void* o = *(void**)(c+0x190);
        VtO* vt = *(VtO**)o;
        vt->f(o, c+0x68);
    }
}
}

// ---- func_ov006_020cea2c.cpp ----
namespace s020cea2c {
extern "C" {
void AddVec3(void *a, void *b, void *c);
void _ZN9Animation7AdvanceEv(void *anim);
}

struct C;
typedef void (C::*PMF)();

extern "C" void func_ov006_020cea2c(char *c)
{
    PMF *pp = (PMF *)c;
    (((C *)c)->**pp)();
    AddVec3(c + 8, c + 0x2c, c + 8);
    _ZN9Animation7AdvanceEv(c + 0x194);
    *(int *)(c + 0x14) = *(int *)(c + 8);
    *(int *)(c + 0x18) = *(int *)(c + 0xc);
    *(int *)(c + 0x1c) = *(int *)(c + 0x10);
    *(int *)(c + 0x50) = *(int *)(c + 0x38);
    *(int *)(c + 0x54) = *(int *)(c + 0x3c);
    *(int *)(c + 0x58) = *(int *)(c + 0x40);
    *(int *)(c + 0x5c) = *(int *)(c + 0x44);
    *(int *)(c + 0x60) = *(int *)(c + 0x48);
    *(int *)(c + 0x64) = *(int *)(c + 0x4c);
}
}

// ---- func_ov006_020ceabc.c ----
namespace s020ceabc {
typedef struct { int x, y, z; } Vec3;

extern "C" {extern int data_ov006_0214081c;}
extern "C" {extern Vec3 data_ov006_021408a8;}
extern "C" {extern void *data_ov006_0214089c;}
extern "C" {extern int data_02092768[4];}
extern "C" {extern int data_020a0ebc[3];}
extern "C" extern void *_ZN7Vector3D1Ev(void *object);
extern "C" extern void func_020731dc(void *object, void *destructor, void **node);
extern "C" extern void func_0203cc28(int *p, int angle);
extern "C" extern void Quaternion_FromVector3(int *q, Vec3 *a, Vec3 *b);
extern "C" extern void func_ov006_020ce0ac(char *c);

extern "C" void func_ov006_020ceabc(char *self, int *v1, int *v2, int a3, short a4)
{
    if ((data_ov006_0214081c & 1) == 0) {
        data_ov006_021408a8.x = 0;
        data_ov006_021408a8.y = 0x1000;
        data_ov006_021408a8.z = 0;
        func_020731dc(&data_ov006_021408a8, (void *)_ZN7Vector3D1Ev, &data_ov006_0214089c);
        data_ov006_0214081c |= 1;
    }
    *(int *)(self + 0x8) = v1[0];
    *(int *)(self + 0xc) = v1[1];
    *(int *)(self + 0x10) = v1[2];
    *(int *)(self + 0x38) = v2[0];
    *(int *)(self + 0x3c) = v2[1];
    *(int *)(self + 0x40) = v2[2];
    {
        int *p38 = (int *)(int)(self + 0x38);
        *(int *)(self + 0x44) = p38[0];
        *(int *)(self + 0x48) = p38[1];
        *(int *)(self + 0x4c) = p38[2];
    }
    func_0203cc28((int *)(self + 0x44), -0x4000);
    *(int *)(self + 0x14) = *(int *)(self + 0x8);
    *(int *)(self + 0x18) = *(int *)(self + 0xc);
    *(int *)(self + 0x1c) = *(int *)(self + 0x10);
    {
        int *p14 = (int *)(int)(self + 0x14);
        *(int *)(self + 0x20) = p14[0];
        *(int *)(self + 0x24) = p14[1];
        *(int *)(self + 0x28) = p14[2];
    }
    *(int *)(self + 0x50) = *(int *)(self + 0x38);
    *(int *)(self + 0x54) = *(int *)(self + 0x3c);
    *(int *)(self + 0x58) = *(int *)(self + 0x40);
    *(int *)(self + 0x5c) = *(int *)(self + 0x44);
    *(int *)(self + 0x60) = *(int *)(self + 0x48);
    *(int *)(self + 0x64) = *(int *)(self + 0x4c);
    *(int *)(self + 0x74) = data_02092768[0];
    *(int *)(self + 0x78) = data_02092768[1];
    *(int *)(self + 0x7c) = data_02092768[2];
    *(int *)(self + 0x80) = data_02092768[3];
    Quaternion_FromVector3((int *)(self + 0x74), &data_ov006_021408a8, (Vec3 *)(self + 0x38));
    *(short *)(self + 0x96) = a3;
    *(short *)(self + 0x98) = a4;
    *(int *)(self + 0x84) = 1;
    switch (*(short *)(self + 0x96)) {
    case 0:
        *(void **)(self + 0x190) = self + 0xa0;
        break;
    case 1:
        *(void **)(self + 0x190) = self + 0xf0;
        break;
    case 2:
    default:
        *(void **)(self + 0x190) = self + 0x140;
        break;
    }
    *(int *)(self + 0x68) = data_020a0ebc[0];
    *(int *)(self + 0x6c) = data_020a0ebc[1];
    *(int *)(self + 0x70) = data_020a0ebc[2];
    *(int *)(self + 0x88) = 0;
    *(short *)(self + 0x92) = 0x5a;
    func_ov006_020ce0ac(self);
}
}

// ---- func_ov006_020cecb4.c ----
namespace s020cecb4 {
extern "C" void func_ov006_020cecb4(int *p)
{
    p[33] = 0;
}
}

// ---- func_ov006_020cecc0.cpp ----
namespace s020cecc0 {
extern "C" {
void func_ov006_020cecb4(int *p);
}
/* Signature deliberately copied from the local declaration above: the
   ROM name carries by-value class parameters (e.g. Fix12<int>), which
   mwccarm passes differently at the call site, so declaring the true
   types breaks the byte match. See notes/mwccarm-codegen.md 6az. */
extern "C" void _ZN18TextureTransformer7SetFileER8BTA_Filei5Fix12IiEj(void *, BTA_File&, int, int, unsigned int);


struct data_t { int a; BMD_File* f; };
extern "C" {extern data_t data_ov006_02140850;}
extern "C" {extern data_t data_ov006_02140858;}
extern "C" {extern data_t data_ov006_02140848;}
extern "C" {extern BTA_File data_ov006_0213b3a4;}

extern "C" void func_ov006_020cecc0(char* c)
{
    ((Model*)(c+0xa0))->SetFile(data_ov006_02140850.f, 1, -1);
    ((Model*)(c+0xf0))->SetFile(data_ov006_02140858.f, 1, -1);
    ((Model*)(c+0x140))->SetFile(data_ov006_02140848.f, 1, -1);
    ((Model*)(c+0xa0))->SetPolygonID(1);
    ((Model*)(c+0xf0))->SetPolygonID(2);
    ((Model*)(c+0x140))->SetPolygonID(3);
    TextureTransformer::Prepare(*data_ov006_02140850.f, data_ov006_0213b3a4);
    _ZN18TextureTransformer7SetFileER8BTA_Filei5Fix12IiEj((TextureTransformer*)(c+0x194), data_ov006_0213b3a4, 0, 0x1000, 0);
    func_ov006_020cecb4((int*)c);
}
}

// ---- func_ov006_020ced84.c ----
namespace s020ced84 {
/* func_ov006_020ced84 at 0x020ced84
 *
 * Matched byte-for-byte with mwccarm 1.2/sp2p3 (ov006).
 */
extern "C" {extern int data_ov006_02140838;}
extern "C" {extern char *data_ov006_0214082c;}
extern "C" extern void func_ov006_020ce988(char *c);

extern "C" void func_ov006_020ced84(void)
{
    int i;
    for (i = 0; i < data_ov006_02140838; i++)
    {
        char *p = data_ov006_0214082c + i * 0x1d0;
        if (*(int *)(p + 0x84) != 0)
            func_ov006_020ce988(p);
    }
}
}

// ---- func_ov006_020cedf0.c ----
namespace s020cedf0 {
/* func_ov006_020cedf0 at 0x020cedf0
 *
 * Matched byte-for-byte with mwccarm 1.2/sp2p3 (ov006).
 */
extern "C" {extern int data_ov006_02140838;}
extern "C" {extern char* data_ov006_0214082c;}
extern "C" extern void func_ov006_020cea2c(char *c);

extern "C" void func_ov006_020cedf0(void){
  int i=0;
  int off;
  if(data_ov006_02140838>0){
    off=0;
    do{
      char *p = data_ov006_0214082c + off;
      if(*(int*)(p+0x84)!=0){
        func_ov006_020cea2c(p);
      }
      i++;
      off+=0x1d0;
    }while(i<data_ov006_02140838);
  }
}
}

// ---- func_ov006_020cee5c.c ----
namespace s020cee5c {
extern "C" {extern int data_ov006_02140838;}
extern "C" {extern unsigned char* data_ov006_0214082c;}
extern "C" {extern int data_ov006_02140828;}
extern "C" {extern int data_ov006_02140818;}
extern "C" {extern int data_ov006_02140830;}
extern "C" extern void func_ov006_020cecb4(int* p);
extern "C" void func_ov006_020cee5c(void){
  int i=0;
  int off;
  if(data_ov006_02140838>0){
    off=0;
    do{
      func_ov006_020cecb4((int*)(data_ov006_0214082c+off));
      i++;
      off+=0x1d0;
    }while(i<data_ov006_02140838);
  }
  data_ov006_02140828=0;
  data_ov006_02140818=0;
  data_ov006_02140830=0;
}
}

// ---- func_ov006_020ceedc.c ----
namespace s020ceedc {
extern "C" extern void _ZN13SharedFilePtr7ReleaseEv(void *);
extern "C" {extern int data_ov006_02140850[];}
extern "C" {extern int data_ov006_02140858[];}
extern "C" {extern int data_ov006_02140848[];}
extern "C" void func_ov006_020ceedc(void)
{
    _ZN13SharedFilePtr7ReleaseEv(data_ov006_02140850);
    _ZN13SharedFilePtr7ReleaseEv(data_ov006_02140858);
    _ZN13SharedFilePtr7ReleaseEv(data_ov006_02140848);
}
}

// ---- func_ov006_020cef14.c ----
namespace s020cef14 {
extern "C" extern void *_ZN5Model8LoadFileER13SharedFilePtr(void *fp);
extern "C" extern void func_ov006_020cecc0(void *p);
extern "C" {extern int data_ov006_02140850[];}
extern "C" {extern int data_ov006_02140858[];}
extern "C" {extern int data_ov006_02140848[];}
extern "C" {extern char *data_ov006_0214082c[];}
extern "C" {extern int data_ov006_02140838[];}

extern "C" void func_ov006_020cef14(char *a, int count)
{
    int i;
    int off;
    _ZN5Model8LoadFileER13SharedFilePtr(data_ov006_02140850);
    _ZN5Model8LoadFileER13SharedFilePtr(data_ov006_02140858);
    _ZN5Model8LoadFileER13SharedFilePtr(data_ov006_02140848);
    data_ov006_0214082c[0] = a;
    data_ov006_02140838[0] = count;
    i = 0;
    if (count <= 0)
        return;
    off = 0;
    do {
        func_ov006_020cecc0(data_ov006_0214082c[0] + off);
        i++;
        off += 0x1d0;
    } while (i < data_ov006_02140838[0]);
}
}

// ---- func_ov006_020cefa4.c ----
namespace s020cefa4 {
/* func_ov006_020cefa4 at 0x020cefa4
 *
 * Matched byte-for-byte with mwccarm 1.2/sp2p3 (ov006).
 */
extern "C" {extern int data_ov006_02140838;}
extern "C" {extern char *data_ov006_0214082c;}
extern "C" extern int func_ov006_020ceabc(char *p, int a0, int a1, int a2, int a3);

extern "C" char *func_ov006_020cefa4(int a0, int a1, int a2, int a3)
{
    int i = 0;
    char *base;
    int off;
    if (data_ov006_02140838 > 0) {
        base = data_ov006_0214082c;
        do {
            if (*(int*)(base + 0x84) == 0) {
                off = i * 0x1d0;
                func_ov006_020ceabc(data_ov006_0214082c + off, a0, a1, a2, a3);
                return data_ov006_0214082c + off;
            }
            i++;
            base += 0x1d0;
        } while (i < data_ov006_02140838);
    }
    return 0;
}
}

// ---- func_ov006_020cf040.c ----
namespace s020cf040 {
struct Vec3
{
  int x;
  int y;
  int z;
};
extern "C" extern int DotVec3(struct Vec3 *a, struct Vec3 *b);
extern "C" extern void SubVec3(struct Vec3 *a, struct Vec3 *b, struct Vec3 *c);
extern "C" extern int LenVec3(struct Vec3 *v);
extern "C" extern int _ZN4cstd4fdivEii(int a, int b);
extern "C" {extern int data_ov006_0212e0f0[];}
extern "C" void func_ov006_020cf040(char *sl, void *arg1, struct Vec3 *r2)
{
  int i;
  int n5 = -DotVec3(r2, (struct Vec3 *) (sl + 0x14));
  int *op = (int *) (sl + 0x29c);
  char *vp = sl + 0x11c;
  int new_var;
  int *dp = data_ov006_0212e0f0;
  for (i = 0; i < 4; i++)
  {
    int j;
    for (j = 0; j < 4; j++)
    {
      struct Vec3 d;
      SubVec3((struct Vec3 *) vp, (struct Vec3 *) arg1, &d);
      int r4 = (long long) (*((int *) (sl + 0x58)));
      int len = LenVec3(&d);
      int f = _ZN4cstd4fdivEii(r4, r4 + len);
      int t = (int) (((((long long) n5) * (*dp)) + 0x800) >> 12);
      new_var = (int) (((((long long) t) * f) + 0x800) >> 12);
      *op = new_var;
      vp += 0xc;
      dp++;
      op++;
    }

  }

}
}

// ---- func_ov006_020cf124.c ----
namespace s020cf124 {
typedef struct { int x, y, z; } Vec3;

extern "C" extern void SubVec3(Vec3* a, Vec3* b, Vec3* c);
extern "C" extern void CrossVec3(const Vec3* a, const Vec3* b, Vec3* out);
extern "C" extern void NormalizeVec3(int* v, int* out);

#pragma push
#pragma opt_strength_reduction off
extern "C" void func_ov006_020cf124(char* self)
{
    Vec3 ej;
    Vec3 ei;
    char* p;
    Vec3* n;
    int* out;
    int i;
    int j;
    int mask = 0x3ff;

    p = self + 0x5c;
    n = (Vec3*)(self + 0x1dc);
    out = (int*)(self + 0x2dc);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            int *q;
            int z = 0;

            q = (int*)&ej; q[0] = z; q[1] = z; q[2] = z;
            q = (int*)&ei; q[0] = z; q[1] = z; q[2] = z;

            if (j == 0)
                SubVec3((Vec3*)p, (Vec3*)(p + 0xc), &ej);
            else if (j == 3)
                SubVec3((Vec3*)(p - 0xc), (Vec3*)p, &ej);
            else
                SubVec3((Vec3*)(p - 0xc), (Vec3*)(p + 0xc), &ej);

            if (i == 0)
                SubVec3((Vec3*)p, (Vec3*)(p + 0x30), &ei);
            else if (i == 3)
                SubVec3((Vec3*)(p - 0x30), (Vec3*)p, &ei);
            else
                SubVec3((Vec3*)(p - 0x30), (Vec3*)(p + 0x30), &ei);

            CrossVec3(&ej, &ei, n);
            NormalizeVec3((int*)n, (int*)n);

            n->x = (int)(((long long)n->x * 0xff8 + 0x800) >> 12);
            n->y = (int)(((long long)n->y * 0xff8 + 0x800) >> 12);
            n->z = (int)(((long long)n->z * 0xff8 + 0x800) >> 12);

            *out = ((n->x >> 3) & mask)
                 | (((n->y >> 3) & mask) << 10)
                 | (((n->z >> 3) & mask) << 20);

            n++;
            out++;
            p += 0xc;
        }
    }
}
#pragma pop
}
