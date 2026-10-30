#include "types.h"
#include "nitro/fx/fx.h"
#include "Ov007Swing.h"
#pragma opt_common_subs off

extern void func_ov007_020c7a84(Ov007Link *link, int stiffness, int damping);
extern void func_ov007_020c80c8(Ov007Follower *f, int damping, int shift);
extern void func_ov007_020c7560(Ov007PointList *list, int stiffness, int damping);
extern void func_ov007_020c7504(Ov007PointList *list, int damping, int shift);

/* One simulation step: the side points spring along z, the chain's pinned
 * first point follows the mesh normal under it, then the chain springs and
 * integrates. */
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
