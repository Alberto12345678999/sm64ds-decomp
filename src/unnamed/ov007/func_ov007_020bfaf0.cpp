//cpp
#include "types.h"
#include "nitro/fx/fx.h"
namespace cstd { int fdiv(int a, int b); }
extern "C" void func_ov007_020bc02c(void* a, void* b);
extern "C" void func_ov007_020bbff0(void* c);
extern void* data_ov007_02104bd8;
extern const short data_02082214[];

/* The 0xd8-byte camera func_ov007_020c023c allocates; names as in
 * func_ov007_020c0128, only the slots this file reads. */
struct Ov007Camera {
    char pad_00[0x44];
    int viewMatrix[12]; /* 0x44: Matrix4x3 */
    char pad_74[0x60];
    /* 0xd4: a u16 angle; this file, like func_ov007_020b2160, indexes the
     * sine table with it >> 4 */
    unsigned short fovy;
};

/* The 0xa0-byte model record func_ov007_020bc6d4 allocates; names as in
 * func_ov007_020bc434 and func_ov007_020bc47c, only the slots this file
 * touches. */
struct Ov007Model {
    char pad_00[0x40];
    Vector3 scale; /* 0x40: ModelComponents::Render's scale (func_ov007_020bbff0) */
    char pad_4c[0x48];
    int visible; /* 0x94: func_ov007_020bbff0 renders only while it is nonzero */
};

/* data_ov007_02104bd8's record; only its second word, the model:
 * func_ov007_020bfbdc sets it up (func_ov007_020bc47c), func_ov007_020bfc54
 * frees it (func_ov007_020bc53c). */
struct Ov007Data02104bd8 {
    void *pad_00;
    Ov007Model *model; /* 0x04 */
};

typedef char Ov007Camera_fovy_must_be_0xd4[(int)&((Ov007Camera *)0)->fovy == 0xd4 ? 1 : -1];
typedef char Ov007Model_visible_must_be_0x94[(int)&((Ov007Model *)0)->visible == 0x94 ? 1 : -1];

/* While the model is visible, scales it in x and z to fill the camera's view
 * at its fovy, then updates it under the camera's view matrix and renders
 * it. c keeps the char * spelling of the definition; `cam` is the typed
 * view. */
extern "C" void func_ov007_020bfaf0(char* c)
{
    Ov007Camera *cam = (Ov007Camera *)c;
    Ov007Model *r4 = (*(Ov007Data02104bd8 **)&data_ov007_02104bd8)->model;
    if (r4->visible == 0)
        return;
    unsigned int idx = cam->fovy >> 4;
    Fix12i t1 = FX_MUL(data_02082214[idx * 2], 0x1064);
    Fix12i base = r4->scale.x * 0xd800 + 0x12c000;
    Fix12i t2 = FX_MUL(base, t1);
    int denom = (short)data_02082214[idx * 2 + 1] * 0x60;
    Fix12i d = cstd::fdiv(t2, denom);
    r4->scale.z = cstd::fdiv(d, 0x5000);
    r4->scale.x = r4->scale.z;
    func_ov007_020bc02c(r4, cam->viewMatrix);
    func_ov007_020bbff0(r4);
}
