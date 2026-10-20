//cpp
/* dCamera_c's deleting and complete destructors.
 * arm9 .text 0x0200705c..0x020070e8 (D1 then D0).
 *
 * Not part of src/engine/view/d_camera.cpp (0x0200bec4..0x0200e494).
 * func_020070e8 is the next function, a camera orbit helper, and
 * Vector3::~Vector3 at 0x020072c0 is a different class. The handlers
 * through 0x0200bb28 stay out: func_0200bb28 needs opt_common_subs off
 * while Behavior needs it on, and that pragma is TU-global under
 * deferred codegen.
 *
 * defer_codegen off emits D1, D0, then a homeless D2. Retail
 * _ZTV9dCamera_c stays at 0x02086f84; this TU's copy is discarded.
 */
#include "dCamera_c.h"

#ifdef _MSC_VER
/* The host needs the ROM's flat D0 name. MSVC folds the Itanium variants
 * into the one ~dCamera_c() it emits, so the deleting destructor is spelled
 * out here: the D1 body, called qualified, then the class-specific delete.
 * Nothing in this arm reaches mwccarm. */
dCamera_c::~dCamera_c() {}

extern "C" dCamera_c *_ZN9dCamera_cD0Ev(dCamera_c *thiz) {
    thiz->dCamera_c::~dCamera_c();
    dCamera_c::operator delete(thiz);
    return thiz;
}
#else
#pragma defer_codegen off

// @symbol _ZN9dCamera_cD1Ev
// @symbol _ZN9dCamera_cD0Ev
dCamera_c::~dCamera_c() {}
#endif
