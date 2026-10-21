/* func_ov007_020b45b0 at 0x020b45b0
 *
 * Matched byte-for-byte with mwccarm 1.2/sp2p3 (ov007).
 */
#include "Ov007MenuState.h"

/* The 0x2c-byte record func_ov007_020aea6c allocates; names as in
 * func_ov007_020b46b0, only the slots read here. */
typedef struct Ov007Item {
    u16 id; /* 0x00: func_ov007_020b4c04's index */
    char pad_02[2];
    Ov007MenuState *state; /* 0x04: func_ov007_020c9388(1) */
    char pad_08[8];
    s32 fade; /* 0x10: Q12; selectable once fully faded in (>= 0x1000) */
} Ov007Item;

/* The 0x1c record func_ov007_020b4c04 returns (names as in that file). */
typedef struct Ov007ItemView {
    Ov007Item *item; /* 0x00 */
} Ov007ItemView;

/* One 0xc-byte entry per item id; only the flags word is read (as in
 * func_ov007_020b46b0): bit 0 never selectable, bit 1 selectable before
 * the fade-in ends. */
struct DataEntry { int flags; char pad_04[8]; };
extern struct DataEntry data_ov007_020d77dc[];
extern int func_ov007_020b79e4(void);
extern int func_ov007_020b63e4(void *t);

/* t keeps the void * spelling of the callers' declarations; `view` is the
 * typed view. */
void func_ov007_020b45b0(void *t) {
    Ov007ItemView *view = (Ov007ItemView *)t;
    Ov007Item *p = view->item;
    int call_it = 0;
    int t0 = 0;
    int b6 = 0;

    if (p->state->currentState == 0) {
        if (p->fade >= 0x1000 ||
            (data_ov007_020d77dc[view->item->id].flags & 2))
            b6 = 1;
    }
    if (b6) {
        if (!(data_ov007_020d77dc[view->item->id].flags & 1))
            t0 = 1;
    }
    if (t0) {
        int ok = 1;
        if (func_ov007_020b79e4()) {
            int special = 0;
            if (func_ov007_020b79e4()) {
                unsigned short id2 = view->item->id;
                int x = ok;
                if (id2 != 0x16 && id2 != 0x17) x = special;
                if (x) special = 1;
            }
            if (!special) ok = 0;
        }
        if (ok) call_it = 1;
    }
    if (!call_it) return;
    func_ov007_020b63e4(t);
}
