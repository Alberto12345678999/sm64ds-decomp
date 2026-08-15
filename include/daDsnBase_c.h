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
 * different overlays: the vtable and this class's own destructor pair are
 * emitted in ov091, at slots 16/17 of that table.  Not because ov091 holds a key
 * function -- the destructor below is inline, so this class has none -- but
 * because a vtable still needs one address per slot, and those copies are what
 * the linker kept.
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
 * mFileTable AT 0x320 IS THIS CLASS'S TOO, and BOTH CHILDREN RUNNING THE SAME
 * CODE is what settles it.  Slots 3 and 9 of the table above -- the functions the
 * tree still files under Thwomp::CleanupResources and Thwomp::Render -- both
 * dereference 0x320, and daDkk_c's vtable carries those same two addresses at
 * those same two slots.  One shared function reached through two different
 * derived types can only be reading storage the common base owns.  (The weaker
 * form of this argument, that a method never reaches a descendant's members, is
 * not true in general -- a downcast reaches anything -- so it is the shared slot
 * and not the method's own scope that does the work here.)  Platform ends at
 * 0x320, so the word belongs to this class.
 *
 * SIZE 0x360 IS A LOWER BOUND MADE EXACT BY CONVENTION, NOT A MEASUREMENT.  This
 * class has no factory of its own, so there is no literal to read.  The
 * destructor proves sizeof >= 0x360: mShadowModel ends at 0x338 + 0x28 = 0x360,
 * already 4-aligned, so nothing rounds away.  What the destructor CANNOT see is a
 * plain POD member -- nothing constructs or destroys one -- so daDsnBase_c owning
 * further words somewhere in 0x360..0x398 is not excluded by any evidence here.
 * 0x360 is the parsimonious read, the same convention the seven earlier
 * intermediates were modelled under, and it is what makes both children's
 * factory literals (Grindel 928 = 0x3a0, Thwomp 932 = 0x3a4) come out right.
 * Nothing about the byte match depends on where the split is drawn.
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
