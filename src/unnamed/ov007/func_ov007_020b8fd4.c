#include "types.h"
#include "Ov007MenuState.h"
#include "Ov007Sprite.h"
extern int _ZN4cstd3divEii(int, int);
extern void func_ov007_020c4388(char *r0, int r1);
extern void func_ov007_020c421c(char *r4);
extern char *data_ov007_02104b9c;
extern char *data_ov007_02104ba0;
extern char *data_ov007_0210342c;

/* The 0xd0-byte touch picker func_ov007_020c690c builds; names as in
 * func_ov007_020b91b4, only the slots this file reads. */
typedef struct Ov007Picker {
    char pad_00[8];
    int groupCount; /* 0x08: committed strokes */
    char pad_0c[8];
    int totalPoints; /* 0x14: points over the stroke and every group */
} Ov007Picker;

/* data_ov007_02104ba0: the 0x4c record func_ov007_020b9880 allocates; names
 * as in func_ov007_020b91b4 and func_ov007_020ba368, only the slots this
 * file reads. */
typedef struct Ov007PickerScene {
    Ov007Picker *picker; /* 0x00: func_ov007_020c690c */
    char pad_04[0x1c];
    int introVariant; /* 0x20: func_ov007_020ba368's intro shape; 0 slides along x, 3 along y */
    char pad_24[0xc];
    int awaitingTap; /* 0x30: func_ov007_020ba05c clears it on the next fresh press */
} Ov007PickerScene;

/* data_ov007_02104b9c: the 0x14 record of the scene's sprites
 * (func_ov007_020b9880); names as in func_ov007_020b91b4. */
typedef struct Ov007PickerSprites {
    /* 0x00, medium confidence: Q12; sprites[1] slides in below while it is
     * <= 0x1000 (func_ov007_020ba368 eases it up) */
    s32 slideProgress;
    Ov007Sprite *sprites[4]; /* 0x04: func_ov007_020c44e4 */
} Ov007PickerSprites;

/* The 0x2c-byte record func_ov007_020aea6c allocates; names as in
 * func_ov007_020b46b0 and func_ov007_020b5f64, only the slots read here. */
typedef struct Ov007Item {
    u16 id; /* 0x00 */
    char pad_02[2];
    Ov007MenuState *state; /* 0x04: func_ov007_020c9388(1) */
    s32 posX;              /* 0x08: Q12 */
    s32 posY;              /* 0x0c */
} Ov007Item;

/* The 0x1c record func_ov007_020b4c04 returns (names as in that file). */
typedef struct Ov007ItemView {
    Ov007Item *item;     /* 0x00 */
    Ov007Sprite *sprite; /* 0x04 */
} Ov007ItemView;

/* data_ov007_0210342c: the overlay's manager; names as in
 * func_ov007_020b9880, only the slots this file reads. */
typedef struct Ov007Work {
    char pad_00[0x30];
    void *cameras[2]; /* 0x30: func_ov007_020c023c */
    char pad_38[0xdc];
    Ov007ItemView *itemViews[0x18]; /* 0x114: func_ov007_020b693c, one per func_ov007_020b4c04 */
} Ov007Work;

/* The externs keep the tree's char * spelling (the declaration-agreement
 * gate); the typed views are reached through cast macros. */
#define WORK ((Ov007Work *)data_ov007_0210342c)
#define SCENE ((Ov007PickerScene *)data_ov007_02104ba0)
#define SPRITES ((Ov007PickerSprites *)data_ov007_02104b9c)

void func_ov007_020b8fd4(int param) {
    int v;
    int mode;
    int d;
    Ov007Sprite *b;
    int other;
    int scale;
    Ov007Sprite *p_c;
    Ov007Sprite *p_10;
    Ov007ItemView *p5;
    int f8;
    Ov007Picker *inner;
    Ov007Item *node;
    Ov007MenuState *ps;
    int flag;
    int f14;
    int sh;
    v = SPRITES->slideProgress;
    if (v <= 0x1000) {
        SPRITES->sprites[1]->screenX = 0x80000;
        b = SPRITES->sprites[1];
        b->screenY = 0x60000;
        mode = SCENE->introVariant;
        switch (mode) {
        case 0:
            b = SPRITES->sprites[1];
            b->screenX += (0x1000 - v) << 8;
            break;
        case 3:
            d = 0x1000 - v;
            b = SPRITES->sprites[1];
            b->screenY += (-d) << 8;
            break;
        }
        func_ov007_020c4388((char *)SPRITES->sprites[1], (int)WORK->cameras[1]);
    }
    func_ov007_020c421c((char *)SPRITES->sprites[0]);
    func_ov007_020c421c((char *)SPRITES->sprites[1]);

    {
        Ov007PickerScene *c;
        Ov007Work *g;
        f8 = (int)data_ov007_02104b9c;
        c = *((Ov007PickerScene *volatile *)&data_ov007_02104ba0);
        g = *((Ov007Work *volatile *)&data_ov007_0210342c);
        flag = c->awaitingTap;
        p5 = g->itemViews[5];
        inner = c->picker;
        node = p5->item;
        ps = node->state;
        p_c = ((Ov007PickerSprites *)f8)->sprites[2];
        p_10 = ((Ov007PickerSprites *)f8)->sprites[3];
        f8 = inner->groupCount;
        sh = ps->currentState;
        f14 = inner->totalPoints;
        if (flag) {
            f8 = 0;
            f14 = f8;
        }
    }

    if (sh == 1) {
        return;
    }
    scale = _ZN4cstd3divEii(f14 << 12, 500);
    other = _ZN4cstd3divEii(f8 << 12, 200);
    if (scale <= other) {
        scale = other;
    }
    p_c->screenX = p5->item->posX + (((int)(p_c->width * scale)) / 2);
    p_c->screenY = p5->item->posY;
    p_c->scaleX = 0x1000 - scale;
    p_10->screenX = p5->item->posX;
    p_10->screenY = p5->item->posY;
    func_ov007_020c4388((char *)p_c, param);
    func_ov007_020c4388((char *)p_10, param);
    func_ov007_020c421c((char *)p_c);
    func_ov007_020c421c((char *)p_10);
}
