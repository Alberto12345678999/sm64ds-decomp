#include "types.h"

extern short ReadUnalignedShort(unsigned char *p);
extern void func_02007c9c(const Vector3 *v0, const Vector3 *v1, int *outDist,
                          short *outVertAng, short *outHorzAng);
extern void func_02007c14(Vector3 *res, const Vector3 *trans, int mag,
                          short ang, short angY);

extern u16 gKuppaScriptFrame;

/* File-local view of dCamera_c (include/dCamera_c.h is C++): the fields this
 * script op touches. */
typedef struct {
    u8 pad_000[0x80];
    Vector3 lookAt; /* 0x080 */
    Vector3 pos;    /* 0x08c */
    u8 pad_098[0x18];
    Vector3 savedLookAt; /* 0x0b0 */
    u8 pad_0bc[0xe6];
    /* Accumulated by this op and added to the vertical and horizontal
       angles of the pos -> savedLookAt line before lookAt is rebuilt from
       it; func_02007d58 zeroes both. */
    short mPitchOffset; /* 0x1a2 */
    short mYawOffset;   /* 0x1a4 */
} CameraView;

int func_020079ac(char *self, unsigned char *p, int tag) {
    CameraView *cam = (CameraView *)self;
    int dist;
    short vert, horz;
    if (tag == gKuppaScriptFrame) {
        cam->savedLookAt.x = cam->lookAt.x;
        cam->savedLookAt.y = cam->lookAt.y;
        cam->savedLookAt.z = cam->lookAt.z;
    }
    cam->mPitchOffset -= ReadUnalignedShort(p);
    cam->mYawOffset += ReadUnalignedShort(p + 2);
    func_02007c9c(&cam->pos, &cam->savedLookAt, &dist, &vert, &horz);
    vert = (short)(vert + cam->mPitchOffset);
    horz = (short)(horz + cam->mYawOffset);
    func_02007c14(&cam->lookAt, &cam->pos, dist, vert, horz);
    return 1;
}
