//cpp
#include "SharedFilePtr.h"

extern "C" {

/* Runtime asset handles resolved through the overlay 0 file table. */
enum sinit_ov030_02114924_AssetId {
    ASSET_MONKEY_BMD = 0x03aa,
    ASSET_MONKEY_HOLD_BCA = 0x03ab,
    ASSET_MONKEY_JUMP_ED_BCA = 0x03ac,
    ASSET_MONKEY_JUMP_ST_BCA = 0x03ad,
    ASSET_MONKEY_RUN_BCA = 0x03ae,
    ASSET_MONKEY_RUN_ED_BCA = 0x03af,
    ASSET_MONKEY_RUN_ST_BCA = 0x03b0,
    ASSET_MONKEY_WAIT1_BCA = 0x03b1,
    ASSET_MONKEY_WAIT2_BCA = 0x03b2,
    ASSET_MONKEY_WAIT3_BCA = 0x03b3,
    ASSET_MONKEY_WAIT4_BCA = 0x03b4
};

extern void *func_02017acc(void *, unsigned int);
extern void func_020731dc(void *, void *, void **);
extern int func_02017ab4(int);
extern int SharedFilePtr_Destruct_Anim(int);
/* local extern: C++ cannot take a destructor's address, so the registrations
   name ~Vector3() by its linker name. */
extern void *_ZN7Vector3D1Ev(void *object);

extern void* data_ov030_02115d00;
extern void* data_ov030_02115d28;
extern SharedFilePtr gMonkeyHoldAnimationFile;
extern void* data_ov030_02115d34;
extern SharedFilePtr gMonkeyJumpStAnimationFile;
extern void* data_ov030_02115d40;
extern SharedFilePtr gMonkeyJumpEdAnimationFile;
extern void* data_ov030_02115d64;
extern SharedFilePtr gMonkeyRunStAnimationFile;
extern void* data_ov030_02115d70;
extern SharedFilePtr gMonkeyRunAnimationFile;
extern void* data_ov030_02115d88;
extern SharedFilePtr gMonkeyRunEdAnimationFile;
extern void* data_ov030_02115d94;
extern SharedFilePtr data_ov030_02115cf0;
extern void* data_ov030_02115dac;
extern SharedFilePtr gMonkeyWait2AnimationFile;
extern void* data_ov030_02115db8;
extern SharedFilePtr gMonkeyWait3AnimationFile;
extern void* data_ov030_02115dc4;
extern SharedFilePtr gMonkeyWait4AnimationFile;
extern void* data_ov030_02115dd0;

/* Two words copied as a unit. Under C++ a struct of two scalar fields is
   assigned field by field, which reorders the loads; an array member keeps
   C's schedule. */
typedef struct {
    int w[2];
} S8;
typedef struct { S8 lo, hi; } S16;

extern S8 data_ov030_02115b68;
extern S8 data_ov030_02115b60;
extern S8 data_ov030_02115af0;
extern S8 data_ov030_02115b50;
extern S8 data_ov030_02115b00;
extern S8 data_ov030_02115b40;
extern S8 data_ov030_02115b48;
extern S8 data_ov030_02115b18;
extern S8 data_ov030_02115b10;
extern S8 data_ov030_02115ad8;
extern S8 data_ov030_02115b58;
extern S8 data_ov030_02115b20;
extern S8 data_ov030_02115ae0;
extern S8 data_ov030_02115b28;
extern S8 data_ov030_02115ae8;
extern S8 data_ov030_02115b30;
extern S8 data_ov030_02115ac8;
extern S8 data_ov030_02115ad0;
extern S8 data_ov030_02115b08;
extern S8 data_ov030_02115b70;
extern S8 data_ov030_02115af8;
extern S8 data_ov030_02115b38;

extern S16 data_ov030_02115e0c[11];

extern void* data_ov030_02115ddc;
extern void* data_ov030_02115d58;
extern void* data_ov030_02115de8;
extern void* data_ov030_02115d4c;
extern void* data_ov030_02115df4;
extern void* data_ov030_02115d7c;
extern void* data_ov030_02115e00;
extern void* data_ov030_02115da0;

void __sinit_ov030_02114924(void)
{
    func_02017acc(&data_ov030_02115d00, ASSET_MONKEY_BMD);
    func_020731dc(&data_ov030_02115d00, (void *)func_02017ab4, &data_ov030_02115d28);
    gMonkeyHoldAnimationFile.Construct(ASSET_MONKEY_HOLD_BCA);
    func_020731dc(&gMonkeyHoldAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov030_02115d34);
    gMonkeyJumpStAnimationFile.Construct(ASSET_MONKEY_JUMP_ST_BCA);
    func_020731dc(&gMonkeyJumpStAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov030_02115d40);
    gMonkeyJumpEdAnimationFile.Construct(ASSET_MONKEY_JUMP_ED_BCA);
    func_020731dc(&gMonkeyJumpEdAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov030_02115d64);
    gMonkeyRunStAnimationFile.Construct(ASSET_MONKEY_RUN_ST_BCA);
    func_020731dc(&gMonkeyRunStAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov030_02115d70);
    gMonkeyRunAnimationFile.Construct(ASSET_MONKEY_RUN_BCA);
    func_020731dc(&gMonkeyRunAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov030_02115d88);
    gMonkeyRunEdAnimationFile.Construct(ASSET_MONKEY_RUN_ED_BCA);
    func_020731dc(&gMonkeyRunEdAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov030_02115d94);
    data_ov030_02115cf0.Construct(ASSET_MONKEY_WAIT1_BCA);
    func_020731dc(&data_ov030_02115cf0, (void *)SharedFilePtr_Destruct_Anim, &data_ov030_02115dac);
    gMonkeyWait2AnimationFile.Construct(ASSET_MONKEY_WAIT2_BCA);
    func_020731dc(&gMonkeyWait2AnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov030_02115db8);
    gMonkeyWait3AnimationFile.Construct(ASSET_MONKEY_WAIT3_BCA);
    func_020731dc(&gMonkeyWait3AnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov030_02115dc4);
    gMonkeyWait4AnimationFile.Construct(ASSET_MONKEY_WAIT4_BCA);
    func_020731dc(&gMonkeyWait4AnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov030_02115dd0);

    data_ov030_02115e0c[0].lo = data_ov030_02115b68;
    data_ov030_02115e0c[0].hi = data_ov030_02115b60;
    data_ov030_02115e0c[1].lo = data_ov030_02115af0;
    data_ov030_02115e0c[1].hi = data_ov030_02115b50;
    data_ov030_02115e0c[2].lo = data_ov030_02115b00;
    data_ov030_02115e0c[2].hi = data_ov030_02115b40;
    data_ov030_02115e0c[3].lo = data_ov030_02115b48;
    data_ov030_02115e0c[3].hi = data_ov030_02115b18;
    data_ov030_02115e0c[4].lo = data_ov030_02115b10;
    data_ov030_02115e0c[4].hi = data_ov030_02115ad8;
    data_ov030_02115e0c[5].lo = data_ov030_02115b58;
    data_ov030_02115e0c[5].hi = data_ov030_02115b20;
    data_ov030_02115e0c[6].lo = data_ov030_02115ae0;
    data_ov030_02115e0c[6].hi = data_ov030_02115b28;
    data_ov030_02115e0c[7].lo = data_ov030_02115ae8;
    data_ov030_02115e0c[7].hi = data_ov030_02115b30;
    data_ov030_02115e0c[8].lo = data_ov030_02115ac8;
    data_ov030_02115e0c[8].hi = data_ov030_02115ad0;
    data_ov030_02115e0c[9].lo = data_ov030_02115b08;
    data_ov030_02115e0c[9].hi = data_ov030_02115b70;
    data_ov030_02115e0c[10].lo = data_ov030_02115af8;
    data_ov030_02115e0c[10].hi = data_ov030_02115b38;

    *(unsigned int*)&data_ov030_02115ddc = 0x1c000;
    *(unsigned int*)((char*)&data_ov030_02115ddc + 4) = (unsigned int)-0x42000;
    *(unsigned int*)((char*)&data_ov030_02115ddc + 8) = 0x18000;
    func_020731dc(&data_ov030_02115ddc, (void *)&_ZN7Vector3D1Ev, &data_ov030_02115d58);
    {
        unsigned int *p = (unsigned int*)&data_ov030_02115de8;
        p[0] = 0x1c000;
        p[1] = (unsigned int)-0x28000;
        p[2] = 0x28000;
        func_020731dc(p, (void *)&_ZN7Vector3D1Ev, &data_ov030_02115d4c);
    }
    {
        unsigned int *p = (unsigned int*)&data_ov030_02115df4;
        p[0] = 0x2b000;
        p[1] = (unsigned int)-0x42000;
        p[2] = 0x18000;
        func_020731dc(p, (void *)&_ZN7Vector3D1Ev, &data_ov030_02115d7c);
    }
    {
        unsigned int *p = (unsigned int*)&data_ov030_02115e00;
        p[0] = 0x30000;
        p[1] = (unsigned int)-0x1e000;
        p[2] = 0x1e000;
        func_020731dc(p, (void *)&_ZN7Vector3D1Ev, &data_ov030_02115da0);
    }
}
}
