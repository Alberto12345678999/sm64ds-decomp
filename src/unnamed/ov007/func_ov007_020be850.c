#include "types.h"
#include "Ov007MenuState.h"
#include "Ov007Work.h"
extern char* data_ov007_0210342c;

/* func_ov007_020c9110's animation player; names as in func_ov007_020bc02c,
 * only the slots this file reads. */
typedef struct Ov007AnimPlayer {
    char pad_00[0xc];
    s16 anim; /* 0x0c: index into the owner's animation table; -1 none */
    char pad_0e[2];
    u16 frame; /* 0x10: the whole frame func_ov007_020c9110 last reached */
} Ov007AnimPlayer;

/* The model record func_ov007_020bc6d4 allocates; names as in
 * func_ov007_020bc02c, only the slot this file reads. */
typedef struct Ov007Model {
    char pad_00[0x18];
    Ov007AnimPlayer *boneAnim; /* 0x18: func_ov007_020bc894 ticks it */
} Ov007Model;

/* Picks a figure: none while +0xe8 is 0; while the model's bone animation
 * is animation 0, the figure (or, from frame 0x7c on with +0xec set to 1,
 * the second figure); otherwise the figure only in main state 0xb. */
int func_ov007_020be850(void) {
    char* g = data_ov007_0210342c;
    Ov007Work *work = (Ov007Work *)g;
    Ov007AnimPlayer *r2;
    int res = 0;
    if (*(int*)(g + 0xe8) == 0) return res;
    r2 = work->model->boneAnim;
    if (r2->anim == 0) {
        if (r2->frame >= 0x7c) {
            if (*(int *)(g + 0xec) == 1)
                return (int)work->altFigure;
        }
        return (int)work->figure;
    }
    if (work->states[1]->currentState == 0xb)
        res = (int)work->figure;
    return res;
}
