// @symbol func_ov007_020c9688
/* func_ov007_020c9688 -- ov007 0x020c9688, 0x300 bytes.
 *
 * Builds a sprite bank from a sprite file (func_ov007_020b6d40 builds six
 * into the display record's spriteBanks). The block index
 * func_ov007_020c9a2c fills carries two counted lists; the bank
 * func_ov007_020c12ac allocates carries the two output tables.
 *
 * The first pass walks list A, the cells. Each cell's header word gives
 * the number of 0x14-byte OAM records that follow it; each record is
 * packed into the three OAM attribute halfwords: attr0/attr1 from the
 * x/y halfwords and the affine, mode, mosaic, colour-mode, shape, size and
 * flip bytes (the affine index only for affine entries, the colour-mode bit
 * not for mode 3, bitmap OBJs), attr2 from the tile (0x10), priority (0xe)
 * and palette (0xf).
 *
 * The second pass walks list B, the cell animations. Each 0xc-byte header
 * gives a frame count at +8; func_ov007_020c13a4 sizes the animation, then
 * every 0x18-byte frame contributes a cell (index at +0) and a duration
 * (+2).
 *
 * ONE SPELLING IS LOAD BEARING, measured against the ROM on 2004/b56:
 * THE SECOND PASS WALKS WITH `p`, THE SAME CURSOR THE FIRST PASS USED.
 * Given its own local pointer the second pass is byte-identical except for a
 * three-way rotation of the callee-saved registers -- the cursor colours to
 * r7 and the two hoisted zeroes to sb and r8, where the ROM has the cursor in
 * sb and the zeroes in r8 and r7. Ten instructions, no other difference.
 * Reusing `p` puts all three where the ROM has them. That rotation survived
 * every declaration order of the block (all 120), the function-top ordering
 * climb in the near-miss note, both loop forms, the named-zero and
 * named-init spellings, and every integer width for the counters; only the
 * shared cursor moves it. */
#include "types.h"

typedef struct RecA {
    s16 f0;
    s16 f2;
    u8 f4;
    u8 f5;
    u8 f6;
    u8 f7;
    u8 f8;
    u8 f9;
    u8 fA;
    u8 fB;
    u8 fC;
    u8 fD;
    u8 fE;
    u8 fF;
    u16 f10;
    u16 f12;
} RecA;

/* One 8-byte cell: `count` OAM entries, each packed into three attribute
 * halfwords (attr0..attr2). */
typedef struct Ov007Cell {
    u16 *oam;
    u32 count;
} Ov007Cell;

/* One 0x10-byte cell animation (func_ov007_020c13a4 sizes it): a cell and
 * a duration per frame, as func_ov007_020c0d70 steps through them. */
typedef struct Ov007CellAnim {
    Ov007Cell **frames;
    u16 *durations;
    u32 f8;
    u32 frameCount;
} Ov007CellAnim;

/* The 0x10-byte sprite bank func_ov007_020c12ac allocates. */
typedef struct Ov007SpriteBank {
    u32 cellCount;
    u8 *cells;
    u32 animCount;
    u8 *anims;
} Ov007SpriteBank;

typedef struct Ctx {
    u8 pad[0x44];
    u32 *listA;
    u8 pad2[8];
    u32 *listB;
    u8 pad3[0x30];
} Ctx;

/* List B: a 0xc-byte group header, then `count` 0x18-byte members. Only
 * the slots this function reads are named. */
typedef struct GroupHdr {
    u8 pad_00[8];
    u8 count; /* 0x08: members that follow; func_ov007_020c13a4 sizes the group */
    u8 pad_09[3];
} GroupHdr;

typedef struct GroupMember {
    u16 entry; /* 0x00: index into the bank's cells */
    u16 value; /* 0x02: the frame's duration */
    u8 pad_04[0x14];
} GroupMember;

typedef char GroupHdr_size_must_be_0xc[sizeof(GroupHdr) == 0xc ? 1 : -1];
typedef char GroupMember_size_must_be_0x18[sizeof(GroupMember) == 0x18 ? 1 : -1];
typedef char RecA_size_must_be_0x14[sizeof(RecA) == 0x14 ? 1 : -1];

typedef struct Packed {
    u32 val;
    u16 ext;
} Packed;

extern void func_ov007_020c9a2c(Ctx *ctx, int a);
extern Ov007SpriteBank *func_ov007_020c12ac(u32 a, u32 b);
extern void *func_ov007_020c3df4(int a, u32 b);
extern void func_ov007_020c13a4(void *c, int r1, short r2, short r3);

Ov007SpriteBank *func_ov007_020c9688(int arg) {
    Ov007SpriteBank *s;
    u32 i;
    u32 nA;
    u32 nB;
    u32 cnt;
    // Every other caller of func_ov007_020c3df4 passes a literal 0; this named local is deliberate (one of the near-miss row's nine zero-plumbing shapes).
    u32 heap = 0;
    Packed tmp;
    Ctx ctx;
    u32 j;
    u8 *p;

    func_ov007_020c9a2c(&ctx, arg);
    nA = *ctx.listA;
    nB = *ctx.listB;
    s = func_ov007_020c12ac(nA, nB);

    p = (u8 *)ctx.listA + 4;
    for (i = 0; i < nA; i++) {
        Ov007Cell *e;
        u8 *base;
        cnt = *p;
        p = p + 4;
        base = s->cells;
        e = (Ov007Cell *)(base + i * 8);
        e->oam = (u16 *)func_ov007_020c3df4(heap, cnt * 6);
        e->count = cnt;
        for (j = 0; j < cnt; j++) {
            s16 h0;
            u32 key;
            u32 hi;
            u8 bE;
            u32 h10;
            u8 b9;
            u8 bA;
            u8 bB;
            u32 bF;
            RecA *r;
            s16 h2;
            u8 b5;
            r = (RecA *)p;
            key = ((u32)r->f8 << 8) | ((u32)r->f6 << 28) | ((u32)r->f7 << 29);
            hi = ((u32)r->fC << 14) | ((u32)r->fD << 30);
            p = p + sizeof(RecA);
            bF = r->fF;
            h10 = r->f10;
            b5 = r->f5;
            bB = r->fB;
            bA = r->fA;
            b9 = r->f9;
            bE = r->fE;
            h2 = r->f2;
            h0 = r->f0;
            if (key == 0x100 || key == 0x300) {
                if (b9 == 3) {
                    tmp.val = key | ((hi | ((h2 & 0xff) | (b5 << 25) | (b9 << 10) | (bA << 12))) |
                                     ((h0 & 0x1ff) << 16));
                } else {
                    tmp.val = key | ((hi | ((h2 & 0xff) | ((b5 << 25) | (bB << 13)) | (b9 << 10) |
                                            (bA << 12))) |
                                     ((h0 & 0x1ff) << 16));
                }
            } else {
                if (b9 == 3) {
                    tmp.val = key | ((hi | ((h2 & 0xff) | (b9 << 10) | (bA << 12))) |
                                     ((h0 & 0x1ff) << 16));
                } else {
                    tmp.val = key | ((hi | ((h2 & 0xff) | (bB << 13) | (b9 << 10) | (bA << 12))) |
                                     ((h0 & 0x1ff) << 16));
                }
            }
            tmp.ext = h10 | (bE << 10) | (bF << 12);
            *(u16 *)((u8 *)e->oam + j * 6) = ((u16 *)&tmp)[0];
            *(u16 *)((u8 *)e->oam + j * 6 + 2) = ((u16 *)&tmp)[1];
            *(u16 *)((u8 *)e->oam + j * 6 + 4) = ((u16 *)&tmp)[2];
        }
    }

    {
        u32 k;
        Ov007CellAnim *g;
        u32 m;
        u32 c2;
        p = (u8 *)ctx.listB + 4;
        for (k = 0; k < nB; k++) {
            c2 = ((GroupHdr *)p)->count;
            g = (Ov007CellAnim *)(s->anims + k * sizeof(Ov007CellAnim));
            p = p + sizeof(GroupHdr);
            func_ov007_020c13a4(g, c2, 0, 0);
            for (m = 0; m < c2; m++) {
                GroupMember *q0 = (GroupMember *)p;
                p = p + sizeof(GroupMember);
                g->frames[m] = (Ov007Cell *)((Ov007Cell *)s->cells + q0->entry);
                g->durations[m] = q0->value;
            }
        }
    }
    return s;
}
