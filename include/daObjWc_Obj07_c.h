#ifndef DAOBJWC_OBJ07_C_H
#define DAOBJWC_OBJ07_C_H

#include "types.h"

/* Wet-Dry World's spinning disc.
 *
 * IT DOES NOT DERIVE FROM dBgActor_c. It derives from daObjKaitendai_c, which derives from
 * dBgActor_c, and the difference is in the bytes rather than only in the RTTI: its
 * destructor stores THREE vptrs -- its own, daObjKaitendai_c's, then dBgActor_c's.
 * A one-level chain emits two.
 *
 *   _ZTI15daObjWc_Obj07_c  ov029 0x02113fc8
 *   _ZTS15daObjWc_Obj07_c  ov029 0x02113fe0
 *   _ZTV15daObjWc_Obj07_c  ov029 0x02114018  (its record sits at V-4)
 *   kind  __si_class_type_info, ONE base, subobject offset 0
 *   base  daObjKaitendai_c, ov002 0x021091ac
 *
 * NO FIELDS OF ITS OWN: daObjWc_Obj07_c_Spawn passes 800 = 0x320 = sizeof(dBgActor_c).
 * It overrides slots 0 and 3, which the base leaves null.
 */

#ifdef __cplusplus

#include "daObjKaitendai_c.h"

struct daObjWc_Obj07_c : daObjKaitendai_c {
    /* --- vtable --- */
    virtual ~daObjWc_Obj07_c(); /* slots 16 (D1), 17 (D0) */

    int CleanupResources();            /* slot  3 */
    int InitResources();               /* slot  0 */
};

typedef char daObjWc_Obj07_c_size_must_be_0x320[sizeof(daObjWc_Obj07_c) == 0x320 ? 1 : -1];

#endif /* __cplusplus */

#endif /* DAOBJWC_OBJ07_C_H */
