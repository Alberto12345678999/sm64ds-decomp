//cpp
#include "OAM.h"

extern "C" {

extern void func_0202345c(void);
extern void func_02018efc(void);
extern int func_02019018(void);
extern void func_0200f4b4(void);
extern void func_0200f468(void);
extern void func_02018ec0(void);

typedef int (*VFN)(void* o);
typedef struct Obj {
    VFN* vt;
} Obj;

extern Obj* data_0209d4a8;

/* The main loop's frame start (func_020197b8, step 2). The scene's
   GraphCallback0 (data_0209d4a8) returning 0 skips OAM::Reset, the
   matrix-stack reset (func_0200f4b4, while the 3D engines are on), the
   empty func_0200f468 and the stage wipe (func_02018ec0); the soft-reset
   fader (func_0202345c) and the scene fader (func_02018efc) step either
   way. */
void func_02019390(void)
{
    Obj* o = data_0209d4a8;
    if (o != 0) {
        if (o->vt[0](o) == 0) {
            func_0202345c();
            func_02018efc();
            return;
        }
    }
    OAM::Reset();
    if (func_02019018() != 0) {
        func_0200f4b4();
    }
    func_0200f468();
    func_0202345c();
    func_02018efc();
    func_02018ec0();
}
}
