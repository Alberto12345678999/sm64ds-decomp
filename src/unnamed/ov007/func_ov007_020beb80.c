#include "types.h"
#include "nitro/fx/fx.h"

extern int func_020538b8(int a, int b);
extern void *func_ov007_020b7690(int i);
extern int func_02053644(s16 *v);
extern int _ZN4cstd4fdivEii(int a, int b);
extern void func_02053380(s16 *in, s16 *out);

/* The fields this file reads; func_ov007_020be9ac calls it with the same
 * object (its b0/b1 bytes and +0x18 callback are not read here).
 * mOwner is the animated object it tracks: its +0x98/+0x94 words gate the
 * update below, and its first word leads (via +0xc) to the node `P` whose
 * +0x24 position this follows. mYaw takes func_020538b8 (atan2) of P's
 * +0x18 x/z; mPrevPos holds P's position from the last gated update, so
 * `dd` is the motion since then. mSlot picks the element
 * func_ov007_020b7690 returns. */
typedef struct BoneFollower {
    u8 pad_00[2];
    u8 mSlot; /* 0x02 */
    u8 pad_03;
    char *mOwner;   /* 0x04 */
    int mYaw;       /* 0x08 */
    Vector3 mPrevPos; /* 0x0c */
} BoneFollower;

/* The element func_ov007_020b7690 hands back; only the fields written here are named. */
typedef struct TrackElem {
    u8 pad_00[0x1c];
    int flags;   /* 0x1c */
    Vector3 pos; /* 0x20 */
    u8 pad_2c[0x10];
    Vector3s delta; /* 0x3c */
    u8 pad_42[0xa];
    int vel; /* 0x4c */
    u8 pad_50[8];
    u8 frames; /* 0x58 */
} TrackElem;

void func_ov007_020beb80(char *self) {
    BoneFollower *f = (BoneFollower *)self;
    char *B = *(char **)f->mOwner;
    char *P = *(char **)(B + 0xc);
    int *q = (int *)(int)(P + 0x18);
    int r;
    Vector3s dd;
    TrackElem *e;
    int frames;
    int vel;
    int sc;
    Vector3 *tp = (Vector3 *)(int)(P + 0x24);
    r = func_020538b8(q[0], q[2]);
    dd.x = (short)(tp->x - f->mPrevPos.x);
    dd.y = (short)(tp->y - f->mPrevPos.y);
    dd.z = (short)(tp->z - f->mPrevPos.z);
    if (*(int *)(f->mOwner + 0x98) != 0) {
        f->mYaw = r;
        f->mPrevPos = *tp;
    }
    e = (TrackElem *)func_ov007_020b7690(f->mSlot);
    {
        char *A = f->mOwner;
        if (*(int *)(A + 0x94) != 0 && (unsigned)*(*(int **)(A + 0x18)) <= 1) {
            vel = 0;
            frames = 0x1000;
            if (dd.x != 0 || dd.y != 0 || dd.z != 0) {
                int mag = (short)func_02053644((s16 *)&dd);
                int t;
                if (mag <= 0) sc = 0;
                else if (mag >= 0xfa0) sc = 0x1000;
                else sc = _ZN4cstd4fdivEii(mag, 0xfa0);
                if (mag <= 0x1f4) t = 0;
                else if (mag >= 0x3e8) t = 0x1000;
                else t = _ZN4cstd4fdivEii(mag - 0x1f4, 0x1f4);
                frames -= t;
                func_02053380((s16 *)&dd, (s16 *)&dd);
                e->delta = dd;
                vel = (short)FX_MUL(sc, 0x460);
            }
            e->frames = (u8)(((frames << 2) >> 12) + 1);
            e->vel = vel;
            e->flags &= ~2;
            e->pos = *tp;
        } else {
            e->flags |= 2;
        }
    }
}
