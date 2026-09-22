//cpp
/* Recovered translation unit -- ov027/daObjSlIceBlock_c, Snowman's Land's
 * sliding ice block, both the shot and the spawner variants of it.
 *
 * .text span 0x021111a0..0x02111564, 7 functions, ROM ordinals 0..6, exactly
 * the contiguous linker run build/tu_map.json places here. All 7 are assembled
 * below and config/tu_manifest.d/ov027/daObjSlIceBlock_c.json names every one,
 * so the run has no hole and the 7 one-function files under src/ that used to
 * own these bytes are deleted by this change.
 *
 * IDENTITY IS THE CARTRIDGE'S. ov027 holds _ZTS17daObjSlIceBlock_c at
 * 0x021137d0; no SlidingIce RTTI record exists anywhere -- that was a coined
 * alias for this same class. The table at 0x02113824 carries this class's
 * own _ZTI (0x021137c4) at its typeinfo word. Two factories
 * (SL_ICEBLOCK_SHOT, SL_ICEBLOCK) build this one class.
 *
 * FUNCTION ORDER IS THE ROM'S OWN, under `#pragma defer_codegen off`.
 * Deferred code generation stays off for this TU so mwccarm emits one .text
 * section per function in SOURCE order: the lowest-address ROM function
 * (_ZN17daObjSlIceBlock_cD1Ev, 0x021111a0) is written FIRST and the highest
 * (_ZN17daObjSlIceBlock_c13InitResourcesEv, 0x02111440) LAST. Do not reorder.
 *
 * THE DESTRUCTOR IS ONE DEFINITION AND TWO SECTIONS (plus a homeless D2).
 * A single `daObjSlIceBlock_c::~daObjSlIceBlock_c()` emits D1 and D0, and
 * with deferred code generation off they land in the cartridge's order, D1
 * first at 0x021111a0 and D0 at 0x021111e4. The homeless D2 has no ROM symbol
 * and no inbound relocation once the leaf D1/D0 pair is retained, so the
 * manifest licenses it as deadstrip compiler-only output. It stores TWO
 * vptrs -- its own, then dBgActor_c's (inlined) -- then destroys dBgActor_c's
 * Model and dBgW_KcMbg and chains to dActor_c.
 *
 * KEY-FUNCTION SIDE EFFECT: none claimed. ~daObjSlIceBlock_c is the first
 * non-inline virtual and this TU defines it, but the promotion is text-only:
 * the manifest's compiler_only_output externalizes _ZTV/_ZTI/_ZTS to their
 * canonical public addresses (deadstrip-data) and claims no data or BSS range.
 *
 * WHAT THE PROMOTION CARRIES OVER, and nothing else was changed:
 *   1. data_ov027_02113be8 stays declared once as char[]; the word-indexed
 *      read in InitResources is cast at the use site (duplicate int[]
 *      spelling dropped as codegen-neutral).
 *   2. The destructor is one definition with two stacked markers -- writing
 *      them as two definitions is an `object redefined` error.
 *   3. Local shadow structs (VObj/V3/V316) stay as the leftover shards
 *      recovered them.
 *
 * The 7 legacy one-function sources this folds are named by the manifest's
 * `legacy_source` fields (history); they are not repeated here.
 */

/* Includes: union of the legacy files', first-seen in ROM-ascending
 * processing order. NOT verified for header ordering constraints (e.g. a
 * common.h-before-X rule) -- watch for new compile errors after this. */
#include "daObjSlIceBlock_c.h"
#include "Player.h"
#include "SharedFilePtr.h"
#include "dBgW.h"
#include "dBgActor_c.h"

/* Local shadow declarations carried from the legacy files verbatim.
 * NOT reconciled against real project headers -- check include/*.h for
 * each of these before compiling; a real header should usually win. */
/* shadow struct 'VObj' */
struct VObj {
  virtual void f0();
  virtual void f1();
  virtual void f2();
  virtual void f3();
  virtual void f4();
  virtual void m5(int);
};

/* shadow struct 'V3' */
struct V3 { int x,y,z; };

/* shadow struct 'V316' */
struct V316 { short x,y,z; };

extern "C" {
extern char data_ov027_02113be8[];
extern char data_ov027_02113be0[];
extern int DecIfAbove0_Short(void*);
extern int DecIfAbove0_Byte(void*);
extern int _Z14ApproachLinearRiii(int*, int, int);
extern void _ZN7fBase_c18MarkForDestructionEv(void*);
extern void _ZN8dActor_c9UpdatePosEP5dCc_c(void*, void*);
extern int _ZN5Sound8PlayLongEjjjRK7Vector3s(unsigned int, unsigned int, unsigned int, void*, unsigned int);
extern int _ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as(unsigned int, unsigned int, void*, void*, int, int);
int _ZN5Model8LoadFileER13SharedFilePtr(void *);
int _ZN7dBgW_Kc8LoadFileER13SharedFilePtr(void *);
int _ZN9ModelBase7SetFileEP8BMD_Fileii(void *, int, int, int);
void _ZN10dBgActor_c21UpdateModelPosAndRotYEv(void *);
void _ZN10dBgActor_c19UpdateClsnPosAndRotEv(void *);
void _ZN10dBgW_KcMbg7SetFileEP8KCL_FileRK9Matrix4x35Fix12IiEsR10CLPS_Block(
void *, int, void *, int, int, void *);
void func_020393d4(int *p, int v);
/* data_ov027_02113be8 is already declared above as char[]; keeping that FIRST
 * declaration and casting where a word is read. */
extern char data_ov027_02113108[];
extern int _ZN4dBgW21UpdatePosWithVelocityERS_P8dActor_cR5dBgPiR7Vector3P10Vector3_16S8_[];
}

#pragma defer_codegen off

/* -------------------------------------------------------------------------- */
/* ROM ordinals 0/1 -- _ZN17daObjSlIceBlock_cD1Ev 0x021111a0, _ZN17daObjSlIceBlock_cD0Ev 0x021111e4. */
/* ONE definition, two emitted sections.                                          */
/* -------------------------------------------------------------------------- */
// @symbol _ZN17daObjSlIceBlock_cD1Ev
// @symbol _ZN17daObjSlIceBlock_cD0Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * Two vtable stores and three destructor calls, every one a consequence of
 * `struct daObjSlIceBlock_c : dBgActor_c`: its own vptr, then dBgActor_c's -- inlined,
 * because dBgActor_c's destructor is defined in its class body -- then
 * dBgActor_c's Model and dBgW_KcMbg, then dActor_c. This class adds no
 * member with a destructor of its own.
 */
daObjSlIceBlock_c::~daObjSlIceBlock_c()
{
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 2 -- _ZN17daObjSlIceBlock_c15OnHitByMegaCharER6Player, 0x0211123c, size 0x28 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN17daObjSlIceBlock_c15OnHitByMegaCharER6Player
/* daObjSlIceBlock_c::OnHitByMegaChar -- vtable slot 27, ov027 0x0211123c.
 *
 * Same idiom as daObjBk_Dossunbar_c/daObjBk_Lift_c/daObjIceBoard_c::OnHitByMegaChar: Player::
 * IncMegaKillCount is a real method, and the trailing unqualified Kill()
 * call dispatches virtually -- daObjSlIceBlock_c does NOT override slot 31
 * itself (relocs.txt: _ZTV17daObjSlIceBlock_c+0x7c still relocates to
 * dBgActor_c::Kill, ov002 0x020ee55c), so this reaches the inherited
 * base implementation through the vtable, same mechanism as an override
 * would. */
void daObjSlIceBlock_c::OnHitByMegaChar(Player &player)
{
    player.IncMegaKillCount();
    Kill();
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 3 -- _ZN17daObjSlIceBlock_c16CleanupResourcesEv, 0x02111264, size 0x50 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN17daObjSlIceBlock_c16CleanupResourcesEv
/* recovered: named members + shared header, real C++ method */
int daObjSlIceBlock_c::CleanupResources()
{
  unsigned char ok = (actorID==0x5d);
  if(ok){ ((dBgW *)((char *)&(*(u8 *)&mMeshCollider)))->Disable(); }
  ((SharedFilePtr *)(data_ov027_02113be8))->Release();
  ((SharedFilePtr *)(data_ov027_02113be0))->Release();
  return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 4 -- _ZN17daObjSlIceBlock_c6RenderEv, 0x021112b4, size 0x50 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN17daObjSlIceBlock_c6RenderEv
/* recovered: named members + shared header, real C++ method */
int daObjSlIceBlock_c::Render()
{
  int x = actorID==0x5d;
  if(x){
    ((dBgActor_c *)(((char*)this)))->UpdateModelPosAndRotY();
    ((dBgActor_c *)(((char*)this)))->UpdateClsnPosAndRot();
    ((VObj*)((char*)&mModel))->m5(0);
  }
  return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 5 -- _ZN17daObjSlIceBlock_c8BehaviorEv, 0x02111304, size 0x13c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN17daObjSlIceBlock_c8BehaviorEv
/* recovered: named members + shared header, real C++ method */
int daObjSlIceBlock_c::Behavior()
{
  int isType = (actorID == 0x5d);
  if(isType){
    if(DecIfAbove0_Short((char *)&mDelayTimer) == 0){
      _Z14ApproachLinearRiii((int*)((char *)&mHorzSpeed), 0, 0x3000);
      if(_Z14ApproachLinearRiii((int*)((char *)&mPosY), mMinPosY, 0xa000) != 0){
        _ZN7fBase_c18MarkForDestructionEv(((char *)this));
      }
    }
    _ZN8dActor_c9UpdatePosEP5dCc_c(((char *)this), 0);
    mSoundID = _ZN5Sound8PlayLongEjjjRK7Vector3s(mSoundID, 3, 0x98, ((char *)this)+0x74, 0);
  } else {
    if(DecIfAbove0_Short((char *)&mDelayTimer) == 0){
      V3 pos;
      pos.x = mPosX;
      pos.y = mPosY;
      pos.z = mPosZ;
      int spawnType = 1;
      if(DecIfAbove0_Byte((char *)&mNumToBigIce) == 0){
        mNumToBigIce = 5;
        spawnType = 2;
      } else {
        pos.y -= 0x50000;
      }
      unsigned char cnt = mNumToBigIce;
      mDelayTimer = (cnt + 1) * 0x14;
      _ZN8dActor_c5SpawnEjjRK7Vector3PK10Vector3_16as(0x5d, spawnType, &pos, ((char *)this)+0x8c, mAreaId, -1);
    }
  }
  return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 6 -- _ZN17daObjSlIceBlock_c13InitResourcesEv, 0x02111440, size 0x124 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN17daObjSlIceBlock_c13InitResourcesEv
int daObjSlIceBlock_c::InitResources()
{
    _ZN5Model8LoadFileER13SharedFilePtr(data_ov027_02113be8);
    _ZN7dBgW_Kc8LoadFileER13SharedFilePtr(data_ov027_02113be0);

    int on = (actorID == 0x5d);
    if (on) {
        if (_ZN9ModelBase7SetFileEP8BMD_Fileii(&mModel, ((int *)data_ov027_02113be8)[1], 1, -1) == 0)
            return 0;
        _ZN10dBgActor_c21UpdateModelPosAndRotYEv(this);
        _ZN10dBgActor_c19UpdateClsnPosAndRotEv(this);
        _ZN10dBgW_KcMbg7SetFileEP8KCL_FileRK9Matrix4x35Fix12IiEsR10CLPS_Block(
            &mMeshCollider, *(int *)(data_ov027_02113be0 + 4), &mClsnMat,
            0x1000, mAngleY, data_ov027_02113108);
        func_020393d4((int *)&mMeshCollider,
            (int)_ZN4dBgW21UpdatePosWithVelocityERS_P8dActor_cR5dBgPiR7Vector3P10Vector3_16S8_);
        mMeshCollider.unk_4c = 0;
        mMeshCollider.Enable(this);
        mHorzSpeed = 0x2d000;
        mDelayTimer = 0x64;
        mPrevAngleY = -0x4000;
        mMinPosY = mPosY - 0xc8000;
    } else {
        mDelayTimer = (u8)mNumToBigIce * 0x14;
        mNumToBigIce = 5;
    }
    return 1;
}
