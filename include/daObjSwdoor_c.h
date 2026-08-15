#ifndef DAOBJSWDOOR_C_H
#define DAOBJSWDOOR_C_H

#include "types.h"
#include "Platform.h"

/* daObjSwdoor_c -- an intermediate the ROM's RTTI names and the tree did not.
 *
 * ShutterBob and ShutterHmc have both been sitting in the tree as direct
 * Platform subclasses. They are not: each destructor stores THREE vtables --
 * its own, then this class's, then _ZTV8Platform -- and the ROM's own type_info
 * base pointer says this class derives from dBgActor_c, which is what the tree
 * calls Platform.
 *
 *     Actor -> Platform -> daObjSwdoor_c -> ShutterBob
 *                                        -> ShutterHmc
 *
 * swdoor = switch door: the shutter a switch opens.
 *
 * SIZE 0x324, ON TWO INDEPENDENT LINES OF EVIDENCE. Both children's factories
 * allocate the literal 804 = 0x324 and store _ZTV13daObjSwdoor_c before their
 * own vtable. Separately, the four bytes above Platform's 0x320 were read off
 * this class's OWN TU -- func_ov002_020bad10 and func_ov002_020bac18 in ov002 --
 * rather than inferred from a leaf. That second line is what makes the tail
 * this class's rather than each child's; a base's tail can never be settled by
 * one subclass alone.
 *
 * DESTRUCTOR IS INLINE, like Platform's above it: no child's destructor contains
 * a `bl` to this one.
 */

struct daObjSwdoor_c : Platform {
    u8  pad_31e[0x2];        /* Platform's tail padding, reused */
    u8  unk_320[0x4];        /* 0x320 -- from this class's own TU, not a leaf's */

    virtual ~daObjSwdoor_c() {}
};

typedef char daObjSwdoor_c_size_must_be_0x324[sizeof(daObjSwdoor_c) == 0x324 ? 1 : -1];

#endif
