extern unsigned char data_020aa3f8[];

/* Return the address of the floating-point handler table data_020aa3f8:
   a head word, then the five handlers func_0206de14 in cstd4.cpp picks by
   the exception bits 26..30 of its flags word (its FpHandlerTable).
   func_01ffafd4 clears it at startup. */
void *func_02073238(void)
{
    return data_020aa3f8;
}
