// @symbol FallBlockLll_Spawn
/* recovered: vtable identified, declarations from a shared header */
#include "decl_ActorBase.h"
#include "decl_Platform.h"
#include "decl_common.h"
/* Vtable references resolved against dsd's relocs.txt: each name below was
 * declared in decl_common.h but defined nowhere, so the file could not link.
 * The replacement is the symbol that already exists at the address the
 * relocation record names for this call site.
 *   _ZTV20daObjFl_Fall_Block_c -> data_ov098_0213c5bc  (ov098 @ 0x213c5bc)
 *
 * The old names were not arbitrary -- they are the ROM's own RTTI class names --
 * but a base class like dBgActor_c has a SEPARATE vtable copy in each overlay
 * that uses it, so one global name cannot address them all. That is why these
 * were missing from symbols.txt rather than merely unnamed.
 */
extern int data_ov098_0213c5bc[];
extern int data_ov022_021142c4[];
/* recovered: vtable identified */
/* vtable identified: VT0 = data_ov098_0213c5bc */
int *FallBlockLll_Spawn(void)
{
    int *p = (int *)_ZN9ActorBasenwEj(844);
    if (p) {
        _ZN8PlatformC2Ev(p);
        p[0] = (int)data_ov098_0213c5bc;
        p[0] = (int)data_ov022_021142c4;
    }
    return p;
}
