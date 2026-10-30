#include "types.h"
#include "Ov007Work.h"

/* The 0x3c-byte record func_ov007_020b6a84 allocates; only the slot this
 * file reads. */
typedef struct Ov007Settings {
    /* 0x00: func_ov007_020b7138's second argument; byte 8 is the sound-mode
     * message index func_ov007_020cc168 writes */
    u8 *bootArgs;
} Ov007Settings;

extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

extern void func_ov007_020b7eec(u8 *bootArgs);

/* Steps the sound mode by `step`, wrapping over 0..2, and redraws the
 * header. Ids 1/2/3 are the owner's sound-mode commands: its dispatcher
 * func_ov007_020cc600 maps them to SetSoundMode(2/0/1). */
void func_ov007_020b64a8(int step) {
    int idx = WORK->settings->bootArgs[8] + step;
    if (idx < 0)
        idx = 2;
    else if (idx > 2)
        idx = 0;
    switch (idx) {
    case 0:
        WORK->callback(1);
        break;
    case 1:
        WORK->callback(2);
        break;
    case 2:
        WORK->callback(3);
        break;
    }
    func_ov007_020b7eec(WORK->settings->bootArgs);
}
