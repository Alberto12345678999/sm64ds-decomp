#include "Ov007MenuState.h"
#include "Ov007Work.h"
#include "Ov007Item.h"

extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* Sends item view `index`'s item to `state`, unless `index` is the item `id`
 * itself (unit020b413c passes the tapped item's id). */
void func_ov007_020b647c(int id, int index, short state) {
    if (id == index)
        return;
    WORK->itemViews[index]->item->state->requestedState = state;
}
