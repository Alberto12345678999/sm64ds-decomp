#include "Ov007Item.h"

extern void func_ov007_020c937c(void *state);
extern int func_ov007_020c3d1c(void *);

/* Frees an item: its menu state, then the record. The int return is the
 * free hook's tail call. */
int func_ov007_020aea4c(Ov007Item *item) {
    func_ov007_020c937c(item->state);
    return func_ov007_020c3d1c(item);
}
