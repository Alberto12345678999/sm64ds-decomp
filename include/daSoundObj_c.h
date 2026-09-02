#ifndef DASOUNDOBJ_C_H
#define DASOUNDOBJ_C_H

#include "types.h"
#include "dActor_c.h"

/* TWO WITNESSES, and they close on each other:
 *
 *   daSoundObj_c_Spawn  fBase_c::operator new(228 = 0xe4), dActor_c::dActor_c(), stores _ZTV12daSoundObj_c,
 *                 then the members below in this order.
 *   ~daSoundObj_c   the same members destroyed in reverse, then ~dActor_c.
 *
 * SIZE 0xe4 is the factory's own literal, and the last member closes exactly on it.
 *
 * THE VTABLE was diffed slot by slot against _ZTV8dActor_c. Only the slots declared
 * below differ; every other slot holds the base's own word and is inherited, so it
 * is deliberately not redeclared here.
 */
struct daSoundObj_c : dActor_c {
    u8  pad_0d0[0x4];
    s32 mLevelID;                /* 0x0d4 */
    s32 mTimerThreshold;         /* 0x0d8 */
    u16 mTimer;                  /* 0x0dc */
    u16 mTimerReset;             /* 0x0de */
    u8  unk_0e0;                 /* 0x0e0 */
    u8  pad_0e1[0x3];

    /* INLINE, AND THAT IS WHAT LETS THIS CLASS OWN A TRANSLATION UNIT. Declared
       out of line, mwccarm 2004/b56 emits D0 before D1 -- the reverse of the
       cartridge, which has D1 at 0x020f934c and D0 at 0x020f9370 -- and adds a
       third, homeless D2 that no ROM address claims; tools/objisolate.py then
       refuses the whole TU rather than one function. Defined here, the pair
       comes out in ROM order and there is no D2 at all.

       SAFE ONLY BECAUSE THIS CLASS IS A LEAF, and that is measured rather than
       assumed: _ZTI12daSoundObj_c, ov002 0x0210c048, occurs exactly once as a
       word anywhere under extracted/ -- at ov002 file offset 0x5ea78, which is
       0x0210c0d8, the typeinfo slot of its own vtable header at _ZTV-4. No other
       class's __si_class_type_info points at it, so no descendant exists to
       inline this body where the ROM has a `bl`.

       THE BODY IS EMPTY, and the ROM agrees: 0x24 bytes is one vptr store plus
       the tail into ~dActor_c. `daSoundObj_c : dActor_c` is a one-level chain,
       so two vptr stores come out of it, and no member of either class has a
       destructor of its own. */
    virtual ~daSoundObj_c() {}          /* slots 16 (D1), 17 (D0) */

    int Behavior();
    int InitResources();
};

typedef char daSoundObj_c_size_must_be_0xe4[sizeof(daSoundObj_c) == 0xe4 ? 1 : -1];

#endif /* DASOUNDOBJ_C_H */
