#ifndef FADER_HPP
#define FADER_HPP

#include "types.h"

/* The screen-fade interpolator hierarchy at 0x020175e8..0x0201786c.
 *
 * Every claim below is read out of the ROM, not guessed:
 *
 * LAYOUT. `Fader` is polymorphic -- the ROM carries `_ZTV5Fader` and
 * `_ZTV15FaderBrightness`, and both destructors store one of those addresses
 * into [this+0x0]. So the vptr is at 0x0 and the first data member starts at
 * 0x4. `Fader::AdvanceInterp` reads a Fix12i at 0x8 and passes &[this+0x4] to
 * the 20.12 approach helper at 0x0203ae58, which pins currInterp=0x4 and
 * speed=0x8, both 4-byte. FaderBrightness adds no members of its own: its D1
 * writes the vptr and immediately tail-calls the Fader subobject destructor.
 *
 * VTABLE ORDER. FaderBrightness::IsBetweenStartAndEnd calls two virtuals
 * through slots 5 and 6 and returns true only when both are 0 -- i.e. "not at
 * the start and not at the end". With the Itanium ABI's two destructor slots
 * (D1, D0) at 0 and 1, that places IsAtStart at 5 and IsAtEnd at 6, and leaves
 * slots 2..4 for AdvanceFade, SetBackwardTime and SetForwardTime. This exact
 * signature list is what src/_ZN15FaderBrightness14SetForwardTimeEj already
 * used to reproduce the ROM byte-for-byte, so the ordering is verified rather
 * than merely plausible.
 *
 * FIXED POINT. currInterp runs 0..0x1000, which is 0.0..1.0 in 20.12. SetToEnd
 * writes 4096 and SetToStart writes 0; SetForwardTime derives speed as
 * 1.0/frames via cstd::fdiv, and SetBackwardTime the same with the sign
 * flipped -- so a "backward" fade is just a negative speed, which is why
 * AdvanceInterp picks its target by testing the sign of speed.
 *
 * Field names are inferred from behaviour; names cannot change codegen, so
 * they are safe to improve. Offsets, widths and vtable slots cannot -- those
 * are pinned by the bytes.
 */
struct Fader {
    Fix12i currInterp;  /* 0x04 -- current fade level, 0..0x1000 */
    Fix12i speed;       /* 0x08 -- per-frame delta; sign selects the target */

    virtual ~Fader();                          /* vtable slots 0 (D1), 1 (D0) */
    virtual void AdvanceFade();                /* slot 2 */
    virtual int SetBackwardTime(u32 frames);   /* slot 3 */
    virtual int SetForwardTime(u32 frames);    /* slot 4 */
    virtual int IsAtStart();                   /* slot 5 */
    virtual int IsAtEnd();                     /* slot 6 */

    /* Steps currInterp toward 1.0 or 0.0 depending on the sign of speed. */
    void AdvanceInterp();
};

struct FaderBrightness : Fader {
    virtual ~FaderBrightness();
    virtual void AdvanceFade();
    virtual int SetBackwardTime(u32 frames);
    virtual int SetForwardTime(u32 frames);
    virtual int IsAtStart();
    virtual int IsAtEnd();

    void SetToStart();
    void SetToEnd();
    int IsBetweenStartAndEnd();
};

#endif /* FADER_HPP */
