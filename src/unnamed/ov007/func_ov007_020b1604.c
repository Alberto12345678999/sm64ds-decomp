#include "Ov007MenuState.h"
#include "Ov007Work.h"

extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

extern void func_ov007_020af34c(void);

/* The screen-fade callback func_ov007_020b155c installs. Pending choice 9
 * clears the choice and runs func_ov007_020af34c; choice 8 sends states[0]
 * to state 6, any other states[1] to state 7. */
void func_ov007_020b1604(void) {
    Ov007Work *w = WORK;
    int choice = w->pendingChoice;
    if (choice == 9) {
        w->choiceReady = 0;
        WORK->pendingChoice = 0;
        func_ov007_020af34c();
        return;
    }
    if (choice == 8) {
        w->states[0]->requestedState = 6;
    } else {
        w->states[1]->requestedState = 7;
    }
}
