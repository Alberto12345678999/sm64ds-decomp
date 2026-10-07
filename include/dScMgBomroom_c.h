#ifndef DSCMGBOMROOM_C_H
#define DSCMGBOMROOM_C_H
#include "dScMgBase_c.h"

/* Bob-omb sorting minigame (dScMgBomroom_c : dScMgBase_c). Fields below
 * 0x4660 belong to the base and stay raw; the bombs themselves start there.
 *
 * The name is the ROM's RTTI name, and rtti_extract.py confirms it is a
 * leaf (no RTTI record names it as a base). dScMgBomroom_c_classInit (alias
 * MgSortOrSplode_Spawn) installs its vtable for the MG_BOMROOM profile.
 */
/* One bomb: 0x70 records at +0x4660, stride 0x40. grabX/grabY are the
   stylus offset at the grab; speed is the Fix12 step along angle. */
struct dScMgBomroom_Bomb {
    s32 x;            /* +0x00 -- Fix12 */
    s32 y;            /* +0x04 -- Fix12 */
    s32 grabX;        /* +0x08 -- stylus x minus bomb x, Fix12 */
    s32 grabY;        /* +0x0c -- stylus y minus bomb y, Fix12 */
    s32 speed;        /* +0x10 -- Fix12 per-frame step; scaled by sin/cos of
                                   angle while roaming, added directly when
                                   walking to its slot */
    u8  unk_14[0x10];
    s32 sound;        /* +0x24 -- sound handle; func_02012468 takes it back
                                   and returns it each frame */
    u8  unk_28[4];
    u16 angle;        /* +0x2c -- 0..0xffff, sine-table index >> 4 */
    u16 unk_2e;       /* +0x2e -- counter, see func_ov006_020d69b8 */
    u16 unk_30;       /* +0x30 */
    u8  unk_32[0x4];
    u8  color;        /* +0x36 -- 0/1; also picks which pen box it bounces in */
    u8  state;        /* +0x37 -- 5 = settled */
    u8  active;       /* +0x38 */
    u8  unk_39[0x7];
};
#ifndef SM64DS_PLATFORM_PC
/* ROM layout under mwccarm; host ABI divergence is tracked separately. */
typedef char dScMgBomroom_Bomb_size_must_be_0x40[sizeof(struct dScMgBomroom_Bomb) == 0x40 ? 1 : -1];
#endif

/* A 0x10-byte HUD sprite record. Each array of them has a state machine
   (state indexes a pointer-to-member table) that steps the frame with the
   timer. */
struct dScMgBomroom_Sign {
    s32 x;            /* +0x00 -- Fix12 */
    s32 y;            /* +0x04 */
    u16 timer;        /* +0x08 */
    u8  pad_0a[0x2];
    u8  state;        /* +0x0c */
    u8  active;       /* +0x0d */
    u8  visible;      /* +0x0e */
    u8  frame;        /* +0x0f */
};

/* The single prompt at 0x62a0: the same shape with frame and visible
   swapped (func_ov006_020d5e5c draws frame while visible is set). */
struct dScMgBomroom_Prompt {
    s32 x;            /* +0x00 */
    s32 y;            /* +0x04 */
    u16 timer;        /* +0x08 */
    u8  pad_0a[0x2];
    u8  state;        /* +0x0c -- data_ov006_02141660 */
    u8  active;       /* +0x0d */
    u8  frame;        /* +0x0e */
    u8  visible;      /* +0x0f */
};

/* The two markers at 0x62b0 (func_ov006_020d5c88 draws them). */
struct dScMgBomroom_Marker {
    s32 x;            /* +0x00 */
    s32 y;            /* +0x04 */
    u16 timer;        /* +0x08 */
    u8  pad_0a[0x2];
    u8  animating;    /* +0x0c */
    u8  visible;      /* +0x0d */
    u8  frame;        /* +0x0e */
    u8  pad_0f;
};

#ifndef SM64DS_PLATFORM_PC
typedef char dScMgBomroom_Sign_size_must_be_0x10[sizeof(struct dScMgBomroom_Sign) == 0x10 ? 1 : -1];
typedef char dScMgBomroom_Prompt_size_must_be_0x10[sizeof(struct dScMgBomroom_Prompt) == 0x10 ? 1 : -1];
typedef char dScMgBomroom_Marker_size_must_be_0x10[sizeof(struct dScMgBomroom_Marker) == 0x10 ? 1 : -1];
#endif

struct dScMgBomroom_c : dScMgBase_c {
    virtual ~dScMgBomroom_c();
    virtual s32 InitResources();  /* slot 0 */
    virtual s32 Behavior();       /* slot 6 */
    virtual s32 Render();         /* slot 9 */
    virtual void OnYoshiTryEat(int arg);               /* slot 18 */

    dScMgBomroom_Bomb mBombs[0x70]; /* 0x4660 -- 0x70 x 0x40 */
    dScMgBomroom_Sign   mSignsA[2];    /* 0x6260 */
    dScMgBomroom_Sign   mSignsB[2];    /* 0x6280 */
    dScMgBomroom_Prompt mPrompt;       /* 0x62a0 */
    dScMgBomroom_Marker mMarkers[2];   /* 0x62b0 */
    s32 unk_62d0;            /* 0x62d0 */
    s32 unk_62d4;            /* 0x62d4 */
    s32 unk_62d8;            /* 0x62d8 */
    s32 mBg2Y;               /* 0x62dc -- Fix12; func_ov006_020d5b10 slides BG2 */
    u16 unk_62e0;            /* 0x62e0 */
    s16 unk_62e2;            /* 0x62e2 */
    s16 unk_62e4;            /* 0x62e4 */
    s16 unk_62e6;            /* 0x62e6 */
    u16 unk_62e8;            /* 0x62e8 */
    u16 unk_62ea;            /* 0x62ea */
    u8  pad_62ec[0x2];
    u16 unk_62ee;            /* 0x62ee */
    u16 unk_62f0;            /* 0x62f0 */
    u16 mBg2Hold;            /* 0x62f2 -- frames BG2 stays raised */
    u8  mBg2State;           /* 0x62f4 -- 0 idle, 1 raising, 2 holding/lowering */
    u8  unk_62f5;            /* 0x62f5 */
    u8  unk_62f6;            /* 0x62f6 */
    u8  unk_62f7;            /* 0x62f7 */
    u8  unk_62f8;            /* 0x62f8 */
    u8  unk_62f9;            /* 0x62f9 */
    u8  mRoundOver;          /* 0x62fa -- func_ov006_020d5ab0 draws the banner */
    u8  unk_62fb;            /* 0x62fb */
    u8  unk_62fc;            /* 0x62fc */
    /* trailing extent the ROM's `new dScMgBomroom_c` literal proves; see tools/opnew_sizes.py */
    u8  pad_62fd[0x3];
};

#ifndef SM64DS_PLATFORM_PC
/* ROM layout under mwccarm; host ABI divergence is tracked separately. */
typedef char dScMgBomroom_c_size_must_be_0x6300[sizeof(struct dScMgBomroom_c) == 0x6300 ? 1 : -1];
#endif

#endif
