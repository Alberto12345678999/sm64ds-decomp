//cpp
#include "types.h"
#include "Ov007Swing.h"
extern "C" {
extern void func_ov007_020c8440(void *p);
extern void func_ov007_020c8098(void *p);
extern void func_ov007_020c78dc(void *p);
extern int func_ov007_020c3d1c(void *p);

/* Frees the swing: its side points (func_ov007_020c8440) and links
 * (func_ov007_020c8098), the chain (func_ov007_020c78dc), the chain's
 * positions and the swing itself. */
void func_ov007_020c9fa0(Ov007Swing *self) {
    int i;
    for (i = 0; i < 2; i++) {
        func_ov007_020c8440(self->xPoints[i]);
        func_ov007_020c8440(self->yPoints[i]);
        func_ov007_020c8098(self->xLinks[i]);
        func_ov007_020c8098(self->yLinks[i]);
    }
    func_ov007_020c78dc(self->chain);
    func_ov007_020c3d1c(self->chainPositions);
    func_ov007_020c3d1c(self);
}
}
