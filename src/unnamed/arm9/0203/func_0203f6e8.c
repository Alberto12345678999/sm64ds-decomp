extern short data_020a0f18;
extern void func_0203f6b4(void);
extern void func_0203f6a4(int v);

/* Finish a measurement with outcome v (a channel, or a negative error):
   keep it in data_020a0f18 for the WM_End callback to report, start
   WM_End and enter state 2. */
void func_0203f6e8(short v) {
    data_020a0f18 = v;
    func_0203f6b4();
    func_0203f6a4(2);
}
