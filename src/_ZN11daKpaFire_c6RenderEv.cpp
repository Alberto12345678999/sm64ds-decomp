//cpp
// @symbol _ZN11daKpaFire_c6RenderEv
/* recovered: shared header, real C++ method
 *
 * `return 1` and nothing else -- the whole ROM body is `mov r0,#1; bx lr`.
 * The flame is drawn by the particle system, so the render slot only has to
 * report success.
 */
#include "daKpaFire_c.h"

int daKpaFire_c::Render()
{
    return 1;
}
