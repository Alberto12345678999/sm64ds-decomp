//cpp
// @symbol _ZN10dScStage_cD0Ev
/* recovered: real C++ deleting destructor -- the compiler emits the whole body
 *
 * Destroy through dScStage_c and dScene_c (see _ZN10dScStage_cD1Ev.cpp), then hand the
 * object back through dScene_c's inline operator delete -- declared there
 * rather than on dBase_c, because mwcc only inlines it when found on
 * the class itself or its IMMEDIATE base, which for dScStage_c is dScene_c.
 */
#include "dScStage_c.h"

#ifdef _MSC_VER
/* THE HOST NEEDS THE ROM'S FLAT D0 NAME, AND MSVC NEVER EMITS IT. MSVC
 * folds the Itanium destructor variants into the one ~dScStage_c() it
 * emits, which the class's D1 file already defines, so compiling the
 * definition below as well would define that symbol twice. This arm
 * spells out, in terms of it, what the deleting destructor this file is
 * enrolled for does: the D1 body, called qualified so it is a direct call
 * even where a header declares the destructor virtual, then the
 * class-specific operator delete. Nothing here reaches mwccarm: it builds
 * the `#else` arm and emits the ROM bytes it always emitted, and the
 * object is byte-identical either way. */
extern "C" dScStage_c *_ZN10dScStage_cD0Ev(dScStage_c *thiz)
{
    thiz->dScStage_c::~dScStage_c();         /* the D1 body, through the one host symbol */
    dScStage_c::operator delete(thiz);  /* the class-specific delete D0 ends with */
    return thiz;
}
#else
dScStage_c::~dScStage_c()
{
}
#endif
