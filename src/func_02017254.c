/* func_02017254 at 0x02017254
 * Single-vtable destructor: write own vtable, call base/helper destructor (0x02017574), return this.
 */
struct Obj { void *vtable; };
extern void *_ZTV10dFdDummy_c[];
extern void _ZN10FaderColorD2Ev(struct Obj *thiz); /* 0x02017574 */
struct Obj *func_02017254(struct Obj *thiz)
{
    thiz->vtable = (void *)_ZTV10dFdDummy_c;
    _ZN10FaderColorD2Ev(thiz);
    return thiz;
}
