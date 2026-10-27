//cpp
#include "types.h"
#include "Ov007Touch.h"
#include "Ov007Work.h"
#include "cstd.h"

extern "C" {

/* func_ov007_020b9ca8 @ 0x020b9ca8 (ov007, size 0x264)
 * Minigame cursor/pen update: advances the shared pen state, spawns the
 * touch feedback (sound id 0x25..0x28 by rhythm), fades the music with pen
 * hold time, and counts the scene's idle frames.
 */

/* The 0xd0-byte touch picker func_ov007_020c690c builds. Names follow
 * func_ov007_020c5a6c's own struct; only the slots this file touches. */
typedef struct Ov007Picker {
    char pad_00[8];
    int groupCount; /* 0x08: committed strokes */
    char pad_0c[0x4c];
    int hitGroup;      /* 0x58: picked group, -1 = none */
    int hitIndex;      /* 0x5c: picked point in that group, -1 = none */
    Vector3 hitOffset; /* 0x60 */
} Ov007Picker;

/* data_ov007_02104ba0: the 0x4c record func_ov007_020b9880 allocates. Only
 * the slots this file touches are spelled; +0x1c (0 here, 0/1/6 in
 * func_ov007_020ba368) has no role yet and stays raw. */
typedef struct Ov007PickerScene {
    Ov007Picker *picker; /* 0x00: func_ov007_020c690c */
    char pad_04[0x20];
    int restartCount; /* 0x24: func_ov007_020ba2e0 counts each restart; the tap
                       * sound below cycles on it */
    int idleFrames;   /* 0x28: frames with no touch and no key; func_ov007_020b8fb4
                       * tests >= 0xf0, func_ov007_020b9f0c presets 0xf0 */
} Ov007PickerScene;

/* The overlay's camera (func_ov007_020c023c); only the slot this file reads. */
typedef struct Ov007Camera {
    char pad_00[0x2c];
    int distance; /* 0x2c: func_ov007_020bffb8 places the eye this far from the target */
} Ov007Camera;

/* The 0x70-byte key record func_ov007_020c2304 allocates;
 * func_ov007_020c20b8 stores the held keys at +0. */
typedef struct Ov007Pad {
    u16 keys; /* 0x00: held this frame */
} Ov007Pad;

extern char *data_ov007_0210342c;
extern char *data_ov007_02104ba0;
/* The externs keep the tree's char * spelling (the declaration-agreement
 * gate); the typed views are reached through cast macros. */
#define WORK ((Ov007Work *)data_ov007_0210342c)
#define SCENE ((Ov007PickerScene *)data_ov007_02104ba0)

extern void func_ov007_020bb4b0(void);
extern int func_ov007_020c1da0(int);
extern void func_ov007_020bfe4c(char *, int, int, int, int *);
extern void func_ov007_020c5a6c(void *, int *, int);
extern void func_ov007_020bdeb0(int);
extern void func_ov007_020bbc08(int, int, int);
extern void func_ov007_020c6314(char *, int, int);
extern void func_ov007_020c5fc8(char *, int, int);
extern void func_ov007_020c5948(char *, int *);

void func_ov007_020b9ca8(void)
{
    Ov007Picker *r5 = SCENE->picker;
    Ov007Touch *r4 = WORK->touch;
    int v[3];

    func_ov007_020bb4b0();

    if (r4->cur.touch != 0 && r4->heldFrames >= 1 && func_ov007_020c1da0(0) == 0) {
        Ov007Camera *camera;
        *(int *)(data_ov007_02104ba0 + 0x1c) = 0;
        camera = WORK->cameras[0];
        func_ov007_020bfe4c((char *)camera, r4->cur.x << 12, r4->cur.y << 12, -camera->distance, v);
        if (r4->heldFrames == 1) {
            int s;
            func_ov007_020c5a6c(r5, v, 0);
            s = 0x25;
            if (cstd::mod(SCENE->restartCount, 3) == 2) {
                switch (cstd::mod(SCENE->restartCount, 9)) {
                case 2:
                    s = 0x26;
                    break;
                case 5:
                    s = 0x27;
                    break;
                case 8:
                    s = 0x28;
                    break;
                }
            }
            func_ov007_020bdeb0(s);
        }
    } else if (r4->releasedFrames == 0) {
        u32 t = r4->heldFrames;
        if (t <= 5) {
            func_ov007_020bbc08(0, 0, 0);
        } else if (SCENE->picker->hitGroup != -1) {
            int f;
            Ov007Picker *picker;
            if ((int)t <= 5)
                f = 0;
            else if ((int)t >= 0x12c)
                f = 0x1000;
            else
                f = cstd::div((t - 5) << 12, 0x127);
            picker = SCENE->picker;
            if (picker->groupCount >= 2)
                func_ov007_020c6314((char *)picker, picker->hitGroup, 2);
            func_ov007_020c5fc8((char *)SCENE->picker, SCENE->picker->hitGroup, f);
        }
        r5->hitIndex = -1;
        r5->hitGroup = r5->hitIndex;
        r5->hitOffset.z = 0;
        r5->hitOffset.y = r5->hitOffset.z;
        r5->hitOffset.x = r5->hitOffset.y;
    }

    func_ov007_020c5948((char *)r5, v);

    if (r4->cur.touch != 0 || WORK->pad->keys != 0) {
        SCENE->idleFrames = 0;
    } else {
        SCENE->idleFrames++;
    }
}
}
