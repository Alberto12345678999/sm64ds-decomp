extern int func_02062df0(int a, int b, int c);

extern int data_020a0f74;
extern unsigned short *data_020a0f80;

/* Step the data sharing: func_02062df0 sends arg0 and receives into
   data_020a0f80 (the argument list of NitroSDK's WM_StepDataSharing).
   On success store the received set's halfword at +2, the received-AID
   bitmap in WMDataSet's layout, in *out and return 1; else 0. */
int func_020406b4(int arg0, unsigned short *out)
{
    if (func_02062df0(data_020a0f74, arg0, (int)data_020a0f80) != 0)
        return 0;
    *out = data_020a0f80[1];
    return 1;
}
