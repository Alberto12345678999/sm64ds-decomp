#include "Ov007Transition.h"

/* Eases the mosaic size from fx.mosaic.from to fx.mosaic.to by t (Q12),
 * each 4-bit axis separately, and writes it on the transition's screens:
 * the BG half of MOSAIC when any of planes 0..3 is set, the OBJ half for
 * plane bit 0x10. */
void func_ov007_020c8c88(Ov007Transition *tr, int t) {
    unsigned char from = tr->fx.mosaic.from;
    unsigned char to = tr->fx.mosaic.to;
    int loFrom = from & 0xf;
    unsigned int flags = tr->planes;
    int hiFrom = (int)(from & 0xf0) >> 4;
    int loTo = to & 0xf;
    int hiTo = (int)(to & 0xf0) >> 4;
    int lo, hi;

    if (t >= 0x1000) {
        lo = loTo;
    } else if (t <= 0) {
        lo = loFrom;
    } else {
        lo = (int)((((s64)(0x1000 - t) * (loFrom << 12) + (s64)t * (loTo << 12)) >> 12)) >> 12;
    }

    if (t >= 0x1000) {
        hi = hiTo;
    } else if (t <= 0) {
        hi = hiFrom;
    } else {
        hi = (int)((((s64)(0x1000 - t) * (hiFrom << 12) + (s64)t * (hiTo << 12)) >> 12)) >> 12;
    }

    if (tr->screens & 1) {
        (void)*(volatile unsigned short *)0x400004c;
        if ((flags & 1) || (flags & 2) || (flags & 4) || (flags & 8))
            *(volatile unsigned char *)0x400004c = (unsigned char)(lo | (hi << 4));
        if (flags & 0x10)
            *(volatile unsigned char *)0x400004d = (unsigned char)(lo | (hi << 4));
    }

    if (!(tr->screens & 2))
        return;

    if (flags & 0x10)
        *(volatile unsigned char *)0x400104d = (unsigned char)(lo | (hi << 4));

    if ((flags & 1) || (flags & 2) || (flags & 4) || (flags & 8))
        *(volatile unsigned char *)0x400104c = (unsigned char)(lo | (hi << 4));
}
