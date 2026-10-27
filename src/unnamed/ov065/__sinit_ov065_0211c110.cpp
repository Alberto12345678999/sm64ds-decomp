//cpp
#include "SharedFilePtr.h"

extern "C" {

/* Runtime asset handles resolved through the overlay 0 file table. */
enum sinit_ov065_0211c110_AssetId {
    ASSET_YUREI_MUCHO_BMD = 0x042d,
    ASSET_YUREI_MUCHO_ATTACK_BCA = 0x042e,
    ASSET_YUREI_MUCHO_BALL_BMD = 0x042f,
    ASSET_YUREI_MUCHO_WAIT_BCA = 0x0430
};

extern void *func_02017acc(void *, unsigned int);
extern void func_020731dc(void *, void *, void **);
extern int func_02017ab4(int);
extern int SharedFilePtr_Destruct_Anim(int);

/* Two words copied as a unit. Under C++ a struct of two scalar fields is
   assigned field by field, which reorders the loads; an array member keeps
   C's schedule. */
typedef struct {
    int w[2];
} S8;

extern S8 data_ov065_0211d610;
extern S8 data_ov065_0211d618;
extern SharedFilePtr data_ov065_0211d600;
extern SharedFilePtr data_ov065_0211d608;
extern void *data_ov065_0211d638[3];
extern void *data_ov065_0211d62c[3];
extern void *data_ov065_0211d620[3];
extern void *data_ov065_0211d644[3];

extern S8 data_ov065_0211d670[2];
extern S8 data_ov065_0211d680[2];
extern S8 data_ov065_0211d650[2];
extern S8 data_ov065_0211d660[2];

extern S8 data_ov065_0211cb30, data_ov065_0211cb58;
extern S8 data_ov065_0211cb20, data_ov065_0211cb40;
extern S8 data_ov065_0211cb28, data_ov065_0211cb50;
extern S8 data_ov065_0211cb38, data_ov065_0211cb48;

void __sinit_ov065_0211c110(void)
{
    func_02017acc(&data_ov065_0211d610, ASSET_YUREI_MUCHO_BALL_BMD);
    func_020731dc(&data_ov065_0211d610, (void *)func_02017ab4, data_ov065_0211d644);
    func_02017acc(&data_ov065_0211d618, ASSET_YUREI_MUCHO_BMD);
    func_020731dc(&data_ov065_0211d618, (void *)func_02017ab4, data_ov065_0211d620);
    data_ov065_0211d600.Construct(ASSET_YUREI_MUCHO_WAIT_BCA);
    func_020731dc(&data_ov065_0211d600, (void *)SharedFilePtr_Destruct_Anim, data_ov065_0211d62c);
    data_ov065_0211d608.Construct(ASSET_YUREI_MUCHO_ATTACK_BCA);
    func_020731dc(&data_ov065_0211d608, (void *)SharedFilePtr_Destruct_Anim, data_ov065_0211d638);

    data_ov065_0211d670[0] = data_ov065_0211cb30; data_ov065_0211d670[1] = data_ov065_0211cb58;
    data_ov065_0211d680[0] = data_ov065_0211cb20; data_ov065_0211d680[1] = data_ov065_0211cb40;
    data_ov065_0211d650[0] = data_ov065_0211cb28; data_ov065_0211d650[1] = data_ov065_0211cb50;
    data_ov065_0211d660[0] = data_ov065_0211cb38; data_ov065_0211d660[1] = data_ov065_0211cb48;
}
}
