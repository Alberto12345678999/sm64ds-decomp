#ifndef SCUTTLEBUG_H
#define SCUTTLEBUG_H

#include "types.h"
#include "dActor_c.h"
#include "ModelAnim.h"
#include "ShadowModel.h"
#include "dCcAc_c.h"
#include "dBgCh_Actr.h"

/* TWO WITNESSES, and they close on each other:
 *
 *   daSpd_c_classInit  fBase_c::operator new(940 = 0x3ac), dActor_c::dActor_c(), stores _ZTV10Scuttlebug,
 *                 then the four members below in this order.
 *   ~Scuttlebug   the same members destroyed in reverse, then ~dActor_c.
 *
 * SIZE 0x3ac is the factory's own literal, and the trailing byte fields close exactly on it.
 *
 * THE VTABLE was diffed slot by slot against _ZTV8dActor_c (relocs.txt, ov071). Only the
 * slots declared below differ; every other slot holds the base's own word and is inherited,
 * so it is deliberately not redeclared here.
 *
 * THE FACTORY daSpd_c_classInit (historical alias Scuttlebug_Spawn) constructs the
 * object for the SPIDER registry profile at 0x02122c08.
 */

/* The ROM's RTTI name for this class is daSpd_c (_ZTI7daSpd_c), while the
 * established function-symbol view spells its methods as Scuttlebug.  Scuttlebug
 * is the compiler-facing compatibility name; config/arm9/overlays/ov071/symbols.txt
 * deliberately aliases its vtable view (_ZTV10Scuttlebug) to the cartridge's
 * _ZTV7daSpd_c address.  The alias is vtable-only: _ZTS/_ZTI are named under the
 * cartridge spelling alone, so a TU that owns the key function emits
 * _ZTS10Scuttlebug and _ZTI10Scuttlebug with no home in the ROM.  That is
 * survivable on the text-only route and fatal to an intact-object one. */
struct Scuttlebug : dActor_c {
    /* PROVEN LIVE, not padding: InitResources writes it whole
       (`str r0,[r4,#0xd0]` at 0x02120528) and two more functions of the run read
       and write it.  A word slot only ever moved whole, so the signedness is not
       observable and the name is a placeholder. */
    u32 unk_0d0;                             /* 0x0d0 */
    ModelAnim mModelAnim;                    /* 0x0d4 */
    ShadowModel mShadowModel;                /* 0x138 */
    dCcAc_c mdCcAc_c;  /* 0x160 */
    dBgCh_Actr mWithMeshClsn;              /* 0x194 */
    /* NOT dead space -- thirteen live offsets sit inside this run and are still
       reached by raw this-relative arithmetic from the unconverted members:
       0x350 and 0x390 and 0x3a0 have their addresses taken, 0x380 holds the
       pointer into the nine-entry state table at ov071:0x02122fa8 that
       Scuttlebug_SetState writes and both dispatch thunks read back, and 0x39c
       is the hottest own word in the class after it (eleven functions).  Kept as
       one pad until the members that use them are named, because splitting it
       would invite a field-address CSE that moves bytes. */
    u8  pad_350[0x58];
    /* Counted down once per frame at the top of Behavior, which passes &mTimer to
       DecIfAbove0_Short -- a short* helper, so the slot is a HALFWORD and not the
       u8 the generated header typed it.  Behavior discards the result, so what
       expiring means is up to a state handler nobody has read.
       [_ZN10Scuttlebug8BehaviorEv.cpp] */
    s16 mTimer;                             /* 0x3a8 */
    /* Its own live byte, not the first of mTimer's padding: func_ov071_0211f498
       reads and writes it, InitResources writes it (`strb r2,[r4,#0x3aa]` at
       0x02120500) and OnTurnIntoEgg reads it twice and writes it once. */
    u8  unk_3aa;                            /* 0x3aa */
    u8  pad_3ab[0x1];

    /* DEFINED INLINE, and declared ahead of every other virtual. The cartridge
       orders the pair D1 (0x0211f000) then D0 (0x0211f048) with no D2 anywhere
       in ov071, which is exactly what mwccarm 2004/b56 emits for an inline
       destructor; an out-of-line one emits D2, D0, D1 plus a homeless D2.
       Declaring it inline also moves the KEY FUNCTION down to OnYoshiTryEat,
       the first non-inline virtual this class declares, which sits inside the
       licensed run at 0x0211f0a4 and so anchors _ZTV10Scuttlebug here. */
    virtual ~Scuttlebug() {}          /* slots 16 (D1), 17 (D0) */

    virtual int   OnYoshiTryEat();               /* slot 18 */
    virtual int   OnTurnIntoEgg(Player &player); /* slot 19 */
    virtual int   OnAimedAtWithEgg();            /* slot 29 */

    int Behavior();
    int CleanupResources();                  /* slot  3 */
    int InitResources();
    void OnPendingDestroy();                 /* slot 12 -- empty body in the ROM */
    int Render();
};

typedef char Scuttlebug_size_must_be_0x3ac[sizeof(Scuttlebug) == 0x3ac ? 1 : -1];

/* OnYoshiTryEat, the key function, owns the compiler-emitted definition of
 * this vtable. daSpd_c_classInit must store its public address point directly
 * because the measured factory calls fBase_c::operator new rather than a
 * natural new; this declaration only exposes that compiler-owned address to
 * the factory seam. */
extern int _ZTV10Scuttlebug[];

#endif /* SCUTTLEBUG_H */
