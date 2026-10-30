//cpp
#include "types.h"
#include "cstd.h"
#include "Ov007Swing.h"

extern "C" {

extern int func_ov007_020c30ac(Vector3 *arr, int count, Vector3 *target, int arg4, int *out);
extern void func_ov007_020c8010(Ov007Link *link, Ov007Follower *from, Ov007Follower *to);

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
        pos->z = mesh->params.restZ;
        func_ov007_020c8010(self->xLinks[i], self->xPoints[i], point);
        point->target->z = oldZ;

        grid = mesh->grid;
        column = cstd::mod(b, grid->columns);
        row = cstd::div(b, grid->rows);
        point = grid->rowLists[row]->items[column];
        pos = point->target;
        oldZ = pos->z;
        pos->z = mesh->params.restZ;
        func_ov007_020c8010(self->yLinks[i], self->yPoints[i], point);
        point->target->z = oldZ;
    }
}
}
