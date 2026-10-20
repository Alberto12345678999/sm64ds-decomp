#include "Ov007MenuState.h"
#include "Ov007Tween.h"

extern int func_ov007_020c8f98(void* p);
extern void func_ov007_020c1d78(int i);
extern void func_ov007_020b0244(void);
extern void func_ov007_020b7d94(int kind);
extern int func_ov007_020b79e4(void);
extern void func_ov007_020c1d8c(int i);
extern void RequestScreenFade(int a, int b, int c);
extern void func_ov007_020b8188(int a, int b, int c);
extern void func_ov007_020c0638(int a, int b, int c, int d);
extern void func_ov007_020b8070(int n);
extern char* data_ov007_0210342c;

#define G data_ov007_0210342c

/* G has no class or header: its +0x8 and +0xc slots hold Ov007MenuStates (freed by
 * func_ov007_020b65e0 like the other menu states); +0x6c/+0x70 are the Ov007Tweens
 * func_ov007_020b6a84 binds to +0x64/+0x68. */

void func_ov007_020afc44(void)
{
    Ov007MenuState *menu = *(Ov007MenuState **)(G + 8);
    unsigned char* r7 = (unsigned char*)(*(int*)(*(char**)(G + 0x28))) + 0xb;
    int r6 = menu->stateTicks;
    Ov007Tween *r5 = *(Ov007Tween **)(G + 0x6c);
    Ov007Tween *r4 = *(Ov007Tween **)(G + 0x70);
    int v0 = func_ov007_020c8f98(r5);
    int v1 = func_ov007_020c8f98(r4);
    int sb = (v0 == 0);
    int fp = (v1 == 0);
    int st = menu->currentState;

    switch (st) {
    case 3:
        if (r6 == 0) {
            func_ov007_020c1d78(0);
            func_ov007_020b0244();
            (*(Ov007MenuState **)(G + 0xc))->requestedState = 0xa;
        }
        switch (menu->stateWork) {
        case 0: {
            int idx = *(int*)(G + 0x58);
            if (idx != -1) {
                if (r7[idx] != 0) {
                    menu->requestedState = 4;
                } else {
                    *(int*)(G + 0x58) = -1;
                    func_ov007_020b7d94(3);
                    menu->stateWork = 1;
                }
            }
            break;
        }
        case 1:
            if (func_ov007_020b79e4() == 0) {
                menu->stateWork = 0;
            }
            break;
        }
        break;
    case 4:
        if (r6 == 0) {
            func_ov007_020c1d8c(0);
            RequestScreenFade(8, 0xa, 0);
            (*(Ov007MenuState **)(G + 0xc))->requestedState = 0xb;
            func_ov007_020b8188(*(int*)(G + 0x58), *(int*)(G + 0x28), *(int*)(G + 0x60));
            r5->state = 1;
            r5->mode = 1;
            r5->t = 0;
            r5->step = 0;
            r5->from = 0;
            *r5->out = r5->from;
            r5->to = 0;
            r4->state = 1;
            r4->mode = 1;
            r4->t = 0;
            r4->step = 0x2000;
            r4->from = 0x30000;
            *r4->out = r4->from;
            r4->to = 0x1000;
        } else if (v1 != 0) {
            menu->requestedState = 2;
        }
        break;
    case 2:
        if (r6 == 0) {
            func_ov007_020c1d78(0);
        }
        {
            int prev = *(int*)(G + 0x5c);
            if (prev != -1) {
                if (prev != *(int*)(G + 0x58)) {
                    menu->requestedState = 5;
                }
            }
        }
        break;
    case 5: {
        int sl = 0x20000;
        int prev = *(int*)(G + 0x5c);
        int sp4 = -0x20000;
        if (prev < *(int*)(G + 0x58)) {
            sp4 = 0x20000;
            sl = -0x20000;
        }
        if (r6 == 0) {
            func_ov007_020c1d8c(0);
            r5->state = 1;
            r5->mode = 1;
            r5->t = 0;
            r5->step = 0x3000;
            r5->from = 0;
            *r5->out = r5->from;
            r5->to = sp4;
        } else if (v0 != 0) {
            switch (menu->stateWork) {
            case 1:
                *(int*)(G + 0x58) = prev;
                *(int*)(G + 0x5c) = -1;
                menu->requestedState = 2;
                break;
            case 0:
            case 2:
                if (r7[prev] != 0) {
                    if (func_ov007_020b79e4() == 0) {
                        func_ov007_020c1d8c(0);
                        if (menu->stateWork == 2) {
                            RequestScreenFade(8, 0xa, 0);
                            (*(Ov007MenuState **)(G + 0xc))->requestedState = 0xb;
                        }
                        func_ov007_020b8188(*(int*)(G + 0x5c), *(int*)(G + 0x28), *(int*)(G + 0x60));
                        sb = 1;
                        r5->state = 1;
                        r5->mode = 1;
                        r5->t = 0;
                        r5->step = 0x3000;
                        r5->from = sl;
                        *r5->out = r5->from;
                        r5->to = 0;
                        r4->state = 1;
                        r4->mode = 1;
                        r4->t = 0;
                        r4->step = 0x1000;
                        r4->from = 0x1000;
                        *r4->out = r4->from;
                        r4->to = 0x1000;
                        menu->stateWork = 1;
                    }
                } else {
                    int t;
                    RequestScreenFade(8, 8, 0);
                    (*(Ov007MenuState **)(G + 0xc))->requestedState = 0xa;
                    t = *(int*)(G + 0x58);
                    *(int*)(G + 0x58) = *(int*)(G + 0x5c);
                    *(int*)(G + 0x5c) = t;
                    func_ov007_020b7d94(3);
                    func_ov007_020c0638(*(int*)(*(char**)(G + 0xe0) + 4), 0, 0, 0);
                    menu->stateWork = 2;
                }
                break;
            }
        }
        break;
    }
    case 6:
        if (r6 == 0) {
            func_ov007_020c1d8c(0);
            if (menu->previousState == 3) {
                menu->requestedState = 0;
            } else {
                RequestScreenFade(8, 8, 0);
                (*(Ov007MenuState **)(G + 0xc))->requestedState = 0xa;
                r4->state = 1;
                r4->mode = 1;
                r4->t = 0;
                r4->step = 0x2000;
                r4->from = 0x1000;
                *r4->out = r4->from;
                r4->to = 0x30000;
            }
        } else if (v1 != 0) {
            if (menu->previousState == 2) {
                menu->requestedState = 3;
            } else {
                menu->requestedState = 0;
            }
        }
        break;
    }

    if (menu->currentState == 3)
        return;
    if (func_ov007_020b79e4() != 0) return;
    if (sb != 0) {
        func_ov007_020c0638(*(int*)(*(char**)(G + 0xe0) + 4), (*(int*)(G + 0x64) >> 0xc) * 8, 0, 0);
        func_ov007_020c0638(*(int*)(*(char**)(G + 0xe4) + 4), (*(int*)(G + 0x64) >> 0xc) * 8, 0, 0);
    }
    if (fp == 0) return;
    func_ov007_020b8070(*(int*)(G + 0x68) >> 0xc);
}
