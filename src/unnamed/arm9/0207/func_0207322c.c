extern unsigned char data_020aa3f4[];

/* Return the address of the soft-float status word data_020aa3f4. The
   soft-double routines (func_01ff97d8 among them) set its bit 0 on a NaN
   through this. */
void *func_0207322c(void)
{
    return data_020aa3f4;
}
