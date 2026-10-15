//cpp
// @symbol _ZN5mHeap9ExpHeap_tC1EPvjPNS_6Heap_tEP22ExpandingHeapAllocator
#include "ExpandingHeap.h"

namespace mHeap {

ExpHeap_t::ExpHeap_t(void* start, u32 size, Heap_t* root,
                             ExpandingHeapAllocator* allocator_)
    : Heap_t(start, size, root), allocator(allocator_)
{
}

} /* namespace mHeap */
