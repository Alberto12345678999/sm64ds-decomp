#include "types.h"
/* NitroSystem's NNSSndHandle and NNSSndSeqPlayer, cut to the sequence number
   (the layout as the Sonic Rush Adventure decomp spells it; SoundEngine.cpp's
   struct E1 is the same object, its fader at 0x1c, player number at 0x3c). */
typedef struct NNSSndSeqPlayer {
    u8 pad[0x38];
    u16 seqNo; /* 0x38 */
} NNSSndSeqPlayer;
typedef struct NNSSndHandle {
    NNSSndSeqPlayer *player;
} NNSSndHandle;
extern int data_020a4c5c[];
extern int data_020a4c4c[];
extern u16 data_020a4c48[];

void func_0204f82c(void *a, int b, int c);
void func_0204f86c(void *a, int b, int c);

/* For the three sequences that have them (0x3b, 0x3d, 0x3e), set the volume
   (data_020a4c5c, 0..0x7f000) of two track masks (data_020a4c48) for `mode`,
   and send each through func_0204f82c; a track set to 0 also gets
   func_0204f86c(a, mask, 1). func_02011dcc calls it with data_0208e438 after
   func_02051fb4 succeeds on the handle at data_0209b4a0. func_020494cc sets
   the matching targets and steps (data_020a4c54, data_020a4c4c). */
void func_0204921c(NNSSndHandle *a, int mode) {
    int i;
    int id;
    NNSSndSeqPlayer *p;

    if (a == 0)
        return;
    p = a->player;
    if (p == 0)
        return;

    id = p->seqNo;

    if (mode == 0) {
        if (id != 0x3b)
            return;
        data_020a4c5c[0] = 0x7f000;
        data_020a4c4c[0] = 0;
        data_020a4c48[0] = 3;
        data_020a4c5c[1] = 0;
        data_020a4c4c[1] = 0;
        data_020a4c48[1] = 0x3ffc;
    } else if (mode == 1) {
        if (id != 0x3b)
            return;
        data_020a4c5c[0] = 0;
        data_020a4c4c[0] = 0;
        data_020a4c48[0] = 3;
        data_020a4c5c[1] = 0;
        data_020a4c4c[1] = 0;
        data_020a4c48[1] = 0x3ffc;
    } else if (mode == 2) {
        if (id != 0x3b)
            return;
        data_020a4c5c[0] = 0x7f000;
        data_020a4c4c[0] = 0;
        data_020a4c48[0] = 3;
        data_020a4c5c[1] = 0x7f000;
        data_020a4c4c[1] = 0;
        data_020a4c48[1] = 0x3ffc;
    } else if (mode == 3) {
        if (id != 0x3d)
            return;
        data_020a4c5c[0] = 0x7f000;
        data_020a4c4c[0] = 0;
        data_020a4c48[0] = 0x70;
        data_020a4c4c[1] = 0;
        data_020a4c48[1] = 0;
    } else if (mode == 4) {
        if (id != 0x3d)
            return;
        data_020a4c5c[0] = 0;
        data_020a4c4c[0] = 0;
        data_020a4c48[0] = 0x70;
        data_020a4c4c[1] = 0;
        data_020a4c48[1] = 0;
    } else if (mode == 5) {
        if (id != 0x3e)
            return;
        data_020a4c5c[0] = 0;
        data_020a4c4c[0] = 0;
        data_020a4c48[0] = 8;
        data_020a4c5c[1] = 0x7f000;
        data_020a4c4c[1] = 0;
        data_020a4c48[1] = 0x100;
    } else {
        if (mode != 6)
            return;
        if (id != 0x3e)
            return;
        data_020a4c5c[0] = 0x7f000;
        data_020a4c4c[0] = 0;
        data_020a4c48[0] = 8;
        data_020a4c5c[1] = 0;
        data_020a4c4c[1] = 0;
        data_020a4c48[1] = 0x100;
    }

    for (i = 0; i < 2; i++) {
        if (data_020a4c5c[i] < 0)
            data_020a4c5c[i] = 0;
        else if (data_020a4c5c[i] > 0x7f000)
            data_020a4c5c[i] = 0x7f000;
        func_0204f82c(a, data_020a4c48[i], data_020a4c5c[i] >> 12);
        if (data_020a4c5c[i] == 0)
            func_0204f86c(a, data_020a4c48[i], 1);
    }
}
