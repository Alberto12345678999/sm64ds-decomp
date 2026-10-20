//cpp
#include "dScEntry_c.h"
#include "OAM.h"
#include "OamAttr.h"

extern "C" {
int func_0200f0bc();
extern OamAttr *data_0208a0f8[];
extern int data_0208ee44;

// local extern: OAM.h excludes this Fix12-by-value overload because the scalar
// bridge preserves the retail call ABI; see notes/mwccarm-codegen.md 6az.
OamAttr *_ZN3OAM6RenderEbP7OamAttriiii5Fix12IiEi(int, OamAttr *, int, int, int, int, int, int);
}

// Interleaved sine/cosine samples; even entries are sine.
extern s16 data_02082214[];

// @symbol _ZN10dScEntry_c17RenderWaitingTextEv
void dScEntry_c::RenderWaitingText() {
    OamAttr *glyph = data_0208a0f8[func_0200f0bc()];

    if (mWaiting.waveDelay <= 0) {
        int phase;
        bool waving;

        phase = mWaiting.wavePhase;
        waving = false;
        do {
            int y;
            if (phase >= 0 && phase < 0x10000) {
                waving = true;
                // The intermediate narrowing preserves the retail ARM shifts.
                y = (data_02082214[2 * ((u16)(s16)(u16)phase >> 4)] >> 10) + 96;
            } else {
                y = 96;
            }
            _ZN3OAM6RenderEbP7OamAttriiii5Fix12IiEi(true, glyph, 128, y, -1, -1, 0x1000, 0);
            if (glyph->attr3 == 0xffff)
                break;
            ++glyph;
            phase -= 0x2000;
        } while (true);

        mWaiting.wavePhase += 0x800;
        if (!waving)
            mWaiting.waveDelay = 120;
    } else {
        OAM::RenderSub(glyph, 128, 96);
        mWaiting.waveDelay -= data_0208ee44;
        mWaiting.wavePhase = 0;
    }
}
