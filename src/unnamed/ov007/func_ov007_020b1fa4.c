#include "types.h"
extern int func_ov007_020c0128(void* c);
extern int _ZN4cstd3divEii(int a, int b);
extern void func_ov007_020bffb8(void* c);
extern void _ZN3G3i7LookAt_EPK7Vector3S2_S2_bP9Matrix4x3(void *camPos, void *camUp, void *target,
                                                         int mult, void *m);
extern void func_ov007_020c0078(void* c);
extern char* data_ov007_0210342c;

/* The 0xd8-byte camera func_ov007_020c023c builds; names as in
 * func_ov007_020c0128, only the slots this file touches. */
typedef struct Ov007Camera {
    char pad_00[8];
    Vector3 eye;    /* 0x08 */
    Vector3 target; /* 0x14 */
    Vector3 up;     /* 0x20 */
    int distance;   /* 0x2c */
    char pad_30[0x14];
    int viewMatrix[12]; /* 0x44: Matrix4x3 */
    char pad_74[0x60];
    short fovy; /* 0xd4 */
} Ov007Camera;

/* data_ov007_0210342c: the overlay's manager; names as in
 * func_ov007_020b1718, only the slots this file touches. +0xec (0 or 1;
 * picks the preset-1 framing here and the sounds in func_ov007_020b10dc and
 * func_ov007_020b1718) stays raw: no role to name. */
typedef struct Ov007Work {
    char pad_00[0x24];
    /* 0x24, medium confidence: the preset this function last applied; no
     * reader found */
    int cameraPreset;
    char pad_28[8];
    Ov007Camera *cameras[2]; /* 0x30: func_ov007_020c023c */
} Ov007Work;

#define WORK ((Ov007Work *)data_ov007_0210342c)

/* preset: 1 (func_ov007_020b10dc), 4 (func_ov007_020b0a20), 2 and 3. */
void func_ov007_020b1fa4(int preset) {
    Ov007Camera *cam = WORK->cameras[0];
    func_ov007_020c0128(cam);
    switch (preset) {
    case 1:
        switch (*(int*)((char*)data_ov007_0210342c + 0xec))
        {
        case 0:
            cam->target.y = -0x3e8;
            cam->distance = 0x1e000;
            cam->fovy = (short)_ZN4cstd3divEii(0xf0000, 0x168);
            break;
        case 1:
            cam->target.y = -0x7d0;
            cam->distance = 0x28000;
            cam->fovy = (short)_ZN4cstd3divEii(0x120000, 0x168);
            break;
        }
        break;
    case 2:
        cam->distance = 0xa000;
        break;
    case 3:
        cam->distance = 0x5000;
        cam->fovy = (short)_ZN4cstd3divEii(0x140000, 0x168);
        break;
    case 4:
        cam->target.y = -0x3e8;
        cam->distance = 0x1e000;
        cam->fovy = (short)_ZN4cstd3divEii(0xf0000, 0x168);
        break;
    }
    func_ov007_020bffb8(cam);
    _ZN3G3i7LookAt_EPK7Vector3S2_S2_bP9Matrix4x3(&cam->eye, &cam->up, &cam->target, 1,
                                                 cam->viewMatrix);
    func_ov007_020c0078(cam);
    WORK->cameraPreset = preset;
}
