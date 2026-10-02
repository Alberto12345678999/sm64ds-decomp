//cpp
// @symbol func_ov006_020e20bc
/* recovered: Shuffle Shell (dScMgCurling_c): a per-index update with sqrt and atan2 over the shell records. */
// NONMATCHING: div 53 of 376 words. mwccarm 2004/b56, --module ov006,
// @ 0x020e20bc size 0x5e0 (exact size, 18 words of shape difference). Residue class:
// scheduling and colouring inside the collision block. The ROM spills &mStone[idx].angle,
// &mStone[idx].speed and &mStone[i].angle to sp4, sp8 and spc and the contact RD to sp1c;
// this draft puts them at spc, sp8, sp1c and sp4. The ROM shifts the moving stone's table
// index once and adds the +1 only after the other stone's index; this draft adds it at once
// and shifts again later. The ROM starts truncating the contact angle to 16 bits among the
// table loads, and shifts the first rotation's index only after it has the second; this
// draft truncates late and shifts at once.
// Draft first banked from nearmiss/db.jsonl at 299, landed 2026-09-14 under Tango's ruling
// that functionally-equivalent drafts live on main with an honest banner so the port and
// readers have source; the near-miss database later held a 203-word C tip. Rewritten on
// 2026-10-02 as C++ on the shape of its Shell Smash twin, func_ov006_020e5450, which brought
// it to 53. The changes were: the contact block reuses dx and dy for the atan2 operands and
// dx for the moving stone's first rotated term; one k index and one rel angle are reused
// for both stones' table words and for both contact rotations; each product names the
// table value first, to match smull's operand order; the first rotated term is built as
// "dx = s*v; dx -= c*w", which gives the ROM's issue order and its exact size; the first
// wall clamp keeps the overshoot in xi; and the locals are declared in the order that puts
// rg at sp0, as the ROM does.
// Counts as decompiled, not matched. tools/enroll.py leaves it out of the ROM build, which
// keeps the original bytes for this range. A byte-exact match replaces this file and
// drops the banner.
#include "dScMgCurling_c.h"

extern "C" {
extern int _ZN4cstd4sqrtEy(u64 v);
extern short _ZN4cstd5atan2E5Fix12IiES1_(int y, int x);
extern void func_02012718(int id, int v);
extern s16 data_02082214[];
}

#define FMUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

extern "C" void func_ov006_020e20bc(dScMgCurling_c *self, int idx)
{
    int i;
    int dx;
    int dy;

    for (i = 0; i < 5; i++) {
        if (self->mStone[i].active == 0) continue;
        if (idx == i) continue;
        if (self->mStone[i].state == 0) continue;
        if (self->mStone[i].state == 3) continue;
        dx = (self->mStone[i].x - self->mStone[idx].x) >> 12;
        dy = (self->mStone[i].y - self->mStone[idx].y) >> 12;
        if (_ZN4cstd4sqrtEy((long long)(dx * dx + dy * dy)) > 0x18) continue;
        {
            int rb;
            int k;
            int sP;
            int vmy;
            int cP;
            u16 ang;
            int rf;
            int sN;
            int rg;
            u16 rel;
            int xi;
            int cN;
            int rd;
            int yi;
            int vmx;
            int rc;
            int vex;
            int re;
            int rh;
            int vey;

            dx = self->mStone[idx].x - self->mStone[i].x;
            dy = self->mStone[idx].y - self->mStone[i].y;
            ang = _ZN4cstd5atan2E5Fix12IiES1_(dy, dx);
            k = (self->mStone[idx].angle >> 4) * 2;
            vmx = FMUL(data_02082214[k + 1], self->mStone[idx].speed);
            vmy = FMUL(data_02082214[k], self->mStone[idx].speed);
            k = (self->mStone[i].angle >> 4) * 2;
            vex = FMUL(data_02082214[k + 1], self->mStone[i].speed);
            vey = FMUL(data_02082214[k], self->mStone[i].speed);
            if (vey == 0) vey = vmy >> 1;
            rel = -ang;
            k = (rel >> 4) * 2;
            cN = data_02082214[k];
            sN = data_02082214[k + 1];
            rel = -rel;
            k = (rel >> 4) * 2;
            cP = data_02082214[k];
            sP = data_02082214[k + 1];
            dx = FMUL(sN, vmx);
            dx -= FMUL(cN, vmy);
            rb = FMUL(cN, vmx) + FMUL(sN, vmy);
            rc = FMUL(sN, vex) - FMUL(cN, vey);
            rf = FMUL(cN, vex) + FMUL(sN, vey);
            rd = FMUL(sP, rc) - FMUL(cP, rb);
            re = FMUL(cP, rc) + FMUL(sP, rb);
            rg = FMUL(sP, dx) - FMUL(cP, rf);
            rh = FMUL(cP, dx) + FMUL(sP, rf);
            self->mStone[idx].angle = _ZN4cstd5atan2E5Fix12IiES1_(re, rd);
            self->mStone[idx].speed = _ZN4cstd4sqrtEy((u64)((long long)rd * rd + (long long)re * re));
            self->mStone[idx].x = self->mStone[i].x + FMUL(sP, 0x1b000);
            self->mStone[idx].y = self->mStone[i].y + FMUL(cP, 0x1b000);
            xi = self->mStone[idx].x >> 12;
            yi = self->mStone[idx].y >> 12;
            if (xi - 0xc < 0) {
                xi = self->mStone[idx].x - 0xc000;
                self->mStone[i].x += xi;
                self->mStone[idx].x = 0xc000;
            }
            if (xi + 0xc > 0x100) {
                self->mStone[i].x += self->mStone[idx].x - 0xf4000;
                self->mStone[idx].x = 0xf4000;
            }
            if (yi - 0xc < -0xe0) {
                self->mStone[i].y += self->mStone[idx].y + 0xd4000;
                self->mStone[idx].y = -0xd4000;
            }
            self->mStone[i].angle = _ZN4cstd5atan2E5Fix12IiES1_(rh, rg);
            self->mStone[i].speed = _ZN4cstd4sqrtEy((u64)((long long)rg * rg + (long long)rh * rh));
            self->mStone[idx].state = 1;
            self->mStone[i].state = 1;
            if (self->mStone[i].speed >= 0x3800) {
                self->mStone[i].fast = 1;
            } else {
                self->mStone[i].fast = 0;
            }
            func_02012718(0xe8, self->mStone[idx].x);
            return;
        }
    }
}
