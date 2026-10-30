#include "types.h"
#include "Ov007Work.h"
#include "Ov007Display.h"
extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)
extern u8 data_ov007_020ccbc4[];
extern u8 data_ov007_020ccb7d[];
extern u8 data_ov007_020ccb7c[];

extern int func_ov007_020c3df4(int a, int b);
extern char *func_ov007_020aea6c(int a, void *b, void *c);
extern Ov007OamNode *func_ov007_020c11ac(int n);
extern void func_ov007_020c10b0(Ov007OamNode *parent, Ov007OamNode *child);
extern void func_ov007_020c0af4(Ov007OamList *list, Ov007OamNode *node);
extern void Sprite_SetAnimation(Ov007OamNode *node, int animIndex, int mode, int rev, int frame);

/* The 0x2c-byte record func_ov007_020aea6c allocates; names as in
 * func_ov007_020ae070, only the slot this file reads. */
typedef struct Ov007Item {
    u16 id; /* 0x00: aea6c's first argument */
} Ov007Item;

/* data_ov007_020ccb7c: one 8-byte row per item. data_ov007_020ccb7d is
 * the same table's animCount byte, read by its own symbol. */
typedef struct Ov007NodeSprites {
    u8 bank;      /* 0x00: index into the display's spriteBanks */
    u8 animCount; /* 0x01: the node's animation count (func_ov007_020c11ac) */
    char pad_02[2];
    u8 *animIndices; /* 0x04: per animation, its index in the bank */
} Ov007NodeSprites;

typedef char Ov007NodeSprites_size_must_be_0x8[sizeof(Ov007NodeSprites) == 0x8 ? 1 : -1];

/* The 8-byte record this function returns (names as in
 * func_ov007_020ae558); func_ov007_020b6d40 keeps nine of them in the
 * manager's itemNodes. */
typedef struct Ov007ItemNode {
    Ov007Item *item;    /* 0x00: func_ov007_020aea6c */
    Ov007OamNode *node; /* 0x04: func_ov007_020c11ac */
} Ov007ItemNode;


void *func_ov007_020ade58(int self)
{
    Ov007ItemNode *s = (Ov007ItemNode *)func_ov007_020c3df4(0, 8);
    Ov007Display *r6 = WORK->display;
    Ov007OamNode *r4;
    Ov007SpriteBank **sl;
    int sb;
    int cnt;

    s->item = (Ov007Item *)func_ov007_020aea6c(self, &data_ov007_020ccbc4[self * 0xa], 0);
    r4 = func_ov007_020c11ac(data_ov007_020ccb7d[self * 8]);
    s->node = r4;

    switch (s->item->id) {
    case 0:
        func_ov007_020c10b0(r4, func_ov007_020c11ac(1));
        func_ov007_020c0af4(r6->oamListSub, r4);
        r4->head->x = 0xe8000;
        r4->priority = 1;
        break;
    case 1:
        func_ov007_020c0af4(r6->oamListSub, r4);
        r4->priority = 0;
        break;
    case 2:
        r4->priority = 3;
        break;
    case 3:
    case 4:
    case 5:
        func_ov007_020c0af4(r6->oamListSub, r4);
        r4->priority = 2;
        break;
    case 7:
        func_ov007_020c0af4(r6->oamListMain, r4);
        r4->priority = 1;
        break;
    case 8:
        func_ov007_020c0af4(r6->oamListMain, r4);
        r4->priority = 0;
        break;
    }

    cnt = r4->animCount;
    sl = r6->spriteBanks;
    sb = 0;
    if (cnt > 0) {
        int zero = sb;
        int one = 1;
        do {
            u16 state = s->item->id;
            Ov007NodeSprites *entry = (Ov007NodeSprites *)&data_ov007_020ccb7c[state * 8];
            int r7 = entry->bank;

            if (state == 1 && sb >= 4) {
                r7 = one;
            } else if (state == 0) {
                r4->head->anims[sb] = &sl[r7]->anims[entry->animIndices[sb]];
                Sprite_SetAnimation(r4->head, zero, zero, zero, zero);
            }

            r4->anims[sb] = &sl[r7]->anims[entry->animIndices[sb]];
            sb++;
        } while (sb < r4->animCount);
    }

    Sprite_SetAnimation(s->node, 0, 0, 0, 0);
    return s;
}
