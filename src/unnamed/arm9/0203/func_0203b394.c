/* fBase_c::SceneNode (fBase_c.h), as func_0203b358.c views it. */
struct Node {
    struct Node *parent; /* 0x00 */
    struct Node *child;  /* 0x04 */
};
extern struct Node *func_0203b358(struct Node *node);

/* The pre-order successor of `node` in the scene tree: its first child,
   else the first node after its subtree (func_0203b358). func_020431c4
   (ActorBase.cpp) and func_020441cc (fListNode.cpp) walk with it; the
   void * return is fListNode.cpp's declaration. */
void *func_0203b394(struct Node *node) {
    struct Node *p = node->child;
    if (p == 0)
        p = func_0203b358(node);
    return p;
}
