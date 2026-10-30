#include "types.h"
#pragma opt_common_subs off
#pragma opt_loop_invariants off
#pragma optimize_for_size on
#define LM(x) ((int*)(long long)(int)(x))
#define EB(t, n) ((struct Arr *)((char *)(t) + ((n) << 4)))
#define LM2(x) ((int*)(long long)(unsigned)(x))

/* Field names from isdoverlay.c's assert strings (data_0208690c..). */
struct Elem {
    u32 m_VMA;     /* load address */
    u32 romOffset; /* func_02018b64 passes the overlay's ROM offset */
    u32 m_SIZE;
    u32 unused; /* zeroed on insert, never read */
};

struct Arr {
    u32 count;
    int pad[3]; /* [0] the swp lock word; [1] has 2 set while editing */
    struct Elem m_info[1];
};

typedef struct {
    u32 irqState;
    u32 fiqState;
    u32 mpuRegion7;
} SavedIntState;

extern struct Arr *data_020a9ec0[2];
extern const char data_020868fc;
extern const char data_0208690c;
extern const char data_0208692c;
extern const char data_0208696c;
extern const char data_0208698c;
extern const char data_020869bc;
extern const char data_020869dc;

extern void func_0206d890(SavedIntState *state);
extern void func_0206d868(const SavedIntState *state);
extern u32 func_0206dab4(u32 val, void *nVMA);
extern void func_0206d940(struct Arr *s, u32 index);
extern void func_0206d8c4(struct Arr *s, u32 index);
extern void _ZN4cstd8__assertEPKcS1_S1_i(const char *, const char *, const char *, int);

/* isdoverlay.c: record [nVMA, nVMA + size) at ROM offset lma in table type,
   in address order. Entries it covers are deleted or trimmed, an entry it
   starts inside is split, and an entry with the same start takes the new
   ROM offset and size. func_02018b64 (FS_LoadOverlayImage) calls it for
   each overlay it loads. Returns 0 for a bad type. */
int func_0206d32c(int type, u32 nVMA, u32 lma, u32 size) {
    unsigned long long end;
    unsigned long long addr64;
    int found;
    unsigned long long vma64;
    u32 i;
    u32 k;
    u32 j;
    SavedIntState state;
    struct Arr *pInfo;

    pInfo = ((unsigned)type >= 2) ? 0 : data_020a9ec0[type];
    if (!pInfo)
        return 0;
    if (size == 0)
        return 1;

    func_0206d890(&state);
    while (func_0206dab4(0x80, &pInfo->pad[0]) != 0) {
    }

    *LM(&pInfo->pad[1]) |= 2;
    addr64 = (u32)nVMA;
    if (addr64 + (u32)size > 0x100000000ULL) {
        size = (u32)(0x100000000ULL - addr64);
    }
    end = addr64 + (u32)size;

    found = 0;
    i = 0;
    vma64 = nVMA;
    for (; i < pInfo->count && !found; i++) {
        u32 ea = pInfo->m_info[i].m_VMA;
        if (ea > nVMA) {
            found = 1;
            func_0206d940(pInfo, i);
            pInfo->m_info[i].m_VMA = nVMA;
            pInfo->m_info[i].romOffset = lma;
            pInfo->m_info[i].m_SIZE = size;
            pInfo->m_info[i].unused = 0;
            j = i + 1;
            while (i + 1 < pInfo->count) {
                if ((unsigned long long)pInfo->m_info[j].m_VMA + (u32)pInfo->m_info[j].m_SIZE <=
                    end) {
                    func_0206d8c4(pInfo, i + 1);
                    continue;
                }
                {
                    long long ov = (long long)end - (long long)pInfo->m_info[j].m_VMA;
                    if (ov <= 0) break;
                    if (!(pInfo->m_info[j].m_SIZE > (u32)ov)) {
                        _ZN4cstd8__assertEPKcS1_S1_i(&data_020868fc, (const char *)0x121, &data_0208698c, 1);
                    }
                    *LM(&EB(pInfo, j)->m_info[0].m_VMA) += (u32)ov;
                    *LM(&EB(pInfo, j)->m_info[0].romOffset) += (u32)ov;
                    *LM(&EB(pInfo, j)->m_info[0].m_SIZE) -= (u32)ov;
                    if (!(pInfo->m_info[j].m_SIZE != 0)) {
                        _ZN4cstd8__assertEPKcS1_S1_i(&data_020868fc, (const char *)0x127, &data_020869bc, 1);
                    }
                    if (!(pInfo->m_info[j].m_SIZE < 0xf0000000)) {
                        _ZN4cstd8__assertEPKcS1_S1_i(&data_020868fc, (const char *)0x128, &data_020869dc, 1);
                    }
                    break;
                }
            }
        } else if (ea <= nVMA) {
            if (vma64 < (unsigned long long)(u32)ea + (u32)pInfo->m_info[i].m_SIZE) {
                if (!(ea <= nVMA)) {
                    _ZN4cstd8__assertEPKcS1_S1_i(&data_020868fc, (const char *)0x12e, &data_0208690c, 1);
                }
                if (!((unsigned long long)(u32)pInfo->m_info[i].m_VMA +
                          (u32)pInfo->m_info[i].m_SIZE >
                      vma64)) {
                    _ZN4cstd8__assertEPKcS1_S1_i(&data_020868fc, (const char *)0x12f, &data_0208692c, 1);
                }
                if (nVMA != pInfo->m_info[i].m_VMA) {
                    u32 ni;
                    struct Arr *dstb;
                    struct Arr *srcb;
                    func_0206d940(pInfo, i);
                    ni = i + 1;
                    dstb = EB(pInfo, i);
                    srcb = EB(pInfo, ni);
                    i = ni;
                    dstb->m_info[0] = srcb->m_info[0];
                    dstb->m_info[0].m_SIZE = nVMA - dstb->m_info[0].m_VMA;
                    *LM(&srcb->m_info[0].m_VMA) += dstb->m_info[0].m_SIZE;
                    *LM(&srcb->m_info[0].romOffset) += dstb->m_info[0].m_SIZE;
                    *LM(&srcb->m_info[0].m_SIZE) -= dstb->m_info[0].m_SIZE;
                }
                if (!(nVMA == pInfo->m_info[i].m_VMA)) {
                    _ZN4cstd8__assertEPKcS1_S1_i(&data_020868fc, (const char *)0x13c, &data_0208696c, 1);
                }
                if (pInfo->m_info[i].m_SIZE <= size) {
                    found = 1;
                    pInfo->m_info[i].romOffset = lma;
                    pInfo->m_info[i].m_SIZE = size;
                    k = i + 1;
                    while (i + 1 < pInfo->count) {
                        u32 wc = pInfo->m_info[k].m_SIZE;
                        u32 wa = pInfo->m_info[k].m_VMA;
                        if ((unsigned long long)wa + (u32)wc <= end) {
                            func_0206d8c4(pInfo, i + 1);
                            continue;
                        }
                        {
                            long long ov = (long long)end - (long long)wa;
                            if (ov <= 0) break;
                            if (!(wc > (u32)ov)) {
                                _ZN4cstd8__assertEPKcS1_S1_i(&data_020868fc, (const char *)0x151, &data_0208698c, 1);
                            }
                            *LM(&EB(pInfo, k)->m_info[0].m_VMA) += (u32)ov;
                            *LM(&EB(pInfo, k)->m_info[0].romOffset) += (u32)ov;
                            *LM(&EB(pInfo, k)->m_info[0].m_SIZE) -= (u32)ov;
                        }
                    }
                } else {
                    found = 1;
                    *LM(&EB(pInfo, i)->m_info[0].m_VMA) += size;
                    *LM(&EB(pInfo, i)->m_info[0].romOffset) += size;
                    *LM(&EB(pInfo, i)->m_info[0].m_SIZE) -= size;
                    func_0206d940(pInfo, i);
                    pInfo->m_info[i].m_VMA = nVMA;
                    pInfo->m_info[i].romOffset = lma;
                    pInfo->m_info[i].m_SIZE = size;
                    pInfo->m_info[i].unused = 0;
                }
            }
        }
    }

    if (!found) {
        func_0206d940(pInfo, i);
        pInfo->m_info[i].m_VMA = nVMA;
        pInfo->m_info[i].romOffset = lma;
        pInfo->m_info[i].m_SIZE = size;
        pInfo->m_info[i].unused = 0;
    }

    *LM2(&pInfo->pad[1]) &= ~2;
    pInfo->pad[0] = 0;
    func_0206d868(&state);
    return 1;
}
