//cpp
/* daPicGate_c, the picture gate. ov080 0x021264ec..0x02126f8c, ten functions.
 *
 * _ZTS11daPicGate_c is at 0x02128280 and _ZTV11daPicGate_c at 0x021282b4.
 * The class was previously the coined name Painting.
 *
 * Five func_ov080_* helpers, then CleanupResources, OnPendingDestroy,
 * Render, Behavior and InitResources. D1 at 0x02125404 and D0 at 0x02125428
 * stay shards: other functions sit between them and this run.
 * daPicGate_c_classInit at 0x02126f8c stays out.
 *
 * #pragma defer_codegen off emits .text in source order, so this file is
 * ROM-ascending. The destructor is not defined here.
 */

#pragma defer_codegen off

#include "daPicGate_c.h"
#include "decl_common.h"

extern "C" {
extern int IsStarCollectedInLevel(signed char levelID, int starID);
extern void func_ov080_021256f8(void *c);
extern int func_ov080_02125bb0(void *c, int x);
extern void func_ov080_02125940(void *c);
extern void func_ov080_02125af0(void *c);
extern int data_0209caa0[];
extern void func_ov080_02126124(void *c);
extern void func_ov080_02125de0(void *c, int a, int b, int d);
extern void func_ov080_02125fd0(char *c);
extern void MulMat4x3Mat4x3(const int *a, const int *b, int *out);
extern void func_ov080_02125460(char *c);
extern Matrix4x3 data_0209b3ec;
extern unsigned short DecIfAbove0_Short(unsigned short *p);
extern void func_0203cbc0(void *a);
/* local extern: dActor_c.h declares no SetRanges, and the real member takes
   four Fix12<int> by value, which these int expressions cannot be passed as
   without an aggregate temporary per argument. */
extern void _ZN8dActor_c9SetRangesE5Fix12IiES1_S1_S1_(void *self, int a, int b, int c, int d);
}
namespace Memory { void *operator_new2(unsigned int size); }
extern daPicGate_c::State data_ov080_02128628[];
int ApproachLinear(int &ref, int target, int step);

// @symbol func_ov080_021264ec
extern "C" {
void func_ov080_021264ec(daPicGate_c *self)
{
    if ((unsigned char)((self->param1 >> 8) & 0x1f) == 7 &&
        !(data_0209caa0[2] & 0x40000) &&
        IsStarCollectedInLevel(0x12, 1)) {
        if (ApproachLinear(self->mPosX, self->mClosedPosX + 0x802000, 0x13e72))
            data_0209caa0[2] |= 0x40000;
        func_ov080_0212555c(self);
    }
    func_ov080_021256f8(self);
    int i;
    for (i = 0; i < self->mNumCells; i++) {
        daPicGate_c::Vertex *v = &self->mCells[i];
        v->z = func_ov080_02125bb0(self, v->dist);
    }
    func_ov080_02125940(self);
    func_ov080_02125af0(self);
    self->mWavePhase = self->mWavePhase + self->mWaveParams->phaseStep;
}
}

// @symbol func_ov080_021265ec
extern "C" {
void func_ov080_021265ec(daPicGate_c *self)
{
    int x = 0, y = 0, row = 0, z = 0;
    int n = self->mRows;
    if (n > 0) {
        int color = 0x1ff00000;
        do {
            int col = 0;
            int m = self->mCols;
            if (m > 0) {
                do {
                    daPicGate_c::Vertex *v = &self->mCells[row * self->mRows + col];
                    int cols;
                    v->x = x; v->y = y; v->z = z; v->color = color;
                    cols = self->mCols;
                    if (col == cols - 2) x = ((u8)(self->param1 & 0xf) + 1) * 0x64000;
                    else x += ((u8)(self->param1 & 0xf) + 1) * 0x64000 / (cols - 1);
                    col++;
                } while (col < self->mCols);
            }
            {
                int rows = self->mRows;
                x = 0;
                if (row == rows - 2) y = ((u8)((self->param1 >> 4) & 0xf) + 1) * 0x64000;
                else y += ((u8)((self->param1 >> 4) & 0xf) + 1) * 0x64000 / (rows - 1);
                row++;
                if (row >= rows) break;
            }
        } while (1);
    }
    func_ov080_02126124(self);
    {
        int width = ((u8)(self->param1 & 0xf) + 1) * 0x64000;
        int height = ((u8)((self->param1 >> 4) & 0xf) + 1) * 0x64000;
        func_ov080_02125de0(self, width / 2, height / 2, 0);
    }
}
}

// @symbol func_ov080_0212677c
extern "C" {
void func_ov080_0212677c(daPicGate_c *self)
{
    int tmp[12];
    int i, j, n;
    int z = 0;

    if (self->mWaveTimer == 0) {
        func_ov080_02125fd0((char *)self);
        return;
    }

    *(int *)0x4000444 = z;
    MulMat4x3Mat4x3(self->mMtx, (const int *)&data_0209b3ec, tmp);
    *(int *)0x4000440 = 2;
    func_020553a4(tmp);
    *(int *)0x4000440 = 1;
    func_020553a4(tmp);

    *(int *)0x40004c8 = 0xe0000000;
    *(int *)0x40004cc = 0xc0007fff;
    func_ov080_02125460((char *)self);

    *(int *)0x400046c = 0x20000;
    *(int *)0x400046c = 0x20000;
    *(int *)0x400046c = 0x20000;

    n = (int)self->mCols;
    i = z; /* mov before sub: use z then sub n */
    n = n - 1;
    if (n > 0) {
        do {
            *(int *)0x4000500 = 2;
            j = z;
            if ((int)self->mRows > 0) {
                do {
                    daPicGate_c::Vertex *base = self->mCells;
                    int rows = (int)self->mRows;
                    daPicGate_c::Vertex *v1 = &base[i + j * rows];
                    daPicGate_c::Vertex *v2 = &base[(i + 1) + j * rows];
                    int vx, vy, vz;
                    s16 s0, s1, s2;

                    *(int *)0x4000488 = v1->texCoord;
                    *(int *)0x4000484 = v1->color;
                    vx = v1->x;
                    vy = v1->y;
                    vz = v1->z;
                    s0 = (s16)(vx >> 8);
                    s1 = (s16)(vy >> 8);
                    s2 = (s16)(vz >> 8);
                    *(int *)0x400048c = (u16)s0 | ((u16)s1 << 16);
                    *(int *)0x400048c = (u16)s2;

                    *(int *)0x4000488 = v2->texCoord;
                    *(int *)0x4000484 = v2->color;
                    vx = v2->x;
                    vy = v2->y;
                    vz = v2->z;
                    s0 = (s16)(vx >> 8);
                    s1 = (s16)(vy >> 8);
                    s2 = (s16)(vz >> 8);
                    *(int *)0x400048c = (u16)s0 | ((u16)s1 << 16);
                    *(int *)0x400048c = (u16)s2;

                    j++;
                } while (j < (int)self->mRows);
            }
            *(int *)0x4000504 = z;
            i++;
        } while (i < (int)self->mCols - 1);
    }
    *(int *)0x4000448 = 1;
}
}

// @symbol func_ov080_021269b8
extern "C" {
void func_ov080_021269b8(daPicGate_c *self)
{
    int i;
    daPicGate_c::Vertex *v;

    func_ov080_021256f8(self);
    if (DecIfAbove0_Short(&self->mWaveTimer) == 0) return;

    for (i = 0; i < self->mNumCells; i++) {
        v = &self->mCells[i];
        v->z = func_ov080_02125bb0(self, v->dist);
    }

    func_ov080_02125940(self);
    func_ov080_02125af0(self);

    self->mWavePhase = self->mWavePhase + self->mWaveParams->phaseStep;
}
}

// @symbol func_ov080_02126a54
extern "C" {
void func_ov080_02126a54(daPicGate_c *self)
{
    int x;
    int y;
    int row;
    int n;
    int col;
    x = 0;
    y = 0;
    row = 0;
    if ((int)self->mRows > 0) {
        do {
            col = 0;
            if ((int)self->mCols > 0) {
                do {
                    daPicGate_c::Vertex *v = &self->mCells[row * (int)self->mRows + col];
                    v->x = x;
                    v->y = y;
                    v->z = 0;
                    v->color = 0x1ff00000;
                    int du = 0x80000 / ((int)self->mCols - 1);
                    int dv = 0x80000 / ((int)self->mRows - 1);
                    int s = du * col;
                    int t = 0x80000 - dv * row;
                    v->texCoord = (u16)(s16)(s >> 8) | (((u16)(s16)(t >> 8) << 1) << 15);
                    n = (int)self->mCols;
                    if (col == n - 2)
                        x = (u8)(self->param1 & 0xf) * 0x64000 + 0x64000;
                    else
                        x += ((u8)(self->param1 & 0xf) * 0x64000 + 0x64000) / (n - 1);
                    col++;
                } while (col < n);
            }
            n = (int)self->mRows;
            x = 0;
            if (row == n - 2)
                y = (u8)((self->param1 >> 4) & 0xf) * 0x64000 + 0x64000;
            else
                y += ((u8)((self->param1 >> 4) & 0xf) * 0x64000 + 0x64000) / (n - 1);
            row++;
        } while (row < n);
    }
    func_ov080_02126124(self);
}
}

// @symbol _ZN11daPicGate_c16CleanupResourcesEv
s32 daPicGate_c::CleanupResources() {
    func_0203cbc0(mCells);
    return 1;
}

// @symbol _ZN11daPicGate_c16OnPendingDestroyEv
void daPicGate_c::OnPendingDestroy() {
}

// @symbol _ZN11daPicGate_c6RenderEv
s32 daPicGate_c::Render() {
    (this->*mState->render)();
    return 1;
}

// @symbol _ZN11daPicGate_c8BehaviorEv
s32 daPicGate_c::Behavior() {
    (this->*mState->behavior)();
    return 1;
}

// @symbol _ZN11daPicGate_c13InitResourcesEv
s32 daPicGate_c::InitResources() {
    unsigned int state = (unsigned char)((param1 >> 0xd) & 3);

    if (state >= 2) {
        mRows = 2;
        mCols = mRows;
        mNumCells = (u16)(mCols * mRows);
    } else {
        unsigned int size = (unsigned char)(param1 & 0xf) + 1;
        switch (size) {
        case 0:
        case 1:
        case 2:
            break;
        case 3:
            mRows = data_ov080_02127714[0];
            mCols = mRows;
            break;
        case 4:
            mRows = data_ov080_02127714[1];
            mCols = mRows;
            break;
        case 5:
            mRows = data_ov080_02127714[2];
            mCols = mRows;
            break;
        case 6:
            mRows = data_ov080_02127714[3];
            mCols = mRows;
            break;
        case 7:
            mRows = data_ov080_02127714[4];
            mCols = mRows;
            break;
        case 8:
            mRows = data_ov080_02127714[5];
            mCols = mRows;
            break;
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            break;
        case 16:
            mRows = data_ov080_02127714[6];
            mCols = mRows;
            break;
        }
        mNumCells = (u16)(mCols * mRows);
    }

    mCells = (Vertex *)Memory::operator_new2((unsigned)mNumCells * 0x18u);
    mTexRecord = func_ov080_02125630(this, (int)((unsigned char)((param1 >> 8) & 0x1f)));
    mWaveParams = (const WaveParams *)&data_ov080_02127834;
    mState = &data_ov080_02128628[(unsigned char)((param1 >> 0xd) & 3)];
    (this->*mState->init)();

    {
        int width = (int)((unsigned char)(param1 & 0xf) + 1) * 0x64000;
        int height = (int)((unsigned char)((param1 >> 4) & 0xf) + 1) * 0x64000;
        _ZN8dActor_c9SetRangesE5Fix12IiES1_S1_S1_(this, height / 2, width / 2 + 0xc8000, 0x1964000, 0x1964000);
    }
    if ((unsigned char)((param1 >> 8) & 0x1f) == 4) {
        if ((unsigned char)((param1 >> 0xd) & 3) == 1)
            mFlags &= ~3;
    }
    if ((unsigned char)((param1 >> 8) & 0x1f) == 7) {
        if ((unsigned char)((param1 >> 0xd) & 3) == 1) {
            mClosedPosX = mPosX;
            if (data_0209caa0[2] & 0x40000)
                mPosX += 0x802000;
        }
    }
    func_ov080_0212555c(this);
    return 1;
}
