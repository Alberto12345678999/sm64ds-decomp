#include "Ov007MenuState.h"
#include "Ov007Work.h"
#include "Ov007Item.h"

/* func_ov007_020b4c04's 0x1c-byte item view; names as in unit020b413c. */
typedef struct Ov007ItemView {
    Ov007Item *item; /* 0x00 */
} Ov007ItemView;

/* Returns the picker scene's states[0] (unit020b8f50). */
extern int func_ov007_020b8f8c(void);
extern void func_ov007_020c1d78(int i);
extern void func_ov007_020b9640(void);
extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* Steps the picker alongside states[1]: in state 0 it starts the picker
 * (state 1) and leaves once the picker reaches state 2; in state 1 it moves
 * the picker to state 2 and, once the picker reaches state 3, sends item view
 * 3's item to state 2. Then func_ov007_020b9640. */
void func_ov007_020af12c(void) {
    Ov007MenuState *s1 = WORK->states[1];
    int state = s1->currentState;
    int ticks = s1->stateTicks;
    Ov007MenuState *picker;

    switch (state) {
    case 0:
        if (ticks == 0) {
            picker = (Ov007MenuState *)func_ov007_020b8f8c();
            picker->requestedState = 1;
        }
        picker = (Ov007MenuState *)func_ov007_020b8f8c();
        if (picker->currentState == 2)
            WORK->states[1]->requestedState = 1;
        break;
    case 1:
        if (ticks == 0) {
            picker = (Ov007MenuState *)func_ov007_020b8f8c();
            picker->requestedState = 2;
            func_ov007_020c1d78(0);
        }
        picker = (Ov007MenuState *)func_ov007_020b8f8c();
        if (picker->currentState == 3)
            WORK->itemViews[3]->item->state->requestedState = 2;
        break;
    }
    func_ov007_020b9640();
}
