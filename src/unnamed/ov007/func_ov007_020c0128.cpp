//cpp
#include "types.h"
#include "cstd.h"
#include "Ov007Camera.h"
extern "C" void Matrix4x3_LoadIdentity(void *m);
extern "C" void func_02052ec8(void *p);

/* Resets a camera: eye at z 1.0 looking at the origin, y up, a 30-degree
 * fovy, 4:3 aspect, near 1.0 and far 400.0, the whole 256x192 screen as the
 * viewport and identity view and projection matrices. The four slots
 * Ov007Camera leaves unnamed are written raw, on the char * `c`. */
extern "C" void func_ov007_020c0128(char *c)
{
    Ov007Camera *cam = (Ov007Camera *)c;
    cam->eye.y = 0;
    cam->eye.x = cam->eye.y;
    cam->eye.z = 0x1000;
    cam->target.z = 0;
    cam->target.y = cam->target.z;
    cam->target.x = cam->target.y;
    cam->distance = 0;
    *(unsigned short *)(c + 0x34) = 0;
    cam->azimuth = *(unsigned short *)(c + 0x34);
    cam->elevation = cam->azimuth;
    cam->up.z = 0;
    cam->up.x = cam->up.z;
    cam->up.y = 0x1000;
    cam->nearZ = 0x1000;
    cam->farZ = 0x190000;
    cam->fovy = (short)cstd::div(0x1e0000, 0x168);
    long long l = cstd::ldiv(0x4000, 0x3000);
    cam->aspect = l;
    cam->viewportMinX = 0;
    cam->viewportMaxX = 0xff;
    cam->viewportMinY = 0;
    cam->viewportMaxY = 0xbf;
    *(int *)(c + 0xcc) = 0x1000;
    *(int *)(c + 0xd0) = 0xc00;
    Matrix4x3_LoadIdentity(&cam->viewMatrix);
    func_02052ec8(cam->projMatrix);
    cam->scaleW = 0x1000;
    *(int *)(c + 0) = 0;
    cam->tweening = 0;
}
