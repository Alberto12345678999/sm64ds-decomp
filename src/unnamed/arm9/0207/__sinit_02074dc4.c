#include "Timer.h"

extern int data_0209d4b8;
extern int data_0209d4bc;
extern struct Timer data_0209d4c8;
extern void func_0201973c(void);

extern void func_0203b9b4(int *p, int v);
extern void func_020731dc(void *object, void *destructor, void **node);
extern struct Timer *func_0201964c(struct Timer *timer);

/* Static initializer for two objects: the random state data_0209d4b8
   (seeded with 1 by func_0203b9b4, registered with the empty destructor
   func_0201973c) and the Timer data_0209d4c8 (func_0201964c). Its owner is
   the unpromoted shard run beside Timer.cpp, so it cannot fold yet
   (notes/mwccarm-codegen.md 6dg, "Not done"). */
void __sinit_02074dc4(void)
{
    func_0203b9b4(&data_0209d4b8, 1);
    func_020731dc(&data_0209d4b8, (void *)&func_0201973c, (void**)&data_0209d4bc);
    func_0201964c(&data_0209d4c8);
}
