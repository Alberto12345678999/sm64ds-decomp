#include "types.h"
#include "nitro/fx/fx.h"

#define reg_G3_COLOR        (*(volatile u32 *)0x04000480)
#define reg_G3_POLYGON_ATTR (*(volatile u32 *)0x040004a4)

/* The SPL field names here (such as dbbScale, textureTileCountS/T,
 * polygonRotAxis, polygonReferencePlane, polygonIDs) are pret's lib/spl
 * coinages, kept so the two can be read side by side. */
/* The particle definition's header (func_0204a730's PtclData; SPL's
 * SPLResourceHeader), as far as this draw reads it: the polygon rotation axis
 * and reference plane flag bits, the aspect ratio, and the texture tile
 * counts in the misc word. */
typedef struct PtclData {
    u32 : 17;
    u32 polygonRotAxis : 2;        /* bits 17-18 -- data_02099fbc index */
    u32 polygonReferencePlane : 1; /* bit 19 -- data_02099fb4 index */
    u32 : 12;
    char pad_04[0x20 - 4];
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
    void *mDrawMatrix;              /* 0x38 */
} ManagerView;

extern s16 data_02082214[];                       /* the sin/cos table */
extern void (*data_02099fbc[])(int, int, void *); /* func_0204c0a8, func_0204c0e8 */
extern void (*data_02099fb4[])(u8, u8);           /* func_0204c24c, func_0204c194 */

extern void func_020527e8(int *m, int sx, int sy, int sz); /* scale matrix */
extern void MulMat4x3Mat4x3(void *a, void *b, void *out);
extern void func_020553a4(void *m); /* load the 4x3 matrix */
extern void func_02055388(void *m); /* multiply by the 4x3 matrix */

/* Draw one particle as a textured quad (draw type 2, func_0204a5c8): alpha
 * and the next polygon ID into POLYGON_ATTR (nothing more when the alpha is
 * 0), rotate by its angle about
 * the definition's axis, scale by scale * animScale (x by aspectRatio too),
 * translate to basePosition + offset, set its color and emit the quad in the
 * definition's plane. pret's SPL calls this SPLDraw_Polygon; func_0204b028
 * is the child-particle twin. */
void func_0204b244(ManagerView *mgr, Particle *ptcl) {
    ParticleSystem *sys = mgr->mCurrentSystem;
    int alpha = (ptcl->visibility.baseAlpha * (ptcl->visibility.animAlpha + 1)) >> 5;
    int out[12];
    int rot[12];
    int scl[12];
    u32 id;
    u32 v;

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

    {
        PtclData *data = mgr->mCurrentSystem->mDefinition->data;
        int idx = ptcl->angle >> 4;
        data_02099fbc[data->polygonRotAxis](data_02082214[idx * 2], data_02082214[idx * 2 + 1],
                                            rot);
    }

    {
        PtclData *data = mgr->mCurrentSystem->mDefinition->data;
        int sy = FX_MUL(ptcl->scale, ptcl->animScale);
        int sx = FX_MUL(sy, data->aspectRatio);
        func_020527e8(scl, sx, sy, sy);
    }

    MulMat4x3Mat4x3(scl, rot, out);

    out[9] = ptcl->offset.x + ptcl->basePosition.x;
    out[10] = ptcl->offset.y + ptcl->basePosition.y;
    out[11] = ptcl->offset.z + ptcl->basePosition.z;

    func_020553a4(mgr->mDrawMatrix);
    func_02055388(out);

    reg_G3_COLOR = ptcl->color;
    {
        PtclData *data = mgr->mCurrentSystem->mDefinition->data;
        data_02099fb4[data->polygonReferencePlane]((u8)data->textureTileCountS,
                                                   (u8)data->textureTileCountT);
    }
}
