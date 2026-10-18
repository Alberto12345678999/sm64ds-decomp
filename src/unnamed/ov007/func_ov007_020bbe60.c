#include "types.h"
#include "nitro/fx/fx.h"
extern void func_ov007_020c6784(void *self, int count, const int *p2, const void *p3,
                                const void *p4, const int *const *p5, int mode);

/* Six portrait drawings, selected by a two-way selector and three-step cycle.
 * Plotting the byte coordinates produces Mario, Luigi and Yoshi portraits.
 * Names are reconstructed from that evidence, not recovered identifiers.
 * The projector uses these as screen X/Y inputs and negates Y; depth is separate.
 * The nested stroke arrays remain ROM imports; threshold units are unknown.
 */
static const int sPortraitStrokeCounts[6] = {30, 34, 36, 20, 32, 32};
extern const int data_ov007_020cf700[30];
extern const int data_ov007_020cfa70[34];
extern const int data_ov007_020cfb84[36];
extern const int data_ov007_020cef80[20];
extern const int data_ov007_020cf96c[32];
extern const int data_ov007_020cf8ec[32];
static const int *sPortraitStrokePointCounts[6] = {data_ov007_020cf700, data_ov007_020cfa70,
                                                   data_ov007_020cfb84, data_ov007_020cef80,
                                                   data_ov007_020cf96c, data_ov007_020cf8ec};
extern const unsigned char *const data_ov007_020d7ffc[30];
extern const unsigned char *const data_ov007_020d8464[34];
extern const unsigned char *const data_ov007_020d85fc[36];
extern const unsigned char *const data_ov007_020d7f0c[20];
extern const unsigned char *const data_ov007_020d82e4[32];
extern const unsigned char *const data_ov007_020d8164[32];
static const unsigned char *const *sPortraitStrokeXCoords[6] = {
    data_ov007_020d7ffc, data_ov007_020d8464, data_ov007_020d85fc,
    data_ov007_020d7f0c, data_ov007_020d82e4, data_ov007_020d8164};
extern const unsigned char *const data_ov007_020d8074[30];
extern const unsigned char *const data_ov007_020d84ec[34];
extern const unsigned char *const data_ov007_020d8690[36];
extern const unsigned char *const data_ov007_020d7f5c[20];
extern const unsigned char *const data_ov007_020d8364[32];
extern const unsigned char *const data_ov007_020d81e4[32];
static const unsigned char *const *sPortraitStrokeYCoords[6] = {
    data_ov007_020d8074, data_ov007_020d84ec, data_ov007_020d8690,
    data_ov007_020d7f5c, data_ov007_020d8364, data_ov007_020d81e4};
extern const int *const data_ov007_020d80ec[30];
extern const int *const data_ov007_020d8574[34];
extern const int *const data_ov007_020d8724[36];
extern const int *const data_ov007_020d7fac[20];
extern const int *const data_ov007_020d83e4[32];
extern const int *const data_ov007_020d8264[32];
static const int *const *sPortraitStrokeProgressThresholds[6] = {
    data_ov007_020d80ec, data_ov007_020d8574, data_ov007_020d8724,
    data_ov007_020d7fac, data_ov007_020d83e4, data_ov007_020d8264};

extern char *data_ov007_0210342c;
extern char *data_ov007_02104ba0;

void func_ov007_020bbe60(int idx) {
    int drawing = idx * 3 + *(u8 *)(data_ov007_0210342c + idx + 0xfc);
    func_ov007_020c6784(*(void **)data_ov007_02104ba0, sPortraitStrokeCounts[drawing],
                        sPortraitStrokePointCounts[drawing], sPortraitStrokeXCoords[drawing],
                        sPortraitStrokeYCoords[drawing], sPortraitStrokeProgressThresholds[drawing],
                        1);
    *(int *)(data_ov007_02104ba0 + 0x38) = 0x78;
    if (idx == 0 && *(u8 *)(data_ov007_0210342c + idx + 0xfc) == 2) {
        int *o = (int *)data_ov007_02104ba0;
        int mid = FX_MUL((o[0x38 / 4] << 12), 0x1800);
        o[0x38 / 4] = mid >> 12;
    }
    ((u8 *)(data_ov007_0210342c + 0xfc))[idx]++;
    {
        u8 *p = (u8 *)(data_ov007_0210342c + 0xfc);
        if (p[idx] >= 3)
            p[idx] = 0;
    }
}
