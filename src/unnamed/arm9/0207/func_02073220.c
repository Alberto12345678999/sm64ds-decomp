/* The default terminate handler, the initial value of data_0209a6fc, which
 * func_020731fc calls: a tail call to abort (ldr ip, [pc]; bx ip; .word
 * abort). The `ldr ip` form is mwccarm's own tail call to an external
 * function, not a linker veneer: MSL's `static void dthandler() { abort(); }`
 * (NMWException.cp, namespace std) compiles to these bytes as
 * _ZSt9dthandlerv. In MSL it is static and shares a file with thandler and
 * terminate, so it keeps its address name until func_020731fc can take
 * std::terminate's.
 */
extern void abort(void);

void func_02073220(void) {
    abort();
}
