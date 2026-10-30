/* The 8-byte palette record: colour data and how many colours it holds, as
 * func_ov007_020c9988 reads them from a palette file and
 * func_ov007_020c32e8 loads them into palette RAM. */
typedef struct Ov007Palette {
    const void *colors; /* 0x00 */
    short colorCount;   /* 0x04 */
    char reserved;      /* 0x06: cleared here; nothing in ov007 reads it */
} Ov007Palette;

extern int func_ov007_020c3df4(int heapName, void *size);

/* Allocates a palette record (the menu's alloc hook) and fills it. */
void *func_ov007_020c3398(const void *colors, int colorCount) {
    Ov007Palette *pal = (Ov007Palette *)func_ov007_020c3df4(0, (void *)sizeof(Ov007Palette));
    pal->colors = colors;
    pal->colorCount = colorCount;
    pal->reserved = 0;
    return pal;
}
