//cpp
#include "Ov007Work.h"
#include "G2.h"
#include "GX.h"

extern "C" {

extern void *func_ov007_020b3f20(int n);
extern void *func_02054ea8(void);
extern int func_02054d88(void);
extern void func_ov007_020b8548(void *unused, int sheet, int baseTile, void *plane0, void *plane1,
                                int plane2, void *bank);
extern void func_ov007_020c32e8(char *c, int sel, unsigned int n, int off);
extern void func_ov007_020b3edc(int r0);
extern void func_02056014(const void *src, unsigned int offset, unsigned int count);
extern void func_ov007_020bcdb8(int idx);
extern void func_ov007_020c33d0(char *c, int sel, unsigned int off);
extern void func_ov007_020b850c(void);
extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* The 0xc-byte character record func_ov007_020c3550 allocates for
 * func_ov007_020c99d8; only the slot this file reads. */
typedef struct Ov007CharRecord {
    void *tiles; /* 0x00: the tile data after block 0's 0xc-byte header */
} Ov007CharRecord;

/* The manager's +0x74: the 0x48-byte 2D display record func_ov007_020b7594
 * allocates; palettes as in func_ov007_020ada70, only the slots this file
 * reads. */
typedef struct Ov007Display {
    char pad_00[0x24];
    /* 0x24: func_ov007_020b7320 allocates the table (count at +0x20),
     * func_ov007_020b6d40 fills it with four func_ov007_020c99d8 character
     * records; func_ov007_020c33d0 loads one into OBJ VRAM */
    Ov007CharRecord **characters;
    char pad_28[4];
    /* 0x2c: func_ov007_020b7320 allocates the table, func_ov007_020b6d40
     * fills it with func_ov007_020c9988 palettes */
    char **palettes;
} Ov007Display;

/* func_ov007_020b7138's second argument: dScDSMT_c's byte-packed
 * download-play table (data_0209b340); only the slot this file reads. */
typedef struct Ov007BootArgs {
    char pad_00[0x9c];
    /* 0x9c: dScDSMT_c::InitResources copies data_0209d6fc here, the
     * message file Message.cpp reads */
    void *messages;
} Ov007BootArgs;

/* The 0x3c-byte record func_ov007_020b6a84 allocates; names as in
 * func_ov007_020b4c04, only the slots this file reads. */
typedef struct Ov007Settings {
    Ov007BootArgs *bootArgs; /* 0x00 */
    char pad_04[0x36];
    unsigned char language; /* 0x3a: func_ov007_020b6a84 seeds it from the owner-info language */
} Ov007Settings;

typedef char Ov007Display_size_must_be_0x30[sizeof(Ov007Display) == 0x30 ? 1 : -1];

/* Loads screen set `idx`'s graphics: the message planes over the main and
 * sub BG1 (set 3 adds main BG3), its characters and palettes, and for set
 * 1 the OBJ sheet (files 0x2c/0x2d), the language's BG3 characters (file
 * 0x25 + language) and the BG palette (file 0x2b). */
void func_ov007_020bcba8(int idx) {
    Ov007Display *s;
    Ov007Work *g = WORK;
    s = g->display;

    switch (idx) {
    case 0:
        return;
    case 1: {
        void *sheet = func_ov007_020b3f20(0x25);
        void *mainBg1 = func_02054ea8();
        void *subBg1 = G2S::GetBG1CharPtr();
        void *messages = g->settings->bootArgs->messages;
        int langFile;
        func_ov007_020b8548(0, (int)sheet, 0, mainBg1, subBg1, 0, messages);

        GX::LoadOBJ(s->characters[1]->tiles, 0, 0x2000);
        func_ov007_020c32e8(s->palettes[1], 0, 0, 0);
        GX::LoadOBJ(func_ov007_020b3f20(0x2c), 0x2000, 0x2000);
        GX::LoadOBJPltt((char *)func_ov007_020b3f20(0x2d) + 0xc0, 0x1e0, 0x20);
        func_ov007_020b3edc(0x2c);
        func_ov007_020b3edc(0x2d);

        langFile = WORK->settings->language + 0x25;
        func_02056014(func_ov007_020b3f20(langFile), 0, 0x4000);
        GX::LoadBGPltt(func_ov007_020b3f20(0x2b), 0, 0x200);
        func_ov007_020b3edc(langFile);
        func_ov007_020b3edc(0x2b);

        func_ov007_020bcdb8(1);
        func_ov007_020c33d0((char *)s->characters[0], 8, 0);
        func_ov007_020c32e8(s->palettes[0], 3, 0, 0);
        func_ov007_020b850c();
    } break;
    case 3: {
        void *sheet = func_ov007_020b3f20(0x25);
        void *mainBg1 = func_02054ea8();
        void *subBg1 = G2S::GetBG1CharPtr();
        int mainBg3 = func_02054d88();
        void *messages = g->settings->bootArgs->messages;
        func_ov007_020b8548(0, (int)sheet, 0, mainBg1, subBg1, mainBg3, messages);

        func_ov007_020bcdb8(2);
        func_ov007_020c33d0((char *)s->characters[3], 9, 0);
        func_ov007_020c32e8(s->palettes[2], 3, 0, 0);
        func_ov007_020b850c();
    } break;
    case 2:
        break;
    }
}
}
