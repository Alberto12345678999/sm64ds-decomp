#include "types.h"
extern int func_0203da9c(void);
extern void* _ZN3G2S12GetBG3ScrPtrEv(void);
extern void* _ZN3G2S12GetBG0ScrPtrEv(void);
extern unsigned LoadCompressedFileAt(u16 fileID, void *target);
extern void func_02020820(void *dst, void *src, int a, int b, int c, int d);
extern void MultiStore_Int(int val, void *dst, int len);
extern void func_02033390(int a);
extern void func_020331fc(int a, int b, int c);
extern void func_02020304(void);

extern u8 data_0209b2f0[];
extern int data_ov075_0211ca64;
extern int data_ov075_0211ca6c;
extern int data_ov075_0211ca74;
extern int data_ov075_0211cc44;
extern int data_ov075_0211cc4c;
extern int data_ov075_0211cc54;
extern int data_ov075_0211cc5c;
extern u8 data_0209d454;

/* C view of include/dScEntry_c.h's dScEntry_c (a C++ class this C file
 * cannot include), with the header's names; only the fields used here.
 * Each mOamAnimations entry is a 0x2c-byte OamAnimation (OamAnimation.h). */
typedef struct OamAnimation {
    u8 pad_00[0x22];
    s8 palette; /* 0x22 */
    u8 pad_23[0x9];
} OamAnimation;

typedef struct dScEntry_c {
    u8 pad_000[0x1b4];
    OamAnimation mOamAnimations[4]; /* 0x1b4 */
    s32 mStepDelay;                 /* 0x264 */
    s32 mStepWork[4];               /* 0x268 */
    u8 pad_278[0x10];
} dScEntry_c;

typedef char dScEntry_c_size_must_be_0x288[sizeof(dScEntry_c) == 0x288 ? 1 : -1];

void func_ov075_021188b4(char *c)
{
    dScEntry_c *scene = (dScEntry_c *)c;
    int id;

    id = func_0203da9c();
    scene->mStepDelay = 0x258;
    scene->mStepWork[0] = 0;
    scene->mStepWork[1] = 0;

    if (data_0209b2f0[id] != 0) {
        LoadCompressedFileAt(0x8404, _ZN3G2S12GetBG3ScrPtrEv());
        func_02020820((char *)&scene->mOamAnimations[0], &data_ov075_0211ca64, 1, 1, 1, 1);
        func_02020820((char *)&scene->mOamAnimations[1], &data_ov075_0211ca6c, 1, 0, 0, 0);
        func_02020820((char *)&scene->mOamAnimations[2], &data_ov075_0211ca74, 1, 1, 1, 1);
    } else {
        LoadCompressedFileAt(0x8401, _ZN3G2S12GetBG3ScrPtrEv());
        func_02020820((char *)&scene->mOamAnimations[0], &data_ov075_0211cc44, 1, 1, 1, 1);
        func_02020820((char *)&scene->mOamAnimations[1], &data_ov075_0211cc4c, 1, 0, 0, 0);
        func_02020820((char *)&scene->mOamAnimations[2], &data_ov075_0211cc54, 1, 0, 0, 0);
        func_02020820((char *)&scene->mOamAnimations[3], &data_ov075_0211cc5c, 1, 0, 0, 0);
    }

    scene->mOamAnimations[0].palette = id + 0xa;
    scene->mOamAnimations[1].palette = id + 0xa;

    {
        void *bg0 = _ZN3G2S12GetBG0ScrPtrEv();
        volatile int zero = 0;
        MultiStore_Int(zero, bg0, 0x800);
    }

    func_02033390(0);

    func_020331fc(0x40, 0x20, func_0203da9c() << 24 >> 24);

    data_0209d454 |= 1;

    func_02020304();

    scene->mStepWork[3] = 0;
}
