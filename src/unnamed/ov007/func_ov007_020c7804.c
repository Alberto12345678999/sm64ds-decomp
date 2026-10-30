extern void func_ov007_020c8010(void *link, void *from, void *to);

/* The 0x14-byte point list func_ov007_020c798c builds; names as there. */
typedef struct Ov007PointList {
    void **items;   /* 0x00: the points */
    int count;      /* 0x04 */
    void **links;   /* 0x08: count - 1, or count when closed */
    int flags;      /* 0x0c: bit 1 is closed */
    int springMode; /* 0x10 */
} Ov007PointList;

/* Binds each link i to points i and i + 1 (the last wraps to point 0 when
 * the list is closed), for the four spring modes func_ov007_020c7560 runs. */
void func_ov007_020c7804(Ov007PointList *list) {
    int count = list->count;
    int n;
    int i;

    if (count <= 1) {
        n = 0;
    } else {
        n = count - !(list->flags & 2);
    }

    switch (list->springMode) {
    case 0:
    case 1:
    case 2:
    case 3:
        for (i = 0; i < n; i++) {
            int j;
            if (i < list->count - 1)
                j = i + 1;
            else
                j = 0;
            func_ov007_020c8010(list->links[i], list->items[i], list->items[j]);
        }
        break;
    default:
        break;
    }
}
