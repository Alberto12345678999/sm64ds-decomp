/* The 0x14-byte point list this function builds; names as in
 * func_ov007_020c5fc8 and func_ov007_020c7560, which read it. */
typedef struct Ov007PointList {
    void **items;   /* 0x00: one func_ov007_020c844c follower per point */
    int count;      /* 0x04 */
    void **links;   /* 0x08: func_ov007_020c80a4 links; count - 1, or count when closed */
    int flags;      /* 0x0c: bit 0 makes its own points, bit 1 is closed */
    int springMode; /* 0x10: which spring step func_ov007_020c7560 runs */
} Ov007PointList;

extern void *func_ov007_020c3df4(int heap, int size);
extern void func_ov007_020c78b0(void *c);
extern void *func_ov007_020c844c(int p, int q);
extern void *func_ov007_020c80a4(void);

/* Builds a list of count points and the links between them. With flags bit
 * 0 it makes each point as a follower of mass pointMass (Q12); otherwise
 * the caller fills items in (func_ov007_020c73f0's column lists share the
 * row lists' points). */
Ov007PointList *func_ov007_020c798c(int springMode, int count, int pointMass, int flags) {
    int i;
    Ov007PointList *list;

    list = (Ov007PointList *)func_ov007_020c3df4(0, sizeof(Ov007PointList));
    func_ov007_020c78b0(list);
    list->springMode = springMode;
    list->count = count;
    list->flags = flags;
    list->items = (void **)func_ov007_020c3df4(0, list->count * 4);
    if (list->flags & 1) {
        for (i = 0; i < list->count; i++)
            list->items[i] = func_ov007_020c844c(0, pointMass);
    }
    if (count > 1) {
        int n;
        if (list->count <= 1)
            n = 0;
        else
            n = list->count - ((list->flags & 2) ? 0 : 1);
        list->links = (void **)func_ov007_020c3df4(0, n * 4);
        for (i = 0; i < n; i++)
            list->links[i] = func_ov007_020c80a4();
    }
    return list;
}
