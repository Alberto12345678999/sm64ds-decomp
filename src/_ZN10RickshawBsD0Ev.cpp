//cpp
// @symbol _ZN10RickshawBsD0Ev
/* recovered: real C++ deleting destructor -- the compiler emits the whole body
 *
 * D0 is vtable slot 17: destroy through this class, its daObjKaitendai_c base
 * and its Platform base -- hence THREE vptr stores -- then return the object to
 * the actor heap through Actor's inline operator delete, which is why no heap
 * is named here.
 *
 * The body is the same `~RickshawBs()` the D1 file declares; mwcc emits D2, D0 and
 * D1 together and objisolate keeps whichever one the file is bound to.
 */
#include "RickshawBs.h"

RickshawBs::~RickshawBs()
{
}
