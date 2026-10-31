//cpp
#include "Ov007MenuState.h"
#include "Ov007Work.h"
#include "cstd.h"
#include "Ov007Item.h"

extern "C" {

extern int func_ov007_020b8fb4(void);
extern void func_ov007_020af260(int, int, int *, int *);
extern Ov007MenuState *func_ov007_020b8f64(void);
extern Ov007MenuState *func_ov007_020b8f50(void);
extern void func_ov007_020b9640(void);

typedef char
    Ov007Work_itemNodes_must_be_at_0xa4[(int)&((Ov007Work *)0)->itemNodes == 0xa4 ? 1 : -1];

/* Every 0xf0 ticks of states[1], from tick 0x3c on, re-arms item node 1's
 * 0x3c-frame wiggle; func_ov007_020af260 picks the state requests below.
 * func_ov007_020b8f64 and func_ov007_020b8f50 return the picker scene's
 * states[2] and states[3] (data_ov007_02104ba0[3] and [4]); their externs
 * keep the tree's int return, so the results are cast here. */
void func_ov007_020aefb4(void) {
    int r6 = 0;
    int n = WORK->states[1]->stateTicks - 0x3c;
    if (n >= 0) {
        int rem = cstd::mod(n, 0xf0);
        int quo = cstd::div(n - rem, 0xf0);
        if (rem == 0) {
            Ov007Item *p = WORK->itemNodes[1]->item;
            p->wiggleFrames = 0x3c;
            p->wiggleTimer = p->wiggleFrames;
        }
        int r7 = (WORK->states[0]->previousState == 3) ? 1 : 0;
        if (func_ov007_020b8fb4() != 0 && quo >= r7) {
            int a = -1, b = -1;
            func_ov007_020af260(quo, rem, &a, &b);
            if (a != -1)
                func_ov007_020b8f64()->requestedState = (short)a;
            if (b != -1)
                func_ov007_020b8f50()->requestedState = (short)b;
        } else {
            r6 = 1;
        }
    } else {
        r6 = 1;
    }
    if (r6) {
        func_ov007_020b8f64()->requestedState = 0;
        func_ov007_020b8f50()->requestedState = 0;
    }
    func_ov007_020b9640();
}
}
