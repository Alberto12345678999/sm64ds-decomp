//cpp
// @symbol _ZN12daMugenBGM_cD0Ev

#include "daMugenBGM_c.h"

#ifdef _MSC_VER
/* THE HOST NEEDS THE ROM'S FLAT D0 NAME, AND MSVC NEVER EMITS IT. MSVC
 * folds the Itanium destructor variants into the one ~daMugenBGM_c() it
 * emits, which the class's D1 file already defines, so compiling the
 * definition below as well would define that symbol twice. This arm
 * spells out, in terms of it, what the deleting destructor this file is
 * enrolled for does: the D1 body, called qualified so it is a direct call
 * even where a header declares the destructor virtual, then the
 * class-specific operator delete. Nothing here reaches mwccarm: it builds
 * the `#else` arm and emits the ROM bytes it always emitted, and the
 * object is byte-identical either way. */
extern "C" daMugenBGM_c *_ZN12daMugenBGM_cD0Ev(daMugenBGM_c *thiz)
{
    thiz->daMugenBGM_c::~daMugenBGM_c();      /* the D1 body, through the one host symbol */
    daMugenBGM_c::operator delete(thiz);  /* the class-specific delete D0 ends with */
    return thiz;
}
#else
daMugenBGM_c::~daMugenBGM_c()
{
}
#endif
