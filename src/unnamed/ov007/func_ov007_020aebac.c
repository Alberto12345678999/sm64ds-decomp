#include "types.h"
#include "Ov007Work.h"

/* func_ov007_020b7138's second argument: dScDSMT_c's byte-packed
 * download-play table (data_0209b340); only the slots this file reads. */
typedef struct Ov007BootArgs {
    int bootFlags; /* 0x00 */
    /* 0x04: dScDSMT_c::InitResources stores 1 here (when data_0209f1e0 is
     * set), CleanupResources 2 */
    int status;
    char pad_08[3];
    /* 0x0b: flags1 bit 0 of the loaded save file */
    u8 fileUsed[3];
} Ov007BootArgs;

/* The 0x3c-byte record func_ov007_020b6a84 allocates; only the slot this
 * file reads. */
typedef struct Ov007Settings {
    Ov007BootArgs *bootArgs; /* 0x00 */
} Ov007Settings;

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
