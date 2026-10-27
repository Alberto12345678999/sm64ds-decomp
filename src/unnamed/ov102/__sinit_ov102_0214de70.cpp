//cpp
#include "types.h"
#include "SharedFilePtr.h"

extern "C" {

/* Runtime asset handles resolved through the overlay 0 file table. */
enum sinit_ov102_0214de70_AssetId {
    ASSET_BOMBHEI_CARRY_BCA = 0x02b7,
    ASSET_BOMBHEI_WALK_BCA = 0x02b8
};

extern void func_020731dc(void *, void *, void **);
extern int SharedFilePtr_Destruct_Anim(int);
/* local extern: C++ cannot take a destructor's address, so the registrations
   name ~Vector3() by its linker name. */
extern int _ZN7Vector3D1Ev[];
extern SharedFilePtr data_ov102_0214e9c0;
extern SharedFilePtr data_ov102_0214e9c8;
extern void *data_ov102_0214e9d0[3];
extern void *data_ov102_0214e9dc[3];
extern void *data_ov102_0214ea0c[3];
extern void *data_ov102_0214e9f4[3];
extern void *data_ov102_0214ea00[3];
extern void *data_ov102_0214e9e8[3];

extern Vector3 data_ov102_0214ea18;
extern Vector3 data_ov102_0214ea24;
extern Vector3 data_ov102_0214ea30;
extern Vector3 data_ov102_0214ea3c;

void __sinit_ov102_0214de70(void)
{
    data_ov102_0214e9c0.Construct(ASSET_BOMBHEI_WALK_BCA);
    func_020731dc(&data_ov102_0214e9c0, (void *)SharedFilePtr_Destruct_Anim, data_ov102_0214e9d0);
    data_ov102_0214e9c8.Construct(ASSET_BOMBHEI_CARRY_BCA);
    func_020731dc(&data_ov102_0214e9c8, (void *)SharedFilePtr_Destruct_Anim, data_ov102_0214e9dc);

    data_ov102_0214ea18.x = 0x1c000;
    data_ov102_0214ea18.y = -0x14000;
    data_ov102_0214ea18.z = 0x28000;
    func_020731dc(&data_ov102_0214ea18, _ZN7Vector3D1Ev, data_ov102_0214ea0c);

    {
        volatile Vector3 *p = (volatile Vector3 *)&data_ov102_0214ea24;
        p->x = 0x1c000;
        p->y = -0x14000;
        p->z = 0x3c000;
    }
    func_020731dc(&data_ov102_0214ea24, _ZN7Vector3D1Ev, data_ov102_0214e9f4);

    {
        volatile Vector3 *p = (volatile Vector3 *)&data_ov102_0214ea30;
        p->x = 0x2b000;
        p->y = -0xa000;
        p->z = -0x14000;
    }
    func_020731dc(&data_ov102_0214ea30, _ZN7Vector3D1Ev, data_ov102_0214ea00);

    {
        volatile Vector3 *p = (volatile Vector3 *)&data_ov102_0214ea3c;
        p->x = 0x30000;
        p->y = -0x1e000;
        p->z = 0x3c000;
    }
    func_020731dc(&data_ov102_0214ea3c, _ZN7Vector3D1Ev, data_ov102_0214e9e8);
}
}
