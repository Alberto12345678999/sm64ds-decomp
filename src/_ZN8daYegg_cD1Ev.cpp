//cpp
// @symbol _ZN8daYegg_cD1Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * One vtable store and five destructor calls, every one a consequence of
 * `struct daYegg_c : dEnemyBase_c` and the four members that declaration types, destroyed in
 * reverse declaration order, then dEnemyBase_c. This class adds no member with a destructor
 * of its own -- a Player pointer and three scalars.
 */
#include "daYegg_c.h"

daYegg_c::~daYegg_c()
{
}
