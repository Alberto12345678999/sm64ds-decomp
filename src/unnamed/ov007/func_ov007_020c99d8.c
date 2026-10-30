#include "Ov007Display.h"
#include "Ov007BinFile.h"

typedef enum { FALSE, TRUE } Bool;

/* Block 0 of a character file: a 0xc-byte header, then the tile data. Each
 * slot is read as a byte; func_ov007_020c3550 keeps them in the record
 * func_ov007_020c33d0 loads into VRAM. */
typedef struct Ov007CharBlock {
    unsigned char width; /* 0x00: in tiles (the record's +8) */
    char pad_01[3];
    unsigned char height; /* 0x04: in tiles (the record's +9) */
    char pad_05[3];
    /* 0x08: func_ov007_020c33d0 sizes each tile 0x40 bytes (8bpp) when set,
     * else 0x20 (4bpp) */
    unsigned char is8bpp;
    char pad_09[3];
} Ov007CharBlock;

typedef char Ov007CharBlock_size_must_be_0xc[sizeof(Ov007CharBlock) == 0xc ? 1 : -1];

extern Ov007CharRecord *func_ov007_020c3550(const void *tiles, int width, int height, int is8bpp);

/* Builds the character record for file x: its tiles follow block 0's header. */
Ov007CharRecord *func_ov007_020c99d8(int x) {
    Ov007BinFile buf;
    Ov007CharBlock *ip;
    unsigned char a;
    unsigned char b;
    unsigned char c;
    Bool d;

    if (x == 0) {
        return 0;
    }
    func_ov007_020c9a2c(&buf, x);
    ip = (Ov007CharBlock *)buf.blockData[0];
    a = ip->is8bpp;
    b = ip->width;
    c = ip->height;
    if (a == 0) {
        d = FALSE;
    } else {
        d = TRUE;
    }
    return func_ov007_020c3550(ip + 1, b, c, d);
}
