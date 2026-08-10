// @symbol Grindel_Spawn
/* recovered: vtable identified, declarations from a shared header */
#include "decl_ActorBase.h"
#include "decl_Platform.h"
#include "decl_ShadowModel.h"
#include "decl_TextureSequence.h"
#include "decl_common.h"
/* Vtable references resolved against dsd's relocs.txt: each name below was
 * declared in decl_common.h but defined nowhere, so the file could not link.
 * The replacement is the symbol that already exists at the address the
 * relocation record names for this call site.
 *   _ZTV7daDkk_c -> data_ov091_021351fc  (ov091 @ 0x21351fc)
 *
 * The old names were not arbitrary -- they are the ROM's own RTTI class names --
 * but a base class like dBgActor_c has a SEPARATE vtable copy in each overlay
 * that uses it, so one global name cannot address them all. That is why these
 * were missing from symbols.txt rather than merely unnamed.
 */
extern int data_ov091_021351fc[];
extern int data_ov025_02113850[];
/* recovered: vtable identified */
/* vtable identified: VT0 = data_ov091_021351fc */
int *Grindel_Spawn(void)
{
    int *p = (int *)_ZN9ActorBasenwEj(928);
    if (p) {
        _ZN8PlatformC2Ev(p);
        p[0] = (int)data_ov091_021351fc;
        _ZN15TextureSequenceC1Ev((char *)p + 0x324);
        _ZN11ShadowModelC1Ev((char *)p + 0x338);
        p[0] = (int)data_ov025_02113850;
    }
    return p;
}
