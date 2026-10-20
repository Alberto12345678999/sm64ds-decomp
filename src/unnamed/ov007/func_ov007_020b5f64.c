#include "types.h"
#include "Ov007MenuState.h"
#include "Ov007Tween.h"
extern u8 data_ov007_0210342c[];

/* *self: the func_ov007_020aea6c record; only its +4 Ov007MenuState has a header.
 * self+0x10 is the Ov007Tween func_ov007_020b4c04 binds to self+0xc. */
void func_ov007_020b5f64(char *self)
{
    char *p;
    char *g;
    int state;
    int x;
    int sel;
    int y;
    Ov007Tween *q;
    int w;

    p = *(char**)self;
    state = *(u16*)p - 0xe;
    g = *(char**)data_ov007_0210342c;
    sel = (*(Ov007MenuState **)(g + 8))->currentState;
    x = *(short*)(self + 0x18);
    y = *(short*)(self + 0x1a);

    switch (sel) {
    case 0:
        x = *(short*)(*(char**)(p + 0x24) + 2);
        y = *(short*)(*(char**)(p + 0x24) + 4);
        break;
    case 1:
        y = 0x24;
        break;
    case 3:
    case 6:
        y = 0x58;
        break;
    case 7:
        if (state == *(int*)(g + 0x58) || state == *(int*)(g + 0x5c))
            y = 0x24;
        else
            y = 0x58;
        break;
    case 9:
        if (state == *(int*)(g + 0x58))
            y = 0x24;
        else
            y = 0x58;
        break;
    }

    if ((*(Ov007MenuState **)(p + 4))->stateWork == 2)
        (*(Ov007MenuState **)(p + 4))->stateWork = 0;

    if (x != *(short*)(self + 0x18) || y != *(short*)(self + 0x1a)) {
        *(short*)(self + 0x14) = (short)(*(int*)(p + 8) >> 12);
        *(short*)(self + 0x16) = (short)(*(int*)(p + 0xc) >> 12);
        *(short*)(self + 0x18) = x;
        *(short*)(self + 0x1a) = y;
        q = *(Ov007Tween **)(self + 0x10);
        q->state = 1;
        q->mode = 1;
        q->t = 0;
        q->step = 0xa0;
        q->from = 0;
        *q->out = q->from;
        q->to = 0x1000;
    } else if ((*(Ov007Tween **)(self + 0x10))->state == 3) {
        if ((*(Ov007MenuState **)(p + 4))->stateWork == 1)
            (*(Ov007MenuState **)(p + 4))->stateWork = 2;
    }

    if ((*(Ov007Tween **)(self + 0x10))->state == 3)
        return;

    w = *(int*)(self + 0xc);
    *(int*)(p + 8) = (int)(((s64)(0x1000 - w) * ((int)*(short*)(self + 0x14) << 12)
                          + (s64)w * ((int)*(short*)(self + 0x18) << 12)) >> 12);
    *(int*)(p + 0xc) = (int)(((s64)(0x1000 - w) * ((int)*(short*)(self + 0x16) << 12)
                            + (s64)w * ((int)*(short*)(self + 0x1a) << 12)) >> 12);
}
