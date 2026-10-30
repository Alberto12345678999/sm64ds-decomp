#include "Ov007MenuState.h"
#include "Ov007Work.h"

extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* A screen-fade callback (func_ov007_020af4dc, func_ov007_020aef84): queues
 * background mode 1 and sends states[0] to state 0. */
void func_ov007_020b0520(void) {
    WORK->pendingBgMode = 1;
    WORK->states[0]->requestedState = 0;
}
