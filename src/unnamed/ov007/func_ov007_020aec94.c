#include "Ov007MenuState.h"
#include "Ov007Work.h"

extern void func_ov007_020bd9e4(int);
extern int *data_ov007_0210342c;

/* The 0x3c-byte record func_ov007_020b6a84 allocates; only the slots this
 * file names. */
typedef struct Ov007Settings {
    char pad_00[0x37];
    /* 0x37 / 0x38: 1 when the owner's dispatcher (func_ov007_020cc600)
     * failed to read the save files (command 0x14) / the minigame data
     * (0x15), as func_ov007_020b066c stores them */
    unsigned char filesFailed;
    unsigned char minigamesFailed;
    /* 0x39: func_ov007_020b7d94's kind, the window menu state 9 opens before
     * the choice goes through (func_ov007_020b0834); 0 = none
     * (func_ov007_020b066c) */
    unsigned char dialogKind;
    char pad_3a[2];
} Ov007Settings;

typedef char Ov007Settings_size_must_be_0x3c[sizeof(Ov007Settings) == 0x3c ? 1 : -1];

/* The extern keeps its int * spelling; the typed view is reached through a
 * cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* Records the menu choice and routes it: choice 9 after either read
 * failure, or 7 after the minigame one, first opens window 1 or 2 through
 * state 9; otherwise choices 3..5 go to state 0xb and the rest to state 6. */
void func_ov007_020aec94(int choice) {
    Ov007Settings *settings = WORK->settings;
    int filesFailed = (settings->filesFailed == 1);
    int minigamesFailed = (settings->minigamesFailed == 1);
    WORK->pendingChoice = choice;
    func_ov007_020bd9e4(0x50);
    if (choice == 9) {
        if (filesFailed != 0 || minigamesFailed != 0) {
            WORK->settings->dialogKind = 1;
            WORK->states[1]->requestedState = 9;
            return;
        }
    }
    if (choice == 7) {
        if (minigamesFailed != 0) {
            WORK->settings->dialogKind = 2;
            WORK->states[1]->requestedState = 9;
            return;
        }
    }
    if ((unsigned int)(choice - 3) <= 2) {
        WORK->states[1]->requestedState = 0xb;
    } else {
        WORK->states[1]->requestedState = 6;
    }
}
