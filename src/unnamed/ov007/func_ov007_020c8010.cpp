//cpp
extern "C" {

/* A point and a link between two points; names as in func_ov007_020c5a6c,
 * which reads the same records. */
struct Point {
    int *pos; /* 0x0: an x/y/z vector */
};

struct Link {
    Point *from; /* 0x0 */
    Point *to;   /* 0x4 */
    int length;  /* 0x8: LenVec3(dir) */
    int dir[3];  /* 0xc: from->pos - to->pos */
};

void SubVec3(void *, void *, void *);
int LenVec3(void *);

/* Links two points: once both have a position, dir is the vector between
 * them and length its length. r4 keeps the callers' char * spelling. */
void func_ov007_020c8010(char *r4, int *a, int *b) {
    Link *link = (Link *)r4;
    link->from = (Point *)a;
    link->to = (Point *)b;
    if (a[0] == 0)
        return;
    if (b[0] == 0)
        return;
    SubVec3(link->from->pos, link->to->pos, link->dir);
    link->length = LenVec3(link->dir);
}
}
