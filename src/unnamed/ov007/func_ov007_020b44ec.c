#include "Ov007MenuState.h"

extern int func_ov007_020b58e4(void* t);
extern void func_ov007_020ae834(void* t);
extern int func_ov007_020b5068(void* t);
extern void func_ov007_020b50e8(void* t);
extern void func_ov007_020b5bf0(void* t);

/* *self: the 0x2c-byte func_ov007_020aea6c record; only its +4 Ov007MenuState has a header. */
void func_ov007_020b44ec(void* self) {
    int* o = *(int**)self;
    void* p24 = *(void**)((char*)o + 0x24);
    if (*(unsigned short*)p24 == 0xa) return;
    Ov007MenuState *menu = *(Ov007MenuState **)((char *)o + 4);
    if (menu->stateWork == 0xff)
        return;
    short r = (short)func_ov007_020b58e4(self);
    menu = *(Ov007MenuState **)((char *)o + 4);
    menu->requestedState = r;
    func_ov007_020ae834(o);
    menu = *(Ov007MenuState **)((char *)o + 4);
    switch (menu->currentState) {
    case 0:
        func_ov007_020b5068(self);
        break;
    case 2:
        func_ov007_020b50e8(self);
        break;
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        break;
    }
    if (*(int*)((char*)o + 0x20) == 0) return;
    func_ov007_020b5bf0(self);
}
