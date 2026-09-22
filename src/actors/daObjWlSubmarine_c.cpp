//cpp
/* Recovered translation unit -- ov026/daObjWlSubmarine_c, Wet-Dry World's
 * submarine platform.
 *
 * .text span 0x021118b8..0x02111a70, 5 functions, ROM ordinals 0..4, exactly
 * the contiguous linker run build/tu_map.json places here. All 5 are assembled
 * below and config/tu_manifest.d/ov026/daObjWlSubmarine_c.json names every one,
 * so the run has no hole and the 5 one-function files under src/ that used to
 * own these bytes are deleted by this change.
 *
 * IDENTITY IS THE CARTRIDGE'S. ov026 holds _ZTS18daObjWlSubmarine_c at
 * 0x02113c30; no Submarine RTTI record exists anywhere -- that was a coined
 * alias for this same class. The table at 0x02113c6c carries this class's
 * own _ZTI (0x02113c24) at its typeinfo word. One factory (WL_SUBMARINE)
 * builds this one class.
 *
 * FUNCTION ORDER IS THE ROM'S OWN, under `#pragma defer_codegen off`.
 * Deferred code generation stays off for this TU so mwccarm emits one .text
 * section per function in SOURCE order: the lowest-address ROM function
 * (_ZN18daObjWlSubmarine_cD1Ev, 0x021118b8) is written FIRST and the highest
 * (_ZN18daObjWlSubmarine_c13InitResourcesEv, 0x021119c0) LAST. Do not reorder.
 *
 * THE DESTRUCTOR IS ONE DEFINITION AND TWO SECTIONS (plus a homeless D2).
 * A single `daObjWlSubmarine_c::~daObjWlSubmarine_c()` emits D1 and D0, and
 * with deferred code generation off they land in the cartridge's order, D1
 * first at 0x021118b8 and D0 at 0x021118fc. The homeless D2 has no ROM symbol
 * and no inbound relocation once the leaf D1/D0 pair is retained, so the
 * manifest licenses it as deadstrip compiler-only output. It stores TWO
 * vptrs -- its own, then dBgActor_c's (inlined) -- then destroys dBgActor_c's
 * Model and dBgW_KcMbg and chains to dActor_c.
 *
 * KEY-FUNCTION SIDE EFFECT: none claimed. ~daObjWlSubmarine_c is the first
 * non-inline virtual and this TU defines it, but the promotion is text-only:
 * the manifest's compiler_only_output externalizes _ZTV/_ZTI/_ZTS to their
 * canonical public addresses (deadstrip-data) and claims no data or BSS range.
 *
 * WHAT THE PROMOTION CARRIES OVER, and nothing else was changed:
 *   1. The destructor is one definition with two stacked markers -- writing
 *      them as two definitions is an `object redefined` error.
 *   2. Local shadow structs (Base/Derived) stay as the leftover shards
 *      recovered them.
 *   3. SharedFilePtr BSS aliases Submarine_ClsnFile / Submarine_ModelFile
 *      remain (no --with-derived rename); InitResources also reads the same
 *      homes via their data_ov026_* labels from decl_common.h.
 *
 * The 5 legacy one-function sources this folds are named by the manifest's
 * `legacy_source` fields (history); they are not repeated here.
 */

/* Includes: union of the legacy files', first-seen in ROM-ascending
 * processing order. NOT verified for header ordering constraints (e.g. a
 * common.h-before-X rule) -- watch for new compile errors after this. */
#include "daObjWlSubmarine_c.h"
#include "decl_common.h"

/* Local shadow declarations carried from the legacy files verbatim.
 * NOT reconciled against real project headers -- check include/*.h for
 * each of these before compiling; a real header should usually win. */
/* shadow struct 'Base' */
struct Base { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void m(int); };

/* shadow struct 'Derived' */
struct Derived { char pad[0xd4]; Base base; };

extern "C" {
extern int Submarine_ClsnFile[];
extern void _ZN13SharedFilePtr7ReleaseEv(void *);
extern int Submarine_ModelFile[];
extern int _ZN5Model8LoadFileER13SharedFilePtr(void *);
extern void _ZN9ModelBase7SetFileEP8BMD_Fileii(void *, int, int, int);
extern void _ZN10dBgActor_c21UpdateModelPosAndRotYEv(void *);
extern void _ZN10dBgActor_c19UpdateClsnPosAndRotEv(void *);
extern int _ZN7dBgW_Kc8LoadFileER13SharedFilePtr(void *);
extern void _ZN10dBgW_KcMbg7SetFileEP8KCL_FileRK9Matrix4x35Fix12IiEsR10CLPS_Block(void *, int, void *, int, int, void *);
extern void _ZN4dBgW6EnableEP8dActor_c(void *, void *);
extern char data_0209caa0[];
}

#pragma defer_codegen off

/* -------------------------------------------------------------------------- */
/* ROM ordinals 0/1 -- _ZN18daObjWlSubmarine_cD1Ev 0x021118b8, _ZN18daObjWlSubmarine_cD0Ev 0x021118fc. */
/* ONE definition, two emitted sections.                                          */
/* -------------------------------------------------------------------------- */
// @symbol _ZN18daObjWlSubmarine_cD1Ev
// @symbol _ZN18daObjWlSubmarine_cD0Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * Two vtable stores and three destructor calls, every one a consequence of
 * `struct daObjWlSubmarine_c : dBgActor_c`: its own vptr, then dBgActor_c's --
 * inlined, because dBgActor_c's destructor is defined in its class body -- then
 * dBgActor_c's Model and dBgW_KcMbg, then dActor_c. This class adds no
 * member with a destructor of its own.
 */
daObjWlSubmarine_c::~daObjWlSubmarine_c()
{
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 2 -- _ZN18daObjWlSubmarine_c16CleanupResourcesEv, 0x02111954, size 0x44 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN18daObjWlSubmarine_c16CleanupResourcesEv
// recovered name: daObjWlSubmarine_c_CleanupResources
/* recovered: renamed to Class_Method, declarations from a shared header */
/* recovered: renamed to Class_Method */
/* daObjWlSubmarine_c::CleanupResources - recovered from vtable slot identity */
s32 daObjWlSubmarine_c::CleanupResources() {
    void * t = (void *)this;
    if (_ZN4dBgW9IsEnabledEv((char *)t + 0x124)) {
        _ZN4dBgW7DisableEv((char *)t + 0x124);
    }
    _ZN13SharedFilePtr7ReleaseEv(Submarine_ModelFile);
    _ZN13SharedFilePtr7ReleaseEv(Submarine_ClsnFile);
    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 3 -- _ZN18daObjWlSubmarine_c6RenderEv, 0x02111998, size 0x28 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN18daObjWlSubmarine_c6RenderEv
// recovered name: daObjWlSubmarine_c_Render
/* recovered: renamed to Class_Method */
/* daObjWlSubmarine_c::Render - recovered from vtable slot identity */
s32 daObjWlSubmarine_c::Render() {
    Derived * d = (Derived *)this; Base *b = &d->base; b->m(0); return 1; }

/* -------------------------------------------------------------------------- */
/* ROM ordinal 4 -- _ZN18daObjWlSubmarine_c13InitResourcesEv, 0x021119c0, size 0xb0 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN18daObjWlSubmarine_c13InitResourcesEv
// recovered name: daObjWlSubmarine_c_InitResources
/* recovered: renamed to Class_Method, declarations from a shared header */
/* recovered: renamed to Class_Method */
/* daObjWlSubmarine_c::InitResources - recovered from vtable slot identity */
s32 daObjWlSubmarine_c::InitResources() {
    char * c = (char *)this;
  void *m = (void*)_ZN5Model8LoadFileER13SharedFilePtr(data_ov026_02113ee4);
  _ZN9ModelBase7SetFileEP8BMD_Fileii(c+0xd4,(int)m,1,-1);
  _ZN10dBgActor_c21UpdateModelPosAndRotYEv(c);
  _ZN10dBgActor_c19UpdateClsnPosAndRotEv(c);
  {
    void *k = (void*)_ZN7dBgW_Kc8LoadFileER13SharedFilePtr(data_ov026_02113edc);
    _ZN10dBgW_KcMbg7SetFileEP8KCL_FileRK9Matrix4x35Fix12IiEsR10CLPS_Block(
        c+0x124,(int)k,c+0x2ec,0x199,*(short*)(c+0x8e),(void*)data_ov026_02112fd4);
  }
  if(*(int*)(data_0209caa0+4) & 0x204) return 0;
  _ZN4dBgW6EnableEP8dActor_c(c+0x124,c);
  return 1;
}
