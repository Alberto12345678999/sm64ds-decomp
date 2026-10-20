#include "Ov007MenuState.h"

extern void func_ov007_020bd9e4(int);
extern int *data_ov007_0210342c;
/* data_ov007_0210342c's record has no class or header; its slot 2 holds an Ov007MenuState. */
void func_ov007_020aec94(int r4) {
    int *g = data_ov007_0210342c;
    int *r2 = (int *)(g[0xa]);
    int r5 = (*(unsigned char *)((char *)r2 + 0x37) == 1);
    int r6 = (*(unsigned char *)((char *)r2 + 0x38) == 1);
    g[4] = r4;
    func_ov007_020bd9e4(0x50);
    if (r4 == 9) {
        if (r5 != 0 || r6 != 0) {
            int *p = (int *)(data_ov007_0210342c[0xa]);
            *(unsigned char *)((char *)p + 0x39) = 1;
            ((Ov007MenuState *)data_ov007_0210342c[2])->requestedState = 9;
            return;
        }
    }
    if (r4 == 7) {
        if (r6 != 0) {
            int *p = (int *)(data_ov007_0210342c[0xa]);
            *(unsigned char *)((char *)p + 0x39) = 2;
            ((Ov007MenuState *)data_ov007_0210342c[2])->requestedState = 9;
            return;
        }
    }
    if ((unsigned int)(r4 - 3) <= 2) {
        ((Ov007MenuState *)data_ov007_0210342c[2])->requestedState = 0xb;
    } else {
        ((Ov007MenuState *)data_ov007_0210342c[2])->requestedState = 6;
    }
}
