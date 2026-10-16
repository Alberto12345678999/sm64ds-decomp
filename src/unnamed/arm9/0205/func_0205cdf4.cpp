//cpp
extern "C" {
extern unsigned int _ZN3IRQ7DisableEv(void);
extern void _ZN3IRQ7RestoreEj(unsigned int saved);
extern void func_0205c788(char *self, int arg);
extern void func_0205d8d8(void *node, void *list);
extern void func_0205cfa4(char *self);
extern void OS_SleepThread(char *self);
extern int func_0205cf5c(char *self);

/* The ROM materialises each of these flag tests as 0/1 before branching on it. */
static inline int HasBits(int word, int bits) {
    return (word & bits) != 0;
}

#pragma opt_loop_invariants off
int func_0205cdf4(char *self, int arg1)
{
    char *list = *(char **)(self + 8);
    unsigned int mask = 1 << arg1;
    unsigned int saved;

    *(int *)(self + 0x10) = arg1;
    *(int *)(self + 0x14) = 2;
    *(int *)(self + 0xc) |= 1;
    saved = _ZN3IRQ7DisableEv();
    if (*(int *)(list + 0x10) & 0x80) {
        func_0205c788(self, 3);
        _ZN3IRQ7RestoreEj(saved);
        return 0;
    }
    if (mask & 0x1fc) {
        *(int *)(self + 0xc) |= 4;
    }
    func_0205d8d8(self, list + 0x14);
    if (!HasBits(*(int *)(list + 0x10), 0x10)) {
        *(int *)(list + 0x10) |= 0x10;
        _ZN3IRQ7RestoreEj(saved);
        if (*(int *)(list + 0x4c) & 0x200) {
            (*(void (**)(char *, int))(list + 0x48))(self, 9);
        }
        if (!HasBits(*(int *)(self + 0xc), 4)) {
            func_0205cfa4(self);
            return 1;
        }
    } else {
        if (!HasBits(*(int *)(self + 0xc), 4)) {
            _ZN3IRQ7RestoreEj(saved);
            return 1;
        }
        do {
            OS_SleepThread(self + 0x18);
        } while ((int)self != *(int *)(list + 0x18));
        _ZN3IRQ7RestoreEj(saved);
    }
    return func_0205cf5c(self);
}
}
