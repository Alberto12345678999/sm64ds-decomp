//cpp
// @symbol _ZN11daChScene_c16CleanupResourcesEv
/* recovered: shared header, real C++ method
 *
 * `return 1`. daChScene_c claims no files -- it is a trigger volume with no
 * model -- so there is nothing to release and the override just reports
 * success.
 */
#include "daChScene_c.h"

int daChScene_c::CleanupResources()
{
    return 1;
}
