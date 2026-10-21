extern void func_0204dab4(void *a0, void *a1, void *a2, int a3, void *a4);
extern void func_ov007_020c3fe4(void *obj);
extern void func_ov007_020be7a8(void);
extern int *data_ov007_02104bc0;

/* The 0x44-byte OAM sprite node func_ov007_020c11ac allocates; names as in
 * func_ov007_020c10ec, only the slots this file touches. */
typedef struct Ov007OamNode {
    int x;       /* 0x00: Q12 screen x */
    int y;       /* 0x04: Q12 screen y */
    int visible; /* 0x08: func_ov007_020c0b78 draws this node and its children only when set */
    char pad_0c[8];
    unsigned char priority;  /* 0x14: OAM priority, used when the caller passes none (> 3) */
    signed char affineIndex; /* 0x15: OAM affine matrix, -1 = none */
} Ov007OamNode;

/* A func_ov007_020c40d4 record: its first word is its node (as
 * func_ov007_020c3f00 and func_ov007_020c3fe4 read it). */
typedef struct Ov007SpriteItem {
    Ov007OamNode *node; /* 0x00 */
} Ov007SpriteItem;

/* The 0x18-byte sprite group func_ov007_020c3f00 builds; names as there.
 * +0x0c (the extra record func_ov007_020c40d4 builds) stays raw on ctx. */
typedef struct Ov007SpriteGroup {
    int *layout;             /* 0x00: [0] is the item count */
    Ov007OamNode *root;      /* 0x04: the items' parent */
    Ov007SpriteItem **items; /* 0x08: layout[0] records */
} Ov007SpriteGroup;

/* One 0xc-byte particle tracking record of the kind func_0204dab4 fills (as
 * dPa_c's edStarKiraCallback_c::trackingRecords). func_0204dab4 claims a free
 * record for each particle of the system, tagging it with its mask argument
 * (only when that is < 4), and calls the callback, here
 * func_ov007_020be7a8, which writes the particle's screen point. */
typedef struct TrackingRecord {
    short screenX; /* 0x00: func_ov007_020be7a8's first output, in pixels */
    short screenY; /* 0x02: its second output */
    /* 0x04: the callback's 0xfff, scaled down by the particle's age over its
     * lifetime (func_0204dab4); this file turns it into an affine index */
    short lifeScale;
    /* 0x06 bits 0-1: the mask the record was claimed with; this file passes
     * an OAM priority and copies it back into the node */
    unsigned char priority : 2;
    /* 0x06 bits 2-7: bit 2 is set while func_0204dab4 sees the particle */
    unsigned char flags : 6;
    unsigned char pad_07;
    void *particle; /* 0x08: the tracked particle, 0 = free */
} TrackingRecord;

typedef char Ov007OamNode_affineIndex_must_be_0x15[(int)&((Ov007OamNode *)0)->affineIndex == 0x15 ? 1 : -1];
typedef char TrackingRecord_size_must_be_0xc[sizeof(TrackingRecord) == 0xc ? 1 : -1];

/* Moves each item's node onto the particle it tracks: func_0204dab4 updates
 * the tracking records (claiming new ones at the extra node's priority while
 * that node is visible), then every item shows while its record holds a
 * particle, at the record's screen point. ctx keeps the char * spelling of
 * the definition; `grp` is the typed view. */
void func_ov007_020be684(void *a0, char *ctx)
{
    Ov007SpriteGroup *grp = (Ov007SpriteGroup *)ctx;
    int i;
    int r3;
    Ov007OamNode *q;
    TrackingRecord *e;
    Ov007SpriteItem *o;

    q = **(Ov007OamNode ***)(ctx + 0xc);
    if (q->visible != 0)
        r3 = q->priority;
    else
        r3 = 4;
    r3 = r3 & 0xff;
    func_0204dab4(a0, (void*)data_ov007_02104bc0[1],
                  (void*)*grp->layout, r3, (void*)&func_ov007_020be7a8);

    for (i = 0; i < *grp->layout; i++) {
        o = grp->items[i];
        e = (TrackingRecord *)data_ov007_02104bc0[1] + i;
        o->node->visible = (e->particle != 0) ? 1 : 0;
        o->node->x = e->screenX << 12;
        o->node->y = e->screenY << 12;
        o->node->priority = e->priority;
        o->node->affineIndex = (e->lifeScale << 4) >> 0xc;
        if (e->particle != 0) func_ov007_020c3fe4(o);
    }
}
