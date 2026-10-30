#include "types.h"
#include "Ov007Swing.h"

extern void *func_ov007_020c3df4(int heapName, int size);
extern Ov007PointList *func_ov007_020c798c(int springMode, int count, int pointMass, int flags);
extern void func_ov007_020c7804(Ov007PointList *list);
extern Ov007Follower *func_ov007_020c844c(Vector3 *p, int q);
extern Ov007Link *func_ov007_020c80a4(void);

/* Builds a swing from params: a chain of chainLength points laid along z
 * with x/y springs (mode 2) and its first point pinned, and two pairs of
 * side points with a link each, for func_ov007_020c9d90 to tie to the
 * mesh. */
Ov007Swing *func_ov007_020ca010(Ov007SwingParams *params) {
    Ov007Swing *swing;
    int n;
    int i;
    int j;
    Ov007PointList *chain;

    swing = func_ov007_020c3df4(0, sizeof(Ov007Swing));
    swing->mesh = 0;
    swing->params = params;
    n = params->chainLength;
    swing->anchor = (Vector3){0, 0, 0};
    swing->chainPositions = func_ov007_020c3df4(0, n * 12);
    swing->chain = func_ov007_020c798c(2, params->chainLength, params->chainPointMass, 1);
    chain = swing->chain;
    for (i = 0; i < params->chainLength; i++) {
        Vector3 v = {0, 0, 0};
        v.z = i << 12;
        swing->chainPositions[i] = v;
        chain->items[i]->target = &swing->chainPositions[i];
    }
    func_ov007_020c7804(chain);
    chain->items[0]->flags |= 1;
    for (j = 0; j < 2; j++) {
        {
            Vector3 a = {0, 0, 0};
            a.x = j << 12;
            swing->xPointPos[j] = a;
        }
        {
            Vector3 b = {0, 0, 0};
            b.y = j << 12;
            swing->yPointPos[j] = b;
        }
        swing->xPoints[j] = func_ov007_020c844c(&swing->xPointPos[j], params->sidePointMass);
        swing->yPoints[j] = func_ov007_020c844c(&swing->yPointPos[j], params->sidePointMass);
        swing->xLinks[j] = func_ov007_020c80a4();
        swing->yLinks[j] = func_ov007_020c80a4();
    }
    return swing;
}
