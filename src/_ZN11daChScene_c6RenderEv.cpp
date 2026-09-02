//cpp
// @symbol _ZN11daChScene_c6RenderEv
/* recovered: shared header, real C++ method
 *
 * `return 1` and nothing else -- the door is INVISIBLE. It is a trigger
 * volume, so there is no model to draw; the override exists to report success
 * without doing anything, which is why the whole body is two instructions.
 */
#include "daChScene_c.h"

int daChScene_c::Render()
{
    return 1;
}
