#include "types.h"
/* func_ov075_02117fe4 @ 0x02117fe4 (ov075, size 0x264)
 * A dScEntry_c step render (its address sits in two of the scene's step
 * sets, whose other entries are dScEntry_c members); an older banner called
 * it a dMeter_c counter. Renders each joined player's two-digit count (the
 * shared base at data_0209ee90+0x1d4 plus that player's data_0209b2ec, mod
 * 100) as tens/ones OAM digits, then every 3 calls toggles a blink flag and
 * has func_ov075_02116128 repaint each flagged player's slot border
 * bright or dim by it.
 */
extern u8 data_0209fc50;
extern u8 data_0209b2ec[];
extern u8 data_0209b2f0[];
extern char data_0209ee90[];
extern char data_ov075_0211c8b0[];

extern int func_02030958(int idx);
struct OamAttr;
extern struct OamAttr *_ZN3OAM6RenderEbP7OamAttriiiiii(bool a, void *attr, int x, int y, int c4,
                                                       int c5, int c6, int c7);
extern void func_ov075_02116128(char *c, int idx, int flag);

/* C view of include/dScEntry_c.h's dScEntry_c (a C++ class this C file
 * cannot include), with the header's names; only the field this file
 * uses. Here mStepWork[0] counts frames and mStepWork[1] is the blink
 * flag it toggles every third one. */
typedef struct dScEntry_c {
    u8 pad_000[0x268];
    s32 mStepWork[4]; /* 0x268 */
    u8 pad_278[0x10];
} dScEntry_c;

typedef char dScEntry_c_size_must_be_0x288[sizeof(dScEntry_c) == 0x288 ? 1 : -1];

void func_ov075_02117fe4(char *c)
{
    dScEntry_c *scene = (dScEntry_c *)c;
    int count = data_0209fc50;
    int d = 4 - count;
    int yBase = d * 16 + 0x30;
    int stride = d * 8 + 0x28;
    int n, tens;
    int i = 0;

    if (count > 0) {
        int sz = 0x1000;
        int xTens = 0xce;
        int eight = 8;
        int yOff = i;
        int zT = 0;
        int zO = 0;
        int minus1 = -1;
        int xOnes = 0xd8;

        do {
            int *p;

            n = *(int *)(data_0209ee90 + 0x1d4) + data_0209b2ec[func_02030958(i)];
            n = n % 100;
            tens = n / 10;
            if (tens != 0) {
                p = (int *)_ZN3OAM6RenderEbP7OamAttriiiiii(zT, data_ov075_0211c8b0, xTens,
                                                            yBase + yOff, eight, minus1, sz, zT);
                if (p != 0) {
                    int *q = (int *)(int)(p + 1);
                    int val = *q;
                    *q = (val & ~0x3ff) | ((tens + ((u32)(val << 22) >> 22)) & 0x3ff);
                }
            }
            p = (int *)_ZN3OAM6RenderEbP7OamAttriiiiii(zO, data_ov075_0211c8b0, xOnes,
                                                        yBase + yOff, eight, minus1, sz, zO);
            if (p != 0) {
                int *q = (int *)(int)(p + 1);
                int val = *q;
                *q = (val & ~0x3ff) | ((((u32)(val << 22) >> 22) + n % 10) & 0x3ff);
            }
        } while (yOff += stride, ++i < count);
    }

    scene->mStepWork[0]++;
    if (scene->mStepWork[0] < 3)
        return;

    scene->mStepWork[0] = 0;
    scene->mStepWork[1] ^= 1;

    if (count <= 0)
        return;

    {
        int j = 0;
        do {
            if (data_0209b2f0[func_02030958(j)] != 0)
                func_ov075_02116128(c, j, scene->mStepWork[1]);
            j++;
        } while (j < count);
    }
}
