//cpp
/* std::dthandler (MSL NMWException.cp): the default terminate handler, and
 * the initial value of std::thandler. It tail-calls abort with
 * `ldr ip, [pc]; bx ip; .word abort`. That is mwccarm's own tail call to an
 * out-of-range target, not a linker veneer.
 *
 * In MSL it is `static void dthandler() { abort(); }`, in the same file as
 * thandler and terminate. Here it has a file of its own, so it has external
 * linkage. The mangled name (_ZSt9dthandlerv) is the same either way.
 */
extern "C" void abort(void);

namespace std {

void dthandler() {
    abort();
}

}
