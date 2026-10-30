#include "Ov007MenuState.h"
#include "Ov007Work.h"

extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

extern void func_ov007_020b0244(void);

/* On the first tick of states[1]'s state: func_ov007_020b0244, then
 * states[2] to state 8. func_ov007_020b01a4 is the same with state 9. */
void func_ov007_020b01f4(void) {
    if (WORK->states[1]->stateTicks != 0)
        return;
    func_ov007_020b0244();
    WORK->states[2]->requestedState = 8;
}
