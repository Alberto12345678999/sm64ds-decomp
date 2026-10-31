//cpp
#include "types.h"
#include "cstd.h"
#include "Ov007Swing.h"

extern "C" {

extern void SubVec3(Vector3 *a, Vector3 *b, Vector3 *c);
extern int func_020538b8(int x, int y);

/* Turns the swing into the item sprite's pose (func_ov007_020beeb0 passes
 * the sprite's posOffset, rotX and rotY): offset gets the chain's last
 * point's x and y, and *rotX/*rotY the x and y side pairs' slopes, eased and
 * capped at maxRotX/maxRotY. */
void func_ov007_020c9a84(Ov007Swing *self, Vector3 *offset, u16 *rotX, u16 *rotY) {
    Vector3 d;
    int ra, rb;
    short a1, a2;
    int aa, ab, t1, t2, q1, q2;

    offset->x = self->chainPositions[self->chain->count - 1].x;
    {
        Ov007PointList *p = self->chain;
        Vector3 *base = self->chainPositions;
        int n = p->count - 1;
        offset->y = base[n].y;
    }
    SubVec3((Vector3 *)&self->xPointPos[0], (Vector3 *)&self->xPointPos[1], (Vector3 *)&d);
    ra = func_020538b8(d.x, d.z);
    SubVec3((Vector3 *)&self->yPointPos[0], (Vector3 *)&self->yPointPos[1], (Vector3 *)&d);
    rb = func_020538b8(d.z, d.y);
    a1 = (unsigned short)(ra + 0x3fff);
    a2 = (unsigned short)(rb + 0x7fff);
    aa = (a1 >= 0) ? a1 : -a1;
    {
        unsigned short lim = self->params->maxRotX;
        if (aa <= 0)
            t1 = 0;
        else if (aa >= lim)
            t1 = 0x1000;
        else
            t1 = cstd::div(aa << 12, lim);
    }
    ab = (a2 >= 0) ? a2 : -a2;
    {
        unsigned short lim = self->params->maxRotY;
        if (ab <= 0)
            t2 = 0;
        else if (ab >= lim)
            t2 = 0x1000;
        else
            t2 = cstd::div(ab << 12, lim);
    }
    q1 = (int)(((long long)t1 * (0x2000 - t1)) >> 12);
    q2 = (int)(((long long)t2 * (0x2000 - t2)) >> 12);
    *rotX = (short)((self->params->maxRotX * (q1 * ((a1 >= 0) ? 1 : -1))) >> 12);
    *rotY = (short)((self->params->maxRotY * (q2 * ((a2 >= 0) ? 1 : -1))) >> 12);
}
}
