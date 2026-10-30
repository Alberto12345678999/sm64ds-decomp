/* NitroSDK geometry-engine command ports. */
#define reg_G3_TEXCOORD   (*(volatile int *)0x04000488)
#define reg_G3_VTX_10     (*(volatile int *)0x04000490)
#define reg_G3_BEGIN_VTXS (*(volatile int *)0x04000500)
#define reg_G3_END_VTXS   (*(volatile int *)0x04000504)

/* A VTX_10 vertex: three 10-bit 4.6 coordinates; 0x40 is +1.0, 0x3c0 -1.0. */
#define VTX10(x, y, z) ((x) | ((y) << 10) | ((z) << 20))
#define ONE  0x40
#define MONE 0x3c0

/* Draw the unit quad in the XZ plane (y = 0), with the texture repeated
 * 2^tileS by 2^tileT times. The particle draws pick it or func_0204c24c out of
 * data_02099fb4 by the definition's polygon reference plane; pret's SPL names
 * it SPLUtil_DrawXZPlane (that revision adds an offset). */
void func_0204c194(int tileS, int tileT) {
    tileS = 0x1000 << tileS;
    tileT = 0x1000 << tileT;
    tileS = tileS << 8;
    tileT = tileT << 8;
    tileS = tileS >> 16;
    tileT = tileT >> 16;

    reg_G3_BEGIN_VTXS = 1; /* GX_BEGIN_QUADS */
    reg_G3_TEXCOORD = 0;
    reg_G3_VTX_10 = VTX10(MONE, 0, ONE);
    reg_G3_TEXCOORD = (unsigned short)tileS;
    reg_G3_VTX_10 = VTX10(ONE, 0, ONE);
    reg_G3_TEXCOORD = (unsigned short)tileS | ((unsigned short)tileT << 0x10);
    reg_G3_VTX_10 = VTX10(ONE, 0, MONE);
    reg_G3_TEXCOORD = (unsigned short)tileT << 0x10;
    reg_G3_VTX_10 = VTX10(MONE, 0, MONE);
    reg_G3_END_VTXS = 0;
}
