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

struct E { char _0[8]; int f8; int fc; char _10[8]; };
struct Cell { int f0, f4, f8, fc, f10, f14; };
struct Elem { char pad[8]; int f8; int fc; char pad2[0xc]; };

/* Render's slot record has the member at +0x10. Behavior's is at +0x8.
 * InitResources calls through an incomplete class, the way its own file did. */
struct RenderView;
typedef int (RenderView::*RenderPMF)();
struct RenderEntry { char pad[0x10]; RenderPMF pmf; };
struct RenderView { char pad[0x1a4]; RenderEntry *ep; };

struct BehaviorView;
typedef int (BehaviorView::*BehaviorPMF)();
struct BehaviorEntry { char pad[0x8]; BehaviorPMF pmf; };
struct BehaviorView { char pad[0x1a4]; BehaviorEntry *ep; };

struct InitActor;
typedef void (InitActor::*InitPMF)();
struct Disp {
    InitPMF pmf;
    int pad[4];
};

/* Flat view. mPosX is dActor_c's field at 0x5c. */
struct PicGateFields {
    u8 pad_000[0x5c];
    s32 mPosX;
    u8 pad_060[0x148];
    s32 unk_1a8;
    u8 pad_1ac[4];
    s32 unk_1b0;
    u8 pad_1b4[4];
    u16 unk_1b8;
    u8 unk_1ba;
    u8 unk_1bb;
};

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
extern void _ZN8dActor_c9SetRangesE5Fix12IiES1_S1_S1_(void *self, int a, int b, int c, int d);
}
extern Disp data_ov080_02128628[];
int ApproachLinear(int &ref, int target, int step);

// @symbol func_ov080_021264ec
extern "C" {
void func_ov080_021264ec(char *c)
{
    if ((unsigned char)((*(unsigned int*)(c + 8) >> 8) & 0x1f) == 7 &&
        !(data_0209caa0[2] & 0x40000) &&
        IsStarCollectedInLevel(0x12, 1)) {
        if (ApproachLinear(*(int*)(c + 0x5c), *(int*)(c + 0x1b0) + 0x802000, 0x13e72))
            data_0209caa0[2] |= 0x40000;
        func_ov080_0212555c(c);
    }
    func_ov080_021256f8(c);
    int i;
    for (i = 0; i < *(unsigned short*)(c + 0x1b8); i++) {
        struct E *e = (struct E *)(*(char**)(c + 0x1a0) + i * 0x18);
        e->f8 = func_ov080_02125bb0(c, e->fc);
    }
    func_ov080_02125940(c);
    func_ov080_02125af0(c);
    *(unsigned short*)(c + 0x1b4) = (unsigned short)(*(short*)(c + 0x1b4) + (*(int**)(c + 0x1ac))[1]);
}
}

// @symbol func_ov080_021265ec
extern "C" {
void func_ov080_021265ec(char* c){
    int sb=0, r8=0, r7=0, r4=0;
    int n=*(u8*)(c+0x1bb);
    if(n > 0){
        int fp=0x1ff00000;
        do {
            int r6=0;
            int m=*(u8*)(c+0x1ba);
            if(m > 0){
                do {
                    struct Cell* g=(struct Cell*)(*(char**)(c+0x1a0) + (r7*(*(u8*)(c+0x1bb))+r6)*0x18);
                    int r5;
                    g->f0=sb; g->f4=r8; g->f8=r4; g->f10=fp;
                    r5=*(u8*)(c+0x1ba);
                    if(r6==r5-2) sb=((u8)(*(u32*)(c+8)&0xf)+1)*0x64000;
                    else sb += ((u8)(*(u32*)(c+8)&0xf)+1)*0x64000/(r5-1);
                    r6++;
                } while(r6 < *(u8*)(c+0x1ba));
            }
            {
                int r5=*(u8*)(c+0x1bb);
                sb=0;
                if(r7==r5-2) r8=((u8)((*(u32*)(c+8)>>4)&0xf)+1)*0x64000;
                else r8 += ((u8)((*(u32*)(c+8)>>4)&0xf)+1)*0x64000/(r5-1);
                r7++;
                if(r7 >= r5) break;
            }
        } while(1);
    }
    func_ov080_02126124(c);
    {
        int a2=((u8)(*(u32*)(c+8)&0xf)+1)*0x64000;
        int a1=((u8)((*(u32*)(c+8)>>4)&0xf)+1)*0x64000;
        func_ov080_02125de0(c, a2/2, a1/2, 0);
    }
}
}

// @symbol func_ov080_0212677c
extern "C" {
void func_ov080_0212677c(char *self)
{
    int tmp[12];
    int i, j, n;
    int z = 0;

    if (*(u16 *)((self + 0x100) + 0xb6) == 0) {
        func_ov080_02125fd0(self);
        return;
    }

    *(int *)0x4000444 = z;
    MulMat4x3Mat4x3((const int *)(self + 0xd4), (const int *)&data_0209b3ec, tmp);
    *(int *)0x4000440 = 2;
    func_020553a4(tmp);
    *(int *)0x4000440 = 1;
    func_020553a4(tmp);

    *(int *)0x40004c8 = 0xe0000000;
    *(int *)0x40004cc = 0xc0007fff;
    func_ov080_02125460(self);

    *(int *)0x400046c = 0x20000;
    *(int *)0x400046c = 0x20000;
    *(int *)0x400046c = 0x20000;

    n = (int)*(u8 *)(self + 0x1ba);
    i = z; /* mov before sub: use z then sub n */
    n = n - 1;
    if (n > 0) {
        do {
            *(int *)0x4000500 = 2;
            j = z;
            if ((int)*(u8 *)(self + 0x1bb) > 0) {
                do {
                    char *base = *(char **)(self + 0x1a0);
                    int cols = (int)*(u8 *)(self + 0x1bb);
                    char *v1 = base + (i + j * cols) * 0x18;
                    char *v2 = base + ((i + 1) + j * cols) * 0x18;
                    int v0, v1y, v2z;
                    s16 s0, s1, s2;

                    *(int *)0x4000488 = *(int *)(v1 + 0x14);
                    *(int *)0x4000484 = *(int *)(v1 + 0x10);
                    v0 = *(int *)(v1 + 0);
                    v1y = *(int *)(v1 + 4);
                    v2z = *(int *)(v1 + 8);
                    s0 = (s16)(v0 >> 8);
                    s1 = (s16)(v1y >> 8);
                    s2 = (s16)(v2z >> 8);
                    *(int *)0x400048c = (u16)s0 | ((u16)s1 << 16);
                    *(int *)0x400048c = (u16)s2;

                    *(int *)0x4000488 = *(int *)(v2 + 0x14);
                    *(int *)0x4000484 = *(int *)(v2 + 0x10);
                    v0 = *(int *)(v2 + 0);
                    v1y = *(int *)(v2 + 4);
                    v2z = *(int *)(v2 + 8);
                    s0 = (s16)(v0 >> 8);
                    s1 = (s16)(v1y >> 8);
                    s2 = (s16)(v2z >> 8);
                    *(int *)0x400048c = (u16)s0 | ((u16)s1 << 16);
                    *(int *)0x400048c = (u16)s2;

                    j++;
                } while (j < (int)*(u8 *)(self + 0x1bb));
            }
            *(int *)0x4000504 = z;
            i++;
        } while (i < (int)*(u8 *)(self + 0x1ba) - 1);
    }
    *(int *)0x4000448 = 1;
}
}

// @symbol func_ov080_021269b8
extern "C" {
void func_ov080_021269b8(char* c)
{
    int i;
    short n;
    struct Elem* arr;

    func_ov080_021256f8(c);
    if (DecIfAbove0_Short((unsigned short*)(c + 0x1b6)) == 0) return;

    for (i = 0; i < *(unsigned short*)(c + 0x1b8); i++) {
        arr = (struct Elem*)(*(int*)(c + 0x1a0) + i * 0x18);
        arr->f8 = func_ov080_02125bb0(c, arr->fc);
    }

    func_ov080_02125940(c);
    func_ov080_02125af0(c);

    n = *(short*)(c + 0x1b4);
    *(short*)(c + 0x1b4) = n + *(int*)(*(int*)(c + 0x1ac) + 4);
}
}

// @symbol func_ov080_02126a54
extern "C" {
void func_ov080_02126a54(char *sl)
{
  int sb;
  int fp;
  int j;
  int nb;
  int i;
  sb = 0;
  fp = 0;
  j = 0;
  if (((int) (*((u8 *) (sl + 0x1bb)))) > 0)
  {
    do
    {
      i = 0;
      if (((int) (*((u8 *) (sl + 0x1ba)))) > 0)
      {
        do
        {
          char *r6 = (*((char **) (sl + 0x1a0))) + (((j * ((int) (*((u8 *) (sl + 0x1bb))))) + i) * 0x18);
          *((int *) (r6 + 0)) = sb;
          *((int *) (r6 + 4)) = (unsigned long) fp;
          *((int *) (r6 + 8)) = 0;
          *((int *) (r6 + 0x10)) = 0x1ff00000;
          int qa = __aeabi_idiv(0x80000, ((int) (*((u8 *) (sl + 0x1ba)))) - 1);
          int qb = __aeabi_idiv(0x80000, ((int) (*((u8 *) (sl + 0x1bb)))) - 1);
          int va = qa * i;
          int vb = 0x80000 - (qb * j);
          *((int *) (r6 + 0x14)) = ((u16) ((s16) (va >> 8))) | ((((u16) ((s16) (vb >> 8))) << 1) << 15);
          nb = (int) (*((u8 *) (sl + 0x1ba)));
          if (i == (nb - 2))
          {
            sb = (((u8) ((*((int *) (sl + 8))) & 0xf)) * 0x64000) + 0x64000;
          }
          else
          {
            sb += __aeabi_idiv((((u8) ((*((int *) (sl + 8))) & 0xf)) * 0x64000) + 0x64000, nb - 1);
          }
          i++;
        }
        while (i < nb);
      }
      nb = (int) (*((u8 *) (sl + 0x1bb)));
      sb = 0;
      if (j == (nb - 2))
      {
        fp = (((u8) ((((*((int *) (sl + 8))) & 0xFFFFFFFF) >> 4) & 0xf)) * 0x64000) + 0x64000;
      }
      else
      {
        fp += __aeabi_idiv((((u8) ((((*((int *) (sl + 8))) & 0xFFFFFFFFu) >> 4) & 0xf)) * 0x64000) + 0x64000, nb - 1);
      }
      j++;
    }
    while (j < nb);
  }
  func_ov080_02126124((u32 *) sl);
}
}

// @symbol _ZN11daPicGate_c16CleanupResourcesEv
s32 daPicGate_c::CleanupResources() {
    void * c = (void *)this;
    func_0203cbc0(*(void **)((char *)c + 0x1a0));
    return 1;
}

// @symbol _ZN11daPicGate_c16OnPendingDestroyEv
void daPicGate_c::OnPendingDestroy() {
}

// @symbol _ZN11daPicGate_c6RenderEv
s32 daPicGate_c::Render() {
    RenderView * c = (RenderView *)this;
  (c->*c->ep->pmf)();
  return 1;
}

// @symbol _ZN11daPicGate_c8BehaviorEv
s32 daPicGate_c::Behavior() {
    BehaviorView * c = (BehaviorView *)this;
  (c->*c->ep->pmf)();
  return 1;
}

// @symbol _ZN11daPicGate_c13InitResourcesEv
s32 daPicGate_c::InitResources() {
    char* c = (char*)this;
    struct PicGateFields *self = (struct PicGateFields *)(void *)c;
    unsigned int m = (unsigned char)((*(unsigned int*)(c + 8) >> 0xd) & 3);

    if (m >= 2) {
        self->unk_1bb = 2;
        self->unk_1ba = self->unk_1bb;
        self->unk_1b8 = (u16)(self->unk_1ba * self->unk_1bb);
    } else {
        unsigned int idx = (unsigned char)(*(unsigned int*)(c + 8) & 0xf) + 1;
        switch (idx) {
        case 0:
        case 1:
        case 2:
            break;
        case 3:
            self->unk_1bb = data_ov080_02127714[0];
            self->unk_1ba = self->unk_1bb;
            break;
        case 4:
            self->unk_1bb = data_ov080_02127714[1];
            self->unk_1ba = self->unk_1bb;
            break;
        case 5:
            self->unk_1bb = data_ov080_02127714[2];
            self->unk_1ba = self->unk_1bb;
            break;
        case 6:
            self->unk_1bb = data_ov080_02127714[3];
            self->unk_1ba = self->unk_1bb;
            break;
        case 7:
            self->unk_1bb = data_ov080_02127714[4];
            self->unk_1ba = self->unk_1bb;
            break;
        case 8:
            self->unk_1bb = data_ov080_02127714[5];
            self->unk_1ba = self->unk_1bb;
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
            self->unk_1bb = data_ov080_02127714[6];
            self->unk_1ba = self->unk_1bb;
            break;
        }
        self->unk_1b8 = (u16)(self->unk_1ba * self->unk_1bb);
    }

    *(void**)(c + 0x1a0) = _ZN6Memory13operator_new2Ej((unsigned)(self->unk_1b8) * 0x18u);
    self->unk_1a8 = func_ov080_02125630(c, (int)((unsigned char)((*(unsigned int*)(c + 8) >> 8) & 0x1f)));
    *(void**)(c + 0x1ac) = &data_ov080_02127834;
    {
        unsigned int mi = (unsigned char)((*(unsigned int*)(c + 8) >> 0xd) & 3);
        *(Disp**)(c + 0x1a4) = &data_ov080_02128628[mi];
    }
    {
        Disp* d = *(Disp**)(c + 0x1a4);
        InitActor* o = (InitActor*)c;
        (o->*(d->pmf))();
    }

    {
        unsigned int f = *(unsigned int*)(c + 8);
        int lo = (int)((unsigned char)(f & 0xf) + 1);
        int hi = (int)((unsigned char)((f >> 4) & 0xf) + 1);
        int a = lo * 0x64000;
        int b = hi * 0x64000;
        _ZN8dActor_c9SetRangesE5Fix12IiES1_S1_S1_(c, b / 2, (a / 2) + 0xc8000, 0x1964000, 0x1964000);
    }
    {
        unsigned int f = *(unsigned int*)(c + 8);
        if ((unsigned char)((f >> 8) & 0x1f) == 4) {
            if ((unsigned char)((f >> 0xd) & 3) == 1) {
                int* pb0 = (int*)(((int)c + 0xb0));
                *pb0 = *pb0 & ~3;
            }
        }
    }
    {
        unsigned int f = *(unsigned int*)(c + 8);
        if ((unsigned char)((f >> 8) & 0x1f) == 7) {
            if ((unsigned char)((f >> 0xd) & 3) == 1) {
                self->unk_1b0 = self->mPosX;
                if (data_0209caa0[2] & 0x40000) {
                    int* p = (int*)(((int)c + 0x5c));
                    *p = *p + 0x802000;
                }
            }
        }
    }
    func_ov080_0212555c(c);
    return 1;
}

