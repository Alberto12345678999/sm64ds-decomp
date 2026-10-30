#include "Ov007MenuState.h"
#include "Ov007Work.h"

extern int func_ov007_020c1d78();

/* The screen-fade callback func_ov007_020b10dc installs: sends states[1] to
 * state 1. */
int func_ov007_020b16f0(void) {
    WORK->states[1]->requestedState = 1;
    return func_ov007_020c1d78(0);
}
