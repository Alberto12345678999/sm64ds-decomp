#ifndef DSCMGTERESA_C_H
#define DSCMGTERESA_C_H
#include "dScMgBase_c.h"

/* dScMgTeresa_c : dScMgBase_c, confirmed leaf via tools/rtti_extract.py (no
   RTTI record names it as a base). Own vtable slots: 0 (InitResources),
   6 (Behavior), 9 (Render), 16 (D1), 17 (D0), 18 (StartRound),
   20 (OnNewRecord) and 34 (PaintSquare). These overrides are declared members.
   Slot 20 is declared here because dScMgBase_c
   declares it, so leaving it out here would put the BASE's body in this
   class's slot 20 where the cartridge holds its own.  The body is a bare
   FreeGfxSlotsById(8) thunk that never reads `this`, which costs nothing --
   `this` arrives in r0 and is immediately overwritten with 8 either way, so
   the bytes are the same whether it is spelled as a member or not.
   "OnNewRecord" is a coined name; see include/dScMgBase_c.h.  Slot 34 IS that multi-argument virtual, and it is
   declared and reconstructed tree-wide now -- `PaintSquare(int, int, int, int)`,
   the family's pixel brush.  The guess recorded here, "draws a dMeter_c
   digit/glyph", was right: this class's override stamps a shape by testing
   data_ov006_0213f9e4[row] one bit per column, so it paints a stipple pattern
   rather than a solid square, and it really does barely touch `this` -- the
   object pointer arrives and is never read, because unlike the base it always
   draws into sub BG0 instead of consulting the layer index at +0x6c.  Fields below
   dScMgBase_c's own 0x4660 are INHERITED, not this class's own -- accessed
   via raw offsets on a char* cast of `this` (0xb4 touched here, already
   dScMgBase_c's own).
 *
 * SM64DS RTTI names the implementation dScMgTeresa_c. The reconstructed factory
 * dScMgTeresa_c_classInit (historical alias MgHideAndBooSeek_Spawn) installs this class's
 * cartridge vtable for the MG_TERESA registry profile.
 */
struct dScMgTeresa_c : dScMgBase_c {
    virtual ~dScMgTeresa_c();
    virtual s32 InitResources();  /* slot 0 */
    virtual s32 Behavior();       /* slot 6 */
    virtual s32 Render();         /* slot 9 */
    virtual void StartRound(int arg);               /* slot 18 */
    virtual void OnNewRecord();                          /* slot 20 */
    virtual void PaintSquare(int cx, int cy, int colour, int size); /* slot 34 */

    /* scene helpers, in ROM order */
    void BigBoo_ShowResult();
    void func_ov006_0211cc90();
    void BigBoo_Draw();
    void BigBoo_State8(int idx);
    void BigBoo_State7();
    void BigBoo_State6(int index);
    void BigBoo_State5(int i);
    void BigBoo_State4(int idx);
    void BigBoo_State3(int i);
    void BigBoo_State2(int i);
    void BigBoo_State1(int i);
    void BigBoo_State0(int i);
    void BigBoo_Update();
    void BigBoo_Start();
    void BigBoo_Hide();
    void StepBg3Scroll();
    void Marker_Draw();
    void Marker_Update();
    void Marker_Show();
    void Marker_Hide();
    void Reveal_Draw();
    void Reveal_State4(int idx);
    void Reveal_State3(int i);
    void Reveal_State2(int i);
    void Reveal_State1(int i);
    void Reveal_State0(int i);
    void Reveal_Update();
    void Reveal_Start();
    void Reveal_Hide();
    void RisingIcon_DrawAll();
    void RisingIcon_ClearAll();
    int RisingIcon_CountBusy();
    void RisingIcon_UpdateAll();
    void RisingIcon_Spawn(int i);
    void RisingIcon_SpawnForFound();
    void FoundMark_DrawAll();
    void FoundMark_UpdateAll();
    void FoundMark_Spawn(int param);
    void DrawCountdown();
    void UpdateCountdown();
    void StartCountdown();
    void Exclaim_DrawAll();
    void Exclaim_UpdateAll();
    void Exclaim_Spawn(int idx);
    void CheckRevealDone();
    void CheckRoundEnd();
    void DrawBoos();
    void AreBoosSettled();
    void TouchTestBoo(int idx);
    void CountRubbedTiles(int idx);
    void MoveBoo(int i);
    void Boo_State7(int i);
    void Boo_State6(int i);
    void Boo_State5(int idx);
    void Boo_State4(int idx);
    void Boo_State3(int i);
    void Boo_State2(int i);
    void BounceBooOffWalls(int i);
    void StepBoo(int i);
    void StartBoosHiding();
    void Boo_State1(int i);
    void Boo_State0(int idx);
    void AnimateBoo(int i);
    void UpdateBoos();
    void SpawnBoos();
    void UpdateRubbing();
    void ReadRubTouch();
    void ResetRound();
    void Scene_State4();
    void Scene_State3();
    void Scene_State2();
    void Scene_State1();
    void Scene_State0();

    u8  pad_4660[0x588];
    s32 unk_4be8;            /* 0x4be8 -- state index for Behavior's pmf dispatch */
    u8  pad_4bec[0x2a];
    s16 unk_4c16;            /* 0x4c16 */
    u8  pad_4c18[0xb];
    u8  unk_4c23;            /* 0x4c23 */
    /* trailing extent the ROM's `new dScMgTeresa_c` literal proves; see tools/opnew_sizes.py */
    u8 pad_4c24[0x4];
};

#ifndef SM64DS_PLATFORM_PC
/* ROM layout under mwccarm; host ABI divergence is tracked separately. */
typedef char dScMgTeresa_c_size_must_be_0x4c28[sizeof(struct dScMgTeresa_c) == 0x4c28 ? 1 : -1];
#endif

#endif
