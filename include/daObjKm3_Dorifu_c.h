#ifndef DAOBJKM3_DORIFU_C_H
#define DAOBJKM3_DORIFU_C_H

#include "types.h"
#include "Model.h"
#include "dBgW_KcMbg.h"

/* The Bowser-in-the-Sky drifting platform. ROM name daObjKm3_Dorifu_c.
 *
 * IT DOES NOT DERIVE FROM dBgActor_c. It derives from daObjDorifu_c, which derives
 * from dBgActor_c. The destructor stores three vptrs -- its own, daObjDorifu_c's,
 * then dBgActor_c's -- and destroys daObjDorifu_c's Model[5] and
 * dBgW_KcMbg[5] in between, all of it from the base declaration.
 *
 *   _ZTI17daObjKm3_Dorifu_c  ov047 0x021124cc
 *   _ZTS17daObjKm3_Dorifu_c  ov047 0x021124d8
 *   _ZTV17daObjKm3_Dorifu_c ov047 0x0211254c  (its record sits at V-4)
 *   kind                     __si_class_type_info, ONE base, offset 0
 *   base                     daObjDorifu_c, ov002 0x02108d70
 *
 * THE TREE'S "Bs" NAMES ARE CROSSED, and this header does not try to fix it. The
 * factory that builds THIS class is StairsBs_Spawn (0xdcc, this class's vtable),
 * mirroring StairsBdw_Spawn in ov043. The function called
 * daObjKm3_Dorifu_c_Spawn builds something else -- 800 = 0x320, daObjKuruma_c's
 * vtable then ov047 0x0211244c, which is daObjKm3_Kuruma_c, a class the tree has
 * never named. Untangling the two names is a config change and belongs in its
 * own piece of work; the class modelled here is the one the vtable symbol names.
 *
 * NO FIELDS OF ITS OWN: StairsBs_Spawn passes 0xdcc, which daObjDorifu_c fills.
 * It overrides slots 0 and 3, which the base leaves null.
 */

#ifdef __cplusplus

#include "daObjDorifu_c.h"

struct daObjKm3_Dorifu_c : daObjDorifu_c {
    /* --- vtable --- */
    virtual ~daObjKm3_Dorifu_c();     /* slots 16 (D1), 17 (D0) */

    int CleanupResources();            /* slot  3 */
    int InitResources();               /* slot  0 */
};

typedef char daObjKm3_Dorifu_c_size_must_be_0xdcc[sizeof(daObjKm3_Dorifu_c) == 0xdcc ? 1 : -1];

#else

/* The same object spelled flat, for the compiler-generated destructor, which
   lives in a C translation unit and can never be migrated. */
struct daObjKm3_Dorifu_c {
    u8  pad_000[0xd4];
    Model mModel;            /* 0x0d4 */
    dBgW_KcMbg mMovingMeshCollider;            /* 0x124 */
};

#endif /* __cplusplus */

#endif /* DAOBJKM3_DORIFU_C_H */
