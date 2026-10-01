//cpp
// @symbol _ZN15daObjTatefuda_cD1Ev
/* recovered: real C++ destructor -- inline in the class, forced out of line here
 *
 * daObjTatefuda_c.h defines `~daObjTatefuda_c() {}` in the class body on purpose (which is
 * why its derived-free destructors inline, and why the header comment keeps
 * it). A TU that merely includes the header then emits no _ZN15daObjTatefuda_cD1Ev,
 * but the ROM carries one at ov002 0x020badd0 -- so this TU asks for it
 * explicitly: the call below cannot be satisfied by the inline copy alone,
 * mwcc has to emit the out-of-line variant, and objisolate drops the forcing
 * function's own .text (notes/dtor-migration.md section 3). The body it
 * emits is the class's: the dBgCh_Actr, ShadowModel, dCcAc_c, dBgW_KcMbg and
 * Model members torn down in reverse declaration order, the dBgActor_c base
 * step last.
 */
#include "daObjTatefuda_c.h"

void _force_SignPostD1(daObjTatefuda_c *p)
{
    p->~daObjTatefuda_c();
}
