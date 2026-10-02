//cpp
// @symbol _ZN8daBook_cD1Ev
/* The destructor is a real method now: the members it used to destroy by hand
   are typed members of daBook_c, so the compiler emits the same chain. See
   include/daBook_c.h for the two witnesses that establish the layout. */
#include "daBook_c.h"

daBook_c::~daBook_c()
{
}
