#include "types.h"

/* The 0x44-byte OAM sprite node func_ov007_020c11ac allocates; names as in
 * func_ov007_020c10ec, only the slots this file touches. */
typedef struct Ov007OamNode {
    s32 x;       /* 0x00: Q12 screen x */
    s32 y;       /* 0x04: Q12 screen y */
    s32 visible; /* 0x08: func_ov007_020c0b78 draws this node and its children only when set */
    char pad_0c[8];
    u8 priority; /* 0x14: OAM priority, used when the caller passes none (> 3) */
} Ov007OamNode;

/* The 0xc-byte record func_ov007_020c40d4 builds around a node; names as
 * in unit020be0dc, only the slots this file touches. */
typedef struct Ov007SpriteItem {
    Ov007OamNode *node; /* 0x00 */
    char pad_04[6];
    u8 margin; /* 0x0a: in pixels */
} Ov007SpriteItem;

/* The 0x18-byte sprite group this function builds and func_ov007_020c3e7c
 * frees: a root node with one child per item. Names as in unit020be0dc;
 * the two words after them have no reader found. */
typedef struct Ov007SpriteGroup {
    int *layout;             /* 0x00: [0] is the item count, [2] each item's animation count */
    Ov007OamNode *root;      /* 0x04: the items' parent (func_ov007_020c10b0) */
    Ov007SpriteItem **items; /* 0x08: layout[0] records */
    Ov007SpriteItem *extra;  /* 0x0c: one more record, also under root */
    int word10;              /* 0x10: -1 on build */
    int word14;              /* 0x14: 0 on build */
} Ov007SpriteGroup;

typedef char
    Ov007SpriteItem_margin_must_be_at_0xa[(int)&((Ov007SpriteItem *)0)->margin == 0xa ? 1 : -1];
typedef char Ov007SpriteGroup_size_must_be_0x18[sizeof(Ov007SpriteGroup) == 0x18 ? 1 : -1];

extern int func_ov007_020c3df4(int a, void *b);
extern void *func_ov007_020c11ac(int n);
extern void *func_ov007_020c40d4(int animCount);
extern void func_ov007_020c10b0(void *a, int b);
extern void func_ov007_020c4090(char *c);

/* Shows the item's node only while it lies within `margin` pixels of the
 * 256x192 screen, and hides it once it leaves. */
void func_ov007_020c3fe4(Ov007SpriteItem *item) {
    s32 y;
    s32 m;
    s32 x;
    s32 inside;
    s32 insideX;
    s32 negM;
    Ov007OamNode *node;
    s32 visible;

    node = item->node;
    m = item->margin;
    x = node->x >> 12;
    inside = 0;
    insideX = 0;
    negM = -m;
    y = node->y >> 12;

    if (negM <= x && x <= m + 255)
        insideX = 1;
    if (insideX && negM <= y && y <= m + 191)
        inside = 1;

    visible = node->visible;
    if ((visible == 0 && inside) || (visible != 0 && !inside))
        node->visible = (visible == 0);
}

/* Builds a sprite group for `layout` (whose count and animation count it
 * reads), an invisible root at priority 4 with an extra record of
 * `extraAnims` animations and one record per item under it. */
void *func_ov007_020c3f00(int *layout, int extraAnims) {
    char *p = (char *)func_ov007_020c3df4(0, (void *)0x18);
    Ov007SpriteGroup *grp = (Ov007SpriteGroup *)p;
    grp->layout = layout;
    grp->root = func_ov007_020c11ac(0);
    grp->root->priority = 4;
    grp->root->visible = 0;
    grp->extra = func_ov007_020c40d4(extraAnims);
    func_ov007_020c10b0(grp->root, (int)grp->extra->node);
    grp->items = (Ov007SpriteItem **)func_ov007_020c3df4(0, (void *)(*layout << 2));
    int i = 0;
    while (i < *layout) {
        grp->items[i] = func_ov007_020c40d4(layout[2]);
        Ov007SpriteItem *item = grp->items[i];
        func_ov007_020c4090((char *)item);
        func_ov007_020c10b0(grp->root, (int)item->node);
        i++;
    }
    grp->word14 = 0;
    grp->word10 = -1;
    return p;
}
