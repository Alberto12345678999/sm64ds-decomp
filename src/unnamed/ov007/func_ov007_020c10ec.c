#include "Ov007OamNode.h"

/* Resets an OAM node: at the origin, shown, no animation playing, linked
 * to nothing. */
void func_ov007_020c10ec(Ov007OamNode *n) {
    int i;
    n->y = 0;
    n->x = n->y;
    n->visible = 1;
    n->flip = 0;
    n->priority = 0;
    n->mosaic = 0;
    n->affineIndex = -1;
    n->animCount = 0;
    n->animIndex = 0;
    n->mode = 0;
    n->rev = 0;
    n->paused = 0;
    n->frame = 0;
    n->tick = 0;
    n->changed = 0;
    n->prev = 0;
    n->next = n->prev;
    n->head = n->next;
    n->owner = n->head;
    for (i = 0; i < n->animCount; i++) {
        n->anims[i] = 0;
    }
}
