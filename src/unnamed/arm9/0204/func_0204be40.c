#include "common.h"
#include "nitro/fx/fx.h"

#define reg_G3_COLOR        (*(volatile u32 *)0x04000480)
#define reg_G3_IDENTITY     (*(volatile u32 *)0x04000454)
#define reg_G3_POLYGON_ATTR (*(volatile u32 *)0x040004a4)

/* The particle definition's header (func_0204a730's PtclData; SPL's
 * SPLResourceHeader), as far as this draw reads it: the aspect ratio and the
 * texture tile counts in the misc word. */
typedef struct PtclData {
    char pad_00[0x20];
    s16 aspectRatio; /* 0x20 -- x scale over y scale */
    char pad_22[0x34 - 0x22];
    u32 : 24;                  /* 0x34 -- loopFrames, dbbScale */
    u32 textureTileCountS : 2; /* bits 24-25 */
    u32 textureTileCountT : 2; /* bits 26-27 */
    u32 : 4;
} PtclData;

/* The particle definition (func_0204a730's PtclDef; SPL's SPLResource). */
typedef struct PtclDef {
    PtclData *data;
} PtclDef;

/* The polygon IDs a system's particles cycle through, one per particle. */
typedef struct PolygonIDs {
    u32 min : 6;
    u32 max : 6;
    u32 current : 6;
    u32 : 14;
} PolygonIDs;

/* Particle::System, named as func_0204c584.c's view. */
typedef struct ParticleSystem {
    char pad_00[0x18];
    PtclDef *mDefinition; /* 0x18 */
    char pad_1c[0x74 - 0x1c];
    PolygonIDs polygonIDs; /* 0x74 */
} ParticleSystem;

typedef struct Visibility {
    u16 baseAlpha : 5;
    u16 animAlpha : 5;
    u16 : 6;
} Visibility;

/* Particle::Element and the fields past its 0x30 bytes, named as in
 * func_0204c584.c. */
typedef struct Particle {
    char pad_00[8];
    Vector3 basePosition; /* 0x08 */
    Vector3 offset;       /* 0x14 */
    char pad_20[0x30 - 0x20];
    int scale;      /* 0x30 */
    s16 animScale;  /* 0x34 */
    u16 angle;      /* 0x36 */
    char pad_38[2]; /* angularSpeed */
    u16 color;      /* 0x3a */
    char pad_3c[4];
    Visibility visibility; /* 0x40 */
} Particle;

/* Particle::Manager (include/Particle__Manager.h is C++), named as there. */
typedef struct ManagerView {
    char pad_00[0x30];
    u32 mPolygonAttr;               /* 0x30 */
    ParticleSystem *mCurrentSystem; /* 0x34 -- the system being drawn */
    int *mDrawMatrix;               /* 0x38 */
} ManagerView;

extern void MulVec3Mat4x3(Vector3 *v, Matrix4x3 *m, Vector3 *dst);
extern void func_02055388(int *m);             /* multiply by the 4x3 matrix */
extern void func_0204c24c(u8 tileS, u8 tileT); /* the XY-plane quad */
extern s16 data_02082214[];                    /* the sin/cos table */

/* Draw one particle as a camera-facing quad (draw type 0, func_0204a5c8):
 * alpha and the next polygon ID into POLYGON_ATTR (nothing more when the
 * alpha is 0), move basePosition + offset into view space, then load a matrix
 * that rotates by the particle's angle about the view axis, scales by
 * scale * animScale (x by aspectRatio too) and translates there, set its
 * color and emit the XY-plane quad. pret's SPL calls this SPLDraw_Billboard;
 * func_0204bbd8 is the child-particle twin. */
void func_0204be40(ManagerView *mgr, Particle *ptcl) {
    ParticleSystem *sys = mgr->mCurrentSystem;
    s16 aspectRatio = sys->mDefinition->data->aspectRatio;
    int alpha = (ptcl->visibility.baseAlpha * (ptcl->visibility.animAlpha + 1)) >> 5;
    int *view = mgr->mDrawMatrix;
    Vector3 trans;
    int mat[12];
    u32 id;
    u32 v;
    int sx;
    int sy;

    /* polygonIDs.current, read through the whole word: the field read does not match */
    v = *(u32 *)&sys->polygonIDs << 14;
    id = v >> 26;
    v = mgr->mPolygonAttr | 0xc0;
    v |= id << 24;
    v |= alpha << 16;
    reg_G3_POLYGON_ATTR = v;
    reg_G3_POLYGON_ATTR;
    {
        PolygonIDs *ids = &sys->polygonIDs;
        ids->current++;
        if (sys->polygonIDs.current > sys->polygonIDs.max)
            ids->current = sys->polygonIDs.min;
    }

    if (alpha == 0)
        return;

    sy = FX_MUL(ptcl->scale, ptcl->animScale);
    trans.x = ptcl->offset.x + ptcl->basePosition.x;
    trans.y = ptcl->offset.y + ptcl->basePosition.y;
    trans.z = ptcl->offset.z + ptcl->basePosition.z;
    MulVec3Mat4x3(&trans, (Matrix4x3 *)view, &trans);

    {
        int idx = ptcl->angle >> 4;
        int cos;
        int sin;

        sx = FX_MUL(sy, aspectRatio);
        cos = data_02082214[idx * 2 + 1];
        sin = data_02082214[idx * 2];

        /* the 4x3 rows: (cos, sin, 0) * sx, (-sin, cos, 0) * sy, (0, 0, 1),
         * then the view-space position */
        mat[0] = FX_MUL(cos, sx);
        mat[3] = FX_MUL(-sin, sy);
        mat[1] = FX_MUL(sin, sx);
        mat[9] = trans.x;
        mat[10] = trans.y;
        mat[8] = 0x1000;
        mat[11] = trans.z;
        mat[6] = 0;
        mat[4] = FX_MUL(cos, sy);
        mat[7] = 0;
        mat[2] = 0;
        mat[5] = 0;
        reg_G3_IDENTITY = 0;
        func_02055388(mat);
    }

    reg_G3_COLOR = ptcl->color;
    {
        PtclData *data = mgr->mCurrentSystem->mDefinition->data;
        func_0204c24c(data->textureTileCountS, data->textureTileCountT);
    }
}
