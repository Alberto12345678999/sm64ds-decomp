#include "Ov007Work.h"

extern void func_ov007_020c1d8c(int i);
extern void func_ov007_020b20e8(void);
extern void func_ov007_020b4b5c(void *view, int camera);
extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* Resets the manager's per-visit state, re-aims camera 1
 * (func_ov007_020b20e8) and puts every item view back at its home point
 * under it. */
void func_ov007_020b6544(void)
{
    func_ov007_020c1d8c(0);
    WORK->pendingCapture = 0;
    WORK->pendingBgMode = 1;
    WORK->pendingChoice = 0;
    WORK->choiceReady = 0;
    WORK->frameCount = 0;
    WORK->chosenItemId = -1;
    WORK->cameraPreset = 0;
    WORK->transitionMode = 1;
    func_ov007_020b20e8();
    int i;
    for (i = 0; i < 0x18; i++) {
        func_ov007_020b4b5c(WORK->itemViews[i], (int)WORK->cameras[1]);
    }
}
