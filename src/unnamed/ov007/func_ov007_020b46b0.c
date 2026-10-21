/* Title/menu per-element stylus hit test.
 *
 * func_ov007_020aed98 calls this once per element per frame, for all 24
 * elements: func_ov007_020b46b0(ctx[0x114 + i*4], ctx[0x50]), where ctx is
 * data_ov007_0210342c.  arg0 is the element (an Ov007ItemView: the item and
 * the sprite that places it), arg1 is the Ov007Touch record that
 * func_ov007_020c1db0 maintains.  Returns nothing; a hit acts by calling
 * func_ov007_020b63e4, which parks the chosen item's id in ctx+0x180.
 *
 * Two independent paths:
 *
 *   1. PRESS.  Gated on down-now && !down-last-frame, i.e. the frame the
 *      stylus first touches, plus releasedFrames >= 1.  Tests the stylus
 *      point against the item's hitBox, offset by the sprite's 20.12 screen
 *      position >> 12.  A hit selects immediately.  If that misses, three
 *      element types get a second chance against a hardcoded screen rect:
 *      x 8..0x66, y 0x50..0x60 for type 0xc (when settings->[0][9] is 0) or
 *      type 0xd (when it is not), and x 8..0x48, y 0x20..0x30 for type 9.
 *
 *   2. HOLD.  Only while states[0] is in state 3, and only for element types
 *      3 and 6.  Requires the stylus merely to be down, not freshly pressed, and
 *      counts frames in the item state's stateWork; past 0x3a it selects.  Any
 *      frame the element is not held resets that counter to 0.
 *
 * Two things about the box shape below are load-bearing, not style.  Each axis is
 * shifted once into its position local rather than at each of the four edges, and
 * the object and rect pointers are re-dereferenced in every edge expression rather
 * than bound to locals.  Neither alone is enough.  Measured at 2004/b56 over all
 * four combinations: bound pointers with per-edge shifts scores 37 divergences,
 * re-dereferencing with per-edge shifts also 37, bound pointers with pre-shifted
 * positions 51, and only the two together 0.
 *
 * The re-dereferencing requirement is narrower than it looks, so measure before
 * tidying rather than assuming the whole shape is fragile.  Binding each pointer on
 * its own, against the shipped source: binding the rect costs 49 divergences,
 * binding the object costs 14, and binding the transform is FREE at 0.  The
 * transform is written out longhand below only to keep the four edges reading
 * alike.
 */
#include "Ov007MenuState.h"
#include "Ov007Sprite.h"
#include "Ov007Touch.h"

/* The 0x2c-byte record func_ov007_020aea6c allocates; names as in
 * func_ov007_020b4c04 and func_ov007_020b5bf0, only the slots read here. */
typedef struct Ov007Item {
    u16 id; /* 0x00 */
    char pad_02[2];
    Ov007MenuState *state; /* 0x04: func_ov007_020c9388(1); stateWork counts hold frames here */
    char pad_08[8];
    s32 fade; /* 0x10: Q12; selectable once fully faded in (>= 0x1000) */
    char pad_14[0x14];
    struct Ov007HitBox *hitBox; /* 0x28 */
} Ov007Item;

/* The 0x14-byte touch rectangles func_ov007_020b4c04 points hitBox at
 * (data_ov007_020d76c0 etc.): pixel offsets from the sprite's screen position. */
typedef struct Ov007HitBox {
    char pad_00[4];
    s32 minX; /* 0x04 */
    s32 minY; /* 0x08 */
    s32 maxX; /* 0x0c */
    s32 maxY; /* 0x10 */
} Ov007HitBox;

typedef char Ov007HitBox_size_must_be_0x14[sizeof(Ov007HitBox) == 0x14 ? 1 : -1];

/* The 0x1c record func_ov007_020b4c04 returns (names as in that file). */
typedef struct Ov007ItemView {
    Ov007Item *item;     /* 0x00 */
    Ov007Sprite *sprite; /* 0x04 */
} Ov007ItemView;

/* data_ov007_0210342c: the overlay's manager; names as in func_ov007_020afc44. */
typedef struct Ov007Work {
    char pad_00[4];
    Ov007MenuState *states[3]; /* 0x04 */
    char pad_10[0x18];
    struct Ov007Settings *settings; /* 0x28: its first word points at a record
                                     * whose byte 9 picks item 0xc or 0xd */
} Ov007Work;

typedef struct { u32 f0; u32 f4; u32 f8; } Tbl;
extern Tbl data_ov007_020d77dc[];
extern char* data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work*)data_ov007_0210342c)

extern int func_ov007_020b79e4(void);
extern int func_ov007_020c1da0(int i);
extern void func_ov007_020b63e4(char** a);
extern int func_ov007_020b8f78(void);
extern int func_ov007_020b8fa0(void);
extern void func_ov007_020c1d78(int i);

/* The ROM contains this block twice, verbatim, once per path.  Twenty lines of
 * hand duplication is the signature of an inlined helper, so it is written as one.
 * `inline` is required, not stylistic: plain `static` is not inlined at -O4 and
 * emits a separate symbol, which breaks the size. Byte-identical to hand
 * duplication either way, so this costs nothing at the gate. */
static inline int elem_selectable(Ov007ItemView *elem) {
    Ov007Item *obj = elem->item;
    int sel = 0;
    int gate2 = 0;
    int gate1 = 0;
    if (obj->state->currentState == 0) {
        if (obj->fade >= 0x1000 || (data_ov007_020d77dc[elem->item->id].f0 & 2))
            gate1 = 1;
    }
    if (gate1) {
        if (!(data_ov007_020d77dc[elem->item->id].f0 & 1))
            gate2 = 1;
    }
    if (gate2) {
        int ok = 1;
        if (func_ov007_020b79e4()) {
            int sub = 0;
            if (func_ov007_020b79e4()) {
                u16 id2 = elem->item->id;
                /* NOT a plain `if (id2 == 0x16 || id2 == 0x17) sub = 1;`. That
                 * compiles four bytes short. */
                int x = ok;
                if (id2 != 0x16 && id2 != 0x17) x = sub;
                if (x) sub = 1;
            }
            if (!sub) ok = 0;
        }
        if (ok) sel = 1;
    }
    return sel;
}

void func_ov007_020b46b0(void* arg0, void* arg1)
{
    Ov007ItemView *elem = (Ov007ItemView *)arg0;
    Ov007Touch *tp = (Ov007Touch *)arg1;
    int held = 0;

    {
        if (elem_selectable(elem) && func_ov007_020c1da0(0) == 0) {
            int armed = 0;
            int fresh = 0;
            int touching = tp->cur.touch;
            if (touching != 0) {
                if (tp->prev.touch == 0)
                    fresh = 1;
            }
            if (fresh) {
                if (tp->releasedFrames >= 1U)
                    armed = 1;
            }
            if (armed) {
                int pos_y = elem->sprite->screenY >> 12;
                int pos_x = elem->sprite->screenX >> 12;
                int max_y = elem->item->hitBox->maxY + pos_y;
                int min_y = elem->item->hitBox->minY + pos_y;
                int max_x = elem->item->hitBox->maxX + pos_x;
                int min_x = elem->item->hitBox->minX + pos_x;
                if (touching != 0 && (s32)tp->cur.x >= min_x && (s32)tp->cur.x <= max_x &&
                    (s32)tp->cur.y >= min_y && (s32)tp->cur.y <= max_y) {
                    func_ov007_020b63e4((char**)arg0);
                } else {
                    u16 t = elem->item->id;
                    if ((t == 0xc && (*(u8 **)WORK->settings)[9] == 0) ||
                        (t == 0xd && (*(u8 **)WORK->settings)[9] != 0)) {
                        if (touching != 0) {
                            s32 x = tp->cur.x;
                            if (x >= 8 && x <= 0x66) {
                                s32 y = tp->cur.y;
                                if (y >= 0x50 && y <= 0x60)
                                    func_ov007_020b63e4((char**)arg0);
                            }
                        }
                    } else if (t == 9) {
                        if (touching != 0) {
                            s32 x = tp->cur.x;
                            if (x >= 8 && x <= 0x48) {
                                s32 y = tp->cur.y;
                                if (y >= 0x20 && y <= 0x30)
                                    func_ov007_020b63e4((char**)arg0);
                            }
                        }
                    }
                }
                goto done; /* kept: an !armed test on HOLD (0x4a0) or an inline press helper re-lays it */
            }
        }
    }

    if (WORK->states[0]->currentState == 3) {
        /* Through arg0, not elem: reading it through elem lets the compiler
         * keep the item in a register for elem_selectable and drops 12 bytes. */
        u16 t0 = ((Ov007ItemView *)arg0)->item->id;
        if (t0 == 3 || t0 == 6) {
            if (elem_selectable(elem) && func_ov007_020c1da0(0) == 0 && tp->cur.touch != 0 &&
                *(s16 *)func_ov007_020b8f78() == 5 && func_ov007_020b8fa0() == 0) {
                int pos_y = elem->sprite->screenY >> 12;
                int pos_x = elem->sprite->screenX >> 12;
                int max_y = elem->item->hitBox->maxY + pos_y;
                int min_y = elem->item->hitBox->minY + pos_y;
                int max_x = elem->item->hitBox->maxX + pos_x;
                int min_x = elem->item->hitBox->minX + pos_x;
                if (tp->cur.touch != 0 && (s32)tp->cur.x >= min_x && (s32)tp->cur.x <= max_x &&
                    (s32)tp->cur.y >= min_y && (s32)tp->cur.y <= max_y) {
                    Ov007MenuState *state = elem->item->state;
                    held = 1;
                    state->stateWork += 1;
                    /* Re-dereferences the element rather than reusing `state`
                     * just above it: reusing the bound local compiles eight bytes
                     * short. Same class as the box shape in the header comment. */
                    if (elem->item->state->stateWork > 0x3a)
                        func_ov007_020b63e4((char**)arg0);
                }
            }
        }
    }

done:
    if (held == 0)
        elem->item->state->stateWork = 0;
    {
        Ov007MenuState *st = elem->item->state;
        if (st->currentState != 2)
            return;
        if (st->requestedState == -1)
            return;
    }
    func_ov007_020c1d78(0);
}