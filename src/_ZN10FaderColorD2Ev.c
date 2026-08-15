/* FaderColor::~FaderColor() at 0x02017574 -- the BASE-object destructor (D2).
 *
 * This was named _ZN5ColorD1Ev, and there is no class `Color`. It writes
 * _ZTV10dFdColor_c, which the ROM's RTTI says is dFdColor_c's vtable -- the same
 * table _ZN10FaderColorD1Ev writes -- and a vtable belongs to exactly one class.
 * It is a D2 rather than a D1 because nothing in any vtable points at it, while
 * six derived-class destructors across three classes (FaderWipe, dFdDummy_c and
 * dWipe_c) call it directly as their base-subobject dtor.
 * notes/dtor-variant-audit.md; chain in notes/rtti-reconciliation.md.
 */

extern int _ZTV10dFdColor_c[];          /* FaderColor's vtable, under EAD's name for it */
extern int _ZN15FaderBrightnessD2Ev(int *self); /* FaderBrightness's base-subobject dtor */

int _ZN10FaderColorD2Ev(int *self)
{
    self[0] = (int)_ZTV10dFdColor_c;  /* +0x00 vptr */
    _ZN15FaderBrightnessD2Ev(self);
    return (int)self;
}
