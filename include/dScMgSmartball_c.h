/* class dScMgSmartball_c, real ROM name confirmed by tools/rtti_extract.py:
 * dScMgSmartball_c : dScMgBase_c, single edge, offset 0 (build/rtti.json).
 * Its own vtable is ov006:0x0213eefc; the RTTI pointer one word below it is
 * _ZTI16dScMgSmartball_c. The LAST direct child of dScMgBase_c to become a
 * real class -- with this, every RTTI descendant of dScMgBase_c is one.
 *
 * A DIRECT child, with no intermediate: its own D1 stores this class's
 * vtable, destroys the four arrays, and calls _ZN11dScMgBase_cD2Ev
 * straight away -- no second vptr store, which is what an inlined
 * intermediate base's destructor would have left behind.
 *
 * SIZE 0x629c, from dScMgSmartball_c_classInit's own
 * `_ZN7fBase_cnwEj(0x629c)`, and the last array closes EXACTLY on it:
 * 0x599c + 0x40 * 0x24 = 0x629c. The coined English _Spawn name
 * MgBingoBallSlotsShot_Spawn is already attributed and is retained as a
 * historical alias, the same convention as dScMgCard_c_classInit
 * (historical alias MgPicturePoker_Spawn) for dScMgCard_c.
 *
 * FACTORY AND DESTRUCTOR AGREE MEMBER FOR MEMBER, in exact reverse order:
 * built 0x47c8, 0x4854, 0x48d4, 0x599c; destroyed 0x599c, 0x48d4, 0x4854,
 * 0x47c8. Nothing is left over either way. Three of the four share an
 * element ctor/dtor pair (func_0203d738 / NullDestructor_0203d47c) so they
 * are the same element type as each other; mSparks's is its own
 * (SmartballObj_ElemCtor / SmartballObj_ElemDtor).
 *
 * THE REST OF THE CLASS IS NOW MODELLED from its access sites: the
 * object counts and tables, the score popup queue, the dust puffs, the two
 * decompressed BG maps, the round state and the result tallies. Each field
 * below carries its evidence. mArray1..3 stay byte arrays: their element is
 * an 8-byte pair with a constructor and destructor, and a member of such a
 * type changes this class's codegen.
 *
 * So: the four arrays below are evidenced by two witnesses each and the
 * size is evidenced by a third.
 *
 * THE DESTRUCTOR IS NOT DEFINED INLINE -- a leaf, no RTTI descendants of
 * its own. Its definition in src/minigames/d_s_mg_smartball.cpp emits both
 * destructor variants. No separate operator delete is needed --
 * dScMgBase_c, the immediate base, already provides one.
 *
 * SM64DS RTTI names the implementation dScMgSmartball_c. The reconstructed factory
 * dScMgSmartball_c_classInit (historical alias MgBingoBallSlotsShot_Spawn) installs this class's
 * cartridge vtable for the MG_SMARTBALL registry profile.
 */
#ifndef DSCMGSMARTBALL_C_H
#define DSCMGSMARTBALL_C_H
#include "dScMgBase_c.h"

extern "C" void __cxa_vec_cleanup(void *base, int count, int stride, void *dtor);
extern "C" void NullDestructor_0203d47c(void);
extern "C" void SmartballObj_ElemDtor(void);

struct cMgSmartball_spring_c;
struct cMgSmartball_ball_c;
struct cMgSmartball_kinoko_c;
struct cMgSmartball_ana_c;
struct cMgSmartball_propeller_c;
struct cMgSmartball_dokan_c;
struct cMgSmartball_pakkun_c;
struct cMgSmartball_pushswitch_c;
struct cMgSmartball_slot_c;
struct cMgSmartball_board_c;
struct cMgSmartball_wing_c;

/* One 0x24-byte spark of the burst EmitSparks seeds, UpdateSparks moves and
   RenderSparks draws. The name is coined; the fields are read off those three
   methods. */
struct SmartballSpark {
    s32 mOrigin[2]; /* 0x00 -- the burst's centre */
    s32 mPos[2];    /* 0x08 -- origin plus a random rotated offset */
    s32 mVel[2];    /* 0x10 -- (0, 0x10) rotated; damped by 7/8 a frame */
    s32 mFrame;     /* 0x18 -- animation frame, sprite index mFrame / 4 */
    s32 mBursts;    /* 0x1c -- re-seeds left; the spark dies at 0 */
    u8  mActive;    /* 0x20 */
    u8  mAlt;       /* 0x21 -- EmitSparks's second argument; picks the
                        second sprite set */
};

struct dScMgSmartball_c : dScMgBase_c {
    virtual ~dScMgSmartball_c();

    /* This class's own overrides, read off the ROM's vtable: the slots where the
       table differs from dScMgBase_c's. Spelled WITHOUT the `virtual` keyword, the
       way include/daObjMarioCap_c.h and include/daObjRc_Dorifu_c.h spell theirs --
       an override of a virtual an ancestor already declares is implicitly virtual
       either way, so each reuses an existing slot and adds no field, and the
       0x629c assert below still holds. The destructor above is declared first and
       out of line, so it stays this class's key function; the production TU owns the
       compiler-emitted vtable.

       AfterCleanupResources takes dScMgBase_c's signature exactly, u32 and all.
       The pre-migration file spelled the parameter `int mode` and still matched,
       because the ROM only ever compares it against 2 -- but the declaration it is
       overriding is `void AfterCleanupResources(u32)`, so that is what it is. */
    /* InitResources was declared here before its body existed, because the
       EMITTED vtable needs the declaration: without it mwcc wrote fBase_c's
       default, _ZN7fBase_c13InitResourcesEv (0x02043c80), into slot 0 while the
       cartridge holds 0x02118b70 -- romdata_check scored _ZTV16dScMgSmartball_c
       DIFFERS on that one word. Its 0x8dc bytes are now decompiled and enrolled
       (src/minigames/d_s_mg_smartball.cpp); the slot is unchanged. */
    virtual void StartRound(int arg);               /* slot 18 */
    virtual int  OnGraphCallback3();                           /* slot 25 */
    virtual int  InitSubScreenBg();                          /* slot 31 */
    s32  InitResources();  /* slot  0 */
    void AfterCleanupResources(u32 vfSuccess);
                           /* slot  5 */
    s32  Behavior();       /* slot  6 */
    s32  Render();         /* slot  9 */

    /* Recovered helpers. The spark/dust pair renders the rolling-ball trail
       and the collision poofs; the Count* counters feed the score popup the
       emitter queue plays back; EmitScore is the 5-slot popup queue. */
    int  SparksActive();
    void EmitSparks(int *pair, int a3);
    void RenderSparks();
    void UpdateSparks();
    void ResetSparks();
    void EndRound();
    void ServeNextBall();
    void CountOut();
    void CountAward(int i);
    void CountDokan();
    void CountAna();
    void CountKinoko();
    void CountBingo();
    int  CountLine(int i);
    void CountCell();
    unsigned short GetTile(int *pos);
    void UpdateDust();
    void SpawnDust(int *origin);
    void UpdateScores();
    void EmitScore(int *src, int v2, int v3, int v5);
    void KickGate(int idx);
    int  IsTableAtRest();
    void ResolveBallPair(int b, int c, u8 *d, u8 *e);
    void CollideBalls();
    void SpawnObjects();

    /* dScMgBase_c's data ends at 0x4660. Field evidence is this class's own
       methods in src/minigames/d_s_mg_smartball.cpp; widths come from the access
       sites. */
    s32 mPhase;           /* 0x4660 -- Behavior's switch: 0 the table runs, 1
                              the result screen (set once IsTableAtRest has held
                              0x3c frames), 2 the hand-off (set on the touch
                              that leaves the result screen) */
    s32 mServeIndex;      /* 0x4664 -- index into mpBalls of the ball in play:
                              Behavior advances it when that ball IsOut, and
                              cMgSmartball_ball_c's QueueBehind and
                              SaveSnapshot compare their mIndex against it */
    /* The seven object counts, each paired with the table below it by
       SpawnObjects (counted while the BG maps are scanned, then used as the
       construction bound) and by AfterCleanupResources (zeroed after that table
       is freed). */
    s32 mBallCount;       /* 0x4668 -- 0xc or 0xd, from the mode byte */
    s32 mAnaCount;        /* 0x466c -- capped at 8, tile 0x2cb */
    s32 mKinokoCount;     /* 0x4670 -- capped at 0x19, tiles 0x2e8 and 0x328 */
    s32 mPropellerCount;  /* 0x4674 -- capped at 3, tile 0x84 */
    s32 mDokanCount;      /* 0x4678 -- capped at 6, tile 0x3d2 */
    s32 mPakkunCount;     /* 0x467c -- capped at 3, tile 0x292 */
    s32 mPushSwitchCount; /* 0x4680 -- capped at 2, tile 0x50 */
    cMgSmartball_spring_c *mpSpring;              /* 0x4684 -- InitResources
                                                      builds it (0x48 bytes) */
    cMgSmartball_ball_c *mpBalls[13];             /* 0x4688 */
    cMgSmartball_kinoko_c *mpKinokos[25];         /* 0x46bc */
    cMgSmartball_ana_c *mpAnas[8];                /* 0x4720 */
    cMgSmartball_propeller_c *mpPropellers[3];    /* 0x4740 */
    cMgSmartball_dokan_c *mpDokans[6];            /* 0x474c */
    cMgSmartball_pakkun_c *mpPakkuns[3];          /* 0x4764 */
    cMgSmartball_pushswitch_c *mpPushSwitches[2]; /* 0x4770 */
    cMgSmartball_slot_c *mpSlot;                  /* 0x4778 -- tile 0x57 */
    cMgSmartball_board_c *mpBoard;                /* 0x477c -- nine tiles 0x4a */
    cMgSmartball_wing_c *mpWing;                  /* 0x4780 -- tile 0xab */
    s32 mGateLampTimer[2]; /* 0x4784 -- KickGate(i) arms [i] to 0x14 (and
                              reverses every propeller when it was 0); Behavior
                              counts both down; Render lights the left/right
                              side sprite while it is positive */
    /* The five-slot score popup queue, EmitScore's writer and UpdateScores's
       reader. */
    s32 mPopupScore[5];    /* 0x478c -- the score value; > 0 marks a live slot */
    s32 mPopupMultiplier[5]; /* 0x47a0 -- EmitScore's last argument */
    s32 mPopupAge[5];      /* 0x47b4 -- frames shown; cleared past 0x3c */
    u8 mArray1[0x28];     /* 0x47c8 -- 5 * 8, the popup positions (UpdateScores
                              rises them each frame). Elem dtor
                              NullDestructor_0203d47c */
    s32 mPopupDelay[5];    /* 0x47f0 -- EmitScore's delay; UpdateScores submits
                              the score once it drains */
    u8 mDustActive[0x10]; /* 0x4804 -- SpawnDust sets, UpdateDust clears */
    s32 mDustAge[0x10];   /* 0x4814 -- UpdateDust retires a puff at 0xf */
    u8 mArray2[0x80];     /* 0x4854 -- 0x10 * 8, the dust positions. Elem dtor
                              NullDestructor_0203d47c */
    u8 mArray3[0x80];     /* 0x48d4 -- 0x10 * 8, the dust velocities. Elem dtor
                              NullDestructor_0203d47c */
    u16 mBg1Map[0x400];   /* 0x4954 -- sSmartballBg1NscFmt decompressed; scanned
                              for the object tiles, and GetTile's upper half */
    u16 mBg2Map[0x400];   /* 0x5154 -- sSmartballBg2NscFmt, the lower half */
    s32 mRestFrames;      /* 0x5954 -- frames IsTableAtRest has held; 0x3c moves
                              mPhase to 1 */
    s32 mDrainTimer;      /* 0x5958 -- EndRound zeroes it; counts while
                              mDraining, music restored at 0xb4, then one ball
                              burst every 0x1e frames */
    u8 mDraining;         /* 0x595c -- EndRound sets it; cleared once no ball
                              is left to burst. The table is not at rest and
                              the board stops scoring while it is up */
    u8 mRoundEnded;       /* 0x595d -- EndRound sets it, nothing clears it;
                              the propellers stop turning */
    s32 mResultTimer;     /* 0x5960 -- Render's itemised-result reveal counter,
                              counts to 0x12c */
    /* The result screen's tallies, one Count* helper each; Render draws them
       with their per-item point values. */
    s32 mCellTally;       /* 0x5964 -- CountCell, x 0x64 */
    s32 mLineTally[4];    /* 0x5968 -- CountLine(i) bumps [i - 1] */
    s32 mBingoTally;      /* 0x5978 -- CountBingo, x 0x2710 */
    s32 mKinokoTally;     /* 0x597c -- CountKinoko, x 0x12c */
    s32 mAnaTally;        /* 0x5980 -- CountAna, x 0x7d0 */
    s32 mDokanTally;      /* 0x5984 -- CountDokan, x 0xbb8 */
    s32 mAwardTally[3];   /* 0x5988 -- CountAward(i) */
    u32 mOutTally;        /* 0x5994 -- CountOut, x 0x7d0 */
    s32 mResultSlideX;    /* 0x5998 -- sub BG0 x offset: InitResources sets
                              0x100, mPhase 1 slides it to 0 by 4 */
    SmartballSpark mSparks[0x40]; /* 0x599c -- elem dtor SmartballObj_ElemDtor */
};

#ifndef SM64DS_PLATFORM_PC
/* ROM layout under mwccarm; host ABI divergence is tracked separately. */
typedef char dScMgSmartball_c_size_must_be_0x629c[sizeof(dScMgSmartball_c) == 0x629c ? 1 : -1];
#endif

#endif
