//cpp
#include "Ov007MenuState.h"

extern "C" {
extern void func_ov007_020b46b0(void* elem, void* tp);
extern void func_ov007_020b7a78(void);
extern void func_ov007_020c92d0(int o);
extern void func_ov007_020c934c(int o, int v);
extern void func_ov007_020b066c(void);
extern void func_ov007_020af0e4(void);
extern void func_ov007_020af1f4(void);
extern void func_ov007_020aef84(void);
extern void func_ov007_020af434(void);
extern void func_ov007_020b0340(void);
extern void func_ov007_020c2090(int c);
extern void func_ov007_020b0548(void);
extern void func_ov007_020b0358(void);
extern void func_ov007_020aefb4(void);
extern void func_ov007_020af12c(void);
extern void func_ov007_020aef78(void);
extern void func_ov007_020af390(void);
extern void func_ov007_020b0324(void);
extern void func_ov007_020b44ec(int a);
extern void func_ov007_020add3c(int c);
extern void func_ov007_020ad660(int a);
extern char *data_ov007_0210342c;

/* data_ov007_0210342c: the overlay's manager; names as in
 * func_ov007_020b1cf0, func_ov007_020b131c (#4237) and #4241's Ov007Work,
 * only the slots this file touches. The records stay void *: this file
 * only hands them on. */
struct Ov007Work {
    char pad_00[4];
    Ov007MenuState *states[3]; /* 0x04: func_ov007_020c9388; [1] is the main one */
    char pad_10[0x40];
    void *touch; /* 0x50: Ov007Touch, func_ov007_020c2068 */
    void *pad;   /* 0x54: Ov007Pad, func_ov007_020c2304 */
    char pad_58[0x4c];
    void *itemNodes[9];   /* 0xa4: func_ov007_020b6d40, one per func_ov007_020ade58 */
    void *layerSlots[8];  /* 0xc8: func_ov007_020b6d40, one per func_ov007_020adc08 */
    char pad_e8[0x2c];
    void *itemViews[0x18]; /* 0x114: func_ov007_020b693c, one per func_ov007_020b4c04 */
    char pad_174[0xc];
    /* 0x180: the id of the item chosen this frame, -1 = none: reset here
     * every frame, set by func_ov007_020b63e4 (a tapped item) and
     * func_ov007_020b3c54, dispatched on by func_ov007_020b1224 */
    int chosenItemId;
};

typedef char Ov007Work_chosenItemId_must_be_0x180[(int)&((Ov007Work *)0)->chosenItemId == 0x180 ? 1 : -1];

#pragma opt_strength_reduction off
void func_ov007_020aed98(void)
{
    Ov007Work *g = (Ov007Work *)data_ov007_0210342c;
    Ov007MenuState *r6 = g->states[0];
    Ov007MenuState *r5 = g->states[1];
    int i;

    for (i = 0; i < 0x18; i++) {
        Ov007Work *gg = (Ov007Work *)data_ov007_0210342c;
        func_ov007_020b46b0(gg->itemViews[i], gg->touch);
    }

    func_ov007_020b7a78();
    func_ov007_020c92d0((int)r6);

    if (r6->stateTicks == 0) {
        func_ov007_020c934c((int)r5, 0);
        switch (r6->currentState) {
        case 0: func_ov007_020b066c(); break;
        case 2: func_ov007_020af0e4(); break;
        case 3: func_ov007_020af1f4(); break;
        case 4: func_ov007_020aef84(); break;
        case 5: func_ov007_020af434(); break;
        case 6: func_ov007_020b0340(); break;
        }
    }

    func_ov007_020c92d0((int)r5);

    if (r6->stateTicks == 0 || r5->stateTicks == 0) {
        Ov007Work *gg = (Ov007Work *)data_ov007_0210342c;
        func_ov007_020c2090((int)gg->pad);
    }

    switch (r6->currentState) {
    case 0: func_ov007_020b0548(); break;
    case 1: func_ov007_020b0358(); break;
    case 2: func_ov007_020aefb4(); break;
    case 3: func_ov007_020af12c(); break;
    case 4: func_ov007_020aef78(); break;
    case 5: func_ov007_020af390(); break;
    case 6: func_ov007_020b0324(); break;
    }

    {
        Ov007Work *gg = (Ov007Work *)data_ov007_0210342c;
        func_ov007_020c92d0((int)gg->states[2]);
    }

    {
        Ov007Work *gg = (Ov007Work *)data_ov007_0210342c;
        gg->chosenItemId = -1;
    }
    for (i = 0; i < 0x18; i++) {
        Ov007Work *gg = (Ov007Work *)data_ov007_0210342c;
        func_ov007_020b44ec((int)gg->itemViews[i]);
    }
    for (i = 0; i < 9; i++) {
        Ov007Work *gg = (Ov007Work *)data_ov007_0210342c;
        func_ov007_020add3c((int)gg->itemNodes[i]);
    }
    for (i = 0; i < 8; i++) {
        Ov007Work *gg = (Ov007Work *)data_ov007_0210342c;
        func_ov007_020ad660((int)gg->layerSlots[i]);
    }
}
}
