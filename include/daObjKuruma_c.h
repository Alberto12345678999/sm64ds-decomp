#ifndef DA_OBJ_KURUMA_C_H
#define DA_OBJ_KURUMA_C_H

#include "types.h"
#include "Platform.h"

/* daObjKuruma_c -- an intermediate the ROM's RTTI names and the tree did not.
 *
 * Every child below has been sitting in the tree as a direct Platform subclass.
 * They are not: each one's destructor stores THREE vtables -- its own, then this
 * class's, then _ZTV8Platform -- and the ROM's own type_info base pointer says
 * this class derives from dBgActor_c, which is what the tree calls Platform.
 *
 *     Actor -> Platform -> daObjKuruma_c -> RickshawPlatformBdw
 *
 * kuruma = cart/vehicle.
 *
 * SIZE. Its one child's factory allocates exactly 800 = 0x320, which IS
 * sizeof(Platform). Nothing between the base's end and the child's start,
 * so neither class declares a byte of its own -- unambiguous even from a
 * single child, because there is no span left to attribute.
 *
 * DESTRUCTOR IS INLINE, like Platform's above it: no child's destructor contains
 * a `bl` to this one -- each stores this vptr and continues straight into
 * Platform's body -- so the compiler must be free to inline it. Out-of-line
 * emits a call the ROM does not have.
 */

struct daObjKuruma_c : Platform {
    virtual ~daObjKuruma_c() {}
};

typedef char daObjKuruma_c_size_must_be_0x320[sizeof(daObjKuruma_c) == 0x320 ? 1 : -1];

#endif
