//cpp
// @symbol _ZN24daPropeller_Heyho_Fire_cD0Ev
/* recovered: real C++ deleting destructor -- the compiler emits the whole body
 *
 * D0 is the DELETING destructor: destroy through this class and its bases, then
 * return the object to its heap. Declaring `~daPropeller_Heyho_Fire_c()` is enough -- mwcc emits
 * D2, D0 and D1 together and objisolate keeps the one this file is bound to.
 *
 * The deallocation is an inline operator delete -- dEnemyBase_c's, reachable because
 * dEnemyBase_c is this class's IMMEDIATE base.
 */
#include "daPropeller_Heyho_Fire_c.h"

#ifdef _MSC_VER
/* THE HOST NEEDS THE ROM'S FLAT D0 NAME, AND MSVC NEVER EMITS IT. MSVC
 * folds the Itanium destructor variants into the one ~daPropeller_Heyho_Fire_c() it
 * emits, which the class's D1 file already defines, so compiling the
 * definition below as well would define that symbol twice. This arm
 * spells out, in terms of it, what the deleting destructor this file is
 * enrolled for does: the D1 body, called qualified so it is a direct call
 * even where a header declares the destructor virtual, then the
 * class-specific operator delete. Nothing here reaches mwccarm: it builds
 * the `#else` arm and emits the ROM bytes it always emitted, and the
 * object is byte-identical either way. */
extern "C" daPropeller_Heyho_Fire_c *_ZN24daPropeller_Heyho_Fire_cD0Ev(daPropeller_Heyho_Fire_c *thiz)
{
    thiz->daPropeller_Heyho_Fire_c::~daPropeller_Heyho_Fire_c();        /* the D1 body, through the one host symbol */
    daPropeller_Heyho_Fire_c::operator delete(thiz);  /* the class-specific delete D0 ends with */
    return thiz;
}
#else
daPropeller_Heyho_Fire_c::~daPropeller_Heyho_Fire_c()
{
}
#endif
