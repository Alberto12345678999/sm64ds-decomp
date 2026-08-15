// @symbol Grindel_Spawn
/* recovered: vtable identified, declarations from a shared header */
#include "decl_ActorBase.h"
#include "decl_Platform.h"
#include "decl_ShadowModel.h"
#include "decl_TextureSequence.h"
#include "decl_common.h"
extern int _ZTV7daDkk_c[];
extern int _ZTV11daDsnBase_c[];
/* recovered: vtable identified */
/* THE FIRST STORE IS THE BASE'S, NOT THIS CLASS'S. Both stores used to be
   spelled _ZTV7daDkk_c, which the reloc table refutes: the literal pool at
   0x02111d38 targets 0x021351fc (daDsnBase_c's vtable) and only the one at
   0x02111d3c targets 0x02113850 (daDkk_c's own). Two distinct pool entries,
   so the source has to name two distinct symbols. Nothing caught this because
   the file carries no `complete` marker in ov025/delinks.txt and has therefore
   never been compiled.
   The shape matches Thwomp_Spawn exactly -- same base, same two subobjects at
   the same offsets -- which is what daDsnBase_c predicts for both children.
   vtable identified: VT0 = _ZTV11daDsnBase_c; VT1 = _ZTV7daDkk_c */
int *Grindel_Spawn(void)
{
    int *p = (int *)_ZN9ActorBasenwEj(928);
    if (p) {
        _ZN8PlatformC2Ev(p);
        p[0] = (int)_ZTV11daDsnBase_c;
        _ZN15TextureSequenceC1Ev((char *)p + 0x324);
        _ZN11ShadowModelC1Ev((char *)p + 0x338);
        p[0] = (int)_ZTV7daDkk_c;
    }
    return p;
}
