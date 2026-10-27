#include "types.h"
extern void func_ov075_02116028(int *p, int v);
extern int LoadFile(int handle);
extern void func_ov075_02116030(void *c, int v);
extern void *_ZN3G2S12GetBG3ScrPtrEv(void);
extern unsigned int LoadCompressedFileAt(u16 fileID, void *target);
extern void _ZN7Message17DisplayVsExitTextEt(u16 a);
extern void func_ov075_02115e8c(void *p, int b, int c, int d, int e);
extern void _ZN3G2x13SetBlendAlphaEPVtiiii(volatile void *p, int a, int b, int c, int d);
extern void func_02020190(void);
extern void func_02012790(int a);
extern void _ZN5Sound22LoadAndSetMusic_Layer1Ei(int a);

extern unsigned char data_0209d454;
extern int data_ov075_0211d71c;
extern unsigned char data_0209d45c;
extern int data_0209fc68;

/* C view of include/dScEntry_c.h's dScEntry_c (a C++ class this C file
 * cannot include), with the header's names; only the fields used here.
 * Each mIcons entry is a dScEntry_c::icon_c, a 0x24-byte dThIcon_c.
 * This step sets data_0209d45c bits 0xe and records them in
 * mDisconnectHideMask; on a player disconnect
 * dScEntry_c::HandlePlayerDisconnect clears data_0209d45c by
 * ~mDisconnectHideMask, and func_ov075_02117e84 clears both on its own. */
typedef struct dThIcon_c {
    u8 pad_00[0x24];
} dThIcon_c;

typedef struct dScEntry_c {
    u8 pad_000[0x70];
    dThIcon_c mIcons[9]; /* 0x070 */
    u8 pad_1b4[0xb4];
    s32 mStepWork[4]; /* 0x268 */
    u8 pad_278[8];
    u8 mIconCount;    /* 0x280 */
    u8 mSelectedIcon; /* 0x281 */
    u8 pad_282[5];
    u8 mDisconnectHideMask; /* 0x287 */
} dScEntry_c;

typedef char dScEntry_c_size_must_be_0x288[sizeof(dScEntry_c) == 0x288 ? 1 : -1];

void func_ov075_02118378(void *c) {
    dScEntry_c *scene = (dScEntry_c *)c;

    data_0209d454 &= ~5;
    func_ov075_02116028(&data_ov075_0211d71c, 1);
    func_ov075_02116030(&data_ov075_0211d71c, LoadFile(0x9801));
    LoadCompressedFileAt(0x8407, _ZN3G2S12GetBG3ScrPtrEv());
    _ZN7Message17DisplayVsExitTextEt(0x1f);

    data_0209d45c |= 0xe;
    data_0209d454 |= 5;
    scene->mSelectedIcon = 0;
    func_ov075_02115e8c(&scene->mIcons[0], 0xa, 0, 0x80, 0x48);
    func_ov075_02115e8c(&scene->mIcons[1], 0xa, 0, 0x80, 0x78);
    scene->mIconCount = 2;
    _ZN3G2x13SetBlendAlphaEPVtiiii((volatile void *)0x4000050, 4, 0x11, 0xc, 4);
    scene->mDisconnectHideMask = 0xe;
    if (data_0209fc68 != 0)
        data_0209fc68 = 5;
    func_02020190();
    scene->mStepWork[0] = 0;
    scene->mStepWork[1] = 0;
    func_02012790(0x125);
    _ZN5Sound22LoadAndSetMusic_Layer1Ei(0x4c);
}
