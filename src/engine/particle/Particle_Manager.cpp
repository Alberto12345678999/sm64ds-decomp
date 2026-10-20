//cpp
/* engine/particle/Particle_Manager.cpp -- Particle::Manager, arm9
 * 0x02049d60..0x0204a5bc.
 *
 * Contiguous manager run, one function per legacy file until this fold.
 * Above it, func_02049cd8 (0x02049cd8..0x02049d60) is the sound-context
 * switch Sound.cpp calls, not a Manager method. Below it, func_0204a5bc
 * (0x0204a5bc) is a tail veneer into func_0204c584, and the system update
 * and draw helpers continue from there. func_0204d958 / func_0204d9a0 /
 * func_0204ae2c, the list and init callees AddSystem names, sit later
 * (0x0204ae2c, 0x0204d958, 0x0204d9a0) and are not part of this span.
 * Particle_Behavior.cpp owns 0x0204d4d0..0x0204d8e8, so this run cannot
 * move into Particle.cpp (0x020226d4..0x020233d4) either.
 *
 * mwccarm emits .text in reverse source order, so the definitions below
 * run ROM-descending.
 *
 *   func_0204a4c8  construct the 0x3c manager and its free lists
 *   func_0204a17c  parse the resource into mDefinitions
 *   func_0204a0dc  upload textures
 *   func_0204a028  upload palettes
 *   func_02049f58  retire expired systems (SysTracker::Update)
 *   func_02049ee8  draw active systems (RenderAll)
 *   AddSystem      spawn one system
 *   func_02049d78  return one system's particles and the system itself
 *   func_02049d60  hand a system the free-particle list
 */
#include "types.h"
#include "Particle__Manager.h"
#include "Particle__System.h"

extern "C" {
/* local extern: decl_common.h already declares func_0204d958, func_0204d9a0
 * and func_0204ae2c. Those spellings are not included here: decl_common.h is
 * a C catch-all, and AddSystem's typed callees are the spellings these bodies
 * matched. */
Particle::System *func_0204d958(void *list);
void func_0204d9a0(void *list, void *node);
int func_0204d8e8(void *list, void *node);
void func_0204ae2c(Particle::System *system, Particle::SystemDefinition *definition,
                   Vector3 *position);
void func_0204a5bc(void *self, void *list);
void func_0204a5c8(void *o);
void func_0204a730(void *manager, void *system);
}

/* File-local, same as Model4.cpp. Static members mangle as the GX loaders
   and are declarations only. */
struct GX {
    static void BeginLoadTexPltt(); /* _ZN2GX16BeginLoadTexPlttEv */
    static void LoadTexPltt(const void *src, u32 addr, u32 size);
    static void EndLoadTexPltt();
    static void BeginLoadTex(); /* _ZN2GX12BeginLoadTexEv */
    static void LoadTex(const void *src, u32 offset, u32 size);
    static void EndLoadTex();
};

struct Vector3;

namespace Particle {
struct EffectData;
struct Acceleration {
    static void Func(EffectData &, char *, Vector3 &);
};
struct Jitter {
    static void Func(EffectData &, char *, Vector3 &);
};
struct Converge {
    static void Func(EffectData &, char *, Vector3 &);
};
struct Turn {
    static void Func(EffectData &, char *, Vector3 &);
};
struct LimitPlane {
    static void Func(EffectData &, char *, Vector3 &);
};
struct RadiusConverge {
    static void Func(EffectData &, char *, Vector3 &);
};
}

typedef void (*BehaviorFunc)(Particle::EffectData &, char *, Vector3 &);

struct Behavior {
    BehaviorFunc func;
    void *data;
};

struct PEntry {
    void *src;
    void *fa;
    void *fb;
    void *fc;
    void *fd;
    void *fe;
    Behavior *behaviors;
    u16 count;
};

struct SEntry {
    void *src;
    char pad4[8];
    int raw;
    u16 s10;
    u16 s12;
};

struct EData {
    void *(*alloc)(int);
    char pad4[0x18];
    PEntry *particles;
    SEntry *seconds;
    u16 numA;
    u16 numB;
};

/* Resource file header. The parsed tables start at +0x20. +0x18 is a size
   Particle.cpp reads; no shared header models the file. */
struct ResourceHeader {
    u8 pad_000[8];
    u16 numA;
    u16 numB;
};

/* Second-table record. +0x04 is the Flags2 word copied into SEntry::raw.
   +0x1c is the length added to the parse cursor. */
struct SecondRecord {
    u8 pad_000[4];
    s32 raw;
    u8 pad_008[0x14];
    s32 length;
};

struct Flags1 {
    unsigned f0_7 : 8;
    unsigned hasA : 1;
    unsigned hasB : 1;
    unsigned hasC : 1;
    unsigned hasD : 1;
    unsigned f12_15 : 4;
    unsigned hasE : 1;
    unsigned f17_23 : 7;
    unsigned hasAccel : 1;
    unsigned hasJitter : 1;
    unsigned hasConverge : 1;
    unsigned hasTurn : 1;
    unsigned hasLimitPlane : 1;
    unsigned hasRadiusConverge : 1;
    unsigned f30_31 : 2;
};

struct Flags2 {
    unsigned f0_3 : 4;
    unsigned val1 : 4;
    unsigned val2 : 4;
    unsigned rest : 20;
};

extern "C" {

// @symbol func_0204a4c8
char *func_0204a4c8(char *(*alloc)(int), int a, int b, int c, unsigned short arg5) {
    int i;
    Particle::Manager *p;
    char *q;
    char *r;
    p = (Particle::Manager *)alloc(0x3c);
    p->unk_028 = (u16)(short)a;
    p->unk_02a = (u16)(short)b;
    p->unk_02c = (u16)(short)c;
    p->unk_02e = (u16)(short)arg5;
    p->allocator = (void *)alloc;
    p->mActiveSystems.count = 0;
    p->mFreeSystems.count = 0;
    p->mFreeParticles.count = 0;
    p->mActiveSystems.head = 0;
    p->mFreeSystems.head = 0;
    p->mFreeParticles.head = 0;
    *(int *)p->pad_030 = 0;
    q = alloc(a * 0x78);
    for (i = 0; i < a; i++) {
        func_0204d9a0(&p->mFreeSystems, q);
        q += 0x78;
    }
    r = alloc(b * 0x44);
    for (i = 0; i < b; i++) {
        func_0204d9a0(&p->mFreeParticles, r);
        r += 0x44;
    }
    p->mDefinitions = 0;
    p->unk_020 = 0;
    p->unk_026 = 0;
    p->unk_024 = p->unk_026;
    return (char *)p;
}

// @symbol func_0204a17c
void func_0204a17c(EData *t, char *d) {
    int off = 0x20;
    int i;

    t->numA = ((ResourceHeader *)d)->numA;
    t->numB = ((ResourceHeader *)d)->numB;
    t->particles = (PEntry *)t->alloc(t->numA << 5);

    for (i = 0; i < t->numA; i++) {
        PEntry *p = (PEntry *)((char *)t->particles + i * 0x20);
        p->src = d + off;
        off += 0x38;
        Flags1 flags = *(Flags1 *)p->src;

        if (flags.hasA) {
            p->fa = d + off;
            off += 0xc;
        } else
            p->fa = 0;

        if (flags.hasB) {
            p->fb = d + off;
            off += 0xc;
        } else
            p->fb = 0;

        if (flags.hasC) {
            p->fc = d + off;
            off += 8;
        } else
            p->fc = 0;

        if (flags.hasD) {
            p->fd = d + off;
            off += 0xc;
        } else
            p->fd = 0;

        if (flags.hasE) {
            p->fe = d + off;
            off += 0x14;
        } else
            p->fe = 0;

        p->count = flags.hasAccel + flags.hasJitter + flags.hasConverge + flags.hasTurn +
                   flags.hasLimitPlane + flags.hasRadiusConverge;

        if (p->count != 0) {
            p->behaviors = (Behavior *)t->alloc(p->count * 8);
            Behavior *b = p->behaviors;

            if (flags.hasAccel) {
                b->data = d + off;
                b->func = &Particle::Acceleration::Func;
                off += 8;
                b++;
            }
            if (flags.hasJitter) {
                b->data = d + off;
                b->func = &Particle::Jitter::Func;
                off += 8;
                b++;
            }
            if (flags.hasConverge) {
                b->data = d + off;
                b->func = &Particle::Converge::Func;
                off += 0x10;
                b++;
            }
            if (flags.hasTurn) {
                b->data = d + off;
                b->func = &Particle::Turn::Func;
                off += 4;
                b++;
            }
            if (flags.hasLimitPlane) {
                b->data = d + off;
                b->func = &Particle::LimitPlane::Func;
                off += 8;
                b++;
            }
            if (flags.hasRadiusConverge) {
                b->data = d + off;
                b->func = &Particle::RadiusConverge::Func;
                off += 0x10;
                b++;
            }
        } else {
            p->behaviors = 0;
        }
    }

    t->seconds = (SEntry *)t->alloc(t->numB * 0x14);

    for (i = 0; i < t->numB; i++) {
        SEntry *s = &t->seconds[i];
        char *rec = d + off;
        s->src = rec;
        /* The two bitfield reads cast inline on each use. Holding a Flags2*
           local for rec+4 makes mwcc CSE that address into r6 and read the
           raw word through it (add r6,r1,#4 / ldr r5,[r6]); the cartridge
           re-issues ldr r5,[r1,#4] each time. */
        s->s10 = 1 << (((Flags2 *)(rec + 4))->val1 + 3);
        s->s12 = 1 << (((Flags2 *)(rec + 4))->val2 + 3);
        s->raw = *(int *)(rec + 4);
        off += ((SecondRecord *)rec)->length;
    }
}

typedef struct TexData {
    int f0;
    u32 f4lo : 4;
    u32 f4hi : 28;
    int f8;
} TexData;

typedef struct Elem {
    TexData *tex;
    u32 result;
    char pad[0x14 - 8];
} Elem;

typedef struct TexHolder {
    char pad20[0x20];
    Elem *list;
    char pad24[0x26 - 0x24];
    u16 count;
} TexHolder;

// @symbol func_0204a0dc
int func_0204a0dc(TexHolder *thiz, u32 (*cb)(const void *, u32)) {
    int i;
    GX::BeginLoadTex();
    for (i = 0; i < thiz->count; i++) {
        Elem *e = (Elem *)((char *)thiz->list + i * 0x14);
        TexData *t = e->tex;
        u32 flag = (t->f4lo == 5) ? 1 : 0;
        u32 r = cb((const void *)t->f8, flag);
        GX::LoadTex((const void *)((char *)e->tex + 0x20), r, (u32)t->f8);
        e->result = r;
    }
    GX::EndLoadTex();
    return 1;
}

typedef struct {
    int field_0; /* 0x0  pointer to Tex */
    int field_4;
    int field_8;
    int field_c;
    int field_10;
} TexEntry;

typedef struct {
    int field_0;
    int field_4; /* low 4 bits select */
    int field_8;
    int field_c;
    int field_10;
} Tex;

typedef struct {
    char pad[0x20];
    TexEntry *list; /* field_20 */
    char pad2[2];
    unsigned short count; /* field_26 */
} Holder;

// @symbol func_0204a028
int func_0204a028(Holder *thiz, unsigned int (*cb)(unsigned int, unsigned int)) {
    int i;

    GX::BeginLoadTexPltt();

    for (i = 0; i < thiz->count; i++) {
        TexEntry *entry = (TexEntry *)((char *)thiz->list + i * 0x14);
        Tex *p = (Tex *)entry->field_0;
        unsigned int r6 = 0;

        if (p->field_10 != 0) {
            unsigned int arg = ((unsigned)(p->field_4 << 0x1c) >> 0x1c) == 2 ? 1 : 0;
            r6 = cb(p->field_10, arg);
            GX::LoadTexPltt((void *)((char *)entry->field_0 + p->field_c), r6, p->field_10);
        }
        entry->field_8 = r6;
    }

    GX::EndLoadTexPltt();
    return 1;
}

/* func_02049f58 at 0x02049f58
 *
 * Matched byte-for-byte with mwccarm 1.2/sp2p3 (arm9 main).
 */

typedef struct UpdSub {
    u32 b_lo : 14;
    u32 b14 : 1; /* bit 14 */
    u32 b_hi : 17;
    char pad0[0x24];
    u16 f28; /* 0x28 */
} UpdSub;

typedef struct UpdNode {
    struct UpdNode *next; /* 0x0 */
    char pad0[0x8];
    int fc; /* 0xc */
    char pad1[0x4];
    int f14;      /* 0x14 */
    UpdSub **f18; /* 0x18 */
    u32 b0 : 1;   /* 0x1c bit 0 */
    u32 b1 : 1;
    u32 b2 : 1; /* bit 2 */
    u32 b_rest : 29;
    char pad2[0x18];
    u16 f38; /* 0x38 */
} UpdNode;

typedef struct UpdObj {
    int f0;
    UpdNode *f4; /* 0x4 */
    char pad0[0x4];
    int fc; /* 0xc */
} UpdObj;

// @symbol func_02049f58
void func_02049f58(UpdObj *o) {
    UpdNode *n = o->f4;
    UpdNode *next;
    if (n == 0)
        return;
    do {
        UpdSub *s = *n->f18;
        next = n->next;
        if (n->b2 == 0) {
            func_0204a730(o, n);
        }
        if ((s->b14 != 0 && s->f28 != 0 && n->f38 > s->f28) || n->b0 != 0) {
            if (n->fc == 0 && n->f14 == 0) {
                int r = func_0204d8e8(&o->f4, n);
                func_0204d9a0(&o->fc, (void *)r);
            }
        }
        n = next;
    } while (next != 0);
}

typedef struct RndNode {
    struct RndNode *next; // 0
    char pad[0x18];
    u32 f1c; // 0x1c
} RndNode;

typedef struct RndObj {
    int f0;
    RndNode *f4; // 0x4
    char pad[0x2c];
    RndNode *f34; // 0x34
    int f38;      // 0x38
} RndObj;

// @symbol func_02049ee8
void func_02049ee8(RndObj *o, int v) {
    RndNode *n;
    u16 m = *(volatile u16 *)0x4000060;
    *(volatile u16 *)0x4000060 = (m & ~0x3000) | 8;
    o->f38 = v;
    n = o->f4;
    if (n == 0)
        return;
    do {
        o->f34 = n;
        if (((n->f1c << 0x1c) >> 0x1f) == 0) {
            func_0204a5c8(o);
        }
        n = n->next;
    } while (n != 0);
}
}

/* Particle::Manager::AddSystem -- spawn a System, arm9
 * 0x02049e0c..0x02049ee8. func_0204d958 pops one off mFreeSystems,
 * func_0204ae2c initializes it from the indexed SystemDefinition, the
 * manager's two flag words seed the system's flags, func_0204d9a0 pushes
 * it onto mActiveSystems, and a definition whose flags carry the
 * self-destruct bit fails the spawn.
 *
 * leftovers: `(flags << 17) >> 31` stays the arithmetic-shift bit-14 test
 * -- `& 0x4000` emits a different sequence. flags.unk_000/unk_006/unk_00c
 * and manager unk_02c/unk_02e keep their placeholder names: the manager
 * ctor (func_0204a4c8) stores its third and fourth arguments there for
 * AddSystem to loan into each new system's flags, but no consumer names
 * what they index.
 */
namespace Particle {

// @symbol _ZN8Particle7Manager9AddSystemEiR7Vector3
System *Manager::AddSystem(int definitionID, Vector3 &position) {
    System *result;
    System *system;

    result = 0;
    if (mFreeSystems.head != 0) {
        system = func_0204d958(&mFreeSystems);
        result = system;
        func_0204ae2c(system, &mDefinitions[definitionID], &position);

        system->flags.unk_000 = unk_02c;
        system->flags.unk_006 = unk_02e;
        system->flags.unk_00c = system->flags.unk_000;
        system->flags.unused = 0;

        func_0204d9a0(&mActiveSystems, system);
        if ((system->mDefinition->data->flags << 17) >> 31)
            result = 0;
    }

    return result;
}

}

extern "C" {

// @symbol func_02049d78
void func_02049d78(void *a, void *b) {
    u8 *ra = (u8 *)a;
    u8 *rb = (u8 *)b;
    int r;
    r = (int)func_0204d958(rb + 8);
    while (r != 0) {
        func_0204d9a0(ra + 0x14, (void *)r);
        r = (int)func_0204d958(rb + 8);
    }
    r = (int)func_0204d958(rb + 0x10);
    while (r != 0) {
        func_0204d9a0(ra + 0x14, (void *)r);
        r = (int)func_0204d958(rb + 0x10);
    }
    func_0204d8e8(ra + 4, b);
    func_0204d9a0(ra + 0xc, b);
}

// @symbol func_02049d60
void func_02049d60(void *manager, void *system) {
    func_0204a5bc(system, &((Particle::Manager *)manager)->mFreeParticles);
}
}
