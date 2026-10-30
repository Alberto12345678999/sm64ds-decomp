extern int func_02062778(int a, int b, int c);

extern int data_020a0f74;
extern int data_020a0f80;

/* Player arg0's packet in the last shared-data step: func_02062778 on the
   sharing info data_020a0f74 and received set data_020a0f80, the argument
   list of NitroSDK's WM_GetSharedDataAddress. func_0203ea5c unpacks each
   player's packet through it. */
int func_0204068c(int arg0)
{
    return func_02062778(data_020a0f74, data_020a0f80, arg0);
}
