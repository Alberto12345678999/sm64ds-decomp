extern void __register_global_object(void *, void *, void *);
extern void *_ZN7Vector3D1Ev(void *object);
extern int data_020a0ebc[];
extern int data_020a0eb0[];

/* Static initializer for the zero Vector3 data_020a0ebc, registered with
   Vector3's destructor. Actors (d_a_door.cpp and others) pass it as a zero
   vector. The owner is one of the unpromoted math runs around
   0x0203adbc..0x0203d47c (notes/mwccarm-codegen.md 6dg and 6df). */
void __sinit_020750b8(void)
{
    data_020a0ebc[0] = 0;
    data_020a0ebc[1] = 0;
    data_020a0ebc[2] = 0;
    __register_global_object(data_020a0ebc, (void *)&_ZN7Vector3D1Ev, data_020a0eb0);
}
