#include "Ov007Display.h"

/* The 0x84-byte block index func_ov007_020c9a2c fills; names as in
 * func_ov007_020c99d8, untyped here: only block 0's data is read. */
typedef struct Ov007BinFile {
    void *header;        /* 0x00 */
    void *blocks[16];    /* 0x04 */
    void *blockData[16]; /* 0x44 */
} Ov007BinFile;

/* Block 0 of a palette file: two words whose product is the colour count
 * (what each one counts is not read anywhere), then the colours. */
typedef struct Ov007PaletteBlock {
    int dims[2]; /* 0x00 */
} Ov007PaletteBlock;

typedef char Ov007BinFile_size_must_be_0x84[sizeof(Ov007BinFile) == 0x84 ? 1 : -1];

extern void func_ov007_020c9a2c(void *buf, int x);
extern Ov007Palette *func_ov007_020c3398(const void *colors, int colorCount);

/* Builds the palette record for file x: its colours follow block 0's
 * header. */
Ov007Palette *func_ov007_020c9988(int x) {
    Ov007BinFile buf;
    Ov007PaletteBlock *block;
    if (x == 0) {
        return 0;
    }
    func_ov007_020c9a2c(&buf, x);
    block = (Ov007PaletteBlock *)buf.blockData[0];
    return func_ov007_020c3398(block + 1, (unsigned short)(block->dims[0] * block->dims[1]));
}
