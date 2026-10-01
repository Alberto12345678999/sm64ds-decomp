//cpp
// @symbol _ZN11daKpaFire_c16CleanupResourcesEv
/* recovered: shared header, real C++ method
 *
 * `return 1` with no releases, which is the finding rather than a stub:
 * daKpaFire_c holds no SharedFilePtr of its own. Bowser loads and frees the
 * whole fight's files -- 0x1c models, six more, and three singles -- and the
 * fire it breathes borrows from that set without taking a reference.
 */
#include "daKpaFire_c.h"

int daKpaFire_c::CleanupResources()
{
    return 1;
}
