//cpp
/* src/IRQ.cpp — IRQ TU (arm9 0x02056c40..0x02057000)
 *
 * The eighteen complete entries from Tim3OverflowHandler through SetIRQHandler,
 * one contiguous .text run. mwccarm emits .text in reverse source order under
 * default deferred codegen, so the file is descending: SetIRQHandler first,
 * Tim3OverflowHandler last. The name is the class already declared in
 * include/IRQ.h.
 *
 * data_020a60c4 is one 12-byte slot table. SetIRQHandler/GetIRQHandler, the
 * DMA helper, and DmaTimHandler each name its fields differently; the
 * anonymous unions are that one layout, not a second object.
 */
#include "IRQ.h"

#define IME (*(volatile u16*)0x4000208)
#define IE  (*(volatile u32*)0x4000210)
#define IF  (*(volatile u32*)0x4000214)

struct IRQTableSlot {
    union {
        IRQ::Handler handler;
        void (*fn)(void *);
    };
    union {
        u32 enabled;
        u32 active;
        u32 flag;
    };
    union {
        u32 argument;
        void *arg;
    };
};

extern "C" {
extern IRQ::Handler data_02099fe4[];
extern IRQTableSlot data_020a60c4[];
}

namespace IRQ {

// @symbol _ZN3IRQ13SetIRQHandlerEjPFvvE
void SetIRQHandler(u32 mask, Handler handler)
{
    for (int i = 0; i < 0x16; i++) {
        if (mask & 1) {
            IRQTableSlot* entry = 0;
            if (i >= 8 && i <= 0xb)
                entry = &data_020a60c4[i - 8];
            else if (i >= 3 && i <= 6)
                entry = &data_020a60c4[i + 1];
            else
                data_02099fe4[i] = handler;

            if (entry) {
                entry->handler = handler;
                entry->argument = 0;
                entry->enabled = 1;
            }
        }
        mask >>= 1;
    }
}

// @symbol _ZN3IRQ13GetIRQHandlerEj
Handler GetIRQHandler(u32 mask)
{
 int i=0;
 Handler* p=data_02099fe4;
 for(;i<0x16;i++){
   if(mask&1){
     if(i>=8 && i<=0xb) return data_020a60c4[i-8].handler;
     if(i>=3 && i<=6) return data_020a60c4[i+1].handler;
     return *p;
   }
   mask>>=1; p++;
 }
 return 0;
}

}

extern "C" {
// @symbol func_02056e98
void func_02056e98(u32 idx, u32 handler, u32 arg)
{
    u32 mask = 1u << (idx + 8);
    data_020a60c4[idx].handler = (IRQ::Handler)handler;
    data_020a60c4[idx].arg = (void *)arg;
    u32 prev_ie = IRQ::EnableIRQs(mask);
    data_020a60c4[idx].active = prev_ie & (1u << (idx + 8));
}
}

extern "C" {
struct TimerIRQEntry {
    u32 handler;    /* +0 */
    u32 active;     /* +4 */
    u32 arg;        /* +8 */
};

extern struct TimerIRQEntry data_020a60f4[];

// @symbol func_02056e4c
void func_02056e4c(u32 idx, u32 handler, u32 arg)
{
    data_020a60f4[idx].handler = handler;
    data_020a60f4[idx].arg = arg;
    IRQ::EnableIRQs(1u << (idx + 3));
    data_020a60f4[idx].active = 1;
}
}

namespace IRQ {

// @symbol _ZN3IRQ7SetIRQsEj
u32 SetIRQs(u32 mask)
{u16 ime=IME;IME=0;u32 old=IE;IE=mask;(void)IME;IME=ime;return old;}

// @symbol _ZN3IRQ10EnableIRQsEj
u32 EnableIRQs(u32 mask)
{u16 ime=IME;IME=0;u32 old=IE;IE=old|mask;(void)IME;IME=ime;return old;}

// @symbol _ZN3IRQ11DisableIRQsEj
u32 DisableIRQs(u32 mask)
{u16 s=IME;IME=0;u32 o=IE;IE=o&~mask;(void)IME;IME=s;return o;}

// @symbol _ZN3IRQ15ClearInterruptsEj
u32 ClearInterrupts(u32 mask)
{u16 ime=IME;IME=0;u32 old=IF;IF=mask;(void)IME;IME=ime;return old;}

// @symbol _ZN3IRQ12EmptyHandlerEv
void EmptyHandler(void)
{
}

}

extern "C" {
extern u16 data_02099fd4[];
extern short data_023c0000[];
}

inline void (*inline_fn(IRQTableSlot *arg0, u32 arg1))(void *)
{
  return arg0[arg1].fn;
}

namespace IRQ {

// @symbol _ZN3IRQ13DmaTimHandlerEj
void DmaTimHandler(u32 idx)
{
  u16 bit = data_02099fd4[idx];
  u32 mask = 1u << bit;
  void (*fn)(void *) = inline_fn(data_020a60c4, idx);
  data_020a60c4[idx].fn = 0;
  if (0 != fn)
  {
    fn(data_020a60c4[idx].arg);
  }
  *(volatile u32 *)(((int)data_023c0000 + 0x3ff8)) |= mask;
  if (data_020a60c4[idx].flag != 0)
  {
    return;
  }
  IRQ::DisableIRQs(mask);
}

// @symbol _ZN3IRQ11Dma0HandlerEv
void Dma0Handler()
{
    DmaTimHandler(0);
}

// @symbol _ZN3IRQ11Dma1HandlerEv
void Dma1Handler()
{
    DmaTimHandler(1);
}

// @symbol _ZN3IRQ11Dma2HandlerEv
void Dma2Handler()
{
    DmaTimHandler(2);
}

// @symbol _ZN3IRQ11Dma3HandlerEv
void Dma3Handler()
{
    DmaTimHandler(3);
}

// @symbol _ZN3IRQ19Tim0OverflowHandlerEv
void Tim0OverflowHandler()
{
    DmaTimHandler(4);
}

// @symbol _ZN3IRQ19Tim1OverflowHandlerEv
void Tim1OverflowHandler()
{
    DmaTimHandler(5);
}

// @symbol _ZN3IRQ19Tim2OverflowHandlerEv
void Tim2OverflowHandler()
{
    DmaTimHandler(6);
}

// @symbol _ZN3IRQ19Tim3OverflowHandlerEv
void Tim3OverflowHandler()
{
    DmaTimHandler(7);
}

}
