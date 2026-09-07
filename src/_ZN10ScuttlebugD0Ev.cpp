//cpp
// @symbol _ZN10ScuttlebugD0Ev
/* D0 is the DELETING destructor: destroy through this class and its bases --
 * which is why more than one vptr store appears -- then return the object to
 * its heap. Nobody writes that body; a delete-expression is enough to force
 * mwccarm to emit it from the inline class-body destructor in Scuttlebug.h,
 * and the inherited inline dActor_c::operator delete supplies the actor-heap
 * release the ROM uses. objisolate keeps the enrolled D0 and discards the
 * forcing wrapper. */
#include "Scuttlebug.h"

void Scuttlebug_EmitDeletingDestructor(Scuttlebug *p)
{
    delete p;
}
