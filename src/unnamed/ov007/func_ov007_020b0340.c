#include "Ov007MenuState.h"
#include "Ov007Work.h"

extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* Clears the pending choice; func_ov007_020aed98 calls it for its case 6. */
void func_ov007_020b0340(void) {
    WORK->pendingChoice = 0;
}
