// @symbol _ZN4HeapD1Ev
/* recovered: named members + shared header */
#include "Heap.h"
/* Heap::~Heap() at 0x0203ca44 -- complete object destructor (D1).
 * A trivial destructor whose only effect is to reset the object's vtable pointer
 * (at offset 0x00) back to Heap's own vtable. Returns void.
 *
 * _ZTVN5mHeap6Heap_tE is the Itanium vtable symbol for Heap. The stored address is a
 * pooled wildcard reloc, so the extern name is not byte-verified -- it is named
 * by convention. */

extern int _ZTVN5mHeap6Heap_tE[]; /* vtable for Heap */

void _ZN4HeapD1Ev(int *self)
{
    self[0] = (int)_ZTVN5mHeap6Heap_tE; /* reset vptr at +0x00 */
}
