#include "Ov007MenuState.h"

extern int func_ov007_020b58e4(void* t);
extern void func_ov007_020ae834(void* t);
extern int func_ov007_020b5068(void* t);
extern void func_ov007_020b50e8(void* t);
extern void func_ov007_020b5bf0(void* t);

/* The 10-byte layout row func_ov007_020aea6c's item points at; names as in
 * func_ov007_020b5bf0, only the slot this file reads. */
typedef struct Ov007ItemLayout {
    u16 kind; /* 0x0: func_ov007_020b5bf0 switches on it */
} Ov007ItemLayout;

/* The 0x2c-byte record func_ov007_020aea6c allocates; names as in
 * func_ov007_020b5bf0 and func_ov007_020beeb0, only the slots this file
 * reads. */
typedef struct Ov007Item {
    char pad_00[4];
    Ov007MenuState *state; /* 0x04: func_ov007_020c9388; ticked by func_ov007_020ae834 */
    char pad_08[0x18];
    s32 ready;               /* 0x20: func_ov007_020ae834 sets it once the state settles */
    Ov007ItemLayout *layout; /* 0x24 */
} Ov007Item;

/* One of the manager's itemViews (func_ov007_020b4c04); only its item. */
typedef struct Ov007ItemView {
    Ov007Item *item; /* 0x00 */
} Ov007ItemView;

/* Runs one item view's frame unless its layout kind is 0xa or its state
 * work is 0xff: requests func_ov007_020b58e4's state, ticks the item, runs
 * the state-0 or state-2 handler, then func_ov007_020b5bf0 once the item is
 * ready. */
void func_ov007_020b44ec(void* self) {
    Ov007Item* o = ((Ov007ItemView*)self)->item;
    Ov007ItemLayout* p24 = o->layout;
    if (p24->kind == 0xa) return;
    Ov007MenuState *menu = o->state;
    if (menu->stateWork == 0xff)
        return;
    short r = (short)func_ov007_020b58e4(self);
    menu = o->state;
    menu->requestedState = r;
    func_ov007_020ae834(o);
    menu = o->state;
    switch (menu->currentState) {
    case 0:
        func_ov007_020b5068(self);
        break;
    case 2:
        func_ov007_020b50e8(self);
        break;
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        break;
    }
    if (o->ready == 0) return;
    func_ov007_020b5bf0(self);
}
