extern int data_0209e650;
extern int data_0209e654;
extern void func_0201973c(void);

extern void func_0203b9b4(int *p, int v);
extern void func_020731dc(void *object, void *destructor, void **node);

/* Static initializer for the random state data_0209e650: seed it with 1
   (func_0203b9b4) and register the empty destructor func_0201973c.
   d_a_bakubaku.cpp draws from it, and d_s_stage_methods.cpp reseeds it.
   Its owner is the unpromoted 0x0201fec8..0x02020820 run, next to
   data_0209e64c, so it cannot fold yet (notes/mwccarm-codegen.md 6dg). */
void __sinit_02074e44(void) {
    func_0203b9b4(&data_0209e650, 1);
    func_020731dc(&data_0209e650, (void *)&func_0201973c, (void **)&data_0209e654);
}
