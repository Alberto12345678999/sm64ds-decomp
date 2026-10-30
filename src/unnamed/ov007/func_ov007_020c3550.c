/* The 0xc-byte character record: tile data and its size in tiles, as
 * func_ov007_020c99d8 reads them from a character file and
 * func_ov007_020c33d0 loads them into VRAM. */
typedef struct Ov007CharRecord {
    const void *tiles;      /* 0x00 */
    int is8bpp;             /* 0x04: 0x40-byte tiles when set, else 0x20 */
    unsigned char width;    /* 0x08: in tiles */
    unsigned char height;   /* 0x09 */
    unsigned char reserved; /* 0x0a: cleared here; nothing in ov007 reads it */
} Ov007CharRecord;

extern int func_ov007_020c3df4(int heapName, void *size);

/* Allocates a character record (the menu's alloc hook) and fills it. */
void *func_ov007_020c3550(const void *tiles, int width, int height, int is8bpp) {
    Ov007CharRecord *rec =
        (Ov007CharRecord *)func_ov007_020c3df4(0, (void *)sizeof(Ov007CharRecord));
    rec->tiles = tiles;
    rec->width = width;
    rec->height = height;
    rec->is8bpp = is8bpp;
    rec->reserved = 0;
    return rec;
}
