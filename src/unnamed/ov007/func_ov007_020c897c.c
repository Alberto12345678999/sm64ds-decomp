#include "Ov007Transition.h"

/* Stops the transition: idle, at t = 1.0, with the request cleared, and
 * turns its effect off on each of its screens. Mosaic (1) clears the mosaic
 * bit of BG0..3CNT; the blend effects (2..4) clear BLDCNT. */
void func_ov007_020c897c(Ov007Transition *tr) {
    tr->state = 0;
    tr->t = 0x1000;
    tr->request = 0;
    switch (tr->effect) {
    case 1:
        if (tr->screens & 1) {
            *(volatile u16 *)0x4000008 &= ~0x40;
            *(volatile u16 *)0x400000a &= ~0x40;
            *(volatile u16 *)0x400000c &= ~0x40;
            *(volatile u16 *)0x400000e &= ~0x40;
        }
        if (tr->screens & 2) {
            *(volatile u16 *)0x4001008 &= ~0x40;
            *(volatile u16 *)0x400100a &= ~0x40;
            *(volatile u16 *)0x400100c &= ~0x40;
            *(volatile u16 *)0x400100e &= ~0x40;
        }
        break;
    case 2:
    case 3:
    case 4:
        if (tr->screens & 1) {
            *(volatile u16 *)0x4000050 = 0;
        }
        if (tr->screens & 2) {
            *(volatile u16 *)0x4001050 = 0;
        }
        break;
    }
}
