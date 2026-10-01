//cpp
// @symbol _ZN11daKpaTail_c16CleanupResourcesEv
/* recovered: shared header, real C++ method
 *
 * `return 1`, no releases. The tail shares Bowser's translation unit and his
 * files -- tu_map puts both classes in one TU at 0x2111900..0x2116484 -- so
 * Bowser::CleanupResources frees everything and the tail takes no reference of
 * its own.
 */
#include "daKpaTail_c.h"

int daKpaTail_c::CleanupResources()
{
    return 1;
}
