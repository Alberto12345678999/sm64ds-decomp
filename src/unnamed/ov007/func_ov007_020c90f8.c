#include "Ov007Tween.h"

/* Resets a tween: idle, mode 0, no step, t at 0. Ov007VecTween shares these
 * fields, so func_ov007_020c8f64 resets its vector tweens through this too. */
void func_ov007_020c90f8(Ov007Tween *tw)
{
    tw->state = 0;
    tw->mode = 0;
    tw->step = 0;
    tw->t = 0;
}
