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
| 34 | `Virtual88(int,int,int,int)` | `PaintSquare` | high | It paints a size x size square of one 4bpp palette index into the brush's BG layer. The line rasteriser `func_ov004_020ae5c4` calls it once per point. |
| 35 | `Virtual8C` | `IsAltVariant` | medium | It returns `(param1 & 0xff) != 0`, and Amida asks `== 1`. Coin, Panel, Sound and Snowball branch on it to pick their second variant's assets. Which menu rows set that byte has not been checked against the menu table. |

Still open for the graph callbacks: what the engine's four `dGraph_c::callback_c`
slots are for. The arm9 dispatchers are `func_02019390` (slot 0),
`func_02019404` (slot 1), `func_02019144` (slot 2) and `func_02019100` (slot 3).
They are named from their call order by the frame loop once the dispatchers are
named, and not before.
