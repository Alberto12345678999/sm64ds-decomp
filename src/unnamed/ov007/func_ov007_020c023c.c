#include "Ov007Tween.h"

extern char* func_ov007_020c3df4(int,int);
extern Ov007VecTween *func_ov007_020c8f64(Vector3 *out);
extern void *func_ov007_020c908c(void *out);
extern void func_ov007_020c0128(void*);

/* The 0xd8-byte camera allocated below; eye/target/distance as in
 * func_ov007_020c0128, the tweens as in func_ov007_020b1718. Each tween is
 * bound here to the field it drives; func_ov007_020bff38 runs the three
 * while their `tweening` bits (0 eye, 1 target, 2 distance) are set. */
typedef struct Ov007Camera {
    char pad_00[8];
    Vector3 eye;    /* 0x08 */
    Vector3 target; /* 0x14 */
    char pad_20[0xc];
    int distance; /* 0x2c */
    char pad_30[8];
    Ov007VecTween *eyeTween;    /* 0x38: func_ov007_020c8f64 */
    Ov007VecTween *targetTween; /* 0x3c: func_ov007_020c8f64 */
    Ov007Tween *distanceTween;  /* 0x40: func_ov007_020c908c */
} Ov007Camera;

typedef char Ov007Camera_size_must_be_0x44[sizeof(Ov007Camera) == 0x44 ? 1 : -1];

/* Allocates a camera, binds its three tweens and resets it
 * (func_ov007_020c0128). */
Ov007Camera *func_ov007_020c023c(void) {
    Ov007Camera *cam = (Ov007Camera *)func_ov007_020c3df4(0, 0xd8);
    cam->eyeTween = func_ov007_020c8f64(&cam->eye);
    cam->targetTween = func_ov007_020c8f64(&cam->target);
    cam->distanceTween = (Ov007Tween *)func_ov007_020c908c(&cam->distance);
    func_ov007_020c0128(cam);
    return cam;
}
