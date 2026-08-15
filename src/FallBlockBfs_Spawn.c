// @symbol FallBlockBfs_Spawn
/* recovered: vtable identified, declarations from a shared header */
#include "decl_ActorBase.h"
#include "decl_Platform.h"
#include "decl_common.h"
extern int _ZTV12FallBlockBfs[];
/* recovered: vtable identified */
/* vtable identified: VT0 = _ZTV16daObjFallBlock_c (daObjFallBlock_c, the base)
   Was spelled _ZTV21daObjKm2_Fall_Block_c -- a symbol that exists in NO symbols.txt, so this file
   never linked and the ROM served its own bytes. The relocation at this
   store targets 0x0213c5bc, which is daObjFallBlock_c's vtable: the old name sat one table
   late, naming the child while pointing at the base. */
int *FallBlockBfs_Spawn(void)
{
    int *p = (int *)_ZN9ActorBasenwEj(844);
    if (p) {
        _ZN8PlatformC2Ev(p);
        p[0] = (int)_ZTV16daObjFallBlock_c;
        p[0] = (int)_ZTV12FallBlockBfs;
    }
    return p;
}
