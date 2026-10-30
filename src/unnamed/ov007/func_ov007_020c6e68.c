// @symbol func_ov007_020c6e68
#include "common.h"
#include "nitro/fx/fx.h"
#include "Ov007Picker.h"

/* Builds group `idx`'s spring chain: a point list over the stroke's points
 * (func_ov007_020c798c), each point's position (the stroke point
 * unprojected through the camera) and a copy of it, a link per point from
 * posPoint, and the head and tail links.
 *
 * The list's flags are 1 (own points), plus 2 (closed) when the path's
 * length (func_ov007_020c249c) times params->closeFactor is at least the
 * distance from the first point to the last. The scaled length has to be
 * computed BEFORE the dx/dz differences: with the multiply after them the
 * compiler colours the two pointer loads the other way round and the whole
 * block moves. The per-point addresses stay int base + byte offset: char *
 * bases lengthen the function by 12 bytes. */

extern int func_ov007_020c249c(Ov007StrokePath *path);
extern int func_020531a4(int a);
extern int func_ov007_020c3df4(int a, void *b);
extern Ov007Link *func_ov007_020c80a4(void);
extern void func_ov007_020c8010(Ov007Link *link, Ov007Follower *from, Ov007Follower *to);
extern void func_ov007_020bfe4c(char *thiz, int a, int b, int c, Vector3 *out);

extern Ov007PointList *func_ov007_020c798c(int springMode, int count, int pointMass, int flags);
extern void func_ov007_020c7804(Ov007PointList *list);

/* The overlay's camera (func_ov007_020c023c); only the slot this file reads. */
typedef struct Ov007Camera {
    char pad_00[0x2c];
    int distance; /* 0x2c: func_ov007_020bffb8 places the eye this far from the target */
} Ov007Camera;

/* The parameter keeps func_ov007_020c6d20's char * spelling (the
 * declaration-agreement gate); the typed view is a local. */
void func_ov007_020c6e68(char *picker, int idx) {
    Ov007Picker *self = (Ov007Picker *)picker;
    Ov007StrokePath *grp;
    Ov007PickerParams *fp;
    int flag;
    int count;
    int i;
    Ov007PointList *sb;
    int scale;
    int *px, *pz;
    int last;
    int dx, dz, proj, lensq;
    Ov007PickerParams *owner;

    grp = self->groups[idx];
    fp = self->params;
    count = grp->pointCount;
    flag = 1;
    scale = func_ov007_020c249c(grp);

    owner = self->params;
    px = grp->xCoords;
    pz = grp->yCoords;
    last = count - 1;
    proj = FX_MUL(scale, owner->closeFactor);
    dx = px[0] - px[last];
    dz = pz[0] - pz[last];
    lensq = FX_MUL(dx, dx) + FX_MUL(dz, dz);
    if (func_020531a4(lensq) <= proj)
        flag |= 2;

    {
        Ov007PointList *node = func_ov007_020c798c(2, grp->pointCount, fp->pointMass, flag);
        flag = count * 0xc;
        self->pointLists[idx] = node;
    }
    sb = self->pointLists[idx];

    self->groupPoints[idx] = (Vector3 *)func_ov007_020c3df4(0, (void *)flag);
    self->groupPointCopies[idx] = (Vector3 *)func_ov007_020c3df4(0, (void *)flag);
    self->groupLinks[idx] = (Ov007Link **)func_ov007_020c3df4(0, (void *)(count << 2));

    i = 0;
    if (count > 0) {
        flag = 0;
        do {
            Ov007Link *p = func_ov007_020c80a4();
            self->groupLinks[idx][i] = p;
            func_ov007_020c8010(p, self->posPoint, sb->items[i]);
            {
                int base = (int)self->groupPoints[idx];
                sb->items[i]->target = (Vector3 *)(base + flag);
            }
            {
                Ov007Camera *a8 = self->camera;
                int base = (int)self->groupPoints[idx];
                Vector3 *out = (Vector3 *)(base + flag);
                func_ov007_020bfe4c((char *)a8, grp->xCoords[i], grp->yCoords[i], -a8->distance,
                                    out);
            }
            {
                int base_d = (int)self->groupPointCopies[idx];
                int base_s = (int)self->groupPoints[idx];
                Vector3 *d = (Vector3 *)(base_d + flag);
                Vector3 *s = (Vector3 *)(base_s + flag);
                flag += 0xc;
                i++;
                *d = *s;
            }
        } while (i < count);
    }

    self->headLinks[idx] = func_ov007_020c80a4();
    self->tailLinks[idx] = func_ov007_020c80a4();
    func_ov007_020c7804(sb);
}
