#include "Ov007OamNode.h"

/* Appends child to parent's child list: sets child's owner, then links it
 * at the head slot if that is empty, else at the end of the sibling chain.
 * Reusing the parameter `parent` as the list walker keeps the walker web
 * pinned to r0 (forces the ROM's `mov r0,r2`). */
void func_ov007_020c10b0(Ov007OamNode *parent, Ov007OamNode *child) {
    child->owner = parent;
    if (parent->head == 0) {
        parent->head = child;
        return;
    }
    parent = parent->head;
    while (parent->next != 0)
        parent = parent->next;
    parent->next = child;
}
