#ifndef FLOATINGFLOORLLLSMALL_H
#define FLOATINGFLOORLLLSMALL_H

#include "types.h"
#include "daObjUkiyuka_c.h"

/* class FloatingFloorLllSmall -- Lethal Lava Land's bobbing floor (ov022).
 * The ROM's RTTI calls it daObjFl_Ukiyuka_c (ov022:0x021140b4); its vtable is
 * the one the tree already spells _ZTV21FloatingFloorLllSmall at 0x0211412c.
 *
 * Base is daObjUkiyuka_c, NOT Platform. Its destructor stores three vtables in
 * chain order and FloatingFloorLllSmall_Spawn allocates 816 = 0x330, storing
 * _ZTV14daObjUkiyuka_c before its own vtable.
 *
 * THE NAME IS HALF RIGHT: ONE CLASS SERVES BOTH SIZES. FloatingFloorLllBig_Spawn
 * at 0x021120f4 stores this same vtable and allocates the same 816 -- it is a
 * second entry point for this class, not a second class. Which one you get is
 * mVariant below: InitResources switches on the spawn word at 0xc and writes 0
 * for 0x4b and 1 for 0x4c, then indexes data_ov022_021140d4 by it in 0xc-byte
 * strides. It also hands the collider a different scale per branch (0x650000 vs
 * 0x1000000), which is the small-versus-big of the name.
 *
 * mVariant is the whole of this class. daObjUkiyuka_c ends at 0x32c, a u8 there
 * ends at 0x32d, and that rounds up to the 0x330 the factory allocates.
 */

struct FloatingFloorLllSmall : daObjUkiyuka_c {
    u8  mVariant;              /* 0x32c -- 0 = small, 1 = big */

    virtual ~FloatingFloorLllSmall();

    /* Both return int: they are slots 3 and 0, and ActorBase declares those two
       virtuals int-returning -- mwcc rejects a void override outright, which is
       how the arity was settled. The .c definition of InitResources spells it
       void because a mangled free function never sees this declaration. */
    int CleanupResources();
    int InitResources();
};

typedef char FloatingFloorLllSmall_size_must_be_0x330[sizeof(FloatingFloorLllSmall) == 0x330 ? 1 : -1];

#endif
