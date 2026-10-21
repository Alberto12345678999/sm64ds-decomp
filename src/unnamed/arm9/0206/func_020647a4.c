/* File-local mirror of include/private/arm9_wbt.h's WBTPacketBitmap (same
 * names and offsets). */
typedef struct WBTPacketBitmap {
    int length;            /* 0x00 */
    int count;             /* 0x04 */
    int pad_08;            /* 0x08 */
    int current;           /* 0x0c */
    int recv_count;        /* 0x10 */
    unsigned int *bitmap;  /* 0x14 */
    unsigned char *buffer; /* 0x18 */
} WBTPacketBitmap;

/* Mark packet value received: count it, remember it as the latest, and set
 * its bit. func_02063ea8 calls it once func_02064674 has copied the packet
 * into the buffer. */
void func_020647a4(char *self, int value)
{
    WBTPacketBitmap *pkt_bmp = (WBTPacketBitmap *)self;
    pkt_bmp->recv_count += 1;
    pkt_bmp->current = value;

    pkt_bmp->bitmap[value >> 5] |= 1 << (value & 0x1f);
}
