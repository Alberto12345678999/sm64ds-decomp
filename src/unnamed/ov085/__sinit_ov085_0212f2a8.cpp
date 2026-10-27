//cpp
#include "SharedFilePtr.h"

extern "C" {

/* Runtime asset handles resolved through the overlay 0 file table. */
enum sinit_ov085_0212f2a8_AssetId {
    ASSET_KINOPIO_BMD = 0x035c,
    ASSET_KINOPIO_WAIT1_BCA = 0x035d,
    ASSET_KINOPIO_WAIT2_BCA = 0x035e
};

extern void *func_02017acc(void *, unsigned int);
extern void func_020731dc(void *, void *, void **);
extern char data_ov085_02130480[];
extern void *data_ov085_02130498[3];
extern SharedFilePtr data_ov085_02130488;
extern void *data_ov085_021304a4[3];
extern SharedFilePtr data_ov085_02130490;
extern void *data_ov085_021304b0[3];
extern int func_02017ab4(int);
extern int SharedFilePtr_Destruct_Anim(int);

/* Two words copied as a unit. Under C++ a struct of two scalar fields is
   assigned field by field, which reorders the loads; an array member keeps
   C's schedule. */
typedef struct {
    int w[2];
} P;
extern P data_ov085_0212fe40;
extern P data_ov085_0212fe48;
extern P data_ov085_0212fe30;
extern P data_ov085_0212fe38;

typedef struct {
    P p0;    /* 0x00 */
    P p1;    /* 0x08 */
    int gap; /* 0x10 */
    P p2;    /* 0x14 */
    P p3;    /* 0x1c */
} D;
extern D data_ov085_0212fe88;

void __sinit_ov085_0212f2a8(void) {
    func_02017acc(data_ov085_02130480, ASSET_KINOPIO_BMD);
    func_020731dc(data_ov085_02130480, (void *)func_02017ab4, data_ov085_02130498);
    data_ov085_02130488.Construct(ASSET_KINOPIO_WAIT1_BCA);
    func_020731dc(&data_ov085_02130488, (void *)SharedFilePtr_Destruct_Anim, data_ov085_021304a4);
    data_ov085_02130490.Construct(ASSET_KINOPIO_WAIT2_BCA);
    func_020731dc(&data_ov085_02130490, (void *)SharedFilePtr_Destruct_Anim, data_ov085_021304b0);
    data_ov085_0212fe88.p0 = data_ov085_0212fe40;
    data_ov085_0212fe88.p1 = data_ov085_0212fe48;
    data_ov085_0212fe88.p2 = data_ov085_0212fe30;
    data_ov085_0212fe88.p3 = data_ov085_0212fe38;
}
}
