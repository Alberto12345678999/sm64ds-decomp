extern char* func_ov007_020c3df4(int a, int b);
extern void func_ov007_020c15ec(char* p);
extern void func_ov007_020c16dc(void* a, int b, int c, int d, void* e, void* f);

/* The 0x2c-byte texture record this function allocates and
 * func_ov007_020c15ec clears; names as in func_ov007_020c15ec (PR #4237). */
typedef struct Ov007Texture {
    /* 0x00: bit 0 = has texels (func_ov007_020c1560 loads them),
     * bit 1 = has a palette (func_ov007_020c14d4 loads it) */
    int flags;
    int fmt;      /* 0x04: BMD texture format; func_ov007_020c1448's name */
    int texSrc;   /* 0x08: texel data, func_ov007_020c1560 `src` */
    int texSize;  /* 0x0c: bytes, from func_ov007_020c16dc; func_ov007_020c1560 `size` */
    int texAddr;  /* 0x10: VRAM slot; func_ov007_020c1448's name */
    int sizeS;    /* 0x14: log2(width / 8); func_ov007_020c1448's name */
    int sizeT;    /* 0x18: log2(height / 8) */
    int plttSrc;  /* 0x1c: palette data, func_ov007_020c14d4 `src` */
    int plttSize; /* 0x20: bytes, colour count << 1 (func_ov007_020c16dc) */
    int plttAddr; /* 0x24: palette VRAM slot; func_ov007_020c1404 writes it to PLTT_BASE */
    /* 0x28: palette size / 2 (func_ov007_020b2308) */
    short plttColorCount;
} Ov007Texture;

typedef char Ov007Texture_size_must_be_0x2c[sizeof(Ov007Texture) == 0x2c ? 1 : -1];

/* Allocates and fills a texture record for texels of format fmt at texSrc,
 * (8 << sizeS) by (8 << sizeT), with an optional palette of plttColorCount
 * colours at plttSrc; func_ov007_020c16dc works out the texel and palette
 * byte sizes. The record keeps the void * spelling of the definition; `tex`
 * is the typed view. */
void *func_ov007_020c162c(void *fmt, int texSrc, int sizeS, int sizeT, int plttSrc,
                          unsigned short plttColorCount) {
    char* r6 = func_ov007_020c3df4(0, 0x2c);
    Ov007Texture *tex = (Ov007Texture *)r6;
    int width = 8 << sizeS;
    int height = 8 << sizeT;
    func_ov007_020c15ec(r6);
    tex->fmt = (int)fmt;
    tex->texSrc = texSrc;
    tex->sizeS = sizeS;
    tex->sizeT = sizeT;
    tex->plttSrc = plttSrc;
    tex->plttColorCount = plttColorCount;
    if (texSrc != 0)
        tex->flags |= 1;
    if (plttSrc != 0)
        tex->flags |= 2;
    func_ov007_020c16dc(fmt, width, height, plttColorCount, &tex->texSize, &tex->plttSize);
    return r6;
}
