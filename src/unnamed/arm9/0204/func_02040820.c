extern int func_0203fd28(void);
extern int Wireless_Reset(void);
extern int data_020a0f94;
extern int data_020a0f5c;

/* Start the link as the parent (target mode 3), as func_02040790 does
   for a child: from idle enable the hardware, while starting retarget,
   while running as child retarget and reset. func_0203ea5c starts it
   from idle when data_020a0f04 is 1. */
void func_02040820(void)
{
    switch (data_020a0f94) {
    case 0:
        data_020a0f94 = 2;
        data_020a0f5c = 3;
        func_0203fd28();
        break;
    case 2:
        data_020a0f5c = 3;
        break;
    case 4:
        data_020a0f5c = 3;
        Wireless_Reset();
        break;
    case 1:
    case 3:
        break;
    }
}
