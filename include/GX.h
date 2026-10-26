#ifndef SM64DS_GX_H
#define SM64DS_GX_H

#include "types.h"

/* GX / GXS -- the main and sub engines' display setup, VRAM bank mapping and
 * VRAM upload helpers (Nitro SDK namespaces, not classes). Defined in
 * src/engine/gx/GX_Init.cpp (DispOn, SetGraphicsMode),
 * src/engine/gx/GX_VramCnt.cpp (SetBankFor*), src/engine/gx/GX.cpp (texture
 * and BG palette loads), src/engine/gx/GXS.cpp (the OBJ, BG-character and
 * extended-palette loads of both engines) and src/game/stages/d_scene.cpp
 * (DisableAllBanks).
 *
 * The SetBankFor* banks are u16 because the definitions take u16: a caller
 * passing a wider non-constant value pays a narrowing the ROM may not have,
 * which is why a few callers keep a local u32 spelling. Parameters stay
 * unnamed: a name here takes an @NNN in every includer. */
namespace GX {
void DispOn(void);
void SetGraphicsMode(int, int, int);
void DisableAllBanks(void);
void SetBankForBG(u16);
void SetBankForOBJ(u16);
void SetBankForTex(u16);
void SetBankForTexPltt(u16);
void SetBankForSubBG(u16);
void SetBankForSubOBJ(u16);
void SetBankForSubBGExtPltt(u16);
void SetBankForSubOBJExtPltt(u16);
void BeginLoadTex(void);
void LoadTex(const void *, unsigned int, unsigned int);
void EndLoadTex(void);
void BeginLoadTexPltt(void);
void LoadTexPltt(const void *, unsigned int, unsigned int);
void EndLoadTexPltt(void);
void LoadBGPltt(const void *, unsigned int, unsigned int);
void LoadOBJPltt(const void *, unsigned int, unsigned int);
void LoadOBJ(const void *, unsigned int, unsigned int);
void LoadBG0Char(const void *, unsigned int, unsigned int);
void LoadBG1Char(const void *, unsigned int, unsigned int);
}

namespace GXS {
void SetGraphicsMode(int);
void LoadBGPltt(const void *, unsigned int, unsigned int);
void LoadOBJPltt(const void *, unsigned int, unsigned int);
void LoadBG0Char(const void *, unsigned int, unsigned int);
void LoadBG1Char(const void *, unsigned int, unsigned int);
void BeginLoadBGExtPltt(void);
void LoadBGExtPltt(const void *, unsigned int, unsigned int);
void EndLoadBGExtPltt(void);
void BeginLoadOBJExtPltt(void);
void LoadOBJExtPltt(const void *, unsigned int, unsigned int);
void EndLoadOBJExtPltt(void);
}

#endif
