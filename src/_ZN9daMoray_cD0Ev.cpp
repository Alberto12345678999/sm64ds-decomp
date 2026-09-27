//cpp
// @symbol _ZN9daMoray_cD0Ev
/* recovered: real C++ deleting destructor -- the compiler emits the whole body
 *
 * Destroy through daMoray_c and dEnemyBase_c, then hand the object back through dActor_c's
 * inline operator delete, which is why nothing here mentions a heap. The array
 * cleanup at 0x448 is Vector3[7]; see the note in the D1 file.
 *
 * The hand-written version declared its own `extern void *data_020a0eac[]`,
 * which collides with the `void *` dActor_c.h supplies for that same heap once the
 * real header is in scope. Declaring the destructor is enough; the compiler
 * writes the rest.
 */
#include "daMoray_c.h"

#ifdef _MSC_VER
/* THE HOST NEEDS THE ROM'S FLAT D0 NAME, AND MSVC NEVER EMITS IT. MSVC
 * folds the Itanium destructor variants into the one ~daMoray_c() it
 * emits, which the class's D1 file already defines, so compiling the
 * definition below as well would define that symbol twice. This arm
 * spells out, in terms of it, what the deleting destructor this file is
 * enrolled for does: the D1 body, called qualified so it is a direct call
 * even where a header declares the destructor virtual, then the
 * class-specific operator delete. Nothing here reaches mwccarm: it builds
 * the `#else` arm and emits the ROM bytes it always emitted, and the
 * object is byte-identical either way. */
extern "C" daMoray_c *_ZN9daMoray_cD0Ev(daMoray_c *thiz)
{
    thiz->daMoray_c::~daMoray_c();         /* the D1 body, through the one host symbol */
    daMoray_c::operator delete(thiz);  /* the class-specific delete D0 ends with */
    return thiz;
}
#else
daMoray_c::~daMoray_c()
{
}
#endif
