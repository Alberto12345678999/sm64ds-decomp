struct Node72 {
    struct Node72 *next;
    void (*fn)(void *object, int v);
    void *object;
};
extern struct Node72 *data_020aa3f0;

/* __destroy_global_chain: pop each node that __register_global_object
   (func_020731dc) pushed, newest first, and call its destructor on its
   object with -1. exit (func_0206dbf8) calls it. */
void __destroy_global_chain(void) {
    struct Node72 *head = data_020aa3f0;
    if (head == 0) return;
    do {
        data_020aa3f0 = head->next;
        head->fn(head->object, -1);
        head = data_020aa3f0;
    } while (head != 0);
}
