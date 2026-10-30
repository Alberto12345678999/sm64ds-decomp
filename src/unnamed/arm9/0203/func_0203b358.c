/* fBase_c::SceneNode (fBase_c.h) as the scene-tree walks see it. The tag
   is fListNode.cpp's, which declares func_0203b394 on its own view of the
   same node (ProcessTree::Node, the owner at 0x10). */
struct Node {
    struct Node *parent; /* 0x00 */
    struct Node *child;  /* 0x04 */
    struct Node *prev;   /* 0x08 */
    struct Node *next;   /* 0x0c */
};

/* The first node after `node`'s subtree in a pre-order walk: its next
   sibling, else the next sibling of the nearest ancestor that has one;
   0 past the root. func_020431c4 (ActorBase.cpp) stops its descendant scan
   there, and func_0203b394 steps to it once a subtree is done. */
struct Node *func_0203b358(struct Node *node) {
    struct Node *n;
    if (node->next)
        return node->next;
    n = node->parent;
    while (n) {
        if (n->next)
            return n->next;
        n = n->parent;
    }
    return 0;
}
