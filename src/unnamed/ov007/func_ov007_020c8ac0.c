#include "Ov007Transition.h"

/* Clears a transition: no effect, idle, no screens, no end callback. */
void func_ov007_020c8ac0(Ov007Transition *tr) {
    tr->screens = 0;
    tr->effect = 0;
    tr->state = 0;
    tr->endAction = 0;
    tr->curve = 0;
    tr->t = 0;
    tr->step = 0;
    tr->reversed = 0;
    tr->onEnd = 0;
    tr->request = 0;
    tr->fx.brightness.to = 0;
    tr->fx.brightness.from = tr->fx.brightness.to;
    tr->planes = tr->fx.brightness.from;
}
