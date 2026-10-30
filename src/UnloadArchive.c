#include "private/arm9_archive_table.h"

extern void func_02018908(void *archive, void *heap);

/* Give archive i back to the heap it came from, if it is mounted. */
void UnloadArchive(int i) {
    ArchiveTableEntry *p = &data_0208ecf4[i];
    void *a = p->archive;
    if (a == 0)
        return;
    func_02018908(a, p->heap);
    p->archive = 0;
    p->heap = 0;
}
