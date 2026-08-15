//cpp
#include "ActorBase.h"
#include "Heap.h"
/* ActorBase::AfterCleanupResources(u32 vfSuccess) at 0x02043b2c -- vtable
 * slot 5. Only runs when vfSuccess == VS_SUCCESS (2); otherwise returns
 * immediately. Tears down the two processing-list registrations, releases
 * the private heap at 0x4c and the still-unnamed resource at 0x48 if
 * either is held, then destructs (virtual call, ~ActorBase) and frees the
 * object itself from the shared actor heap -- not from its own `heap`.
 *
 * NOTE: compiled as C++ (the virtual-call codegen `mov r0,r4; ldr r1,[r0]`
 * only reproduces from a real C++ virtual dispatch; a function-pointer-
 * through-a-data-field reads the vtable from r4 directly and swaps those
 * two words).
 */
extern "C" {
  char gGlobalA;                 /* 0x020a4b6c */
  char gGlobalB;                 /* 0x020a4ba8 */
  void func_0203b3c0(void*, void*);
  void func_0203b27c(void*, void*);
  void func_02044334(void*);
  void _ZN6Memory10DeallocateEPvP4Heap(void*, void*);
  void *data_020a0eac;
}

void ActorBase::AfterCleanupResources(u32 vfSuccess)
{
    if (vfSuccess != 2) return;
    func_0203b3c0(&gGlobalA, &sceneNode);
    func_0203b27c(&gGlobalB, &behavNode);
    if (heap) ((Heap *)heap)->_Destroy();
    if (unk_048) func_02044334(unk_048);
    this->~ActorBase();
    _ZN6Memory10DeallocateEPvP4Heap(this, data_020a0eac);
}
