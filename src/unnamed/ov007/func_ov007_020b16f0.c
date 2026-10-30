#include "Ov007MenuState.h"
#include "Ov007Work.h"

extern int func_ov007_020c1d78();
extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* The screen-fade callback func_ov007_020b10dc installs: sends states[1] to
 * state 1. */
int func_ov007_020b16f0(void) {
    WORK->states[1]->requestedState = 1;
    return func_ov007_020c1d78(0);
}
