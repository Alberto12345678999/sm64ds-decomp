extern void (*data_0209a6fc)(void);

/* The terminate path: call the handler at data_0209a6fc. Its default is
   func_02073220, a veneer to func_0206dc4c, which calls func_0207037c(1),
   sets data_020a9ed4 to 1 and calls exit (func_0206dbf8) with 1. The EH
   runtime calls this when no handler or action table is found. */
void func_020731fc(void) {
    data_0209a6fc();
}
