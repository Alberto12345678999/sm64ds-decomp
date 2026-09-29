//cpp
/* dMap_c, the touch-screen minimap actor (ov002).
 *
 * One translation unit, eleven functions, 0x020f975c..0x020fb8bc: the
 * destructor pair, the two coordinate helpers FixTHIPaintingRoomPos and
 * UpdateLevelSpecific, the four fBase_c/dBase_c virtuals the class
 * overrides, and the two minimap-space projection helpers at the tail.
 * This is dMap_c's key-function TU, so the object also carries the class's
 * vtable and its RTTI chain; the manifest licenses those against their ROM
 * homes (config/tu_manifest.d/ov002/dMap_c.json).
 */
#include "dMap_c.h"
#include "decl_common.h"
#include "types.h"

#pragma defer_codegen off
/* Codegen is deferred by default in mwccarm 2004/b56, which makes its
 * optimisation pragmas file-global, last one wins. With it off, the
 * positional brackets below bind to the members they enclose -- and .text is
 * then emitted in SOURCE order, so this file is written in ascending ROM
 * order.
 *
 * Render and InitResources were each matched under
 * #pragma opt_strength_reduction off; Behavior, between them, needs it on.
 * Only the bound form gets all eleven. A function is not generated at its
 * closing brace but at the next top-level token, so a pragma written
 * directly after Behavior would still reach it; the declarations that sit
 * between Behavior and InitResources are that token. */

namespace G2S {
    void* GetBG3CharPtr();
}

struct Event {
    static int GetBit(unsigned int bit);
};

/* The slice of Player that Render reads. */
struct Player {
    int unk0, unk4;
    int unk8;                   // 0x008
    u8 padC[0x8e - 0xc];
    s16 unk8E;                  // 0x08e
    u8 pad90[0x6c8 - 0x90];
    u16 unk6C8;                 // 0x6c8
    u8 pad6CA[0x6d9 - 0x6ca];
    u8 unk6D9;                  // 0x6d9
    int HasNoCap();
};

struct Obj {
    char pad0[0x5c];
    Vector3 pos;        /* 0x5c */
    char pad1[0xcc - 0x68];
    s8 f0cc;            /* 0xcc */
    char pad2[0x110 - 0xcd];
    void *f110;         /* 0x110 */
    char pad3[0x154 - 0x114];
    s32 f154;           /* 0x154 */
    char pad4[0x17c - 0x158];
    s16 f17c;           /* 0x17c */
};

struct Vtbl { s32 (*f[8])(void *); };

struct VtblOwner { Vtbl *vt; };

struct Vec3 { int x, y, z; };

#define F218 (*(s32 *)(((int)self + 0x218)))
#define FANG (*(s16 *)(((int)self + 0x21c)))
#define F254 (*(u8 *)(((int)self + 0x254)))
#define FMUL(a, b) ((s32)((((long long)(a) * (b)) + 0x800) >> 12))

extern "C" {
extern void Vec3_Sub(struct Vector3* out, struct Vector3* a, struct Vector3* b);
extern int _ZN4cstd4fdivEii(int a, int b);
extern signed char data_0209f2f8;
extern u8 data_0209f220;
extern u32 data_0209caa0[];
int SublevelToLevel(int i);
int IsStarCollected(int level, int star);
extern void _ZN3OAM9RenderSubEP7OamAttriiii(void *oam, int x, int y, int a, int pal);
extern void _ZN3OAM6RenderEbP7OamAttriiii5Fix12IiEi(int on, void *oam, int x, int y, int a, int pal, int scale, int ang);
extern void _ZN3OAM6RenderEbP7OamAttriiiiP9Matrix2x2(int on, void *oam, int x, int y, int a, int pal, void *mtx);
extern u8 data_0209f20c;
extern u8 data_0209f2c4;
extern u8 data_0209f294;
extern u8 data_0209f250;
extern u8 data_0209f2d4;
extern u8 data_0209f2d8;
extern Player *data_0209f394[];
extern void *_ZN3OAM18MM_VS_PLAYER_ICONSE[];
extern s16 data_02082214[];
extern char _ZN3OAM8MM_ARROWE[];
extern void *_ZN3OAM20MM_VS_PLAYER_ICONS_SE[];
extern s8 data_ov002_02111148;
extern void *_ZN3OAM15MM_PLAYER_ICONSE[];
extern u8 data_0209f37c[];
extern int data_0208ee44;
extern void *_ZN3OAM15MM_STAR_MARKERSE[];
extern u8 data_0209f288;
extern char _ZN3OAM11MM_RED_COINE[];
extern u8 data_ov002_02111154[];
extern u8 data_0209f370[];
extern void *data_ov002_0210cac8[];
extern void *data_ov002_0210c748[];
extern u8 data_0209d660;
extern u32 data_020a0db0;
extern void *_ZN3OAM12MM_STAR_KEYSE[];
extern char _ZN3OAM13MM_SPIKE_BOMBE[];
extern VtblOwner *data_0209f5bc;
extern Obj  *data_0209f318;
extern u32  data_0209b454;
extern s32  data_0209d4b0;
extern u8   data_0209f350[];
extern s8   data_02092110;
extern u8   data_0209f204;
extern u8   data_ov002_02111150;
extern u8   data_020a0e40;
extern u8   data_0209f4ac[];
extern u8   data_0209d454;
extern u8   data_0209f4a8[];
extern u8   data_0209f4a9[];
extern u8   data_0209f4ae[];
extern u8   data_ov002_0211114c;
extern u8   data_ov002_02111144;
extern Obj  *data_0209f40c[];
extern Obj  *data_0209f3e8[];
extern Obj  *data_0209f3a4[];
extern s32  _ZN6Player12Unk_020ca8f8Ev(Obj *p);
extern void SetSubBg2Offset(s32 a, s32 b);
extern void _ZN3G2x13SetBlendAlphaEPVttttj(volatile u16 *p, u16 a, u16 b, u16 c, u16 d);
extern void _ZN6dMap_c15GetPosOnMinimapER7Vector3S1_5Fix12IiEsS1_(Vector3 *a, Vector3 *b, int c, s16 d, Vector3 *e);
extern void _ZN6dMap_c20GetPosFromMinimapPosER7Vector3S1_5Fix12IiEsS1_(Vector3 *a, Vector3 *b, int c, s16 d, Vector3 *e);
extern void AddVec3(Vector3 *a, Vector3 *b, Vector3 *c);
extern s32  GetMinimapID(Obj *obj, s32 arg);
extern s32  GetMinimapScale(s32 idx);
extern void UpdateMinimap(s32 *a, s32 b, s32 c, s32 d, s32 e);
void Vec3_DivScalarInPlace(struct Vec3* v, int s);
void Vec3_MulScalarInPlace(struct Vec3* v, int s);
void Vec3_RotateYAndTranslate(struct Vec3* out, struct Vec3* in, short ang, struct Vec3* t);
extern struct Vec3 data_ov002_0211116c;
}

// @symbol _ZN6dMap_cD1Ev
/* The complete-object destructor: store this class's vptr and chain to
 * dBase_c's destructor. dMap_c adds no member with a destructor of its own,
 * so the body is empty and the compiler writes the whole thing.
 */
dMap_c::~dMap_c()
{
}
// @symbol _ZN6dMap_cD0Ev
/* The deleting destructor has no text of its own: the single ~dMap_c() above
 * emits D1, D0 and D2 together, and D0 is D1 plus the inline operator
 * delete. The cartridge keeps D1 and D0 only; the manifest deadstrips D2.
 */

// @symbol _ZN6dMap_c21FixTHIPaintingRoomPosER7Vector3
/* recovered: shared header, real C++ method (static)
 *
 * Bends a position inside the THI painting room so the minimap draws it in the
 * right place -- the room's real geometry and its map are not the same shape.
 *
 * It only fires on one specific place: level 0x1d, sublevel 5, room 2. Three
 * guards in a row, and any of them failing leaves the position untouched.
 *
 * Two zones, split at p0.z, each anchored on its own reference point and
 * scaled DIFFERENTLY per axis -- the far zone's x scale is even computed from
 * how far past the anchor the point is (`0xc00 - depth/-0x2e60`), so the
 * correction stretches with distance rather than being a fixed factor.
 *
 * No `this`: the ROM keeps r0 (the Vector3) in r4 and clobbers r1 before any
 * use, so the only incoming pointer is the argument. See include/dMap_c.h.
 */
/* recovered: named members + shared header */
void dMap_c::FixTHIPaintingRoomPos(Vector3 & v_)
{
    struct Vector3* v = &v_;
    struct Vector3 p0, p1, out, out2;

    p0.x = (int)0xfee30000;
    p0.y = 0;
    p0.z = (int)0xff564000;
    p1.x = -0x1440000;
    p1.y = 0;
    p1.z = (int)0xff741000;

    if (SublevelToLevel(data_0209f2f8) != 0x1d) return;
    if (data_0209f2f8 != 5) return;
    if (data_ov002_02111148 != 2) return;

    if (v->z <= p0.z) {
        int factor;
        Vec3_Sub(&out, v, &p0);
        factor = 0xc00 - (_ZN4cstd4fdivEii(out.z, (int)0xffffd1a0) >> 12);
        v->x = p0.x + (int)(((long long)out.x * factor + 0x800) >> 12);
        v->z = p0.z + (int)(((long long)out.z * 0x200 + 0x800) >> 12);
    } else {
        if (v->x > p1.x) return;
        Vec3_Sub(&out2, v, &p1);
        v->x = p1.x + (int)(((long long)out2.x * 0x400 + 0x800) >> 12);
        v->z = p1.z + (int)(((long long)out2.z * 0xe00 + 0x800) >> 12);
    }
}

// @symbol _ZN6dMap_c19UpdateLevelSpecificEv
void dMap_c::UpdateLevelSpecific()
{
    int state = data_0209f2f8;
    switch (state) {
    case 7: {
        u16* p;
        u16 tile;
        int i;
        if (!IsStarCollected(SublevelToLevel(state), 1)) return;
        if (data_0209f220 < 2) return;
        p = (u16*)((char*)G2S::GetBG3CharPtr() - 0x734);
        tile = 0x39c;
        for (i = 0; i < 4; i++) {
            p[0] = tile;
            p[1] = tile + 1;
            p[2] = tile + 2;
            p[3] = tile + 3;
            p += 0x10;
            tile += 0x20;
        }
        break;
    }
    case 8: {
        u16 tile;
        int i;
        u16* p;
        if (!IsStarCollected(SublevelToLevel(state), 1)) return;
        if (data_0209f220 < 2) return;
        p = (u16*)((char*)G2S::GetBG3CharPtr() - 0x6ea);
        tile = 0x35c;
        for (i = 0; i < 6; i++) {
            p[0] = tile;
            p[1] = tile + 1;
            p[2] = tile + 2;
            p[3] = tile + 3;
            p += 0x10;
            tile += 0x20;
        }
        break;
    }
    case 0x12: {
        u16 tile;
        int i;
        u16* p;
        if (!(data_0209caa0[1] & 0x204)) return;
        p = (u16*)((char*)G2S::GetBG3CharPtr() - 0x748);
        tile = 0x35d;
        for (i = 0; i < 6; i++) {
            p[0] = tile;
            p[1] = tile + 1;
            p[2] = tile + 2;
            p += 0x10;
            tile += 0x20;
        }
        break;
    }
    case 1: {
        u16 tile;
        int i;
        u16* p;
        if (!(data_0209caa0[2] & 0x80000)) return;
        p = (u16*)((char*)G2S::GetBG3CharPtr() - 0x73a);
        tile = 0x396;
        for (i = 0; i < 4; i++) {
            p[0] = tile;
            p[1] = tile + 1;
            p[2] = tile + 2;
            p[3] = tile + 3;
            p[4] = tile + 4;
            p[5] = tile + 5;
            p[6] = tile + 6;
            p[7] = tile + 7;
            p[8] = tile + 8;
            p[9] = tile + 9;
            p += 0x10;
            tile += 0x20;
        }
        break;
    }
    case 4: {
        u16 tile;
        int i;
        u16* p;
        if (!(data_0209caa0[2] & 0x80000)) return;
        p = (u16*)((char*)G2S::GetBG3CharPtr() - 0x1ca4);
        tile = 0x38e;
        for (i = 0; i < 4; i++) {
            p[0] = tile;
            p[1] = tile + 1;
            p[2] = tile + 2;
            p[3] = tile + 3;
            p[4] = tile + 4;
            p[5] = tile + 5;
            p[6] = tile + 6;
            p[7] = tile + 7;
            p[8] = tile + 8;
            p[9] = tile + 9;
            p[10] = tile + 10;
            p[11] = tile + 11;
            p[12] = tile + 12;
            p[13] = tile + 13;
            p[14] = tile + 14;
            p[15] = tile + 15;
            p[16] = tile + 16;
            p[17] = tile + 17;
            p += 0x20;
            tile += 0x20;
        }
        break;
    }
    case 0x10: {
        u16 tile;
        int i;
        u16* p;
        if (!Event::GetBit(0xe)) return;
        p = (u16*)((char*)G2S::GetBG3CharPtr() - 0x736);
        tile = 0x3de;
        for (i = 0; i < 2; i++) {
            p[0] = tile;
            p[1] = tile + 1;
            p += 0x10;
            tile += 0x20;
        }
        break;
    }
    case 0x18: {
        u16 tile;
        int i;
        u16* p;
        if (!Event::GetBit(0xe)) return;
        p = (u16*)((char*)G2S::GetBG3CharPtr() - 0x752);
        tile = 0x3be;
        for (i = 0; i < 3; i++) {
            p[0] = tile;
            p[1] = tile + 1;
            p += 0x10;
            tile += 0x20;
        }
        break;
    }
    case 0x19: {
        u16* p;
        if (!Event::GetBit(0xe)) return;
        p = (u16*)((int)G2S::GetBG3CharPtr() - 0x712);
        p[0] = 0x3fe;
        p[1] = 0x3ff;
        break;
    }
    }
}

// @symbol _ZN6dMap_c16CleanupResourcesEv
/* recovered: named members + shared header, real C++ method */
/* dMap_c::CleanupResources() at 0x020f9e8c (ov002) -- vtable slot 3.
 * Returns VS_FAIL (1); the minimap holds no SharedFilePtr/heap resources
 * to release on death. dMap_c : dBase_c : fBase_c.
 */
s32 dMap_c::CleanupResources()
{
    (void)this;
    return 1;
}

// @symbol _ZN6dMap_c16OnPendingDestroyEv
/* recovered: named members + shared header, real C++ method */
/* dMap_c::OnPendingDestroy() at 0x020f9e94 (ov002) -- vtable slot 12.
 * Empty override; the minimap does nothing when marked for destruction.
 */
void dMap_c::OnPendingDestroy()
{
    (void)this;
}

#pragma opt_strength_reduction off
// @symbol _ZN6dMap_c6RenderEv
int dMap_c::Render()
{
    u8 a = data_0209f20c;
    u8 b = data_0209f2c4;
    u8 d = data_0209f294;
    int i;
    int j;
    u8 idx = data_0209f250;

    if ((u8)(d | (b | a)) == 0 || !(data_0209caa0[2] & 0x80) || (a != 0 && (u32)data_0209f2d4 < 3)) {
        Player *pl = data_0209f394[idx];
        int vs = (data_0209f2d8 == 1);
        if (vs != 0) {
            _ZN3OAM9RenderSubEP7OamAttriiii(
                _ZN3OAM18MM_VS_PLAYER_ICONSE[pl->unk8 + idx * 4],
                this->mPlayerIconX[idx], this->mPlayerIconY[idx], -1, 2);
            {
                u16 ang = (s16)this->mAngle + ((pl->unk8E ^ 0xffff) + 0x8001);
                int t = ((u16)(s16)ang >> 4) * 2;
                s16 sn = data_02082214[t + 1];
                this->mArrowMatrixA = (s16)(((s64)sn * this->mArrowScale + 0x800) >> 0xc);
                s16 cn = data_02082214[t];
                this->mArrowMatrixB = (s16)(((s64)cn * this->mArrowScale + 0x800) >> 0xc);
                this->mArrowMatrixC = -this->mArrowMatrixB;
                this->mArrowMatrixD = this->mArrowMatrixA;
                _ZN3OAM6RenderEbP7OamAttriiii5Fix12IiEi(1, _ZN3OAM8MM_ARROWE,
                    this->mPlayerIconX[idx], this->mPlayerIconY[idx], -1, 2, this->mArrowScale, ang);
            }
            {
                for (i = 0, j = 0; i < 4; i++, j += 4) {
                    if (i != idx) {
                        int y = this->mPlayerIconY[i];
                        if ((u16)(y + 0x10) < 0xe0) {
                            int x = this->mPlayerIconX[i];
                            if ((u16)(x + 0x10) < 0x120) {
                                if (data_ov002_02111148 == this->mPlayerMapIDs[i]) {
                                    _ZN3OAM9RenderSubEP7OamAttriiii(
                                        _ZN3OAM20MM_VS_PLAYER_ICONS_SE[j + data_0209f394[i]->unk8],
                                        x, y, -1, 2);
                                }
                            }
                        }
                    }
                }
            }
        } else {
            u16 t = pl->unk6C8;
            if (t == 0 || ((t / 10) & 1) == 0) {
                if (this->mInIntroCutscene == 0) {
                    int icon;
                    if (pl->HasNoCap() != 0)
                        icon = pl->unk6D9 * 4 + 3;
                    else
                        icon = pl->unk8 + pl->unk6D9 * 4;
                    _ZN3OAM9RenderSubEP7OamAttriiii(_ZN3OAM15MM_PLAYER_ICONSE[icon],
                        this->mPlayerIconX[idx], this->mPlayerIconY[idx], -1, 2);
                }
                if (data_0209caa0[2] & 0x80) {
                    u8 s = this->mArrowType;
                    if (s != 0) {
                        u16 ang;
                        if (s == 1)
                            ang = (pl->unk8E ^ 0xffff) + 0x8001;
                        else
                            ang = (s16)this->mAngle + ((pl->unk8E ^ 0xffff) + 0x8001);
                        {
                            int t2 = ((u16)(s16)ang >> 4) * 2;
                            s16 sn = data_02082214[t2 + 1];
                            this->mArrowMatrixA = (s16)(((s64)sn * this->mArrowScale + 0x800) >> 0xc);
                            s16 cn = data_02082214[t2];
                            this->mArrowMatrixB = (s16)(((s64)cn * this->mArrowScale + 0x800) >> 0xc);
                            this->mArrowMatrixC = -this->mArrowMatrixB;
                            this->mArrowMatrixD = this->mArrowMatrixA;
                            _ZN3OAM6RenderEbP7OamAttriiii5Fix12IiEi(1, _ZN3OAM8MM_ARROWE,
                                this->mPlayerIconX[idx], this->mPlayerIconY[idx], -1, 2, this->mArrowScale, ang);
                        }
                    }
                }
            }
        }

        {
            u8 *p = data_0209f37c;
            for (i = 0; i < 12; p++, i++) {
                s8 lvl = this->mStarMapIDs[i];
                if (lvl >= 0) {
                    if (*p != 4) {
                        if (data_ov002_02111148 == lvl) {
                            this->mStarIconAnimFrame[i] += data_0208ee44;
                            if ((u32)this->mStarIconAnimFrame[i] >= 0xc)
                                this->mStarIconAnimFrame[i] = 0;
                            {
                                int flag = 0;
                                u8 k = *p;
                                if (k != 3) {
                                    if (this->mStarIconAnimFrame[i] % 12 > 4)
                                        flag = 1;
                                }
                                int icon = flag + k * 2;
                                {
                                    int y = this->mStarIconY[i];
                                    if ((u16)(y + 0x10) < 0xe0) {
                                        int x = this->mStarIconX[i];
                                        if ((u16)(x + 0x10) < 0x120) {
                                            _ZN3OAM9RenderSubEP7OamAttriiii(_ZN3OAM15MM_STAR_MARKERSE[icon],
                                                x, y, -1, 2);
                                        }
                                    }
                                }
                            }
                        } else {
                            this->mStarIconAnimFrame[i] = 0;
                        }
                    } else {
                        if (data_0209f288 != 0) {
                            _ZN3OAM6RenderEbP7OamAttriiiiP9Matrix2x2(1, _ZN3OAM11MM_RED_COINE,
                                this->mStarIconX[i], this->mStarIconY[i], -1, 2, 0);
                        }
                    }
                } else {
                    this->mStarIconAnimFrame[i] = 0;
                }
            }
        }

        {
            u8 *p1 = data_ov002_02111154;
            u8 *p2 = data_0209f370;
            int vs2 = (data_0209f2d8 == 1);
            void **tbl = (vs2 != 0) ? data_ov002_0210cac8 : data_ov002_0210c748;
            for (i = 0; i < 9; i++, p1++, p2++) {
                if (*p1 != 0) {
                    if (data_ov002_02111148 == this->mCapMapIDs[i]) {
                        int y = this->mCapIconY[i];
                        if ((u16)(y + 0x10) < 0xe0) {
                            int x = this->mCapIconX[i];
                            if ((u16)(x + 0x10) < 0x120) {
                                _ZN3OAM6RenderEbP7OamAttriiiiP9Matrix2x2(1, tbl[*p2], x, y, -1, 2, 0);
                            }
                        }
                    }
                }
            }
        }

        if (!(data_0209caa0[1] & 0x40) && (data_0209caa0[2] & 0x20000)) {
            this->mStarKeyBlinkTimer += 1;
            if ((u32)this->mStarKeyBlinkTimer >= 5)
                this->mStarKeyBlinkTimer = 0;
            if (this->mStarKeyMapID >= 0) {
                if (data_0209d660 == 0 || !(data_020a0db0 & 8)) {
                    int sel = ((u32)this->mStarKeyBlinkTimer < 2) ? 1 : 0;
                    _ZN3OAM6RenderEbP7OamAttriiiiP9Matrix2x2(1, _ZN3OAM12MM_STAR_KEYSE[sel],
                        this->mStarKeyIconX, this->mStarKeyIconY, -1, 2, 0);
                }
            }
        }

        for (i = 0; i < 8; i++) {
            if (data_ov002_02111148 == this->mSpikeBombMapIDs[i]) {
                int y = this->mSpikeBombIconY[i];
                if ((u16)(y + 0x10) < 0xe0) {
                    int x = this->mSpikeBombIconX[i];
                    if ((u16)(x + 0x10) < 0x120) {
                        _ZN3OAM6RenderEbP7OamAttriiiiP9Matrix2x2(1, _ZN3OAM13MM_SPIKE_BOMBE, x, y, -1, 2, 0);
                    }
                }
            }
        }
    }

    return 1;
}

#pragma opt_strength_reduction on

// @symbol _ZN6dMap_c8BehaviorEv
/* recovered: named members + shared header, real C++ method, shadow struct removed
 *
 * One frame of the minimap. This file's whole point is that it no longer
 * carries its own idea of what a dMap_c is: the pre-image declared a private
 * `struct dMap_c` describing the object in full, and every field access went
 * through it. That shadow is gone and the shared header serves instead.
 *
 * The shadow was RICHER than dMap_c.h, which is why it existed. It declared
 * twelve ranges as ARRAYS and indexed them -- 0x070, 0x080, 0x0a0, 0x0d0,
 * 0x100, 0x124, 0x180, 0x1a0, 0x21e, 0x222, 0x23a, 0x249 -- where the header
 * had flat padding, so the header simply could not express what this function
 * does. Those arrays are in the header now and the reconstruction is
 * offset-neutral: the struct still spans 0x256.
 *
 * Two disagreements between the two views, both settled toward the header:
 *   0x1e0 and 0x1f4  the shadow called each a Vector3; only two sites need
 *                    that, and they take `(Vector3*)&mMapCenterWorldX` rather than the
 *                    header asserting a type the other eight matched
 *                    functions never see.
 *   0x21c            the shadow said s16 and then cast EVERY read to (u16).
 *                    The header's u16 says the same thing without the casts.
 */
s32 dMap_c::Behavior()
{
    dMap_c *self = this;
    Obj *obj;
    Vector3 v8, v14, v20, v2c, v38;
    Vector3 *op;
    Obj *player;
    Obj *cam;
    u32 orv;
    s32 i;

    cam = data_0209f318;
    player = (Obj *)data_0209f394[data_0209f250];
    obj = 0;

    if (data_0209f5bc->vt->f[5](data_0209f5bc) == 0) goto L274;
    if (data_0209b454 & 0x40000000) goto L274;
    if (data_0209d4b0 != 0) goto L274;
    if (data_0209f350[data_0209f250] != 0) goto L274;
    if (_ZN6Player12Unk_020ca8f8Ev(player) == 1) goto L274;

    if (self->mTouchCircleTimer != 0) {
        F254 -= data_0208ee44;
    }

    orv = data_0209f2c4 | data_0209f20c | data_0209f294;
    if ((u8)orv) goto L200;
    if (data_02092110 >= 0) goto L200;
    if (data_0209f204 != 0) goto L200;
    if (data_ov002_02111150 != 0) goto L200;
    if (data_0209d660 != 0) goto L200;
    {
        u8 v = data_0209f4ac[data_020a0e40 * 0x18];
        if (v == 0 && self->mTouchCircleTimer == 0) goto L200;
        data_0209d454 |= 4;
        if (v != 0) {
            self->mTouchCircleTimer = 0x1e;
            SetSubBg2Offset(0x100 - data_0209f4a8[data_020a0e40 * 0x18],
                            0x80 - data_0209f4a9[data_020a0e40 * 0x18]);
        }
        _ZN3G2x13SetBlendAlphaEPVttttj((volatile u16 *)0x4001050, 4, 0x28, 4, 0xd);
        if (data_0209f4ae[data_020a0e40 * 0x18] != 2)
            *(volatile u16 *)0x400100c = (u16)((*(volatile u16 *)0x400100c & 0x43) | 0x5300);
        else
            *(volatile u16 *)0x400100c = (u16)((*(volatile u16 *)0x400100c & 0x43) | 0x5500);
        goto L2a4;
    }

L200:
    {
        s32 b = (data_0209f2d8 == 1);
        if (b == 0) {
            if ((data_0209caa0[2] & 0x80) == 0) goto L2a4;
        }
        data_0209d454 &= ~4;
        if (!(u8)orv) {
            *(volatile s32 *)0x4001000 = (*(volatile s32 *)0x4001000 & ~0x1f00) | (data_0209d454 << 8);
            *(volatile u16 *)0x4001050 = 0;
        }
        self->mTouchCircleTimer = 0;
        goto L2a4;
    }

L274:
    if ((data_0209caa0[2] & 0x80) == 0) {
        if (data_0209d4b0 == 0) goto L2a4;
    }
    data_0209d454 &= ~4;

L2a4:
    if (cam == 0) goto L3e8;
    if (SublevelToLevel(data_0209f2f8) != 0x1d) goto A1;
    if (data_0209f2f8 == 1) goto A1;
    if (data_0209f2f8 == 0x33) goto A1;
    if (data_0209f2f8 != 3) goto L350;
A1:
    if (SublevelToLevel(data_0209f2f8) == 4) goto L350;
    if (SublevelToLevel(data_0209f2f8) != 0x13) goto L318;
    if (data_0209f2f8 == 0x2e) goto L350;
L318:
    {
        s32 b = (data_0209f2d8 == 0);
        if (b == 0) goto L360;
        if (data_0209caa0[2] & 0x80) goto L360;
        if (self->mInIntroCutscene != 0) goto L360;
    }
L350:
    self->mAngle = 0;
    goto L3e0;

L360:
    if (self->mInIntroCutscene == 0) goto L3a4;
    if (data_ov002_0211114c == 0) goto L3e0;
    FANG += 0x40;
    if ((u16)self->mAngle >= 0x8000)
        data_ov002_0211114c = 0;
    goto L3e0;

L3a4:
    if (data_0209d660 != 0) goto L3e0;
    {
        s32 f = cam->f154;
        if (f & 0xc000) goto L3e0;
        if (f & 8) goto L3e0;
    }
    self->mAngle = (s16)(cam->f17c & 0xffe0);

L3e0:
    obj = (Obj *)cam->f110;

L3e8:
    if (obj == 0) goto Lae4;

    if (self->mInIntroCutscene == 0) goto L44c;
    if (data_ov002_02111144 == 0) goto L4d8;
    F218 -= 9;
    if (self->mTargetInvScale <= self->mInvScale) goto L4d8;
    self->mInvScale = self->mTargetInvScale;
    data_ov002_02111144 = 0;
    data_ov002_0211114c = 1;
    goto L4d8;

L44c:
    if (data_0209d660 == 0) goto L47c;
    if (self->mInvScale < 0xbb8)
        F218 += 0x1c;
    goto L4d8;

L47c:
    if (self->mTargetInvScale <= self->mInvScale) goto L4b0;
    F218 += 0x1c;
    if (self->mTargetInvScale < self->mInvScale)
        self->mInvScale = self->mTargetInvScale;
    goto L4d8;

L4b0:
    if (self->mTargetInvScale >= self->mInvScale) goto L4d8;
    F218 -= 0x1c;
    if (self->mTargetInvScale > self->mInvScale)
        self->mInvScale = self->mTargetInvScale;

L4d8:
    self->mCurrentScale = _ZN4cstd4fdivEii(self->mScale, self->mInvScale);
    { s32 s1 = data_02082214[(((s32)(u16)self->mAngle >> 4) * 2) + 1];
      self->mBgMatrixA = FMUL(s1, self->mInvScale); }
    { s32 s2 = data_02082214[((s32)(u16)self->mAngle >> 4) * 2];
      self->mBgMatrixB = FMUL(s2, self->mInvScale); }
    self->mBgMatrixC = -self->mBgMatrixB;
    self->mBgMatrixD = self->mBgMatrixA;
    ((Vector3*)&self->mMapCenterWorldX)->x = ((Vector3*)&self->mMapOriginX)->x;
    ((Vector3*)&self->mMapCenterWorldX)->y = ((Vector3*)&self->mMapOriginX)->y;
    ((Vector3*)&self->mMapCenterWorldX)->z = ((Vector3*)&self->mMapOriginX)->z;
    self->mMapCenterX = self->mMapCenterOffset + ((FMUL(((Vector3*)&self->mMapCenterWorldX)->x, self->mScale) + 0x800) >> 12);
    self->mMapCenterY = self->mMapCenterOffset + ((FMUL(((Vector3*)&self->mMapCenterWorldX)->z, self->mScale) + 0x800) >> 12);

    op = (Vector3 *)(((int)obj + 0x5c));
    v14 = *op;
    FixTHIPaintingRoomPos(v14);
    _ZN6dMap_c15GetPosOnMinimapER7Vector3S1_5Fix12IiEsS1_(&v14, (Vector3*)&self->mMapCenterWorldX, self->mCurrentScale, self->mAngle, &v8);
    {
        s32 p = data_0209f250;
        self->mPlayerIconX[p] = (v8.x + 0x800) >> 12;
        self->mPlayerIconY[p] = (v8.z + 0x800) >> 12;

        if (SublevelToLevel(data_0209f2f8) != 0x1d) goto B1;
        if (data_0209f2f8 != 1) goto L6a4;
        if (data_0209f2f8 == 0x33) goto B1;
        if (data_0209f2f8 != 3) goto L6a4;
B1:
        if (SublevelToLevel(data_0209f2f8) != 0x13) goto L6f0;
        if (data_0209f2f8 != 0x2e) goto L6f0;
L6a4:
        if (self->mPlayerIconX[p] < 0x60) { v8.x = 0x60000; }
        else if (self->mPlayerIconX[p] > 0xa0) { v8.x = 0xa0000; }
        if (self->mPlayerIconY[p] < 0x40) { v8.z = 0x40000; }
        else if (self->mPlayerIconY[p] > 0x80) { v8.z = 0x80000; }
        goto L738;
L6f0:
        if (self->mPlayerIconX[p] < 0x24) { v8.x = 0x24000; }
        else if (self->mPlayerIconX[p] > 0xdc) { v8.x = 0xdc000; }
        if (self->mPlayerIconY[p] < 0x24) { v8.z = 0x24000; }
        else if (self->mPlayerIconY[p] > 0x9c) { v8.z = 0x9c000; }
    }
L738:
    _ZN6dMap_c20GetPosFromMinimapPosER7Vector3S1_5Fix12IiEsS1_(&v8, (Vector3*)&self->mMapCenterWorldX, self->mCurrentScale, self->mAngle, &v20);
    Vec3_Sub(&v38, &v14, &v20);
    AddVec3((Vector3*)&self->mMapCenterWorldX, &v38, (Vector3*)&self->mMapCenterWorldX);
    self->mMapCenterX = self->mMapCenterOffset + ((FMUL(((Vector3*)&self->mMapCenterWorldX)->x, self->mScale) + 0x800) >> 12);
    self->mMapCenterY = self->mMapCenterOffset + ((FMUL(((Vector3*)&self->mMapCenterWorldX)->z, self->mScale) + 0x800) >> 12);

    for (i = 0; i < 4; i++) {
        Obj *o = (Obj *)data_0209f394[i];
        if (o != 0) {
        v2c = *(Vector3 *)(((int)o + 0x5c));
        FixTHIPaintingRoomPos(v2c);
        _ZN6dMap_c15GetPosOnMinimapER7Vector3S1_5Fix12IiEsS1_(&v2c, (Vector3*)&self->mMapCenterWorldX, self->mCurrentScale, self->mAngle, &v8);
        self->mPlayerIconX[i] = (v8.x + 0x800) >> 12;
        self->mPlayerIconY[i] = (v8.z + 0x800) >> 12;
        if (i != data_0209f250)
            self->mPlayerMapIDs[i] = (s8)GetMinimapID(o, -1);
        else
            self->mPlayerMapIDs[i] = (s8)GetMinimapID(o, data_ov002_02111148);
        } else {
            self->mPlayerMapIDs[i] = -1;
        }
    }

    for (i = 0; i < 0xc; i++) {
        Obj *o = data_0209f40c[i];
        if (o != 0) {
        _ZN6dMap_c15GetPosOnMinimapER7Vector3S1_5Fix12IiEsS1_(&o->pos, (Vector3*)&self->mMapCenterWorldX, self->mCurrentScale, self->mAngle, &v8);
        self->mStarIconX[i] = (v8.x + 0x800) >> 12;
        self->mStarIconY[i] = (v8.z + 0x800) >> 12;
        if (data_0209f37c[i] != 4)
            self->mStarMapIDs[i] = (s8)GetMinimapID(o, -1);
        else
            self->mStarMapIDs[i] = 1;
        } else {
            self->mStarMapIDs[i] = -1;
        }
    }

    for (i = 0; i < 9; i++) {
        Obj *o = data_0209f3e8[i];
        if (o != 0) {
        _ZN6dMap_c15GetPosOnMinimapER7Vector3S1_5Fix12IiEsS1_(&o->pos, (Vector3*)&self->mMapCenterWorldX, self->mCurrentScale, self->mAngle, &v8);
        self->mCapIconX[i] = (v8.x + 0x800) >> 12;
        self->mCapIconY[i] = (v8.z + 0x800) >> 12;
        self->mCapMapIDs[i] = (s8)GetMinimapID(o, -1);
        } else { self->mCapMapIDs[i] = -1; }
    }

    if (data_0209caa0[1] & 0x40) goto La64;
    if ((data_0209caa0[2] & 0x20000) == 0) goto La64;
    {
        Obj *o = (Obj *)data_0209f33c;
        if (o == 0) { self->mStarKeyMapID = -1; goto La64; }
        _ZN6dMap_c15GetPosOnMinimapER7Vector3S1_5Fix12IiEsS1_(&o->pos, (Vector3*)&self->mMapCenterWorldX, self->mCurrentScale, self->mAngle, &v8);
        self->mStarKeyIconX = (v8.x + 0x800) >> 12;
        self->mStarKeyIconY = (v8.z + 0x800) >> 12;
        self->mStarKeyMapID = 1;
    }

La64:
    for (i = 0; i < 8; i++) {
        Obj *o = data_0209f3a4[i];
        if (o != 0) {
        _ZN6dMap_c15GetPosOnMinimapER7Vector3S1_5Fix12IiEsS1_(&o->pos, (Vector3*)&self->mMapCenterWorldX, self->mCurrentScale, self->mAngle, &v8);
        self->mSpikeBombIconX[i] = (v8.x + 0x800) >> 12;
        self->mSpikeBombIconY[i] = (v8.z + 0x800) >> 12;
        self->mSpikeBombMapIDs[i] = o->f0cc;
        } else { self->mSpikeBombMapIDs[i] = -1; }
    }

Lae4:
    {
        s32 id = GetMinimapID(obj, data_ov002_02111148);
        if (id == data_ov002_02111148) goto Lc30;
        if (id >= 0x10) goto Lc30;
        if (id < 0) goto Lbf0;

        if (SublevelToLevel(data_0209f2f8) != 0x1d) goto C1;
        if (data_0209f2f8 == 1) goto C1;
        if (data_0209f2f8 == 0x33) goto C1;
        if (data_0209f2f8 != 3) goto Lb9c;
C1:
        if (SublevelToLevel(data_0209f2f8) == 4) goto Lb9c;
        if (SublevelToLevel(data_0209f2f8) != 0x13) goto Lb84;
        if (data_0209f2f8 == 0x2e) goto Lb9c;
Lb84:
        if (SublevelToLevel(data_0209f2f8) != -1) goto Lbc0;
Lb9c:
        *(volatile u16 *)0x400100e = ((0x1f - id) << 8) | ((*(volatile u16 *)0x400100e & 0x43) | 0x4010);
        goto Lbdc;
Lbc0:
        *(volatile u16 *)0x400100e = ((0x1f - id) << 8) | ((*(volatile u16 *)0x400100e & 0x43) | 0x10);
Lbdc:
        data_0209d454 |= 8;
        goto Lc00;
Lbf0:
        data_0209d454 &= ~8;
Lc00:
        *(volatile s32 *)0x4001000 = (*(volatile s32 *)0x4001000 & ~0x1f00) | (data_0209d454 << 8);
        data_ov002_02111148 = (s8)id;
        self->mTargetInvScale = GetMinimapScale(id);
    }
Lc30:
    UpdateMinimap(&self->mBgMatrixA, self->mMapCenterX, self->mMapCenterY, self->mMapCenterX - 0x80, self->mMapCenterY - 0x60);
    return 1;
}

/* What InitResources loads the map graphics with. */
extern "C" {
int func_0202a980(void);
int LoadFile(int handle);
void DecompressLZ16(int src, void* dst);
void Deallocate(void* ptr);
int func_0202a96c(void);
void _ZN3GXS18BeginLoadBGExtPlttEv(void);
void _ZN3GXS13LoadBGExtPlttEPKvjj(const void* p, u32 a, u32 b);
void _ZN3GXS16EndLoadBGExtPlttEv(void);
void _ZN3GXS10LoadBGPlttEPKvjj(const void* p, u32 a, u32 b);
void* _ZN3G2S12GetBG3ScrPtrEv(void);
int func_0202a958(void);
extern u8 data_0209f2e8;
extern u16* data_0209f334;
extern s32 data_0209fc48;
}

#pragma opt_strength_reduction off
// @symbol _ZN6dMap_c13InitResourcesEv
/* recovered: named members + shared header, real C++ method */
int dMap_c::InitResources()
{
    u16 *p;
    s32 i;

    *(volatile u16*)0x400100e = (*(volatile u16*)0x400100e & ~3) | 2;
    *(volatile u16*)0x400100e = (*(volatile u16*)0x400100e & 0x43) | 0x1f10;
    *(volatile u16*)0x400100e &= ~0x40;

    {
        int id1 = func_0202a980();
        if (id1 != 0) {
            int f1 = LoadFile(id1);
            DecompressLZ16(f1, _ZN3G2S13GetBG3CharPtrEv());
            Deallocate((void*)f1);
        }
    }

    {
        int id2 = func_0202a96c();
        if (id2 != 0) {
            int f2 = LoadFile(id2);
            _ZN3GXS18BeginLoadBGExtPlttEv();
            _ZN3GXS13LoadBGExtPlttEPKvjj((void*)f2, 0x6000, 0x200);
            _ZN3GXS16EndLoadBGExtPlttEv();
            _ZN3GXS10LoadBGPlttEPKvjj((void*)f2, 0, 2);
            Deallocate((void*)f2);
        }
    }

    p = data_0209f334;
    for (i = 0; i < data_0209f2e8; i++) {
        if (*p != 0) {
            int f3 = LoadFile(*p);
            DecompressLZ16(f3, (char*)_ZN3G2S12GetBG3ScrPtrEv() - (i << 11));
            Deallocate((void*)f3);
        }
        p++;
    }

    {
        int b = (data_0209f2d8 == 1);
        if (!b) {
            UpdateLevelSpecific();
        }
    }

    data_ov002_02111148 = (signed char)GetMinimapID((Obj *)data_0209f394[data_0209f250], -1);

    if (data_ov002_02111148 >= 0) {
        if ((SublevelToLevel(data_0209f2f8) == 0x1d && data_0209f2f8 != 1 && data_0209f2f8 != 0x33 && data_0209f2f8 != 3)
            || SublevelToLevel(data_0209f2f8) == 4
            || (SublevelToLevel(data_0209f2f8) == 0x13 && data_0209f2f8 == 0x2e)
            || SublevelToLevel(data_0209f2f8) == -1)
        {
            *(volatile u16*)0x400100e = (u16)(((0x1f - data_ov002_02111148) << 8) | ((*(volatile u16*)0x400100e & 0x43) | 0x4010));
            mMapWidth = 0x100;
            mMapCenterOffset = 0x80;

            if (SublevelToLevel(data_0209f2f8) == 4) {
                mMapOriginX = 0x258000;
                mMapOriginY = 0;
                mMapOriginZ = 0x64000;
            } else if (SublevelToLevel(data_0209f2f8) == 0x1d && data_0209f2f8 != 1 && data_0209f2f8 != 0x33 && data_0209f2f8 != 3) {
                mMapOriginX = -0x2bc000;
                mMapOriginY = 0;
                mMapOriginZ = -0x2bc000;
            } else {
                SublevelToLevel(data_0209f2f8);
                mMapOriginX = 0;
                mMapOriginY = 0;
                mMapOriginZ = 0;
            }
            mArrowType = 1;
        } else {
            *(volatile u16*)0x400100e = (u16)(((0x1f - data_ov002_02111148) << 8) | ((*(volatile u16*)0x400100e & 0x43) | 0x10));
            mMapWidth = 0x80;
            mMapCenterOffset = 0x40;
            mMapOriginX = 0;
            mMapOriginY = 0;
            mMapOriginZ = 0;
            mArrowType = 2;
        }
        data_0209d454 |= 8;
    } else {
        data_0209d454 &= ~8;
    }

    mTargetInvScale = GetMinimapScale(data_ov002_02111148);

    {
        int b1 = (data_0209f2d8 == 0);
        if (b1) {
            if (!(data_0209caa0[2] & 0x80)) {
                int b3 = (data_0209fc48 != 0);
                if (!b3) {
                    mInvScale = (mTargetInvScale) << 1;
                    mAngle = 0;
                    mInIntroCutscene = 1;
                    goto unk218_done;
                }
            }
        }
        mInvScale = mTargetInvScale;
        mInIntroCutscene = 0;
    unk218_done:;
    }

    data_ov002_02111150 = 0;
    mBgMatrixA = 0x1000;
    mBgMatrixB = 0;
    mBgMatrixC = 0;
    mBgMatrixD = 0x1000;
    mArrowMatrixA = 0x1000;
    mArrowMatrixB = 0;
    mArrowMatrixC = 0;
    mArrowMatrixD = 0x1000;
    unk_1ec = 0;
    mArrowScale = 0x1000;
    unk_090 = 0;
    unk_094 = 0;
    unk_098 = 0;
    unk_09c = 0;

    mScale = func_0202a958();
    mScale = ((mMapWidth) << 12) / (mScale) / 10;

    return 1;
}

#pragma opt_strength_reduction on

// @symbol _ZN6dMap_c20GetPosFromMinimapPosER7Vector3S1_5Fix12IiEsS1_
/* recovered: named members + shared header */
extern "C" void _ZN6dMap_c20GetPosFromMinimapPosER7Vector3S1_5Fix12IiEsS1_(
    Vector3* a, Vector3* b, int c, short d, Vector3* e)
{
    struct Vec3 local;
    Vec3_Sub((Vector3*)&local, a, (Vector3*)&data_ov002_0211116c);
    Vec3_DivScalarInPlace(&local, c);
    Vec3_RotateYAndTranslate((struct Vec3*)e, (struct Vec3*)b, d, &local);
}

// @symbol _ZN6dMap_c15GetPosOnMinimapER7Vector3S1_5Fix12IiEsS1_
extern "C" {
void _ZN6dMap_c15GetPosOnMinimapER7Vector3S1_5Fix12IiEsS1_(Vector3* out, Vector3* a, int s, short ang, Vector3* res)
{
    struct Vec3 v;
    Vec3_Sub((Vector3*)&v, out, a);
    Vec3_MulScalarInPlace(&v, s);
    Vec3_RotateYAndTranslate((struct Vec3*)res, &data_ov002_0211116c, (short)(-ang), &v);
}
}

