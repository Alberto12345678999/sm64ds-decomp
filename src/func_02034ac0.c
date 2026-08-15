// @symbol func_02034ac0
/* recovered: renamed to Class_Method */
struct MultiBootScene { void **vtable; };
struct Heap;
extern void *_ZTV7dScMB_c[];
extern void *_ZTV5Scene[];
extern void *data_0208e4b8[];
extern void _ZN10FaderColorD1Ev(void *thiz);
extern void _ZN9ActorBaseD2Ev(struct MultiBootScene *thiz);
extern void _ZN6Memory10DeallocateEPvP4Heap(void *ptr, struct Heap *heap);
extern struct Heap *data_020a0eac;

struct MultiBootScene *func_02034ac0(struct MultiBootScene *thiz)
{
    thiz->vtable = (void **)_ZTV7dScMB_c;
    _ZN10FaderColorD1Ev((char *)thiz + 0x50);
    thiz->vtable = (void **)_ZTV5Scene;
    thiz->vtable = (void **)data_0208e4b8;
    _ZN9ActorBaseD2Ev(thiz);
    _ZN6Memory10DeallocateEPvP4Heap(thiz, data_020a0eac);
    return thiz;
}
