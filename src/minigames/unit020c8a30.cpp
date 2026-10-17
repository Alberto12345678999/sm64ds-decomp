//cpp
/* ov006 sprite pool, 0x020c8a30..0x020c8dd4.
 *
 * Three 0x20-byte records at sPuffs. Jump, Jump2,
 * Trampoline and Trampoline2 reset the pool through 0x020c8a9c.
 * No RTTI or vtable, so the functions keep their address names.
 * The empty constructor and destructor are what the sinit at
 * 0x0212f660 passes to __cxa_vec_ctor.
 *
 * leftovers:
 * - Draw, update and clear use the existing record fields. Their public
 *   pointer signatures stay unchanged for the pool callers.
 * - ApproachLinear and ApproachLinear2 stay local externs. They
 *   take the value by reference.
 * - The pool, the counter and the sprite table are overlay data,
 *   not this TU's.
 */
#include "nitro/fx/fx.h"

#include "nitro/fx/fx.h"

typedef long long s64;

struct Ent_ov006 {
    int x;
    int y;
    int mVelX;
    int mVelY;
    int mSpread;
    int mScale;
    short mActive;
    short mIndex;
    short mAngle;
    short mTimer;
};

extern int ApproachLinear(int &, int, int);
extern int ApproachLinear2(short &, short, short);

extern "C" {
int GetGameLanguage(void);
void Hud_RenderSprite(void *a0, int a1, int a2, int a3, int a4);
typedef void (*dtor_t)(void *);
void __cxa_vec_cleanup(void *block, unsigned int n, unsigned int size, dtor_t dtor);
extern short data_02082214[];
extern void **sPuffSprites[];
extern int sPuffNextIndex;
extern void **sPuffXTable;
extern struct Ent_ov006 sPuffs[3];
extern int sPuffPoolLast[];

void Puff_Draw(char *c);
void Puff_Update(char *c);
void Puff_Clear(short *p);
void Puff_ElemDtor(void);

// @symbol Puff_Nothing
void Puff_Nothing(void) {}

// @symbol Puff_ElemDtor
void Puff_ElemDtor(void) {}

// @symbol Puff_CleanupAll
void Puff_CleanupAll(void) {
    __cxa_vec_cleanup(sPuffs, 3, 0x20, (dtor_t)Puff_ElemDtor);
}

// @symbol Puff_Spawn
void Puff_Spawn(int x, int y) {
    int i;
    int v;

    if (sPuffNextIndex >= 3) {
        return;
    }
    for (i = 0; i < 3; i++) {
        if (sPuffs[i].mActive != 0) {
            continue;
        }
        sPuffs[i].mIndex = sPuffNextIndex;
        sPuffs[i].x = x << 12;
        v = sPuffs[i].x;
        if (v < 0x20000) {
            v = 0x20000;
        } else if (v > 0xE0000) {
            v = 0xE0000;
        }
        sPuffs[i].x = v;
        sPuffs[i].y = y << 12;
        sPuffs[i].mVelX = 0;
        sPuffs[i].mVelY = -0x400;
        sPuffs[i].mActive = 1;
        sPuffs[i].mAngle = 0;
        sPuffs[i].mScale = 0x1000;
        sPuffs[i].mSpread = 0x30000;
        sPuffs[i].mTimer = 90;
        sPuffNextIndex++;
        return;
    }
}

// @symbol Puff_Clear
void Puff_Clear(short *p) {
    ((Ent_ov006 *)p)->mActive = 0;
}

// @symbol Puff_Update
void Puff_Update(char *c) {
    Ent_ov006 *entry = (Ent_ov006 *)c;
    if (entry->mActive == 0)
        return;
    entry->mAngle += 0x200;
    entry->mSpread = FX_MUL(entry->mSpread, entry->mScale);
    entry->mVelY -= 0x40;
    ApproachLinear(entry->mScale, 0x800, 0x10);
    if (ApproachLinear2(entry->mTimer, 0, 1) != 0) {
        if (entry->mIndex != 2)
            entry->mActive = 0;
    } else {
        entry->x += entry->mVelX;
        entry->y += entry->mVelY;
    }
}

// @symbol Puff_Draw
void Puff_Draw(char *c) {
    Ent_ov006 *entry = (Ent_ov006 *)c;
    void *sprite;
    int sine;
    int offsetX;
    int drawX;
    if (entry->mActive == 0)
        return;
    if (sPuffXTable != 0) {
        sprite = sPuffXTable[entry->mIndex];
    } else {
        int language = GetGameLanguage();
        sprite = sPuffSprites[language][entry->mIndex];
    }
    sine = data_02082214[((unsigned short)entry->mAngle >> 4) * 2];
    offsetX = FX_MUL(entry->mSpread, sine);
    drawX = entry->x + offsetX;
    Hud_RenderSprite(sprite, drawX >> 12, entry->y >> 12, -1, -1);
}

// @symbol Puff_ClearAll
void Puff_ClearAll(int a0, int a1) {
    int i;
    short *p = (short *)sPuffs;
    for (i = 0; i < 3; i++) {
        Puff_Clear(p);
        p = (short *)((char *)p + 0x20);
    }
    sPuffNextIndex = a0;
    sPuffXTable = (void **)a1;
}

// @symbol Puff_UpdateAll
void Puff_UpdateAll(void) {
    int i = 0;
    char *p = (char *)sPuffs;
    for (;;) {
        Puff_Update(p);
        i++;
        p += 0x20;
        if (i >= 3)
            break;
    }
}

// @symbol Puff_DrawAll
void Puff_DrawAll(void) {
    int i;
    char *p = (char *)sPuffPoolLast;
    for (i = 2; i >= 0; i--) {
        Puff_Draw(p);
        p -= 0x20;
    }
}
}
