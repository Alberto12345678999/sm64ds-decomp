//cpp
#include "types.h"
#include "SharedFilePtr.h"

extern "C" {

/* Runtime asset handles resolved through the overlay 0 file table. */
enum sinit_ov019_021127a4_AssetId {
    ASSET_PENGUIN_BMD = 0x03fb,
    ASSET_PENGUIN_ANGRY_BTP = 0x03fd,
    ASSET_PENGUIN_DIVE_BCA = 0x0400,
    ASSET_PENGUIN_JUMP_ED_BCA = 0x0401,
    ASSET_PENGUIN_JUMP_ST_BCA = 0x0402,
    ASSET_PENGUIN_SLIDER_BCA = 0x0403,
    ASSET_PENGUIN_SLIDER_BTP = 0x0404,
    ASSET_PENGUIN_STAND_UP_BCA = 0x0405,
    ASSET_PENGUIN_WAIT1_BCA = 0x0406,
    ASSET_PENGUIN_WAIT1_BTP = 0x0407,
    ASSET_PENGUIN_WALK_BCA = 0x0408
};

extern void *func_02017acc(void *, unsigned int);
extern void func_020731dc(void *, void *, void **);
extern void *SharedFilePtr_Construct_TexSeq(void *, unsigned int);
extern int func_02017ab4(int);
extern int SharedFilePtr_Destruct_Anim(int);
extern int SharedFilePtr_Destruct_TexSeq(int);
/* local extern: C++ cannot take a destructor's address, so the registrations
   name ~Vector3() by its linker name. */
extern void *_ZN7Vector3D1Ev(void *object);

extern void* data_ov019_02113498;
extern void* data_ov019_021134dc;
extern SharedFilePtr gOV019PenguinWait1AnimationFile;
extern void* data_ov019_021134f4;
extern SharedFilePtr gOV019PenguinWalkAnimationFile;
extern void* data_ov019_02113500;
extern SharedFilePtr gPenguinJumpStAnimationFile;
extern void* data_ov019_0211350c;
extern SharedFilePtr gPenguinJumpEdAnimationFile;
extern void* data_ov019_02113524;
extern SharedFilePtr gPenguinDiveAnimationFile;
extern void* data_ov019_02113530;
extern SharedFilePtr gPenguinSliderAnimationFile;
extern void* data_ov019_02113548;
extern SharedFilePtr gPenguinStandUpAnimationFile;
extern void* data_ov019_02113554;
extern struct SharedFilePtr gOV019PenguinAngryTextureSequenceFile;
extern void* data_ov019_02113560;
extern struct SharedFilePtr gPenguinSliderTextureSequenceFile;
extern void* data_ov019_021134b8;
extern struct SharedFilePtr gOV019PenguinWait1TextureSequenceFile;
extern void* data_ov019_021134c4;

/* Two words copied as a unit. Under C++ a struct of two scalar fields is
   assigned field by field, which reorders the loads; an array member keeps
   C's schedule. */
struct P2 {
    int w[2];
};
extern struct P2 data_ov019_0211356c[12];
extern struct P2 data_ov019_021132b8;
extern struct P2 data_ov019_02113280;
extern struct P2 data_ov019_021132a8;
extern struct P2 data_ov019_021132b0;
extern struct P2 data_ov019_02113278;
extern struct P2 data_ov019_02113290;
extern struct P2 data_ov019_021132c0;
extern struct P2 data_ov019_021132a0;
extern struct P2 data_ov019_02113288;
extern struct P2 data_ov019_02113298;
extern struct P2 data_ov019_02113270;
extern struct P2 data_ov019_021132c8;

extern Vector3 data_ov019_021134e8;
extern void* data_ov019_021134d0;

extern Vector3 data_ov019_0211353c;
extern void* data_ov019_02113518;

void __sinit_ov019_021127a4(void)
{
    func_02017acc(&data_ov019_02113498, ASSET_PENGUIN_BMD);
    func_020731dc(&data_ov019_02113498, (void *)func_02017ab4, &data_ov019_021134dc);
    gOV019PenguinWait1AnimationFile.Construct(ASSET_PENGUIN_WAIT1_BCA);
    func_020731dc(&gOV019PenguinWait1AnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov019_021134f4);
    gOV019PenguinWalkAnimationFile.Construct(ASSET_PENGUIN_WALK_BCA);
    func_020731dc(&gOV019PenguinWalkAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov019_02113500);
    gPenguinJumpStAnimationFile.Construct(ASSET_PENGUIN_JUMP_ST_BCA);
    func_020731dc(&gPenguinJumpStAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov019_0211350c);
    gPenguinJumpEdAnimationFile.Construct(ASSET_PENGUIN_JUMP_ED_BCA);
    func_020731dc(&gPenguinJumpEdAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov019_02113524);
    gPenguinDiveAnimationFile.Construct(ASSET_PENGUIN_DIVE_BCA);
    func_020731dc(&gPenguinDiveAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov019_02113530);
    gPenguinSliderAnimationFile.Construct(ASSET_PENGUIN_SLIDER_BCA);
    func_020731dc(&gPenguinSliderAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov019_02113548);
    gPenguinStandUpAnimationFile.Construct(ASSET_PENGUIN_STAND_UP_BCA);
    func_020731dc(&gPenguinStandUpAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  &data_ov019_02113554);
    SharedFilePtr_Construct_TexSeq(&gOV019PenguinAngryTextureSequenceFile, ASSET_PENGUIN_ANGRY_BTP);
    func_020731dc(&gOV019PenguinAngryTextureSequenceFile, (void *)SharedFilePtr_Destruct_TexSeq,
                  &data_ov019_02113560);
    SharedFilePtr_Construct_TexSeq(&gPenguinSliderTextureSequenceFile, ASSET_PENGUIN_SLIDER_BTP);
    func_020731dc(&gPenguinSliderTextureSequenceFile, (void *)SharedFilePtr_Destruct_TexSeq,
                  &data_ov019_021134b8);
    SharedFilePtr_Construct_TexSeq(&gOV019PenguinWait1TextureSequenceFile, ASSET_PENGUIN_WAIT1_BTP);
    func_020731dc(&gOV019PenguinWait1TextureSequenceFile, (void *)SharedFilePtr_Destruct_TexSeq,
                  &data_ov019_021134c4);

    data_ov019_0211356c[0] = data_ov019_021132b8;
    data_ov019_0211356c[1] = data_ov019_02113280;
    data_ov019_0211356c[2] = data_ov019_021132a8;
    data_ov019_0211356c[3] = data_ov019_021132b0;
    data_ov019_0211356c[4] = data_ov019_02113278;
    data_ov019_0211356c[5] = data_ov019_02113290;
    data_ov019_0211356c[6] = data_ov019_021132c0;
    data_ov019_0211356c[7] = data_ov019_021132a0;
    data_ov019_0211356c[8] = data_ov019_02113288;
    data_ov019_0211356c[9] = data_ov019_02113298;
    data_ov019_0211356c[10] = data_ov019_02113270;
    data_ov019_0211356c[11] = data_ov019_021132c8;

    data_ov019_021134e8.x = -25962657;
    data_ov019_021134e8.y = -23381572;
    data_ov019_021134e8.z = -26155537;
    func_020731dc(&data_ov019_021134e8, (void *)&_ZN7Vector3D1Ev, &data_ov019_021134d0);

    data_ov019_0211353c.x = -19464192;
    data_ov019_0211353c.y = 0x600000;
    data_ov019_0211353c.z = 0;
    func_020731dc(&data_ov019_0211353c, (void *)&_ZN7Vector3D1Ev, &data_ov019_02113518);
}
}
