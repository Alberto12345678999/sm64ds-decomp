extern void *_ZTVN5mHeap6Heap_tE;
extern void _ZN6Memory16operator_delete2EPv(void *ptr);

struct Heap {
    void *vtable;
};

void *_ZN4HeapD0Ev(struct Heap *self)
{
    self->vtable = &_ZTVN5mHeap6Heap_tE;
    _ZN6Memory16operator_delete2EPv(self);
    return self;
}
