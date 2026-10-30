#include "Ov007MenuState.h"
#include "Ov007Work.h"

extern void func_ov007_020c1d8c(int i);
extern void func_ov007_020b2764(int n);
extern void RequestScreenFade(int r0, int r1, int r2);
extern void func_ov007_020b16f0(void);
extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* On states[1]'s first tick: sets the screen quads' corner colours to their
 * end values and fades to func_ov007_020b16f0, with fade 1 / 2 when states[0]
 * came from state 6 and 2 / 3 otherwise. */
void func_ov007_020b166c(void) {
    Ov007Work *w = WORK;
    int fromState6 = (w->states[0]->previousState == 6);
    if (w->states[1]->stateTicks != 0)
        return;
    func_ov007_020c1d8c(0);
    func_ov007_020b2764(0x1000);
    if (fromState6)
        RequestScreenFade(1, 2, (int)func_ov007_020b16f0);
    else
        RequestScreenFade(2, 3, (int)func_ov007_020b16f0);
}
