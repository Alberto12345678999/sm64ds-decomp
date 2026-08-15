#ifndef DAOBJKAITENDAI_C_H
#define DAOBJKAITENDAI_C_H

#include "types.h"
#include "Platform.h"

/* daObjKaitendai_c -- an intermediate the ROM's RTTI names and the tree did not.
 *
 * The tree has been calling this class's five children direct subclasses of
 * Platform. They are not. Each one's destructor stores THREE vtables --
 * its own, then 0x021091d4, then _ZTV8Platform -- and 0x021091d4 is the vtable
 * of the type_info record named `daObjKaitendai_c` (build/rtti.json, ov002).
 * The ROM's own base pointer says daObjKaitendai_c derives from dBgActor_c,
 * which is what this tree calls Platform, so the chain is
 *
 *     Actor -> Platform -> daObjKaitendai_c -> RotatingPlatformWf   (and four more)
 *
 * Kaitendai (回転台) is "rotating platform/turntable", and every child is one:
 * RotatingPlatformWf, RotatingPlatformLll, RotatingPlatformWdw,
 * RotatingPlatformRr, RickshawBs.
 *
 * NO DATA MEMBER, AND THAT IS A MEASUREMENT, NOT AN OMISSION. All five children
 * place their own first member at 0x320, which is sizeof(Platform) -- so this
 * class occupies no bytes between Platform's end and its children's start.
 * Nothing in its own TU touches an offset at or above 0x300 either. A tail field
 * invented from span would push every child's member and break all five.
 *
 * DESTRUCTOR IS INLINE, like Platform's directly above it in the chain, and for
 * the same reason: no child's destructor contains a `bl` to this one. Each child
 * stores this vptr and then goes straight on to Platform's body, so the compiler
 * must be free to inline it. Declaring it out-of-line emits a call the ROM does
 * not have.
 *
 * The class is abstract in the ROM -- slots 0 and 3 of its vtable are null -- but
 * it is not marked abstract here: a pure virtual would change what the children's
 * own tables must contain, and this header exists to model the chain, not to
 * re-derive their slot lists.
 */

struct daObjKaitendai_c : Platform {
    virtual ~daObjKaitendai_c() {}
};

/* sizeof is 0x320: the class adds no data member, and all four of its evidenced children's
 * factories allocate the literal 800 = 0x320, the same as Platform's. */
typedef char daObjKaitendai_c_size_must_be_0x320[sizeof(daObjKaitendai_c) == 0x320 ? 1 : -1];

#endif
