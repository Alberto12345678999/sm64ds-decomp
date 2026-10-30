extern short data_020a9dc0[];
/* Set the scan's maxChannelTime: the u16 at +6 of the WMScanParam
   data_020a9dc0. func_02068d08 sets it to 10. */
void func_02068834(int v) { data_020a9dc0[3] = v; }
