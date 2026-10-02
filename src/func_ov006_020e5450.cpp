//cpp
// @symbol func_ov006_020e5450
/* recovered: Shell Smash (dScMgCurling2_c): a per-index update with sqrt and atan2 over the shell records. */
// NONMATCHING: div 70 of 344 words. mwccarm 2004/b56, --module ov006,
// @ 0x020e5450 size 0x560 (exact size, 24 words of shape difference). Residue class:
// scheduling and colouring inside the collision block. The ROM computes &mStone[i].angle
// and loads the trig table base before the idx angle load; it loads the two table words
// for the contact angle after the other stone's table words and sign-extends them only
// after vex; it orders the 0x4668 and table literals the other way; and one idx.y reload
// colours r1 where this draft gives r0.
// Draft first banked from nearmiss/db.jsonl at 191, landed 2026-09-14 under Tango's ruling
// that functionally-equivalent drafts live on main with an honest banner so the port and
// readers have source. Improved to 70 on 2026-10-02. The changes were: the contact block reuses dx and dy for the
// moving stone's new velocity, so the slots follow the ROM frame; the c, s, k and rel
// temporaries are reused for both stones, so the schedule follows the ROM order; each
// product names the table value first, which gives smull's operand order; and the first
// wall clamp keeps the overshoot in xi, as the ROM does, so the second test reads it.
// Counts as decompiled, not matched. tools/enroll.py leaves it out of the ROM build, which
// keeps the original bytes for this range. A byte-exact match replaces this file and
// drops the banner.
// @symbol func_ov006_020e5450
#include "dScMgCurling2_c.h"

extern "C" {
extern int _ZN4cstd4sqrtEy(u64 v);
extern short _ZN4cstd5atan2E5Fix12IiES1_(int y, int x);
extern void func_02012718(void *id, int v);
extern s16 data_02082214[];
}

#define FMUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

extern "C" void func_ov006_020e5450(dScMgCurling2_c *self, int idx)
{
    int i;
    int dx;
    int dy;

    for (i = 0; i < 11; i++) {
        if (self->mStone[i].active == 0) continue;
        if (idx == i) continue;
        if (self->mStone[i].state == 0) continue;
        if (self->mStone[i].state == 3) continue;
        dy = self->mStone[i].y;
        dx = self->mStone[i].x - self->mStone[idx].x;
        dy -= self->mStone[idx].y;
        if ((_ZN4cstd4sqrtEy((u64)((long long)dx * dx + (long long)dy * dy)) >> 12) >= 0x18) continue;
        {
            int nex;
            int ney;
            u16 ang;
            u16 rel;
            int k;
            int E;
            int c;
            int s;
            int sP;
            int cP;
            int vmx;
            int vmy;
            int vex;
            int vey;
            int yi;
            int xi;

            dx = self->mStone[i].x - self->mStone[idx].x;
            dy = self->mStone[i].y - self->mStone[idx].y;
            ang = _ZN4cstd5atan2E5Fix12IiES1_(dy, dx);
            E = (ang >> 4) * 2;
            rel = self->mStone[idx].angle - ang;
            k = (rel >> 4) * 2;
            c = data_02082214[k + 1];
            s = data_02082214[k];
            vmx = FMUL(c, self->mStone[idx].speed);
            vmy = FMUL(s, self->mStone[idx].speed);
            rel = self->mStone[i].angle - ang;
            k = (rel >> 4) * 2;
            c = data_02082214[k + 1];
            s = data_02082214[k];
            sP = data_02082214[E];
            cP = data_02082214[E + 1];
            vex = FMUL(c, self->mStone[i].speed);
            vey = FMUL(s, self->mStone[i].speed);
            dy = FMUL(cP, vex) - FMUL(sP, vmy);
            dx = FMUL(sP, vex) + FMUL(cP, vmy);
            nex = FMUL(cP, vmx) - FMUL(sP, vey);
            ney = FMUL(sP, vmx) + FMUL(cP, vey);
            self->mStone[idx].angle = _ZN4cstd5atan2E5Fix12IiES1_(dx, dy);
            self->mStone[idx].speed = _ZN4cstd4sqrtEy((u64)((long long)dy * dy + (long long)dx * dx));
            self->mStone[idx].x = self->mStone[i].x - FMUL(cP, 0x1b000);
            self->mStone[idx].y = self->mStone[i].y - FMUL(sP, 0x1b000);
            yi = self->mStone[idx].y >> 12;
            xi = self->mStone[idx].x >> 12;
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
                self->mStone[idx].y = -0xd4000;
                self->mStone[i].y = self->mStone[idx].y + 0x18000;
            }
            self->mStone[i].angle = _ZN4cstd5atan2E5Fix12IiES1_(ney, nex);
            self->mStone[i].speed = _ZN4cstd4sqrtEy((u64)((long long)nex * nex + (long long)ney * ney));
            self->mStone[idx].state = 1;
            self->mStone[i].state = 1;
            if (self->mStone[i].speed >= 0x3800) {
                self->mStone[i].fast = 1;
            } else {
                self->mStone[i].fast = 0;
            }
            func_02012718((void *) 0xe8, self->mStone[idx].x);
            self->SpawnValue(idx, i);
            return;
        }
    }
}
