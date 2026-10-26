#include "Ov007MenuState.h"
#include "Ov007Work.h"

extern void func_ov007_020b7d94(void *self);
extern void *data_ov007_0210342c;
extern int data_ov007_02103428;

/* The 0x2c-byte record func_ov007_020aea6c allocates; names as in
 * func_ov007_020b5bf0, only the slot this file touches. */
typedef struct Ov007Item {
    char pad_00[4];
    Ov007MenuState *state; /* 0x04: func_ov007_020c9388 */
} Ov007Item;

/* One of the manager's itemViews (func_ov007_020b4c04); only its item. */
typedef struct Ov007ItemView {
    Ov007Item *item; /* 0x00 */
} Ov007ItemView;

/* Requests state 3 on item views 0x16 and 0x17 (the manager's +0x16c and
 * +0x170), then hands `self` (9 or 0xc at the callers) to
 * func_ov007_020b7d94. */
void func_ov007_020b43dc(void *self) {
    Ov007Work *obj = (Ov007Work *)data_ov007_0210342c;
    data_ov007_02103428 = 1;
    Ov007ItemView *chain1 = obj->itemViews[0x16];
    Ov007Item *inner1 = chain1->item;
    Ov007MenuState *elem1 = inner1->state;
    elem1->requestedState = 3;
    Ov007Work *obj2 = (Ov007Work *)data_ov007_0210342c;
    Ov007ItemView *chain2 = obj2->itemViews[0x17];
    Ov007Item *inner2 = chain2->item;
    Ov007MenuState *elem2 = inner2->state;
    elem2->requestedState = 3;
    func_ov007_020b7d94(self);
}
