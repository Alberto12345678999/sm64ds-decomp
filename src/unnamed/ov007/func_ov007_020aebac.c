#include "types.h"
#include "Ov007Work.h"
#include "Ov007Settings.h"

extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* 1 when no save file is in use and the status word is still 0. */
int func_ov007_020aebac(void) {
    Ov007BootArgs *args = WORK->settings->bootArgs;
    u8 *used = args->fileUsed;
    if (used[0] == 0 && used[1] == 0 && used[2] == 0 && args->status == 0)
        return 1;
    return 0;
}
