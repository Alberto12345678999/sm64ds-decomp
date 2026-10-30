#include "types.h"
#include "nitro/fx/fx.h"

#define reg_G3_COLOR        (*(volatile u32 *)0x04000480)
#define reg_G3_POLYGON_ATTR (*(volatile u32 *)0x040004a4)

/* The SPL field names here (such as dbbScale, textureTileCountS/T,
 * polygonRotAxis, polygonReferencePlane, polygonIDs) are pret's SPL
 * coinages, kept so the two can be read side by side. */
/* The particle definition's header (func_0204a730's PtclData; SPL's
 * SPLResourceHeader): only the aspect ratio applies to children. */
typedef struct PtclData {
    char pad_00[0x20];
    s16 aspectRatio; /* 0x20 -- x scale over y scale */
} PtclData;

/* The child record (func_0204c304's Def; SPL's SPLChildResource), as far as
 * this draw reads it: the polygon rotation axis and reference plane flag
 * bits and the texture tile counts. */
typedef struct PtclChild {
    u16 : 9;
    u16 polygonRotAxis : 2;        /* bits 9-10 -- data_02099fbc index */
    u16 polygonReferencePlane : 1; /* bit 11 -- data_02099fb4 index */
    u16 : 4;
    char pad_02[0x10 - 2];
    u32 textureTileCountS : 2; /* 0x10 bits 0-1 */
    u32 textureTileCountT : 2; /* bits 2-3 */
    u32 : 28;
} PtclChild;

/* The particle definition (func_0204a730's PtclDef; SPL's SPLResource). */
typedef struct PtclDef {
    PtclData *data;
    char pad_04[0x14 - 4];
    PtclChild *child; /* 0x14 */
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

/* Draw one child particle as a textured quad (child draw type 2,
 * func_0204a5c8): func_0204b244 with the child record's rotation axis, plane
 * and tile counts, and the rotation applied before the scale. pret's SPL calls
 * this SPLDraw_Child_Polygon. */
void func_0204b028(ManagerView *mgr, Particle *ptcl) {
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
        PtclChild *child = mgr->mCurrentSystem->mDefinition->child;
        int idx = ptcl->angle >> 4;
        data_02099fbc[child->polygonRotAxis](data_02082214[idx * 2], data_02082214[idx * 2 + 1],
                                             rot);
    }

    {
        PtclDef *def = mgr->mCurrentSystem->mDefinition;
        int sy = FX_MUL(ptcl->scale, ptcl->animScale);
        s16 aspectRatio = def->data->aspectRatio;
        int sx = FX_MUL(sy, aspectRatio);
        func_020527e8(scl, sx, sy, sy);
    }

    MulMat4x3Mat4x3(rot, scl, out);

    out[9] = ptcl->offset.x + ptcl->basePosition.x;
    out[10] = ptcl->offset.y + ptcl->basePosition.y;
    out[11] = ptcl->offset.z + ptcl->basePosition.z;

    func_020553a4(mgr->mDrawMatrix);
    func_02055388(out);

    reg_G3_COLOR = ptcl->color;
    {
        PtclChild *child = mgr->mCurrentSystem->mDefinition->child;
        data_02099fb4[child->polygonReferencePlane](child->textureTileCountS,
                                                    child->textureTileCountT);
    }
}
