extern void (*data_0209a6fc)(void);

/* The terminate path: call the handler at data_0209a6fc. Its default is
   func_02073220, which tail-calls abort. The EH runtime calls this when no
   handler or action table is found.
   This is MSL's std::terminate (NMWException.cp): compiled as C++ with
   `static terminate_handler thandler = dthandler;` and
   `extern void terminate() { thandler(); }` in namespace std, mwccarm emits
   _ZSt9terminatev with these bytes, and data_0209a6fc is thandler. It keeps
   its address name because its five callers in the EH runtime
   (func_02071be8, func_02071d3c, func_02072014, func_02072168,
   func_020729f4) are C sources, which cannot spell the mangled name; the
   rename goes with their conversion to C++. */
void func_020731fc(void) {
    data_0209a6fc();
}
