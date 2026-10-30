#include "Ov007SpriteGroup.h"

/* Resets a sprite item and hides its node. */
void func_ov007_020c4090(Ov007SpriteItem *item) {
    item->half8 = -1;
    item->half6 = 0;
    item->half4 = item->half6;
    item->node->visible = 0;
}
