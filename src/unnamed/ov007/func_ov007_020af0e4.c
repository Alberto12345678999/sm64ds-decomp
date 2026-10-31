#include "Ov007MenuState.h"
#include "Ov007Work.h"

/* Returns the picker scene's states[0] (unit020b8f50). */
extern Ov007MenuState *func_ov007_020b8f8c(void);
extern void func_ov007_020c1d78(int i);

/* Sends the picker's states[0] to state 5, and states[2] too unless
 * states[0] came from state 1. */
void func_ov007_020af0e4(void) {
    Ov007MenuState *picker = func_ov007_020b8f8c();
    picker->requestedState = 5;
    if (WORK->states[0]->previousState != 1)
        WORK->states[2]->requestedState = 5;
    func_ov007_020c1d78(0);
}
