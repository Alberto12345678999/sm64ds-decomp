//cpp
// @symbol _ZN5mHeap11SolidHeap_tD1Ev
/* D1, the complete-object destructor. One `mHeap::SolidHeap_t::~SolidHeap_t()` definition makes
 * mwcc emit D0, D1 and D2 together; objisolate keeps the one this file is
 * bound to by its delinks entry, so the D0/D2 siblings carry the same
 * definition in their own files. */
#include "SolidHeap.h"

namespace mHeap {

SolidHeap_t::~SolidHeap_t()
{
}

} /* namespace mHeap */
