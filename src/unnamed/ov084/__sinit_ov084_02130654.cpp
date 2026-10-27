//cpp
#include "SharedFilePtr.h"

extern "C" {

/* Runtime asset handles resolved through the overlay 0 file table. */
enum sinit_ov084_02130654_AssetId {
    ASSET_PAKKUN_ATTACK_BCA = 0x03cf,
    ASSET_PAKKUN_DEAD_BCA = 0x03d0,
    ASSET_PAKKUN_FIRE_BCA = 0x03d1,
    ASSET_PAKKUN_FIRE_ED_BCA = 0x03d2,
    ASSET_PAKKUN_MODEL_BMD = 0x03d3,
    ASSET_PAKKUN_SLEEP_BCA = 0x03d4,
    ASSET_PAKKUN_SLEEP_LOOP_BCA = 0x03d5
};

extern void *func_02017acc(void *, unsigned int);
extern void func_020731dc(void *, void *, void **);
extern int func_02017ab4(int);
extern int SharedFilePtr_Destruct_Anim(int);

extern char data_ov084_02130dfc[];
extern void *data_ov084_02130e44[3];
extern SharedFilePtr data_ov084_02130e14;
extern void *data_ov084_02130e50[3];
extern SharedFilePtr data_ov084_02130e24;
extern void *data_ov084_02130e68[3];
extern SharedFilePtr data_ov084_02130e0c;
extern void *data_ov084_02130e74[3];
extern SharedFilePtr data_ov084_02130df4;
extern void *data_ov084_02130e5c[3];
extern SharedFilePtr data_ov084_02130e04;
extern void *data_ov084_02130e2c[3];
extern SharedFilePtr data_ov084_02130e1c;
extern void *data_ov084_02130e38[3];

/* Two words copied as a unit. Under C++ a struct of two scalar fields is
   assigned field by field, which reorders the loads; an array member keeps
   C's schedule. */
struct P2 {
    int w[2];
};
extern struct P2 data_ov084_02130e80[];
extern struct P2 data_ov084_02130bb4;
extern struct P2 data_ov084_02130ba4;
extern struct P2 data_ov084_02130bbc;
extern struct P2 data_ov084_02130bac;
extern struct P2 data_ov084_02130bc4;
extern struct P2 data_ov084_02130bcc;
extern struct P2 data_ov084_02130bdc;
extern struct P2 data_ov084_02130bd4;
extern struct P2 data_ov084_02130be4;

void __sinit_ov084_02130654(void) {
    func_02017acc(data_ov084_02130dfc, ASSET_PAKKUN_MODEL_BMD);
    func_020731dc(data_ov084_02130dfc, (void *)func_02017ab4, data_ov084_02130e44);
    data_ov084_02130e14.Construct(ASSET_PAKKUN_ATTACK_BCA);
    func_020731dc(&data_ov084_02130e14, (void *)SharedFilePtr_Destruct_Anim, data_ov084_02130e50);
    data_ov084_02130e24.Construct(ASSET_PAKKUN_DEAD_BCA);
    func_020731dc(&data_ov084_02130e24, (void *)SharedFilePtr_Destruct_Anim, data_ov084_02130e68);
    data_ov084_02130e0c.Construct(ASSET_PAKKUN_SLEEP_BCA);
    func_020731dc(&data_ov084_02130e0c, (void *)SharedFilePtr_Destruct_Anim, data_ov084_02130e74);
    data_ov084_02130df4.Construct(ASSET_PAKKUN_SLEEP_LOOP_BCA);
    func_020731dc(&data_ov084_02130df4, (void *)SharedFilePtr_Destruct_Anim, data_ov084_02130e5c);
    data_ov084_02130e04.Construct(ASSET_PAKKUN_FIRE_BCA);
    func_020731dc(&data_ov084_02130e04, (void *)SharedFilePtr_Destruct_Anim, data_ov084_02130e2c);
    data_ov084_02130e1c.Construct(ASSET_PAKKUN_FIRE_ED_BCA);
    func_020731dc(&data_ov084_02130e1c, (void *)SharedFilePtr_Destruct_Anim, data_ov084_02130e38);

    data_ov084_02130e80[0] = data_ov084_02130bb4;
    data_ov084_02130e80[1] = data_ov084_02130ba4;
    data_ov084_02130e80[2] = data_ov084_02130bbc;
    data_ov084_02130e80[3] = data_ov084_02130bac;
    data_ov084_02130e80[4] = data_ov084_02130bc4;
    data_ov084_02130e80[5] = data_ov084_02130bcc;
    data_ov084_02130e80[6] = data_ov084_02130bdc;
    data_ov084_02130e80[7] = data_ov084_02130bd4;
    data_ov084_02130e80[8] = data_ov084_02130be4;
}
}
