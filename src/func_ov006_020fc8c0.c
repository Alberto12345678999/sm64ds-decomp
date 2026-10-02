// @symbol func_ov006_020fc8c0
/* Bob-omb Squad (dScMgPachinko_c): draws the 30 balls. Each record is 0x38
 * bytes from 0x4660 in the scene (mBall[i]). A ball whose byte at +0x2d is set
 * is drawn with the sprite the byte at +0x33 picks, at its position plus the
 * offset at +0x10/+0x14, through a 2x2 rotate-and-scale matrix: the u16 at
 * +0x24 is the angle (>> 4 indexes the shared sine/cosine table) and the
 * 20.12 value at +0x20 is the scale.
 *
 * The fixed-point multiply is the NitroSDK FX_Mul shape, written as a local
 * inline, as the score drawer func_ov004_020b2220 does. With the products
 * written out in the body the compiler puts the scale in the first smull's
 * Rm instead of the table value.
 *
 * `opt_prelinearize off` is file-wide on purpose. Codegen is deferred to the
 * end of the file, so the setting in force there is the one that applies; a
 * push/pop bracket around the function would restore it before it is read.
 * With it on, every callee-saved register in the loop rotates by one place.
 *
 * Matched 2026-10-02 (mwccarm 2004/b56, --module ov006, 0x020fc8c0, 0xf0).
 * The earlier draft, from the near-miss database, sat at 6 of 60 words.
 */
typedef long long s64;
typedef short s16;

struct Matrix2x2 { int _00, _01, _10, _11; };

extern void func_ov004_020b023c(void *sprite, int x, int y, int a3, void *m);
extern s16 data_02082214[];
extern int data_ov006_02136cd4[];

#pragma opt_prelinearize off

static inline int FX_Mul(int v1, int v2)
{
    s64 t = (s64)v1 * v2;
    return (int)((t + 0x800) >> 12);
}

void func_ov006_020fc8c0(char *scene)
{
    int i;
    char *ball = scene;
    for (i = 0; i < 30; i++, ball += 0x38) {
        char *p = ball + 0x4000;
        if (*(unsigned char *)(p + 0x68d) != 0) {
            int idx = ((int)*(unsigned short *)(ball + 0x4684) >> 4) << 1;
            int scale = *(int *)(p + 0x680);
            int sprite = *(unsigned char *)(p + 0x693);
            struct Matrix2x2 m;
            int cosv = FX_Mul(data_02082214[idx + 1], scale);
            int sinv = FX_Mul(data_02082214[idx], scale);
            int x = (*(int *)(p + 0x660) + *(int *)(p + 0x670)) >> 12;
            int y = (*(int *)(p + 0x664) + *(int *)(p + 0x674)) >> 12;
            m._00 = cosv;
            m._01 = sinv;
            m._10 = -sinv;
            m._11 = cosv;
            func_ov004_020b023c((void *)data_ov006_02136cd4[sprite], x, y, -1, &m);
        }
    }
}
