#include "types.h"
#pragma opt_common_subs off
#pragma opt_loop_invariants off
#pragma optimize_for_size on
#define LM(x) ((int*)(long long)(int)(x))
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

extern void func_0206d890(SavedIntState *state);
extern void func_0206d868(const SavedIntState *state);
extern u32 func_0206dab4(u32 value, void *lock);
extern void func_0206d940(struct Arr *s, u32 index);
extern void func_0206d8c4(struct Arr *s, u32 index);
extern void _ZN4cstd8__assertEPKcS1_S1_i(const char *, const char *, const char *, int);

/* isdoverlay.c (the debugger's overlay table, named by the assert strings):
   remove [nVMA, nVMA + size) from table type (0 or 1; FS_EndOverlay passes
   its overlay's target processor). An entry inside the range is deleted, an
   entry crossing either end is split or trimmed. Interrupts are off and the
   table's lock word is held for the edit. Returns 0 for a bad type. */
int func_0206cf98(int type, u32 nVMA, u32 size) {
    unsigned long long end;
    unsigned long long addr64;
    int found;
    u32 i;
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
    for (i = 0; i < pInfo->count && !found; i++) {
        u32 ea = pInfo->m_info[i].m_VMA;
        if (ea > nVMA) {
            if ((unsigned long long)(u32)ea + (u32)pInfo->m_info[i].m_SIZE <= end) {
                size -= ea - nVMA;
                nVMA = ea;
                found = 1;
            }
        }
        if (ea <= nVMA) {
            if (nVMA < (unsigned long long)(u32)ea + (u32)pInfo->m_info[i].m_SIZE) {
                found = 1;
            }
        }
        if (!found) continue;

        if (!(ea <= nVMA)) {
            _ZN4cstd8__assertEPKcS1_S1_i(&data_020868fc, (const char *)0x1a9, &data_0208690c, 1);
        }
        if (!((unsigned long long)(u32)pInfo->m_info[i].m_VMA + (u32)pInfo->m_info[i].m_SIZE >
              nVMA)) {
            _ZN4cstd8__assertEPKcS1_S1_i(&data_020868fc, (const char *)0x1aa, &data_0208692c, 1);
        }

        if (nVMA != pInfo->m_info[i].m_VMA) {
            u32 ni;
            struct Arr *dstb;
            struct Arr *srcb;
            func_0206d940(pInfo, i);
            ni = i + 1;
            dstb = (struct Arr *)((char *)pInfo + (i << 4));
            srcb = (struct Arr *)((char *)pInfo + (ni << 4));
            i = ni;
            dstb->m_info[0] = srcb->m_info[0];
            dstb->m_info[0].m_SIZE = nVMA - dstb->m_info[0].m_VMA;
            *LM(&srcb->m_info[0].m_VMA) += dstb->m_info[0].m_SIZE;
            *LM(&srcb->m_info[0].romOffset) += dstb->m_info[0].m_SIZE;
            *LM(&srcb->m_info[0].m_SIZE) -= dstb->m_info[0].m_SIZE;
        }

        if (!(nVMA == pInfo->m_info[i].m_VMA)) {
            _ZN4cstd8__assertEPKcS1_S1_i(&data_020868fc, (const char *)0x1b7, &data_0208696c, 1);
        }

        if (pInfo->m_info[i].m_SIZE <= size) {
            func_0206d8c4(pInfo, i);
            while (i < pInfo->count) {
                u32 wc = pInfo->m_info[i].m_SIZE;
                u32 wa = pInfo->m_info[i].m_VMA;
                if ((unsigned long long)(u32)wa + (u32)wc <= end) {
                    func_0206d8c4(pInfo, i);
                    continue;
                }
                {
                    long long ov = (long long)end - (long long)(u32)wa;
                    if (ov <= 0) break;
                    if (!(wc > (u32)ov)) {
                        _ZN4cstd8__assertEPKcS1_S1_i(&data_020868fc, (const char *)0x1ca, &data_0208698c, 1);
                    }
                    *LM(&((struct Arr *)((char *)pInfo + (i << 4)))->m_info[0].m_VMA) += (u32)ov;
                    *LM(&((struct Arr *)((char *)pInfo + (i << 4)))->m_info[0].romOffset) +=
                        (u32)ov;
                    *LM(&((struct Arr *)((char *)pInfo + (i << 4)))->m_info[0].m_SIZE) -= (u32)ov;
                }
            }
        } else {
            struct Arr *eb = (struct Arr *)((char *)pInfo + (i << 4));
            *LM(&eb->m_info[0].m_VMA) += size;
            *LM(&eb->m_info[0].romOffset) += size;
            *LM(&eb->m_info[0].m_SIZE) -= size;
        }
    }

    *LM2(&pInfo->pad[1]) &= ~2;
    pInfo->pad[0] = 0;
    func_0206d868(&state);
    return 1;
}
