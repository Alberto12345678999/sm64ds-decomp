/* The 0xd8-byte camera func_ov007_020c023c allocates; names as there, only
 * the three tweens this file frees. */
typedef struct Ov007Camera {
    char pad_00[0x38];
    void *eyeTween;      /* 0x38: func_ov007_020c8f64's vector tween */
    void *targetTween;   /* 0x3c: func_ov007_020c8f64's vector tween */
    void *distanceTween; /* 0x40: func_ov007_020c908c's scalar tween */
} Ov007Camera;

/* The free veneers that sit just ahead of each tween's allocator; both
 * reach the free hook func_ov007_020c3d1c with the pointer still in r0. */
extern int func_ov007_020c8f58();
extern int func_ov007_020c9080();
extern void func_ov007_020c3d1c(void *p);

/* Frees a camera and its three tweens. r4 keeps the tree's char * spelling;
 * `cam` is the typed view. */
void func_ov007_020c020c(char *r4) {
    Ov007Camera *cam = (Ov007Camera *)r4;
    func_ov007_020c8f58(cam->eyeTween);
    func_ov007_020c8f58(cam->targetTween);
    func_ov007_020c9080(cam->distanceTween);
    func_ov007_020c3d1c(r4);
}
