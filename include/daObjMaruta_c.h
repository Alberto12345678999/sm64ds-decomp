#ifndef DA_OBJ_MARUTA_C_H
#define DA_OBJ_MARUTA_C_H

#include "types.h"
#include "Platform.h"

/* daObjMaruta_c -- an intermediate the ROM's RTTI names and the tree did not.
 *
 * Actor -> Platform -> daObjMaruta_c -> RollingLogLll
 *                                       -> RollingLogTtm
 *
 * maruta = log; both children are rolling logs.
 *
 * SIZE 0x344. Both children's factories allocate the literal 836 = 0x344 and store
 * _ZTV13daObjMaruta_c before their own vtable. Two independent children
 * agreeing gives the total; the base-vs-child split is the parsimonious read.
 *
 * ITS VTABLE AT 0x02128338 IS ONE OF THE FOUR ADDRESSES `_ZTV10dBgActor_c` STOOD FOR.
 * That placeholder appears in 12 source files and resolves to a different class
 * in each; it can never be aliased to one address. Deriving these children for
 * real retires every use site here by construction -- the compiler emits the
 * right reference -- rather than by picking a spelling.
 *
 * DESTRUCTOR IS INLINE, like Platform's above it: no child's destructor contains
 * a `bl` to this one.
 */

struct daObjMaruta_c : Platform {
    u8  pad_31e[0x2];        /* Platform's tail padding, reused */
    u8  unk_320[0x24];       /* 0x320 -- span evidenced by the factory literals */

    virtual ~daObjMaruta_c() {}
};

typedef char daObjMaruta_c_size_must_be_0x344[sizeof(daObjMaruta_c) == 0x344 ? 1 : -1];

#endif
