//cpp
#include "types.h"
#include "SharedFilePtr.h"

extern "C" {

/* Runtime asset handles resolved through the overlay 0 file table. */
enum sinit_ov078_02126660_AssetId {
    ASSET_BOMBKING_DAMAGE_BCA = 0x02bb,
    ASSET_BOMBKING_GETUP_BCA = 0x02bc,
    ASSET_BOMBKING_JUMP_BCA = 0x02bd,
    ASSET_BOMBKING_JUMPED_BCA = 0x02be,
    ASSET_BOMBKING_LIFT_BCA = 0x02bf,
    ASSET_BOMBKING_START_BCA = 0x02c0,
    ASSET_BOMBKING_STRUGGLE_BCA = 0x02c1,
    ASSET_BOMBKING_THROW_BCA = 0x02c2,
    ASSET_BOMBKING_WAIT1_BCA = 0x02c3,
    ASSET_BOMBKING_WAIT2_BCA = 0x02c4,
    ASSET_BOMBKING_WALK1_BCA = 0x02c5,
    ASSET_BOMBKING_WALK2_BCA = 0x02c6,
    ASSET_BOMB_KING_BMD = 0x02c7
};

extern void *func_02017acc(void *, unsigned int);
extern void func_020731dc(void *, void *, void **);
extern int func_02017ab4(int);
extern int SharedFilePtr_Destruct_Anim(int);
/* local extern: C++ cannot take a destructor's address, so the registrations
   name ~Vector3() by its linker name. */
extern void *_ZN7Vector3D1Ev(void *object);

/* Opaque declarations of the typed storage in d_a_bombking.cpp.
 * The initializer passes addresses only; it does not access the payload fields. */
struct BombkingModelFile;
struct BombkingAnimFile;
extern struct BombkingModelFile gBombkingModelFile;
extern void* data_ov078_02126f48;
extern SharedFilePtr gBombkingGetupAnimationFile;
extern void* data_ov078_02126f54;
extern SharedFilePtr gBombkingDamageAnimationFile;
extern void* data_ov078_02126f60;
extern SharedFilePtr gBombkingJumpAnimationFile;
extern void* data_ov078_02126f6c;
extern SharedFilePtr gBombkingJumpedAnimationFile;
extern void* data_ov078_02126f78;
extern SharedFilePtr gBombkingLiftAnimationFile;
extern void* data_ov078_02126f84;
extern SharedFilePtr gBombkingStruggleAnimationFile;
extern void* data_ov078_02126f90;
extern SharedFilePtr gBombkingThrowAnimationFile;
extern void* data_ov078_02126f9c;
extern SharedFilePtr gBombkingWait1AnimationFile;
extern void* data_ov078_02126fa8;
extern SharedFilePtr gBombkingWait2AnimationFile;
extern void* data_ov078_02126fb4;
extern SharedFilePtr gBombkingWalk1AnimationFile;
extern void* data_ov078_02126fc0;
extern SharedFilePtr gBombkingWalk2AnimationFile;
extern void* data_ov078_02126fcc;
extern SharedFilePtr gBombkingStartAnimationFile;
extern void* data_ov078_02126fd8;

extern Vector3 data_ov078_0212711c;
extern void* data_ov078_02126fe4;
extern Vector3 data_ov078_02127128;
extern void* data_ov078_02126ff0;

/* Two words copied as a unit. Under C++ a struct of two scalar fields is
   assigned field by field, which reorders the loads; an array member keeps
   C's schedule. */
struct P2 {
    int w[2];
};
struct P4 { struct P2 lo, hi; };

extern struct P4 data_ov078_0212710c;
extern struct P2 data_ov078_02126d78;
extern struct P2 data_ov078_02126d40;
extern struct P4 data_ov078_0212700c;
extern struct P2 data_ov078_02126cf8;
extern struct P2 data_ov078_02126db8;
extern struct P4 data_ov078_0212701c;
extern struct P2 data_ov078_02126ce8;
extern struct P2 data_ov078_02126ce0;
extern struct P4 data_ov078_0212703c;
extern struct P2 data_ov078_02126d00;
extern struct P2 data_ov078_02126dc8;
extern struct P4 data_ov078_0212704c;
extern struct P2 data_ov078_02126df0;
extern struct P2 data_ov078_02126de8;
extern struct P4 data_ov078_0212707c;
extern struct P2 data_ov078_02126dd8;
extern struct P2 data_ov078_02126dd0;
extern struct P4 data_ov078_0212708c;
extern struct P2 data_ov078_02126d28;
extern struct P2 data_ov078_02126d38;
extern struct P4 data_ov078_021270ac;
extern struct P2 data_ov078_02126d98;
extern struct P2 data_ov078_02126d50;
extern struct P4 data_ov078_021270bc;
extern struct P2 data_ov078_02126d60;
extern struct P2 data_ov078_02126d20;
extern struct P4 data_ov078_021270dc;
extern struct P2 data_ov078_02126d70;
extern struct P2 data_ov078_02126d88;
extern struct P4 data_ov078_021270ec;
extern struct P2 data_ov078_02126d30;
extern struct P2 data_ov078_02126da0;
extern struct P4 data_ov078_02126ffc;
extern struct P2 data_ov078_02126d08;
extern struct P2 data_ov078_02126d80;
extern struct P4 data_ov078_0212702c;
extern struct P2 data_ov078_02126d10;
extern struct P2 data_ov078_02126cf0;
extern struct P4 data_ov078_0212706c;
extern struct P2 data_ov078_02126df8;
extern struct P2 data_ov078_02126de0;
extern struct P4 data_ov078_0212709c;
extern struct P2 data_ov078_02126dc0;
extern struct P2 data_ov078_02126db0;
extern struct P4 data_ov078_021270cc;
extern struct P2 data_ov078_02126d18;
extern struct P2 data_ov078_02126d48;
extern struct P4 data_ov078_021270fc;
extern struct P2 data_ov078_02126d90;
extern struct P2 data_ov078_02126da8;
extern struct P4 data_ov078_0212705c;
extern struct P2 data_ov078_02126d68;
extern struct P2 data_ov078_02126d58;

void __sinit_ov078_02126660(void)
{
    func_02017acc(&gBombkingModelFile, ASSET_BOMB_KING_BMD);
    func_020731dc(&gBombkingModelFile, (void *)func_02017ab4, &data_ov078_02126f48);
    gBombkingGetupAnimationFile.Construct(ASSET_BOMBKING_GETUP_BCA);
    func_020731dc(&gBombkingGetupAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov078_02126f54);
    gBombkingDamageAnimationFile.Construct(ASSET_BOMBKING_DAMAGE_BCA);
    func_020731dc(&gBombkingDamageAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov078_02126f60);
    gBombkingJumpAnimationFile.Construct(ASSET_BOMBKING_JUMP_BCA);
    func_020731dc(&gBombkingJumpAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov078_02126f6c);
    gBombkingJumpedAnimationFile.Construct(ASSET_BOMBKING_JUMPED_BCA);
    func_020731dc(&gBombkingJumpedAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov078_02126f78);
    gBombkingLiftAnimationFile.Construct(ASSET_BOMBKING_LIFT_BCA);
    func_020731dc(&gBombkingLiftAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov078_02126f84);
    gBombkingStruggleAnimationFile.Construct(ASSET_BOMBKING_STRUGGLE_BCA);
    func_020731dc(&gBombkingStruggleAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov078_02126f90);
    gBombkingThrowAnimationFile.Construct(ASSET_BOMBKING_THROW_BCA);
    func_020731dc(&gBombkingThrowAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov078_02126f9c);
    gBombkingWait1AnimationFile.Construct(ASSET_BOMBKING_WAIT1_BCA);
    func_020731dc(&gBombkingWait1AnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov078_02126fa8);
    gBombkingWait2AnimationFile.Construct(ASSET_BOMBKING_WAIT2_BCA);
    func_020731dc(&gBombkingWait2AnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov078_02126fb4);
    gBombkingWalk1AnimationFile.Construct(ASSET_BOMBKING_WALK1_BCA);
    func_020731dc(&gBombkingWalk1AnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov078_02126fc0);
    gBombkingWalk2AnimationFile.Construct(ASSET_BOMBKING_WALK2_BCA);
    func_020731dc(&gBombkingWalk2AnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov078_02126fcc);
    gBombkingStartAnimationFile.Construct(ASSET_BOMBKING_START_BCA);
    func_020731dc(&gBombkingStartAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov078_02126fd8);

    data_ov078_0212711c.x = 0x2c000;
    data_ov078_0212711c.y = -0x19000;
    data_ov078_0212711c.z = 0x34000;
    func_020731dc(&data_ov078_0212711c, (void *)&_ZN7Vector3D1Ev, &data_ov078_02126fe4);

    {
        int *p = (int *)&data_ov078_02127128;
        *p = 0x44000;
        p[1] = -0x19000;
        p[2] = 0x34000;
    }
    func_020731dc(&data_ov078_02127128, (void *)&_ZN7Vector3D1Ev, &data_ov078_02126ff0);

    data_ov078_0212710c.lo = data_ov078_02126d78;
    data_ov078_0212710c.hi = data_ov078_02126d40;
    data_ov078_0212700c.lo = data_ov078_02126cf8;
    data_ov078_0212700c.hi = data_ov078_02126db8;
    data_ov078_0212701c.lo = data_ov078_02126ce8;
    data_ov078_0212701c.hi = data_ov078_02126ce0;
    data_ov078_0212703c.lo = data_ov078_02126d00;
    data_ov078_0212703c.hi = data_ov078_02126dc8;
    data_ov078_0212704c.lo = data_ov078_02126df0;
    data_ov078_0212704c.hi = data_ov078_02126de8;
    data_ov078_0212707c.lo = data_ov078_02126dd8;
    data_ov078_0212707c.hi = data_ov078_02126dd0;
    data_ov078_0212708c.lo = data_ov078_02126d28;
    data_ov078_0212708c.hi = data_ov078_02126d38;
    data_ov078_021270ac.lo = data_ov078_02126d98;
    data_ov078_021270ac.hi = data_ov078_02126d50;
    data_ov078_021270bc.lo = data_ov078_02126d60;
    data_ov078_021270bc.hi = data_ov078_02126d20;
    data_ov078_021270dc.lo = data_ov078_02126d70;
    data_ov078_021270dc.hi = data_ov078_02126d88;
    data_ov078_021270ec.lo = data_ov078_02126d30;
    data_ov078_021270ec.hi = data_ov078_02126da0;
    data_ov078_02126ffc.lo = data_ov078_02126d08;
    data_ov078_02126ffc.hi = data_ov078_02126d80;
    data_ov078_0212702c.lo = data_ov078_02126d10;
    data_ov078_0212702c.hi = data_ov078_02126cf0;
    data_ov078_0212706c.lo = data_ov078_02126df8;
    data_ov078_0212706c.hi = data_ov078_02126de0;
    data_ov078_0212709c.lo = data_ov078_02126dc0;
    data_ov078_0212709c.hi = data_ov078_02126db0;
    data_ov078_021270cc.lo = data_ov078_02126d18;
    data_ov078_021270cc.hi = data_ov078_02126d48;
    data_ov078_021270fc.lo = data_ov078_02126d90;
    data_ov078_021270fc.hi = data_ov078_02126da8;
    data_ov078_0212705c.lo = data_ov078_02126d68;
    data_ov078_0212705c.hi = data_ov078_02126d58;
}
}
