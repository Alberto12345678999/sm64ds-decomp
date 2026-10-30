struct E { unsigned int f0; unsigned int f4; int f8; };

/* EH runtime: binary search of count index entries for the one whose
   [f0, f0 + (f4 & ~1)] range holds key. Returns 0 when none does.
   func_02072dac calls it. */
struct E *func_02072ed0(struct E *base, int count, unsigned int key)
{
    int lo = 0, hi = count - 1;
    while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        struct E *e = &base[mid];
        unsigned int v = e->f0;
        if (key < v) { hi = mid - 1; }
        else if (key > v + (e->f4 & ~1u)) { lo = mid + 1; }
        else { return e; }
    }
    return 0;
}
