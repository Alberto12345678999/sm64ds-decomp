/* 1 if a 6-byte MAC address (three halfwords) is all zero, else 0.
   func_0203ea5c skips the empty entries of its address table with it. */
int func_0204271c(unsigned short *o)
{
    int i;
    for (i = 0; i < 3; i++) {
        if (o[i] != 0) return 0;
    }
    return 1;
}
