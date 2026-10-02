// @symbol func_ov004_020b2220
/* recovered: minigame framework (dScMgBase_c block): draws a score number rotated by an angle through a 2x2 matrix and the sprite chain. */
/* Splits the value (clamped to 9999) into thousands, hundreds, tens and units, builds the
 * rotation-and-scale matrix from the sine table, and draws the digits centred on x: four
 * digits from x-0x30, three from x-0x20, two from x-0x10, a lone unit at x. The fixed-point
 * multiply and the 2x2 rotation are the NitroSDK FX_Mul / MTX_Rot22 shapes, written here as
 * file-local inlines. */
typedef unsigned short u16;
typedef long long s64;
typedef short s16;
struct M { int _00, _01, _10, _11; };
extern void func_ov004_020b1c68(void* a0, int a1, int a2, int a3, int a4, struct M* a5);
extern s16 data_02082214[];
extern int data_ov006_02137cd8[];

static inline int FX_Mul(int v1, int v2)
{
    s64 t = (s64)v1 * v2;
    return (int)((t + 0x800) >> 12);
}

static inline void MTX_Rot22(struct M *p, int sinVal, int cosVal)
{
    p->_00 = cosVal;
    p->_01 = sinVal;
    p->_10 = -sinVal;
    p->_11 = cosVal;
}

static inline s16 FX_SinIdx(int idx) { return data_02082214[idx << 1]; }
static inline s16 FX_CosIdx(int idx) { return data_02082214[(idx << 1) + 1]; }

#pragma opt_propagation off
void func_ov004_020b2220(int x, int y, int value, int a3, int a4, int scale, u16 angle)
{
    struct M m;
    int idx;
    int te, hu, th;

    if (value >= 9999) value = 9999;
    te = hu = th = 0;
    while (value >= 1000) { value -= 1000; th++; }
    while (value >= 100) { value -= 100; hu++; }
    while (value >= 10) { value -= 10; te++; }

    idx = angle >> 4;
    MTX_Rot22(&m, FX_Mul(FX_SinIdx(idx), scale), FX_Mul(FX_CosIdx(idx), scale));

    if (th != 0) {
        func_ov004_020b1c68((void *)data_ov006_02137cd8[th], x - 0x30, y, a3, a4, &m);
        func_ov004_020b1c68((void *)data_ov006_02137cd8[hu], x - 0x10, y, a3, a4, &m);
        func_ov004_020b1c68((void *)data_ov006_02137cd8[te], x + 0x10, y, a3, a4, &m);
        x += 0x30;
    } else if (hu != 0) {
        func_ov004_020b1c68((void *)data_ov006_02137cd8[hu], x - 0x20, y, a3, a4, &m);
        func_ov004_020b1c68((void *)data_ov006_02137cd8[te], x, y, a3, a4, &m);
        x += 0x20;
    } else if (te != 0) {
        func_ov004_020b1c68((void *)data_ov006_02137cd8[te], x - 0x10, y, a3, a4, &m);
        x += 0x10;
    }
    func_ov004_020b1c68((void *)data_ov006_02137cd8[value], x, y, a3, a4, &m);
}
