#include "Ov007Camera.h"

extern int func_ov007_020c8de0(Ov007VecTween *o);
extern int func_ov007_020c8f98(Ov007Tween *tw);

/* Steps each of the camera's tweens whose `tweening` bit is set, and clears
 * the bit once the tween reports it has arrived. Each clear re-reads the
 * flags through a const view: with `&=` mwccarm keeps the value read before
 * the call in a register and the function grows by 0xc bytes. */
void func_ov007_020bff38(Ov007Camera *cam) {
    if (cam->tweening & 1) {
        if (func_ov007_020c8de0(cam->eyeTween))
            cam->tweening = ((const Ov007Camera *)cam)->tweening & ~1u;
    }
    if (cam->tweening & 2) {
        if (func_ov007_020c8de0(cam->targetTween))
            cam->tweening = ((const Ov007Camera *)cam)->tweening & ~2u;
    }
    if (cam->tweening & 4) {
        if (func_ov007_020c8f98(cam->distanceTween))
            cam->tweening = ((const Ov007Camera *)cam)->tweening & ~4u;
    }
}
