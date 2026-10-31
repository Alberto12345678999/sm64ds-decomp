extern unsigned int data_020aa3f4;

/* Return the address of the soft-float status word data_020aa3f4. The
   soft-double routines (func_01ff97d8 among them) read it through this on
   a NaN: bit 8 enabled sends them to the trap, otherwise they set bit 0.
   Those are the invalid-operation trap-enable and cumulative-flag bits of
   the ARM FPSCR layout (IOE, IOC), the word ARM's floating-point library
   reaches through __rt_fp_status_addr. With no source or probe for that
   name here, the address name stays. */
unsigned int *func_0207322c(void) {
    return &data_020aa3f4;
}
