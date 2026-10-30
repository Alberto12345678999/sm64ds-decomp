/* NitroSDK geometry-engine command ports. */
#define reg_G3_TEXCOORD   (*(volatile int *)0x04000488)
#define reg_G3_VTX_10     (*(volatile int *)0x04000490)
#define reg_G3_BEGIN_VTXS (*(volatile int *)0x04000500)
#define reg_G3_END_VTXS   (*(volatile int *)0x04000504)

/* A VTX_10 vertex: three 10-bit 4.6 coordinates; 0x40 is +1.0, 0x3c0 -1.0. */
#define VTX10(x, y, z) ((x) | ((y) << 10) | ((z) << 20))
#define ONE  0x40
#define MONE 0x3c0

/* Draw the unit quad in the XY plane (z = 0), with the texture repeated
 * 2^tileS by 2^tileT times. The particle draws pick it or func_0204c194 out of
 * data_02099fb4 by the definition's polygon reference plane; pret's SPL names
 * it SPLUtil_DrawXYPlane (that revision adds an offset). */
void func_0204c24c(int tileS, int tileT) {
    tileS = 0x1000 << tileS;
    tileT = 0x1000 << tileT;

    reg_G3_BEGIN_VTXS = 1; /* GX_BEGIN_QUADS */
    reg_G3_TEXCOORD = 0;
    reg_G3_VTX_10 = VTX10(MONE, ONE, 0);
    reg_G3_TEXCOORD = (unsigned short)((int)(tileS << 8) >> 0x10);
    reg_G3_VTX_10 = VTX10(ONE, ONE, 0);
    reg_G3_TEXCOORD = (unsigned short)((int)(tileS << 8) >> 0x10) |
                      ((unsigned short)((int)(tileT << 8) >> 0x10) << 0x10);
    reg_G3_VTX_10 = VTX10(ONE, MONE, 0);
    reg_G3_TEXCOORD = (unsigned short)((int)(tileT << 8) >> 0x10) << 0x10;
    reg_G3_VTX_10 = VTX10(MONE, MONE, 0);
    reg_G3_END_VTXS = 0;
}
