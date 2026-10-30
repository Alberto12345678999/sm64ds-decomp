#include "types.h"
/* NitroSDK TPData: one touch-panel sample. The tag is func_0205ea28's
   (TP_GetCalibratedPoint), whose definition spells the same record V4. */
struct V4 {
    u16 x, y, touch, validity;
};

extern volatile struct V4 data_020a0df8[];
extern struct V4 data_020a0dd8;

extern int func_0205edc8(void);
extern void func_0205ea28(struct V4 *dst, struct V4 *src);

/* Read the touch panel through the auto-sampling ring func_0203bbc0 starts
   (data_020a0df8, nine samples, four samples a frame). Of the four samples
   before the latest index (func_0205edc8, TP_GetLatestIndexInAuto by its
   place in the TP run), an invalid one counts as untouched. The newest run
   of three touched samples has its middle one calibrated into
   data_020a0dd8 (func_0205ea28, TP_GetCalibratedPoint); with no touch at
   all it becomes a release at (0xff, 0xff), and anything in between keeps
   the last point.
   func_0203df40 copies the result into the local input record. */
void func_0203b9bc(struct V4 *out) {
    struct V4 tmp[4];
    int i;
    int flag;
    int idx;

    idx = func_0205edc8();
    flag = 0;
    for (i = 0; i < 4; i++) {
        int k = idx - 4 + i;
        if (k < 0)
            k += 9;
        if (data_020a0df8[k].touch != 0)
            flag = 1;
        if (data_020a0df8[k].validity != 0) {
            tmp[i].touch = 0;
        } else {
            tmp[i].x = data_020a0df8[k].x;
            tmp[i].y = data_020a0df8[k].y;
            tmp[i].touch = data_020a0df8[k].touch;
            tmp[i].validity = data_020a0df8[k].validity;
        }
    }

    if (tmp[3].touch != 0 && tmp[2].touch != 0 && tmp[1].touch != 0) {
        func_0205ea28(&data_020a0dd8, &tmp[2]);
    } else if (tmp[0].touch != 0 && tmp[1].touch != 0 && tmp[2].touch != 0) {
        func_0205ea28(&data_020a0dd8, &tmp[1]);
    } else if (flag == 0) {
        data_020a0dd8.touch = 0;
        data_020a0dd8.x = 0xff;
        data_020a0dd8.y = 0xff;
        data_020a0dd8.validity = 0;
    }

    *out = data_020a0dd8;
}
