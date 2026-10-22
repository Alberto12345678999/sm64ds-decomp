#include "Ov007MenuState.h"
#include "Ov007Tween.h"
extern void func_ov007_020c0638(int a, int b, int c, int d);
extern char* data_ov007_0210342c;

/* The 0x2c-byte record func_ov007_020aea6c allocates; names as in
 * func_ov007_020ae070, only the slot this file touches. */
typedef struct Ov007Item {
    u16 id; /* 0x00: aea6c's first argument */
    char pad_02[2];
    Ov007MenuState *state; /* 0x04: func_ov007_020c9388(1) */
} Ov007Item;

/* The 0x1c record func_ov007_020b4c04 returns; names as in
 * func_ov007_020b9880, only the slot read here. */
typedef struct Ov007ItemView {
    Ov007Item *item; /* 0x00 */
} Ov007ItemView;

/* The 0xc-byte record func_ov007_020adc08 returns; names as there, only the
 * layer read here. */
typedef struct Ov007LayerSlot {
    int state; /* 0x00: an Ov007MenuState (func_ov007_020c9388) */
    int layer; /* 0x04: the Ov007BgLayer func_ov007_020c0638 scrolls */
} Ov007LayerSlot;

/* data_ov007_0210342c: the overlay's manager; names as in
 * func_ov007_020afc44 and func_ov007_020b9880, only the slots this file
 * touches. +0x60 (handed to func_ov007_020b8188) stays raw on G. */
typedef struct Ov007Work {
    char pad_00[0x58];
    /* 0x58/0x5c, medium confidence: the tapped slot and its target
     * (func_ov007_020afc44); -1 = none */
    int selectedSlot;
    int targetSlot;
    char pad_60[4];
    int tweenOut[2];       /* 0x64: bound as tweens[i]->out (func_ov007_020b6a84) */
    Ov007Tween *tweens[2]; /* 0x6c: func_ov007_020c908c */
    char pad_74[0x54];
    /* 0xc8: func_ov007_020b6d40 stores func_ov007_020adc08(i, ...) for
     * i = 0..7 */
    Ov007LayerSlot *layerSlots[8];
    char pad_e8[0x2c];
    Ov007ItemView *itemViews[0x18]; /* 0x114: func_ov007_020b693c, one per func_ov007_020b4c04 */
} Ov007Work;

typedef char Ov007Work_size_must_be_0x174[sizeof(Ov007Work) == 0x174 ? 1 : -1];

/* The extern keeps the tree's char * spelling; the typed view is reached
 * through a cast macro. */
#define G ((char*)data_ov007_0210342c)
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* Resets the slot choice: requests state 5 on slot items 14..16, clears
 * selectedSlot/targetSlot, parks both tweens with their outputs at
 * 0x20000/0x30000, and scrolls layers 6 and 7 back to the origin. */
void func_ov007_020b0244(void)
{
    WORK->itemViews[14]->item->state->requestedState = 5;
    WORK->itemViews[15]->item->state->requestedState = 5;
    WORK->itemViews[16]->item->state->requestedState = 5;
    WORK->targetSlot = -1;
    WORK->selectedSlot = WORK->targetSlot;
    *(int*)(G + 0x60) = 0;
    WORK->tweenOut[0] = 0x20000;
    WORK->tweenOut[1] = 0x30000;
    WORK->tweens[0]->state = 0;
    WORK->tweens[1]->state = 0;
    func_ov007_020c0638(WORK->layerSlots[6]->layer, 0, 0, 0);
    func_ov007_020c0638(WORK->layerSlots[7]->layer, 0, 0, 0);
}
