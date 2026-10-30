//cpp
#include "types.h"
#include "cstd.h"

extern "C" {

extern void Crash(void);
typedef struct {
    const char* name;
    char pad[0xc];
} Entry16;

typedef struct {
    char pad[0x1c];
    u32 count;
    Entry16* entries;
} Table2;

/* The index of the BMD palette named name: a search of the palette table
   (count at +0x1c, 0x10-byte entries at +0x20). An unknown name crashes.
   dExtAnmTexPat_c's prepare step (func_02046d50) uses it. */
int func_02047144(const Table2* tbl, const char* name)
{
    u32 count = tbl->count;
    u32 i = 0;
    if (i < count) {
        Entry16* entries = tbl->entries;
        do {
            if (cstd::strcmp(entries[i].name, name) == 0)
                return (int)i;
            i++;
        } while (i < tbl->count);
    }
    Crash();
    return -1;
}
}
