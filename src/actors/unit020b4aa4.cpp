//cpp
/* ov004 minigame unit 0x020b4aa4..0x020b67e8, text only.
 *
 * Twenty 0x24-byte entries at data_ov004_020bfa34: a position at +8,
 * a target at +0x10, a step at +0x18, and an active byte at +0x22.
 * func_ov004_020b67bc runs __cxa_vec_cleanup over them. The state
 * machine steps through data_ov004_020bfa20. No RTTI or vtable.
 *
 * leftovers:
 * - Address names and extern "C" stay. There is no class to hang them on.
 * - Struct copies go through an int[2] member so C++ keeps the block move.
 * - The entry array and the state pointer belong to the sinit, not this TU.
 */

#include "types.h"
#include "PlayerInput.h"

struct Pair { int a, b; };
struct V2 { int x, y; };
typedef struct { int x, y; } Vec2_Fix12;
struct P2 { int w[2]; };
struct M2 { int w[2]; };
struct W2 { int w[2]; };
struct P { int w[2]; };
struct E36 { int w[9]; };

struct C;
typedef void (C::*PMF)();
struct C { PMF pmf; };

namespace Sound { void PlayBank2_2D(unsigned int); }
int ApproachLinear(int&, int, int);
int ApproachLinear2(short&, short, short);

extern "C" {
extern void Vec2_Sub(void* o, void* a, void* b);
extern void func_0203d680(void* out, void* in, int scale);
extern int __aeabi_idiv(int a, int b);
extern void __cxa_vec_cleanup(void *, unsigned int, unsigned int, void (*)(void *));
extern unsigned int func_02012790(unsigned int a);
extern int GetGameLanguage(void);
extern void Hud_RenderSprite(void* a0, int a1, int a2, int a3, int a4);

extern void func_ov004_020b1b40(void* c);
extern void func_ov004_020b1b08(void* x);
extern void func_ov004_020b1de8(int a, int b, int c, int d);
extern int func_ov004_020b04c0(void);
extern int func_ov004_020ae1a8(void);
extern void func_ov004_020adb1c(int self);
extern void func_ov004_020af948(void *a, int b, int c, void *d);
extern void func_ov004_020b2444(int a, int b, int c, int d, int e, int f, int g);

extern void func_ov004_020b4b84(char* c, int* in);
extern void func_ov004_020b4cc4(char* r4);
extern void func_ov004_020b4e78(char* c);
extern void func_ov004_020b506c(char* c);
extern void func_ov004_020b5108(char* c, int* in);
extern void func_ov004_020b51e4(char* p);
extern void func_ov004_020b52b8(char *c);
extern void func_ov004_020b52fc(C *c);
extern void func_ov004_020b5334(char* c);
extern void func_ov004_020b5368(void);
extern void func_ov004_020b53f0(void);
extern void func_ov004_020b556c(void);
extern void func_ov004_020b586c(void);
extern void func_ov004_020b58c4(void);
extern void func_ov004_020b5a54(void);
extern void func_ov004_020b5aac(void);
extern void func_ov004_020b5c18(void);
extern void func_ov004_020b5768(void);
extern void func_ov004_020b5f6c(void);
extern void func_ov004_020b612c(void);
extern void func_ov004_020b6234(void);
extern void func_ov004_020b653c(int arg);
extern void func_ov004_020b67e0(void);

extern int data_ov004_020b9488[];
extern int data_ov004_020bc7d0;
extern int data_ov004_020bc7d4;
extern struct W2 data_ov004_020bc7d8;
extern struct M2 data_ov004_020bc7e0;
extern char data_ov004_020bc7e8[];
extern struct P2 data_ov004_020bc7f0;
extern struct M2 data_ov004_020bc7f8;
extern struct P data_ov004_020bc800;
extern int data_ov004_020bc808[];
extern struct W2 data_ov004_020bc810;
extern struct P2 data_ov004_020bc818;
extern struct P data_ov004_020bc820;
extern int *data_ov004_020bc828[];
extern unsigned char *data_ov004_020bc83c[];
extern short data_ov004_020bf9e4;
extern int data_ov004_020bf9e8;
extern int data_ov004_020bf9ec;
extern int data_ov004_020bf9f0;
extern int data_ov004_020bf9f4;
extern int data_ov004_020bf9f8;
extern int data_ov004_020bf9fc;
extern int data_ov004_020bfa00;
extern int data_ov004_020bfa04;
extern int data_ov004_020bfa08;
extern int data_ov004_020bfa0c;
extern int data_ov004_020bfa10;
extern int data_ov004_020bfa14;
extern int data_ov004_020bfa18;
extern int data_ov004_020bfa1c;
extern void (*data_ov004_020bfa20)();
extern int data_ov004_020bfa24;
extern struct E36 data_ov004_020bfa34[];
extern unsigned char data_ov004_020bfa56[];
extern char* data_ov004_020beb68;
extern int data_020a0db0;
}

// @symbol func_ov004_020b67e4
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b67e4(void)
{
}
}

// @symbol func_ov004_020b67e0
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b67e0(void)
{
}
}

// @symbol func_ov004_020b67bc
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b67bc(void)
{
    __cxa_vec_cleanup(data_ov004_020bfa34, 0x14, 0x24, (void (*)(void *))func_ov004_020b67e0);
}
}

// @symbol func_ov004_020b66d4
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b66d4(void) {
    int i;
    for (i = 0; i < 0x14; i++)
        func_ov004_020b5334((char*)&data_ov004_020bfa34[i]);
    data_ov004_020bfa00 = 0;
    data_ov004_020bfa18 = 0;
    data_ov004_020bc7d0 = 5;
    data_ov004_020bf9fc = 0;
    data_ov004_020bf9f8 = 0;
    data_ov004_020bfa04 = 0;
    data_ov004_020bf9e4 = 0;
    data_ov004_020bf9ec = 0;
    data_ov004_020bfa10 = 0;
    data_ov004_020bf9f0 = 0;
    data_ov004_020bf9e8 = 0;
    data_ov004_020bfa24 = 0;
    data_ov004_020bc7d4 = 0;
    data_ov004_020bfa20 = 0;
}
}

// @symbol func_ov004_020b65e4
/* func_ov004_020b65e4 at 0x020b65e4
 *
 * Matched byte-for-byte with mwccarm 1.2/sp2p3 (ov004).
 */
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b65e4(void) {
    int i;
    unsigned char *p;

    if (data_ov004_020bf9ec == 0 && data_ov004_020bfa18 != 0) {
        int idx = gActivePlayerSlot;
        int flag = ((unsigned char (*)[4])gTouchHeld)[idx][0] != 0 && ((unsigned char (*)[4])gTouchEdge)[idx][0] != 0;
        if (flag) {
            int a = ((unsigned char (*)[4])gTouchX)[idx][0];
            int b = ((unsigned char (*)[4])gTouchY)[idx][0];
            if (a < 0x40 && b < 0x50) {
                func_ov004_020b6234();
            }
        }
    }

    p = (unsigned char*)data_ov004_020bfa34;
    for (i = 0; i < 0x14; i++) {
        func_ov004_020b52fc((C*)p);
        p += 0x24;
    }

    if (data_ov004_020bfa20 != 0) {
        data_ov004_020bfa20();
    }
}
}

// @symbol func_ov004_020b653c
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b653c(int arg)
{
    int absv;
    int r4;
    int r6;

    if (arg < 0) absv = -arg; else absv = arg;

    if (arg >= 0) {
        int idx = GetGameLanguage();
        r4 = 0x14;
        r6 = *(int *)(data_ov004_020bc83c[idx] + 0x34);
    } else {
        int idx = GetGameLanguage();
        r4 = 0x28;
        r6 = *(int *)(data_ov004_020bc83c[idx] + 0x38);
    }

    func_ov004_020b1de8(0x6e, 0x60, 0, -1);
    func_ov004_020af948((void *)r6, 0x80, 0x60, 0);
    func_ov004_020b2444(0x92, 0x60, absv, 0, -1, 2, r4);
}
}

// @symbol func_ov004_020b6430
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b6430(void) {
    int i;
    char *p;
    if (data_ov004_020bf9ec == 0 && data_ov004_020bfa18 != 0) {
        if (data_020a0db0 & 0x10) {
            Hud_RenderSprite((void*)data_ov004_020bc828[GetGameLanguage()][0], 0x14, 0x30, -1, -1);
        } else {
            Hud_RenderSprite((void*)data_ov004_020bc828[GetGameLanguage()][1], 0x14, 0x30, -1, -1);
        }
        Hud_RenderSprite((void*)data_ov004_020bc828[GetGameLanguage()][2], 0x14, 0x30, -1, -1);
    }
    if (data_ov004_020bfa24 != 0) {
        func_ov004_020b653c(data_ov004_020bf9e8);
    }
    for (p = (char*)data_ov004_020bfa34, i = 0; i < 0x14; i++) {
        func_ov004_020b52b8(p);
        p += 0x24;
    }
}
}

// @symbol func_ov004_020b63a0
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b63a0(int r0){
  char* p;
  int v;
  if (data_ov004_020bf9ec != 0) return;
  p = data_ov004_020beb68;
  v = p ? *(int*)(p + 0xa8) : 0;
  if (r0 <= v) v = r0;
  data_ov004_020bfa18 += v;
  data_ov004_020bfa20 = func_ov004_020b612c;
  Sound::PlayBank2_2D(0x14d);
  data_ov004_020bf9ec = 1;
}
}

// @symbol func_ov004_020b6324
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b6324(int c) {
    data_ov004_020bc7d0 = 5;
    ApproachLinear(data_ov004_020bfa18, 5, c);
    data_ov004_020bfa00 = 0;
    data_ov004_020bfa1c = c;
    data_ov004_020bfa10 = 1;
    data_ov004_020bfa04 = 0;
    data_ov004_020bfa20 = func_ov004_020b5f6c;
}
}

// @symbol func_ov004_020b6234
extern "C" void func_ov004_020b6234(void) {
    int x;
    if (data_ov004_020beb68 != 0) {
        x = *(int *)((char *)data_ov004_020beb68 + 0xa8);
    } else {
        x = 0;
    }
    if (x == 0) {
        func_02012790(0xe);
        return;
    }
    if (data_ov004_020bf9ec != 0 || data_ov004_020bfa18 >= data_ov004_020bc7d0) {
        func_02012790(0xe);
        return;
    }
    if (data_ov004_020bfa10 != 0) {
        return;
    }
    data_ov004_020bfa10 = 1;
    ApproachLinear(data_ov004_020bfa18, data_ov004_020bc7d0, 1);
    data_ov004_020bfa00 = data_ov004_020bfa18 - 1;
    Sound::PlayBank2_2D(0x14e);
    data_ov004_020bfa20 = func_ov004_020b5f6c;
}

// @symbol func_ov004_020b612c
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b612c(void)
{
    int in[2];
    int n;
    int idx;
    if (data_ov004_020bfa18 <= data_ov004_020bfa00) return;
    if (ApproachLinear(data_ov004_020bfa04, 0, 1) == 0) return;
    n = -func_ov004_020b04c0();
    idx = data_ov004_020bfa00;
    n = (n - 0x10) << 12;
    in[0] = (idx * 16 + 8) << 12;
    in[1] = n;
    func_ov004_020b5108((char*)data_ov004_020bfa34 + idx * 0x24, in);
    Sound::PlayBank2_2D(0x14d);
    {
        int b = data_ov004_020bfa00;
        if (b == data_ov004_020bfa18 - 1) {
            data_ov004_020bf9e4 = 1;
            data_ov004_020bfa20 = 0;
            return;
        }
        data_ov004_020bfa00 = b + 1;
        data_ov004_020bfa04 = 0x18;
    }
}
}

// @symbol func_ov004_020b5f6c
extern "C" void func_ov004_020b5f6c(void)
{
    int inA[2];
    int inB[2];
    if (data_ov004_020bfa18 <= data_ov004_020bfa00)
        return;
    if (data_ov004_020bfa00 < data_ov004_020bfa1c) {
        if (ApproachLinear(data_ov004_020bfa04, 0, 1) == 0)
            return;
        {
            int v1 = (-func_ov004_020b04c0() - 0x10) << 12;
            int v0 = (data_ov004_020bfa00 * 16 + 8) << 12;
            inA[0] = v0;
            inA[1] = v0 ? v1 : v1;
        }
        func_ov004_020b5108((char*)data_ov004_020bfa34 + data_ov004_020bfa00 * 0x24, inA);
        Sound::PlayBank2_2D(0x14d);
        data_ov004_020bfa04 = 0x18;
        if (data_ov004_020bfa00 == data_ov004_020bfa18 - 1) {
            data_ov004_020bfa10 = 0;
            data_ov004_020bf9e4 = 1;
            data_ov004_020bfa20 = 0;
            return;
        }
        data_ov004_020bfa00 = data_ov004_020bfa00 + 1;
        return;
    }
    {
        int v1 = (-func_ov004_020b04c0() - 0x10) << 12;
        int v0 = (data_ov004_020bfa00 * 16 + 8) << 12;
        inB[0] = v0;
        inB[1] = v0 ? v1 : v1;
        func_ov004_020b5108((char*)data_ov004_020bfa34 + data_ov004_020bfa00 * 0x24, inB);
    }
    data_ov004_020bfa10 = 0;
    if (data_ov004_020bfa00 == data_ov004_020bfa18 - 1) {
        data_ov004_020bf9e4 = 1;
        data_ov004_020bfa20 = 0;
        return;
    }
    data_ov004_020bfa00 = data_ov004_020bfa00 + 1;
}

// @symbol func_ov004_020b5ed0
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b5c18(void);

void func_ov004_020b5ed0(void) {
    data_ov004_020bf9e4 = 2;
    data_ov004_020bfa04 = 0;
    data_ov004_020bf9fc = data_ov004_020bfa18;
    if (data_ov004_020bc7d4 != 0) {
        data_ov004_020bf9e8 = -data_ov004_020bfa18;
        data_ov004_020bfa24 = 1;
    }
    data_ov004_020bf9f0 = 1;
    data_ov004_020bfa20 = func_ov004_020b5c18;
}
}

// @symbol func_ov004_020b5e40
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b5e40(int x){
  int cond = data_ov004_020bc7d4;
  data_ov004_020bf9e4 = 2;
  data_ov004_020bfa04 = 0;
  data_ov004_020bf9fc = x;
  if (cond != 0) {
    data_ov004_020bf9e8 = -x;
    data_ov004_020bfa24 = 1;
  }
  data_ov004_020bf9f0 = 1;
  data_ov004_020bfa20 = func_ov004_020b58c4;
}
}

// @symbol func_ov004_020b5dd4
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b5aac(void);
void func_ov004_020b5dd4(void){
  data_ov004_020bf9e4 = 2;
  data_ov004_020bfa04 = 0;
  data_ov004_020bf9fc = data_ov004_020bf9fc + 1;
  data_ov004_020bf9f0 = 1;
  data_ov004_020bfa20 = func_ov004_020b5aac;
}
}

// @symbol func_ov004_020b5d74
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b5d74(void) {
    data_ov004_020bf9e4 = 4;
    data_ov004_020bfa04 = 0x1e;
    data_ov004_020bf9fc = data_ov004_020bfa18;
    data_ov004_020bfa20 = func_ov004_020b5768;
}
}

// @symbol func_ov004_020b5c18
extern "C" void func_ov004_020b5c18(void)
{
    if (data_ov004_020bf9fc > 0) {
        if (ApproachLinear(data_ov004_020bfa04, 0, 1) == 0)
            return;
        func_ov004_020b506c((char*)data_ov004_020bfa34 + data_ov004_020bfa00 * 0x24);
        if (data_ov004_020bf9f0 != 0) {
            int t = data_ov004_020beb68 ? *(int*)(data_ov004_020beb68 + 0xa8) : 0;
            if (t != 0)
                Sound::PlayBank2_2D(0x14b);
            else
                Sound::PlayBank2_2D(0x14c);
            data_ov004_020bf9f0 = 0;
        }
        data_ov004_020bfa14 = data_ov004_020bfa00;
        ApproachLinear(data_ov004_020bfa00, 0, 1);
        if (ApproachLinear(data_ov004_020bf9fc, 0, 1) == 0)
            data_ov004_020bfa04 = 0x10;
        return;
    }
    if (data_ov004_020bfa56[data_ov004_020bfa14 * 0x24] != 0)
        return;
    data_ov004_020bfa04 = 0x3c;
    data_ov004_020bfa20 = func_ov004_020b5a54;
}

// @symbol func_ov004_020b5aac
extern "C" void func_ov004_020b5aac(void)
{
    if (data_ov004_020bf9fc > 0) {
        if (ApproachLinear(data_ov004_020bfa04, 0, 1) == 0)
            return;
        func_ov004_020b506c((char*)data_ov004_020bfa34 + data_ov004_020bfa00 * 0x24);
        if (data_ov004_020bf9f0 != 0) {
            int t = data_ov004_020beb68 ? *(int*)(data_ov004_020beb68 + 0xa8) : 0;
            if (t == 0 && data_ov004_020bfa00 == 0)
                Sound::PlayBank2_2D(0x14c);
            else
                Sound::PlayBank2_2D(0x14b);
            data_ov004_020bf9f0 = 0;
        }
        data_ov004_020bf9f4 = data_ov004_020bfa00;
        ApproachLinear(data_ov004_020bfa00, 0, 1);
        if (ApproachLinear(data_ov004_020bf9fc, 0, 1) == 0)
            data_ov004_020bfa04 = 0x10;
        return;
    }
    if (data_ov004_020bfa56[data_ov004_020bf9f4 * 0x24] != 0)
        return;
    data_ov004_020bfa04 = 0x3c;
    data_ov004_020bfa20 = func_ov004_020b5a54;
}

// @symbol func_ov004_020b5a54
extern "C" void func_ov004_020b5a54(void) {
    if (ApproachLinear(data_ov004_020bfa04, 0, 1) == 0)
        return;
    data_ov004_020bf9e4 = 1;
    data_ov004_020bfa20 = 0;
}

// @symbol func_ov004_020b58c4
extern "C" void func_ov004_020b58c4(void)
{
    if (data_ov004_020bf9fc > 0 && (data_ov004_020beb68 ? *(int*)(data_ov004_020beb68 + 0xa8) : 0) != 0) {
        if (ApproachLinear(data_ov004_020bfa04, 0, 1) == 0)
            return;
        if (data_ov004_020bf9f0 != 0) {
            int t = data_ov004_020beb68 ? *(int*)(data_ov004_020beb68 + 0xa8) : 0;
            if (t <= data_ov004_020bf9fc)
                Sound::PlayBank2_2D(0x14c);
            else
                Sound::PlayBank2_2D(0x14b);
            data_ov004_020bf9f0 = 0;
        }
        func_ov004_020b4e78((char*)data_ov004_020bfa34 + data_ov004_020bfa00 * 0x24);
        data_ov004_020bfa0c = data_ov004_020bfa00;
        if (ApproachLinear(data_ov004_020bfa00, 0x14, 1) != 0)
            data_ov004_020bfa00 = 0;
        if (ApproachLinear(data_ov004_020bf9fc, 0, 1) == 0)
            data_ov004_020bfa04 = 0x10;
        return;
    }
    if (data_ov004_020bfa56[data_ov004_020bfa0c * 0x24] != 0)
        return;
    data_ov004_020bfa04 = 0x3c;
    data_ov004_020bfa20 = func_ov004_020b586c;
}

// @symbol func_ov004_020b586c
extern "C" void func_ov004_020b586c(void) {
    if (ApproachLinear(data_ov004_020bfa04, 0, 1) == 0)
        return;
    data_ov004_020bf9e4 = 1;
    data_ov004_020bfa20 = 0;
}

// @symbol func_ov004_020b5768
extern "C" {
void func_ov004_020b5768() {
    if (data_ov004_020bf9fc > 0) {
        if (ApproachLinear(data_ov004_020bfa04, 0, 1) == 0)
            return;
        func_ov004_020b4cc4((char*)data_ov004_020bfa34 + data_ov004_020bfa00 * 0x24);
        data_ov004_020bfa08 = data_ov004_020bfa00;
        ApproachLinear(data_ov004_020bfa00, 0, 1);
        if (ApproachLinear(data_ov004_020bf9fc, 0, 1) == 0) {
            data_ov004_020bfa04 = 0xc;
        }
        return;
    }
    if (data_ov004_020bfa56[data_ov004_020bfa08 * 0x24] != 0)
        return;
    data_ov004_020bf9e4 = 1;
    data_ov004_020bfa20 = 0;
}
}

// @symbol func_ov004_020b56c8
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b56c8(char* p)
{
    int i;
    int cond;
    char* it = (char*)data_ov004_020bfa34;
    for (i = 0; i < 0x14; i++) {
        func_ov004_020b51e4(it);
        it += 0x24;
    }
    cond = data_ov004_020bc7d4;
    data_ov004_020bf9f8 = (int)p;
    data_ov004_020bfa04 = 0;
    data_ov004_020bf9e4 = 3;
    if (cond != 0) {
        data_ov004_020bf9e8 = (int)p;
        data_ov004_020bfa24 = 1;
    }
    data_ov004_020bfa20 = func_ov004_020b556c;
}
}

inline short load_s(short* p) { return *p; }
struct EI { char* e; int i; };

// @symbol func_ov004_020b556c
extern "C" void func_ov004_020b556c(void)
{
    int step, idx, n, limit;
    int cx, rx;
    int sp[2];
    struct EI ei;
    if (ApproachLinear(data_ov004_020bfa04, 0, 1) == 0)
        return;
    step = 8;
    n = data_ov004_020bf9f8;
    if (n > 0x14) limit = 0x14; else limit = n;
    if (n > 0x14) step >>= 1;
    idx = 0;
    if (limit > 0) {
        ei.e = (char*)data_ov004_020bfa34;
        ei.i = idx;
        do {
            int row = idx / 5;
            int col = idx % 5;
            cx = col << 0x10;
            rx = -(row << 0x10);
            {
                int ret = -func_ov004_020b04c0();
                sp[1] = (ret - 0x10) << 0xc;
            }
            sp[0] = 0x60000;
            {
                int c2 = data_ov004_020bf9f8;
                if (c2 < 5)
                    sp[0] = (0x80 - ((c2 - 1) << 3)) << 0xc;
            }
            sp[0] = sp[0] + cx;
            sp[1] = sp[1] + rx;
            func_ov004_020b4b84(ei.e, sp);
            {
                short* p = (short*)(int)(ei.e + 0x20);
                int cur = load_s(p);
                *p = cur + ei.i;
            }
            idx++;
            ei.e += 0x24;
            ei.i += step;
        } while (idx < limit);
    }
    data_ov004_020bfa04 = 0;
    data_ov004_020bfa20 = func_ov004_020b53f0;
}

// @symbol func_ov004_020b53f0
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b53f0(void)
{
    int step, i, idx, n, limit;
    char* e;
    int sp[2];

    e = (char*)data_ov004_020bfa34;
    for (i = 0; i < 0x14; i++) {
        if (*(u8*)(e + 0x22) != 0)
            return;
        e += 0x24;
    }

    n = data_ov004_020bf9f8;
    if (n > 0) {
        if (n > 0x14)
            limit = 0x14;
        else
            limit = n;
        step = 8;
        if (n > 0x14)
            step >>= 1;
        /* idx holds loop counter (r8); i holds display index (r4) */
        idx = 0;
        if (limit > 0) {
            e = (char*)data_ov004_020bfa34;
            i = idx;
            do {
                int row = idx / 5;
                int col = idx % 5;
                int cx = col << 0x10;
                int rx = -(row << 0x10);
                int ret = -func_ov004_020b04c0();
                sp[1] = (ret - 0x10) << 0xc;
                sp[0] = 0x60000;
                {
                    int c2 = data_ov004_020bf9f8;
                    if (c2 < 5) {
                        sp[0] = (0x80 - ((c2 - 1) << 3)) << 0xc;
                    }
                }
                sp[0] = sp[0] + cx;
                sp[1] = sp[1] + rx;
                func_ov004_020b4b84(e, sp);
                *(u16*)(e + 0x20) = (u16)i;
                idx++;
                e += 0x24;
                i += step;
            } while (idx < limit);
        }
        data_ov004_020bfa04 = 0;
        return;
    }
    data_ov004_020bfa04 = 0x3c;
    data_ov004_020bfa20 = func_ov004_020b5368;
}
}

// @symbol func_ov004_020b5368
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b5368(void){
  if(ApproachLinear(data_ov004_020bfa04, 0, 1)==0) return;
  if(func_ov004_020ae1a8()==2){
    char* p = data_ov004_020beb68;
    func_ov004_020adb1c(p ? *(int*)(p+0xa8) : 0);
  }
  data_ov004_020bfa04 = 0;
  data_ov004_020bf9e4 = 1;
  data_ov004_020bfa20 = 0;
}
}

// @symbol func_ov004_020b5334
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b5334(char *c) {
    func_ov004_020b51e4(c);
    *(short*)(c+0x20) = 0;
    *(struct W2*)c = *(struct W2*)data_ov004_020bc7e8;
}
}

// @symbol func_ov004_020b52fc
extern "C" void func_ov004_020b52fc(C *c) {
  (c->*(c->pmf))();
}

// @symbol func_ov004_020b52b8
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b52b8(char *c)
{
    if (*(unsigned char *)(c + 0x22) == 0)
        return;
    func_ov004_020b1de8(*(int *)(c + 8) >> 12, *(int *)(c + 0xc) >> 12, -1, -1);
}
}

// @symbol func_ov004_020b5288
extern "C" void func_ov004_020b5288(char *c)
{
    ApproachLinear(*(int*)(c + 8), *(int*)(c + 0x10), *(int*)(c + 0x18));
    ApproachLinear(*(int*)(c + 0xc), *(int*)(c + 0x14), *(int*)(c + 0x1c));
}

// @symbol func_ov004_020b51f0
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b51f0(char* c) {
  int out[2];
  ApproachLinear(*(int*)(c + 8), *(int*)(c + 0x10), *(int*)(c + 0x18));
  ApproachLinear(*(int*)(c + 0xc), *(int*)(c + 0x14), *(int*)(c + 0x1c));
  Vec2_Sub(out, (int*)(c + 0x10), (int*)(c + 8));
  if (out[0] != 0) return;
  if (out[1] != 0) return;
  func_ov004_020b1b40((void*)1);
  func_ov004_020b51e4(c);
  *(struct P2*)c = data_ov004_020bc7f0;
}
}

// @symbol func_ov004_020b51e4
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b51e4(char *p)
{
    p[34] = 0;
}
}

// @symbol func_ov004_020b5108
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b5108(char* c, int* in)
{
    int loc0[2];
    int loc2[2];
    *(unsigned char*)(c + 0x22) = 1;
    *(int*)(c + 8) = 0xc000;
    *(int*)(c + 0xc) = 0xc000;
    *(int*)(c + 0x10) = in[0];
    *(int*)(c + 0x14) = in[1];
    Vec2_Sub(loc0, (int*)(c + 0x10), (int*)(c + 8));
    func_0203d680(loc2, loc0, 0x100);
    struct P* bc = &data_ov004_020bc800;
    *(int*)(c + 0x18) = loc2[0];
    *(int*)(c + 0x1c) = loc2[1];
    {
        int v = *(int*)(c + 0x18);
        if (v < 0) v = -v;
        *(int*)(c + 0x18) = v;
    }
    {
        int v = *(int*)(c + 0x1c);
        if (v < 0) v = -v;
        *(int*)(c + 0x1c) = v;
    }
    if (*(int*)c == bc->w[0]) {
        if (*(int*)(c + 4) == bc->w[1]) goto end;
        if (*(int*)c == 0) goto end;
    }
    func_ov004_020b1b08((void*)1);
end:
    *(struct P*)c = data_ov004_020bc820;
}
}

// @symbol func_ov004_020b506c
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b506c(char *c)
{
    struct V2 a;
    struct V2 b;
    *(int*)(c+0x10) = 0x80000;
    Vec2_Sub(&a, c+0x10, c+8);
    func_0203d680(&b, &a, 0xc0);
    *(int*)(c+0x18) = b.x;
    *(int*)(c+0x1c) = b.y;
    {
        int x = *(int*)(c+0x18);
        if (x < 0) x = -x;
        *(int*)(c+0x18) = x;
    }
    {
        int y = *(int*)(c+0x1c);
        if (y < 0) y = -y;
        *(int*)(c+0x1c) = y;
    }
    *(short*)(c+0x20) = 0x14;
    Sound::PlayBank2_2D(0x14a);
    *(struct W2*)c = data_ov004_020bc7d8;
}
}

// @symbol func_ov004_020b4ff0
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b4ff0(char *c) {
    int v[2];
    ApproachLinear(*(int*)(c + 8), *(int*)(c + 0x10), *(int*)(c + 0x18));
    ApproachLinear(*(int*)(c + 0xc), *(int*)(c + 0x14), *(int*)(c + 0x1c));
    Vec2_Sub(v, (int*)(c + 0x10), (int*)(c + 8));
    if (v[0] != 0) return;
    if (v[1] == 0) *(struct M2*)c = data_ov004_020bc7f8;
}
}

// @symbol func_ov004_020b4f44
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b4f44(char* c){
  int* p = (int*)((int)c + 0xc);
  int g = data_ov004_020b9488[0];
  int n = -(((short)*(short*)(c+0x20) - (g >> 1)) << 12);
  int q;
  int v;
  n = p ? n : n;
  q = __aeabi_idiv(n, g);
  v = (int)(((long long)(q - 0x600) * 0x4000 + 0x800) >> 12);
  *p += v;
  if (ApproachLinear2(*(short*)(c+0x20), 0, 1) == 0)
    return;
  ApproachLinear(data_ov004_020bfa18, 0, 1);
  func_ov004_020b5334(c);
}
}

// @symbol func_ov004_020b4e78
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b4e78(char *c)
{
    struct V2 a;
    struct V2 b;
    func_ov004_020b1b08((void*)1);
    *(char*)(c+0x22) = 1;
    *(int*)(c+8) = 0xc000;
    *(int*)(c+0xc) = 0xc000;
    *(int*)(c+0x10) = 0x80000;
    *(int*)(c+0x14) = ((-func_ov004_020b04c0()) - 0x10) << 12;
    Vec2_Sub(&a, c+0x10, c+8);
    func_0203d680(&b, &a, 0xc0);
    *(int*)(c+0x18) = b.x;
    *(int*)(c+0x1c) = b.y;
    {
        int x = *(int*)(c+0x18);
        if (x < 0) x = -x;
        *(int*)(c+0x18) = x;
    }
    {
        int y = *(int*)(c+0x1c);
        if (y < 0) y = -y;
        *(int*)(c+0x1c) = y;
    }
    *(short*)(c+0x20) = 0x14;
    Sound::PlayBank2_2D(0x14a);
    *(struct W2*)c = data_ov004_020bc810;
}
}

// @symbol func_ov004_020b4dfc
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b4dfc(char *c) {
    int v[2];
    ApproachLinear(*(int*)(c + 8), *(int*)(c + 0x10), *(int*)(c + 0x18));
    ApproachLinear(*(int*)(c + 0xc), *(int*)(c + 0x14), *(int*)(c + 0x1c));
    Vec2_Sub(v, (int*)(c + 0x10), (int*)(c + 8));
    if (v[0] != 0) return;
    if (v[1] == 0) *(struct M2*)c = data_ov004_020bc7e0;
}
}

// @symbol func_ov004_020b4d50
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b4d50(char* c){
  int* p = (int*)(((int)c + 0xc));
  int g = data_ov004_020b9488[0];
  int n = -(((short)*(short*)(c+0x20) - (g >> 1)) << 12);
  int q = n / g;
  int v = (int)(((long long)(q - 0x600) * 0x4000 + 0x800) >> 12);
  *p = *p + v;
  if (ApproachLinear2(*(short*)(c+0x20), 0, 1) == 0)
    return;
  ApproachLinear(data_ov004_020bfa18, 0, 1);
  func_ov004_020b5334(c);
}
}

// @symbol func_ov004_020b4cc4
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b4cc4(char* r4){
  Vec2_Fix12 v1;
  Vec2_Fix12 v2;
  int a, b;
  *(int*)(r4 + 0x10) = 0xc000;
  *(int*)(r4 + 0x14) = 0xc000;
  Vec2_Sub((int*)&v1, (int*)(r4 + 0x10), (int*)(r4 + 8));
  func_0203d680(&v2, &v1, 0xc0);
  *(int*)(r4 + 0x18) = v2.x;
  *(int*)(r4 + 0x1c) = v2.y;
  a = *(int*)(r4 + 0x18);
  if (a < 0) a = -a;
  *(int*)(r4 + 0x18) = a;
  b = *(int*)(r4 + 0x1c);
  if (b < 0) b = -b;
  *(int*)(r4 + 0x1c) = b;
  *(struct P2*)r4 = data_ov004_020bc818;
}
}

// @symbol func_ov004_020b4c30
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b4c30(char* r4){
  int v[2];
  ApproachLinear(*(int*)(r4 + 8), *(int*)(r4 + 0x10), *(int*)(r4 + 0x18));
  ApproachLinear(*(int*)(r4 + 0xc), *(int*)(r4 + 0x14), *(int*)(r4 + 0x1c));
  Vec2_Sub(v, (int*)(r4 + 0x10), (int*)(r4 + 8));
  if (v[0] != 0) return;
  if (v[1] != 0) return;
  ApproachLinear(data_ov004_020bfa18, 0, 1);
  func_ov004_020b1b40((void*)1);
  func_ov004_020b5334(r4);
}
}

// @symbol func_ov004_020b4b84
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b4b84(char* c, int* in){
  V2 a;
  int pad[2];
  V2 b;
  *(int*)(c+8) = in[0];
  *(int*)(c+0xc) = in[1];
  *(short*)(c+0x20) = 0;
  *(unsigned char*)(c+0x22) = 1;
  *(int*)(c+0x10) = 0xc000;
  *(int*)(c+0x14) = 0xc000;
  Vec2_Sub(&a, (int*)(c+0x10), (int*)(c+8));
  func_0203d680(&b, &a, 0x100);
  *(int*)(c+0x18) = b.x;
  *(int*)(c+0x1c) = b.y;
  {
    int x = *(int*)(c+0x18);
    if (x < 0) x = -x;
    *(int*)(c+0x18) = x;
  }
  {
    int y = *(int*)(c+0x1c);
    if (y < 0) y = -y;
    *(int*)(c+0x1c) = y;
  }
  *(P*)c = *(P*)data_ov004_020bc808;
}
}

// @symbol func_ov004_020b4aa4
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov004_020b4aa4(char* c) {
    struct Pair t;
    if (ApproachLinear2(*(short*)(c + 0x20), 0, 1) == 0) return;
    ApproachLinear(*(int*)(c + 8), *(int*)(c + 0x10), *(int*)(c + 0x18));
    ApproachLinear(*(int*)(c + 0xc), *(int*)(c + 0x14), *(int*)(c + 0x1c));
    Vec2_Sub(&t, (int*)(c + 0x10), (int*)(c + 8));
    if (t.a != 0) return;
    if (t.b != 0) return;
    if (ApproachLinear2(*(short*)(c + 0x20), 0, 1) == 0) return;
    Sound::PlayBank2_2D(0x149);
    func_ov004_020b1b40((void*)1);
    ApproachLinear(data_ov004_020bf9f8, 0, 1);
    func_ov004_020b5334(c);
}
}
