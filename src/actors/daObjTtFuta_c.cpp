//cpp
/* Recovered translation unit -- ov033/daObjTtFuta_c, Tiny-Huge Island's
 * pounded lid / cover (TT_FUTA).
 *
 * .text span 0x021111a0..0x021113a4, 7 functions, ROM ordinals 0..6, exactly
 * the contiguous linker run build/tu_map.json places here. All 7 are assembled
 * below and config/tu_manifest.d/ov033/daObjTtFuta_c.json names every one,
 * so the run has no hole and the 7 one-function files under src/ that used to
 * own these bytes are deleted by this change.
 *
 * IDENTITY IS THE CARTRIDGE'S. ov033 holds _ZTS13daObjTtFuta_c at
 * 0x02112348; no TinyCover RTTI record exists anywhere -- that was a coined
 * alias for this same class. The table at 0x0211237c carries this class's
 * own _ZTI (0x0211233c) at its typeinfo word. One factory (TT_FUTA) builds
 * this one class.
 *
 * FUNCTION ORDER IS THE ROM'S OWN, under `#pragma defer_codegen off`.
 * Deferred code generation stays off for this TU so mwccarm emits one .text
 * section per function in SOURCE order: the lowest-address ROM function
 * (_ZN13daObjTtFuta_cD1Ev, 0x021111a0) is written FIRST and the highest
 * (_ZN13daObjTtFuta_c13InitResourcesEv, 0x02111310) LAST. Do not reorder.
 *
 * THE DESTRUCTOR IS ONE DEFINITION AND TWO SECTIONS (plus a homeless D2).
 * A single `daObjTtFuta_c::~daObjTtFuta_c()` emits D1 and D0, and with
 * deferred code generation off they land in the cartridge's order, D1 first
 * at 0x021111a0 and D0 at 0x021111e4. The homeless D2 has no ROM symbol and
 * no inbound relocation once the leaf D1/D0 pair is retained, so the
 * manifest licenses it as deadstrip compiler-only output.
 *
 * KEY-FUNCTION SIDE EFFECT: none claimed. ~daObjTtFuta_c is the first
 * non-inline virtual and this TU defines it, but the promotion is text-only:
 * the manifest's compiler_only_output externalizes _ZTV/_ZTI/_ZTS to their
 * canonical public addresses (deadstrip-data) and claims no data or BSS range.
 *
 * The 7 legacy one-function sources this folds are named by the manifest's
 * `legacy_source` fields (history); they are not repeated here.
 */

/* Includes: union of the legacy files', first-seen in ROM-ascending
 * processing order. NOT verified for header ordering constraints (e.g. a
 * common.h-before-X rule) -- watch for new compile errors after this. */
#include "daObjTtFuta_c.h"
#include "decl_common.h"

/* Local shadow declarations carried from the legacy files verbatim.
 * NOT reconciled against real project headers -- check include/*.h for
 * each of these before compiling; a real header should usually win. */
/* shadow struct 'Base' */
struct Base { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void m(int); };

/* shadow struct 'Derived' */
struct Derived { char pad[0xd4]; Base base; };

extern "C" {
extern void _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(unsigned int a, int x, int y, int z);
extern void _ZN5Sound9PlayBank3EjRK7Vector3(unsigned int a, void *v);
extern void _ZN5Event6SetBitEj(unsigned int b);
extern void _ZN13SharedFilePtr7ReleaseEv(void *);
extern int data_ov033_021124c8[];
extern int data_ov033_021124c0[];
extern int data_ov033_02111bfc[];
extern int _ZN10dBgActor_c13IsClsnInRangeE5Fix12IiES1_(void *self, int a, int b);
extern int _ZN4dBgW9IsEnabledEv(void *);
extern void _ZN4dBgW7DisableEv(void *);
extern void* _ZN5Model8LoadFileER13SharedFilePtr(void*);
extern void _ZN9ModelBase7SetFileEP8BMD_Fileii(void*, void*, int, int);
extern void _ZN10dBgActor_c21UpdateModelPosAndRotYEv(void*);
extern void _ZN10dBgActor_c19UpdateClsnPosAndRotEv(void*);
extern void* _ZN7dBgW_Kc8LoadFileER13SharedFilePtr(void*);
extern void _ZN10dBgW_KcMbg7SetFileEP8KCL_FileRK9Matrix4x35Fix12IiEsR10CLPS_Block(void*, void*, void*, int, short, void*);
extern int _ZN5Event6GetBitEj(unsigned int);
}

#pragma defer_codegen off

/* -------------------------------------------------------------------------- */
/* ROM ordinals 0/1 -- _ZN13daObjTtFuta_cD1Ev 0x021111a0, _ZN13daObjTtFuta_cD0Ev 0x021111e4. */
/* ONE definition, two emitted sections.                                          */
/* -------------------------------------------------------------------------- */
// @symbol _ZN13daObjTtFuta_cD1Ev
// @symbol _ZN13daObjTtFuta_cD0Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * Vtable slots 16 (D1) and 17 (D0): one vtable store, the members in reverse,
 * then ~dBgActor_c. This class adds no member with a destructor of its own.
 */
daObjTtFuta_c::~daObjTtFuta_c()
{
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 2 -- _ZN13daObjTtFuta_c15OnGroundPoundedER8dActor_c, 0x0211123c, size 0x44 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN13daObjTtFuta_c15OnGroundPoundedER8dActor_c
/* daObjTtFuta_c::OnGroundPounded -- vtable slot 21, ov033 0x0211123c.
 *
 * Real member function: fBase_c::MarkForDestruction is a real method
 * (include/fBase_c.h), and &mCamSpacePosX (a real named field,
 * include/dActor_c.h) replaces `this + 0x74` as the Vector3 argument.
 * `other`'s own position (mPosX/mPosY/mPosZ) stays a raw pointer read
 * (`(char *)&other + 0x5c`, then `v[0..2]`) rather than three named-field
 * reads: the ROM computes one base address and offsets from it (`add r3,
 * r1, #0x5c` then three `ldr [r3, #N]`), not three independent field
 * loads -- member-access syntax compiled to the latter and cost 4 words. */
void daObjTtFuta_c::OnGroundPounded(dActor_c &other)
{
    int *v = (int *)(((char *)&other) + 0x5c);
    _ZN8Particle6System9NewSimpleEj5Fix12IiES2_S2_(0x28, v[0], v[1], v[2]);
    _ZN5Sound9PlayBank3EjRK7Vector3(0xf, &mCamSpacePosX);
    _ZN5Event6SetBitEj(0xe);
    MarkForDestruction();
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 3 -- _ZN13daObjTtFuta_c16CleanupResourcesEv, 0x02111280, size 0x44 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN13daObjTtFuta_c16CleanupResourcesEv
// recovered name: daObjTtFuta_c_CleanupResources
/* recovered: renamed to Class_Method, declarations from a shared header */
/* recovered: renamed to Class_Method */
/* daObjTtFuta_c::CleanupResources - recovered from vtable slot identity */
s32 daObjTtFuta_c::CleanupResources() {
    void * t = (void *)this;
    if (_ZN4dBgW9IsEnabledEv((char *)t + 0x124)) {
        _ZN4dBgW7DisableEv((char *)t + 0x124);
    }
    _ZN13SharedFilePtr7ReleaseEv(data_ov033_021124c8);
    _ZN13SharedFilePtr7ReleaseEv(data_ov033_021124c0);
    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 4 -- _ZN13daObjTtFuta_c6RenderEv, 0x021112c4, size 0x28 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN13daObjTtFuta_c6RenderEv
// recovered name: daObjTtFuta_c_Render
/* recovered: renamed to Class_Method */
/* daObjTtFuta_c::Render - recovered from vtable slot identity */
s32 daObjTtFuta_c::Render() {
    Derived * d = (Derived *)this; Base *b = &d->base; b->m(0); return 1; }

/* -------------------------------------------------------------------------- */
/* ROM ordinal 5 -- _ZN13daObjTtFuta_c8BehaviorEv, 0x021112ec, size 0x24 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN13daObjTtFuta_c8BehaviorEv
// recovered name: daObjTtFuta_c_Behavior
/* recovered: renamed to Class_Method */
/* daObjTtFuta_c::Behavior - recovered from vtable slot identity */
s32 daObjTtFuta_c::Behavior() {
    void * c = (void *)this;
    _ZN10dBgActor_c13IsClsnInRangeE5Fix12IiES1_(c, 0, 0);
    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 6 -- _ZN13daObjTtFuta_c13InitResourcesEv, 0x02111310, size 0x94 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN13daObjTtFuta_c13InitResourcesEv
// recovered name: daObjTtFuta_c_InitResources
/* recovered: renamed to Class_Method, declarations from a shared header */
/* daObjTtFuta_c::InitResources - recovered from vtable slot identity */
s32 daObjTtFuta_c::InitResources() {
    char * c = (char *)this;
  void *f = _ZN5Model8LoadFileER13SharedFilePtr((void*)data_ov033_021124c8);
  _ZN9ModelBase7SetFileEP8BMD_Fileii(c+0xd4, f, 1, -1);
  _ZN10dBgActor_c21UpdateModelPosAndRotYEv(c);
  _ZN10dBgActor_c19UpdateClsnPosAndRotEv(c);
  void *k = _ZN7dBgW_Kc8LoadFileER13SharedFilePtr((void*)data_ov033_021124c0);
  _ZN10dBgW_KcMbg7SetFileEP8KCL_FileRK9Matrix4x35Fix12IiEsR10CLPS_Block(c+0x124, k, c+0x2ec, 0x199, *(short*)(c+0x8e), data_ov033_02111bfc);
  return _ZN5Event6GetBitEj(0xe) == 0;
}
