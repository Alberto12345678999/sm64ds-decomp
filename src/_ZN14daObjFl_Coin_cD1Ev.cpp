//cpp
// @symbol _ZN14daObjFl_Coin_cD1Ev
/* recovered: real C++ destructor -- the compiler emits the whole body.
 * Vtable slot 16: one vtable store, the members in reverse, then ~dActor_c. */
#include "daObjFl_Coin_c.h"

/* The destructor is inline in the header. This call is what asks for D1.
 * objisolate keeps the variant this file is bound to. */
void daObjFl_Coin_c_EmitDestructor(daObjFl_Coin_c *coin)
{
    coin->~daObjFl_Coin_c();
}
