#include "types.h"
#include "Ov007MenuState.h"

/* The 0x2c-byte record func_ov007_020aea6c allocates; names as in
 * func_ov007_020ae834 and func_ov007_020ae810, only the slots this file
 * touches. */
typedef struct Ov007Item {
    char pad_00[4];
    Ov007MenuState *state; /* 0x04: func_ov007_020c9388(1) */
    int posX;              /* 0x08: Q12 */
    int posY;              /* 0x0c */
    char pad_10[0x10];
    int ready; /* 0x20: set once the state settles, cleared on reset */
} Ov007Item;

/* The 0x40-byte OAM node func_ov007_020c11ac allocates; names as in
 * func_ov007_020c10ec, only the slots this file writes. */
typedef struct Ov007OamNode {
    int x;       /* 0x00: Q12 screen x */
    int y;       /* 0x04: Q12 screen y */
    int visible; /* 0x08 */
} Ov007OamNode;

/* The 8-byte record func_ov007_020ade58 returns: an item and the OAM node
 * drawn for it. */
typedef struct Ov007ItemNode {
    Ov007Item *item;    /* 0x00: func_ov007_020aea6c */
    Ov007OamNode *node; /* 0x04: func_ov007_020c11ac */
} Ov007ItemNode;

extern int func_ov007_020ae558(char *self);
extern void func_ov007_020ae834(char *c);
extern void func_ov007_020ae2d0(char *self);
extern void func_ov007_020ae070(char *self);
extern void func_ov007_020ae454(char *self);

/* Steps one item node a frame: func_ov007_020ae558 picks the item's next
 * state, func_ov007_020ae834 runs it, states 0 and 3 add their effects, and
 * the node follows the item's position and visibility, hidden once it is
 * at or above y = -0x64 (Q12). c keeps the callers' char * spelling; `self`
 * is the typed view. */
void func_ov007_020add3c(char *c) {
    Ov007ItemNode *self = (Ov007ItemNode *)c;
    int r = func_ov007_020ae558(c);
    self->item->state->requestedState = r;
    func_ov007_020ae834((char *)self->item);
    switch (self->item->state->currentState) {
    case 0:
        func_ov007_020ae2d0(c);
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        func_ov007_020ae070(c);
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    }
    func_ov007_020ae454(c);
    self->node->x = self->item->posX;
    self->node->y = self->item->posY;
    self->node->visible = self->item->ready;
    if (self->node->visible != 0) {
        if (self->node->y <= -0x64000)
            self->node->visible = 0;
    }
}
