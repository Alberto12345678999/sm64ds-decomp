//cpp
#include "types.h"
#include "Ov007Work.h"
#include "G3i.h"
#include "Ov007Camera.h"

extern "C" {

extern char* data_ov007_0210342c;
extern void func_ov007_020c0128(char* c);
extern void func_ov007_020bffb8(char* c);
extern void func_ov007_020c0078(char *c);

/* The extern keeps the tree's char * spelling; the typed view is reached
 * through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* Resets the second camera and frames it: distance 8, fovy 0x4da, scaleW
 * 0x12bb, then orbits the eye and rebuilds its view matrix. */
void func_ov007_020b20e8(void){
    Ov007Camera *cam = WORK->cameras[1];
    func_ov007_020c0128((char *)cam);
    cam->distance = 0x8000;
    cam->fovy = 0x4da;
    cam->scaleW = 0x12bb;
    func_ov007_020bffb8((char *)cam);
    G3i::LookAt_(&cam->eye, &cam->up, &cam->target, true, &cam->viewMatrix);
    func_ov007_020c0078((char *)cam);
}
}
