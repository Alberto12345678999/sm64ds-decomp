#ifndef DAOBJWC_OBJ03_C_H
#define DAOBJWC_OBJ03_C_H

#include "dActor_c.h"
#include "Model.h"
#include "dCcAc_c.h"

/* daObjWc_Obj03_c is the readable symbol spelling for the class whose cartridge
 * RTTI name is daObjWc_Obj03_c. The ROM exposes both names at the same vtable
 * address: methods mangle as daObjWc_Obj03_c while the typeinfo string retains
 * EAD's daObjWc_Obj03_c name.
 *
 * The factory allocates 0x160 bytes, constructs dActor_c, then constructs the
 * Model at 0x0d4 and dCcAc_c at 0x124. Both destructor variants destroy those
 * members in reverse order before chaining to dActor_c, independently proving
 * their ownership and the class extent.
 *
 * The 31-slot ROM vtable differs from dActor_c only in slots 0, 3, 6, 9, 16
 * and 17, exactly the virtual declarations below. The three non-virtual
 * helpers form the rest of the same high-confidence ten-function TU and are
 * called directly by Behavior.
 */
struct daObjWc_Obj03_c : dActor_c {
    u8      pad_0d0[0x4];
    Model   mModel;             /* 0x0d4 */
    dCcAc_c mCylinder;          /* 0x0124 */
    u32     mWaterID;           /* 0x0158 -- unique ID of actor 0x65 */
    u8      mWaterParam;        /* 0x015c -- selects the matching WDW water */
    u8      mActive;            /* 0x015d -- water movement in progress */
    u8      pad_15e[0x2];

    virtual ~daObjWc_Obj03_c();                  /* slots 16 (D1), 17 (D0) */

    virtual s32 InitResources();              /* slot  0 */
    virtual s32 CleanupResources();           /* slot  3 */
    virtual s32 Behavior();                   /* slot  6 */
    virtual s32 Render();                     /* slot  9 */

    void CheckClsnWithPlayer();
    void SetWaterID();
    void UpdateModelTransform();
};

typedef char daObjWc_Obj03_c_size_must_be_0x160[
    sizeof(daObjWc_Obj03_c) == 0x160 ? 1 : -1];

#endif
