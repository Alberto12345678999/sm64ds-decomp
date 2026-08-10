// @symbol _ZN11FallBlockWfD0Ev
/* recovered: named members + shared header, vtable identified, declarations from a shared header */
#include "decl_Actor.h"
#include "decl_Model.h"
#include "decl_MovingMeshCollider.h"
#include "decl_common.h"
/* Symbols resolved against dsd's relocs.txt: each name below was declared
 * but defined nowhere, so this file could not be linked into the ROM. The
 * replacement is the symbol that already exists at the address the relocation
 * record names for this site; declarations are cloned from the originals so
 * the types -- which decide how the compiler indexes them -- are unchanged.
 *   G0 -> data_020a0eac  (main @ 0x20a0eac)
 *   VT1 -> data_ov098_0213c5bc  (ov098 @ 0x213c5bc)
 *   VT2 -> _ZTV8Platform  (ov002 @ 0x210ae38)
 *   _ZTV10dBgActor_c -> _ZTV11FallBlockWf  (ov015 @ 0x21148dc)
 */
extern int data_ov098_0213c5bc[];
extern int _ZTV8Platform[];
extern int _ZTV11FallBlockWf[];
/* recovered: named members + shared header, vtable identified */
/* vtable identified: VT0 = _ZTV11FallBlockWf */
extern void *data_020a0eac;
int *_ZN11FallBlockWfD0Ev(int *t)
{
    t[0] = (int)_ZTV11FallBlockWf;
    t[0] = (int)data_ov098_0213c5bc;
    t[0] = (int)_ZTV8Platform;
    _ZN18MovingMeshColliderD1Ev((char *)t + 0x124);
    _ZN5ModelD1Ev((char *)t + 0xd4);
    _ZN5ActorD2Ev(t);
    _ZN6Memory10DeallocateEPvP4Heap(t, data_020a0eac);
    return t;
}
