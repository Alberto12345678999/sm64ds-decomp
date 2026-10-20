#include "types.h"
#include "Ov007MenuState.h"
#pragma opt_strength_reduction off

/* Ov007Sprite: reconstructed name and layout, not a recovered class (no RTTI,
 * no vtable; plain C helpers). The 0x88-byte screen-space textured quad that
 * func_ov007_020c44e4 allocates and initialises and func_ov007_020c44c4 frees.
 * Field roles come from its readers: func_ov007_020c4388 (screen -> world),
 * func_ov007_020c43bc (world size), func_ov007_020c42f8 (transform),
 * func_ov007_020c421c (draw + drop shadow) and func_ov007_020c4684 (quad). */
typedef struct Ov007Sprite {
    s32 drawFlags;   /* 0x00: c4684: 1|2 plain quad, 2 corner colours; c421c: 4 shadow; 8 tilemap */
    s32 screenX;     /* 0x04: c4388 -> func_ov007_020bfe4c centres it on 0x80000 (128 px) */
    s32 screenY;     /* 0x08: c4388 -> func_ov007_020bfe4c centres it on 0x60000 (96 px) */
    u16 width;       /* 0x0c: pixels; c43bc scales it, c4684 uses it as the texel width */
    u16 height;      /* 0x0e */
    s32 depth;       /* 0x10: c4388 view z; c43bc scales width/height by |depth| */
    Vector3 pos;     /* 0x14: c4388 writes the world position, c42f8 translates by it */
    s32 worldWidth;  /* 0x20: c43bc result; c4684 quad width */
    s32 worldHeight; /* 0x24 */
    Vector3 posOffset;   /* 0x28: c42f8 adds it to pos */
    u16 rotX;            /* 0x34: c42f8 rotation angles */
    u16 rotY;            /* 0x36 */
    u16 rotZ;            /* 0x38 */
    char pad_3a[2];      /* 0x3a */
    s32 scaleX;          /* 0x3c: c42f8 MTX_SCALE */
    s32 scaleY;          /* 0x40 */
    u16 color;           /* 0x44: c421c -> c4684 COLOR */
    u16 cornerColors[4]; /* 0x46: c4684 per-vertex COLOR when drawFlags & 2 */
    u8 polygonId;        /* 0x4e: c421c -> c4684 POLYGON_ATTR bits 24-29 */
    char pad_4f;         /* 0x4f */
    s32 alpha;           /* 0x50: Q12; c421c passes (alpha >> 12) & 0xff as POLYGON_ATTR alpha */
    s32 polygonAttr;     /* 0x54: c4684 ORs it into POLYGON_ATTR */
    u16 frameCount;      /* 0x58: c44e4 sizes frames[] by it */
    u16 frame;           /* 0x5a: c4684 draws frames[frame] */
    void **frames;       /* 0x5c: texture records (mgr textures[] entries) */
    u16 repeatU;         /* 0x60: c4684 texture repeat count; 1 means use width */
    u16 repeatV;         /* 0x62: 1 means use height */
    s32 texRepeat;       /* 0x64: func_ov007_020c1448 `repeat` */
    s32 texFlip;         /* 0x68: func_ov007_020c1448 `flip` */
    s32 texColor0;       /* 0x6c: func_ov007_020c1448 `color0` */
    s16 texS;            /* 0x70: c4684 texel origin */
    s16 texT;            /* 0x72 */
    s32 shadowScaleX;    /* 0x74: c421c second, black, offset pass: medium-confidence "shadow" */
    s32 shadowScaleY;    /* 0x78 */
    u8 shadowAlphaDrop;  /* 0x7c: subtracted from the alpha for the shadow pass */
    u8 shadowPolygonId;  /* 0x7d */
    s16 shadowOffset[3]; /* 0x7e: c421c passes it as the shadow pass's vector */
    u16 *tilemap;        /* 0x84: c4684 tile map when drawFlags & 8 */
} Ov007Sprite;

/* Copy of include/Ov007Tween.h's layout and names (this matched file takes no
 * new #include). */
typedef struct Ov007Tween {
    s32 state;
    s32 mode;
    s32 step;
    s16 t;
    s32 *out;
    s32 from;
    s32 to; /* 0x18 */
} Ov007Tween;

/* The 0x1c record func_ov007_020b4c04 returns (names as in that file). */
typedef struct Ov007ItemView {
    struct Ov007Item *item; /* 0x00 */
    Ov007Sprite *sprite;    /* 0x04 */
} Ov007ItemView;

/* data_ov007_0210342c: the overlay's manager. No class or header names it;
 * only the slots this file touches are spelled. */
typedef struct Ov007Work {
    char pad_00[0x30];
    void *cameras[2]; /* 0x30: both built by func_ov007_020c023c; [1] is the
                         * one func_ov007_020b2160 loads into the projection */
    char pad_38[0x40];
    void *textures[11]; /* 0x78: func_ov007_020b697c builds them from the BMD textures */
    char pad_a4[0x70];
    Ov007ItemView *itemViews[0x18]; /* 0x114: func_ov007_020b693c, one per func_ov007_020b4c04 */
} Ov007Work;

/* data_ov007_02104ba0: the 0x4c record this function allocates and
 * func_ov007_020b9770 frees. It owns the touch picker func_ov007_020c690c
 * builds (fields named in func_ov007_020c5a6c). +0x14..+0x3b have no evidenced
 * role yet; their sites below stay raw. */
typedef struct Ov007PickerScene {
    void *picker;              /* 0x00: func_ov007_020c690c; freed by c6684 */
    Ov007MenuState *states[4]; /* 0x04: func_ov007_020c9388; [1] is the main one */
    char pad_14[0x28];
    s32 tweenOut[2];       /* 0x3c: bound as tweens[i]->out */
    Ov007Tween *tweens[2]; /* 0x44: func_ov007_020c908c */
} Ov007PickerScene;

/* data_ov007_02104b9c: the 0x14 record of the scene's sprites (freed by
 * func_ov007_020b9770). +0x00 is not touched here. */
typedef struct Ov007PickerSprites {
    char pad_00[4];
    Ov007Sprite *sprites[4]; /* 0x04: func_ov007_020c44e4 */
} Ov007PickerSprites;
extern void *func_ov007_020c3df4(int a, int b);
extern void *func_ov007_020c690c(int a0, int a1, int a2, int a3, void *a4, void *a5);
extern void *func_ov007_020c9388(int a);
extern void *func_ov007_020c908c(void *r5);
extern void *func_ov007_020c44e4(int a);
extern void func_ov007_020c43bc(void *a, int b);
extern void func_ov007_020c4388(char *r0, int r1);
extern void func_ov007_020bbe60(int idx);

extern char *data_ov007_02104ba0;
extern char *data_ov007_02104b9c;
extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)
#define SCENE ((Ov007PickerScene *)data_ov007_02104ba0)
#define SCENE_SPRITES ((Ov007PickerSprites *)data_ov007_02104b9c)
extern int data_ov007_020d7b60;
extern int data_ov007_020d7b80;

void func_ov007_020b9880(int a0, int a1)
{
    int sp14, sp18, sp10, sp1c;
    int var_sl;
    Ov007Sprite *sprite;
    Ov007Sprite *itemSprite;
    Ov007Sprite *temp_r5;

    if (data_ov007_02104ba0 != 0)
        return;

    data_ov007_02104ba0 = (char *)func_ov007_020c3df4(0, 0x4c);
    data_ov007_02104b9c = (char *)func_ov007_020c3df4(0, 0x14);

    SCENE->picker = func_ov007_020c690c(0xc8, 0x1f4, 0x1f4, (int)WORK->cameras[0],
                                        &data_ov007_020d7b60, &data_ov007_020d7b80);

    SCENE->states[0] = func_ov007_020c9388(0);
    SCENE->states[1] = func_ov007_020c9388(-1);
    SCENE->states[2] = func_ov007_020c9388(0);
    SCENE->states[3] = func_ov007_020c9388(0);

    *(int *)(data_ov007_02104ba0 + 0x1c) = 0;
    *(int *)(data_ov007_02104ba0 + 0x20) = 0;
    *(int *)(data_ov007_02104ba0 + 0x28) = 0;
    *(int *)(data_ov007_02104ba0 + 0x24) = 0;
    *(int *)(data_ov007_02104ba0 + 0x2c) = 0;
    *(int *)(data_ov007_02104ba0 + 0x38) = 0;

    SCENE->tweens[0] = func_ov007_020c908c(&SCENE->tweenOut[0]);
    SCENE->tweens[1] = func_ov007_020c908c(&SCENE->tweenOut[1]);

    sp1c = 0;
    sp14 = 0x60000;
    sp18 = 0x100;
    sp10 = 1;

    for (var_sl = 0; var_sl < 2; var_sl++) {
        SCENE_SPRITES->sprites[var_sl] = func_ov007_020c44e4(sp10);
        sprite = SCENE_SPRITES->sprites[var_sl];

        if (var_sl == 0) {
            sprite->frames[0] = WORK->textures[3];
            sprite->depth = 0xfffcdf01;
            sprite->polygonId = 0x18;
        } else {
            sprite->frames[0] = WORK->textures[4];
            sprite->depth = -0x32000;
            sprite->polygonId = 0x17;
        }

        sprite->repeatV = 8;
        sprite->repeatU = sprite->repeatV;
        sprite->screenX = 0x80000;
        sprite->screenY = sp14;
        sprite->width = (s16)sp18;
        sprite->height = (s16)sp18;
        sprite->alpha = sp1c;

        func_ov007_020c43bc(sprite, (int)WORK->cameras[1]);
        func_ov007_020c4388((char *)sprite, (int)WORK->cameras[1]);
    }

    SCENE_SPRITES->sprites[2] = func_ov007_020c44e4(1);
    temp_r5 = SCENE_SPRITES->sprites[2];
    temp_r5->width = 0x48;
    temp_r5->height = 8;
    temp_r5->cornerColors[3] = 0x7f8a;
    temp_r5->cornerColors[0] = temp_r5->cornerColors[3];
    temp_r5->cornerColors[2] = 0x6e02;
    temp_r5->cornerColors[1] = temp_r5->cornerColors[2];
    temp_r5->drawFlags = temp_r5->drawFlags | 2;
    temp_r5->polygonId = 0x19;

    SCENE_SPRITES->sprites[3] = func_ov007_020c44e4(1);
    temp_r5 = SCENE_SPRITES->sprites[3];
    temp_r5->width = 0x48;
    temp_r5->height = 8;
    temp_r5->color = 0x294a;
    temp_r5->alpha = 0x5000;
    temp_r5->drawFlags = temp_r5->drawFlags | 1;
    temp_r5->polygonId = 0x1a;

    itemSprite = WORK->itemViews[5]->sprite;
    SCENE_SPRITES->sprites[2]->depth = itemSprite->depth - 0x10;
    SCENE_SPRITES->sprites[3]->depth = itemSprite->depth - 0xff;

    func_ov007_020c43bc(SCENE_SPRITES->sprites[2], (int)WORK->cameras[1]);
    func_ov007_020c43bc(SCENE_SPRITES->sprites[3], (int)WORK->cameras[1]);

    *(int *)(data_ov007_02104ba0 + 0x34) = 0;
    SCENE->tweens[0]->to = 0x800;
    SCENE->tweenOut[0] = SCENE->tweens[0]->to;

    if (a0 != 0) {
        if (a0 == 1) {
            *(int *)(data_ov007_02104ba0 + 0x30) = 0;
            SCENE->tweenOut[1] = 0;
            SCENE->states[1]->requestedState = 0;
        }
    } else {
        *(int *)(data_ov007_02104ba0 + 0x30) = 1;
        SCENE->tweenOut[1] = 0x1000;
        SCENE->states[1]->requestedState = 2;
    }

    if (a0 != 1)
        return;

    func_ov007_020bbe60(a1);
}
