#include "Ov007Transition.h"

extern void *func_ov007_020c3df4(int a, int b);
extern void func_ov007_020c8ac0(Ov007Transition *tr);

/* Allocates a transition and clears it (func_ov007_020c8ac0). */
Ov007Transition *func_ov007_020c8b10(void) {
    Ov007Transition *tr = (Ov007Transition *)func_ov007_020c3df4(0, sizeof(Ov007Transition));
    func_ov007_020c8ac0(tr);
    return tr;
}
