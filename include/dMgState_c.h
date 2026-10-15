#ifndef DMGSTATE_C_H
#define DMGSTATE_C_H

#include "types.h"

/* The shared minigame state machine, embedded in dScMgBase_c at 0xcc. It
 * has no vtable and the ROM has no RTTI for it, so the class name and its
 * member names are coined. The matched methods fix the layout: SetState
 * takes mEnter from a 20-entry table and calls it, Behavior counts mTimer
 * toward 0 and calls mBehavior, Render calls mRender, and mState -1 (the
 * constructor's value) makes Behavior and Render do nothing. */
struct dMgState_c {
    typedef void (dMgState_c::*Callback)();

    Callback mEnter;
    Callback mBehavior;
    Callback mRender;
    s32 mState;
    s32 mTimer;
    s32 unk_020;
    s32 unk_024; /* dScMgBase_c steps and draws the machine only while this is 0 */

    dMgState_c();
    void Render();
    void Behavior();
    void SetState(s32 state);

    /* State handlers: pointer-to-member constants at 0x020bc8bc..0x020bca3c
       (the enter/behavior/render records) name these as targets. */
    void DrawRecordTable();
    void DrawScoreDigits();
    void DrawScore();
    void State19_Update();
    void State19_Enter();
    void State18_Update();
    void State18_Enter();
    void State17_Update();
    void State17_Enter();
    void State16_Update();
    void State16_Enter();
    void State15_Enter();
    void UpdateFadeThenResume();
    void State14_Enter();
    void UpdateRetryPrompt();
    void State13_Enter();
    void State12_Enter();
    void State11_Update();
    void State11_Enter();
    void State10_Update();
    void State10_Enter();
    void State09_Update();
    void State09_Enter();
    void UpdateWaitThenResume();
    void State08_Enter();
    void State07_Enter();
    void UpdateAfterHidden();
    void State06_Update();
    void State06_Enter();
    void UpdateGameOverToMenu();
    void State05_Update();
    void State05_Enter();
    void State04_Update();
    void State04_Enter();
    void UpdateRetryFadeOut();
    void State03_Update();
    void State03_Enter();
    void State02_Update();
    void State02_Enter();
    void State01_Update();
    void State01_Enter();
    void State00_Update();
    void State00_Enter();
};

#ifndef SM64DS_PLATFORM_PC
/* ROM layout under mwccarm; host ABI divergence is tracked separately. */
typedef char dMgState_c_size_must_be_0x28[
    sizeof(dMgState_c) == 0x28 ? 1 : -1];
#endif

#endif
