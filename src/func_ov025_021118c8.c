// @symbol func_ov025_021118c8
/* recovered: vtable identified, declarations from a shared header */
#include "decl_Actor.h"
#include "decl_Model.h"
#include "decl_MovingMeshCollider.h"
#include "decl_ShadowModel.h"
#include "decl_common.h"
extern int _ZTV7daDkk_c[];
extern int _ZTV11daDsnBase_c[];
extern int _ZTV8Platform[];
/* recovered: vtable identified */
/* This is daDkk_c::~daDkk_c -- slot 16 of _ZTV7daDkk_c. The second store was
   resolved from the reloc table rather than from the name it used to carry:
   the word at 0x02111920 targets 0x021351fc, which is daDsnBase_c's vtable.
   The spelling it had before existed in no symbols.txt, so this file never
   linked.
   vtable identified: VT0 = _ZTV7daDkk_c; VT1 = _ZTV11daDsnBase_c */
extern void _ZN15TextureSequenceD1Ev(void *);
int *func_ov025_021118c8(int *t)
{
    t[0] = (int)_ZTV7daDkk_c;
    t[0] = (int)_ZTV11daDsnBase_c;
    _ZN11ShadowModelD1Ev((char *)t + 0x338);
    _ZN15TextureSequenceD1Ev((char *)t + 0x324);
    t[0] = (int)_ZTV8Platform;
    _ZN18MovingMeshColliderD1Ev((char *)t + 0x124);
    _ZN5ModelD1Ev((char *)t + 0xd4);
    _ZN5ActorD2Ev(t);
    return t;
}
