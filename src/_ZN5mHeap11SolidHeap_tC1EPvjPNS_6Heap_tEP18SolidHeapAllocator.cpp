//cpp
// @symbol _ZN5mHeap11SolidHeap_tC1EPvjPNS_6Heap_tEP18SolidHeapAllocator
#include "SolidHeap.h"

namespace mHeap {

SolidHeap_t::SolidHeap_t(void* start, u32 size, Heap_t* root,
                                 SolidHeapAllocator* allocator_)
    : Heap_t(start, size, root), allocator(allocator_)
{
}

} /* namespace mHeap */
