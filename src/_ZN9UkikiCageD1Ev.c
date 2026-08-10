// @symbol _ZN9UkikiCageD1Ev
/* recovered: named members + shared header, vtable identified, declarations from a shared header */
#include "decl_Actor.h"
#include "decl_Model.h"
#include "decl_MovingMeshCollider.h"
#include "decl_common.h"
/* Vtable references resolved against dsd's relocs.txt: each name below was
 * declared in decl_common.h but defined nowhere, so the file could not link.
 * The replacement is the symbol that already exists at the address the
 * relocation record names for this call site.
 *   _ZTV10dBgActor_c -> data_ov080_02128338  (ov080 @ 0x2128338)
 *   _ZTV15daObjHmMaruta_c -> _ZTV9UkikiCage  (ov030 @ 0x2115a48)
 *
 * The old names were not arbitrary -- they are the ROM's own RTTI class names --
 * but a base class like dBgActor_c has a SEPARATE vtable copy in each overlay
 * that uses it, so one global name cannot address them all. That is why these
 * were missing from symbols.txt rather than merely unnamed.
 */
extern int data_ov080_02128338[];
extern int _ZTV9UkikiCage[];
extern int _ZTV8Platform[];
/* recovered: named members + shared header, vtable identified */
/* vtable identified: VT0 = _ZTV9UkikiCage; VT1 = data_ov080_02128338 */
int *_ZN9UkikiCageD1Ev(int *t)
{
    t[0] = (int)_ZTV9UkikiCage;
    t[0] = (int)data_ov080_02128338;
    t[0] = (int)_ZTV8Platform;
    _ZN18MovingMeshColliderD1Ev((char *)t + 0x124);
    _ZN5ModelD1Ev((char *)t + 0xd4);
    _ZN5ActorD2Ev(t);
    return t;
}
