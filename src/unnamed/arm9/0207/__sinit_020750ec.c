extern void func_020731dc();
extern int data_020a0ec8[];
extern int NullDestructor_0203d47c[];
extern int data_020a0ed0[];
/* Static initializer for the zero two-word vector data_020a0ec8,
   registered with NullDestructor_0203d47c. The owner is one of the
   unpromoted math runs around 0x0203adbc..0x0203d47c, so it cannot fold
   yet (notes/mwccarm-codegen.md 6dg, "Not done"). */
void __sinit_020750ec(void)
{
    data_020a0ec8[0] = 0;
    data_020a0ec8[1] = 0;
    func_020731dc(data_020a0ec8, NullDestructor_0203d47c, data_020a0ed0);
}
