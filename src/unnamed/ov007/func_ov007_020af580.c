#include "Ov007MenuState.h"
#include "Ov007Work.h"

extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* Sends states[1] to state 0xc. */
void func_ov007_020af580(void) {
    WORK->states[1]->requestedState = 0xc;
}
