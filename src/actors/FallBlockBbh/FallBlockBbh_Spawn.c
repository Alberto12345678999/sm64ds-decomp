// @symbol FallBlockBbh_Spawn
/* recovered: vtable identified, declarations from a shared header */
#include "decl_ActorBase.h"
#include "decl_Platform.h"
#include "decl_common.h"
extern int _ZTV12FallBlockBbh[];
extern int _ZTV16daObjFallBlock_c[];
/* recovered: vtable identified */
/* The first store was resolved from the reloc table rather than from the name it
   used to carry: it targets 0x0213c5bc, which is daObjFallBlock_c's vtable. The
   spelling it had before existed in no symbols.txt, so this file never linked.
   vtable identified: VT0 = _ZTV16daObjFallBlock_c */
int *FallBlockBbh_Spawn(void)
{
    int *p = (int *)_ZN9ActorBasenwEj(844);
    if (p) {
        _ZN8PlatformC2Ev(p);
        p[0] = (int)_ZTV16daObjFallBlock_c;
        p[0] = (int)_ZTV12FallBlockBbh;
    }
    return p;
}
