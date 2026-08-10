// @symbol func_ov025_02111928
// recovered name: daDkk_c_OnYoshiTryEat
/* recovered: vtable identified, renamed to Class_Method, declarations from a shared header */
#include "decl_Actor.h"
#include "decl_Model.h"
#include "decl_MovingMeshCollider.h"
#include "decl_ShadowModel.h"
#include "decl_common.h"
/* Symbols resolved against dsd's relocs.txt: each name below was declared
 * but defined nowhere, so this file could not be linked into the ROM. The
 * replacement is the symbol that already exists at the address the relocation
 * record names for this site; declarations are cloned from the originals so
 * the types -- which decide how the compiler indexes them -- are unchanged.
 *   G0 -> data_020a0eac  (main @ 0x20a0eac)
 *   VT0 -> data_ov025_02113850  (ov025 @ 0x2113850)
 *   VT1 -> data_ov091_021351fc  (ov091 @ 0x21351fc)
 *   VT2 -> _ZTV8Platform  (ov002 @ 0x210ae38)
 */
extern int data_ov025_02113850[];
extern int data_ov091_021351fc[];
extern int _ZTV8Platform[];
/* recovered: vtable identified, renamed to Class_Method */
/* daDkk_c::OnYoshiTryEat - recovered from vtable slot identity */
extern void _ZN15TextureSequenceD1Ev(void *);
extern void *data_020a0eac;
int *func_ov025_02111928(int *t)
{
    t[0] = (int)data_ov025_02113850;
    t[0] = (int)data_ov091_021351fc;
    _ZN11ShadowModelD1Ev((char *)t + 0x338);
    _ZN15TextureSequenceD1Ev((char *)t + 0x324);
    t[0] = (int)_ZTV8Platform;
    _ZN18MovingMeshColliderD1Ev((char *)t + 0x124);
    _ZN5ModelD1Ev((char *)t + 0xd4);
    _ZN5ActorD2Ev(t);
    _ZN6Memory10DeallocateEPvP4Heap(t, data_020a0eac);
    return t;
}
