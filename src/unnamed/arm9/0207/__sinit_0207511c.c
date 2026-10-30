extern void __register_global_object();
extern short data_020a0edc[];
extern int _ZN8Vector3sD1Ev[];
extern int data_020a0ee4[];
/* Static initializer for the zero Vector3s data_020a0edc, registered with
   Vector3s's destructor. d_a_obj_hatena_block.cpp copies its rotation
   from it. The owner is one of the unpromoted math runs around
   0x0203adbc..0x0203d47c (notes/mwccarm-codegen.md 6dg, "Not done"). */
void __sinit_0207511c(void)
{
    data_020a0edc[0] = 0;
    data_020a0edc[1] = 0;
    data_020a0edc[2] = 0;
    __register_global_object(data_020a0edc, _ZN8Vector3sD1Ev, data_020a0ee4);
}
