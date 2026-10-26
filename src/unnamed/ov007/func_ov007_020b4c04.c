#include "types.h"
#include "Ov007Sprite.h"
#include "Ov007Work.h"

/* The 0x2c-byte record func_ov007_020aea6c allocates; only the fields this
 * file touches are spelled. */
typedef struct Ov007Item {
    u16 id;            /* 0x00: aea6c's first argument (this file's arg0) */
    char pad_02[0x22]; /* 0x02 */
    s16 *layout;       /* 0x24: 10-byte record; ae810 seeds the item position from [1], [2] */
    void *hitBox;      /* 0x28: b46b0 reads the touch rectangle at +4..+0x10 */
} Ov007Item;

/* The 0x1c-byte record this function returns (freed by func_ov007_020b4bd4,
 * stored in the manager's items[] by func_ov007_020b693c). func_ov007_020b5f64
 * slides item from slideFrom to slideTo by slideT. */
typedef struct Ov007ItemView {
    Ov007Item *item;               /* 0x00 */
    Ov007Sprite *sprite;           /* 0x04: func_ov007_020c44e4 */
    char pad_08[4];                /* 0x08: cleared here; no reader found */
    s32 slideT;                    /* 0x0c: slideTween output, 0..0x1000 */
    struct Ov007Tween *slideTween; /* 0x10: func_ov007_020c908c, bound to slideT */
    s16 slideFromX;                /* 0x14 */
    s16 slideFromY;                /* 0x16 */
    s16 slideToX;                  /* 0x18 */
    s16 slideToY;                  /* 0x1a */
} Ov007ItemView;

/* The 0x3c-byte record at the manager's +0x28; only +0x3a is known here. */
typedef struct Ov007Settings {
    char pad_00[0x3a];
    u8 language; /* 0x3a: func_ov007_020b6a84 seeds it from the owner-info language */
} Ov007Settings;

extern void *func_ov007_020c3df4(int a, int b);
extern void *func_ov007_020aea6c(int a, void *b, void *c);
extern void *func_ov007_020c44e4(u8 x);
extern void *func_ov007_020c908c(void *p);

extern s32 data_ov007_020d77d8[];
extern u8 data_ov007_020d76e8[];
extern u8 data_ov007_020d78f8[];
extern u8 data_ov007_020d77e0[];
extern u16 data_ov007_020d76a0[];
extern u16 data_ov007_020d76a1[];
extern u8 data_ov007_020d77e1[];
extern s32 data_ov007_020d7648[];
extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)
extern u16 data_ov007_020d75e8[];
extern u16 data_ov007_020d75f8[];
extern u8 data_ov007_020d76c0[];
extern u8 data_ov007_020d7680[];
extern u16 data_ov007_020d7608[];
extern u16 data_ov007_020d7600[];
extern u8 data_ov007_020d7658[];
extern u8 data_ov007_020d766c[];
extern u16 data_ov007_020d7628[];
extern u16 data_ov007_020d7638[];

void *func_ov007_020b4c04(int arg0)
{
    Ov007ItemView *view;
    Ov007Sprite *sprite;
    s32 r5;
    u8 t;

    view = (Ov007ItemView *)func_ov007_020c3df4(0, 0x1c);
    r5 = *(s32 *)((char *)data_ov007_020d77d8 + arg0 * 0xc);
    view->item = func_ov007_020aea6c(arg0, (char *)data_ov007_020d76e8 + arg0 * 0xa,
                                     (char *)data_ov007_020d78f8 + r5 * 0x14);
    view->sprite = func_ov007_020c44e4(((u8 *)data_ov007_020d77e0)[view->item->id * 0xc]);
    sprite = view->sprite;
    if (arg0 == 0x15) {
        sprite->polygonId = 0x1c;
    } else {
        sprite->polygonId = 0x1b;
    }
    sprite->texRepeat = 3;
    sprite->texFlip = 0;
    sprite->texColor0 = 1;
    sprite->width = (s16)((
        u8 *)data_ov007_020d76a0)[*(s32 *)((char *)data_ov007_020d77d8 + view->item->id * 0xc) * 2];
    sprite->height = (s16)((
        u8 *)data_ov007_020d76a1)[*(s32 *)((char *)data_ov007_020d77d8 + view->item->id * 0xc) * 2];
    sprite->depth = data_ov007_020d7648[((u8 *)data_ov007_020d77e1)[view->item->id * 0xc]];
    *(s32 *)((char *)view + 8) = 0; /* +0x08 has no reader, so it stays unnamed */
    view->slideTween = func_ov007_020c908c(&view->slideT);
    view->slideT = 0;
    view->slideToX = view->item->layout[1];
    view->slideFromX = view->slideToX;
    view->slideToY = view->item->layout[2];
    view->slideFromY = view->slideToY;

    if (arg0 >= 0 && arg0 <= 2) {

        sprite->frames[0] = WORK->textures[6];
        sprite->texS = data_ov007_020d75e8[arg0];
        sprite->texT = data_ov007_020d75f8[arg0];
        if (WORK->settings->language == 5) {
            view->item->hitBox = &data_ov007_020d76c0[(r5 - 1) * 0x14];
            view->item->layout = (s16 *)&data_ov007_020d7680[arg0 * 0xa];
            if (arg0 != 0) {
                sprite->width = 0x48;
            } else {
                sprite->depth += 0xc;
            }
        }
    } else if (arg0 >= 3 && arg0 <= 6) {

        sprite->frames[0] = WORK->textures[1];
        sprite->texS = data_ov007_020d7608[arg0 - 3];
        sprite->texT = data_ov007_020d7600[arg0 - 3];
    } else if (arg0 >= 7 && arg0 <= 0xd) {
        if (arg0 == 7) {
            sprite->frames[0] = WORK->textures[6];
        } else {
            sprite->frames[0] = WORK->textures[8];
        }
        switch (arg0) {
        case 7:
            sprite->texS = 0x60;
            break;
        case 8:
            sprite->texS = 0xc0;
            sprite->texT = 0x20;
            t = WORK->settings->language;
            switch (t) {
            case 3:
                sprite->frames[0] = WORK->textures[7];
                sprite->texS = 0;
                sprite->texT = 0;
                sprite->width = 0x50;
                view->item->hitBox = &data_ov007_020d7658;
                break;
            case 4:
                sprite->frames[0] = WORK->textures[7];
                sprite->texS = 0x50;
                sprite->texT = 0;
                sprite->width = 0x60;
                view->item->hitBox = &data_ov007_020d766c;
                break;
            }
            break;
        case 9:
            break;
        case 10:
            sprite->texS = 0x90;
            sprite->texT = 0x20;
            break;
        case 11:
            sprite->texS = 0x90;
            sprite->texT = 0x30;
            break;
        default:
            sprite->texT = 0x20;
            break;
        }
    } else if (arg0 >= 0xe && arg0 <= 0x15) {

        sprite->frames[0] = WORK->textures[2];
        sprite->texS = data_ov007_020d7628[arg0 - 0xe];
        sprite->texT = data_ov007_020d7638[arg0 - 0xe];
    } else if (arg0 >= 0x16 && arg0 <= 0x17) {

        sprite->frames[0] = WORK->textures[2];
        sprite->texS = (u16)((arg0 - 0x16) * 0x48);
        sprite->texT = 0x80;
    }
    return view;
}
