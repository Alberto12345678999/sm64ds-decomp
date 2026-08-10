// @symbol func_ov025_021118c8
/* recovered: vtable identified, declarations from a shared header */
#include "decl_Actor.h"
#include "decl_Model.h"
#include "decl_MovingMeshCollider.h"
#include "decl_ShadowModel.h"
#include "decl_common.h"
/* Vtable references resolved against dsd's relocs.txt: each name below was
 * declared in decl_common.h but defined nowhere, so the file could not link.
 * The replacement is the symbol that already exists at the address the
 * relocation record names for this call site.
 *   _ZTV10dBgActor_c -> data_ov091_021351fc  (ov091 @ 0x21351fc)
 *   _ZTV7daDkk_c -> data_ov025_02113850  (ov025 @ 0x2113850)
 *
 * The old names were not arbitrary -- they are the ROM's own RTTI class names --
 * but a base class like dBgActor_c has a SEPARATE vtable copy in each overlay
 * that uses it, so one global name cannot address them all. That is why these
 * were missing from symbols.txt rather than merely unnamed.
 */
extern int data_ov091_021351fc[];
extern int data_ov025_02113850[];
extern int _ZTV8Platform[];
/* recovered: vtable identified */
/* vtable identified: VT0 = data_ov025_02113850; VT1 = data_ov091_021351fc */
extern void _ZN15TextureSequenceD1Ev(void *);
int *func_ov025_021118c8(int *t)
{
    t[0] = (int)data_ov025_02113850;
    t[0] = (int)data_ov091_021351fc;
    _ZN11ShadowModelD1Ev((char *)t + 0x338);
    _ZN15TextureSequenceD1Ev((char *)t + 0x324);
    t[0] = (int)_ZTV8Platform;
    _ZN18MovingMeshColliderD1Ev((char *)t + 0x124);
    _ZN5ModelD1Ev((char *)t + 0xd4);
    _ZN5ActorD2Ev(t);
    return t;
}
