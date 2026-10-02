//cpp
// @symbol func_ov006_020e20bc
/* Shuffle Shell (dScMgCurling_c): stone idx has just moved, so find the first
 * other stone it overlaps and resolve the collision. The two exchange their
 * velocity components along the line between their centres and keep the
 * components across it; the moving stone is then pushed back to one stone
 * width (0x1b000) along that line and clamped to the board, with any overshoot
 * passed on to the stone it hit. Both stones end up moving, the hit stone is
 * flagged fast above 0x3800, and the knock sound plays panned to the x.
 *
 * Matched 2026-10-02 (mwccarm 2004/b56, --module ov006, 0x020e20bc, 0x5e0).
 * The draft came from the near-miss database (299 words), was rewritten as
 * C++ on the shape of the Shell Smash twin func_ov006_020e5450 (53), and
 * closed with three more spellings: the contact angle is negated right after
 * atan2, before the velocities are read; the three fields written after a
 * call are reached through pointers taken beside each stone's reads, which is
 * what puts their addresses in the frame chain ahead of the pool; and the
 * moving stone's new x velocity reuses the outer dx, which drops it to the
 * end of the pool.
 */
#include "dScMgCurling_c.h"

extern "C" {
extern int _ZN4cstd4sqrtEy(u64 v);
extern short _ZN4cstd5atan2E5Fix12IiES1_(int y, int x);
extern void func_02012718(int id, int v);
extern s16 data_02082214[];
}

/* FX_Mul: 12-bit fixed-point product, rounded. */
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
            u16 *pAngle;
            s32 *pSpeed;
            u16 *pHitAngle;
            int mTangent;
            int k;
            int cosA;
            int vmy;
            int sinA;
            u16 contact;
            int hTangent;
            int cosN;
            int hvx;
            u16 rel;
            int xi;
            int sinN;
            int mNormal;
            int yi;
            int vmx;
            int hNormal;
            int vhx;
            int mvy;
            int hvy;
            int vhy;

            /* Contact line, from the hit stone to the moving one. */
            dx = self->mStone[idx].x - self->mStone[i].x;
            dy = self->mStone[idx].y - self->mStone[i].y;
            contact = _ZN4cstd5atan2E5Fix12IiES1_(dy, dx);
            rel = -contact;

            /* Both velocities as x/y. A hit stone at rest takes half the
             * moving stone's y so the exchange below cannot stall. */
            pAngle = &self->mStone[idx].angle;
            pSpeed = &self->mStone[idx].speed;
            k = (self->mStone[idx].angle >> 4) * 2;
            vmx = FMUL(data_02082214[k + 1], self->mStone[idx].speed);
            vmy = FMUL(data_02082214[k], self->mStone[idx].speed);
            pHitAngle = &self->mStone[i].angle;
            k = (self->mStone[i].angle >> 4) * 2;
            vhx = FMUL(data_02082214[k + 1], self->mStone[i].speed);
            vhy = FMUL(data_02082214[k], self->mStone[i].speed);
            if (vhy == 0) vhy = vmy >> 1;

            /* sin/cos of -contact rotate into the contact frame; sin/cos of
             * +contact rotate back out. */
            k = (rel >> 4) * 2;
            sinN = data_02082214[k];
            cosN = data_02082214[k + 1];
            rel = -rel;
            k = (rel >> 4) * 2;
            sinA = data_02082214[k];
            cosA = data_02082214[k + 1];

            /* Normal and tangential components of each velocity. */
            mNormal = FMUL(cosN, vmx);
            mNormal -= FMUL(sinN, vmy);
            mTangent = FMUL(sinN, vmx) + FMUL(cosN, vmy);
            hNormal = FMUL(cosN, vhx) - FMUL(sinN, vhy);
            hTangent = FMUL(sinN, vhx) + FMUL(cosN, vhy);

            /* Swap the normal components and rotate back: dx/mvy for the
             * moving stone, hvx/hvy for the one it hit. */
            dx = FMUL(cosA, hNormal) - FMUL(sinA, mTangent);
            mvy = FMUL(sinA, hNormal) + FMUL(cosA, mTangent);
            hvx = FMUL(cosA, mNormal) - FMUL(sinA, hTangent);
            hvy = FMUL(sinA, mNormal) + FMUL(cosA, hTangent);

            *pAngle = _ZN4cstd5atan2E5Fix12IiES1_(mvy, dx);
            *pSpeed = _ZN4cstd4sqrtEy((u64)((long long)dx * dx + (long long)mvy * mvy));

            /* Separate the stones along the contact line, then keep the
             * moving one on the board and hand any overshoot to the other. */
            self->mStone[idx].x = self->mStone[i].x + FMUL(cosA, 0x1b000);
            self->mStone[idx].y = self->mStone[i].y + FMUL(sinA, 0x1b000);
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

            *pHitAngle = _ZN4cstd5atan2E5Fix12IiES1_(hvy, hvx);
            self->mStone[i].speed = _ZN4cstd4sqrtEy((u64)((long long)hvx * hvx + (long long)hvy * hvy));
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
