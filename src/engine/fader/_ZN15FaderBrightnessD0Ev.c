/* FaderBrightness::~FaderBrightness (deleting / D0) at 0x020177e8
 *   [this+0] = _ZTV15dFdBrightness_c (0x0208eacc)
 *   bl 0x02017838 = FaderBrightness::~FaderBrightness (D2/base)
 *   bl 0x0203cbcc = Memory::operator_delete2(this)
 * returns this.
 */

struct FaderBrightness {
    void **vtable; /* 0x0 */
};

extern void *_ZTV15dFdBrightness_c[];

extern void *_ZN5FaderD2Ev(struct FaderBrightness *thiz);  /* 0x02017838 */
extern void _ZN6Memory16operator_delete2EPv(void *ptr);        /* 0x0203cbcc */

struct FaderBrightness *_ZN15FaderBrightnessD0Ev(struct FaderBrightness *thiz)
{
    thiz->vtable = (void **)_ZTV15dFdBrightness_c;
    _ZN5FaderD2Ev(thiz);
    _ZN6Memory16operator_delete2EPv(thiz);
    return thiz;
}
