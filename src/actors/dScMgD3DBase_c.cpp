//cpp
/* Shared 3D minigame scene for Jump, Jump2, Trampoline and Trampoline2.
 * Production TU ov006/dScMgD3DBase_c: 27 functions in [0x020e6c28, 0x020e7660).
 * Keep definition order: 2004/b56 reverses ordinary function sections.
 * The inline destructor and BeforeInitResources key function preserve the
 * emitted vtable and D1/D0 order; see dScMgD3DBase_c.h for layout evidence.
 * Ten free helpers share this reconstructed TU; the original file boundary
 * remains an inference, recorded as medium confidence in the manifest. */

#include "dScMgD3DBase_c.h"
#include "decl_common.h"
#include "decl_Particle.h"
#include "types.h"

/* Local eight-byte OAM view for the sub-screen table builder.
 * OamAttr.h represents the same hardware entry with individual attributes;
 * this code retains its combined attr01 word stores. */
typedef struct Oam {
    u32 attr01;
    u16 attr2;
    u16 aff;
} Oam;

/* Local data views and ABI boundaries not yet represented by shared headers.
 * The manifest retains the resolved declaration-conflict history. */
extern "C" {

/* ov006's own data. */
extern void *data_ov006_02141a48;
extern void *data_ov006_02141a50;
extern Oam   data_ov006_02141a54[];
extern unsigned char data_ov006_0212e574[];

/* arm9 / ov004 globals with no project header. */
extern unsigned char data_0209d454;
extern unsigned char data_0209d45c;
extern unsigned char data_0209e660;
extern unsigned char data_0209f5f8;
extern void *data_0209d4a8;
extern unsigned int data_020a0db0;
extern int data_0208ee44;

/* arm9 / ov004 helpers with no project header. */
int   func_02053ea0(void);
int   func_02053eb0(void);
void  func_02054140(void);
void  func_02054154(void);
void  func_02054430(int);
void  func_02054748(int);
void  func_02056674(const void *src, unsigned int offset, unsigned int count);
int   func_020126e8(int a);
void  func_020126ac(int a0, int a1, int a2, int a3, int s0);
void  func_020127ec(int a0, int a1, int a2, int a3, int a4, int a5);
void *func_ov004_020adc68(int id);
void  func_ov004_020b0d30(void);
void  func_ov004_020b290c(void);
void  func_ov004_020b2980(void);
int   GetGameLanguage(void);
void  DecompressLZ16(void *src, void *dst);
/* The callee takes u16; narrowing the loaded file IDs grows Virtual7C
 * from 260 to 276 bytes. Keep this existing wide ABI boundary pending
 * reconstruction of the file-ID tables and their callers. */
u32   LoadCompressedFileAt(unsigned int fileID, void *target);
void  Ov004_Deallocate(void *x);
struct Camera;
void  Camera_UpdateMatrices(Camera *camera);

/* Retained wide-argument ABI bridges for the four saved-bank restores.
 * The native definitions take u16. Narrowing the saved s32 values adds 16
 * bytes each to Virtual7C and OnAimedAtWithEggReturnVec under 2004/b56.
 * Constant bank selections below use the actual namespace declarations. */
void  _ZN2GX15SetBankForSubBGEt(unsigned int x);
void  _ZN2GX16SetBankForSubOBJEt(unsigned int x);

/* Stage.h's tracker view lacks these ordinary methods. Its layout remains
 * shared with Stage; adding methods to that header is separate scoped work.
 * decl_Particle.h supplies the Initialise ABI declaration. */
void _ZN8Particle10SysTracker6UpdateEv(void *self);

/* This TU's own free helpers, forward-declared because they are called from
   members written above their definitions. */
void func_ov006_020e73c4(void);
void func_ov006_020e740c(void);
void func_ov006_020e7428(void);
void func_ov006_020e7508(void);
void func_ov006_020e759c(void);
void func_ov006_020e7110(void *self);
int  func_ov006_020e6da4(int a);

}

namespace GX {
void LoadOBJPltt(const void*, u32, u32);
void SetBankForBG(u16);
void SetBankForOBJ(u16);
void SetBankForSubBG(u16);
void SetBankForSubOBJ(u16);
void DisableAllBanks();
void SetBankForTex(u16);
void SetBankForTexPltt(u16);
void SetGraphicsMode(int, int, int);
}
namespace GXS { void LoadOBJPltt(const void*, u32, u32); void SetGraphicsMode(int); }
namespace G2S { u32 GetBG1CharPtr(); u32 GetBG1ScrPtr(); }
namespace CP15 { void FlushAndInvalidateDataCache(u32, u32); }
namespace Particle { void RenderAll(); }

// @symbol func_ov006_020e759c
extern "C" void func_ov006_020e759c(void) {
    *(volatile unsigned short *)0x4000304 |= 0x8000;
    func_02054140();
    GX::SetBankForSubBG(4);
    func_02054430(8);
    *(volatile unsigned int *)0x4000064 = 0x80330010;
    data_0209d454 &= ~0x10;
    data_0209d454 |= 4;
    *(volatile unsigned int *)0x4001000 =
        (*(volatile unsigned int *)0x4001000 & ~0x1f00) | (data_0209d454 << 8);
    *(volatile unsigned short *)0x400100c =
        (*(volatile unsigned short *)0x400100c & 0x43) | 0x4284;
    *(volatile unsigned short *)0x400100c &= ~3;
    *(volatile unsigned short *)0x400100c &= ~0x40;
}

// @symbol func_ov006_020e7508
extern "C" void func_ov006_020e7508(void)
{
    *(volatile unsigned short *)0x4000304 &= ~0x8000;
    func_02054154();
    GX::SetBankForSubOBJ(8);
    func_02054430(4);
    *(volatile int *)0x4000064 = 0x80360010;
    GXS::SetGraphicsMode(5);
    data_0209d454 |= 0x10;
    data_0209d454 &= ~4;
    *(volatile int *)0x4001000 = (*(volatile int *)0x4001000 & ~0x1f00) | (data_0209d454 << 8);
}

// @symbol func_ov006_020e7428
extern "C" void func_ov006_020e7428(void)
{
    int entry;
    int x;
    int y;
    int sprite;
    int tileY;
    int tileX;
    u32 displayControl;

    displayControl = *(volatile u32 *)0x4001000;
    *(volatile u32 *)0x4001000 = (displayControl & 0xffbfff9f) | 0x20;

    /* Keep the index round trips below: removing them grows this table
     * builder from 0xe0 to 0xe8 bytes under 2004/b56. */
    sprite = 0;
    for (entry = 0; entry < 0x80; entry++) {
        data_ov006_02141a54[entry].attr01 = 0;
        *(u32 *)&data_ov006_02141a54[(int)(((long long)entry))].attr2 = 0;
    }

    y = 0;
    tileY = 0;
    for (; y < 0xc0; y += 0x40) {
        x = 0;
        tileX = 0;
        for (; x < 0x100; x += 0x40) {
            data_ov006_02141a54[sprite].attr01 = ((y & 0xff) | 0xc0000c00) | ((x & 0x1ff) << 16);
            data_ov006_02141a54[sprite].attr2 = (u16)(((int)(((long long)tileX)) + ((int)(((long long)tileY)) << 5)) | 0xf000);
            tileX += 8;
            sprite++;
        }
        tileY += 8;
    }

    CP15::FlushAndInvalidateDataCache((u32)data_ov006_02141a54, 0x400);
    func_02056674(data_ov006_02141a54, 0, 0x400);
}

// @symbol func_ov006_020e740c
extern "C" void func_ov006_020e740c(void)
{
    func_02056674(data_ov006_02141a54, 0, 0x400u);
}

// @symbol func_ov006_020e73c4
extern "C" void func_ov006_020e73c4(void)
{
    func_02054154();
    func_02054140();
    GX::SetBankForSubOBJ(8);
    GX::SetBankForSubBG(4);
    *(unsigned int *)0x4001000 &= ~0x300010;
}

// @symbol _ZN14dScMgD3DBase_c9Virtual7CEv
/* Slot 31 prepares sub-screen BG/OBJ resources and restores their saved banks.
 * The actor Kill name does not establish this scene callback's meaning. */
int dScMgD3DBase_c::Virtual7C()
{
    unk_4660 = func_02053ea0();
    GX::SetBankForSubOBJ(0x100);
    LoadCompressedFileAt(data_ov006_0213c5fc[GetGameLanguage()], (void*)0x6600000);
    {
        char *dst = (char*)0x6600000; dst += 0x2000;
        DecompressLZ16((void*)data_ov006_0213c5e8[GetGameLanguage()], dst);
    }
    _ZN2GX16SetBankForSubOBJEt(unk_4660);
    unk_0a0 = func_02053eb0();
    GX::SetBankForSubBG(0x80);
    {
        volatile u16 *p = (volatile u16*)0x400100a;
        *p = (*p & 0x43) | 0x800;
        *p = *p & ~3;
        *p = *p & ~0x40;
    }
    SetSubBg1Offset(0, 0);
    data_0209d454 &= ~2;
    {
        s32 language = GetGameLanguage();
        LoadCompressedFileAt(data_ov006_0213c610[language], (void*)G2S::GetBG1CharPtr());
    }
    LoadCompressedFileAt(0x5b, (void*)G2S::GetBG1ScrPtr());
    _ZN2GX15SetBankForSubBGEt(unk_0a0);
}

// @symbol _ZN14dScMgD3DBase_c9Virtual84Ev
/* Slot 33 configures the 3D display and VRAM banks. Keep the loaded buffers
 * alive for later palette/menu work, and publish the two camera bases.
 * This override is shared by all four child minigames. */
void dScMgD3DBase_c::Virtual84()
{
    char *obj = (char *)this;

    void *p;

    *(vu32 *)0x4001000u |= 0x10000u;
    data_0209d45c = 0x10;
    data_0209d454 = 0x10;
    func_ov004_020b290c();
    func_ov004_020b2980();
    data_0209e660 = 1;
    GX::DisableAllBanks();
    GX::SetBankForTex(1);
    GX::SetBankForTexPltt(0x40);
    *(vu32 *)0x4000000u &= ~0x7000000u;
    *(vu32 *)0x4000000u &= ~0x38000000u;
    func_02054748(0);
    GX::SetBankForOBJ(0x10);
    GX::SetBankForBG(2);
    p = func_ov004_020adc68(data_ov006_0213c5fc[GetGameLanguage()]);
    data_ov006_02141a4c = p;
    {
        char *dst = (char *)0x6400000;
        dst += 0x4000;
        DecompressLZ16(p, dst);
    }
    p = func_ov004_020adc68(0xc3);
    data_ov006_02141a48 = p;
    GX::LoadOBJPltt(p, 0x100u, 0x100u);
    GXS::LoadOBJPltt(data_ov006_02141a48, 0x100u, 0x100u);
    InitialiseVramGlobals();
    func_ov004_020b0d30();
    func_ov006_020e7428();
    data_0208ee44 = 1;
    GX::SetGraphicsMode(1, 0, 1);
    GXS::SetGraphicsMode(5);
    *(vu32 *)0x4000000u &= 0xffcfffefu;
    data_ov006_02141a44 = (int)(obj + 0x466c);
    data_ov006_02141a40 = obj + 0x466c;
    data_ov006_02141a50 = obj + 0x4728;
    data_ov004_020beb74[1] = (int)obj;
    data_0209d4a8 = (void *)data_ov004_020beb74;
}

// @symbol func_ov006_020e7110
/* Clear sub-screen BG1 ownership. The cleanup caller passes this;
 * the helper ignores it and reloads r0 from its literal pool. */
extern "C" void func_ov006_020e7110(void *) { data_0209e660 = 0; }

// @symbol _ZN14dScMgD3DBase_c19BeforeInitResourcesEv
/* THIS IS THE TU'S KEY FUNCTION -- the first DECLARED non-inline virtual of
   dScMgD3DBase_c (the destructor is declared before it but is defined inline
   in the class body, so it cannot be the key function).  Defining it here is
   what makes mwcc emit _ZTV14dScMgD3DBase_c, the class's _ZTI/_ZTS and its
   four ancestors', and -- through vtable slots 16 and 17 -- the out-of-line
   D1/D0 pair at the bottom of the ROM range.  See the closing comment. */
bool dScMgD3DBase_c::BeforeInitResources()
{
    if (dScMgBase_c::BeforeInitResources() == 0) return 0;
    unk_5000 = 0;
    return 1;
}

// @symbol _ZN14dScMgD3DBase_c18AfterInitResourcesEj
void dScMgD3DBase_c::AfterInitResources(unsigned int vfSuccess)
{
    dScMgBase_c::AfterInitResources(vfSuccess);
    _ZN8Particle10SysTracker10InitialiseEv(&mSysTracker);
}

// @symbol _ZN14dScMgD3DBase_c14BeforeBehaviorEv
int dScMgD3DBase_c::BeforeBehavior()
{
    if (dScMgBase_c::BeforeBehavior() == 0) return 0;
    if (data_020a0db0 & 1)
        _ZN8Particle10SysTracker6UpdateEv(&mSysTracker);
    return 1;
}

// @symbol _ZN14dScMgD3DBase_c12BeforeRenderEv
int dScMgD3DBase_c::BeforeRender()
{
    if (dScMgBase_c::BeforeRender() == 0) {
        return 0;
    }

    Particle::RenderAll();
    return 1;
}

// @symbol _ZN14dScMgD3DBase_c11AfterRenderEj
void dScMgD3DBase_c::AfterRender(unsigned int arg)
{
    volatile unsigned short *reg = (volatile unsigned short *)0x04000006;
    int v = *reg;

    if (v > 0xb9 && v <= 0xc0) {
        while ((int)*reg < 0xc0) {
        }
    }

    dScene_c::AfterRender(arg);
}

// @symbol _ZN14dScMgD3DBase_c21AfterCleanupResourcesEj
void dScMgD3DBase_c::AfterCleanupResources(unsigned int vfSuccess)
{
    int result = (int)vfSuccess;

    if (result == 2) {
        CleanCommonModelDataArr();
        *(int*)0x40004c8 = 0x296a5800;
        *(int*)0x40004cc = 0x7fff;
        *(int*)0x40004c8 = 0x696a5800;
        *(int*)0x40004cc = 0x40007fff;
        func_ov006_020e7110(this);
        Ov004_Deallocate(data_ov006_02141a4c);
        Ov004_Deallocate(data_ov006_02141a48);
    }
    data_0209f5f8 = 0;
    dScMgBase_c::AfterCleanupResources(result);
}

// @symbol _ZN14dScMgD3DBase_c8OnKickedEv
/* Slot 24 is inherited by Jump and Jump2; it switches the active camera.
 * The two 0xbc-byte camera records remain explicit byte-offset views. */
int dScMgD3DBase_c::OnKicked()
{
    char *self = (char *)this;

    if (dScMgBase_c::OnKicked() == 0) return 0;
    if (mMenuOpen == 0) {
        if (data_0209d464 == 0) return 0;
        if (unk_4664 == 0)
            unk_4664 = 1;
        else
            unk_4664 = 0;
        int cameraAddress = (int)(self + 0x466c + unk_4664 * 0xbc);
        data_ov006_02141a44 = cameraAddress;
        Camera_UpdateMatrices((Camera *)cameraAddress);
        if (unk_4664 == 1) {
            func_ov006_020e7508();
        } else {
            func_ov006_020e759c();
            if (data_0209f5f8 == 0) {
                *(int*)0x4001000 &= ~0xe000;
                data_0209f5f8 = 1;
            }
        }
    }
    return 1;
}

// @symbol _ZN14dScMgD3DBase_c8OnPushedEv
/* Slot 25 forwards to the common minigame scene and normalizes its result. */
int dScMgD3DBase_c::OnPushed()
{
    return dScMgBase_c::OnPushed() != 0;
}

// @symbol _ZN14dScMgD3DBase_c24OnHitByCannonBlastedCharEv
/* Slot 26 identifies this branch of minigame scenes with the value 2. */
int dScMgD3DBase_c::OnHitByCannonBlastedChar()
{
    return 2;
}

// @symbol func_ov006_020e6e3c
/* Thunk: func_02012718(a, b + 0x80000).  decl_common.h types func_02012718 as
   returning void, so the forwarded r0 falls out of the tail call rather than
   being spelled as a `return` -- the same instruction either way. */
extern "C" int func_ov006_020e6e3c(int a, int b)
{
    func_02012718(a, b + 0x80000);
}

// @symbol Sound_PlayBank1Panned
extern "C" void Sound_PlayBank1Panned(int a0, char *a1, void *a2) {
    a1 += data_ov006_0212e574[a0];
    int r = func_ov006_020e6da4((int)a2);
    func_020127ec(1, (int)a1, 4, 0, 0, r);
}

// @symbol func_ov006_020e6db4
extern "C" void func_ov006_020e6db4(int a0, int a1, int a2) {
    int s0 = func_020126e8(a1 + 0x80000);
    func_020126ac(a0, 6, 0, a2, s0);
}

// @symbol func_ov006_020e6da4
/* Thunk: func_020126e8(a + 0x80000). */
extern "C" int func_ov006_020e6da4(int a)
{
    return func_020126e8(a + 0x80000);
}

// @symbol _ZN14dScMgD3DBase_c15OnHitByMegaCharEv
/* Slot 27 forwards across overlays. Its twelve-byte ROM body is a
 * long-branch veneer; the scene behavior belongs to the common base. */
void dScMgD3DBase_c::OnHitByMegaChar()
{
    dScMgBase_c::OnHitByMegaChar();
}

// @symbol _ZN14dScMgD3DBase_c19OnHitFromUnderneathEv
/* Slot 28 forwards the existing base contract. The inherited int return
 * is provisional; no meaningful return value is established by this wrapper. */
int dScMgD3DBase_c::OnHitFromUnderneath()
{
    return dScMgBase_c::OnHitFromUnderneath();
}

// @symbol _ZN14dScMgD3DBase_c16OnAimedAtWithEggEv
/* Slot 29 claims the sub-screen banks before delegating menu setup.
 * Its actor-style name and inherited int return remain provisional. */
int dScMgD3DBase_c::OnAimedAtWithEgg()
{
    func_ov006_020e73c4();
    GXS::LoadOBJPltt(data_ov006_02141a48, 0x100, 0x100);
    data_0209e660 = 0;
    unk_0a0 = func_02053eb0();
    GX::SetBankForSubBG(0x80);
    unk_4660 = func_02053ea0();
    GX::SetBankForSubOBJ(0x100);
    return dScMgBase_c::OnAimedAtWithEgg();
}

// @symbol _ZN14dScMgD3DBase_c25OnAimedAtWithEggReturnVecEv
/* Slot 30 restores sub-screen banks around the common menu teardown. */
void dScMgD3DBase_c::OnAimedAtWithEggReturnVec()
{
    _ZN2GX15SetBankForSubBGEt(unk_0a0);
    _ZN2GX16SetBankForSubOBJEt(unk_4660);
    data_0209e660 = 1;
    func_ov006_020e740c();
    dScMgBase_c::OnAimedAtWithEggReturnVec();
    if (unk_4664 == 1) {
        func_ov006_020e7508();
    } else {
        func_ov006_020e759c();
        if (data_0209f5f8 == 0) data_0209f5f8 = 1;
    }
}

/* The inline class destructor lets this TU's key function emit D1/D0 in
 * cartridge order without adding a standalone D2. All four child scenes
 * inline this base teardown, including mSysTracker destruction. */
