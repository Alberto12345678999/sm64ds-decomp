#include "Ov007OamNode.h"

/* The 0x2c-byte record func_ov007_020aea6c allocates; names as in
 * func_ov007_020ade58, only the slot this file reads. */
typedef struct Ov007Item {
    unsigned short id; /* 0x00 */
} Ov007Item;

/* The 8-byte record func_ov007_020ade58 builds; the manager keeps nine in
 * its itemNodes. */
typedef struct Ov007ItemNode Ov007ItemNode;
struct Ov007ItemNode {
    Ov007Item *item;    /* 0x00 */
    Ov007OamNode *node; /* 0x04 */
};

extern int func_ov007_020c1180(Ov007OamNode *node);
extern int func_ov007_020aea4c();
extern void func_ov007_020c3d1c(void *p);

/* Frees an item node: for item 0 the child sprite func_ov007_020ade58 gave
 * it, then the item, the sprite node and the record. */
void func_ov007_020ade14(Ov007ItemNode *in) {
    if (in->item->id == 0)
        func_ov007_020c1180(in->node->head);
    func_ov007_020aea4c(in->item);
    func_ov007_020c1180(in->node);
    func_ov007_020c3d1c(in);
}
