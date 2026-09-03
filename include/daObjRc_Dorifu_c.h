#ifndef DAOBJRC_DORIFU_C_H
#define DAOBJRC_DORIFU_C_H

#include "types.h"
#include "Model.h"
#include "dBgW_KcMbg.h"

/* The Rainbow Ride drifting platform. Only ever named by its ROM name.
 *
 * IT DOES NOT DERIVE FROM dBgActor_c. It derives from daObjDorifu_c, which derives
 * from dBgActor_c. The destructor stores three vptrs -- its own, daObjDorifu_c's,
 * then dBgActor_c's -- and destroys daObjDorifu_c's Model[5] and
 * dBgW_KcMbg[5] in between. That shape is inherited from the base declaration,
 * but it is no longer compiler-derived here: since the promotion both destructor
 * variants are carried in src/actors/d_a_obj_rc_dorifu.cpp as hand-transcribed
 * mangled bodies (see the class-body comment below for why), so what follows is
 * a description of the cartridge's code, not of code mwccarm generates.
 *
 *   _ZTI16daObjRc_Dorifu_c  ov036 0x02113e4c
 *   _ZTS16daObjRc_Dorifu_c  ov036 0x02113e58
 *   _ZTV16daObjRc_Dorifu_c  ov036 0x02113ecc  (its record sits at V-4)
 *   kind                    __si_class_type_info, ONE base, offset 0
 *   base                    daObjDorifu_c, ov002 0x02108d70 -- CROSSING OVERLAYS,
 *                           which is ordinary here: 183 of the ROM's 413 base
 *                           edges leave their overlay.
 *
 * NO FIELDS OF ITS OWN: daObjRc_Dorifu_c_classInit (historical alias
 * TrickyTriangles_Spawn) passes 0xdcc to
 * fBase_c::operator new, which daObjDorifu_c fills. It overrides slots 0 and 3,
 * which the base leaves null, and both bodies just forward to daObjDorifu_c's
 * shared helpers in ov002 with this class's own argument block. Everything this
 * header used to restate was dBgActor_c's, twice removed.
 */

#ifdef __cplusplus

#include "daObjDorifu_c.h"

struct daObjRc_Dorifu_c : daObjDorifu_c {
    /* --- vtable --- */
    int CleanupResources();            /* slot  3 */
    int InitResources();               /* slot  0 */

    /* DECLARED LAST ON PURPOSE, after the other members. Nothing DEFINES this
       destructor as a C++ member -- D1 and D0 are carried in
       src/actors/d_a_obj_rc_dorifu.cpp as `// @symbol` marked mangled bodies,
       for the emission-order reason that file's header gives -- so the class's
       vtable and RTTI have no key function to home them. With the declaration
       LAST, mwccarm still emits them as vague linkage into the TU that defines
       the class's members, and tools/romdata_check.py word-compares that
       emitted copy against the cartridge; with the declaration FIRST it emits
       no data at all and those ROM records go unverified by any source.
       Measured both ways on the sibling daObjWc_Mizu_c: first -> 0 data
       symbols, last -> 11. This class licenses 13 rather than Mizu's 11
       because it sits two levels below dBgActor_c, so its base chain
       contributes one more _ZTI/_ZTS pair; the manifest's
       compiler_only_output lists all 13 with their canonical addresses. */
    virtual ~daObjRc_Dorifu_c();       /* slots 16 (D1), 17 (D0) */
};

typedef char daObjRc_Dorifu_c_size_must_be_0xdcc[sizeof(daObjRc_Dorifu_c) == 0xdcc ? 1 : -1];

#else

/* The C spelling of the same object, flat. NOTHING IN THE TREE COMPILES THIS
   BRANCH any more: the per-function shards this was written for are gone, and
   the one file that includes this header,
   src/actors/d_a_obj_rc_dorifu.cpp, is //cpp. It is kept only as the readable
   field record -- the same arrangement as include/dBgActor_c.h -- and must stay
   in step with the C++ struct above if either changes. */
struct daObjRc_Dorifu_c {
    u8  pad_000[0xd4];
    /* Model member. The cartridge's own ~daObjRc_Dorifu_c calls _ZN5ModelD1Ev at +0x0d4
       (D0/D1), a relocation the ROM build checks; recovered by tools/dtor_members.py.
       D1 and not D2, so it is this type and not an inlined base. */
    Model mModel;            /* 0x0d4 */
    /* dBgW_KcMbg member. The cartridge's own ~daObjRc_Dorifu_c calls
       _ZN10dBgW_KcMbgD1Ev at +0x124 (D0/D1), a relocation the ROM build checks;
       recovered by tools/dtor_members.py. D1 and not D2, so it is this type and not an
       inlined base. */
    dBgW_KcMbg mMovingMeshCollider;            /* 0x124 */
};

#endif /* __cplusplus */

#endif /* DAOBJRC_DORIFU_C_H */
