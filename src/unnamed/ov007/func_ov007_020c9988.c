#include "Ov007Display.h"
#include "Ov007BinFile.h"

/* Block 0 of a palette file: two words whose product is the colour count
 * (what each one counts is not read anywhere), then the colours. */
typedef struct Ov007PaletteBlock {
    int dims[2]; /* 0x00 */
} Ov007PaletteBlock;

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
