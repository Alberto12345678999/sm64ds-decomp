//cpp
/* IRQ2 -- func_0201a4e4 and IRQ::VBlankHandler.
 *
 * Not part of an earlier IRQ translation unit: func_0201a4d0 ends where this
 * run begins, and func_0201a5cc begins where it ends. The name is the tree
 * class IRQ plus the numeric suffix (Juan 2026-10-11).
 *
 * Default deferred codegen emits .text in reverse source order, so the
 * higher address (VBlankHandler) is first. Do not reorder.
 *
 * data_0209d4fc and data_0209d500 are halfwords in func_0201a4e4. The handler
 * only takes their addresses and passes them to OS_WakeupThread, which is
 * declared to take int *. The casts keep that call; a word type here turns
 * the helper's stores into str.
 */

#include "types.h"

extern "C" {
extern int data_0209d514;
extern int data_0208ee44;
extern u8 data_0209d4f0;
extern u16 data_0209d500;
extern u16 data_0209d4fc;
extern char data_023c0000[];
extern void OS_WakeupThread(int *p);
extern void func_02019144(void);
extern void func_02019100(void);
extern void _ZN3IRQ13SetIRQHandlerEjPFvvE(u32 irqBit, void (*handler)(void));
extern void _ZN3IRQ13VBlankHandlerEv(void);
extern u8 data_0209d4dc;
}

// 0x0201a534 (0x98)
// @symbol _ZN3IRQ13VBlankHandlerEv
namespace IRQ {

void VBlankHandler(void)
{
  int *new_var;
  data_0209d514 = data_0209d514 + 1;
  if ((data_0209d514 >= data_0208ee44) && (data_0209d4f0 != 0))
  {
    OS_WakeupThread((int *)&data_0209d500);
    data_0209d514 = 0;
    func_02019144();
  }
  new_var = (int *)&data_0209d4fc;
  OS_WakeupThread(new_var);
  *(int *)(((int)data_023c0000 + 0x3ff8)) |= 1;
  func_02019100();
}

}

// 0x0201a4e4 (0x50)
// @symbol func_0201a4e4
extern "C" void func_0201a4e4(void)
{
    data_0209d4fc = 0;
    data_0209d500 = 0;
    _ZN3IRQ13SetIRQHandlerEjPFvvE(1, _ZN3IRQ13VBlankHandlerEv);
    data_0209d4dc = 1;
}
