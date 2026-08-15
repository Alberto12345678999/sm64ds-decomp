#ifndef DAOBJKURUMAJIKU_C_H
#define DAOBJKURUMAJIKU_C_H

#include "types.h"
#include "Platform.h"

/* daObjKurumajiku_c -- an intermediate the ROM's RTTI names and the tree did not.
 *
 *     Actor -> Platform -> daObjKurumajiku_c -> daObjKm1_Kurumajiku_c  (RickshawBdw)
 *                                            -> daObjKm3_Kurumajiku_c
 *
 * type_info 0x021092f8 (ov002), vtable 0x02109320 (ov002).
 *
 * kurumajiku = 車軸, an axle. That is exactly what the class does: slot 6 of its
 * vtable spins the object 0x100 units about Z every frame, then carries four
 * other actors around with it.
 *
 * ITS 0x10 TAIL IS A MEMBER READ OFF ITS OWN TU, NOT A SPAN INFERRED FROM A LEAF.
 * func_ov002_020b6b38 is slot 6 of the table above, it lives in ov002 with the
 * class, and it walks four u32 actor IDs at 0x320: for each one it calls
 * Actor::FindWithID, rotates the matching entry of data_ov002_0210ddd0 by the
 * axle's own X/Y/Z angles, adds the axle's position, and writes the result to
 * that actor's position. Four u32s at 0x320 end at 0x330 -- and 0x330 is exactly
 * the literal 816 that BOTH children's factories allocate. The member evidence
 * and the size evidence are independent and they meet.
 *
 * That is a stronger footing than the earlier intermediates in this family had.
 * daObjFallBlock_c's tail, for instance, is only a total that three children
 * agree on; here the base's own code names the field.
 *
 * DESTRUCTOR IS INLINE, like Platform's above it: neither child's destructor
 * contains a `bl` to this one -- each stores this vptr and then goes straight on
 * to Platform's body. The out-of-line pair at 0x020b6a3c (D1) and 0x020b69e4
 * (D0) exists because slots 16/17 of the table need an address.
 *
 * BEWARE THE FACTORY NAMES HERE. src/RickshawBs_Spawn.c is daObjKm3_Kurumajiku_c's
 * factory, not RickshawBs's -- that class is a daObjKaitendai_c child whose vtable
 * is a different address in the same overlay. include/RickshawBs.h records the
 * trap. Pair a class to its factory by vtable address, never by filename.
 */

struct daObjKurumajiku_c : Platform {
    u8  pad_31e[0x2];          /* Platform's tail padding, reused */
    u32 mCarriedIds[4];        /* 0x320 -- Actor unique IDs, walked by slot 6 */

    virtual ~daObjKurumajiku_c() {}
};

typedef char daObjKurumajiku_c_size_must_be_0x330[sizeof(daObjKurumajiku_c) == 0x330 ? 1 : -1];

#endif
