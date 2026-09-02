#ifndef DAOBJWAKAME_C_H
#define DAOBJWAKAME_C_H

#include "types.h"
#include "dActor_c.h"
#include "ModelAnim.h"

/* TWO WITNESSES, and they close on each other:
 *
 *   daObjWakame_c_Spawn  fBase_c::operator new(312 = 0x138), dActor_c::dActor_c(), stores _ZTV13daObjWakame_c,
 *                 then the member below in this order.
 *   ~daObjWakame_c   the same member destroyed in reverse, then ~dActor_c.
 *
 * SIZE 0x138 is the factory's own literal, and the last member closes exactly on it.
 *
 * THE VTABLE was diffed slot by slot against _ZTV8dActor_c. Only the slots declared
 * below differ; every other slot holds the base's own word and is inherited, so it
 * is deliberately not redeclared here.
 */
struct daObjWakame_c : dActor_c {
    u8  pad_0d0[0x4];
    ModelAnim              mModelAnim;   /* 0x0d4 */

    virtual ~daObjWakame_c();            /* slots 16 (D1), 17 (D0) */

    virtual s32   InitResources();         /* slot  0 */
    virtual s32   CleanupResources();      /* slot  3 */
    virtual s32   Behavior();              /* slot  6 */
    virtual s32   Render();                /* slot  9 */
};

typedef char daObjWakame_c_size_must_be_0x138[sizeof(daObjWakame_c) == 0x138 ? 1 : -1];

#endif /* DAOBJWAKAME_C_H */
