//cpp
#include "SharedFilePtr.h"

extern "C" {

/* Runtime asset handles resolved through the overlay 0 file table. */
enum sinit_ov084_02130558_AssetId {
    ASSET_RED_BOMBHEI_BMD = 0x02b9,
    ASSET_RED_WAIT_BCA = 0x02ba
};

extern void *func_02017acc(void *, unsigned int);
extern void func_020731dc(void *, void *, void **);
extern int func_02017ab4(int);
extern int SharedFilePtr_Destruct_Anim(int);
extern int data_ov084_02130da4[];
extern void *data_ov084_02130dac[3];
extern SharedFilePtr data_ov084_02130d9c;
extern void *data_ov084_02130db8[3];

/* Two words copied as a unit. Under C++ a struct of two scalar fields is
   assigned field by field, which reorders the loads; an array member keeps
   C's schedule. */
struct Pair {
    int w[2];
};
extern struct Pair data_ov084_021309dc;
extern struct Pair data_ov084_021309ec;
extern struct Pair data_ov084_021309cc;
extern struct Pair data_ov084_021309e4;
extern struct Pair data_ov084_021309c4;
extern struct Pair data_ov084_021309d4;

struct Dst {
    struct Pair p0;
    struct Pair p1;
    struct Pair p2;
    struct Pair p3;
    struct Pair p4;
    struct Pair p5;
};
extern struct Dst data_ov084_02130dc4;

void __sinit_ov084_02130558(void)
{
    func_02017acc(data_ov084_02130da4, ASSET_RED_BOMBHEI_BMD);
    func_020731dc(data_ov084_02130da4, (void *)func_02017ab4, data_ov084_02130dac);
    data_ov084_02130d9c.Construct(ASSET_RED_WAIT_BCA);
    func_020731dc(&data_ov084_02130d9c, (void *)SharedFilePtr_Destruct_Anim, data_ov084_02130db8);
    data_ov084_02130dc4.p0 = data_ov084_021309dc;
    data_ov084_02130dc4.p1 = data_ov084_021309ec;
    data_ov084_02130dc4.p2 = data_ov084_021309cc;
    data_ov084_02130dc4.p3 = data_ov084_021309e4;
    data_ov084_02130dc4.p4 = data_ov084_021309c4;
    data_ov084_02130dc4.p5 = data_ov084_021309d4;
}
}
