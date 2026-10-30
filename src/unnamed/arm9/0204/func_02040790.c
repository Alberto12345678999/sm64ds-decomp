extern int func_0203fd28(void);
extern int Wireless_Reset(void);
extern int data_020a0f94;
extern int data_020a0f5c;

/* Start the link as a child (target mode 4): from idle, mark it starting
   (status 2) and enable the hardware (func_0203fd28); while starting,
   just retarget; while running as parent, retarget and reset
   (Wireless_Reset), which reconnects as a child. func_0203ea5c starts it
   from idle when data_020a0f04 is 2. */
void func_02040790(void)
{
    switch (data_020a0f94) {
    case 0:
        data_020a0f94 = 2;
        data_020a0f5c = 4;
        func_0203fd28();
        break;
    case 2:
        data_020a0f5c = 4;
        break;
    case 3:
        data_020a0f5c = 4;
        Wireless_Reset();
        break;
    case 1:
    case 4:
        break;
    }
}
