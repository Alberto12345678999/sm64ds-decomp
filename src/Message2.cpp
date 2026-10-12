//cpp
/* arm9/Message2 -- talk-window TU, the matched prefix of the
 * Message talk-window run (EndTalk through the byte before func_0201adfc).
 * 0x0201ab04..0x0201adfc, 5 functions. Definitions are descending so the
 * default reverse emission is ROM-ascending.
 *
 * Stop: src/unnamed/arm9/0201/func_0201adfc.c does not reproduce on
 * 2004/b56 (object 0x304 against ROM 0x104), including as its own C file.
 * func_0201b100 and everything above it stay out so the range stays contiguous.
 */
#include "types.h"

struct Message {
    static void EndTalk();
    static void PrepareTalk();
};

extern "C" {
extern u8 *data_0209d6f4;
}

extern "C" void _ZN7Message7AddCharEc(int c);
// @symbol func_0201adac
extern "C" void func_0201adac(void) {
    /* Calls Message::AddChar twice with the font byte and the next byte.
       Index is data_0209d6f4 bytes [3] and [4], looked up in data_0208ee6c. */

    struct MsgTextChar {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 indexHi;  /* offset 3 */
    u8 indexLo;  /* offset 4 */
    };
    extern u8 data_0208ee6c[];
    struct MsgTextChar* state = (struct MsgTextChar*)data_0209d6f4;
    u16 idx = state->indexLo | (state->indexHi << 8);
    _ZN7Message7AddCharEc(data_0208ee6c[idx]);
    _ZN7Message7AddCharEc((data_0208ee6c[idx] + 1) & 0xff);
}

extern "C" u8 NumStars(void);
extern "C" int func_020138dc(void);
extern "C" int _ZN8SaveData22NumGlowingRabbitsFoundEv(void);
extern "C" int __aeabi_idiv(int, int);
extern "C" void _ZN7Message7AddCharEc(int c);
// @symbol func_0201aca4
extern "C" void func_0201aca4(void) {

    struct MsgTextChar {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 indexHi;  /* 3 */
    u8 indexLo;  /* 4 */
    u8 mode;     /* 5 */
    u8 base;     /* 6 */
    };

    extern u8 data_0208ee74[];
    extern u16 data_0208ee64[];
    struct MsgTextChar* state = (struct MsgTextChar*)data_0209d6f4;
    u16 idx = state->indexLo | (state->indexHi << 8);
    switch (idx) {
        case 0: {
            u8 mode = state->mode;
            u8 num = 0;
            int leading = 0;
            u8 base = state->base;
            int i;
            switch (mode) {
                case 0: num = base - NumStars(); break;
                case 1: num = func_020138dc(); break;
                case 2: num = base - _ZN8SaveData22NumGlowingRabbitsFoundEv(); break;
            }
            for (i = 0; i < 3; i++) {
                int q = __aeabi_idiv(num, data_0208ee64[i]);
                if (q != 0 || leading != 0 || i == 2) {
                    _ZN7Message7AddCharEc(data_0208ee74[q]);
                    leading = 1;
                }
                num = num % data_0208ee64[i];
            }
            break;
        }
        case 1:
            break;
    }
}

extern "C" void _ZN7Message7AddCharEc(int c);
// @symbol func_0201ab6c
extern "C" void func_0201ab6c(void) {

    struct S { u8 b[8]; };
    extern u8 data_0209d6b4;
    extern u8 data_0209d688;
    extern u8 data_0209d68c;
    extern u8 data_0209d6b0;
    extern u8 data_0209d6e4[];
    extern u8 data_0209d694;
    struct S *p = (struct S *)data_0209d6f4;
    u16 v = p->b[4] | (p->b[3] << 8);
    u8 idx;
    switch (v) {
    case 0:
        data_0209d688 = data_0209d6b4;
        break;
    case 1:
        idx = data_0209d68c;
        data_0209d68c = idx + 1;
        data_0209d6e4[idx] = data_0209d6b0;
        _ZN7Message7AddCharEc(0x4d);
        data_0209d694 = 1;
        break;
    case 2:
        idx = data_0209d68c;
        data_0209d68c = idx + 1;
        data_0209d6e4[idx] = data_0209d6b4;
        _ZN7Message7AddCharEc(0x4d);
        data_0209d694 = 2;
        break;
    case 3:
        idx = data_0209d68c;
        data_0209d68c = idx + 1;
        data_0209d6e4[idx] = data_0209d6b4;
        _ZN7Message7AddCharEc(0x4d);
        data_0209d694 = 3;
        break;
    }
}

extern "C" {
extern u8 data_0209d664;  /* nonzero while a dialogue box is up */
void _ZN5Sound17ChangeMusicVolumeEj5Fix12IiE(u32 vol, Fix12i speed);
}
// @symbol _ZN7Message11PrepareTalkEv
void Message::PrepareTalk()
{
    /* Message::PrepareTalk() at 0x0201ab38 -- static, no `this`.
     *
     * Ducks the music before dialogue: volume to 0x40 over 0xc999/4096 of a frame, and
     * raises the "in talk" flag. EndTalk is the exact inverse.
     *
     * Sound::ChangeMusicVolume stays an `extern "C"` free function on purpose. Its
     * second parameter is a by-value `Fix12<int>`, and declaring a method with a
     * by-value class parameter is a measured dead end -- mwccarm homes r0-r3 to the
     * stack for it, +0x14, on all 25 sweep versions at every optimisation level. See
     * runbook-type-reconstruction.md section 7.
     */
    _ZN5Sound17ChangeMusicVolumeEj5Fix12IiE(0x40, 0x0000c999);
    data_0209d664 = 1;
}

extern "C" {
extern u8 data_0209d664;  /* nonzero while a dialogue box is up */
void _ZN5Sound17ChangeMusicVolumeEj5Fix12IiE(u32 vol, Fix12i speed);
}
// @symbol _ZN7Message7EndTalkEv
void Message::EndTalk()
{
    /* Message::EndTalk() at 0x0201ab04 -- static, no `this`.
     *
     * The inverse of PrepareTalk: restores music to full volume (0x7f) over
     * 0x64cc/4096 of a frame -- a slower ramp back up than the duck down -- and clears
     * the "in talk" flag.
     *
     * Sound::ChangeMusicVolume stays `extern "C"`: by-value `Fix12<int>` parameter,
     * runbook-type-reconstruction.md section 7.
     */
    _ZN5Sound17ChangeMusicVolumeEj5Fix12IiE(0x7f, 0x000064cc);
    data_0209d664 = 0;
}
