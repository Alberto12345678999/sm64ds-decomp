extern void (*data_020a0f90)(short *);

/* Report the channel measurement's outcome to the caller's callback
   (data_020a0f90, set by func_0203f9d4): a positive x is the chosen channel,
   sent as {0, channel}; zero or a negative error code is sent as {x, 0}.
   func_0203e978 reads the pair as {result, channel}. */
void func_0203f650(int x) {
    short v[2];
    void (*fn)(short *) = data_020a0f90;
    if (fn == 0)
        return;
    if (x > 0) {
        v[0] = 0;
        v[1] = (short)x;
    } else {
        v[0] = (short)x;
        v[1] = 0;
    }
    fn(v);
}
