#include "types.h"

/* The 0x24-byte follower func_ov007_020c844c allocates; names as in
 * func_ov007_020c83fc, only the slots this file touches. */
typedef struct Ov007Follower {
    Vector3 *target; /* 0x00 */
    char pad_04[0x1c];
    int flags; /* 0x20: bit 0 pins the point */
} Ov007Follower;

/* The 0x14-byte point list func_ov007_020c798c builds; only the points. */
typedef struct Ov007PointList {
    Ov007Follower **items; /* 0x0 */
} Ov007PointList;

/* The template every swing is built from (data_ov007_020d7cc8); names as in
 * func_ov007_020c9c24, only the slots this file reads. */
typedef struct Ov007SwingParams {
    int chainLength;    /* 0x00: points in the chain */
    int chainPointMass; /* 0x04: Q12 */
    char pad_08[0xc];
    int sidePointMass; /* 0x14: Q12 */
} Ov007SwingParams;

/* The 0x70-byte swing this function builds; names as in
 * func_ov007_020c9c24, func_ov007_020c9a84 and func_ov007_020c9f10. */
typedef struct Ov007Swing {
    void *mesh;               /* 0x00: func_ov007_020c9d90 binds it */
    Ov007SwingParams *params; /* 0x04 */
    int meshPoint;            /* 0x08 */
    Vector3 anchor;           /* 0x0c */
    /* 0x18: one position per chain point, z = index << 12 apart */
    Vector3 *chainPositions;
    Ov007PointList *chain; /* 0x1c */
    Vector3 xPointPos[2];  /* 0x20: i << 12 apart along x */
    Vector3 yPointPos[2];  /* 0x38: i << 12 apart along y */
    void *xPoints[2];      /* 0x50 */
    void *yPoints[2];      /* 0x58 */
    void *xLinks[2];       /* 0x60 */
    void *yLinks[2];       /* 0x68 */
} Ov007Swing;

typedef char Ov007Swing_size_must_be_0x70[sizeof(Ov007Swing) == 0x70 ? 1 : -1];

extern int func_ov007_020c3df4(int a, void *b);
extern Ov007PointList *func_ov007_020c798c(int springMode, int count, int pointMass, int flags);
extern void func_ov007_020c7804(Ov007PointList *list);
extern void *func_ov007_020c844c(int p, int q);
extern void *func_ov007_020c80a4(void);

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

    swing = (Ov007Swing *)func_ov007_020c3df4(0, (void *)sizeof(Ov007Swing));
    swing->mesh = 0;
    swing->params = params;
    n = params->chainLength;
    swing->anchor = (Vector3){0, 0, 0};
    swing->chainPositions = (Vector3 *)func_ov007_020c3df4(0, (void *)(n * 12));
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
        swing->xPoints[j] = func_ov007_020c844c((int)&swing->xPointPos[j], params->sidePointMass);
        swing->yPoints[j] = func_ov007_020c844c((int)&swing->yPointPos[j], params->sidePointMass);
        swing->xLinks[j] = func_ov007_020c80a4();
        swing->yLinks[j] = func_ov007_020c80a4();
    }
    return swing;
}
