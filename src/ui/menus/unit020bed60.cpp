//cpp
/* unit020bed60 -- ov007 unit 0x020bed60..0x020bf690: 7 functions, .text only.
 *
 * The title menu's rippling mesh backdrop. ov007 is the title and
 * file-select menu program that dScDSMT_c hosts; outside dScDSMT_c it has no
 * ROM RTTI or vtable, so no class name is claimed and the file keeps the
 * unit<addr> name.
 *
 * What the code does. The module owns one 0x30-byte record,
 * data_ov007_02104bd4 (Ov007MeshScene): a grid mesh (func_ov007_020cbbb0),
 * two materials it is drawn with, a wave that ripples it, and eight swings,
 * one per menu item, that tie item sprites to the mesh.
 * func_ov007_020bf428 builds it and func_ov007_020bf304 tears it down;
 * func_ov007_020beeb0 runs each frame: it pokes the mesh under the stylus
 * or the cursor's item (func_ov007_020bed60, through func_ov007_020bf630's
 * pick), ripples it, lets each item's swing move its sprite, and blends the
 * second material and the first light by the menu state.
 * func_ov007_020bf57c binds a swing to its item's sprite and
 * func_ov007_020bee14 draws the mesh with both materials.
 *
 * Edges: the bss word 0x02104bd4 is referenced by these functions and
 * nothing else in the overlay; func_ov007_020bf630 references no data and
 * is called only by func_ov007_020bed60. The previous function,
 * func_ov007_020beb80, references no ov007 data and is called only from
 * func_ov007_020be9ac; the next one, func_ov007_020bf690, starts the
 * screen-fade module (unit020bf690, bss 0x02104bd8).
 *
 * Emission order: mwccarm 2004/b56 emits one .text section per function in
 * the reverse of source order, so the highest-address function is written
 * first here and the functions come out in ROM order.
 *
 * The functions keep their ROM names under C linkage.
 */
#include "common.h"
#include "cstd.h"
#include "nitro/fx/fx.h"
#include "types.h"
#include "Ov007MenuState.h"
#include "Ov007Sprite.h"
#include "Ov007Touch.h"
#include "Ov007Work.h"
#include "Ov007Swing.h"
#include "Ov007Camera.h"
#include "Ov007Item.h"
#include "Ov007Light.h"

extern "C" {

/* data_ov007_02104bd4: the 0x30-byte record func_ov007_020bf428 allocates
 * and fills; medium-confidence name. The slot names follow their builders. */
typedef struct Ov007MeshScene {
    Ov007Mesh *mesh;                 /* 0x00: func_ov007_020cbbb0 */
    Ov007MeshMaterial *materials[2]; /* 0x04: func_ov007_020bee14 draws the mesh with each */
    Ov007MeshWave *wave;             /* 0x0c: func_ov007_020ca2a8 */
    Ov007Swing *swings[8];           /* 0x10: func_ov007_020ca010, one per item */
} Ov007MeshScene;

typedef char Ov007MeshScene_size_must_be_0x30[sizeof(Ov007MeshScene) == 0x30 ? 1 : -1];

/* Vector3's layout as a POD: a Vector3 local would make this object emit
 * Vector3's empty out-of-line destructor. */
typedef struct Ov007Point {
    Fix12i x, y, z;
} Ov007Point;

extern Ov007MeshScene *data_ov007_02104bd4;
extern struct Vector3 data_ov007_020d7d60;
extern Ov007MeshParams data_ov007_020d7cb0;
extern u8 data_ov007_020d7c98[];
extern Ov007MeshWaveParams data_ov007_020d7c9c;
extern Ov007SwingParams data_ov007_020d7cc8;
extern Ov007MeshMaterial data_ov007_020d7cf8[2];

extern int func_020531a4(int a);
extern char *func_ov007_020b2cdc(void);
extern int func_ov007_020b42d8(int index);
extern void func_ov007_020bce70(int n, int m);
extern void func_ov007_020bfe4c(Ov007Camera *camera, int x, int y, int z, void *out);
extern int func_ov007_020c1da0(int i);
extern int func_ov007_020c30ac(Vector3 *arr, int count, void *target, int arg4, int *out);
extern unsigned short func_ov007_020c3be0(int t, int a, int b);
extern void func_ov007_020c3d1c(void *self);
extern void *func_ov007_020c3df4(const char *name, int size);
extern void func_ov007_020c9a84(Ov007Swing *swing, Vector3 *offset, u16 *rotX, u16 *rotY);
extern void func_ov007_020c9c24(Ov007Swing *swing, int shift);
extern void func_ov007_020c9d90(Ov007Swing *swing, Ov007Mesh *mesh);
extern void func_ov007_020c9f10(Ov007Swing *swing, void *pos, int w, int h);
extern void func_ov007_020c9fa0(Ov007Swing *swing);
extern Ov007Swing *func_ov007_020ca010(Ov007SwingParams *params);
extern void func_ov007_020ca1d4(Ov007MeshWave *wave, Ov007Mesh *mesh);
extern int func_ov007_020ca26c(Ov007MeshWave *wave);
extern Ov007MeshWave *func_ov007_020ca2a8(Ov007MeshWaveParams *params);
extern void func_ov007_020ca578(Ov007Mesh *mesh, int i, int j, int t);
extern void func_ov007_020ca5f0(Ov007Mesh *mesh, Ov007MeshMaterial *mat, int *pos, int scaleZ,
                                int smooth);
extern void func_ov007_020cb3dc(Ov007Mesh *mesh);
extern void func_ov007_020cba78(Ov007Mesh *mesh, int shift);
extern void func_ov007_020cbb04(Ov007Mesh *mesh);
extern Ov007Mesh *func_ov007_020cbbb0(int columns, int rows, int width, Ov007MeshParams *params);
extern Ov007MeshMaterial *func_ov007_020cbf8c(Ov007MeshMaterial *src);

/* Defined below, after their callers (ROM order). */
void func_ov007_020bed60(int arg0, int arg1, int arg2);
void func_ov007_020beeb0(void);

#define SCENE data_ov007_02104bd4

/* func_ov007_020bf57c's copy of an Ov007Sprite. Ov007Sprite holds two
 * Vector3s, so in C++ a local of it emits Vector3's out-of-line destructor
 * and `buf = *e` copies member by member; the ROM copies the 0x88 bytes as
 * one block. The copy goes through the word view; the fields read through
 * the layout view, a POD twin of the slots the function names. The sprite
 * calls take the copy's address as the Ov007Sprite it holds. */
typedef struct Ov007SpriteBits {
    s32 words[0x88 / 4];
} Ov007SpriteBits;

typedef struct Ov007SpriteView {
    char pad_00[0x10];
    s32 depth;       /* 0x10 */
    Ov007Point pos;  /* 0x14 */
    s32 worldWidth;  /* 0x20 */
    s32 worldHeight; /* 0x24 */
    char pad_28[0x60];
} Ov007SpriteView;

typedef union Ov007SpriteCopy {
    Ov007SpriteBits bits;
    Ov007SpriteView view;
} Ov007SpriteCopy;

typedef char
    Ov007SpriteCopy_size_must_match[sizeof(Ov007SpriteCopy) == sizeof(Ov007Sprite) ? 1 : -1];

// @symbol func_ov007_020bf630
/* Picks the grid point of the mesh under screen point (x, y): the point is
 * unprojected through the camera at the camera's depth, then
 * func_ov007_020c30ac finds the mesh vertex nearest it. Returns its index,
 * or -1. */
int func_ov007_020bf630(Ov007Mesh *mesh, Ov007Camera *camera, int x, int y, int arg5) {
    Ov007Point local;
    func_ov007_020bfe4c(camera, x << 0xc, y << 0xc, -camera->distance, &local);
    {
        Ov007Grid *grid = mesh->grid;
        return func_ov007_020c30ac(mesh->verts, grid->columns * grid->rows, &local, arg5, 0);
    }
}

// @symbol func_ov007_020bf57c
/* Places swing idx on item view idx + 0xe's sprite: a copy of the sprite,
 * set the camera's distance in front of it (arg0 is cameras[0] for both
 * callers), is sized and moved into the world, and the swing takes its
 * position and world size and is bound to the mesh. */
void func_ov007_020bf57c(Ov007Camera *camera, int idx) {
    Ov007Sprite *e = WORK->itemViews[idx + 0xe]->sprite;
    Ov007Swing *swing = SCENE->swings[idx];

    Ov007SpriteCopy buf;
    buf.bits = *(Ov007SpriteBits *)e;
    buf.view.depth = -camera->distance;
    func_ov007_020c43bc((Ov007Sprite *)&buf, camera);
    func_ov007_020c4388((Ov007Sprite *)&buf, camera);
    func_ov007_020c9f10(swing, &buf.view.pos, buf.view.worldWidth, buf.view.worldHeight);
    func_ov007_020c9d90(swing, SCENE->mesh);
}

// @symbol func_ov007_020bf428
/* Builds the mesh scene once: the 0xf x 0xe grid mesh, its two materials
 * (each given one of the menu's textures), the wave and the eight swings
 * (each bound to its item), then the manager's three number sprites, and
 * runs the frame 0x14 times to settle the mesh. */
void func_ov007_020bf428(void) {
    int i;
    Ov007MeshMaterial *w;
    u8 *bp;
    Ov007MeshMaterial *ret;

    if (SCENE != 0)
        return;

    SCENE = (Ov007MeshScene *)func_ov007_020c3df4(0, sizeof(Ov007MeshScene));
    SCENE->mesh = func_ov007_020cbbb0(0xf, 0xe, 0x6000, &data_ov007_020d7cb0);

    w = data_ov007_020d7cf8;
    bp = data_ov007_020d7c98;
    for (i = 0; i < 2; i++) {
        ret = func_ov007_020cbf8c(w);
        w++;
        SCENE->materials[i] = ret;
        SCENE->materials[i]->texture = (struct Ov007Texture *)WORK->textures[*bp];
        bp++;
    }

    SCENE->wave = func_ov007_020ca2a8(&data_ov007_020d7c9c);

    for (i = 0; i < 8; i++) {
        SCENE->swings[i] = func_ov007_020ca010(&data_ov007_020d7cc8);
        func_ov007_020bf57c(WORK->cameras[0], i);
    }

    for (i = 0; i <= 2; i++) {
        WORK->numberSprites[i] = (Ov007Sprite *)func_ov007_020b42d8(i);
    }

    for (i = 0; i < 0x14; i++) {
        func_ov007_020beeb0();
    }
}

// @symbol func_ov007_020bf304
/* Tears down the mesh scene: frees the mesh, the wave, both materials and
 * the eight swings, then the manager's number sprites and the scene itself. */
void func_ov007_020bf304(void) {
    int i;
    Ov007MeshScene *g;

    g = SCENE;
    if (g == 0) {
        return;
    }

    {
        Ov007Mesh *mesh = g->mesh;
        if (mesh != 0) {
            func_ov007_020cbb04(mesh);
            SCENE->mesh = 0;
        }
    }

    {
        Ov007MeshWave *wave = SCENE->wave;
        if (wave != 0) {
            func_ov007_020ca26c(wave);
            SCENE->wave = 0;
        }
    }

    for (i = 0; i < 2; i++) {
        if (SCENE->materials[i] != 0) {
            func_ov007_020c3d1c(SCENE->materials[i]);
            SCENE->materials[i] = 0;
        }
    }

    for (i = 0; i < 8; i++) {
        func_ov007_020c9fa0(SCENE->swings[i]);
    }

    for (i = 0; i <= 2; i++) {
        if (WORK->numberSprites[i] != 0) {
            func_ov007_020c44c4(WORK->numberSprites[i]);
            WORK->numberSprites[i] = 0;
        }
    }

    func_ov007_020c3d1c(SCENE);
    SCENE = 0;
}

// @symbol func_ov007_020beeb0
/* One frame of the backdrop: pokes the mesh under the stylus (harder for a
 * fast stroke) or, with no touch, under the cursor's settled item; ripples
 * and steps the mesh; lets each visible item's swing move its sprite; then
 * blends the second material towards the colours of the current main state
 * and the first light towards grey in the file-select states 0xa / 0xb. */
void func_ov007_020beeb0(void) {
    int sp0;
    int sp4;
    int sp8;
    Ov007Mesh *mesh;

    mesh = SCENE->mesh;

    if (WORK->touch->cur.touch != 0) {
        int r6;
        Ov007Touch *base;
        if (func_ov007_020c1da0(0) == 0)
            r6 = 0x1000;
        else
            r6 = 0xbb8;
        base = WORK->touch;
        if (base->heldFrames != 0) {
            int s2 = base->deltaY;
            int s1 = base->deltaX;
            int d = cstd::div(func_020531a4((s1 * s1 + s2 * s2) << 0xc), 0x1e);
            int r2 = FX_MUL(r6, d);
            if (r2 >= 0x1000)
                r2 = 0x1000;
            r6 = (int)(((s64)r2 * r2) >> 0xc);
        }
        base = WORK->touch;
        func_ov007_020bed60(base->cur.x, base->cur.y, r6);
    } else {
        /* the menu cursor's state (func_ov007_020b2cdc returns
         * Ov007Cursor::state) */
        Ov007MenuState *p = (Ov007MenuState *)func_ov007_020b2cdc();
        int a;
        if (p->stateTicks == 0) {
            a = p->currentState;
            if (a >= 0 && a < 0x18) {
                a = p->previousState;
                if (a >= 0 && a < 0x18) {
                    Ov007ItemView *q = WORK->itemViews[a];
                    Ov007Item *v = q->item;
                    func_ov007_020bed60(v->posX >> 0xc, v->posY >> 0xc, 0x7d0);
                }
            }
        }
    }

    func_ov007_020ca1d4(SCENE->wave, mesh);
    func_ov007_020cba78(mesh, 2);

    for (int i = 0; i < 8; i++) {
        Ov007Swing *swing = SCENE->swings[i];
        Ov007ItemView *r6p = WORK->itemViews[i + 0xe];
        Ov007Sprite *w;
        int t;
        if (r6p->item->state->stateWork == 2)
            func_ov007_020bf57c(WORK->cameras[0], i);
        if (r6p->item->visible != 0) {
            func_ov007_020c9c24(swing, 2);
            w = r6p->sprite;
            func_ov007_020c9a84(swing, &w->posOffset, &w->rotX, &w->rotY);
            w = r6p->sprite;
            t = w->posOffset.x;
            w->posOffset.x = FX_MUL(t, 0x64);
            w = r6p->sprite;
            t = w->posOffset.y;
            w->posOffset.y = FX_MUL(t, 0x64);
        }
    }

    int r5;
    switch (WORK->states[1]->currentState) {
    case 0:
    case 1:
    case 11:
    case 12:
        sp0 = 4;
        r5 = 0x1e;
        sp4 = 0x7fff;
        sp8 = 0x4800;
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        sp0 = 5;
        r5 = 0x3c;
        sp4 = 0x575c;
        sp8 = 0x178;
        break;
    case 7:
    case 8:
        sp0 = 6;
        r5 = 0x3c;
        sp4 = 0x631a;
        sp8 = 0x7fbf;
        break;
    case 9:
    case 10:
        r5 = 0x3c;
        sp4 = 0x7fff;
        sp8 = 0x49e0;
        sp0 = 7;
        break;
    default:
        break;
    }

    func_ov007_020bce70(sp0, r5);

    {
        Ov007MeshMaterial *o8 = SCENE->materials[1];
        int n = WORK->paletteState->stateTicks;
        u16 *p7 = &o8->diffuse;
        u16 *p6 = &o8->ambient;
        int ratio;
        if (n <= 0)
            ratio = 0;
        else if (n >= r5)
            ratio = 0x1000;
        else
            ratio = cstd::div(n << 0xc, r5);
        *p7 = func_ov007_020c3be0(ratio, *p7, sp4);
        *p6 = func_ov007_020c3be0(ratio, *p6, sp8);
    }

    {
        int r0;
        Ov007MenuState *t2 = WORK->states[2];
        int r4v = 0x7fff;
        r0 = 0x1000;
        int s = t2->currentState;
        if (s == 0xb) {
            int n = t2->stateTicks;
            r4v = 0x3def;
            if (n <= 0)
                r0 = 0;
            else if (n < 0x1e)
                r0 = cstd::div(n << 0xc, 0x1e);
        } else if (s == 0xa) {
            int n = t2->stateTicks;
            if (n <= 0)
                r0 = 0;
            else if (n < 0x1e)
                r0 = cstd::div(n << 0xc, 0x1e);
        }
        WORK->lights[0]->color = func_ov007_020c3be0(r0, WORK->lights[0]->color, r4v);
    }
}

// @symbol func_ov007_020bee14
/* Draws the mesh twice, once with each material, 0x200 and 0x400 in front
 * of the template point data_ov007_020d7d60. */
void func_ov007_020bee14(void) {
    Ov007Point v = *(Ov007Point *)&data_ov007_020d7d60;
    v.z += 0x200;
    func_ov007_020ca5f0(SCENE->mesh, SCENE->materials[0], (int *)&v, 0x3e8, 1);
    func_ov007_020cb3dc(SCENE->mesh);
    v.z += 0x200;
    func_ov007_020ca5f0(SCENE->mesh, SCENE->materials[1], (int *)&v, 0x3e8, 1);
}

// @symbol func_ov007_020bed60
/* Pokes the mesh at screen point (arg0, arg1): func_ov007_020bf630 picks the
 * grid point under it through the camera, func_ov007_020ca578 pushes that
 * point with strength arg2, and the waves hold off for 0x78 ticks. */
void func_ov007_020bed60(int arg0, int arg1, int arg2) {
    Ov007Mesh *mesh = SCENE->mesh;
    Ov007Camera *camera = WORK->cameras[0];
    int res = func_ov007_020bf630(mesh, camera, arg0, arg1, -1);
    if (res == -1)
        return;
    {
        int m = cstd::mod(res, mesh->grid->columns);
        int d = cstd::div(res, mesh->grid->columns);
        func_ov007_020ca578(mesh, m, d, arg2);
    }
    SCENE->wave->delay = 0x78;
}
}
