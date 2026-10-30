#include "Ov007SpriteGroup.h"

/* Resets a sprite item and hides its node. */
void func_ov007_020c4090(Ov007SpriteItem *item) {
    item->word8 = -1;
    item->word6 = 0;
    item->word4 = item->word6;
    item->node->visible = 0;
}
