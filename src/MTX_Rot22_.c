/* MTX_Rot22_ @ 0x020524e4 (arm9, Thumb): stores (cos, sin, -sin, cos) into
 * m[0..3]. Identified as the Nitro SDK's FX_mtx22.c MTX_Rot22_ from pret's
 * FX_mtx22.c, whose body is the same five instructions.
 * str r2,[r0]; str r1,[r0,#4]; negs r1,r1; str r1,[r0,#8]; str r2,[r0,#0xc]; bx lr
 */
#pragma thumb on
typedef int s32;

void MTX_Rot22_(s32 *m, s32 s, s32 c) {
    m[0] = c;
    m[1] = s;
    m[2] = -s;
    m[3] = c;
}
