extern int func_ov007_020bf630(int* self, int* p1, int p2, int p3, int arg5);
extern int _ZN4cstd3modEii(int, int);
extern int _ZN4cstd3divEii(int, int);
extern void func_ov007_020ca578(int* a, int b, int c, int d);
extern int *data_ov007_02104bd4;
extern int *data_ov007_0210342c;

/* Reconstructed layouts, not recovered class identity; names as in
 * func_ov007_020ca5f0 and func_ov007_020ca308, only the slots this
 * file reads. */
typedef struct Ov007Grid {
    int columns; /* 0x00 */
} Ov007Grid;

/* data_ov007_02104bd4[0], the 0x38-byte grid mesh func_ov007_020cbbb0 builds. */
typedef struct Ov007Mesh {
    char pad_00[4];
    Ov007Grid *grid; /* 0x04: func_ov007_020c73f0 */
} Ov007Mesh;

/* data_ov007_02104bd4[3], the 0x1c-byte wave record func_ov007_020ca2a8 builds. */
typedef struct Ov007MeshWave {
    int frame; /* 0x00 */
    int delay; /* 0x04: no wave runs until it counts down to 0 */
} Ov007MeshWave;

/* data_ov007_0210342c: the overlay's manager; names as in
 * func_ov007_020c023c, only the slot this file reads. */
typedef struct Ov007Work {
    char pad_00[0x30];
    int *cameras[2]; /* 0x30: func_ov007_020bfe4c's Ov007Camera */
} Ov007Work;

/* Pokes the mesh at screen point (arg0, arg1): func_ov007_020bf630 picks the
 * grid point under it through the camera, func_ov007_020ca578 pushes that
 * point with strength arg2, and the waves hold off for 0x78 ticks. */
void func_ov007_020bed60(int arg0, int arg1, int arg2)
{
    Ov007Mesh *self = (Ov007Mesh *)*data_ov007_02104bd4;
    int *p1 = ((Ov007Work *)data_ov007_0210342c)->cameras[0];
    int res = func_ov007_020bf630((int *)self, p1, arg0, arg1, -1);
    if (res == -1) return;
    {
        int m = _ZN4cstd3modEii(res, self->grid->columns);
        int d = _ZN4cstd3divEii(res, self->grid->columns);
        func_ov007_020ca578((int *)self, m, d, arg2);
    }
    {
        Ov007MeshWave *p = (Ov007MeshWave *)data_ov007_02104bd4[3];
        p->delay = 0x78;
    }
}
