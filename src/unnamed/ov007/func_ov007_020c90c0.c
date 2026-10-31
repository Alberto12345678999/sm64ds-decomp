#include "Ov007Tween.h"

/* Mode 0 step, shared by the scalar and vector tweens: advances t by step
 * and, once t has reached 0x1000, holds it there and sets state 2. */
void func_ov007_020c90c0(Ov007Tween *tw) {
    short value = tw->t;

    if (value >= 0x1000) {
        tw->t = 0x1000;
        tw->state = 2;
        return;
    }

    {
        int speed = tw->step;
        short *pos = &tw->t;
        short old = *pos;

        speed <<= 16;
        *pos = old + (speed >> 16);
    }
}
