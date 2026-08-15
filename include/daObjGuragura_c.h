#ifndef DAOBJGURAGURA_C_H
#define DAOBJGURAGURA_C_H

#include "types.h"
#include "Platform.h"

/* daObjGuragura_c -- an intermediate the ROM's RTTI names and the tree did not.
 *
 *     Actor -> Platform -> daObjGuragura_c -> TiltingPlatformBfs
 *                                          -> TiltingPlatformLll
 *
 * guragura (ぐらぐら) is "wobbling/unsteady" -- both children are tilting
 * platforms.
 *
 * SIZE 0x350. Both children's factories allocate the literal 848 = 0x350 and
 * store _ZTV15daObjGuragura_c before their own vtable, so the chain is confirmed
 * from the constructor side as well as from the three vtable stores in each
 * destructor. The 0x30 tail is attributed to this shared base because two
 * independent children agree on the total; that split is the parsimonious read,
 * the TOTAL is what is measured.
 *
 * 0x30 is exactly the width of a Matrix4x3, and a shadow Matrix4x3 is the usual
 * occupant of a gap this size in this family. That is a HYPOTHESIS and is left
 * unnamed here rather than declared as fact -- nothing in either child's TU
 * touches the span.
 *
 * DESTRUCTOR IS INLINE, like Platform's above it: no child's destructor contains
 * a `bl` to this one.
 */

struct daObjGuragura_c : Platform {
    u8  pad_31e[0x2];        /* Platform's tail padding, reused */
    u8  unk_320[0x30];       /* 0x320 -- span evidenced by both factory literals */

    virtual ~daObjGuragura_c() {}
};

typedef char daObjGuragura_c_size_must_be_0x350[sizeof(daObjGuragura_c) == 0x350 ? 1 : -1];

#endif
