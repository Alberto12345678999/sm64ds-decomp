//cpp
#include "Ov007MenuState.h"
#include "Ov007Work.h"

extern "C" {
extern void func_ov007_020b283c(void);
extern void func_ov007_020b9770(void);
extern void func_ov007_020bf304(void);
extern void func_ov007_020b6544(void);
extern void func_ov007_020bcba8(int i);
extern void func_ov007_020bca40(int i);
extern void RequestScreenFade(int a, int b, int c);
extern void func_ov007_020bd1c0(int i);
extern void func_ov007_020b131c(void);
extern char *data_ov007_0210342c;
}

/* The 0xa0-byte model record func_ov007_020bc6d4 allocates; names as in
 * func_ov007_020bc47c, only the slot this file writes. */
struct Ov007Model {
    char pad_00[0x94];
    int visible; /* 0x94: func_ov007_020bbff0 renders only while it is nonzero */
};

/* The 0x1c-byte record func_ov007_020beaa0 builds around an Ov007Model;
 * names as in func_ov007_020b0da0. */
struct Ov007Figure {
    char pad_00[4];
    Ov007Model *model; /* 0x04: func_ov007_020bc6d4 */
};

/* func_ov007_020b7138's second argument: dScDSMT_c's byte-packed
 * download-play table (data_0209b340); only the slot this file reads. */
struct Ov007BootArgs {
    int bootFlags; /* 0x00 */
    /* 0x04: dScDSMT_c::InitResources stores 1 here (when data_0209f1e0 is
     * set), CleanupResources 2 */
    int status;
};

/* The 0x3c-byte record func_ov007_020b6a84 allocates; names as in
 * func_ov007_020aec94, only the slots this file touches. */
struct Ov007Settings {
    Ov007BootArgs *bootArgs; /* 0x00 */
    char pad_04[0x33];
    /* 0x37 / 0x38: what the owner's dispatcher (func_ov007_020cc600) returns
     * for command 0x14 (read the three save files) and 0x15 (read the
     * minigame data): 1 when the read failed */
    unsigned char filesFailed;
    unsigned char minigamesFailed;
    /* 0x39: func_ov007_020b7d94's kind, the window menu state 9 opens before
     * the choice goes through (func_ov007_020b0834); cleared here */
    unsigned char dialogKind;
};

typedef char Ov007Model_visible_must_be_at_0x94[(int)&((Ov007Model *)0)->visible == 0x94 ? 1 : -1];

/* The extern keeps the tree's char * spelling; the typed view is reached
 * through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

extern "C" void func_ov007_020b066c(void) {
    switch (WORK->states[0]->previousState) {
    case 6:
        func_ov007_020b283c();
        break;
    case 4:
        func_ov007_020b9770();
        break;
    case 5:
        func_ov007_020bf304();
        WORK->callback(0x11);
        break;
    default:
        WORK->settings->minigamesFailed = WORK->callback(0x15);
        WORK->settings->filesFailed = WORK->callback(0x14);
        WORK->settings->dialogKind = 0;
        break;
    }

    func_ov007_020b6544();
    func_ov007_020bcba8(1);
    func_ov007_020bca40(0);

    {
        Ov007Work *bb = WORK;
        if ((unsigned short)(short)(bb->states[0]->previousState - 4) <= 2) {
            bb->states[1]->requestedState = 5;
        } else {
            switch (bb->settings->bootArgs->status) {
            case 0:
            case 2:
                bb->states[1]->requestedState = 0xb;
                break;
            case 1:
                bb->states[1]->requestedState = 0xa;
                RequestScreenFade(3, 0xa, 0);
                break;
            }
        }
    }

    WORK->states[2]->requestedState = 0;

    WORK->figureIndex = WORK->nextFigureIndex;

    if (WORK->nextFigureIndex == 0)
        WORK->nextFigureIndex = 1;
    else
        WORK->nextFigureIndex = 0;

    func_ov007_020bd1c0(0);

    WORK->model->visible = 0;
    WORK->figure->model->visible = 0;
    WORK->altFigure->model->visible = 0;
    func_ov007_020b131c();
}
