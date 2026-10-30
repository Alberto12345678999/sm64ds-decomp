extern void __register_global_object();
extern int data_020a0ec8[];
extern int NullDestructor_0203d47c[];
extern int data_020a0ed0[];
void __sinit_020750ec(void)
{
    data_020a0ec8[0] = 0;
    data_020a0ec8[1] = 0;
    __register_global_object(data_020a0ec8, NullDestructor_0203d47c, data_020a0ed0);
}
