/* The 0x44-byte OAM sprite node; names as in func_ov007_020c10ec, only the
 * slot this file clears. */
typedef struct Ov007OamNode {
    char pad_00[8];
    int visible; /* 0x08: func_ov007_020c0b78 draws the node only when set */
} Ov007OamNode;

/* The 0xc-byte record func_ov007_020c40d4 builds; node and margin as in
 * func_ov007_020c3f00. The three halfwords have no reader found. */
typedef struct Ov007SpriteItem {
    Ov007OamNode *node;   /* 0x00 */
    short word4;          /* 0x04: 0 on reset */
    short word6;          /* 0x06: 0 on reset */
    short word8;          /* 0x08: -1 on reset */
    unsigned char margin; /* 0x0a */
} Ov007SpriteItem;

/* Resets a sprite item and hides its node. c keeps the callers' char *
 * spelling; `item` is the typed view. */
void func_ov007_020c4090(char *c) {
    Ov007SpriteItem *item = (Ov007SpriteItem *)c;
    item->word8 = -1;
    item->word6 = 0;
    item->word4 = item->word6;
    item->node->visible = 0;
}
