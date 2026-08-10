// @symbol _ZN12FallBlockBfsD0Ev
/* recovered: named members + shared header, vtable identified, declarations from a shared header */
#include "decl_Actor.h"
#include "decl_Model.h"
#include "decl_MovingMeshCollider.h"
#include "decl_common.h"
/* Vtable references resolved against dsd's relocs.txt: each name below was
 * declared in decl_common.h but defined nowhere, so the file could not link.
 * The replacement is the symbol that already exists at the address the
 * relocation record names for this call site.
 *   _ZTV10dBgActor_c -> data_ov098_0213c5bc  (ov098 @ 0x213c5bc)
 *   _ZTV21daObjKm2_Fall_Block_c -> _ZTV12FallBlockBfs  (ov045 @ 0x21130f4)
 *
 * The old names were not arbitrary -- they are the ROM's own RTTI class names --
 * but a base class like dBgActor_c has a SEPARATE vtable copy in each overlay
 * that uses it, so one global name cannot address them all. That is why these
 * were missing from symbols.txt rather than merely unnamed.
 */
extern int data_ov098_0213c5bc[];
extern int _ZTV12FallBlockBfs[];
extern int _ZTV8Platform[];
/* recovered: named members + shared header, vtable identified */
/* vtable identified: VT0 = _ZTV12FallBlockBfs; VT1 = data_ov098_0213c5bc */
extern void *data_020a0eac;
int *_ZN12FallBlockBfsD0Ev(int *t)
{
    t[0] = (int)_ZTV12FallBlockBfs;
    t[0] = (int)data_ov098_0213c5bc;
    t[0] = (int)_ZTV8Platform;
    _ZN18MovingMeshColliderD1Ev((char *)t + 0x124);
    _ZN5ModelD1Ev((char *)t + 0xd4);
    _ZN5ActorD2Ev(t);
    _ZN6Memory10DeallocateEPvP4Heap(t, data_020a0eac);
    return t;
}
