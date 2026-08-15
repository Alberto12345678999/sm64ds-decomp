#ifndef DADSNBASE_C_H
#define DADSNBASE_C_H

#include "types.h"
#include "Platform.h"
#include "TextureSequence.h"
#include "ShadowModel.h"

/* daDsnBase_c -- an intermediate the ROM's RTTI names and the tree did not.
 *
 *     Actor -> Platform -> daDsnBase_c -> daDsn_c   (the tree calls it Thwomp)
 *                                      -> daDkk_c   (the tree spawns it as Grindel)
 *
 * dsn = ドッスン (Dossun), the Japanese name for Thwomp; dkk is its square
 * sibling, which the tree spawns through Grindel_Spawn.  The shared base is the
 * "slab that slams down" behaviour both of them are.
 *
 * type_info 0x021137f8 (ov025), vtable 0x021351fc (ov091).  The two live in
 * different overlays because ov091 is the key-function TU: this class's own
 * destructor pair is emitted there, at slots 16/17 of that table.
 *
 * THIS CLASS'S OWN DESTRUCTOR IS THE EVIDENCE FOR ITS MEMBERS, and it is the
 * cleanest kind there is.  func_ov091_02132d6c IS daDsnBase_c::~daDsnBase_c --
 * slot 16 of the table above -- and its whole body is
 *
 *     store _ZTV11daDsnBase_c
 *     ShadowModel::~ShadowModel     (this + 0x338)
 *     TextureSequence::~TextureSequence (this + 0x324)
 *     store _ZTV8Platform ... Platform's own teardown
 *
 * A destructor destroys its own members and no others, so those two subobjects
 * are this class's.  Both children's factories agree from the constructor side:
 * Thwomp_Spawn and Grindel_Spawn each store _ZTV11daDsnBase_c, then construct
 * TextureSequence at 0x324 and ShadowModel at 0x338, then store their own
 * vtable.  Everything between the two vtable stores is this class's constructor,
 * inlined.
 *
 * mFileTable AT 0x320 IS THIS CLASS'S TOO, read off its own methods rather than
 * a child's.  Slots 3 and 9 of the table above -- the functions the tree still
 * files under Thwomp::CleanupResources and Thwomp::Render -- both dereference
 * it, and neither child overrides either slot.  A method can reach its own
 * class's members and its ancestors', never a descendant's, so an offset above
 * Platform's 0x320 end that a daDsnBase_c method touches is daDsnBase_c's.
 *
 * SIZE 0x360 IS A FIELD SPAN, NOT A FACTORY LITERAL -- this class has no factory
 * of its own.  mShadowModel ends at 0x338 + 0x28 = 0x360, which is already
 * 4-aligned, so there is no trailing padding for sizeof to round away.  Both
 * children allocate more (Grindel 928 = 0x3a0, Thwomp 932 = 0x3a4) and both
 * place their own first observed member well above 0x360, which is consistent
 * but does not by itself pin the split -- the destructor above does.
 *
 * DESTRUCTOR IS INLINE, like Platform's above it: neither child's destructor
 * contains a `bl` to this one -- each stores this vptr and then runs this body
 * itself.  The out-of-line copy in ov091 exists because the vtable needs an
 * address for slots 16/17, not because the definition is out-of-line.
 */

struct daDsnBase_c : Platform {
    u8  pad_31e[0x2];                     /* Platform's tail padding, reused */
    s32 mFileTable;                       /* 0x320 -- SharedFilePtr *[], indices 0/1/3 used */
    TextureSequence mTextureSequence;     /* 0x324 */
    ShadowModel     mShadowModel;         /* 0x338 */

    virtual ~daDsnBase_c() {}
};

typedef char daDsnBase_c_size_must_be_0x360[sizeof(daDsnBase_c) == 0x360 ? 1 : -1];

#endif
