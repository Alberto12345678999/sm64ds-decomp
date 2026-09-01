//cpp
// @symbol daObjWaterfall_c_classInit
#include "daObjWaterfall_c.h"

extern "C" {
extern void *_ZN7fBase_cnwEj(unsigned);
extern void _ZN8dActor_cC2Ev(void *);
}

/* Reconstructed source-style name: SM64DS proves the daObjWaterfall_c RTTI
 * identity, WATERFALL registry ID, descriptor/factory relationship, and
 * object shape; later EAD lineage supplies the classInit spelling prior.
 * Exact original SM64DS spelling is not preserved. Historical project alias:
 * WaterfallMist_Spawn.
 *
 * Natural `new daObjWaterfall_c` emits the right instructions but relocates
 * the allocation call to unresolved global `_Znwm`. mwccarm 2004/b56 also
 * rejects a placement-new declaration, so this C ABI factory retains the
 * retail fBase allocator while the class methods and destructor stay genuine
 * compiler-spelled C++. In this isolated production owner, config already
 * names `_ZTV` at the public function-slot address point. */
extern "C" daObjWaterfall_c *daObjWaterfall_c_classInit(void)
{
    daObjWaterfall_c *p =
        (daObjWaterfall_c *)_ZN7fBase_cnwEj(sizeof(daObjWaterfall_c));
    if (p) {
        _ZN8dActor_cC2Ev(p);
        *(int *)p = (int)_ZTV16daObjWaterfall_c;
    }
    return p;
}
