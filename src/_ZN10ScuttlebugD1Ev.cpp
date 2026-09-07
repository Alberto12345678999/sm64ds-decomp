//cpp
// @symbol _ZN10ScuttlebugD1Ev
/* The class-body destructor is real C++ -- Scuttlebug.h defines it inline,
 * because the cartridge emits D1 (0x0211f000) then D0 (0x0211f048) with no D2
 * anywhere in ov071, which is what mwccarm 2004/b56 does for an inline
 * destructor. This otherwise-unused explicit call forces the compiler to
 * materialize the out-of-line D1 copy; objisolate keeps that symbol and
 * discards the forcing wrapper. Vtable slot 16: one vtable store, the four
 * members in reverse, then ~dActor_c. */
#include "Scuttlebug.h"

void Scuttlebug_EmitDestructor(Scuttlebug *p)
{
    p->~Scuttlebug();
}
