// @symbol func_ov022_02112380
/* recovered: vtable identified, declarations from a shared header */
#include "decl_Actor.h"
#include "decl_Model.h"
#include "decl_MovingMeshCollider.h"
#include "decl_common.h"
extern int _ZTV20daObjFl_Fall_Block_c[];
extern int _ZTV16daObjFallBlock_c[];
extern int _ZTV8Platform[];
/* recovered: vtable identified */
/* This is daObjFl_Fall_Block_c::~daObjFl_Fall_Block_c. The second store was
   resolved from the reloc table rather than from the name it used to carry: it
   targets 0x0213c5bc, which is daObjFallBlock_c's vtable. The spelling it had
   before existed in no symbols.txt, so this file never linked.
   vtable identified: VT0 = _ZTV20daObjFl_Fall_Block_c; VT1 = _ZTV16daObjFallBlock_c */
int *func_ov022_02112380(int *t)
{
    t[0] = (int)_ZTV20daObjFl_Fall_Block_c;
    t[0] = (int)_ZTV16daObjFallBlock_c;
    t[0] = (int)_ZTV8Platform;
    _ZN18MovingMeshColliderD1Ev((char *)t + 0x124);
    _ZN5ModelD1Ev((char *)t + 0xd4);
    _ZN5ActorD2Ev(t);
    return t;
}
