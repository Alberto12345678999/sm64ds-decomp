// Restarts the picker scene at data_ov007_02104ba0: settles the picker
// (func_ov007_020c5dec), re-arms awaitingTap, retargets the first tween to
// 0x800 and mirrors that into its output, counts the restart, and requests
// state 5 on states[1].

#include "Ov007MenuState.h"
#include "Ov007Tween.h"

/* The 0x4c record func_ov007_020b9880 allocates; names as in
 * func_ov007_020b91b4, func_ov007_020b9ca8 and func_ov007_020ba05c. The tags
 * keep the extern's spelling. */
typedef struct G {
    void *picker;              /* 0x00: func_ov007_020c690c */
    Ov007MenuState *states[4]; /* 0x04: func_ov007_020c9388; [1] is the main one */
    char pad_14[0x10];
    int restartCount; /* 0x24: counted here */
    char pad_28[8];
    int awaitingTap; /* 0x30: func_ov007_020ba05c clears it on the next fresh press */
    char pad_34[8];
    int tweenOut[2];       /* 0x3c: bound as tweens[i]->out */
    Ov007Tween *tweens[2]; /* 0x44: func_ov007_020c908c */
} G;

typedef char G_size_must_be_0x4c[sizeof(G) == 0x4c ? 1 : -1];

extern G *data_ov007_02104ba0;
extern void func_ov007_020c5dec(void *c);

void func_ov007_020ba2e0(void)
{
    func_ov007_020c5dec(data_ov007_02104ba0->picker);
    data_ov007_02104ba0->awaitingTap = 1;
    data_ov007_02104ba0->tweenOut[1] = 0x1000;
    data_ov007_02104ba0->tweens[0]->to = 0x800;
    data_ov007_02104ba0->tweenOut[0] = data_ov007_02104ba0->tweens[0]->to;
    data_ov007_02104ba0->restartCount += 1;
    data_ov007_02104ba0->states[1]->requestedState = 5;
}
