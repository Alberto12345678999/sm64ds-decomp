#include "Ov007MenuState.h"
#include "Ov007Work.h"
#include "Ov007Item.h"

/* func_ov007_020b4c04's 0x1c-byte item view; names as in unit020b413c. */
typedef struct Ov007ItemView {
    Ov007Item *item; /* 0x00 */
} Ov007ItemView;

extern void func_ov007_020c1d8c(int i);
extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

void func_ov007_020b63e4(char **view);

/* Chooses the item `view` shows (unit020b413c calls it on a tap): items 10
 * and 11 also send item view 9's item to state 2, item 9 sends item view
 * 11's. The item itself goes to state 2 and its id becomes chosenItemId.
 * view keeps the char ** spelling of its declarations; `v` is the typed
 * view. */
void func_ov007_020b63e4(char **view) {
    Ov007ItemView *v = (Ov007ItemView *)view;
    int id = v->item->id;
    if (id == 10 || id == 11) {
        WORK->itemViews[9]->item->state->requestedState = 2;
    } else if (id == 9) {
        WORK->itemViews[11]->item->state->requestedState = 2;
    }
    func_ov007_020c1d8c(0);
    v->item->state->requestedState = 2;
    WORK->chosenItemId = v->item->id;
}
