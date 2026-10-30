extern void (*data_0209a6fc)(void);

/* The terminate path: call the handler at data_0209a6fc. Its default is
   func_02073220, which tail-calls abort. The EH runtime calls this when no
   handler or action table is found.
   This is MSL's std::terminate (NMWException.cp): compiled as C++ with
   `static terminate_handler thandler = dthandler;` and
   `extern void terminate() { thandler(); }` in namespace std, mwccarm emits
   _ZSt9terminatev with these bytes, and data_0209a6fc is thandler. It keeps
   its address name until its callers can call std::terminate by name: five
   EH-runtime C sources (func_02071be8, func_02071d3c, func_02072014,
   func_02072168, func_020729f4) and three C++ ones that declare it
   extern "C" (__cxa_vec_cleanup, func_02073300, func_02073534). */
void func_020731fc(void) {
    data_0209a6fc();
}
