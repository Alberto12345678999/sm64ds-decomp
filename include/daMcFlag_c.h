#ifndef DAMCFLAG_C_H
#define DAMCFLAG_C_H
#include "types.h"
#include "dActor_c.h"
#include "ModelAnim.h"

/* daMcFlag_c_Spawn allocates 0x138 bytes, constructs dActor_c, writes the daMcFlag_c
 * vtable, then constructs the ModelAnim member at 0xd4.  Both destructor
 * variants destroy that member before chaining to dActor_c, independently
 * confirming the ownership and the class extent.
 *
 * The cartridge RTTI names this class daMcFlag_c.  The readable symbol set
 * calls it daMcFlag_c, and symbols.txt therefore retains co-address aliases for the
 * ROM vtable.  The inheritance edge itself is unambiguous: daMcFlag_c derives
 * directly from dActor_c at offset zero.
 *
 * The 31-slot ROM vtable differs from dActor_c only in slots 0, 3, 6, 9, 16
 * and 17, exactly the declarations below.  All other actor virtuals are
 * inherited and must not be redeclared here.
 */
struct daMcFlag_c : dActor_c {
    u8        pad_0d0[0x4];
    ModelAnim mModelAnim;       /* 0x0d4 */

    virtual ~daMcFlag_c();                         /* slots 16 (D1), 17 (D0) */

    virtual s32 InitResources();             /* slot  0 */
    virtual s32 CleanupResources();          /* slot  3 */
    virtual s32 Behavior();                  /* slot  6 */
    virtual s32 Render();                    /* slot  9 */
};

typedef char daMcFlag_c_size_must_be_0x138[sizeof(daMcFlag_c) == 0x138 ? 1 : -1];

#endif
