#ifndef DA_OBJ_FALL_BLOCK_C_H
#define DA_OBJ_FALL_BLOCK_C_H

#include "types.h"
#include "Platform.h"

/* daObjFallBlock_c -- an intermediate the ROM's RTTI names and the tree did not.
 *
 * Actor -> Platform -> daObjFallBlock_c -> FallBlockWf
 *                                       -> FallBlockBfs
 *                                       -> FallBlockBbh
 *
 * fall block: the platform that drops when Mario stands on it.
 *
 * SIZE 0x34c. ALL THREE children's factories allocate the literal 844 = 0x34c and store
 * _ZTV16daObjFallBlock_c before their own vtable. Three independent classes
 * agreeing on one total is why the 0x2c tail is attributed to this shared
 * base; the TOTAL is measured, the base-vs-child split is the parsimonious
 * read.
 *
 * ITS VTABLE AT 0x0213c5bc IS ONE OF THE FOUR ADDRESSES `_ZTV10dBgActor_c` STOOD FOR.
 * That placeholder appears in 12 source files and resolves to a different class
 * in each; it can never be aliased to one address. Deriving these children for
 * real retires every use site here by construction -- the compiler emits the
 * right reference -- rather than by picking a spelling.
 *
 * DESTRUCTOR IS INLINE, like Platform's above it: no child's destructor contains
 * a `bl` to this one.
 */

struct daObjFallBlock_c : Platform {
    u8  pad_31e[0x2];        /* Platform's tail padding, reused */
    u8  unk_320[0x2c];       /* 0x320 -- span evidenced by the factory literals */

    virtual ~daObjFallBlock_c() {}
};

typedef char daObjFallBlock_c_size_must_be_0x34c[sizeof(daObjFallBlock_c) == 0x34c ? 1 : -1];

#endif
