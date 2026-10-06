//cpp
/* dFdDummy_c -- a no-op fade variant: overrides five of FaderColor's ten
   slots with trivial or pass-through bodies and adds no fields of its own.
   Cartridge class: _ZTV10dFdDummy_c at 0x0208ea6c (ten slots; slots 0..4 are
   this class's, 5..9 inherited from FaderColor/FaderBrightness). TU claims
   0x020171c8..0x02017278, the whole class run in delinks order. Written
   back-to-front: mwccarm emits .text in reverse source order under default
   deferred codegen.

   The class is only ever embedded (dScDSMT_c member at +0x54, built by the
   func_02017278 helper immediately above this range), so the cartridge homes
   no C1/C2 -- there is nothing to absorb for them, and the D2 sibling the
   destructor definition emits deadstrips unenrolled. The vtable
   emits here because this TU defines the key function ~dFdDummy_c()
   -- and nothing else should. The cartridge spells the base
   chain dFdColor_c / dFdBrightness_c, so _ZTS/_ZTI records emitted under
   the project spellings (Fader, FaderColor, FaderBrightness) would be
   homeless; compiling with RTTI off emits none, and the vtable preamble's
   typeinfo word deadstrips with the rest of the data sections. Same lever
   the MaterialChanger/TextureTransformer folds use for their dExt* names. */
#pragma RTTI off

#include "dFdDummy_c.h"
#include "decl_Fader.h"

// @symbol _ZN10dFdDummy_cD1Ev
dFdDummy_c::~dFdDummy_c()
{
}

/* Vtable slot 2. The whole body is a tail call into the base chain's own
   AdvanceInterp at 0x020175e8: `this' rides through in r0 untouched, which
   is exactly what the inherited implementation wants. The base
   implementation is still a mangled free function, so it is reached through
   decl_Fader.h's extern "C" declaration rather than as Fader::. */
// @symbol _ZN10dFdDummy_c11AdvanceFadeEv
void dFdDummy_c::AdvanceFade()
{
    _ZN5Fader13AdvanceInterpEv();
}

/* Vtable slot 3: writes the interp speed and makes a genuinely virtual call
   through slot 5 -- dFdDummy_c overrides none of slots 5-9, so this lands on
   FaderColor/FaderBrightness's own inherited body. */
// @symbol _ZN10dFdDummy_c15SetBackwardTimeEj
int dFdDummy_c::SetBackwardTime(u32)
{
    speed = -0x1000;
    return IsAtStart();
}

/* Vtable slot 4: same shape through slot 6. */
// @symbol _ZN10dFdDummy_c14SetForwardTimeEj
int dFdDummy_c::SetForwardTime(u32)
{
    speed = 0x1000;
    return IsAtEnd();
}
