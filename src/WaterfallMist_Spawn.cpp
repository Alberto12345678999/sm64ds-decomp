//cpp
// @symbol WaterfallMist_Spawn
#include "daObjWaterfall_c.h"

extern "C" {
extern int _ZTV16daObjWaterfall_c[];
extern void *_ZN7fBase_cnwEj(unsigned);
extern void _ZN8dActor_cC2Ev(void *);
}

/* Natural `new daObjWaterfall_c` emits the right instructions but relocates
 * the allocation call to unresolved global `_Znwm`. mwccarm 2004/b56 also
 * rejects a placement-new declaration, so this C ABI factory retains the
 * retail fBase allocator while the class methods and destructor stay genuine
 * compiler-spelled C++. In this isolated production owner, config already
 * names `_ZTV` at the public function-slot address point. */
extern "C" daObjWaterfall_c *WaterfallMist_Spawn(void)
{
    daObjWaterfall_c *p =
        (daObjWaterfall_c *)_ZN7fBase_cnwEj(sizeof(daObjWaterfall_c));
    if (p) {
        _ZN8dActor_cC2Ev(p);
        *(int *)p = (int)_ZTV16daObjWaterfall_c;
    }
    return p;
}
