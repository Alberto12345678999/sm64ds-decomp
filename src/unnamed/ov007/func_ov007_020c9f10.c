#include "types.h"
#include "Ov007Swing.h"

/* Places the swing at pos: the anchor there, the x side pair w apart along
 * x and the y side pair h apart along y, both centred on it. */
void func_ov007_020c9f10(Ov007Swing *self, Vector3 *pos, int w, int h) {
    Vector3 *pe = &self->yPointPos[1];
    Vector3 *pd = &self->yPointPos[0];
    Vector3 *pc = &self->xPointPos[1];
    int *qd = &self->yPointPos[0].y;
    int *qe = &self->yPointPos[1].y;
    *pe = *pos;
    *pd = *pe;
    *pc = *pd;
    {
        Vector3 *pb = &self->xPointPos[0];
        *pb = *pc;
        self->anchor = *pb;
        pb->x -= w / 2;
        pc->x += w / 2;
        *qd -= h / 2;
        *qe += h / 2;
    }
}
