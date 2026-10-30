/* The touch-panel work block at data_020a80cc, 0x38 bytes: the next symbol row
   is data_020a8104, exactly 0x38 past the start, and func_0205edd8.cpp's own
   view of the same object ends at its volatile u16 pair at +0x34/+0x36.

   The six calibration words at +0x18 carried their own symbol row,
   data_020a80e4, although they are this object's member: this function is
   their only reader, and it reads the +0x30 calibrated flag out of the same
   object in the line above. One object, two rows.

   The arithmetic is the SDK's calibrated-point transform: for each axis,
   (coeff * ((raw << 2) - origin)) >> 22, clamped to the screen. */
struct TPWork {
    char pad_00[0x18];
    int calib[6];              /* 0x18 -- {x origin, ?, x coeff, y origin, ?, y coeff} */
    unsigned short calibrated; /* 0x30 -- zero until the panel is calibrated */
    unsigned short pad_32;
    volatile unsigned short f34;
    volatile unsigned short f36;
};
extern struct TPWork data_020a80cc;

struct V4 { unsigned short a, b, c, d; };

void func_0205ea28(struct V4 *r0, struct V4 *r1)
{
    int *p;
    int t;
    if (data_020a80cc.calibrated == 0) {
        *r0 = *r1;
        return;
    }
    p = data_020a80cc.calib;
    r0->c = r1->c;
    r0->d = r1->d;
    if (r1->c == 0) {
        r0->a = 0;
        r0->b = 0;
        return;
    }
    r0->a = (int)(((long long)p[2] * ((long long)(r1->a << 2) - (long long)p[0])) >> 22);
    t = (short)r0->a;
    if (t < 0) { r0->a = 0; }
    else if (t > 0xff) { r0->a = 0xff; }
    r0->b = (int)(((long long)p[5] * ((long long)(r1->b << 2) - (long long)p[3])) >> 22);
    t = (short)r0->b;
    if (t < 0) { r0->b = 0; return; }
    if (t > 0xbf) { r0->b = 0xbf; }
}
