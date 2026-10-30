//cpp
#include "dCamera_c.h"

extern "C" {

/* Parameter types follow the definitions in src/engine/view/d_camera.cpp. */
void func_0200cb58(void *cam, int index);
void func_0200cce4(char *cam);

/* Camera state init: switch to mode record 0x1e, place lookAt and pos from
 * it (func_0200cce4), and set mFlags 0x100. */
int func_020050dc(dCamera_c *cam) {
    func_0200cb58(cam, 0x1e);
    func_0200cce4((char *)cam);
    cam->mFlags |= 0x100;
    return 1;
}
}
