#ifndef DA_OBJ_FLOAT_BOARD_C_H
#define DA_OBJ_FLOAT_BOARD_C_H

#include "types.h"
#include "Platform.h"

/* daObjFloatBoard_c -- an intermediate the ROM's RTTI names and the tree did not.
 *
 * Every child below has been sitting in the tree as a direct Platform subclass.
 * They are not: each one's destructor stores THREE vtables -- its own, then this
 * class's, then _ZTV8Platform -- and the ROM's own type_info base pointer says
 * this class derives from dBgActor_c, which is what the tree calls Platform.
 *
 *     Actor -> Platform -> daObjFloatBoard_c -> FloatOnWaterPlatformJrb
 *
 * a board that floats on water.
 *
 * SIZE. All THREE children's factories allocate the same literal 840 = 0x348,
 * and each stores _ZTV17daObjFloatBoard_c before its own vtable. Three
 * independent classes agreeing on one total is why the 0x28 tail is
 * attributed to this shared base rather than to each child separately --
 * one child can never falsify a base's tail, three agreeing is the
 * parsimonious read. The SPLIT is inferred; the TOTAL is measured.
 *
 * DESTRUCTOR IS INLINE, like Platform's above it: no child's destructor contains
 * a `bl` to this one -- each stores this vptr and continues straight into
 * Platform's body -- so the compiler must be free to inline it. Out-of-line
 * emits a call the ROM does not have.
 */

struct daObjFloatBoard_c : Platform {
    u8  pad_31e[0x2];        /* Platform's tail padding, reused */
    u8  unk_320[0x28];       /* 0x320 -- span evidenced by the factory literal */
    virtual ~daObjFloatBoard_c() {}
};

typedef char daObjFloatBoard_c_size_must_be_0x348[sizeof(daObjFloatBoard_c) == 0x348 ? 1 : -1];

#endif
