//cpp
// @symbol __destroy_arr
// Load-bearing: the ROM build passes -Cpp_exceptions off and has no per-file CFLAGS mechanism; the .exceptix record at 0x02073988 (length 0x74) exists only because this pragma turns exceptions back on for this file.
#pragma exceptions on

// MSL C++ runtime array-destroy helper. Runs `dtor` over the `n` elements of
// `size` bytes in reverse order; if an element destructor throws, the catch
// hands off to the terminate path. The compiler places that handler out of
// line at 0x020732e8 and emits the matching .exception / .exceptix unwind
// records, so the whole 0x74-byte range plus both unwind entries come from
// this one function. `__cxa_vec_cleanup` is a second name for this entry.

extern "C" void func_020731fc(void);

typedef void (*dtor_t)(void *);

extern "C" void __destroy_arr(void *block, unsigned int n, unsigned int size, dtor_t dtor)
{
    if (dtor) {
        char *p = (char *)block + n * size;
        try {
            if (n) {
                do {
                    p -= size;
                    dtor(p);
                } while (--n);
            }
        } catch (...) {
            func_020731fc();
        }
    }
}
