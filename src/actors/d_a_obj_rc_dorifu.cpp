//cpp
/* ov036/daObjRc_Dorifu_c -- the Rainbow Ride drifting platform, one file.
 *
 * FUNCTION ORDER IS DELIBERATELY THE REVERSE OF THE ROM'S. mwccarm 2004/b56
 * emits one .text section per function in the REVERSE of source order, so the
 * highest-address ROM function is written FIRST here and the lowest LAST. Do
 * not reorder.
 *
 * BOTH DESTRUCTOR VARIANTS ARE MANGLED `// @symbol` BODIES, not a C++ member.
 * The cartridge keeps D1 at 0x02111f8c, BELOW D0 at 0x0211200c, while a real
 * `daObjRc_Dorifu_c::~daObjRc_Dorifu_c()` member makes mwccarm emit the
 * D2/D1/D0 triple as one group in the order D0-then-D1 -- `tubuild verify`
 * reported exactly that as `1 ordinal pair(s) NOT in ROM order: [(0, 1)]` --
 * and the group also carries an unhomed `_ZN16daObjRc_Dorifu_cD2Ev` that no
 * ROM address claims. objisolate refuses both. So the two variants are
 * transcribed from the cartridge with tools/disasm.py (ov036 base 0x021111a0)
 * and given C linkage under their mangled names. That costs the CONVERTED
 * tier's no-raw-offset and no-mangled-refs criteria for those two functions,
 * banked in config/converted-backslide-exceptions.jsonl.
 *
 * NO VPTR BIAS. symbols.txt records _ZTV16daObjRc_Dorifu_c at ov036
 * 0x02113ecc and that IS the address point -- D1's literal pool word at
 * 0x02111ff8 is exactly 0x02113ecc -- so every vptr store below names the
 * symbol with addend 0, never `&_ZTV16daObjRc_Dorifu_c[2]`, which production
 * isolation refuses.
 *
 * THE DESTRUCTOR IS DECLARED LAST IN include/daObjRc_Dorifu_c.h on purpose.
 * Because nothing here defines it as a C++ member, the class's vtable and RTTI
 * have no key function to home them; whether mwccarm emits them at all turns
 * on where the declaration sits in the class body. Declared last it emits
 * them, tools/romdata_check.py word-compares the emitted copy against the
 * cartridge, and the resulting data symbols are licensed in this TU's manifest
 * as compiler_only_output. Declared first it emits none of them and
 * tools/validate_merge.py's ROM-data ratchet reds the pull request.
 *
 * THE BASE DESTRUCTORS ARE INLINED IN THE ROM, which is why the bodies below
 * spell out daObjDorifu_c's and dBgActor_c's work instead of calling
 * _ZN13daObjDorifu_cD1Ev: three vptr stores (own, daObjDorifu_c's,
 * dBgActor_c's), daObjDorifu_c's dBgW_KcMbg[5] at 0x4b0 and Model[5] at 0x320
 * through __destroy_arr, then dBgActor_c's own dBgW_KcMbg at 0x124 and Model
 * at 0xd4, then dActor_c.
 *
 * Absorbed from these legacy one-function sources (ROM address order):
 *   [0] 0x02111f8c  src/_ZN16daObjRc_Dorifu_cD1Ev.cpp
 *   [1] 0x0211200c  src/_ZN16daObjRc_Dorifu_cD0Ev.cpp
 *   [2] 0x021120a0  src/_ZN16daObjRc_Dorifu_c16CleanupResourcesEv.cpp
 *   [3] 0x021120b4  src/_ZN16daObjRc_Dorifu_c13InitResourcesEv.cpp
 *   [4] 0x021120c8  src/daObjRc_Dorifu_c_classInit.cpp
 */

#include "daObjRc_Dorifu_c.h"

/* The resource table this platform hands to its base, five 0xc-byte entries at
 * ov036 0x02113e88. daObjDorifuResources and the two base methods that consume
 * it are declared by include/daObjDorifu_c.h, which daObjRc_Dorifu_c.h
 * includes, so no shadow declaration is needed for either.
 *
 * tubuild's generated shadow block spelled this WRONGLY: a local
 * `struct ResourceDescriptor { void *entries[3]; }` plus raw
 * `func_ov002_020b4b6c` / `func_ov002_020b4d58` externs. Those two names are
 * exported by no module -- the addresses are real, but the symbols there are
 * _ZN13daObjDorifu_c16CleanupResourcesEP20daObjDorifuResources
 * (config/arm9/overlays/ov002/symbols.txt:196) and
 * _ZN13daObjDorifu_c13InitResourcesEP20daObjDorifuResources (:199) -- so the TU
 * would compile and byte-match and then fail the ROM link on promotion with
 * `Undefined : "func_ov002_020b4b6c"`. That is exactly what happened to
 * daObjKm3_Dorifu_c, which had the same generated block, in the same overlay,
 * inventing the same two names. */
extern daObjDorifuResources data_ov036_02113e88[5];

/* -------------------------------------------------------------------------- */
/* ROM ordinal 4 -- daObjRc_Dorifu_c_classInit, 0x021120c8, size 0x90          */
/* -------------------------------------------------------------------------- */
extern "C" {
// @symbol daObjRc_Dorifu_c_classInit
extern void *_ZN7fBase_cnwEj(unsigned);
extern void _ZN10dBgActor_cC2Ev(void *);
extern void func_020733a8(void *, int, int, void *, void *);
extern int _ZTV13daObjDorifu_c[];
extern int _ZTV16daObjRc_Dorifu_c[];
extern void _ZN5ModelD1Ev(void *);
extern void _ZN5ModelC1Ev(void *);
extern void _ZN10dBgW_KcMbgD1Ev(void *);
extern void _ZN10dBgW_KcMbgC1Ev(void *);
/* Reconstructed source-style name: SM64DS proves daObjRc_Dorifu_c through
 * RTTI, allocation size, vtable identity, and the RC_DORIFU registry profile;
 * later EAD lineage supplies classInit. Exact original spelling is not
 * preserved. The project's TrickyTriangles implementation alias remains
 * unchanged (symbols/actor_renames.tsv still carries that row). Historical
 * alias: TrickyTriangles_Spawn. */
void *daObjRc_Dorifu_c_classInit(void)
{
    char *c = (char *)_ZN7fBase_cnwEj(0xdcc);
    if (c) {
        _ZN10dBgActor_cC2Ev(c);
        *(int *)c = (int)_ZTV13daObjDorifu_c;
        func_020733a8(c + 0x320, 5, 0x50, (void *)_ZN5ModelC1Ev, (void *)_ZN5ModelD1Ev);
        func_020733a8(c + 0x4b0, 5, 0x1c8, (void *)_ZN10dBgW_KcMbgC1Ev, (void *)_ZN10dBgW_KcMbgD1Ev);
        *(int *)c = (int)_ZTV16daObjRc_Dorifu_c;
    }
    return c;
}
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 3 -- _ZN16daObjRc_Dorifu_c13InitResourcesEv, 0x021120b4, 0x14   */
/* -------------------------------------------------------------------------- */
// @symbol _ZN16daObjRc_Dorifu_c13InitResourcesEv
/* recovered: named members + shared header, real C++ method */
int daObjRc_Dorifu_c::InitResources()
{
    return daObjDorifu_c::InitResources(data_ov036_02113e88);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 2 -- _ZN16daObjRc_Dorifu_c16CleanupResourcesEv, 0x021120a0, 0x14 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN16daObjRc_Dorifu_c16CleanupResourcesEv
/* recovered: named members + shared header, real C++ method */
int daObjRc_Dorifu_c::CleanupResources()
{
    return daObjDorifu_c::CleanupResources(data_ov036_02113e88);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 1 -- _ZN16daObjRc_Dorifu_cD0Ev, 0x0211200c, size 0x94           */
/* -------------------------------------------------------------------------- */
extern "C" {  /* mangled body: C linkage so the name is emitted verbatim */
// @symbol _ZN16daObjRc_Dorifu_cD0Ev
/* The DELETING destructor: everything D1 does, then the object goes back to the
 * heap the cartridge keeps at 0x020a0eac. */
extern void __destroy_arr(void *, int, int, void *);
extern void _ZN8dActor_cD2Ev(void *);
extern void _ZN6Memory10DeallocateEPvP4Heap(void *, void *);
extern int _ZTV10dBgActor_c[];
extern void *data_020a0eac;
int *_ZN16daObjRc_Dorifu_cD0Ev(int *t)
{
    t[0] = (int)_ZTV16daObjRc_Dorifu_c;
    t[0] = (int)_ZTV13daObjDorifu_c;
    __destroy_arr((char *)t + 0x4b0, 5, 0x1c8, (void *)_ZN10dBgW_KcMbgD1Ev);
    __destroy_arr((char *)t + 0x320, 5, 0x50, (void *)_ZN5ModelD1Ev);
    t[0] = (int)_ZTV10dBgActor_c;
    _ZN10dBgW_KcMbgD1Ev((char *)t + 0x124);
    _ZN5ModelD1Ev((char *)t + 0xd4);
    _ZN8dActor_cD2Ev(t);
    _ZN6Memory10DeallocateEPvP4Heap(t, data_020a0eac);
    return t;
}
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 0 -- _ZN16daObjRc_Dorifu_cD1Ev, 0x02111f8c, size 0x80           */
/* -------------------------------------------------------------------------- */
extern "C" {  /* mangled body: C linkage so the name is emitted verbatim */
// @symbol _ZN16daObjRc_Dorifu_cD1Ev
int *_ZN16daObjRc_Dorifu_cD1Ev(int *t)
{
    t[0] = (int)_ZTV16daObjRc_Dorifu_c;
    t[0] = (int)_ZTV13daObjDorifu_c;
    __destroy_arr((char *)t + 0x4b0, 5, 0x1c8, (void *)_ZN10dBgW_KcMbgD1Ev);
    __destroy_arr((char *)t + 0x320, 5, 0x50, (void *)_ZN5ModelD1Ev);
    t[0] = (int)_ZTV10dBgActor_c;
    _ZN10dBgW_KcMbgD1Ev((char *)t + 0x124);
    _ZN5ModelD1Ev((char *)t + 0xd4);
    _ZN8dActor_cD2Ev(t);
    return t;
}
}
