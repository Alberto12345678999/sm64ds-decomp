/* __register_global_object at 0x020731dc -- the C++ runtime (MSL's
 * global_destructor_chain.c). Every static initializer that constructs an
 * object with a destructor calls it, passing the object, the destructor and
 * a 12-byte node the compiler reserves next to the object. The node is
 * pushed onto __global_destructor_chain as {next, destructor, object}.
 * func_02072f3c runs the chain at exit, and FS_EndOverlay unlinks and runs
 * the nodes whose objects live in an overlay being unloaded. */

typedef struct DestructorChain {
    struct DestructorChain *next;
    void *destructor;
    void *object;
} DestructorChain;

extern DestructorChain *__global_destructor_chain;

void __register_global_object(void *object, void *destructor, void **regmem) {
    DestructorChain *node = (DestructorChain *)regmem;

    node->next = __global_destructor_chain;
    node->destructor = destructor;
    node->object = object;
    __global_destructor_chain = node;
}
