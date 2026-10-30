//cpp
#include "GX.h"
#include "Ov007Work.h"
#include "Ov007Settings.h"

extern "C" {

extern void func_ov007_020c33d0(char *c, int target, unsigned int offset);
extern void func_ov007_020c32e8(char *c, int target, unsigned int row, int skip);
extern void *func_ov007_020b3f20(int idx);
extern int func_ov007_020c99d8(int x);
extern void func_ov007_020c3544(void *p);
extern void func_ov007_020b3edc(int idx);
extern char *data_ov007_0210342c;

/* The 0xc-byte character record func_ov007_020c3550 builds; only the slot
 * this file reads. */
typedef struct Ov007CharRecord {
    const void *tiles; /* 0x00 */
} Ov007CharRecord;

/* The manager's +0x74: the 0x48-byte 2D display record func_ov007_020b7594
 * allocates; names as there, only the tables read here. */
struct Ov007Display {
    char pad_00[0x24];
    /* 0x24: four func_ov007_020c99d8 character records */
    Ov007CharRecord **characters;
    char pad_28[4];
    char **palettes; /* 0x2c: six func_ov007_020c9988 palettes */
};

typedef char Ov007Work_display_must_be_at_0x74[(int)&((Ov007Work *)0)->display == 0x74 ? 1 : -1];

/* The extern keeps the tree's char * spelling; the typed view is reached
 * through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* Loads character record idx into the sub engine's OBJ characters and
 * palette 1 into its OBJ palette. For language 2 and up it also builds a
 * character record from file slot idx + 0x17 + 2 * (language - 2)
 * (func_ov007_020b3f20), loads it to the sub OBJ as well, copies its first
 * 0x2000 bytes to the main OBJ characters, then frees the record and
 * releases the slot. */
void func_ov007_020bcdb8(int idx) {
    Ov007Display *s = WORK->display;
    func_ov007_020c33d0((char *)s->characters[idx], 5, 0);
    func_ov007_020c32e8(s->palettes[1], 2, 0, 0);

    int k = WORK->settings->language - 2;
    if (k < 0)
        return;

    int slot = idx + 0x17 + (k << 1);
    Ov007CharRecord *rec = (Ov007CharRecord *)func_ov007_020c99d8((int)func_ov007_020b3f20(slot));
    func_ov007_020c33d0((char *)rec, 5, 0);
    GX::LoadOBJ(rec->tiles, 0, 0x2000);
    func_ov007_020c3544(rec);
    func_ov007_020b3edc(slot);
}
}
