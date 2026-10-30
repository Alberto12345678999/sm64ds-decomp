#include "types.h"
extern void func_0203f650(int x);
extern void func_0203f8a4(void);
struct WMMeasureChannelCallback;
extern void func_0203f714(struct WMMeasureChannelCallback *s);
extern void func_0203f6a4(int v);
extern s16 data_020a0f18;
extern int data_020a0f90;

/* The WM callback for the channel measurement. o is the SDK callback
   record: o[0] the apiid, o[1] the errcode. Initialize (0) fails with -2
   or starts measuring, measure-channel (0x1e) goes to func_0203f714, and
   WM_End (2) returns to idle, reports data_020a0f18 and drops the caller's
   callback. Anything else just reports. */
void func_0203f920(u16 *o) {
    switch (o[0]) {
    case 0:
        if (o[1] != 0)
            func_0203f650(-2);
        else
            func_0203f8a4();
        break;
    case 0x1e:
        func_0203f714((struct WMMeasureChannelCallback *)o);
        break;
    case 2:
        func_0203f6a4(3);
        func_0203f650(data_020a0f18);
        data_020a0f90 = 0;
        break;
    default:
        func_0203f650(data_020a0f18);
        break;
    }
}
