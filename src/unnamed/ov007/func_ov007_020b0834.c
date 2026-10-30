#include "types.h"
#include "Ov007MenuState.h"
#include "Ov007Touch.h"
#include "Ov007Work.h"

/* The 0x3c-byte record func_ov007_020b6a84 allocates; names as in
 * func_ov007_020aec94, only the slots this file touches. */
typedef struct Ov007Settings {
    char pad_00[0x37];
    /* 0x37 / 0x38: 1 when the owner's dispatcher (func_ov007_020cc600)
     * failed to read the save files (command 0x14) / the minigame data
     * (0x15), as func_ov007_020b066c stores them */
    unsigned char filesFailed;
    unsigned char minigamesFailed;
    /* 0x39: func_ov007_020b7d94's kind, the window menu state 9 opens before
     * the choice goes through; 0 = none (func_ov007_020b066c) */
    unsigned char dialogKind;
} Ov007Settings;

/* func_ov007_020adc08's 0xc-byte layer slot; func_ov007_020c0638 rebuilds its layer. */
typedef struct Ov007LayerSlot {
    int state;   /* 0x00: an Ov007MenuState (func_ov007_020c9388) */
    void *layer; /* 0x04 */
} Ov007LayerSlot;

/* The 0x70-byte key record func_ov007_020c2304 allocates; names as in
 * func_ov007_020c20b8. */
typedef struct Ov007Pad {
    u16 keys;     /* 0x00: held this frame */
    u16 prevKeys; /* 0x02: held last frame */
} Ov007Pad;

extern void func_ov007_020c0638(int a, int b, int c, int d);
extern void func_ov007_020b7d94(int kind);
extern void func_ov007_020b2614(int a, int b, int c);
extern void func_ov007_020c1d8c(int i);
extern int func_ov007_020b79c8(void);
extern void func_ov007_020bdeb0(int a);
extern void func_ov007_020b7a44(void);
extern int func_ov007_020b79e4(void);
extern void func_ov007_020aec94(int a);

extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* Main state 9: on its first tick rebuilds layer slot 6's screen, opens the
 * settings' dialog window (func_ov007_020b7d94) and starts
 * func_ov007_020b2614(2, 0, 8). Once func_ov007_020b79c8 reports it, a new
 * key press or a fresh tap answers it: a set filesFailed (only for pending
 * choice 9) / minigamesFailed is replaced with what the owner's commands
 * 0x16 (erase the files not in use) / 0x17 (save the minigame data) return,
 * and func_ov007_020b7a44 runs; once func_ov007_020b79e4 reads 0 it
 * replays the pending choice (func_ov007_020aec94). */
void func_ov007_020b0834(void) {
    if (WORK->states[1]->stateTicks == 0) {
        func_ov007_020c0638((int)WORK->layerSlots[6]->layer, 0, 0, 0);
        func_ov007_020b7d94(WORK->settings->dialogKind);
        func_ov007_020b2614(2, 0, 8);
        func_ov007_020c1d8c(0);
    }

    switch (WORK->states[1]->stateWork) {
    case 0:
        if (func_ov007_020b79c8() == 0)
            return;
        {
            Ov007Pad *pad = WORK->pad;
            if ((pad->keys & ~pad->prevKeys) == 0) {
                Ov007Touch *touch = WORK->touch;
                if (touch->cur.touch == 0)
                    return;
                if (touch->prev.touch != 0)
                    return;
                if (touch->releasedFrames < 1)
                    return;
            }
        }
        {
            Ov007Settings *settings = WORK->settings;
            int filesFailed = (settings->filesFailed == 1);
            int minigamesFailed = (settings->minigamesFailed == 1);
            func_ov007_020bdeb0(0xc);
            if (filesFailed) {
                if (WORK->pendingChoice == 9) {
                    int v = WORK->callback(0x16);
                    WORK->settings->filesFailed = v;
                }
            }
            if (minigamesFailed) {
                int v = WORK->callback(0x17);
                WORK->settings->minigamesFailed = v;
            }
            func_ov007_020b7a44();
            WORK->states[1]->stateWork = 1;
        }
        return;
    case 1:
        if (func_ov007_020b79e4() != 0)
            return;
        func_ov007_020aec94(WORK->pendingChoice);
        return;
    }
}
