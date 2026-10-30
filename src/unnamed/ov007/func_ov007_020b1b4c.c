#include "Ov007MenuState.h"
#include "Ov007Work.h"

extern int func_ov007_020b1f2c();
extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* Eases modelGrowth over states[1]'s ticks (func_ov007_020b1f2c). */
int func_ov007_020b1b4c(void) {
    Ov007Work *w = WORK;
    return func_ov007_020b1f2c(w->states[1]->stateTicks, &w->modelGrowth);
}
