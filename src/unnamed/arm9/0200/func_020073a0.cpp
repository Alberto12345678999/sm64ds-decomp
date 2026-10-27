//cpp
#include "types.h"
#include "math/Approach.h"

extern "C" {

/* A dCamera_c script op, not an actor method: its entry in the camera's
   member-function table is at 0x02086cb0, between func_020072c4 and
   func_02007d58. The fields used here, named as in include/dCamera_c.h. */
struct dCamera_c {
    char pad_000[0xb0];
    Vector3 savedLookAt; /* 0x0b0 */
    Vector3 savedPos;    /* 0x0bc */
};

extern int data_02086ed8[3];
extern int func_02007cec(int a, int b, int c);

int func_020073a0(struct dCamera_c *cam) {
    int stackbuf[3];
    stackbuf[0] = data_02086ed8[0];
    stackbuf[1] = data_02086ed8[1];
    stackbuf[2] = data_02086ed8[2];

    func_02007cec((int)&cam->savedLookAt, (int)stackbuf, 0xcc);
    ApproachLinear(cam->savedPos.y, 0, 0x2000);
    ApproachLinear(cam->savedPos.z, -0xc8000, 0x6aaa);
    return 1;
}
}
