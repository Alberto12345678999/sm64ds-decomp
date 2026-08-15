//cpp
// @symbol _ZN18RotatingPlatformWfD0Ev
/* recovered: real C++ deleting destructor -- the compiler emits the whole body
 *
 * D0 is vtable slot 17: destroy through this class, its daObjKaitendai_c base and
 * its Platform base -- which is why THREE vptr stores appear -- then return the
 * object to the actor heap. The deallocation is Actor's inline operator delete,
 * so nothing here names a heap.
 *
 * An earlier comment on this file called it OnYoshiTryEat, which is slot 18 --
 * off by one. This body stores the class vtables, destroys the members and
 * deallocates; no eat handler does any of that.
 *
 * The body is the same `~RotatingPlatformWf()` the D1 file declares; mwcc emits
 * D2, D0 and D1 together and objisolate keeps whichever one the file is bound to.
 */
#include "RotatingPlatformWf.h"

RotatingPlatformWf::~RotatingPlatformWf()
{
}
