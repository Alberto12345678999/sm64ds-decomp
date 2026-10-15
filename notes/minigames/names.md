# Minigame names: evidence and confidence

The cartridge carries class names (RTTI) but no method, field or helper names
for the minigame code. Every name on this page is coined in this tree. Each one
records:
- the evidence it rests on
- a confidence level
- for anything below **high**, what to watch at runtime to settle it (see
  [runtime-checks.md](runtime-checks.md))

Confidence levels:
- **high**: the body and every caller agree, and no other reading fits.
- **medium**: the role is clear from the code, but the exact meaning rests on
  something not yet observed, such as which banner graphic a file index shows.
- **low**: a best guess from one caller or one body. Rename freely when better
  evidence turns up.

A rename is checked by compiling every minigame TU before and after. The objects
must be identical apart from the renamed symbols: same section bytes, same
relocation offsets and types, same targets.

## dScMgBase_c virtual slots 18-35 (renamed 2026-10-14)

Until this rename, slots 18-30 carried `dActor_c` method names, copied across by
vtable slot index alone. `dActor_c` and `dScMgBase_c` share only `dBase_c`,
which declares no virtual, so a slot number means nothing between them.
- **Where they came from.** The actor names are themselves imports from an ASM-hack
  symbol file. An untooled "vtable-identity" pass (#877) wrote them onto the scene
  classes as `recovered from vtable slot identity` comments.
- **How they spread.** `tools/reconcile_names.py` (#944) turned those comments into
  `// recovered name:` lines. The slot campaign of 2026-08-31 (#2088-#2112) then made
  them symbols. Slots 31 and 32 got `Kill` and `AfterClsn` the same way, from
  `dBgActor_c` and `dPathLiftActor_c`.
- **Reach.** No other non-actor class has a vtable longer than 18 slots, so the
  transplant is confined to these 33 classes.

| Slot | Old name | New name | Confidence | Evidence |
|---|---|---|---|---|
| 18 | `OnYoshiTryEat(int)` | `StartRound(int)` | medium | `dMgState_c` calls it with the finished state's number when a banner ends. Games call it with -1 to retry after a lost life (Cup's `StateFinish`). The overrides reset their round, and Memory's calls `ResetGame`. |
| 19 | `OnTurnIntoEgg(int)` | `CanEndState(int)` | high | Every `dMgState_c` behaviour handler polls it with `mState` and waits for nonzero. The overrides return 0 while their own reaction animation plays. |
| 20 | `Virtual50` | `OnNewRecord` | medium | Its one caller is state 17's behaviour, the results path taken when the new-record flag is set, 120 frames in. Cup and Sound play a win animation; 3DEsp and Teresa free banner slot 8. |
| 21 | `OnGroundPounded` | `OnHostAnimCue` | low | Its one caller is `func_ov006_020c14bc` (the presenter model's reaction animation, unit020bfec0), on that animation's last repeat. BSC picks a reaction tier from the score; Memory and Memory2 pass `mMaxMisses` to an ov004 helper. |
| 22 | `OnAttacked1` | `OnGraphCallback1` | high (mapping) | `graphCallback_c::GraphCallback1` forwards to it. What the engine's callback 1 is for is not known. |
| 23 | `OnAttacked2` | `OnGraphCallback0` | high (mapping) | `GraphCallback0` forwards to it. The arm9 caller `func_02019390` skips its OAM reset and 3D flush when the callback returns 0. |
| 24 | `OnKicked` | `OnGraphCallback2` | high (mapping) | `GraphCallback2` returns its result. The base body saves or restores the screen on an edge of `mMenuOpen`. |
| 25 | `OnPushed` | `OnGraphCallback3` | high (mapping) | `GraphCallback3` forwards to it. The base returns `mMenuOpen == 0`. |
| 26 | `OnHitByCannonBlastedChar` | `GetDisplayMode` | high | It returns 0, 1 or 2 from Base, Single3DBase and D3DBase. `BeforeInitResources` enables the 3D engines for any nonzero value, and the sprite wrappers choose a screen on 2. |
| 27 | `OnHitByMegaChar` | `OpenMenu` | high | It sets the three menu items to their slide-in positions and sets `mMenuOpen = 1`. `BeforeBehavior` calls it on A, B, Select or Start with the stylus up. |
| 28 | `OnHitFromUnderneath` | `CloseMenu` | high | It clears `mMenuOpen` and resets the options panel. It runs from the resume item, or from a button press with nothing highlighted. |
| 29 | `OnAimedAtWithEgg` | `SaveScreenForMenu` | high | It saves POWCNT1, both DISPCNT BG bits, 0x400 bytes of palette and 0x2000 bytes of OBJ VRAM, then draws the menu graphics. It runs on the rising edge of `mMenuOpen`. |
| 30 | `OnAimedAtWithEggReturnVec` | `RestoreScreenFromMenu` | high | It is slot 29's exact mirror and runs on the falling edge. It returns nothing (the bytes settle `void`). |
| 31 | `Virtual7C` (was `Kill`) | `InitSubScreenBg` | high | It sets up sub-engine BG1 and loads the language's character file plus screen map 0x5b. |
| 32 | `Virtual80` (was `AfterClsn`) | `InitMainScreenBg` | high | It does the same for main-engine BG1 with screen map 0x67. |
| 33 | `Virtual84` | `InitEngines` | high | It sets graphics modes, VRAM banks, the BG/OBJ character files and palettes, and registers the graph callback. (`InitDisplay` was already taken by Trampoline's own method.) |
| 34 | `Virtual88(int,int,int,int)` | `PaintSquare` | high | It paints a size x size square of one 4bpp palette index into the brush's BG layer. The line rasteriser `Mg_DrawLine` calls it once per point. |
| 35 | `Virtual8C` | `IsAltVariant` | medium | It returns `(param1 & 0xff) != 0`, and Amida asks `== 1`. Coin, Panel, Sound and Snowball branch on it to pick their second variant's assets. Which menu rows set that byte has not been checked against the menu table. |

Still open for the graph callbacks: what the engine's four `dGraph_c::callback_c`
slots are for. The arm9 dispatchers are `func_02019390` (slot 0),
`func_02019404` (slot 1), `func_02019144` (slot 2) and `func_02019100` (slot 3).
They are named from their call order by the frame loop once the dispatchers are
named, and not before.

## ov004 runtime helpers and globals (renamed 2026-10-14)

These are free functions and data of the shared ov004 runtime
(`src/minigames/d_s_mg_base.cpp`). Each was named from its body, and its body's
comment in that file carries the detail. The `Mg_` prefix marks the minigame
runtime. `Ov004_` marks a thunk that only forwards to an arm9 routine.

**High confidence.** The body says exactly this, and the callers agree.

| Area | Names (old address) |
|---|---|
| Scene singleton | `gMgScene` (data_ov004_020beb68): set by the `dScMgBase_c` constructor, cleared by its destructor. `gMgMenuRow` (arm9 data_0209b308): the 0x34-byte menu row the select menu copies in. Word 2 is the scoring mode, words 5/6 the record defaults, word 11 the music mode. |
| Scores and records | `Mg_SubmitScore` (020adb1c), `Mg_GetSubmittedScore` (020adbc0), `Mg_SetSessionBest` (020ada40), `Mg_GetSessionBest` (020adafc), `Mg_IsNewRecord` (020adbe0), `Mg_ClearNewRecordFlag` (020ada20), `Mg_SetTopRecord`/`Mg_GetTopRecord` (020adc00/020adc1c), `Mg_GetSaveTable` (020adc3c), `Mg_FindRecordRank` (020ad6fc), `Mg_GetLastRecordRank` (020ad6f4), `Mg_RankSessionBest` (020ad940), `Mg_CommitRecords` (020ad90c), `Mg_SaveRecordPair` (020ad79c), `Mg_GetSavedRecord0/1` (020ad8b8/020ad878), `Mg_GetScoringMode` (020ae1a8) |
| Shared state machine | `Mg_SetSharedState` (020b0a54), `Mg_CallStartRound` (020b29a0) |
| Banners | `Mg_ShowBanner` (020b0cac), `gMgBanners` (data_ov004_020bf648, three 0x134-byte records) |
| Effect pool | `sMgFxPool` (0x40 records), `sMgFxUpdateTable`/`sMgFxDrawTable`, `Mg_SpawnFx`, `Mg_InitFx`, `Mg_UpdateFx`, `Mg_DrawFx` |
| Pause menu | `Mg_UpdateMenu` (020aeb24), `Mg_DrawMenu` (020ae858) |
| Drawing | `Mg_DrawSpriteList`, `Mg_DrawSpriteListEntry`, `Mg_CopySpriteList`, `Mg_DrawNumber` (8 px digits), `Mg_DrawBigNumber` (16 px digits), `Mg_DrawNumberRotated`, `Mg_DrawTally`, `Mg_DrawScoreTally`, `Mg_DrawRecordTable`, `Mg_DrawRecordRow`, `Mg_DrawPrompt`, `Mg_DrawLine`, `Mg_InitBrush`, `sMgSpriteTables` (per-language sprite lists) |
| Display | `Mg_ResetBgOffsets`, `Mg_DisableAllBanks`, `Mg_GetTopScreenYOffset`/`Mg_SetTopScreenYOffset` with `sMgTopScreenYOffset`, `Mg_ResetOverlays` |
| Music | `Mg_GetMusicMode`, `Mg_GetMusicTrack`, `Mg_StartMusic`, `Mg_InitMusic`, `Mg_RestoreMusic` |
| Files and memory | `Ov004_LoadFile`, `Ov004_LoadFileByPath`, `sMgWorkBuffer`/`Mg_GetWorkBuffer` (the 0x4000-byte buffer `BeforeInitResources` allocates) |

**Medium confidence.** The mechanics are certain, but the game-facing meaning is not observed yet.

| Name (old) | Why it is not high |
|---|---|
| `Mg_PlayJingle` (020ae274) | It starts sequence `id` on `Sound::PlaySub`'s player and sets the music volume target to 0x40. The callers pass 1, 3 and 4 when a banner goes up. "Jingle" is inferred; the IDs are not mapped to sounds. |
| `Mg_LoseLives`, `Mg_GainLives`, `Mg_SubLives`, `Mg_AddLives`, `Mg_DrawLives`, `Mg_DrawLivesIcon` | They work on `unk_0a8`, clamped to 0..9999, which `BeforeBehavior` eases `unk_0ac` toward for display. Cup gives 2 and loses one per wrong pick before game over; Memory caps the value at 3. A wider "credits" reading is possible in the gambling games. |
| `Mg_ResumeSharedState` (020b0a38) | It clears `mStateController.unk_024`, which lets `BeforeBehavior`/`BeforeRender` step and draw the controller again. What sets the flag (state 6's behaviour) reads as "hand control back to the game". |
| `Mg_CheckBannerButton` (020b0b1c) | It hit-tests a touch against a shown banner whose graphic id is `arg` (0x40 x 0x13 box), or reports the banner's finish. States use ids 0, 1 and 2 as retry/quit buttons. |
| `Mg_DrawBlinkSprite` (020b0d8c) | It alternates sprite words 0x11/0x12 on the 40-frame counter. Which graphic that is has not been seen. |
| `Mg_DrawTopLeftCounter`, `Mg_DrawTopRightCounter`, `Mg_DrawTopCenterCounter`, `Mg_DrawStockCounter` | HUD numbers with a label sprite, named by screen position. The label graphics (sprite words 8, 4, 3 and 0/1) are not identified. |
| `Mg_RenderSub*`, `Mg_RenderMain*`, `Mg_RenderSpriteBoth*`, `Mg_RenderSpriteOn*` | OAM wrappers named by screen and arguments. `OAM::Render`'s first argument is read as main=0 / sub=1 from `RenderOamMainScreen` and `Hud_RenderSprite`; that reading has not been checked on hardware. |

**Low confidence.**
- `Mg_GetRowWord12` (020b1aec) returns `unk_0bc`, which the constructor copies from menu-row word 12. The name only describes where the value lives. Jump reads it `% 5`.
