#include "Ov007MenuState.h"
#include "Ov007Work.h"
#include "Ov007Item.h"
extern void func_ov007_020b1390(int x);
extern char* func_ov007_020b2cdc(void);
extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

void func_ov007_020b1224(void)
{
    Ov007Work *w = WORK;
    if (w->itemViews[8]->item->state->currentState != 0)
        return;
    switch (w->chosenItemId) {
    case 9: case 10: case 11: func_ov007_020b1390(0); break;
    case 12: case 13: func_ov007_020b1390(1); break;
    case 8: func_ov007_020b1390(3); break;
    }
    {
        int val = WORK->chosenItemId;
        if (val == -1) return;
        /* func_ov007_020b2cdc returns the menu cursor's state
         * (func_ov007_020b2e64's Ov007Cursor::state) */
        if ((unsigned int)(val - 0xa) <= 1) {
            Ov007MenuState *p = (Ov007MenuState *)func_ov007_020b2cdc();
            p->requestedState = 9;
        } else {
            Ov007MenuState *p = (Ov007MenuState *)func_ov007_020b2cdc();
            p->requestedState = (short)val;
        }
    }
}
