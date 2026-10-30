//cpp
#include "types.h"
#include "cstd.h"
#include "Ov007Spring.h"

extern "C" {

/* Reconstructed layouts and names, not recovered class identity; only the
 * slots this file touches. */

/* data_ov007_02104bd4[0], the grid mesh func_ov007_020cbbb0 builds; names
 * as in func_ov007_020ca5f0. */
typedef struct Ov007Mesh {
    Vector3 *verts;  /* 0x00: one per grid point */
    Ov007Grid *grid; /* 0x04 */
    char pad_08[0x18];
    int restZ; /* 0x20: the z func_ov007_020cbbb0 builds every point at */
} Ov007Mesh;

/* The swing func_ov007_020ca010 builds; names as there. */
typedef struct Ov007Swing {
    Ov007Mesh *mesh; /* 0x00 */
    char pad_04[4];
    int meshPoint;  /* 0x08 */
    Vector3 anchor; /* 0x0c */
    char pad_18[8];
    Vector3 xPointPos[2]; /* 0x20 */
    Vector3 yPointPos[2]; /* 0x38 */
    void *xPoints[2];     /* 0x50 */
    void *yPoints[2];     /* 0x58 */
    void *xLinks[2];      /* 0x60 */
    void *yLinks[2];      /* 0x68 */
} Ov007Swing;

extern int func_ov007_020c30ac(Vector3 *arr, int count, Vector3 *target, int arg4, int *out);
extern void func_ov007_020c8010(void *link, void *from, void *to);

/* Binds the swing to mesh: meshPoint is the mesh point nearest the anchor,
 * and each side point is linked to the mesh point nearest it. Each link is
 * bound with that mesh point held at restZ, so its rest offset is taken
 * against the flat mesh. The row of point index a is taken as a / rows,
 * not a / columns, as the ROM has it. */
void func_ov007_020c9d90(Ov007Swing *self, Ov007Mesh *mesh) {
    int count;
    int i;
    int a;
    int b;
    int column;
    int row;
    Ov007Grid *grid;
    Ov007Follower *point;
    Vector3 *pos;
    int oldZ;

    count = mesh->grid->columns * mesh->grid->rows;
    self->mesh = mesh;
    self->meshPoint = func_ov007_020c30ac(mesh->verts, count, &self->anchor, -1, 0);

    for (i = 0; i < 2; i++) {
        a = func_ov007_020c30ac(mesh->verts, count, &self->xPointPos[i], -1, 0);
        b = func_ov007_020c30ac(mesh->verts, count, &self->yPointPos[i], -1, 0);

        grid = mesh->grid;
        column = cstd::mod(a, grid->columns);
        row = cstd::div(a, grid->rows);
        point = grid->rowLists[row]->items[column];
        pos = point->target;
        oldZ = pos->z;
        pos->z = mesh->restZ;
        func_ov007_020c8010(self->xLinks[i], self->xPoints[i], point);
        point->target->z = oldZ;

        grid = mesh->grid;
        column = cstd::mod(b, grid->columns);
        row = cstd::div(b, grid->rows);
        point = grid->rowLists[row]->items[column];
        pos = point->target;
        oldZ = pos->z;
        pos->z = mesh->restZ;
        func_ov007_020c8010(self->yLinks[i], self->yPoints[i], point);
        point->target->z = oldZ;
    }
}
}
