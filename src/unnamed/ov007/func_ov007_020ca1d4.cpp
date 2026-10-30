//cpp
#include "types.h"
#include "nitro/fx/fx.h"
#include "Ov007MenuState.h"
#include "cstd.h"

extern "C" {

#pragma opt_common_subs off
#pragma opt_strength_reduction off

/* The 0x24-byte follower func_ov007_020c844c allocates; names as in
 * func_ov007_020c83fc, only the slot this file adds to. */
typedef struct Ov007Follower {
    char pad_00[0x10];
    int force[3]; /* 0x10: accumulated per frame, cleared at the end of each step */
    char pad_1c[8];
} Ov007Follower;

/* A point list as func_ov007_020c798c builds it (names as in
 * func_ov007_020c9a84). */
typedef struct Ov007PointList {
    Ov007Follower **items; /* 0x0 */
    int count;             /* 0x4 */
} Ov007PointList;

/* The 0x10-byte grid func_ov007_020c73f0 builds: rows lists of columns
 * points, and the same points again as columns lists of rows. */
typedef struct Ov007Grid {
    int columns;                  /* 0x00 */
    int rows;                     /* 0x04 */
    Ov007PointList **rowLists;    /* 0x08: one per row, columns points each */
    Ov007PointList **columnLists; /* 0x0c: one per column, rows points each */
} Ov007Grid;

/* data_ov007_02104bd4[0], the 0x38-byte grid mesh func_ov007_020cbbb0
 * builds; names as in func_ov007_020ca5f0, only the slot this file reads. */
typedef struct Ov007Mesh {
    char pad_00[4];
    Ov007Grid *grid; /* 0x04: func_ov007_020c73f0 */
} Ov007Mesh;

/* data_ov007_020d7c9c, the wave template; chances are per mille. */
typedef struct Ov007MeshWaveParams {
    int speed;      /* 0x00: phase advance per tick of the wave's state */
    int spread;     /* 0x04: phase across one whole row or column */
    int amplitude;  /* 0x08: Q12, times the sine */
    u16 minIdle;    /* 0x0c: ticks a wave stays idle (-1) before it may re-roll */
    u16 keepChance; /* 0x0e: chance each tick a running wave keeps pushing */
    u16 idleChance; /* 0x10: chance a re-roll goes idle instead of picking a line */
} Ov007MeshWaveParams;

/* The 0x1c-byte record func_ov007_020ca2a8 builds and func_ov007_020ca1d4
 * ticks: waves[0] runs down a mesh column and waves[1] along a row (2 and 3
 * are ticked but drive nothing). Each wave's currentState is its column or
 * row, -1 when idle, and its stateTicks the sine's time. */
typedef struct Ov007MeshWave {
    int frame;                   /* 0x00: func_ov007_020ca1d4 counts it up every call */
    int delay;                   /* 0x04: no wave runs until it counts down to 0 */
    Ov007MenuState *waves[4];    /* 0x08: func_ov007_020c9388(-2) */
    Ov007MeshWaveParams *params; /* 0x18: func_ov007_020ca2a8's argument */
} Ov007MeshWave;

typedef char Ov007Follower_size_must_be_0x24[sizeof(Ov007Follower) == 0x24 ? 1 : -1];

typedef char Ov007MeshWave_size_must_be_0x1c[sizeof(Ov007MeshWave) == 0x1c ? 1 : -1];

extern short data_02082214[];
extern int func_ov007_020c3ba8(int);
extern void *func_ov007_020c3df4(int a, int b);
extern void *func_ov007_020c9388(int initialState);
extern void func_ov007_020c937c(void *state);
extern int func_ov007_020c3d1c(void *);
extern void func_ov007_020c92d0(void *state);

/* Steps wave i over the mesh: while it holds a line and keepChance wins it
 * adds a travelling sine to the z force of every point on that line;
 * otherwise, once any idle time is served, it re-rolls to idle or to a
 * random line. The parameters keep their char * spelling; `wave` and `mesh`
 * are the typed views. */
void func_ov007_020ca308(char *self, char *t, int i) {
    Ov007MeshWave *wave = (Ov007MeshWave *)self;
    Ov007Mesh *mesh = (Ov007Mesh *)t;
    Ov007MenuState *state;
    Ov007MeshWaveParams *params;
    int line;
    int amplitude;
    int count;
    int speed;
    int spread;
    int lines;
    int ticks;
    int j;
    int phase;

    state = wave->waves[i];
    params = wave->params;
    speed = params->speed;
    line = state->currentState;
    spread = params->spread;
    amplitude = params->amplitude;

    if (state->stateTicks == 0)
        wave->waves[i]->stateTicks = func_ov007_020c3ba8(0x3c);
    ticks = wave->waves[i]->stateTicks;

    if (i == 0 || i == 2) {
        Ov007Grid *grid = mesh->grid;
        count = grid->rows;
        lines = grid->columns;
    } else if (i == 1 || i == 3) {
        Ov007Grid *grid = mesh->grid;
        count = grid->columns;
        lines = grid->rows;
    }

    if (line >= 0 && line < lines) {
        int keep = params->keepChance;
        if (func_ov007_020c3ba8(10000) <= keep * 10 - 1) {
            u16 base;
            u16 step = (u16)cstd::div(spread, count);
            j = 0;
            base = (u16)(ticks * speed);
            if (count <= 0)
                return;
            phase = j;
            do {
                s16 sine = data_02082214[((u16)(base + phase) >> 4) * 2];
                int val = FX_MUL(amplitude, sine);
                if (i == 0) {
                    mesh->grid->rowLists[j]->items[line]->force[2] += val;
                } else if (i == 1) {
                    mesh->grid->rowLists[line]->items[j]->force[2] += val;
                }
                j++;
                phase += step;
            } while (j < count);
            return;
        }
    }

    if (line == -1) {
        if (line != -1)
            return;
        if (ticks < params->minIdle)
            return;
    }
    {
        int idle = params->idleChance;
        if (func_ov007_020c3ba8(10000) <= idle * 10 - 1) {
            wave->waves[i]->requestedState = -1;
            return;
        }
    }
    wave->waves[i]->requestedState = func_ov007_020c3ba8(lines);
}

/* Allocates a mesh wave over the template params: four idle waves
 * (func_ov007_020c9388(-2)), no delay. */
void *func_ov007_020ca2a8(void *params) {
    Ov007MeshWave *wave = (Ov007MeshWave *)func_ov007_020c3df4(0, sizeof(Ov007MeshWave));
    int i;
    for (i = 0; i < 4; i++) {
        wave->waves[i] = (Ov007MenuState *)func_ov007_020c9388(-2);
    }
    wave->params = (Ov007MeshWaveParams *)params;
    wave->delay = 0;
    wave->frame = 0;
    return wave;
}

/* Frees a mesh wave and its four wave states. c keeps the callers' char *
 * spelling; `wave` is the typed view. */
int func_ov007_020ca26c(char *c) {
    Ov007MeshWave *wave = (Ov007MeshWave *)c;
    int i;
    for (i = 0; i < 4; i++) {
        func_ov007_020c937c(wave->waves[i]);
    }
    return func_ov007_020c3d1c(c);
}

/* One tick of a mesh wave over mesh: once the delay has run out, ticks the
 * four wave states and steps waves 0 and 1 (func_ov007_020ca308); counts
 * frame up every call. */
void func_ov007_020ca1d4(char *self, int mesh) {
    Ov007MeshWave *wave = (Ov007MeshWave *)self;
    int i;
    if (wave->delay <= 0) {
        for (i = 0; i < 4; i++) {
            func_ov007_020c92d0(wave->waves[i]);
            switch (i) {
            case 0:
            case 1:
                func_ov007_020ca308(self, (char *)mesh, i);
                break;
            case 2:
            case 3:
                break;
            }
        }
    } else {
        wave->delay--;
        if (wave->delay <= 0)
            wave->delay = 0;
    }
    wave->frame++;
}
}
