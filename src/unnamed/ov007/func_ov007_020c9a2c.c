#include "Ov007BinFile.h"

#pragma opt_strength_reduction off
void func_ov007_020c9a2c(Ov007BinFile *f, int x) {
    Ov007BinFileHeader *base;
    int i;

    f->header = (Ov007BinFileHeader *)x;
    base = f->header;
    x += 0x10;
    for (i = 0; i < base->dataBlocks; i++) {
        Ov007BinBlockHeader *q;
        f->blocks[i] = (Ov007BinBlockHeader *)x;
        q = f->blocks[i];
        f->blockData[i] = (void *)(x + 8);
        x += q->size;
    }
}
