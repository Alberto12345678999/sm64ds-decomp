//cpp
/* leftovers:
 * The Heap* forms are defined first. Deferred codegen emits definitions in
 * reverse source order, and the convenience overloads call those forms.
 * A null heap selects defaultHeapPtr.
 */
/* Memory: allocate and free on a Heap, or on the default heap. */
#include "Memory.h"
#include "Heap.h"

namespace Memory {

// @symbol _ZN6Memory8AllocateEjiP4Heap
void *Allocate(u32 size, int align, Heap *heap)
{
    if (!heap)
        heap = defaultHeapPtr;
    return heap->Allocate(size, align);
}

// @symbol _ZN6Memory10DeallocateEPvP4Heap
void Deallocate(void *ptr, Heap *heap)
{
    if (!heap)
        heap = defaultHeapPtr;
    heap->Deallocate(ptr);
}

// @symbol _ZN6Memory8AllocateEji
void *Allocate(u32 size, int align)
{
    return Allocate(size, align, 0);
}

// @symbol _ZN6Memory8AllocateEj
void *Allocate(u32 size)
{
    return Allocate(size, 4, 0);
}

// @symbol _ZN6Memory10DeallocateEPv
void Deallocate(void *ptr)
{
    Deallocate(ptr, 0);
}

}
