//cpp
#include "Ov007Work.h"
#include "G3i.h"
#include "Ov007Camera.h"

extern "C" {

typedef int Fix12;

extern void func_ov007_020bff38(Ov007Camera *cam);
extern void func_ov007_020bffb8(char *c);

extern char *data_ov007_0210342c;
extern short data_02082214[];

/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

void func_ov007_020b2160(int mode) {
    int a;

    switch (mode) {
    case 1:
        a = (int)WORK->cameras[1]->fovy >> 4;
        G3i::PerspectiveW_(data_02082214[a * 2], data_02082214[a * 2 + 1],
                           (int)(WORK->cameras[1]->aspect >> 0x14), WORK->cameras[1]->nearZ,
                           WORK->cameras[1]->farZ, WORK->cameras[1]->scaleW, 1,
                           (Matrix4x3 *)WORK->cameras[1]->projMatrix);
        G3i::LookAt_(&WORK->cameras[1]->eye, &WORK->cameras[1]->up, &WORK->cameras[1]->target, true,
                     &WORK->cameras[1]->viewMatrix);
        break;
    case 0:
        a = (int)WORK->cameras[0]->fovy >> 4;
        G3i::PerspectiveW_(data_02082214[a * 2], data_02082214[a * 2 + 1],
                           (int)(WORK->cameras[0]->aspect >> 0x14), WORK->cameras[0]->nearZ,
                           WORK->cameras[0]->farZ, 0x1000, 1, (Matrix4x3 *)0);
        func_ov007_020bff38(WORK->cameras[0]);
        func_ov007_020bffb8((char *)WORK->cameras[0]);
        G3i::LookAt_(&WORK->cameras[0]->eye, &WORK->cameras[0]->up, &WORK->cameras[0]->target, true,
                     &WORK->cameras[0]->viewMatrix);
        break;
    }
}
}
