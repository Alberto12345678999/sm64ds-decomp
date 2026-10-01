//cpp
// @symbol _ZN11daKpaTail_cD0Ev
/* recovered: real C++ deleting destructor -- the compiler emits the whole body
 *
 * D0 is vtable slot 17: destroy, then return the object to the actor heap. The
 * hand-written version spelled that out -- store the vtable, call the member's
 * destructor, chain to dActor_c, call Memory::Deallocate. All four come from the same
 * `~daKpaTail_c()` the D1 file declares; the deallocation is the inline
 * dActor_c::operator delete, which is why nothing here mentions the heap.
 *
 * The identical body in both files is not duplication: D1 and D0 are two of the
 * three functions the compiler emits from one destructor, and each file is bound
 * to one of them by config/arm9/overlays/ov060/delinks.txt.
 */
#include "daKpaTail_c.h"

#ifdef _MSC_VER
/* THE HOST NEEDS THE ROM'S FLAT D0 NAME, AND MSVC NEVER EMITS IT. MSVC
 * folds the Itanium destructor variants into the one ~daKpaTail_c() it
 * emits, which the class's D1 file already defines, so compiling the
 * definition below as well would define that symbol twice. This arm
 * spells out, in terms of it, what the deleting destructor this file is
 * enrolled for does: the D1 body, called qualified so it is a direct call
 * even where a header declares the destructor virtual, then the
 * class-specific operator delete. Nothing here reaches mwccarm: it builds
 * the `#else` arm and emits the ROM bytes it always emitted, and the
 * object is byte-identical either way. */
extern "C" daKpaTail_c *_ZN11daKpaTail_cD0Ev(daKpaTail_c *thiz)
{
    thiz->daKpaTail_c::~daKpaTail_c();    /* the D1 body, through the one host symbol */
    daKpaTail_c::operator delete(thiz);  /* the class-specific delete D0 ends with */
    return thiz;
}
#else
daKpaTail_c::~daKpaTail_c()
{
}
#endif
