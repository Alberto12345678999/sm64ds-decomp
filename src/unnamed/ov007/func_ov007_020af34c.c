#include "Ov007MenuState.h"
#include "Ov007Work.h"

extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* Queues background mode 6, clears the pending choice and sends states[0]
 * to state 5 and states[2] to state 8. */
void func_ov007_020af34c(void) {
    WORK->pendingBgMode = 6;
    WORK->pendingChoice = 0;
    WORK->states[0]->requestedState = 5;
    WORK->states[2]->requestedState = 8;
}
