/* The 0x2c-byte texture record func_ov007_020c162c allocates and fills
 * from a BMD texture/palette pair (func_ov007_020b2308). */
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

typedef char
    Ov007Texture_color_count_at_0x28[(int)&((Ov007Texture *)0)->plttColorCount == 0x28 ? 1 : -1];

void func_ov007_020c15ec(char *p)
{
    Ov007Texture *tex = (Ov007Texture *)p;
    tex->flags = 0;
    tex->fmt = 0;
    tex->texSrc = 0;
    tex->sizeS = 0;
    tex->sizeT = 0;
    tex->texSize = 0;
    tex->texAddr = 0;
    tex->plttSrc = 0;
    tex->plttColorCount = 0;
    tex->plttSize = 0;
    tex->plttAddr = 0;
}
