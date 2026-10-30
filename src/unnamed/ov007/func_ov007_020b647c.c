#include "Ov007MenuState.h"
#include "Ov007Work.h"

/* func_ov007_020aea6c's 0x2c-byte item; names as in unit020b413c, only the
 * slot this file reads. */
typedef struct Ov007Item {
    char pad_00[4];
    Ov007MenuState *state; /* 0x04 */
} Ov007Item;

/* func_ov007_020b4c04's 0x1c-byte item view; names as in unit020b413c. */
typedef struct Ov007ItemView {
    Ov007Item *item; /* 0x00 */
} Ov007ItemView;

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
