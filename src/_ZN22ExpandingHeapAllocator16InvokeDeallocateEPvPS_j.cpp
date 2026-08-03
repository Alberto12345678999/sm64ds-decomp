//cpp
extern "C" {
extern "C" void _ZN22ExpandingHeapAllocator10DeallocateEPv(void*, void*);

void _ZN22ExpandingHeapAllocator16InvokeDeallocateEPvPS_j(void* p, void* alloc, unsigned int size) {
    _ZN22ExpandingHeapAllocator10DeallocateEPv(alloc, p);
}
}
