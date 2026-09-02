//cpp
/* Manually curated shadow translation unit.
 * ov036/daObjRc_Dorifu_c  (4 function(s))
 *
 * NOT ENROLLED and NOT CANONICAL. The readable class and member definitions
 * are compiled only by tubuild's scratch pipeline while the four legacy
 * production sources remain authoritative.
 *
 * FUNCTION ORDER IS DELIBERATELY THE REVERSE OF THE ROM'S -- mwccarm 2004/b56
 * emits one .text section per function, in the REVERSE of source order, so
 * the highest-address ROM function is written FIRST here. Do not reorder;
 * see notes/tu-reconstruction-pilot-report.md sec 3 for the one documented
 * exception (a destructor's D0/D1/D2 group has compiler-chosen order).
 *
 * Assembled from these legacy one-function sources (ROM address order):
 *   [0] 0x02111f8c  src/_ZN16daObjRc_Dorifu_cD1Ev.cpp
 *   [1] 0x0211200c  src/_ZN16daObjRc_Dorifu_cD0Ev.c
 *   [2] 0x021120a0  src/_ZN16daObjRc_Dorifu_c16CleanupResourcesEv.cpp
 *   [3] 0x021120b4  src/_ZN16daObjRc_Dorifu_c13InitResourcesEv.cpp
 */

#include "daObjRc_Dorifu_c.h"

/* The resource table this platform hands to its base, five 0xc-byte entries at
 * ov036 0x02113e88. daObjDorifuResources and the two base methods that consume
 * it are declared by include/daObjDorifu_c.h, which daObjRc_Dorifu_c.h includes,
 * so no shadow declaration is needed for either.
 *
 * tubuild's generated shadow block spelled this WRONGLY: a local
 * `struct ResourceDescriptor { void *entries[3]; }` plus raw
 * `func_ov002_020b4b6c` / `func_ov002_020b4d58` externs. Those two names are
 * exported by no module -- the addresses are real, but the symbols there are
 * _ZN13daObjDorifu_c16CleanupResourcesEP20daObjDorifuResources
 * (config/arm9/overlays/ov002/symbols.txt:196) and
 * _ZN13daObjDorifu_c13InitResourcesEP20daObjDorifuResources (:199) -- so the TU
 * would compile and byte-match here and then fail the ROM link on promotion
 * with `Undefined : "func_ov002_020b4b6c"`. That is exactly what happened to
 * daObjKm3_Dorifu_c, which had the same generated block, in the same overlay,
 * inventing the same two names. The legacy one-function sources this shadow
 * stands in for had already recovered the real base calls; what follows is that
 * recovery restored, not a new guess, and it is the pattern the sibling
 * src_tu/actors/daObjKm1_Dorifu_c.cpp already uses. */
extern daObjDorifuResources data_ov036_02113e88[5];

/* -------------------------------------------------------------------------- */
/* ROM ordinal 3 -- _ZN16daObjRc_Dorifu_c13InitResourcesEv, 0x021120b4, size 0x14 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN16daObjRc_Dorifu_c13InitResourcesEv
/* recovered: named members + shared header, real C++ method */
int daObjRc_Dorifu_c::InitResources()
{
    return daObjDorifu_c::InitResources(data_ov036_02113e88);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 2 -- _ZN16daObjRc_Dorifu_c16CleanupResourcesEv, 0x021120a0, size 0x14 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN16daObjRc_Dorifu_c16CleanupResourcesEv
/* recovered: named members + shared header, real C++ method */
int daObjRc_Dorifu_c::CleanupResources()
{
    return daObjDorifu_c::CleanupResources(data_ov036_02113e88);
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 0 -- _ZN16daObjRc_Dorifu_cD1Ev, 0x02111f8c, size 0x80 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN16daObjRc_Dorifu_cD1Ev
/* The compiler emits D2, D0 and D1 from this one class definition. */
daObjRc_Dorifu_c::~daObjRc_Dorifu_c()
{
}
