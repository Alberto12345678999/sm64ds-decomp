#include "types.h"
#include "Ov007MenuState.h"
#include "Ov007Work.h"
#include "Ov007OamNode.h"
extern void Sprite_SetAnimation(Ov007OamNode *node, int animIndex, int mode, int rev, int frame);

/* The 0x2c-byte record func_ov007_020aea6c allocates; names as in
 * func_ov007_020b5bf0, only the slots this file reads. */
typedef struct Ov007Item {
    u16 id; /* 0x00: aea6c's first argument */
    char pad_02[2];
    Ov007MenuState *state; /* 0x04: func_ov007_020c9388(1) */
} Ov007Item;

/* The 8-byte record func_ov007_020ade58 returns (Ov007ItemNode, as in
 * func_ov007_020ae558):
 * an item and the OAM node drawn for it. func_ov007_020add3c passes it
 * here. */
typedef struct Ov007ItemNode {
    Ov007Item *item; /* 0x00: func_ov007_020aea6c */
    Ov007OamNode *node; /* 0x04: func_ov007_020c11ac; Sprite_SetAnimation's target */
} Ov007ItemNode;

typedef char
    Ov007Work_selectedSlot_must_be_at_0x58[(int)&((Ov007Work *)0)->selectedSlot == 0x58 ? 1 : -1];

extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* func_ov007_020add3c calls this while the item is in state 3. On that
 * state's first tick, item 1 sets its node's animation to follow the mode
 * states[2] is in. self keeps the callers' char * spelling; `icon` is the
 * typed view. */
void func_ov007_020ae070(char *self) {
    Ov007ItemNode *icon = (Ov007ItemNode *)self;
    Ov007Item *item = icon->item;
    u16 id = item->id;
    int ticks = item->state->stateTicks;
    Ov007Work *g = WORK;
    short mode = g->states[2]->currentState;

    if (id != 1)
        return;
    if (ticks != 0)
        return;

    switch (mode) {
    case 3:
        Sprite_SetAnimation(icon->node, 0, 0, 0, 0);
        break;
    case 14:
        Sprite_SetAnimation(icon->node, 3, 0, 0, 0);
        break;
    case 4:
        Sprite_SetAnimation(icon->node, 2, 0, 0, 0);
        break;
    case 5:
        Sprite_SetAnimation(icon->node, 1, 0, 0, 0);
        break;
    case 7:
        if (g->transitionMode == 1)
            Sprite_SetAnimation(icon->node, 1, 0, 0, 0);
        else
            Sprite_SetAnimation(icon->node, 2, 0, 0, 0);
        break;
    case 8:
        Sprite_SetAnimation(icon->node, 4, 0, 0, 0);
        break;
    case 9:
        Sprite_SetAnimation(icon->node, 5, 0, 0, 0);
        break;
    case 10:
        Sprite_SetAnimation(icon->node, 6, 0, 0, 0);
        break;
    case 12:
        if (g->selectedSlot == -1)
            Sprite_SetAnimation(icon->node, 7, 0, 0, 0);
        else
            Sprite_SetAnimation(icon->node, 8, 0, 0, 0);
        break;
    case 13:
        Sprite_SetAnimation(icon->node, 9, 0, 0, 0);
        break;
    }
}
