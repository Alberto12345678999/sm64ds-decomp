struct Node72 {
    struct Node72 *next;
    void (*fn)(void *object, int v);
    void *object;
};
extern struct Node72 *__global_destructor_chain;

void func_02072f3c(void) {
    struct Node72 *head = __global_destructor_chain;
    if (head == 0) return;
    do {
        __global_destructor_chain = head->next;
        head->fn(head->object, -1);
        head = __global_destructor_chain;
    } while (head != 0);
}
