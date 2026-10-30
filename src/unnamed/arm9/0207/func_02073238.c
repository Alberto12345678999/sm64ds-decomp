extern unsigned char data_020aa3f8[];

/* Return the address of the floating-point handler table data_020aa3f8:
   a head word, then the handlers func_0206de14 in cstd4.cpp picks by the
   exception flags. _fp_init clears it at startup. */
void *func_02073238(void)
{
    return data_020aa3f8;
}
