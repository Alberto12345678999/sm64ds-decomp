#ifndef FLOATINGFLOORBFS_H
#define FLOATINGFLOORBFS_H

#include "types.h"
#include "daObjUkiyuka_c.h"

/* class FloatingFloorBfs -- Bowser in the Fire Sea's bobbing floor (ov045).
 * The ROM's RTTI calls it daObjKm2_Ukishima_c (ov045:0x02112efc); its vtable is
 * the one the tree already spells _ZTV16FloatingFloorBfs at 0x02112f50.
 *
 * Base is daObjUkiyuka_c, NOT Platform. Its destructor stores three vtables in
 * chain order and FloatingFloorBfs_Spawn allocates 812 = 0x32c, storing
 * _ZTV14daObjUkiyuka_c before its own vtable.
 *
 * NO MEMBER OF ITS OWN, AND THIS IS THE CHILD THAT PINS THE BASE. 812 is exactly
 * where daObjUkiyuka_c's mDwellTimer ends, so this class adds nothing at all --
 * and because a base's size cannot vary between children, that is what fixes
 * daObjUkiyuka_c at 0x32c and makes its sibling's extra word the sibling's own.
 *
 * ukishima = 浮島, a floating island, where the base is ukiyuka, a floating
 * floor. The ROM uses both words for one chain.
 */

struct FloatingFloorBfs : daObjUkiyuka_c {
    virtual ~FloatingFloorBfs();
};

typedef char FloatingFloorBfs_size_must_be_0x32c[sizeof(FloatingFloorBfs) == 0x32c ? 1 : -1];

#endif
