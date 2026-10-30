//cpp
/* std::terminate (MSL NMWException.cp): call the installed terminate handler.
 * The EH runtime calls it when a throw finds no handler, or no action table
 * covers a PC.
 *
 * In MSL the handler is `static terminate_handler thandler = dthandler;` in
 * the same file. Compiling that file as C++ gives these bytes for terminate
 * and mangles the handler as _ZSt8thandler. So the word at 0x0209a6fc is
 * thandler, and its initial value is std::dthandler (0x02073220). The three
 * are in separate files here, so thandler is declared extern, not static.
 */
typedef void (*terminate_handler)();

namespace std {

extern terminate_handler thandler;

void terminate() {
    thandler();
}

}
