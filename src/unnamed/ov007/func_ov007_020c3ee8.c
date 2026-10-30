#include "Ov007SpriteGroup.h"

extern void func_ov007_020c0af4(Ov007OamList *list, Ov007OamNode *node);

/* Appends the group's root node (and so every item under it) to OAM node
 * list `list`. */
void func_ov007_020c3ee8(Ov007SpriteGroup *grp, Ov007OamList *list) {
    func_ov007_020c0af4(list, grp->root);
}
