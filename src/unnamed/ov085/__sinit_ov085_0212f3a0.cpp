//cpp
#include "SharedFilePtr.h"

extern "C" {

/* Runtime asset handles resolved through the overlay 0 file table. */
enum sinit_ov085_0212f3a0_AssetId {
    ASSET_PEACH_JUMP_BCA = 0x03f0,
    ASSET_PEACH_JUMP_END_BCA = 0x03f1,
    ASSET_PEACH_JUMP_LOOP_BCA = 0x03f2,
    ASSET_PEACH_LOW_BMD = 0x03f3,
    ASSET_PEACH_OP_WAIT_BCA = 0x03f4,
    ASSET_PEACH_RUN_BCA = 0x03f6,
    ASSET_PEACH_WAIT_BCA = 0x03f7,
    ASSET_PEACH_WALK_BCA = 0x03f9
};

extern void *func_02017acc(void *, unsigned int);
extern void func_020731dc(void *, void *, void **);
extern int func_02017ab4(int);
extern int SharedFilePtr_Destruct_Anim(int);

extern char data_ov085_021304f4[];
extern void *data_ov085_02130538[3];
extern SharedFilePtr data_ov085_021304d4;
extern void *data_ov085_02130544[3];
extern SharedFilePtr data_ov085_021304c4;
extern void *data_ov085_02130550[3];
extern SharedFilePtr data_ov085_021304e4;
extern void *data_ov085_021304fc[3];
extern SharedFilePtr data_ov085_021304ec;
extern void *data_ov085_02130508[3];
extern SharedFilePtr gPeachJumpEndAnimationFile;
extern void *data_ov085_02130514[3];
extern SharedFilePtr gPeachJumpLoopAnimationFile;
extern void *data_ov085_02130520[3];
extern SharedFilePtr data_ov085_021304bc;
extern void *data_ov085_0213052c[3];

/* Two words copied as a unit. Under C++ a struct of two scalar fields is
   assigned field by field, which reorders the loads; an array member keeps
   C's schedule. */
struct P2 {
    int w[2];
};
extern struct P2 data_ov085_0213055c[];
extern struct P2 data_ov085_0212ff7c;
extern struct P2 data_ov085_0212ff64;
extern struct P2 data_ov085_0212ff44;
extern struct P2 data_ov085_0212ff6c;
extern struct P2 data_ov085_0212ff4c;
extern struct P2 data_ov085_0212ff74;
extern struct P2 data_ov085_0212ff54;
extern struct P2 data_ov085_0212ff5c;
extern struct P2 data_ov085_0212ff3c;
extern struct P2 data_ov085_0212ff34;

void __sinit_ov085_0212f3a0(void) {
    func_02017acc(data_ov085_021304f4, ASSET_PEACH_LOW_BMD);
    func_020731dc(data_ov085_021304f4, (void *)func_02017ab4, data_ov085_02130538);
    data_ov085_021304d4.Construct(ASSET_PEACH_WAIT_BCA);
    func_020731dc(&data_ov085_021304d4, (void *)SharedFilePtr_Destruct_Anim, data_ov085_02130544);
    data_ov085_021304c4.Construct(ASSET_PEACH_WALK_BCA);
    func_020731dc(&data_ov085_021304c4, (void *)SharedFilePtr_Destruct_Anim, data_ov085_02130550);
    data_ov085_021304e4.Construct(ASSET_PEACH_RUN_BCA);
    func_020731dc(&data_ov085_021304e4, (void *)SharedFilePtr_Destruct_Anim, data_ov085_021304fc);
    data_ov085_021304ec.Construct(ASSET_PEACH_JUMP_BCA);
    func_020731dc(&data_ov085_021304ec, (void *)SharedFilePtr_Destruct_Anim, data_ov085_02130508);
    gPeachJumpEndAnimationFile.Construct(ASSET_PEACH_JUMP_END_BCA);
    func_020731dc(&gPeachJumpEndAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  data_ov085_02130514);
    gPeachJumpLoopAnimationFile.Construct(ASSET_PEACH_JUMP_LOOP_BCA);
    func_020731dc(&gPeachJumpLoopAnimationFile, (void *)SharedFilePtr_Destruct_Anim,
                  data_ov085_02130520);
    data_ov085_021304bc.Construct(ASSET_PEACH_OP_WAIT_BCA);
    func_020731dc(&data_ov085_021304bc, (void *)SharedFilePtr_Destruct_Anim, data_ov085_0213052c);

    data_ov085_0213055c[0] = data_ov085_0212ff7c;
    data_ov085_0213055c[1] = data_ov085_0212ff64;
    data_ov085_0213055c[2] = data_ov085_0212ff44;
    data_ov085_0213055c[3] = data_ov085_0212ff6c;
    data_ov085_0213055c[4] = data_ov085_0212ff4c;
    data_ov085_0213055c[5] = data_ov085_0212ff74;
    data_ov085_0213055c[6] = data_ov085_0212ff54;
    data_ov085_0213055c[7] = data_ov085_0212ff5c;
    data_ov085_0213055c[8] = data_ov085_0212ff3c;
    data_ov085_0213055c[9] = data_ov085_0212ff34;
}
}
