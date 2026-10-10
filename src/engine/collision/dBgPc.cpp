//cpp
/* engine/collision/dBgPc.cpp — dBgPc TU (arm9 0x02037eb0..0x02037f4c)
 *
 * dBgPc is dBgPi's non-polymorphic base (the SurfaceInfo record at +0x04);
 * the cartridge's RTTI records that hierarchy but the class itself has no
 * vtable. The TU is the two member definitions below: mwccarm emits the
 * destructor as D2+D1 (D0 also emits and deadstrips — nothing ever deletes
 * a dBgPc) and the constructor as C1+C2, byte-identical here because a
 * non-polymorphic base has no vptr to store.
 *
 * The edge helpers are absorbed as C++ inside extern "C" (both probe
 * C++OK:hoist). Source runs ROM-descending — mwccarm emits one .text per
 * function in reverse source order — so func_02037f44 leads and
 * func_02037eb0 closes; the constructor stays defined before the
 * destructor, which is what lands the D2,D1 group below the C1,C2 group.
 */
#include "dBgPc.h"

extern "C" {
/* Absorbed from src/unnamed/arm9/0203/func_02037f44.c
 * (arm9 0x02037f44..0x02037f4c). */
int func_02037f44(int *p)
{
    return p[8];
}
}

/* The constructor is defined before the destructor so the deferred
 * emission order lands the D2,D1 group below the C1,C2 group, matching
 * the ROM's layout (mwccarm emits .text in reverse source order). */
// @symbol _ZN5dBgPcC1Ev
// @symbol _ZN5dBgPcC2Ev
dBgPc::dBgPc()
{
    surface.clps.w0 = 0xfc0;
    surface.clps.w1 = 0xff;
    surface.normal.z = 0;
    surface.normal.y = surface.normal.z;
    surface.normal.x = surface.normal.y;
}

// @symbol _ZN5dBgPcD2Ev
// @symbol _ZN5dBgPcD1Ev
dBgPc::~dBgPc()
{
}

extern "C" {
/* Absorbed from src/func_02037eb0.c (arm9 0x02037eb0..0x02037ee4). Local
 * record spellings travel with the body; struct Vector3 comes from the
 * header chain. */
struct AB { int a; int b; };
struct Obj { int a; int b; struct Vector3 v; };

void func_02037eb0(struct Obj *o, struct AB ab, struct Vector3 *v)
{
    o->a = ab.a;
    o->b = ab.b;
    o->v.x = v->x;
    o->v.y = v->y;
    o->v.z = v->z;
}
}
