//cpp
/* dBgCh_SphCrr -- the sphere collision query: dBgCh plus a dBgPi hit record
 * at 0x10 plus the dM3dGSph query sphere at 0x38 (the ROM's own
 * __vmi_class_type_info lists all three bases; _ZTS12dBgCh_SphCrr @
 * 0x020992f8, _ZTI @ 0x02099308, primary _ZTV @ 0x02099338 and the two
 * secondary thunk blocks at 0x02099348 / 0x02099358).
 *
 * The class keeps three result records -- mClsnResult1/2/3 at
 * 0x74/0x9c/0xc4, the floor / wall / underneath hits the query found -- each
 * with a copy setter that preserves the record's own vptr (the stores start
 * at +4, past it) and a slot getter. DetectClsn and the two registry scans
 * live in dBgCh_SphCrr_query.cpp: the cartridge emits this file's members at
 * 0x0203782c..0x02037dc4 and those at 0x02038824..0x02038ea4, with the
 * SurfaceInfo/dBgPi/dBgPc block linked between them.
 *
 * Deferred codegen emits the plain members in reverse definition order and
 * the lifecycle group in its fixed order at the tail, so the file defines
 * ctor and dtor first. The dBgPi/dM3dGSph-base destructor thunks (_ZThn16_
 * and _ZThn56_) are compiler-emitted after C1.
 */
#include "dBgCh_SphCrr.h"

extern "C" {
void func_020353b0(char *c, int *p);    /* dBgCh-side: bind query to its actor */
void func_02037fd4(int *dst, int h, int *src);      /* dBgPi: set tri + copy surface */
void func_02037fec(char *c, int p1, int p2, int p3, int p4); /* dBgPi hit-record fill */
void func_020380c0(char *c);            /* dBgPi hit-record init */
void func_0203abd4(int *a, int *b, int c);        /* dM3dGSph::Set(pos, radius) */
}

// @symbol _ZN12dBgCh_SphCrrC1Ev
dBgCh_SphCrr::dBgCh_SphCrr() : unk_0ec(0) {}

// @symbol _ZN12dBgCh_SphCrrD1Ev
// @symbol _ZN12dBgCh_SphCrrD0Ev
// @symbol _ZThn16_N12dBgCh_SphCrrD0Ev
// @symbol _ZThn16_N12dBgCh_SphCrrD1Ev
// @symbol _ZThn56_N12dBgCh_SphCrrD0Ev
// @symbol _ZThn56_N12dBgCh_SphCrrD1Ev
dBgCh_SphCrr::~dBgCh_SphCrr()
{
}

/* Stays a mangled free definition: the real signature carries Fix12<int> and
   wall 6az homes class-typed by-value parameters. The declaration in
   dBgCh_SphCrr.h is the real one and callers may use it. */
extern "C" void _ZN12dBgCh_SphCrr15SetObjAndSphereERK7Vector35Fix12IiEP8dActor_c(
    dBgCh_SphCrr *self, const Vector3 *pos, int radius, dActor_c *actor)
{
    /* through the REFERENCE: a pointer-level upcast makes mwcc emit the
       null-checked MI adjustment (movs/addne), the ROM's is unconditional */
    func_0203abd4((int *)&(dM3dGSph &)*self, (int *)pos, radius);
    func_020353b0((char *)self, (int *)actor);
    self->func_02037b5c();
    self->mScale = 0x1000;
}

// @symbol _ZN12dBgCh_SphCrr13func_02037b5cEv
void dBgCh_SphCrr::func_02037b5c()
{
    func_02037b1c();
    flags &= ~1;
    flags &= ~4;
    flags &= ~8;
    flags &= ~0x10;
    flags &= ~2;
    flags &= ~0x20;
    flags &= ~0x40;
    func_020380c0((char *)this + 0x10);  /* the dBgPi secondary base */
    func_020380c0((char *)&mClsnResult1);
    func_020380c0((char *)&mClsnResult2);
    func_020380c0((char *)&mClsnResult3);
    unk_0fc = 0;
    unk_100 = -0x1000;
    unk_104 = 0;
}

// @symbol _ZN12dBgCh_SphCrr13func_02037b1cEv
void dBgCh_SphCrr::func_02037b1c()
{
    disp.x = disp.y = disp.z = 0;
    aabbMin.x = aabbMax.x = 0;
    aabbMin.y = aabbMax.y = 0;
    aabbMin.z = aabbMax.z = 0;
}

// @symbol _ZN12dBgCh_SphCrr13func_02037a6cEiiiiii
void dBgCh_SphCrr::func_02037a6c(s32 minX, s32 minY, s32 minZ, s32 maxX, s32 maxY, s32 maxZ)
{
    if (aabbMin.x > minX) aabbMin.x = minX;
    if (aabbMax.x < minX) aabbMax.x = minX;
    if (aabbMin.x > maxX) aabbMin.x = maxX;
    if (aabbMax.x < maxX) aabbMax.x = maxX;
    if (aabbMin.y > minY) aabbMin.y = minY;
    if (aabbMax.y < minY) aabbMax.y = minY;
    if (aabbMin.y > maxY) aabbMin.y = maxY;
    if (aabbMax.y < maxY) aabbMax.y = maxY;
    if (aabbMin.z > minZ) aabbMin.z = minZ;
    if (aabbMax.z < minZ) aabbMax.z = minZ;
    if (aabbMin.z > maxZ) aabbMin.z = maxZ;
    if (aabbMax.z < maxZ) aabbMax.z = maxZ;
}

// @symbol _ZN12dBgCh_SphCrr13func_02037a38Ev
void dBgCh_SphCrr::func_02037a38()
{
    disp.x = aabbMin.x + aabbMax.x;
    disp.y = aabbMin.y + aabbMax.y;
    disp.z = aabbMin.z + aabbMax.z;
}

// @symbol _ZN12dBgCh_SphCrr13func_02037a04EP7Vector3S1_
void dBgCh_SphCrr::func_02037a04(Vector3 *outMin, Vector3 *outMax)
{
    outMin->x = aabbMin.x;
    outMin->y = aabbMin.y;
    outMin->z = aabbMin.z;
    outMax->x = aabbMax.x;
    outMax->y = aabbMax.y;
    outMax->z = aabbMax.z;
}

// @symbol _ZN12dBgCh_SphCrr13func_020379f4EiPv
void dBgCh_SphCrr::func_020379f4(int triID, void *src)
{
    func_02037fd4((int *)&mClsnResult1, triID, (int *)src);
}

// @symbol _ZN12dBgCh_SphCrr13func_020379d0Eiiii
void dBgCh_SphCrr::func_020379d0(int i, int clsnID, int owner, int collider)
{
    func_02037fec((char *)&mClsnResult1, i, clsnID, owner, collider);
}

// @symbol _ZN12dBgCh_SphCrr13func_020379c0EiPv
void dBgCh_SphCrr::func_020379c0(int triID, void *src)
{
    func_02037fd4((int *)&mClsnResult2, triID, (int *)src);
}

// @symbol _ZN12dBgCh_SphCrr13func_0203799cEiiii
void dBgCh_SphCrr::func_0203799c(int i, int clsnID, int owner, int collider)
{
    func_02037fec((char *)&mClsnResult2, i, clsnID, owner, collider);
}

// @symbol _ZN12dBgCh_SphCrr13func_0203798cEiPv
void dBgCh_SphCrr::func_0203798c(int triID, void *src)
{
    func_02037fd4((int *)&mClsnResult3, triID, (int *)src);
}

// @symbol _ZN12dBgCh_SphCrr13func_02037968Eiiii
void dBgCh_SphCrr::func_02037968(int i, int clsnID, int owner, int collider)
{
    func_02037fec((char *)&mClsnResult3, i, clsnID, owner, collider);
}

// @symbol _ZN12dBgCh_SphCrr13func_0203794cEPKi
void dBgCh_SphCrr::func_0203794c(const s32 *payload)
{
    unk_0fc = payload[0];
    unk_100 = payload[1];
    unk_104 = payload[2];
}

// @symbol _ZN12dBgCh_SphCrr13func_02037940Eh
void dBgCh_SphCrr::func_02037940(u8 flags_)
{
    flags = flags_ & ~0x1c;
}

// @symbol _ZN12dBgCh_SphCrr14GetFloorResultEv
dBgPi *dBgCh_SphCrr::GetFloorResult()
{
    return &mClsnResult1;
}

// @symbol _ZN12dBgCh_SphCrr14SetFloorResultERK5dBgPi
void dBgCh_SphCrr::SetFloorResult(const dBgPi &src_)
{
    *reinterpret_cast<u64 *>(&mClsnResult1.surface.clps) =
        *reinterpret_cast<const u64 *>(&src_.surface.clps);
    mClsnResult1.surface.normal.x = src_.surface.normal.x;
    mClsnResult1.surface.normal.y = src_.surface.normal.y;
    mClsnResult1.surface.normal.z = src_.surface.normal.z;
    mClsnResult1.triangleID = src_.triangleID;
    mClsnResult1.flags = src_.flags;
    mClsnResult1.clsnID = src_.clsnID;
    mClsnResult1.unk_020 = src_.unk_020;
    mClsnResult1.unk_024 = src_.unk_024;
}

// @symbol _ZN12dBgCh_SphCrr13GetWallResultEv
dBgPi *dBgCh_SphCrr::GetWallResult()
{
    return &mClsnResult2;
}

// @symbol _ZN12dBgCh_SphCrr13SetWallResultERK5dBgPi
void dBgCh_SphCrr::SetWallResult(const dBgPi &src_)
{
    *reinterpret_cast<u64 *>(&mClsnResult2.surface.clps) =
        *reinterpret_cast<const u64 *>(&src_.surface.clps);
    mClsnResult2.surface.normal.x = src_.surface.normal.x;
    mClsnResult2.surface.normal.y = src_.surface.normal.y;
    mClsnResult2.surface.normal.z = src_.surface.normal.z;
    mClsnResult2.triangleID = src_.triangleID;
    mClsnResult2.flags = src_.flags;
    mClsnResult2.clsnID = src_.clsnID;
    mClsnResult2.unk_020 = src_.unk_020;
    mClsnResult2.unk_024 = src_.unk_024;
}

// @symbol _ZN12dBgCh_SphCrr14GetUnderResultEv
dBgPi *dBgCh_SphCrr::GetUnderResult()
{
    return &mClsnResult3;
}

// @symbol _ZN12dBgCh_SphCrr14SetUnderResultERK5dBgPi
void dBgCh_SphCrr::SetUnderResult(const dBgPi &src_)
{
    *reinterpret_cast<u64 *>(&mClsnResult3.surface.clps) =
        *reinterpret_cast<const u64 *>(&src_.surface.clps);
    mClsnResult3.surface.normal.x = src_.surface.normal.x;
    mClsnResult3.surface.normal.y = src_.surface.normal.y;
    mClsnResult3.surface.normal.z = src_.surface.normal.z;
    mClsnResult3.triangleID = src_.triangleID;
    mClsnResult3.flags = src_.flags;
    mClsnResult3.clsnID = src_.clsnID;
    mClsnResult3.unk_020 = src_.unk_020;
    mClsnResult3.unk_024 = src_.unk_024;
}
