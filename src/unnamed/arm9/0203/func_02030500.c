#include "types.h"
extern void func_02019028(void);
void DisableAllBanks(void);
void SetBankForBG(int);
void SetBankForOBJ(int);
void SetBankForSubBG(int);
void SetBankForSubOBJ(int);
/* local extern: C file cannot include GX.h. */
extern void SetGraphicsMode(int a, int b, int c);
extern void _ZN3GXS15SetGraphicsModeEi(int a);
extern s32 func_02030fa8(void);
extern void* func_02054ea8(void);
extern void* _ZN3G2S13GetBG1CharPtrEv(void);
extern void DecompressLZ16(const void* src, void* dst);
/* local extern: C file cannot include GX.h. */
extern void LoadBGPltt(const void *p, u32 a, u32 b);
extern void _ZN3GXS10LoadBGPlttEPKvjj(const void* p, u32 a, u32 b);
extern void* _ZN2G212GetBG1ScrPtrEv(void);
extern void* _ZN3G2S12GetBG1ScrPtrEv(void);
extern void SetBg1Offset(int a, int b);
extern void SetSubBg1Offset(int a, int b);

extern u8 data_0209d45c;
extern u8 data_0209d454;
extern void* data_020927b0[];
extern void* data_020927c4[];
extern void* data_020927d8[];
extern u8 data_0209440c;
extern u8 data_0209fc58;

void func_02030500(void)
{
    u32 tmp;
    void* p;

    data_0209d45c = 0;
    data_0209d454 = 0;
    *(volatile u32*)0x4000000 &= ~0x1f00;
    *(volatile u32*)0x4001000 &= ~0x1f00;

    func_02019028();
    DisableAllBanks();
    SetBankForBG(1);
    SetBankForOBJ(2);
    SetBankForSubBG(4);
    SetBankForSubOBJ(8);

    tmp = *(volatile u32*)0x4000000 & ~0x7000000;
    *(volatile u32*)0x4000000 = tmp;
    tmp = *(volatile u32*)0x4000000 & ~0x38000000;
    *(volatile u32*)0x4000000 = tmp;
    *(volatile u16*)0x4000304 |= 0x8000;
    *(volatile u16*)0x4000050 = 0;
    *(volatile u16*)0x4001050 = 0;
    tmp = *(volatile u32*)0x4000000 & ~0xe000;
    *(volatile u32*)0x4000000 = tmp;
    *(volatile u32*)0x4001000 &= ~0xe000;
    SetGraphicsMode(1, 0, 0);

    *(volatile u32*)0x4000000 &= 0xffcfffef;
    *(volatile u16*)0x400000a = (*(volatile u16*)0x400000a & 0x43) | 8;
    *(volatile u16*)0x400000a &= ~0x40;
    _ZN3GXS15SetGraphicsModeEi(0);

    *(volatile u32*)0x4001000 &= 0xffcfffef;
    *(volatile u16*)0x400100a = (*(volatile u16*)0x400100a & 0x43) | 8;
    *(volatile u16*)0x400100a &= ~0x40;

    DecompressLZ16(data_020927b0[func_02030fa8()], func_02054ea8());
    DecompressLZ16(data_020927b0[func_02030fa8()], _ZN3G2S13GetBG1CharPtrEv());

    LoadBGPltt(&data_0209440c, 0, 0x40);
    _ZN3GXS10LoadBGPlttEPKvjj(&data_0209440c, 0, 0x40);

    if (data_0209fc58 & 0x30) {
        p = data_020927d8[func_02030fa8()];
    } else {
        p = data_020927c4[func_02030fa8()];
    }
    DecompressLZ16(p, _ZN2G212GetBG1ScrPtrEv());
    DecompressLZ16(p, _ZN3G2S12GetBG1ScrPtrEv());

    *(volatile u16*)0x400000a &= ~3;
    *(volatile u16*)0x400100a &= ~3;
    SetBg1Offset(0, 0);
    SetSubBg1Offset(0, 0);

    data_0209d45c = 2;
    data_0209d454 = 2;
    *(volatile u32*)0x4000000 = (*(volatile u32*)0x4000000 & ~0x1f00) | 0x200;
    *(volatile u32*)0x4001000 = (*(volatile u32*)0x4001000 & ~0x1f00) | 0x200;
}
