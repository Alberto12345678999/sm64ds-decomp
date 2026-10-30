extern int WM_StepDataSharing(unsigned char *dsInfo, unsigned char *sendData,
                              unsigned char *receiveData);

extern void *data_020a0f74;
extern unsigned short *data_020a0f80;

/* Step the data sharing: WM_StepDataSharing sends sendData and receives into
   data_020a0f80.
   On success store the received set's halfword at +2, the received-AID
   bitmap in WMDataSet's layout, in *out and return 1; else 0. */
int func_020406b4(unsigned char *sendData, unsigned short *out) {
    if (WM_StepDataSharing(data_020a0f74, sendData, (unsigned char *)data_020a0f80) != 0)
        return 0;
    *out = data_020a0f80[1];
    return 1;
}
