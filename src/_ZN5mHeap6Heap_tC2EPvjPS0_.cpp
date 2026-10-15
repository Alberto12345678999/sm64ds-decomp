//cpp
// @symbol _ZN5mHeap6Heap_tC2EPvjPS0_
#include "Heap.h"

namespace mHeap {

Heap_t::Heap_t(void* start, u32 size, Heap_t* root)
    : heapStart(start), heapSize(size), parentHeap(root), flags(0)
{
    flags = 0x4000;
}

} /* namespace mHeap */
