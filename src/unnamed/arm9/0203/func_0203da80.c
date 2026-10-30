extern unsigned short data_020a0f1c;

/* The link status bits of data_020a0f1c that mask x selects.
   func_02030e4c and func_020197b8 test the error bits 0x9d with it. */
unsigned short func_0203da80(unsigned short x)
{
    return data_020a0f1c & x;
}
