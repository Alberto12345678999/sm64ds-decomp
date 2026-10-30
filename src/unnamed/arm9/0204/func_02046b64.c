typedef struct Table Table;
extern int func_02046590(const Table *tbl, const char *name);

struct Elem46 {
    short result;
    char pad[2];
    const char *name;
    char pad2[0x1c - 8];
};
struct Obj46 {
    char pad[0x10];
    unsigned short count;
    char pad2[2];
    struct Elem46 *elems;
};

/* dExtAnmTexSRT_c::Prepare's body (see dExtAnmTexSRT_c.h): give each of
   the texture-SRT file's o->count 0x1c-byte entries the index of the BMD
   material its name names (func_02046590). */
void func_02046b64(const Table *tbl, struct Obj46 *o) {
    int i;
    for (i = 0; i < (int)o->count; i++) {
        struct Elem46 *e = &o->elems[i];
        e->result = (short)func_02046590(tbl, e->name);
    }
}
