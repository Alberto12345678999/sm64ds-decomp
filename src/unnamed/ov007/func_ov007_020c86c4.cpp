//cpp
#include "types.h"
#include "G2x.h"
#include "Ov007Transition.h"

extern "C" {

/* Starts the transition: state 1 from t = 0, with the request cleared, and
 * sets up its effect's registers on each of its screens. Mosaic (1) sets or
 * clears the mosaic bit of BG0..3CNT by the planes mask; blend alpha (2/3)
 * and brightness (4) load BLDCNT and BLDALPHA/BLDY with the start values,
 * which are the end values when the curve runs reversed. */
void func_ov007_020c86c4(Ov007Transition *tr) {
    tr->state = 1;
    tr->t = 0;
    tr->request = 0;

    switch (tr->effect) {
    case 0:
        break;

    case 1: {
        s32 mask = tr->planes;
        if (tr->screens & 1) {
            if (mask & 1)
                *(volatile u16 *)0x4000008 |= 0x40;
            else
                *(volatile u16 *)0x4000008 &= ~0x40;
            if (mask & 2)
                *(volatile u16 *)0x400000a |= 0x40;
            else
                *(volatile u16 *)0x400000a &= ~0x40;
            if (mask & 4)
                *(volatile u16 *)0x400000c |= 0x40;
            else
                *(volatile u16 *)0x400000c &= ~0x40;
            if (mask & 8)
                *(volatile u16 *)0x400000e |= 0x40;
            else
                *(volatile u16 *)0x400000e &= ~0x40;
        }
        if (!(tr->screens & 2))
            return;
        if (mask & 1)
            *(volatile u16 *)0x4001008 |= 0x40;
        else
            *(volatile u16 *)0x4001008 &= ~0x40;
        if (mask & 2)
            *(volatile u16 *)0x400100a |= 0x40;
        else
            *(volatile u16 *)0x400100a &= ~0x40;
        if (mask & 4)
            *(volatile u16 *)0x400100c |= 0x40;
        else
            *(volatile u16 *)0x400100c &= ~0x40;
        if (mask & 8)
            *(volatile u16 *)0x400100e |= 0x40;
        else
            *(volatile u16 *)0x400100e &= ~0x40;
        return;
    }

    case 2:
    case 3:
        if (tr->screens & 1) {
            G2x::SetBlendAlpha((volatile unsigned short *)0x4000050, tr->planes,
                               tr->fx.alpha.planes2,
                               tr->reversed ? tr->fx.alpha.evaTo : tr->fx.alpha.evaFrom,
                               tr->reversed ? tr->fx.alpha.evbTo : tr->fx.alpha.evbFrom);
        }
        if (!(tr->screens & 2))
            return;
        G2x::SetBlendAlpha((volatile unsigned short *)0x4001050, tr->planes, tr->fx.alpha.planes2,
                           tr->reversed ? tr->fx.alpha.evaTo : tr->fx.alpha.evaFrom,
                           tr->reversed ? tr->fx.alpha.evbTo : tr->fx.alpha.evbFrom);
        return;

    case 4:
        if (tr->screens & 1) {
            G2x::SetBlendBrightness((volatile unsigned short *)0x4000050, tr->planes,
                                    tr->reversed ? tr->fx.brightness.to : tr->fx.brightness.from);
        }
        if (!(tr->screens & 2))
            return;
        G2x::SetBlendBrightness((volatile unsigned short *)0x4001050, tr->planes,
                                tr->reversed ? tr->fx.brightness.to : tr->fx.brightness.from);
        return;
    }
}
}
