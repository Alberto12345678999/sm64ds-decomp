// @symbol RollingLogLll_Spawn
/* recovered: vtable identified, declarations from a shared header */
#include "decl_ActorBase.h"
#include "decl_Platform.h"
#include "decl_common.h"
extern int _ZTV13RollingLogLll[];
/* recovered: vtable identified */
/* vtable identified: VT0 = _ZTV13daObjMaruta_c (daObjMaruta_c, the base)
   Was spelled with that class's own ROM name -- a symbol that exists in NO symbols.txt, so this file
   never linked and the ROM served its own bytes. The relocation at this
   store targets 0x02128338, which is daObjMaruta_c's vtable: the old name sat one table
   late, naming the child while pointing at the base. */
int *RollingLogLll_Spawn(void)
{
    int *p = (int *)_ZN9ActorBasenwEj(836);
    if (p) {
        _ZN8PlatformC2Ev(p);
        p[0] = (int)_ZTV13daObjMaruta_c;
        p[0] = (int)_ZTV13RollingLogLll;
    }
    return p;
}
