#ifndef DASTAR_C_H
#define DASTAR_C_H

/* RECONSTRUCTED NAMES USED IN THIS HEADER. SM64DS RTTI names the
 * implementation(s) below; the registry profile object and the factory
 * spelling are Tier B reconstructions -- evidence-bounded proposals, not
 * recovered SM64DS symbols. Exact original spellings are not preserved.
 *
 *   daStar_c -- daStar_c_classInit_STAR (was PowerStar_Spawn), g_profile_STAR (was PowerStar_SpawnInfo)
 */

#include "types.h"

/* Derives from dEnemyBase_c, and TWO INDEPENDENT WITNESSES agree on the layout:
 * the class's own destructor `_ZN8daStar_cD1Ev` destroys each member, and
 * `daStar_c_classInit_STAR` constructs the same types at the same offsets before
 * storing `_ZTV8daStar_c`. Everything this header used to restate below
 * 0x110 belongs to dEnemyBase_c and dActor_c and is inherited now.
 *
 * The members close on each other, which is what makes the layout a
 * reading rather than a guess:
 *
 *     0x110 dCcAcPos_c  0x40    -> 0x150
 *     0x150 dBgCh_Actr               0x1bc   -> 0x30c
 *     0x30c ModelAnim                  0x64    -> 0x370
 *     0x370 ModelAnim                  0x64    -> 0x3d4
 *     0x3d4 ShadowModel                0x28    -> 0x3fc
 *
 * SIZE IS THE ROM'S OWN: `daStar_c_classInit_STAR` calls
 * `fBase_c::operator new(1220)` -- 0x4c4 -- and stores this class's
 * vtable, so that literal IS this class's sizeof.
 */

#include "dEnemyBase_c.h"
#include "ModelAnim.h"
#include "dCcAcPos_c.h"
#include "ShadowModel.h"
#include "dBgCh_Actr.h"

struct daStar_c : dEnemyBase_c {
    dCcAcPos_c    mdCc_c;         /* 0x110 */
    dBgCh_Actr                 mWithMeshClsn;         /* 0x150 */
    ModelAnim                    mModelAnim1;           /* 0x30c */
    ModelAnim                    mModelAnim2;           /* 0x370 */
    ShadowModel                  mShadowModel;          /* 0x3d4 */
    u8  pad_3fc[0x40];
    s32                          unk_43c;               /* 0x43c */
    s32                          unk_440;               /* 0x440 */
    u8  pad_444[0x54];
    s8                           unk_498;               /* 0x498 */
    u8  pad_499[0x1];
    u8                           unk_49a;               /* 0x49a */
    u8  pad_49b[0x2];
    u8                           unk_49d;               /* 0x49d */
    u8  pad_49e[0x1];
    u8                           unk_49f;               /* 0x49f */
    u8  pad_4a0[0x2];
    u16 unk_4a2;              /* 0x4a2 */
    u8  pad_4a4[0x4];
    s32                          unk_4a8;               /* 0x4a8 */
    s32                          unk_4ac;               /* 0x4ac */
    s32                          unk_4b0;               /* 0x4b0 */
    u8  pad_4b4[0x10];

    /* --- vtable --- */
    virtual ~daStar_c();

    virtual s32   OnYoshiTryEat();         /* slot 18 */
    virtual void  OnTurnIntoEgg(Player &player); /* slot 19 */

    void AddStarMarker();
    void func_ov002_020e7104(int r1);
    int Behavior();
    int CleanupResources();
    s32 InitResources();
    int Render();

    /* Receivers. The address is the method name. */
    void func_ov002_020e6d88();
    void func_ov002_020e6df8();
    void func_ov002_020e6edc();
    void func_ov002_020e6fbc(int arg);
    void func_ov002_020e700c();
    void func_ov002_020e7090(int arg);
    void func_ov002_020e7218(char* a, int gate);
    int func_ov002_020e73ac();
    void func_ov002_020e7454();
    void func_ov002_020e7554();
    void func_ov002_020e763c();
    void func_ov002_020e7934(void* cam);
    int func_ov002_020e7c90(void* cam);
    void func_ov002_020e7d08();
    int func_ov002_020e7e14();
    void func_ov002_020e7e24();
    void func_ov002_020e7e58();
    void func_ov002_020e7eb4();
    void func_ov002_020e7eb8();
    void func_ov002_020e7f2c();
    void func_ov002_020e7fcc();
    void func_ov002_020e8098();
    void func_ov002_020e81e0();
    void func_ov002_020e8398();
    void func_ov002_020e84ec();
    void func_ov002_020e8618();
    void func_ov002_020e86ec();
    void func_ov002_020e88a8();
    void func_ov002_020e8abc();
    volatile unsigned int func_ov002_020e8c34();
    int func_ov002_020e8dd8();
    void func_ov002_020e8e80(int a);
    int func_ov002_020e8ef0(void* p);
    void func_ov002_020e930c();
    void func_ov002_020e9448();
    void func_ov002_020e9464();
    void func_ov002_020e947c(Vector3 *p, int n);
    void func_ov002_020e9590();
    int func_ov002_020e9630();
    void func_ov002_020e96a0();
    void func_ov002_020e9804();
    void func_ov002_020e9840();
    void func_ov002_020e99e8();
    void func_ov002_020e9af4();
    void func_ov002_020e9d18();
    void func_ov002_020ea06c();
    void func_ov002_020ea100();
    int func_ov002_020ea3a4();
    void func_ov002_020ea410();
    void func_ov002_020ea420();
    void func_ov002_020ea7ac();
    void func_ov002_020ea824();
    void func_ov002_020ea90c();
    void func_ov002_020ea9d0();
};

#ifndef SM64DS_PLATFORM_PC
/* ROM layout under mwccarm; host ABI divergence is tracked separately. */
typedef char PowerStar_size_must_be_0x4c4[sizeof(daStar_c) == 0x4c4 ? 1 : -1];
#endif

#endif /* DASTAR_C_H */
