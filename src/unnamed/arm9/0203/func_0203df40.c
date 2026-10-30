#include "types.h"
#include "nitro/spi/tp.h"

/* The per-frame input record at data_020a1040 (0x24 bytes; data_020a1154
   holds four of them, one per player). func_0203dafc stores the camera's
   input yaw at 0x10 (dCamera_c.h). */
typedef struct {
    s32 frame;         /* 0x00 -- counts up once per frame here */
    TPData touch;      /* 0x04 -- the calibrated sample func_0203b9bc returns */
    u16 flags;         /* 0x0c -- 0x8000 set every frame here */
    u16 keys;          /* 0x0e -- pressed buttons (PAD_Read inlined) */
    s16 inputYaw;      /* 0x10 -- the camera's input yaw (GetAngleToCamera reads it ldrsh) */
    u8 settings[0x10]; /* 0x12 -- the link settings bytes (GetPlayerFlagByte, func_0203db3c) */
    u8 unk22;
    u8 unk23;
} Rec;

extern Rec data_020a1040;
extern u8 data_020a0f04;
extern u8 data_020a0f10;
extern u8 data_02099e18;
extern u16 data_020a0f1c;
extern int data_020a0f98;

extern void func_0203b9bc(TPData *out);
extern void func_0203ea5c(void);
extern void func_0203e20c(void);
extern void func_0203e0ac(void);
extern void func_02040724(void);

/* Sample this frame's local input into data_020a1040, the buttons and the
   calibrated touch point, then run the link step for the current mode
   (data_020a0f04: 0 local only, func_0203e0ac; 1 and 2 func_0203ea5c; 3
   func_0203e20c) and count the frame. When the mode has just dropped back to
   0 from 1 or 2, it shuts the link down with func_02040724. */
void func_0203df40(void) {
    TPData sample;
    u8 sel;

    data_020a1040.keys =
        ((*(volatile u16 *)0x4000130 | *(volatile u16 *)0x27fffa8) ^ 0x2fff) & 0x2fff;

    func_0203b9bc(&sample);

    data_020a1040.touch.x = sample.x;
    data_020a1040.touch.y = sample.y;
    data_020a1040.touch.touch = sample.touch;
    data_020a1040.touch.validity = sample.validity;
    data_020a1040.flags |= 0x8000;

    sel = data_020a0f04;
    switch (sel) {
    case 1:
        func_0203ea5c();
        break;
    case 2:
        func_0203ea5c();
        break;
    case 3:
        func_0203e20c();
        break;
    default:
        data_020a0f04 = 0;
    case 0:
        func_0203e0ac();
        break;
    }

    data_020a1040.frame += 1;

    if (data_020a0f04 == 0) {
        switch (data_020a0f98) {
        default:
        case 0:
        case 3:
            break;
        case 1:
        case 2:
            data_020a0f1c &= 0x7fff;
            func_02040724();
            data_02099e18 = 1;
            data_020a0f10 = 0;
            break;
        }
    }

    data_020a0f98 = data_020a0f04;
}
