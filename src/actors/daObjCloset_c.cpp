//cpp
/* Recovered translation unit -- ov058/daObjCloset_c, the PL_CLOSET cupboard.
 *
 * .text span 0x021111a0..0x02111688, 5 functions, ROM ordinals 0..4, exactly
 * the contiguous linker run build/tu_map.json places here. All 5 are assembled
 * below and config/tu_manifest.d/ov058/daObjCloset_c.json names every one, so
 * the run has no hole and the 5 one-function files under src/ that used to own
 * these bytes are deleted by this change.
 *
 * IDENTITY IS THE CARTRIDGE'S. ov058 holds _ZTS13daObjCloset_c at 0x02111a3c;
 * _ZTI13daObjCloset_c at 0x02111a30 is the matching typeinfo. No RecRoomCupboard
 * RTTI record exists anywhere -- that was a coined alias for this same class.
 * The table at 0x02111a70 carries this class's own _ZTI (0x02111a30) at its
 * typeinfo word (reloc from 0x02111a6c). One factory (PL_CLOSET) builds this
 * one class.
 *
 * FUNCTION ORDER IS THE ROM'S OWN, under `#pragma defer_codegen off`.
 * Deferred code generation stays off for this TU so mwccarm emits one .text
 * section per function in SOURCE order: the lowest-address ROM function
 * (_ZN13daObjCloset_cD1Ev, 0x021111a0) is written FIRST and the highest
 * (_ZN13daObjCloset_c13InitResourcesEv, 0x0211161c) LAST. Do not reorder.
 *
 * THE DESTRUCTOR IS ONE DEFINITION AND TWO SECTIONS (plus a homeless D2).
 * A single `daObjCloset_c::~daObjCloset_c()` emits D1 and D0, and with deferred
 * code generation off they land in the cartridge's order, D1 first at
 * 0x021111a0 and D0 at 0x021111e0. The homeless D2 has no ROM symbol and no
 * inbound relocation once the leaf D1/D0 pair is retained, so the manifest
 * licenses it as deadstrip compiler-only output. Declaring
 * `dCcAcPos_c mColliders[5]` and deriving from dActor_c is what emits the
 * vptr store, the five-element array destroy at +0xd4, and the base step.
 *
 * KEY-FUNCTION SIDE EFFECT: none claimed. ~daObjCloset_c is the first
 * non-inline virtual and this TU defines it, but the promotion is text-only:
 * the manifest's compiler_only_output externalizes _ZTV/_ZTI/_ZTS to their
 * canonical public addresses (deadstrip-data) and claims no data or BSS range.
 * The chain is dActor_c (self + dActor_c + dBase_c + fBase_c), 2*4+1 data rows.
 *
 * The legacy Behavior shard's `#pragma opt_strength_reduction off` was left
 * out of the text-verified shadow: all five members matched without it. It is
 * not reintroduced here. RecRoomCupboard_Spawn stays the historical alias in
 * comments; class_rename was run without --with-derived.
 *
 * The 5 legacy one-function sources this folds are named by the manifest's
 * `legacy_source` fields (history); they are not repeated here.
 */

/* Includes: union of the legacy files', first-seen in ROM-ascending
 * processing order. NOT verified for header ordering constraints (e.g. a
 * common.h-before-X rule) -- watch for new compile errors after this. */
#include "daObjCloset_c.h"

/* Local shadow declarations carried from the legacy files verbatim.
 * NOT reconciled against real project headers -- check include/*.h for
 * each of these before compiling; a real header should usually win. */
/* shadow typedef 's64' */
typedef long long s64;

/* shadow struct 'Vec3Raw' */
struct Vec3Raw { int x, y, z; };

extern "C" {
int _ZN6Player12GetTalkStateEv(void* self);
int _Z14ApproachLinearRsss(short* cur, short target, short step);
void _ZN7Message11PrepareTalkEv(void);
void _ZN6Player12ShowMessage2ER7fBase_cjPK7Vector3hh(void* self, void* actor, unsigned int msg, const void* vec, unsigned int a, unsigned int b);
void func_02012790(int a);
int _ZN6Player18HasFinishedTalkingEv(void* self);
void _ZN7Message7EndTalkEv(void);
void _ZN7Message13DisplaySavingEt(unsigned short a);
void StartMinigameMenu(unsigned char a);
void* _ZN8dActor_c10FindWithIDEj(unsigned int id);
short Vec3_HorzAngle(const struct Vec3Raw* a, const struct Vec3Raw* b);
int AngleDiff(int a, int b);
int _ZN6Player9StartTalkER7fBase_cb(void* actor, void* self, int b);
void _ZN5dCc_c5ClearEv(void* self);
void _ZN5dCc_c6UpdateEv(void* self);
extern s16 data_02082214[];
extern u8 data_0209d684;
extern u8 data_0209d660;
extern "C" void _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj( void *self, void *actor, void *offset, int radius, int height, unsigned int flags, unsigned int vulnFlags);
}

#pragma defer_codegen off

/* -------------------------------------------------------------------------- */
/* ROM ordinals 0/1 -- _ZN13daObjCloset_cD1Ev 0x021111a0, _ZN13daObjCloset_cD0Ev 0x021111e0. */
/* ONE definition, two emitted sections.                                          */
/* -------------------------------------------------------------------------- */
// @symbol _ZN13daObjCloset_cD1Ev
// @symbol _ZN13daObjCloset_cD0Ev
/* recovered: real C++ destructor -- the compiler emits the whole body.
 * Vtable slots 16 and 17: one vtable store, the five dCcAcPos_c members in
 * reverse, then ~dActor_c. */
daObjCloset_c::~daObjCloset_c()
{
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 2 -- _ZN13daObjCloset_c16CleanupResourcesEv, 0x02111234, size 0x8 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN13daObjCloset_c16CleanupResourcesEv
/* recovered: real class form -- the compiler spells the mangled name. */
s32 daObjCloset_c::CleanupResources()
{
    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 3 -- _ZN13daObjCloset_c8BehaviorEv, 0x0211123c, size 0x3e0 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN13daObjCloset_c8BehaviorEv
/* recovered: real class form -- the compiler spells the mangled name. */
/* The scratch position triples below are deliberately NOT include/types.h's
   Vector3: that one declares an (empty) destructor, because the ROM destroys
   arrays of it, and the five locals here grow the frame by 0x10 bytes under a
   non-POD type. A file-local POD triple is what the ROM's frame says was
   here. */
s32 daObjCloset_c::Behavior()
{
    volatile Vec3Raw v1, v2, v3;
    Vec3Raw apos;
    volatile Vec3Raw pos;
    char* target = (char*)mTalkingPlayer;

    if (target) {
        v1.x = *(volatile s32*)&mPosX;
        v1.y = *(volatile s32*)&mPosY;
        v1.z = *(volatile s32*)&mPosZ;
        v2.x = mPosX;
        v2.y = mPosY;
        v2.z = mPosZ;
        v2.x = mPosX + (int)(((s64)0x5a000 * data_02082214[(*(volatile u16*)&mAngleY >> 4) * 2] + 0x800) >> 12);
        v2.z = mPosZ + (int)(((s64)0x5a000 * data_02082214[(*(volatile u16*)&mAngleY >> 4) * 2 + 1] + 0x800) >> 12);
        {
            struct Vec3Raw* tp = (struct Vec3Raw*)((int)target + 0x5c);
            v3.x = tp->x;
            v3.y = tp->y;
            v3.z = tp->z;
        }

        switch (_ZN6Player12GetTalkStateEv(target)) {
        case 0: {
            short cur = (short)(mAngleY + 0x8000);
            if (_Z14ApproachLinearRsss((short*)(target + 0x8e), cur, 0x800) != 0) {
                mMessageID = 0xb09;
                _ZN7Message11PrepareTalkEv();
                _ZN6Player12ShowMessage2ER7fBase_cjPK7Vector3hh(
                    target, this, (s16)mMessageID, 0, 1, 0);
            }
            break;
        }
        case 1:
            break;
        default: {
            u8 st = data_0209d684;
            if (mMessageID == 0xb09) {
                if (st == 1) {
                    if (mSoundStarted == 0) {
                        func_02012790(0x98);
                        mSoundStarted = 1;
                    }
                    if (_ZN6Player18HasFinishedTalkingEv(target) != 0) {
                        _ZN7Message7EndTalkEv();
                        mTalkingPlayer = 0;
                        mSoundStarted = 0;
                    }
                } else if (st == 2) {
                    if (mSoundStarted == 0) {
                        func_02012790(0x97);
                        mSoundStarted = 1;
                    }
                    _ZN7Message13DisplaySavingEt(0x295);
                } else {
                    if (data_0209d660 == 0) {
                        StartMinigameMenu(1);
                        mTalkingPlayer = 0;
                        mSoundStarted = 0;
                    }
                }
            } else {
                mTalkingPlayer = 0;
                mSoundStarted = 0;
            }
            break;
        }
        }
    } else {
        int i;
        for (i = 0; i < 5; i++) {
            if (mColliders[i].hitFlags & 0x8000000) {
                u32 id = mColliders[i].otherOwner;
                char* actor = (char*)_ZN8dActor_c10FindWithIDEj(id);
                if (actor) {
                    int isMatch = (*(u16*)(actor + 0xc) == 0xbf);
                    if (isMatch != false) {
                        struct Vec3Raw* ap = (struct Vec3Raw*)((int)actor + 0x5c);
                        short ang;
                        int diff;
                        apos.x = ap->x;
                        apos.y = ap->y;
                        apos.z = ap->z;
                        ang = Vec3_HorzAngle((struct Vec3Raw*)&mPosX, &apos);
                        diff = AngleDiff(ang, mAngleY);
                        if (diff < 0x4000) {
                            if (_ZN6Player9StartTalkER7fBase_cb(actor, this, 0) != 0) {
                                mTalkingPlayer = (Player*)actor;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    {
        int j;
        dCcAcPos_c* cyl = mColliders;
        for (j = 0; j < 5; j++) {
            pos.x = mPosX;
            pos.y = mPosY;
            pos.z = mPosZ;
            {
                int distFixed = ((2 - j) * 100) << 12;
                int idx = (unsigned short)(short)(mAngleY + 0x4000) >> 4;
                s16 cosv = data_02082214[idx * 2];
                s16 sinv = data_02082214[idx * 2 + 1];
                int offX = (int)(((s64)distFixed * cosv + 0x800) >> 12);
                int offZ = (int)(((s64)distFixed * sinv + 0x800) >> 12);
                int newX = mPosX + offX;
                int newZ = mPosZ + offZ;
                pos.x = newX;
                pos.z = newZ;
                mColliders[j].pos.x = newX;
                mColliders[j].pos.y = pos.y;
                mColliders[j].pos.z = pos.z;
            }
            _ZN5dCc_c5ClearEv(cyl);
            _ZN5dCc_c6UpdateEv(cyl);
            cyl++;
        }
    }

    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 4 -- _ZN13daObjCloset_c13InitResourcesEv, 0x0211161c, size 0x6c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN13daObjCloset_c13InitResourcesEv
/* recovered: real class form -- the compiler spells the mangled name.
 *
 * dCcAcPos_c::Init is CALLED, not defined, through its mangled name with int
 * parameters: its ROM name carries by-value Fix12<int> arguments, which
 * mwccarm passes differently from a plain int at the call site, so spelling
 * the true types breaks the byte match. Every other InitResources in the tree
 * that touches this function does the same (notes/mwccarm-codegen.md 6az).
 */
s32 daObjCloset_c::InitResources()
{
    int i;
    dCcAcPos_c *collider = mColliders;
    for (i = 0; i < 5; i++) {
        _ZN10dCcAcPos_c4InitEP8dActor_cRK7Vector35Fix12IiES6_jj(
            collider, this, &mPosX, 0x6e000, 0x8c000, 0x4800002, 0);
        collider++;
    }
    return 1;
}
