struct Node72 {
    struct Node72 *next;
    void (*fn)(void *object, int v);
    void *object;
};
extern struct Node72 *__global_destructor_chain;

/* __destroy_global_chain: pop each node that __register_global_object
   pushed, newest first, and call its destructor on its object with -1.
   exit (func_0206dbf8) calls it. */
void __destroy_global_chain(void) {
    struct Node72 *head = __global_destructor_chain;
    if (head == 0)
        return;
    do {
        __global_destructor_chain = head->next;
        head->fn(head->object, -1);
        head = __global_destructor_chain;
    } while (head != 0);
}
