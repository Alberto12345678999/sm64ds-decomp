#include "types.h"
#include "Ov007StrokePath.h"

/* The 0xd0-byte touch picker this function builds. Names follow
 * func_ov007_020c5a6c's own struct and the readers cited per slot; only the
 * slots this file touches are spelled.
 *
 * Left raw, no reader found to name them: +0x18 (a5), +0x30 (cleared),
 * +0x40/+0x44 (per-group links func_ov007_020c6e68 appends after the
 * per-point ones), the four u16 arrays at +0x48..+0x54 (0xffff = unset) and
 * the Point at +0x94 that anchors `link`'s from end. Those stay on the char *
 * alias `o` of the allocation; the named slots go through `p`. */
typedef struct Ov007Picker {
    char pad_00[0xc];
    int maxGroups; /* 0x0c: a0; func_ov007_020c6550 stops committing at it */
    int maxPoints; /* 0x10: a1; func_ov007_020c65bc stops appending at it */
    char pad_14[8];
    /* 0x1c: a4; func_ov007_020c65bc reads its +8/+0xc/+0x10 point thresholds,
     * func_ov007_020c6e68 its +0x1c factor */
    void *params;
    Ov007StrokePath *path; /* 0x20: the stroke being drawn (func_ov007_020c2c68) */
    /* 0x24: a2 points; func_ov007_020c65bc unprojects each appended point
     * into it through `camera` */
    Vector3 *pathPoints;
    Vector3 **groupPoints;      /* 0x28: func_ov007_020c6e68, per group */
    Vector3 **groupPointCopies; /* 0x2c: func_ov007_020c6e68 copies groupPoints */
    char pad_30[4];
    /* 0x34: per group, one link per point from posPoint (func_ov007_020c6e68) */
    void ***groupLinks;
    Ov007StrokePath **groups; /* 0x38: committed strokes (func_ov007_020c6d20) */
    void **pointLists;        /* 0x3c: func_ov007_020c798c, per group */
    char pad_40[0x2c];
    void *posPoint; /* 0x6c: func_ov007_020c844c's Point over pos */
    Vector3 pos;    /* 0x70 */
    char pad_7c[0x1c];
    Vector3 anchorPos; /* 0x98: the +0x94 Point's position (func_ov007_020c5a6c) */
    void *link;   /* 0xa4: func_ov007_020c80a4; from +0x94 to posPoint */
    void *camera; /* 0xa8: a3; func_ov007_020c65bc unprojects through it */
} Ov007Picker;

extern void* func_ov007_020c3df4(int a, int size);
extern void func_ov007_020c684c(void* self);
extern void* func_ov007_020c844c(void* p, int q);
extern void* func_ov007_020c80a4(void);
extern void func_ov007_020c8010(void* self, void* a, void* b);
extern int func_ov007_020c2c68(int a, int b, int c);
extern void func_ov007_020c6724(void* self, int flag);

void* func_ov007_020c690c(int a0, int a1, int a2, int a3, int a4, int a5)
{
    char* o = (char*)func_ov007_020c3df4(0, 0xd0);
    Ov007Picker *p = (Ov007Picker *)o;
    int n4 = a0 << 2;
    int n2;
    int i;

    p->maxGroups = a0;
    p->maxPoints = a1;
    *(s32*)(o + 0x18) = a5;
    p->params = (void *)a4;
    p->camera = (void *)a3;

    p->groupPoints = (Vector3 **)func_ov007_020c3df4(0, n4);
    p->groupPointCopies = (Vector3 **)func_ov007_020c3df4(0, n4);
    *(s32*)(o + 0x30) = 0;
    p->groups = (Ov007StrokePath **)func_ov007_020c3df4(0, n4);
    p->pointLists = (void **)func_ov007_020c3df4(0, n4);

    n2 = a0 << 1;
    *(void**)(o + 0x48) = func_ov007_020c3df4(0, n2);
    *(void**)(o + 0x4c) = func_ov007_020c3df4(0, n2);
    *(void**)(o + 0x50) = func_ov007_020c3df4(0, n2);
    *(void**)(o + 0x54) = func_ov007_020c3df4(0, n2);

    p->groupLinks = (void ***)func_ov007_020c3df4(0, n4);
    *(void**)(o + 0x40) = func_ov007_020c3df4(0, n4);
    *(void**)(o + 0x44) = func_ov007_020c3df4(0, n4);

    func_ov007_020c684c(p);

    for (i = 0; i < a0; i++) {
        p->groups[i] = 0;
        ((u16*)*(void**)(o + 0x4c))[i] = 0xffff;
        ((u16*)*(void**)(o + 0x48))[i] = ((u16*)*(void**)(o + 0x4c))[i];
        ((u16*)*(void**)(o + 0x54))[i] = 0xffff;
        ((u16*)*(void**)(o + 0x50))[i] = ((u16*)*(void**)(o + 0x54))[i];
    }

    p->posPoint = func_ov007_020c844c(&p->pos, 0xa000);
    *(void **)(o + 0x94) = func_ov007_020c844c(&p->anchorPos, 0x1000);
    p->link = func_ov007_020c80a4();
    func_ov007_020c8010(p->link, *(void **)(o + 0x94), p->posPoint);

    p->path = (Ov007StrokePath *)func_ov007_020c2c68(0, a2, 1);
    p->pathPoints = (Vector3 *)func_ov007_020c3df4(0, a2 * 0xc);

    func_ov007_020c6724(p, 1);
    return p;
}
