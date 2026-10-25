#ifndef OV007_WORK_H
#define OV007_WORK_H

#include "types.h"

/* Reconstructed names and layout, not an original class identity.
 *
 * ov007's work block: func_ov007_020b68e8 allocates it,
 * func_ov007_020c3df4(data_ov007_02102dc4, 0x188), and stores it in
 * data_ov007_0210342c; func_ov007_020b65e0 frees it with func_ov007_020c3d1c.
 * Each field below was named by the files that use it; where they agreed on
 * a name but not a type, the typed pointer is the one kept. Words no file
 * names stay padding. */
typedef struct Ov007Work {
    u8 pad_000[4];
    /* func_ov007_020c9388; func_ov007_020b65e0 frees them with func_ov007_020c937c */
    struct Ov007MenuState *states[3]; /* 0x004 */
    /* the choice func_ov007_020aec94 was last given; func_ov007_020b0834
     * replays it once the state-9 window closes */
    int pendingChoice; /* 0x010 */
    u8 pad_014[4];
    /* func_ov007_020b6eb4 starts a display capture (func_ov007_020bd4e8
     * writes DISPCAPCNT) while it is set, and clears it */
    int pendingCapture; /* 0x018 */
    /* func_ov007_020b6eb4 hands it to func_ov007_020bd648 and clears it */
    int pendingBgMode; /* 0x01c */
    /* func_ov007_020b1718 runs mode 1 after a stylus tap, mode 0 after a button */
    int transitionMode; /* 0x020 */
    /* medium confidence: the preset func_ov007_020b1fa4 last applied */
    int cameraPreset; /* 0x024 */
    /* the 0x3c-byte record func_ov007_020b6a84 allocates */
    struct Ov007Settings *settings; /* 0x028 */
    u8 pad_02c[4];
    /* both built by func_ov007_020c023c; [1] is the one func_ov007_020b2160
     * loads into the projection */
    struct Ov007Camera *cameras[2]; /* 0x030 */
    /* func_ov007_020c241c(0/1); func_ov007_020c232c writes them to
     * LIGHT_VECTOR / LIGHT_COLOR */
    struct Ov007Light *lights[2]; /* 0x038 */
    /* func_ov007_020bce70 requests palette n on it and blends over its stateTicks */
    struct Ov007MenuState *paletteState; /* 0x040 */
    /* three words func_ov007_020b65e0 releases with func_ov007_020c9460 */
    u8 pad_044[0xc];
    /* func_ov007_020c2068's 0x44-byte touch-panel record, updated by
     * func_ov007_020c1db0 */
    struct Ov007Touch *touch; /* 0x050 */
    struct Ov007Pad *pad;     /* 0x054 */
    /* medium confidence: the tapped slot and its target, -1 = none;
     * func_ov007_020af84c indexes data_ov007_020ccc20[selectedSlot][targetSlot] */
    int selectedSlot; /* 0x058 */
    int targetSlot;   /* 0x05c */
    u8 pad_060[4];
    /* bound as tweens[i]->out (func_ov007_020b6a84) */
    int tweenOut[2];              /* 0x064 */
    struct Ov007Tween *tweens[2]; /* 0x06c: func_ov007_020c908c */
    struct Ov007Display *display; /* 0x074: func_ov007_020b7594's record */
    /* func_ov007_020b697c builds them from the BMD textures */
    void *textures[11]; /* 0x078 */
    /* func_ov007_020b6d40, one per func_ov007_020ade58 */
    struct Ov007ItemNode *itemNodes[9]; /* 0x0a4 */
    /* func_ov007_020b6d40 stores func_ov007_020adc08(i, ...) for i = 0..7 */
    struct Ov007LayerSlot *layerSlots[8]; /* 0x0c8 */
    u8 pad_0e8[4];
    /* 0 or 1: which of figure / altFigure is shown (func_ov007_020be850
     * returns altFigure when it is 1); func_ov007_020b066c copies it from +0xf0 */
    int figureIndex; /* 0x0ec */
    u8 pad_0f0[4];
    struct Ov007Model *model; /* 0x0f4: func_ov007_020b2998 stores func_ov007_020b2bd4's */
    /* Q12; func_ov007_020b2370 scales the model from 1/16 (0) up to 1 (0x1000) */
    int modelGrowth; /* 0x0f8 */
    u8 pad_0fc[4];
    struct Ov007Figure *figure;    /* 0x100: func_ov007_020beaa0 */
    struct Ov007Figure *altFigure; /* 0x104 */
    /* the three full-screen quads func_ov007_020b2998 builds: [0] a
     * corner-colour fill, [1] textured, [2] plain white */
    struct Ov007Sprite *screenSprites[3]; /* 0x108 */
    /* func_ov007_020b693c, one per func_ov007_020b4c04 */
    struct Ov007ItemView *itemViews[0x18]; /* 0x114 */
    /* medium confidence: func_ov007_020b42d8 builds them; func_ov007_020b413c
     * draws a number with them */
    struct Ov007Sprite *numberSprites[3]; /* 0x174 */
    /* the id of the item chosen this frame, -1 = none */
    int chosenItemId; /* 0x180 */
    u8 pad_184[4];    /* func_ov007_020b68e8 clears this word after allocating */
} Ov007Work;

typedef char Ov007Work_size_must_be_0x188[sizeof(Ov007Work) == 0x188 ? 1 : -1];

#endif
