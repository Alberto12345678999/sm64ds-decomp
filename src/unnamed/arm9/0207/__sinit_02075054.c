extern void __register_global_object(short *a, void *b, void *node);
extern short data_020a0dbc[];
extern short data_020a0db8[];
extern char NoOpDestructor[];
extern char data_020a0dc0[];
extern char data_020a0dcc[];

/* Static initializer for two constant two-short vectors: data_020a0dbc =
   (0, 0), which the trampoline minigames read as their touch origin, and
   data_020a0db8 = (1, 1). Both register NoOpDestructor. The owner is one
   of the unpromoted math runs around 0x0203adbc..0x0203d47c, so it cannot
   fold yet (notes/mwccarm-codegen.md 6dg, "Not done"). */
void __sinit_02075054(void)
{
    data_020a0dbc[0] = 0;
    data_020a0dbc[1] = 0;
    __register_global_object(data_020a0dbc, NoOpDestructor, data_020a0dc0);
    data_020a0db8[0] = 1;
    data_020a0db8[1] = 1;
    __register_global_object(data_020a0db8, NoOpDestructor, data_020a0dcc);
}
