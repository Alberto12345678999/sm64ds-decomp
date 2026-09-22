//cpp
/* Recovered translation unit -- ov033/daObjTtWater_c, Tiny-Huge Island's
 * drainable water pool (TT_WATER).
 *
 * .text span 0x021113d4..0x02111690, 6 functions, ROM ordinals 0..5, exactly
 * the contiguous linker run build/tu_map.json places here. All 6 are assembled
 * below and config/tu_manifest.d/ov033/daObjTtWater_c.json names every one,
 * so the run has no hole and the 6 one-function files under src/ that used to
 * own these bytes are deleted by this change.
 *
 * IDENTITY IS THE CARTRIDGE'S. ov033 holds _ZTS14daObjTtWater_c at
 * 0x02112408; no TinyWater RTTI record exists anywhere -- that was a coined
 * alias for this same class. The table at 0x02112440 carries this class's
 * own _ZTI (0x021123fc) at its typeinfo word. One factory (TT_WATER) builds
 * this one class.
 *
 * FUNCTION ORDER IS THE ROM'S OWN, under `#pragma defer_codegen off`.
 * Deferred code generation stays off for this TU so mwccarm emits one .text
 * section per function in SOURCE order: the lowest-address ROM function
 * (_ZN14daObjTtWater_cD1Ev, 0x021113d4) is written FIRST and the highest
 * (_ZN14daObjTtWater_c13InitResourcesEv, 0x021115bc) LAST. Do not reorder.
 *
 * THE DESTRUCTOR IS ONE DEFINITION AND TWO SECTIONS (plus a homeless D2).
 * A single `daObjTtWater_c::~daObjTtWater_c()` emits D1 and D0, and with
 * deferred code generation off they land in the cartridge's order, D1 first
 * at 0x021113d4 and D0 at 0x02111420. The homeless D2 has no ROM symbol and
 * no inbound relocation once the leaf D1/D0 pair is retained, so the
 * manifest licenses it as deadstrip compiler-only output.
 *
 * KEY-FUNCTION SIDE EFFECT: none claimed. ~daObjTtWater_c is the first
 * non-inline virtual and this TU defines it, but the promotion is text-only:
 * the manifest's compiler_only_output externalizes _ZTV/_ZTI/_ZTS to their
 * canonical public addresses (deadstrip-data) and claims no data or BSS range.
 *
 * The 6 legacy one-function sources this folds are named by the manifest's
 * `legacy_source` fields (history); they are not repeated here.
 */

/* Includes: union of the legacy files', first-seen in ROM-ascending
 * processing order. NOT verified for header ordering constraints (e.g. a
 * common.h-before-X rule) -- watch for new compile errors after this. */
#include "daObjTtWater_c.h"
#include "decl_common.h"
#include "SharedFilePtr.h"
#include "dBgW.h"
#include "TextureTransformer.h"
#include "Sound.h"

/* Local shadow declarations carried from the legacy files verbatim.
 * NOT reconciled against real project headers -- check include/*.h for
 * each of these before compiling; a real header should usually win. */
/* shadow struct 'Sub' */
struct Sub { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void m(int); };

/* shadow struct 'Base' */
struct Base { char pad[0xd4]; Sub sub; };

extern "C" {
extern int data_ov033_021124f0[];
int  _ZN5Event6GetBitEj(u32 bit);
void _ZN6dMap_c19UpdateLevelSpecificEv(void);
extern void* _ZN5Model8LoadFileER13SharedFilePtr(void* fp);
extern void _ZN9ModelBase7SetFileEP8BMD_Fileii(void* thiz, void* f, int a, int b);
extern void _ZN18TextureTransformer7PrepareER8BMD_FileR8BTA_File(void* bmd, void* bta);
extern void _ZN18TextureTransformer7SetFileER8BTA_Filei5Fix12IiEj(void* thiz, void* bta, int a, int b, unsigned int e);
extern void _ZN10dBgActor_c21UpdateModelPosAndRotYEv(void* thiz);
extern void _ZN10dBgActor_c19UpdateClsnPosAndRotEv(void* thiz);
extern void* _ZN7dBgW_Kc8LoadFileER13SharedFilePtr(void* fp);
extern void _ZN10dBgW_KcMbg7SetFileEP8KCL_FileRK9Matrix4x35Fix12IiEsR10CLPS_Block(void* thiz, void* kcl, void* mtx, int fix, short s, void* clps);
/* TUBUILD CONFLICT -- alternate declaration of _ZN5Event6GetBitEj, from the legacy file for _ZN14daObjTtWater_c13InitResourcesEv, NOT applied: extern int _ZN5Event6GetBitEj(unsigned int n); */
}

#pragma defer_codegen off

/* -------------------------------------------------------------------------- */
/* ROM ordinals 0/1 -- _ZN14daObjTtWater_cD1Ev 0x021113d4, _ZN14daObjTtWater_cD0Ev 0x02111420. */
/* ONE definition, two emitted sections.                                          */
/* -------------------------------------------------------------------------- */
// @symbol _ZN14daObjTtWater_cD1Ev
// @symbol _ZN14daObjTtWater_cD0Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * Two vtable stores and three destructor calls, every one a consequence of
 * `struct daObjTtWater_c : dBgActor_c`: its own vptr, then dBgActor_c's -- inlined,
 * because dBgActor_c's destructor is defined in its class body -- then
 * dBgActor_c's Model and dBgW_KcMbg, then dActor_c. This class adds no
 * member with a destructor of its own.
 */
daObjTtWater_c::~daObjTtWater_c()
{
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 2 -- _ZN14daObjTtWater_c16CleanupResourcesEv, 0x02111480, size 0x44 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN14daObjTtWater_c16CleanupResourcesEv
/* recovered: named members + shared header, real C++ method, declarations from a shared header */
/* recovered: named members + shared header, real C++ method */
int daObjTtWater_c::CleanupResources()
{
    if (((dBgW *)((char *)&(*(u8 *)&mMeshCollider)))->IsEnabled()) {
        ((dBgW *)((char *)&(*(u8 *)&mMeshCollider)))->Disable();
    }
    ((SharedFilePtr *)(data_ov033_021124f0))->Release();
    ((SharedFilePtr *)(data_ov033_021124e8))->Release();
    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 3 -- _ZN14daObjTtWater_c6RenderEv, 0x021114c4, size 0x34 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN14daObjTtWater_c6RenderEv
/* recovered: named members + shared header, real C++ method */
int daObjTtWater_c::Render()
{
 ((TextureTransformer *)((char *)((Base *)this) + 0x320))->Update(*(ModelComponents *)((char *)((Base *)this) + 0xdc)); Sub *b = &((Base *)this)->sub; b->m(0); return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 4 -- _ZN14daObjTtWater_c8BehaviorEv, 0x021114f8, size 0xc4 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN14daObjTtWater_c8BehaviorEv
/* daObjTtWater_c::Behavior -- once event bit 0xe is set, drain the pool: sink one
 * unit a frame while looping the drain sound, and when the surface reaches
 * mMinPosY play the secret jingle and destroy the actor once it finishes.
 *
 * Sound and Event have no headers in this tree, so those two stay extern-C
 * mangled free functions. dMap_c::UpdateLevelSpecific is declared in
 * include/dMap_c.h since #2899; the call stays mangled here to keep the
 * text-verified shadow's instruction selection (member spelling needs the
 * build box). Animation::Advance and fBase_c::MarkForDestruction are
 * declared, and are reached as members.
 */
int daObjTtWater_c::Behavior()
{
    if (_ZN5Event6GetBitEj(0xe)) {
        if (mPosY <= mMinPosY) {
            if (Sound::PlaySecretSound((dActor_c *)this, (u16 *)&mSoundTimer))
                MarkForDestruction();
        } else {
            mPosY -= 0x1000;
            mSoundID = Sound::PlayLong(mSoundID, 3, 0x96, *(const Vector3 *)&mCamSpacePosX, 0);
            if (mPosY <= mMinPosY) {
                mPosY = mMinPosY;
                _ZN6dMap_c19UpdateLevelSpecificEv();
            }
        }
    }
    mTextureTransformer.speed = 0x1000;
    mTextureTransformer.Advance();
    UpdateModelPosAndRotY();
    UpdateClsnPosAndRot();
    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 5 -- _ZN14daObjTtWater_c13InitResourcesEv, 0x021115bc, size 0xd4 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN14daObjTtWater_c13InitResourcesEv
/* recovered: named members + shared header, real C++ method, declarations from a shared header */
/* recovered: named members + shared header, real C++ method */
int daObjTtWater_c::InitResources()
{
    void* m = _ZN5Model8LoadFileER13SharedFilePtr(data_ov033_021124f0);
    _ZN9ModelBase7SetFileEP8BMD_Fileii(((char*)this) + 0xd4, m, 1, 0x14);
    _ZN18TextureTransformer7PrepareER8BMD_FileR8BTA_File(*(void**)((char*)data_ov033_021124f0 + 4), data_ov033_02111bc8);
    _ZN18TextureTransformer7SetFileER8BTA_Filei5Fix12IiEj(((char*)this) + 0x320, data_ov033_02111bc8, 0, 0x1000, 0);
    _ZN10dBgActor_c21UpdateModelPosAndRotYEv(((char*)this));
    _ZN10dBgActor_c19UpdateClsnPosAndRotEv(((char*)this));
    void* mc = _ZN7dBgW_Kc8LoadFileER13SharedFilePtr(data_ov033_021124e8);
    _ZN10dBgW_KcMbg7SetFileEP8KCL_FileRK9Matrix4x35Fix12IiEsR10CLPS_Block(
        ((char*)this) + 0x124, mc, ((char*)this) + 0x2ec, 0x1000, mAngleY, data_ov033_02111c1c);
    ((dBgW *)(((char*)this) + 0x124))->Enable((dActor_c *)(((char*)this)));
    mMinPosY = mPosY - 0x3c000;
    return _ZN5Event6GetBitEj(0xe) == 0;
}
