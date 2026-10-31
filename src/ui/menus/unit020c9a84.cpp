//cpp
/* unit020c9a84 -- ov007 unit 0x020c9a84..0x020ca1d4: 6 functions, .text only.
 *
 * The menu's item swings. ov007 is the title and file-select menu program
 * that dScDSMT_c hosts; outside dScDSMT_c it has no ROM RTTI or vtable, so
 * no class name is claimed and the file keeps the unit<addr> name.
 *
 * What the code does. Each menu item hangs from the grid mesh on a swing
 * (Ov007Swing, include/Ov007Swing.h): a chain of spring points along z with
 * its first point pinned, and two pairs of side points spread along x and
 * along y, each linked to the mesh point nearest it.
 * func_ov007_020ca010 builds a swing from its template and
 * func_ov007_020c9fa0 frees it; func_ov007_020c9f10 places it and
 * func_ov007_020c9d90 binds it to the mesh; func_ov007_020c9c24 steps it
 * once; func_ov007_020c9a84 turns it into the item sprite's offset and tilt.
 *
 * Edges: these six are the overlay's only functions that take an
 * Ov007Swing. func_ov007_020c9a2c before them parses a binary file
 * (Ov007BinFile) and func_ov007_020ca1d4 after them starts the mesh-wave
 * functions.
 *
 * Emission order: mwccarm 2004/b56 emits one .text section per function in
 * the reverse of source order, so the highest-address function is written
 * first here and the functions come out in ROM order.
 *
 * The functions keep their ROM names under C linkage.
 */
#include "types.h"
#include "nitro/fx/fx.h"
#include "cstd.h"
#include "math/CalcLib.h"
#include "Ov007Swing.h"

extern "C" {

extern void *func_ov007_020c3df4(const char *name, int size);
extern void func_ov007_020c3d1c(void *p);
extern int func_ov007_020c30ac(Vector3 *arr, int count, Vector3 *target, int arg4, int *out);
extern void func_ov007_020c7504(Ov007PointList *list, int damping, int shift);
extern void func_ov007_020c7560(Ov007PointList *list, int stiffness, int damping);
extern void func_ov007_020c7804(Ov007PointList *list);
extern void func_ov007_020c78dc(void *p);
extern Ov007PointList *func_ov007_020c798c(int springMode, int count, int pointMass, int flags);
extern void func_ov007_020c7a84(Ov007Link *link, int stiffness, int damping);
extern void func_ov007_020c8010(Ov007Link *link, Ov007Follower *from, Ov007Follower *to);
extern void func_ov007_020c8098(void *p);
extern Ov007Link *func_ov007_020c80a4(void);
extern void func_ov007_020c80c8(Ov007Follower *f, int damping, int shift);
extern void func_ov007_020c8440(void *p);
extern Ov007Follower *func_ov007_020c844c(Vector3 *p, int q);
extern int func_020538b8(int x, int y);

/* The ROM copies a Vector3 here as a block move (ldm/stm). The C++ front end
   copies Vector3, and any struct of three named ints, member by member; a
   struct whose only member is an array keeps the block move, so every copy
   goes through Vector3Bits. */
struct Vector3Bits {
    int w[3];
};

/* A POD Vector3 for locals. A real Vector3 local emits the vague-linkage
   ~Vector3 into this text-only unit, and with Vector3's user-declared
   constructor the zero-initialised locals store differently from the ROM's. */
struct RawVector3 {
    int x, y, z;
};

/* Ov007Swing's side point positions (0x20 xPointPos, 0x38 yPointPos) as
   block-copy rows. Copying into swing->xPointPos[j] through a cast pointer
   shares its address with the func_ov007_020c844c argument; the ROM forms
   the copy's address from the swing plus a fixed offset, as a member
   access does. */
struct SwingSideRows {
    u8 pad[0x20];
    Vector3Bits x[2];
    Vector3Bits y[2];
};

/* Builds a swing from params: a chain of chainLength points laid along z
 * with x/y springs (mode 2) and its first point pinned, and two pairs of
 * side points with a link each, for func_ov007_020c9d90 to tie to the
 * mesh. */
// @symbol func_ov007_020ca010
Ov007Swing *func_ov007_020ca010(Ov007SwingParams *params) {
    Ov007Swing *swing;
    int n;
    int i;
    int j;
    Ov007PointList *chain;

    swing = (Ov007Swing *)func_ov007_020c3df4(0, sizeof(Ov007Swing));
    swing->mesh = 0;
    swing->params = params;
    n = params->chainLength;
    /* A temporary, not a named zero: the ROM gives it the frame's last slot. */
    (Vector3Bits &)swing->anchor = Vector3Bits();
    swing->chainPositions = (Vector3 *)func_ov007_020c3df4(0, n * 12);
    swing->chain = func_ov007_020c798c(2, params->chainLength, params->chainPointMass, 1);
    chain = swing->chain;
    for (i = 0; i < params->chainLength; i++) {
        RawVector3 v = {0, 0, 0};
        v.z = i << 12;
        (Vector3Bits &)swing->chainPositions[i] = (Vector3Bits &)v;
        chain->items[i]->target = &swing->chainPositions[i];
    }
    func_ov007_020c7804(chain);
    chain->items[0]->flags |= 1;
    for (j = 0; j < 2; j++) {
        {
            RawVector3 a = {0, 0, 0};
            a.x = j << 12;
            ((SwingSideRows *)swing)->x[j] = (Vector3Bits &)a;
        }
        {
            RawVector3 b = {0, 0, 0};
            b.y = j << 12;
            ((SwingSideRows *)swing)->y[j] = (Vector3Bits &)b;
        }
        swing->xPoints[j] = func_ov007_020c844c(&swing->xPointPos[j], params->sidePointMass);
        swing->yPoints[j] = func_ov007_020c844c(&swing->yPointPos[j], params->sidePointMass);
        swing->xLinks[j] = func_ov007_020c80a4();
        swing->yLinks[j] = func_ov007_020c80a4();
    }
    return swing;
}

/* Frees the swing: its side points (func_ov007_020c8440) and links
 * (func_ov007_020c8098), the chain (func_ov007_020c78dc), the chain's
 * positions and the swing itself. */
// @symbol func_ov007_020c9fa0
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

/* Places the swing at pos: the anchor there, the x side pair w apart along
 * x and the y side pair h apart along y, both centred on it. */
// @symbol func_ov007_020c9f10
void func_ov007_020c9f10(Ov007Swing *self, Vector3 *pos, int w, int h) {
    Vector3 *pe = &self->yPointPos[1];
    Vector3 *pd = &self->yPointPos[0];
    Vector3 *pc = &self->xPointPos[1];
    int *qd = &self->yPointPos[0].y;
    int *qe = &self->yPointPos[1].y;
    (Vector3Bits &)*pe = (Vector3Bits &)*pos;
    (Vector3Bits &)*pd = (Vector3Bits &)*pe;
    (Vector3Bits &)*pc = (Vector3Bits &)*pd;
    {
        Vector3 *pb = &self->xPointPos[0];
        (Vector3Bits &)*pb = (Vector3Bits &)*pc;
        (Vector3Bits &)self->anchor = (Vector3Bits &)*pb;
        pb->x -= w / 2;
        pc->x += w / 2;
        *qd -= h / 2;
        *qe += h / 2;
    }
}

/* Binds the swing to mesh: meshPoint is the mesh point nearest the anchor,
 * and each side point is linked to the mesh point nearest it. Each link is
 * bound with that mesh point held at restZ, so its rest offset is taken
 * against the flat mesh. The row of point index a is taken as a / rows,
 * not a / columns, as the ROM has it. */
// @symbol func_ov007_020c9d90
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

/* One simulation step: the side points spring along z, the chain's pinned
 * first point follows the mesh normal under it, then the chain springs and
 * integrates. Its one-function source was compiled with opt_common_subs
 * off; the push/pop keeps that to this function. */
#pragma push
#pragma opt_common_subs off
// @symbol func_ov007_020c9c24
void func_ov007_020c9c24(Ov007Swing *self, int arg1) {
    int i;
    int bnd;
    int nx, ny;
    int scale;
    Vector3_16 *n;
    Ov007SwingParams *ctx;

    for (i = 0; i < 2; i++) {
        ctx = self->params;
        func_ov007_020c7a84(self->xLinks[i], ctx->sideStiffness, ctx->sideDamping);
        func_ov007_020c80c8(self->xPoints[i], 0, arg1);
        ctx = self->params;
        func_ov007_020c7a84(self->yLinks[i], ctx->sideStiffness, ctx->sideDamping);
        func_ov007_020c80c8(self->yPoints[i], 0, arg1);
    }

    n = &self->mesh->vertexNormals[self->meshPoint];
    ctx = self->params;
    bnd = ctx->maxNormalX;
    nx = n->x;
    ny = n->y;

    if (nx > bnd)
        nx = bnd;
    else if (nx < -bnd)
        nx = (s16)(-bnd);

    bnd = ctx->maxNormalY;
    if (ny > bnd)
        ny = bnd;
    else if (ny < -bnd)
        ny = (s16)(-bnd);

    scale = ctx->normalScale;
    self->chain->items[0]->target->x = FX_MUL(nx, scale);
    scale = self->params->normalScale;
    self->chain->items[0]->target->y = FX_MUL(ny, scale);

    ctx = self->params;
    func_ov007_020c7560(self->chain, ctx->chainStiffness, ctx->chainDamping);
    func_ov007_020c7504(self->chain, 0, arg1);
}
#pragma pop

/* Turns the swing into the item sprite's pose (func_ov007_020beeb0 passes
 * the sprite's posOffset, rotX and rotY): offset gets the chain's last
 * point's x and y, and *rotX/*rotY the x and y side pairs' slopes, eased and
 * capped at maxRotX/maxRotY. */
// @symbol func_ov007_020c9a84
void func_ov007_020c9a84(Ov007Swing *self, Vector3 *offset, u16 *rotX, u16 *rotY) {
    RawVector3 d;
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
    SubVec3(&self->xPointPos[0], &self->xPointPos[1], (Vector3 *)&d);
    ra = func_020538b8(d.x, d.z);
    SubVec3(&self->yPointPos[0], &self->yPointPos[1], (Vector3 *)&d);
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
